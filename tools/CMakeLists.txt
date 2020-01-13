
add_executable(chessGame
        Main.cpp
        )



set_target_properties(chessGame
        PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 17
        PREFIX ""
        )






target_link_libraries(chessGame
        ${libchess}
        )
