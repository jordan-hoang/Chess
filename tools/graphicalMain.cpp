//
// Created by jordan on 25/04/19.
//

#define GLFW_INCLUDE_NONE

#include <ChessController.h>
#include <boost/algorithm/string/constants.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>

#include "include/ResourceManager.h"
#include "include/Game.h"
#define GLEW_STATIC

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;




void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);


// The Width of the screen
const GLuint SCREEN_WIDTH = 800;
// The height of the screen
const GLuint SCREEN_HEIGHT = 600;

Game chess(SCREEN_WIDTH, SCREEN_HEIGHT);

int main(int argc, char *argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "ChessGame", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    ///

    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, 1);
    ///



    glewExperimental = GL_TRUE;
    glewInit();
    glGetError(); // Call it once to catch glewInit() bug, all other errors are now from our application.

    glfwSetKeyCallback(window, key_callback);

    glViewport(0, 0, SCREEN_WIDTH, SCR_HEIGHT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    chess.init();

    // DeltaTime variables


    // Start Game within Menu State
    chess.State = GAME_ACTIVE;

    double xPos = 0;
    double yPos = 0;

    while (!glfwWindowShouldClose(window))
    {
        // Calculate delta time

        glfwPollEvents();


        // Render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        chess.Render();

        glfwSwapBuffers(window);
    }


    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS) {
            //std::cout << "Pressed";

        }
        else if (action == GLFW_RELEASE) {
            //std::cout << "released";
            //.Keys[key] = GL_FALSE;
        }
    }
}


void mouse_button_callback(GLFWwindow *window, int button, int action, int mods){
    double xPos = 0;
    double yPos = -1;
    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if(state == GLFW_PRESS && action == GLFW_MOUSE_BUTTON_LEFT){
        glfwGetCursorPos(window, &xPos, &yPos);
        chess.ProcessInput(xPos,yPos);
    }
}