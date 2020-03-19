/**************************************************************************
 *
 * dictionary.c
 *
 *    This module implements an object dictionary.
 *
 * Copyright 2019
 *
 **************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dictionary.h>

/**************************************************************************
 * PRIVATE FUNCTIONS
 **************************************************************************/

/* Allocation of Doubles associated with the pointer */
static void *mem_double(void *pMem, int size) {

	void *newptr;

	newptr = calloc(2 * size, 1);
	if (newptr == NULL) {
		return NULL;
	}

	memcpy(newptr, pMem, size);
	free(pMem);

	return newptr;
}

/**
 * @brief    Duplicate a string
 * @param    pchDup String to duplicate
 *
 * @return   Pointer to new allocated string
 */
static char *xstrdup(const char *pchDup) {

	char *pchTemp;

	if (!pchDup) {
		return NULL;
	}

	pchTemp = (char *) malloc(strlen(pchDup) + 1);
	if (pchTemp) {
		strcpy(pchTemp, pchDup);
	}

	return pchTemp;
}

unsigned dictionary_hash(const char *pchKey) {

	int len, i;
	unsigned hash;

	len = strlen(pchKey);
	for (hash = 0, i = 0; i < len; i++) {
		hash += (unsigned) pchKey[i];
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);

	return hash;
}

dictionary * dictionary_new(int size) {

	dictionary *pDictionary;

	/* If no size was specified, allocate space for DICTMINSZ */
	if (size < DICTMINSZ) {
		size = DICTMINSZ;
	}

	if (!(pDictionary = (dictionary *) calloc(1, sizeof(dictionary)))) {
		return NULL;
	}

	pDictionary->size = size;
	pDictionary->val  = (char **) calloc(size, sizeof(char *));
	pDictionary->key  = (char **) calloc(size, sizeof(char *));
	pDictionary->hash = (unsigned int *) calloc(size, sizeof(unsigned));

	return pDictionary;
}

void dictionary_del(dictionary *pDictionary) {

	int i;

	if (pDictionary == NULL) {
		return;
	}

	for (i = 0; i < pDictionary->size; i++) {

		if (pDictionary->key[i] != NULL) {
			free(pDictionary->key[i]);
		}

		if (pDictionary->val[i] != NULL) {
			free(pDictionary->val[i]);
		}
	}

	free(pDictionary->val);
	free(pDictionary->key);
	free(pDictionary->hash);
	free(pDictionary);

	return;
}

char *dictionary_get(dictionary *pDictionary, const char *pchKey, char *pchDef) {

	unsigned hash;
	int i;

	hash = dictionary_hash(pchKey);
	for (i = 0; i < pDictionary->size; i++) {
		if (pDictionary->key[i] == NULL)
			continue;
		/* Compare hash */
		if (hash == pDictionary->hash[i]) {
			/* Compare string, to avoid hash collisions */
			if (!strcmp(pchKey, pDictionary->key[i])) {
				return pDictionary->val[i];
			}
		}
	}

	return pchDef;
}

int dictionary_set(dictionary *pDictionary, const char *pchKey, const char *pchVal) {

	int i;
	unsigned hash;

	if ((pDictionary == NULL) || (pchKey == NULL)) {
		return -1;
	}

	/* Compute hash for this parameter*/
	hash = dictionary_hash(pchKey);
	/* Find if the value is already in the dictionary */
	if (pDictionary->n > 0) {
		for (i = 0; i < pDictionary->size; i++) {
			if (pDictionary->key[i] == NULL)
				continue;
			if (hash == pDictionary->hash[i]) { 
				if (!strcmp(pchKey, pDictionary->key[i])) {
					if (pDictionary->val[i] != NULL) {
						free(pDictionary->val[i]);
					}
					pDictionary->val[i] = pchVal ? xstrdup(pchVal) : NULL;
					return 0;
				}
			}
		}
	}
  
	if (pDictionary->n == pDictionary->size) {
		pDictionary->val = (char **) mem_double(pDictionary->val, pDictionary->size * sizeof(char *));
		pDictionary->key = (char **) mem_double(pDictionary->key, pDictionary->size * sizeof(char *));
		pDictionary->hash = (unsigned int *) mem_double(pDictionary->hash, pDictionary->size * sizeof(unsigned));
		if ((pDictionary->val == NULL) || (pDictionary->key == NULL) || (pDictionary->hash == NULL)) {
			return -1;
		}

		pDictionary->size *= 2;
	}

	for (i = pDictionary->n; pDictionary->key[i];) {
		if (++i == pDictionary->size) {
			i = 0;
		}
	}

	pDictionary->key[i]   = xstrdup(pchKey);
	pDictionary->val[i]   = pchVal ? xstrdup(pchVal) : NULL;
	pDictionary->hash[i]  = hash;
	pDictionary->n++;

	return 0;
}

void dictionary_unset(dictionary *pDictionary, const char *pchKey) {

	unsigned hash;
	int i;

	if (pchKey == NULL) {
		return;
	}

	hash = dictionary_hash(pchKey);
	for (i = 0; i < pDictionary->size; i++) {
		if (pDictionary->key[i] == NULL)
			continue;
		if (hash == pDictionary->hash[i]) {
			if (!strcmp(pchKey, pDictionary->key[i])) {
				break;
			}
		}
	}

	if (i >= pDictionary->size) {
		return;
	}

	free(pDictionary->key[i]);
	pDictionary->key[i] = NULL;
	if (pDictionary->val[i] != NULL) {
		free(pDictionary->val[i]);
		pDictionary->val[i] = NULL;
	}

	pDictionary->hash[i] = 0;
	pDictionary->n--;

	return;
}

void dictionary_dump(dictionary *pDictionary, FILE *pFile) {

	int i;

	if ((pDictionary == NULL) || (pFile == NULL)) {
		return;
	}

	if (pDictionary->n < 1) {
		fprintf(pFile, "empty dictionary\n");
		return;
	}

	for (i = 0; i < pDictionary->size; i++) {
		if (pDictionary->key[i]) {
			fprintf(pFile, "%20s\t[%s]\n", pDictionary->key[i], pDictionary->val[i] ? pDictionary->val[i] : "UNDEF");
		}
	}

	return;
}
