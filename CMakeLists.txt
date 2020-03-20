cmake_minimum_required(VERSION 2.8)

project (iniparser)

SET(CMAKE_SYSTEM_NAME Linux)  

if(APPLE)
  include_directories( /usr/local/include )
  link_directories( /usr/local/lib/ )
  set(CMAKE_MACOSX_RPATH ON)
endif()

include_directories( lib/include/ )
file(GLOB headers "lib/include/*.h" )
file(GLOB sources "lib/src/*.c" )

IF(TESTS)

  file(GLOB headers_test ${headers} "tests/include/*.h" )
  file(GLOB sources_test ${sources} "tests/src/*.cpp" )
  add_executable(iniparser_test ${sources_test} ${headers_test})
  target_link_libraries( iniparser_test utils CppUTest CppUTestExt)  

ELSE()

  add_library(iniparser SHARED ${sources} ${headers})
  target_link_libraries(iniparser utils)  

  set (VERSION 1.0.0)
  add_definitions (-DCMAKE -DVERSION=\"${VERSION}\")

  set_target_properties(iniparser PROPERTIES
    OUTPUT_NAME iniparser
    VERSION ${VERSION}
    SOVERSION 1
  )

  install(TARGETS iniparser DESTINATION /usr/local/lib)
  install(FILES "lib/include/iniparser.h" DESTINATION /usr/local/include)
  install(FILES "lib/include/dictionary.h" DESTINATION /usr/local/include)
  
ENDIF(TESTS)


