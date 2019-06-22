/**************************************************************************
 * iniparser.h
 *
 *  Create on: 21/06/2019
 *
 *  Header ini parser files
 *
 * Copyrights, 2019
 *
 **************************************************************************/

#ifndef _INIPARSER_H_
#define _INIPARSER_H_

/**************************************************************************
 * INCLUDES
 **************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

/**************************************************************************
 * DEFINITIONS
 **************************************************************************/

#define ASCIILINESZ               (1024)
#define INI_INVALID_KEY           ((char *)-1)

#define CONFIG_FILE_PATH          "/etc/resources.ini"

#define CONFIG_RELEASE_PATH       "/etc/"
#define CONFIG_RELEASE_FILE       "release"
#define PRODUCT_VERSION           "version"

/* Init config for handset */
#define CFG_HANDSETS_NUMBER       "handsetGeneral:handsetNumber"
#define CFG_HANDSETS_VERSION      "handsetGeneral:version"
#define CFG_CHANNELS_NUMBER       "handsetGeneral:channelsNumber"
#define CFG_MULTCAST_SUPPORT      "handsetGeneral:multicastSupport"
#define CFG_HANDSET_BUSID         "bus:handset_id"

// Handset Phone
#define CFG_HANDSET_TYPE          "handset%d:type"
#define CFG_NUMBER_SOFTKEYS       "handset%d:numberSoftkeys"
#define CFG_MODULE_SUPPORT        "handset%d:moduleSupport"
#define CFG_NUMBER_MODULES        "handset%d:numberModules"
#define CFG_NUMBER_KEYS_MODULE    "handset%d:numberKeysModule"
#define CFG_DISPLAY_SUPPORT       "handset%d:displaySupport"
#define CFG_CONF_SUPPORT          "handset%d:conferenceMenuKey"
#define CFG_BACKLIGHT_SUPPORT     "handset%d:backlightSupport"
#define CFG_DISPLAY_SIZE          "handset%d:displaySize"

// Control-call
#define CFG_MULT_ACCOUNTS			    "controlCall:multiAccountsSupport"
#define CFG_ACCOUNTS_NUMBER 		  "controlCall:accountNumber"
#define CFG_ACCOUNTS_PER_ENDPOINT	"controlCall:accountPerEndpoint"
#define CFG_ENDP_SERV_CODE_SUPP		"controlCall:endpointServiceCodeSupport"
#define CFG_ENDP_PHONE_BOOK_SUPP	"controlCall:endpointPhoneBookSupport"
#define CFG_ENDP_FLASH_SERV_SUPP	"controlCall:flashService"
#define CFG_SIP_SYSLOG            "controlCall:sipSyslog"
#define CFG_SYNC_STATE            "controlCall:syncState"
#define CFG_NUM_MAX_CALLS 			  "controlCall:numberMaxCalls"
#define CFG_IVR_SUPPORT		  		  "controlCall:ivrSupport"
#define CFG_CTRL_CALL_VERSION		  "controlCall:version"
#define CFG_ENDPOINT_MASTER 		  "controlCall:endpointMasterSupport"
#define CFG_HASH_URI 				      "controlCall:hashURI"
#define CFG_PRODUCT		  			    "general:product"
#define CFG_PRODUCT_VERSION       "general:version"
#define CFG_TYPE		  			      "general:type"
#define CFG_DATABASE	  			    "general:database_path"
#define CFG_CTRL_CALL_BUSID			  "bus:controlcall_id"

#define PARAM_CONFIG_NAME_SIZE    50

/**************************************************************************
 * TYPEDEFS
 **************************************************************************/

/*
 * @enum E_PARAM_TYPE
 *
 * Elements for basic parameters 
 */
typedef enum {
  TYPE_INVALID,
  TYPE_CHAR,
  TYPE_BYTE,
  TYPE_HEX,
  TYPE_INT,
  TYPE_WORD,
  TYPE_DWORD,
  TYPE_BOOL,
  TYPE_STRING,
  TYPE_DOUBLE
} E_PARAM_TYPE;

/**
 * Este enum armazena o status de cada linha parsed.
 */
typedef enum _line_status_ {
  LINE_UNPROCESSED,
  LINE_ERROR,
  LINE_EMPTY,
  LINE_COMMENT,
  LINE_SECTION,
  LINE_VALUE
} E_LINE_STATUS;

/**************************************************************************
 * INTERNAL CALL FUNCTIONS
 **************************************************************************/

/*
 * Realize a open to a file with system configs.
 */
int openConfig();

/**
 * Retrieves one or more parameters from the System Resources file.
 *
 * @param pParam pointer to parameters that need to be load.
 * @param pchParamName pointer name to parameter.
 * @param pchParamValue pointer to value.
 * @param wLength Lenght buffer that returns.
 *
 * @return int Inidicate that parameter was load with success.
 */
int getConfig(char *pchParamName, void *pParamValue, E_PARAM_TYPE eType);


/**
 * Close the config instance.
 */
void closeConfig();

