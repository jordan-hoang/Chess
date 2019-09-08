add_subdirectory(lib)

add_executable(runAllTests
        testChessBoard.cpp
        testCheck.cpp
        )

target_link_libraries(runAllTests
  gmock
  gtest
  gtest_main
  ${libchess}
 )

add_test(NAME AllTests COMMAND runAllTests)

