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
    ResourceManager::LoadTexture("../../textures/ChessBoard.png", GL_TRUE, "chess_board");

    ResourceManager::LoadTexture("../../textures/B_BISHOP.png", GL_TRUE, "bbishop");
    ResourceManager::LoadTexture("../../textures/B_KING.png", GL_TRUE, "bking");
    ResourceManager::LoadTexture("../../textures/B_KNIGHT.png", GL_TRUE, "bknight");
    ResourceManager::LoadTexture("../../textures/B_PAWN.png", GL_TRUE, "bpawn");
    ResourceManager::LoadTexture("../../textures/B_QUEEN.png", GL_TRUE, "bqueen");
    ResourceManager::LoadTexture("../../textures/B_ROOK.png", GL_TRUE, "brook");

    //Time to load white pieces.
    ResourceManager::LoadTexture("../../textures/W_BISHOP.png", GL_TRUE, "wbishop");
    ResourceManager::LoadTexture("../../textures/W_KING.png", GL_TRUE, "wking");
    ResourceManager::LoadTexture("../../textures/W_KNIGHT.png", GL_TRUE, "wknight");
    ResourceManager::LoadTexture("../../textures/W_PAWN.png", GL_TRUE, "wpawn");
    ResourceManager::LoadTexture("../../textures/W_QUEEN.png", GL_TRUE, "wqueen");
    ResourceManager::LoadTexture("../../textures/W_ROOK.png", GL_TRUE, "wrook");

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
    //800,600
    std::string input_string = "";

    if(xPos < 100) {
        input_string += 'a';
    }else if(xPos < 200 && xPos > 100){
        input_string += 'b';
    }else if(xPos < 300 && xPos > 200){
        input_string += 'c';
    }else if(xPos < 400 && xPos > 300){
        input_string += 'd';
    }else if(xPos < 500 && xPos > 400){
        input_string += 'e';
    }else if(xPos < 600 && xPos > 500){
        input_string += 'f';
    }else if(xPos < 700 && xPos > 600){
        input_string += 'g';
    }else if(xPos < 800 && xPos > 700){
        input_string += 'h';
    }

    int lower_bound = 0;
    int upper_bound = 75;
    for(int i = 0; i < 8; i++){
        char tmp = '1';
        if(yPos > lower_bound && yPos < upper_bound) {
            input_string+=tmp;
            break;
        }
        tmp++;
        lower_bound+=75;
        upper_bound+=75;
    }

    buildInput(input_string);


}

void Game::buildInput(std::string in) {
    if(this->input.size() == 0){
        this->input += in + ',';
    }


    if(this->input.size() == 5){
        this->chessGame.readInput(input, "playerOne");

    }



}

void Game::endTurn() {


}



void Game::Render()
{
    Texture2D chess_board, chess_pieces;


    chess_board = ResourceManager::GetTexture("chess_board");
    Renderer->DrawSprite(chess_board, glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0, glm::vec3(1.0f, 1.0f, 1.0f));


    //100, 75
    //Texture2D bbishop = ResourceManager::GetTexture("bbishop");
    //Renderer->DrawSprite(bbishop, glm::vec2(0,0), glm::vec2(bbishop.Width,bbishop.Height), 0, glm::vec3(1.0f, 1.0f, 1.0f));

    const auto &ref = this->chessGame.getChessBoard();


    int posX = 0;
    int posY = 0;
    for(int i = 0; i < 8 ;i++){
        for(int j = 0; j < 8; j++) {
            const auto &name =ref[i][j].getName();
            if(name != ""){
                Texture2D texture = ResourceManager::GetTexture(name);
                Renderer->DrawSprite(texture, glm::vec2(posX,posY), glm::vec2(ResourceManager::GetTexture(name).Width,
                        ResourceManager::GetTexture(name).Height),   0, glm::vec3(1.0f,1.0f,1.0f));
            }
            posX = posX + 100;
        }
        posX = 0;
        posY += 75;
    }



}
