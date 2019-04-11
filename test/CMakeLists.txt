add_subdirectory(lib)

add_executable(runAllTests
  # Add all new test files to the list here.
  # Place each file name on a separate line.
    testChessBoard.cpp
)

target_link_libraries(runAllTests
  gmock
  gtest
  gtest_main
  ${libchess}
 )

add_test(NAME AllTests COMMAND runAllTests)

