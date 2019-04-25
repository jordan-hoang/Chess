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


int main(){

    ChessController chessGame;
    bool isPlayerOneTurn = true;
    std::string playerName = "playerOne";


        while(!chessGame.isGameFinished()){
            std::cout << chessGame.getBoardView();
            std::string userInput = takeUserInput();

            bool isValid = chessGame.readInput(userInput,playerName);
            if(isValid){
                if(isPlayerOneTurn){
                    isPlayerOneTurn = false;
                    playerName = "playerTwo";
                } else{
                    isPlayerOneTurn = true;
                    playerName = "playerOne";
                }
            } else {
                std::cout << "Invalid move!\n";
            }

        }

        std::cout << chessGame.gameOverMessage();

}
