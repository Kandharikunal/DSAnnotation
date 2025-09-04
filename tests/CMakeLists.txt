# In tests/CMakeLists.txt
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.tar.gz
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
# For Windows: prevents overriding parent project compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(${CMAKE_SOURCE_DIR})
add_executable(unit_tests
    PropertyParserTest.cpp
    # Add other test files here
)

target_link_libraries(unit_tests
    gtest
    gtest_main
    parser_lib  # Link to the library instead of the executable
    # Your project libraries
)
add_test(NAME unit_tests COMMAND unit_tests)
set_tests_properties(unit_tests PROPERTIES ENVIRONMENT "GTEST_COLOR=1")