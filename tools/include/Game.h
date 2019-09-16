/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
 * Modified by jordan
******************************************************************/

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




    Game(GLuint width, GLuint height);
    ~Game();


    void init();
    void ProcessInput(double xPos, double yPos);
    void Update(GLfloat dt);
    void Render();

    void buildInput(std::string input);
    void endTurn();

private:
    std::string input = "";
    std::string player = "playerTwo";
    ChessController chessGame;


};


#endif //CHESS_GAME_H
