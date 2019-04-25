//
// Created by jordan on 25/04/19.
//




#include <ChessController.h>
#include <boost/algorithm/string/constants.hpp>
#include <boost/algorithm/string.hpp>

/**
 * Runs the chess program itself. Meant for local play using the same keyboard for both players
 *
 */


bool validateString(std::string &input, std::vector<std::string> &result) {

    if(input.size() >= 10){
        return false;
    }

    boost::trim(input);
    boost::split(result,input,boost::is_any_of(","));

    if(result.size() != 2  || result.at(0).size() != 2 || result.at(1).size() != 2 ){
        //print out error message
        return false;
    }

    return true;
}





/*

int main(){

    ChessController chessGame;


        while(!chessGame.isGameFinished()){
            chessGame.getBoardView();
            
            
            //Read userInput <---
            //chessGame.executeMove();

        }


}
 */