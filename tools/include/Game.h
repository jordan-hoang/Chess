//
// Created by jordan on 23/08/19.
//

#ifndef CHESS_GAME_H
#define CHESS_GAME_H


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../../lib/chess/include/ChessController.h"


enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};


class Game {
public:

    GameState State;
    GLuint Width, Height;
    ChessController chessGame;

    std::string input = "";
    std::string player = "playerOne";


    Game(GLuint width, GLuint height);
    ~Game();


    void init();
    void ProcessInput(double xPos, double yPos);
    void Update(GLfloat dt);
    void Render();

    void buildInput(std::string input);
    void endTurn();



};


#endif //CHESS_GAME_H
