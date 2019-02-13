//
// Created by jordanhoang on 12/02/19.
//

#include "../header/MoveValidator.h"
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
    return result;
}


void MoveValidator::processChessMove(int startCol, int startRow, int finishCol, int finishRow) {

    //Retrieve the board and check the spots



}






/**
 * @param input - Takes in a chess move. First specify the location of a piece then specify the
 * end spot next. Example move "a2,b6"
 */
void MoveValidator::readChessMove(std::string &input) {


   // boost::trim_if(fullCommand, boost::is_any_of(" \t") );
   // boost::split(splitByColon, fullCommand, boost::is_any_of(":"), boost::token_compress_on);
    boost::trim(input);



    std::vector<std::string> result;
    boost::split(result,input,boost::is_any_of(","));

    if(result.size() != 2  || result.at(0).size() != 2 || result.at(1).size() != 2 ){
        //print out error message
        return;
    }


    int startPositionColumn = convertCharColToInt(result.at(0).at(0));
    int startPositionRow = convertChessRowToInt(result.at(0).at(1));

    int finishPositionColumn = convertCharColToInt(result.at(1).at(0));
    int finishPositionRow = convertChessRowToInt(result.at(1).at(1));


    // std::cout << startPositionColumn << ", " << startPositionRow << " : " <<   //debug
    //     finishPositionColumn << ", " << finishPositionRow << std::endl;
    processChessMove(startPositionColumn,startPositionRow,finishPositionColumn,finishPositionColumn);


}