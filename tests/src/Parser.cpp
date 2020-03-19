/**************************************************************************
 *
 * Parser.cpp
 *
 *    Parser test
 *
 * Copyright 2020 Intelbras
 *
 **************************************************************************/

#include "CppUTest/TestHarness.h"
extern "C" {
  #include <iniparser.h>
  #include "string.h"
}
 
TEST_GROUP(Parser) {

  void setup() {
    
  }

  void teardown() {
    
  }

};
 
TEST(Parser, ParserInt) {

  int integerValue;

  iniparser_open();

  // Get integer parameter
  iniparser_get_config("general:dev_id", &integerValue, TYPE_INT);
  CHECK_EQUAL(integerValue, 17);  // 17 is dev_id expected

  iniparser_close();
}

TEST(Parser, ParserString) {

  char *pchValue = NULL;

  iniparser_open();

  // Get string parameter
  iniparser_get_config("general:database_path", &pchValue, TYPE_STRING);
  STRCMP_EQUAL("/data/database.sql", pchValue);

  // Get undefined string parameter
  free(pchValue);
  pchValue = NULL;
  iniparser_get_config("general:database_path_test", &pchValue, TYPE_STRING);
  STRCMP_EQUAL(NULL, pchValue);

  iniparser_close();
}

TEST(Parser, ParserBool) {

  int boolValue;

  iniparser_open();

  // Get integer parameter
  iniparser_get_config("controlCall:ivrSupport", &boolValue, TYPE_BOOL);
  CHECK_FALSE(boolValue);

  iniparser_close();
}
