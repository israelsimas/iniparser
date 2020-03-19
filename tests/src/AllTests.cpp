/**************************************************************************
 *
 * AllTests.cpp
 *
 *    Test runner to Sirius platform
 *
 * Copyright 2020 Intelbras
 *
 **************************************************************************/

#include "CppUTest/CommandLineTestRunner.h"
 
int main(int ac, char** av) {

  return CommandLineTestRunner::RunAllTests(ac, av);
}
