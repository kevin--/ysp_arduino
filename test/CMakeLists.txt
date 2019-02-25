

###
### target configuration
###

list( APPEND FILES_test container/circular_buffer.test.cpp )

source_group( TREE . FILES ${FILES_test} )

add_executable( ysp_arduino_tests ${FILES_test} )
target_link_libraries(
  ysp_arduino_tests
  PRIVATE
    ysp_arduino
    gtest
    gtest_main
)
