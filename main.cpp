#include <iostream>
#include "termcolor.hpp"
#include "libs/Board.h"

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















int main() {
    //    printColorExample();
    testBoard();




    return 0;
}