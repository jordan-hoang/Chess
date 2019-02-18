add_executable(chessTest
        main.cpp
        )

set_target_properties(chessTest
        PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 17
        PREFIX ""
        )


target_link_libraries(chessTest
        ${libchess}
        ${libcolor}
        ${CMAKE_THREAD_LIBS_INIT}
        )

install(TARGETS chessTest
        RUNTIME DESTINATION bin
        )
