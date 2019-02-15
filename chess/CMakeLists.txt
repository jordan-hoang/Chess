add_library(chess
        src/MoveValidator.cpp
        src/Piece.cpp
        src/Board.cpp
        )

find_package(Boost 1.68 COMPONENTS system REQUIRED)

target_include_directories(chess
        PUBLIC
            $<INSTALL_INTERFACE:include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            ${CMAKE_CURRENT_SOURCE_DIR}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
        )


target_link_libraries(chess
            ${Boost_LIBRARIES}
        )

set_target_properties(chess
        PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 17
        )


install(TARGETS chess
        ARCHIVE DESTINATION lib
        )


