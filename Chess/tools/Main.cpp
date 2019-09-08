//
// Created by jordan on 25/04/19.
//




#include <ChessController.h>
#include <boost/algorithm/string/constants.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>


std::string takeUserInput(){

    std::string rst;
    std::cin >> rst;
    return std::move(rst);
}

std::string invalidMessage(ChessErrorCode code){
    std::string rst = "tingy";
    switch(code){
        case ChessErrorCode::VALID_MOVE:
            rst = "Whoa this message shouldn't appear since the move was valid!\n";
        case ChessErrorCode::INVALID_INPUT:
            rst = "Bad input!, please enter input in this format: a7,a5\n";
            break;
        case ChessErrorCode::INVALID_MOVE:
            rst = "Invalid move, your selected piece can't move that way!\n";
            break;
        case ChessErrorCode::INVALID_PIECE:
            rst = "You attempted to move a piece that doesn't belong to you!\n";
            break;
        default:
            assert(false && "Somehow this function recieved an ErrorCode that isn't supposed to exist\n");
    }
    return rst;

}


int main(){

    ChessController chessGame;
    bool isPlayerOneTurn = true;
    std::string playerName = "playerOne";


        while(!chessGame.isGameFinished()){
            std::cout << chessGame.getBoardView();
            std::string userInput = takeUserInput();

            ChessErrorCode gameMessage = chessGame.readInput(userInput,playerName);
            if(gameMessage == ChessErrorCode::VALID_MOVE){
                if(isPlayerOneTurn){
                    isPlayerOneTurn = false;
                    playerName = "playerTwo";
                } else{
                    isPlayerOneTurn = true;
                    playerName = "playerOne";
                }
            } else if(gameMessage == ChessErrorCode::CHECK_MATED){
                break;
            } else {
              std::cout << invalidMessage(gameMessage);
            }

        }

        std::cout << chessGame.gameOverMessage();


}
