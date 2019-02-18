//
// Created by jordanhoang on 12/02/19.
//

#include "MoveValidator.h"
#include <boost/algorithm/string.hpp>
#include <iostream>



/**
 * Converts a column to a integer Ex. the move a2 will convert the 'a' into a 0
 *
 */
int MoveValidator::convertCharColToInt(char input){

    input = std::tolower(input);

   // std::cout << "input is " << input << "\n";
    switch(input){
        case 'a':
            return 0;
        case 'b':
            return 1;
        case 'c':
            return 2;
        case 'd':
            return 3;
        case 'e':
            return 4;
        case 'f':
            return 5;
        case 'g':
            return 6;
        case 'h':
            return 7;
    }

    return -1;
}

/**
 * @param input
 * @return The int for the vector to handle.
 */
int MoveValidator::convertChessRowToInt(char input){
    int result = input - '0';
    if(result < 0 || result > 8){
        return -1;
    }
    return result - 1;
}


void MoveValidator::drawBoard() {
    gameBoard.drawBoard();
}


/**
 * Checks to see if the input is valid.
 * @param startPos - The position you are starting from
 * @param finishPos - The position you expect to finish at.
 */
bool MoveValidator::processChessMove(const ChessCoordinate &startPos, const ChessCoordinate &finishPos) {

    if(startPos.col <= -1 || startPos.row <= -1 || finishPos.col <= -1 || finishPos.row <= -1){
        std::cout << "Invalid output\n";
        return false;
    }

       return  gameBoard.movePiece(startPos, finishPos);

}



/**
 * @param input - Takes in a chess move. First specify the location of a piece then specify the
 * end spot next. Example move "a2,b6"
 */
bool MoveValidator::readChessMove(std::string &input) {

    boost::trim(input);

    std::vector<std::string> result;
    boost::split(result,input,boost::is_any_of(","));

    if(result.size() != 2  || result.at(0).size() != 2 || result.at(1).size() != 2 ){
        //print out error message
        std::cout << "Invalid move! \n";
        return false;
    }


    int sCol =  convertCharColToInt(result.at(0).at(0));
    int sRow = convertChessRowToInt(result.at(0).at(1));
    ChessCoordinate startPos{sRow,sCol};

    int finishPositionColumn = convertCharColToInt(result.at(1).at(0));
    int finishPositionRow = convertChessRowToInt(result.at(1).at(1));
    ChessCoordinate finishPos{ finishPositionRow,finishPositionColumn };

    return processChessMove( startPos, finishPos );

}


