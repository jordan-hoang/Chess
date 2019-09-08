add_library(${libchess}
        src/ChessController.cpp
        src/Piece.cpp
        src/Board.cpp
        src/MoveRecorder.cpp
        src/CheckMate.cpp
        )

find_package(Boost 1.68 COMPONENTS system REQUIRED)

target_include_directories(${libchess}
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> # this line here fixes the include/include issues
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${Boost_INCLUDE_DIR}
        )


target_link_libraries(${libchess}
        ${Boost_LIBRARIES}
        )

set_target_properties(${libchess}
        PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 17
        )


install(TARGETS ${libchess}
        ARCHIVE DESTINATION lib
        )