/**
 * @brief    Recuper o número de seções em um dicionário
 * @param    pDictionary   Dicionário para examinar
 *
 * @return   int Número de seções encontradas em um dicionário
 */
int iniparser_getnsec(dictionary *pDictionary);

/**
 * @brief    Recupera o nome a seção n em um dicionário.
 * @param    pDictionary   Dictionary to examine
 * @param    numSection   Section number (from 0 to nsec-1).
 *
 * @return   Pointer to char string
 */
char *iniparser_getsecname(dictionary *pDictionary, int numSection);

/**
 * @brief    Salva um dicionário para um arquivo ini
 * @param    pDictionary   Dictionary to dump
 * @param    pFile   Opened file pointer to dump to
 *
 * @return   void
 */
void iniparser_dump_ini(dictionary *pDictionary, FILE *pFile);

/**
 * @brief    Salva um dicionário para um arquivo ini
 * @param    pDictionary   Dicionário para dump
 * @param    pchSecName   Nome da seção do dicionário para dump
 * @param    pFile   Ponteiro do arquivo aberto para dump
 *
 * @return   void
 */
void iniparser_dumpsection_ini(dictionary *pDictionary, char *pchSlection, FILE *pFile);

/**
 * @brief    Dump um dicionário para ponteiro de arquivo aberto.
 * @param    pDictionary   Dicionário para dump.
 * @param    pFile   ponteiro do arquivo aberto para dump.
 *
 * @return   void
 */
void iniparser_dump(dictionary *pDictionary, FILE *pFile);

/**
 * @brief    Recupera o número de parâmetros em uma seção de um dicionário.
 * @param    pDictionary  Dicionário para examinar
 * @param    pchSecName   Nome da seção do dicionário para examinar
 *
 * @return   Número de parâmetros na seção
 */
int iniparser_getsecnkeys(dictionary *pDictionary, char *pchSection);

/**
 * @brief    Recupera o número de parâmetros em uma seção de um dicionário.
 * @param    pDictionary  Dicionário para examinar
 * @param    pchSecName   Nome da seção do dicionário para examinar
 *
 * @return   ponteiro para uma string previamente alocada
 */
char **iniparser_getseckeys(dictionary *pDictionary, char *pchSection);

/**
 * @brief    Recupera a string associada ao parâmetro
 * @param    pDictionary   Dicionário para a busca
 * @param    pchKey     Parâmetro a ser procurado
 * @param    pchDef     valor Default para retorno se o parâmetro não é encontrado.
 *
 * @return   ponteiro para uma string previamente alocada
 */
char *iniparser_getstring(dictionary *pDictionary, const char *pchKey, char *pchDef);

/**
 * @brief    Recupera a string associada para o parâmetro converte para int
 * @param    pDictionary Dicionário de busca
 * @param    pchKey parâmetro a ser procurado
 * @param    notfound Valor de retorno em caso de erro
 *
 * @return   integer
 */
int iniparser_getint(dictionary *pDictionary, const char *pchKey, int notfound);

/**
 * @brief    Recupera string associada para o parâmetro converte para double
 * @param    pDictionary Dicionário para a busca
 * @param    pchKey parâmetro procurado
 * @param    notfound Valor de retorno em caso de erro
 *
 * @return   double
 */
double iniparser_getdouble(dictionary *pDictionary, const char *pchKey, double notfound);

/**
 * @brief    Recupera string associada para o parâmetro converte para bool
 * @param    pDictionary Dicionário para a busca
 * @param    pchKey parâmetro procurado
 * @param    notfound Valor de retorno em caso de erro
 *
 * @return   double
 */
int iniparser_getboolean(dictionary *pDictionary, const char *pchKey, int notfound);

/**
 * @brief    Conjunto de entradas para um dicionário.
 * @param    pIni     Dicionário para ser modificado.
 * @param    pchEntry Entrada a ser modificada
 * @param    pchVal   Novo valor assciado.
 *
 * @return   int 0 Se Ok, -1 caso não.
 */
int iniparser_set(dictionary *pIni, const char *pchEntry, const char *pVal);

/**
 * @brief    Remove uma entrada de um dicionário
 * @param    pIni     Dicionário para ser modificado
 * @param    pchEntry Entrada a ser removida
 *
 * @return   void
 */
void iniparser_unset(dictionary *pIni, const char *pchEntry);

/**
 * @brief    Busca se uma determina entrada existe no dicionário
 * @param    pIni     Dicionário de busca
 * @param    pchEntry Nome da entrada a ser procurada
 *
 * @return   integer 1 se existe, 0 outro caso
 */
int iniparser_find_entry(dictionary *pIni, const char *pchEntry);

/**
 * @brief    Parse um arquivo ini e retorna objeto de dicionário
 * @param    pchIniname Nome do arquivo ini para ler.
 * @return   Pointer para a memória do novo dicionário
 */
dictionary *iniparser_load(const char *pIniname);

/**
 * @brief    Libera a memória para o dicionário associado
 * @param    pDictionary Dicionário a ser liberado
 *
 * @return   void
 */
void iniparser_freedict(dictionary *pDictionary);

#endif
