#include <iostream>
#include "termcolor.hpp"
#include "libs/header/Board.h"
#include "libs/header/MoveValidator.h"

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
    input = "a0,a0";
    move.readChessMove(input);

    input = "b2,b4";
    move.readChessMove(input);


    input = "b5,b7";
    move.readChessMove(input);



}




int main() {
    //    printColorExample();
    testBoard();
    testMoveValidator();






    return 0;
}