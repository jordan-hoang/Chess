//
// Created by jordan on 23/08/19.
//

#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"

SpriteRenderer *Renderer;

Game::Game(GLuint width, GLuint height):
   State(GAME_ACTIVE), Width(width), Height(height), chessGame()
{

}

Game::~Game()
{
    delete Renderer;
}

void Game::init()
{
    // Load shaders
    ResourceManager::LoadShader("../../tools/shaders/sprite.vs", "../../tools/shaders/sprite.frag", nullptr, "sprite");

    // Configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);



    // Load textures
    ResourceManager::LoadTexture("../../textures/chess4.png", GL_TRUE, "chess_board");
    ResourceManager::LoadTexture("../../textures/chessPieces.jpeg", GL_TRUE, "chess_pieces");
    ResourceManager::LoadTexture("../../textures/bbishop.png", GL_TRUE, "bbishop");

    // Set render-specific controls

    Shader myShader;
    myShader = ResourceManager::GetShader("sprite");
    Renderer = new SpriteRenderer(myShader);




}

void Game::Update(GLfloat dt)
{

}


void Game::ProcessInput(double xPos, double yPos)
{
    //Manipulate the chessController here.


}

void Game::Render()
{
    Texture2D chess_board, chess_pieces;


    chess_board = ResourceManager::GetTexture("chess_board");
    Renderer->DrawSprite(chess_board, glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0, glm::vec3(1.0f, 1.0f, 1.0f));

    chess_pieces = ResourceManager::GetTexture("chess_pieces");

    //100, 75
    Texture2D bbishop = ResourceManager::GetTexture("bbishop");
    Renderer->DrawSprite(bbishop, glm::vec2(14,0), glm::vec2(bbishop.Width,bbishop.Height), 0, glm::vec3(1.0f, 1.0f, 1.0f));



    //Renderer->DrawScaledImage(whiteKing, glm::vec2(0, 0), glm::vec2(whiteKing.Width, whiteKing.Height), 0, glm::vec3(1.0f, 1.0f, 1.0f));


}
