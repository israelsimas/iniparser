# Iniparser

Parser to read the parameters of files of type INI.

## Command to create a project 

mkdir build && cd build/ && cmake ../

## SUBLIME ENVIROMENT
## Command to create a project in sublime

mkdir build && cd build/ && cmake -G "Sublime Text 2 - Unix Makefiles" ../

## Defines examples to insert in include from application to capture parameters

<pre>
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
#define CFG_MULT_ACCOUNTS         "controlCall:multiAccountsSupport"  
#define CFG_ACCOUNTS_NUMBER       "controlCall:accountNumber"  
#define CFG_ACCOUNTS_PER_ENDPOINT "controlCall:accountPerEndpoint"  
#define CFG_ENDP_SERV_CODE_SUPP   "controlCall:endpointServiceCodeSupport"  
#define CFG_ENDP_PHONE_BOOK_SUPP  "controlCall:endpointPhoneBookSupport"  
#define CFG_ENDP_FLASH_SERV_SUPP  "controlCall:flashService"  
#define CFG_SIP_SYSLOG            "controlCall:sipSyslog"  
#define CFG_SYNC_STATE            "controlCall:syncState"  
#define CFG_NUM_MAX_CALLS         "controlCall:numberMaxCalls"  
#define CFG_IVR_SUPPORT           "controlCall:ivrSupport"  
#define CFG_CTRL_CALL_VERSION     "controlCall:version"  
#define CFG_ENDPOINT_MASTER       "controlCall:endpointMasterSupport"  
#define CFG_HASH_URI              "controlCall:hashURI"  
#define CFG_CTRL_CALL_SHAREMEM    "controlCall:sharedmem"  

// general  
#define CFG_PRODUCT               "general:product"  
#define CFG_PRODUCT_VERSION       "general:version"  
#define CFG_TYPE                  "general:type"  
#define CFG_DATABASE              "general:database_path"  

// bus  
#define CFG_CTRL_CALL_BUSID       "bus:controlcall_id"  
#define CFG_HANDSET_BUSID         "bus:handset_id"  
</pre>
