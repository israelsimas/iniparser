/**************************************************************************
 * dictionary.h
 *
 *  Create on: 21/06/2019
 *
 *  Header File to Plataform SIP Intelbras
 *  This module implements a simple dictionary object, i.e. a list
 *  of string/string associations. This object is useful to store e.g.
 *  informations retrieved from a configuration file (ini files).
 *
 * Copyrights, 2019
 *
 **************************************************************************/

#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_

/**************************************************************************
 * INCLUDES
 **************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**************************************************************************
 * DEFINITIONS
 **************************************************************************/

/** Maior valor para integers e doubles. */
#define MAXVALSZ    1024

/** Número mínimo alocado de entradas para um dicionário */
#define DICTMINSZ   128

/** Token inválido */
#define DICT_INVALID_KEY    ((char *)-1)

/**************************************************************************
 * TYPEDEFS
 **************************************************************************/
/**
 * @brief    object dictionary
 *
 */
typedef struct _dictionary_ {
    int             n;     		
    int           size;  		
    char        **val;   		
    char        **key;   			
    unsigned     *hash;  		
} dictionary ;


/**************************************************************************
 * INTERNAL CALL FUNCTIONS
 **************************************************************************/

/**
 * @brief    Computes the hash key for a string.
 * @param    pchKey   Character of a string for use in the parameter.
 *
 * @return   1 unsigned int to at least 32 bits.
 */
unsigned dictionary_hash(const char *pchKey);

/**
 * @brief    Creates a new dictionary object.
 * @param    size    Initial dictionary size (optional).
 *
 * @return   1 dictionary allocated.
 */
dictionary *dictionary_new(int size);

/**
 * @brief    Removes a dictionary
 * @param    pDictionary   dictionary to be removed.
 *
 * @return   void
 */
void dictionary_del(dictionary *pDictionary);

/**
 * @brief    Retrieves the value of a dictionary.
 * @param    pDictionary       dictionary to be searched.
 * @param    pchKey     Parameter for dictionary search.
 * @param    pchDef     Default value for return if no parameter is found.
 *
 * @return   1 return pointer.
 */
char *dictionary_get(dictionary *pDictionary, const char *pchKey, char *pchDef);

/**
 * @brief    Sets a value for a dictionary.
 * @param    pDictionary      dictionary to modify.
 * @param    pchKey     parameter to be modified.
 * @param    pchVal     Value to insert.
 *
 * @return   int     0 if Ok
 */
int dictionary_set(dictionary *pDictionary, const char *pchKey, const char *pchVal);

/**
 * @brief    Removes a parameter from the dictionary
 * @param    pDictionary       Dictionary to be modified.
 * @param    pchKey     parameter to be removed.
 *
 * @return   void
 */
void dictionary_unset(dictionary *pDictionary, const char *pchKey);

/**
 * @brief    Dump a dictionary to a file pointer.
 * @param    pDictionary   Dictionary for dump
 * @param    pFile   open file pointer.
 *
 * @return   void
 */
void dictionary_dump(dictionary *pDictionary, FILE *pFile);

#endif
