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
#define CFG_HEADSET_SUPPORT       "handsetGeneral:headsetSupport"

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
#define CFG_CTRL_CALL_SHAREMEM    "controlCall:sharedmem"

// general
#define CFG_PRODUCT		  			    "general:product"
#define CFG_PRODUCT_VERSION       "general:version"
#define CFG_TYPE		  			      "general:type"
#define CFG_DATABASE	  			    "general:database_path"

// bus
#define CFG_CTRL_CALL_BUSID			  "bus:controlcall_id"
#define CFG_HANDSET_BUSID         "bus:handset_id"

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
 * This enum stores the status of each parsed line.
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
 * API FUNCTIONS
 **************************************************************************/

/*
 * Realize a open to a file with system configs.
 */
int iniparser_open();

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
int iniparser_get_config(char *pchParamName, void *pParamValue, E_PARAM_TYPE eType);


/**
 * Close the config instance.
 */
void iniparser_close();

/**
 * @brief    Retrieves the number of sections in a dictionary
 * @param    pDictionary  Dictionary to examine
 *
 * @return   int Number of sections found in a dictionary
 */
int iniparser_getnsec(dictionary *pDictionary);

/**
 * @brief    Retrieves the n section name in a dictionary.
 * @param    pDictionary   Dictionary to examine
 * @param    numSection   Section number (from 0 to nsec-1).
 *
 * @return   Pointer to char string
 */
char *iniparser_getsecname(dictionary *pDictionary, int numSection);

/**
 * @brief    Saves a dictionary to an ini file
 * @param    pDictionary   Dictionary to dump
 * @param    pFile   Opened file pointer to dump to
 *
 * @return   void
 */
void iniparser_dump_ini(dictionary *pDictionary, FILE *pFile);

/**
 * @brief    Saves a dictionary to an ini file
 * @param    pDictionary    Dictionary to dump
 * @param    pchSecName   Dictionary section name for dump
 * @param    pFile   File pointer open for dump
 *
 * @return   void
 */
void iniparser_dumpsection_ini(dictionary *pDictionary, char *pchSlection, FILE *pFile);

/**
 * @brief    Dump a dictionary for open file pointer.
 * @param    pDictionary    Dictionary to dump
 * @param    pFile   open file pointer to dump.
 *
 * @return   void
 */
void iniparser_dump(dictionary *pDictionary, FILE *pFile);

/**
 * @brief    Retrieves the number of parameters in a section of a dictionary.
 * @param    pDictionary   Dictionary to dump
 * @param    pchSecName   Dictionary section name to browse
 *
 * @return   Number of parameters in section
 */
int iniparser_getsecnkeys(dictionary *pDictionary, char *pchSection);

/**
 * @brief    Retrieves the number of parameters in a section of a dictionary.
 * @param    pDictionary   Dictionary to dump
 * @param    pchSecName   Dictionary section name to browse
 *
 * @return   pointer to a previously allocated string
 */
char **iniparser_getseckeys(dictionary *pDictionary, char *pchSection);

/**
 * @brief    Recupera a string associada ao parâmetro
 * @param    pDictionary   Dictionary Search
 * @param    pchKey     Parameter to be searched for
 * @param    pchDef     Default value for return if parameter is not found.
 *
 * @return   pointer to a previously allocated string
 */
char *iniparser_getstring(dictionary *pDictionary, const char *pchKey, char *pchDef);

/**
 * @brief    Retrieves the associated string for the parameter converts to int
 * @param    pDictionary Search dictionary
 * @param    pchKey parameter to be searched
 * @param    notfound Return value in case of error
 *
 * @return   integer
 */
int iniparser_getint(dictionary *pDictionary, const char *pchKey, int notfound);

/**
 * @brief    Retrieves associated string for parameter converts to double
 * @param    pDictionary Dictionary Search
 * @param    pchKey desired parameter
 * @param    notfound Return value in case of error
 *
 * @return   double
 */
double iniparser_getdouble(dictionary *pDictionary, const char *pchKey, double notfound);

/**
 * @brief    Recupera string associada para o parâmetro converte para bool
 * @param    pDictionary Dictionary Search
 * @param    pchKey desired parameter
 * @param    notfound Return value in case of error
 *
 * @return   double
 */
int iniparser_getboolean(dictionary *pDictionary, const char *pchKey, int notfound);

/**
 * @brief    Set of entries for a dictionary.
 * @param    pIni     Dictionary to be modified.
 * @param    pchEntry Entry to be modified
 * @param    pchVal   New value attached.
 *
 * @return   int 0 if Ok, -1 if not.
 */
int iniparser_set(dictionary *pIni, const char *pchEntry, const char *pVal);

/**
 * @brief    Removes an entry from a dictionary
 * @param    pIni     Dictionary to be modified
 * @param    pchEntry Input to be removed
 *
 * @return   void
 */
void iniparser_unset(dictionary *pIni, const char *pchEntry);

/**
 * @brief    Search if a certain entry exists in the dictionary
 * @param    pIni     Search dictionary
 * @param    pchEntry Name of the entry to be searched
 *
 * @return   integer 1 if exist, 0 if not exist
 */
int iniparser_find_entry(dictionary *pIni, const char *pchEntry);

/**
 * @brief    Parse an ini file and return dictionary object
 * @param    pchIniname Name of the ini file to read.
 * @return   Pointer for the memory of the new dictionary
 */
dictionary *iniparser_load(const char *pIniname);

/**
 * @brief    Releases the memory for the associated dictionary
 * @param    pDictionary Dictionary to be released
 *
 * @return   void
 */
void iniparser_freedict(dictionary *pDictionary);

#endif
