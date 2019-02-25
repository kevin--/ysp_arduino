###
### ysp_arduino
###

cmake_minimum_required(VERSION 3.6)
cmake_policy( SET CMP0076 NEW )

project(ysp_arduino)

set(CMAKE_CXX_STANDARD           14  )
set(CMAKE_CXX_STANDARD_REQUIRED  ON  )
set(CMAKE_CXX_EXTENSIONS         OFF )

add_subdirectory(libs)

###
### target configuration
###

list( APPEND FILES_src inc/ysp/container/circular_buffer.h )
list( APPEND FILES_src inc/ysp/synth/sine_voice.h          )

source_group( TREE inc FILES ${FILES_src} )

add_library( ysp_arduino INTERFACE )
target_sources( ysp_arduino INTERFACE ${FILES_src} )
target_include_directories(
  ysp_arduino
  INTERFACE
    inc
)

### tests
add_subdirectory(test)
