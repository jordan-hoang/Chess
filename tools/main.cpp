#include <iostream>
#include <assert.h>
#include "../termcolor.hpp"
#include "../chess/header/MoveValidator.h"
#include "../chess/header/Board.h"


using std::cout;
using std::endl;


void printColorExample(){

    std::cout << termcolor::red << "Printing red" << std::endl;
    std::cout << termcolor::reset;


}

void testBoard(){
    Board b;
    b.drawBoard();
}



void testMoveValidator(){

    MoveValidator move;

    std::string input = "ab,52";
    /*
    move.readInput(input);

    input = "0a,bs";
    move.readInput(input);


    input = "aabcds";
    move.readInput(input);


    input = "aacd";
    move.readInput(input);


    input = "frw,a0";
    move.readChessMove(input);
    */

    input = "a0,4f";
    move.readChessMove(input);


    //Valid
    input = "a0,a3";
    move.readChessMove(input);

    input = "b2,b4";
    move.readChessMove(input);


    input = "b5,b7";
    move.readChessMove(input);


}






void testPawn(){

    MoveValidator move;
    move.drawBoard();

    std::string input = "a2,a3";

    bool isValid = move.readChessMove(input) ;

    if(isValid == false){
        std::cout << "Invalid move " << "\n";
    }


    move.drawBoard();


}






int main() {
    //    printColorExample();
    //    testBoard();
    //testMoveValidator();
        testPawn();





    return 0;
}