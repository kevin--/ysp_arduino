###
### ysp_arduino
###

cmake_minimum_required(VERSION 3.6)
cmake_policy( SET CMP0076 NEW )

project(ysp_arduino)

if( CMAKE_PROJECT_NAME STREQUAL ysp_arduino )
  set( YSP_ARDUINO_TESTS ON )
endif()

set( CMAKE_CXX_STANDARD           14  )
set( CMAKE_CXX_STANDARD_REQUIRED  ON  )
set( CMAKE_CXX_EXTENSIONS         OFF )

add_subdirectory(libs)

###
### target configuration
###

### container
list( APPEND FILES_src inc/ysp/container/circular_buffer.h )

### math
list( APPEND FILES_src inc/ysp/math/constants.h            )
list( APPEND FILES_src inc/ysp/math/functor.h              )

list( APPEND FILES_src inc/ysp/math/sine.h                 )
list( APPEND FILES_src src/ysp/math/sine.cpp               )
list( APPEND FILES_src src/ysp/math/sine_table_full.h      )
list( APPEND FILES_src src/ysp/math/sine_table_quarter.h   )

list( APPEND FILES_src inc/ysp/math/interp.h               )

### synth
list( APPEND FILES_src inc/ysp/synth/sine_voice.h          )
list( APPEND FILES_src inc/ysp/synth/voice.h               )

source_group( TREE . FILES ${FILES_src} )

add_library( ysp_arduino ${FILES_src} )
target_include_directories(
  ysp_arduino
  PUBLIC
    inc
)

if( YSP_ARDUINO_TESTS )
  ### tests
  add_subdirectory(test)
endif()
