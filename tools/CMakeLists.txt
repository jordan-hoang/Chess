
add_executable(chessGame
        Main.cpp
        graphicalMain.cpp)


find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)


set_target_properties(chessGame
        PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 17
        PREFIX ""
        )



SET(SOIL SOIL)
link_directories(/usr/local/lib/) #Path to SOIL

include_directories(${GLUT_INCLUDE_DIRS})





target_link_libraries(chessGame
        glfw
        gladlib
        ${OPENGL_LIBRARIES}
        ${SOIL}
        ${libchess}
        ${libcolor}
        ${CMAKE_THREAD_LIBS_INIT}
        ${GLEW_LIBRARIES}
        )



install(TARGETS chessGame
        RUNTIME DESTINATION bin
        )


add_subdirectory(include)