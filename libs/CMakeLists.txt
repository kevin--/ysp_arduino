
if( YSP_ARDUINO_TESTS )
  # Prevent overriding the parent project's compiler/linker
  # settings on Windows
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  add_subdirectory(googletest)
endif()
