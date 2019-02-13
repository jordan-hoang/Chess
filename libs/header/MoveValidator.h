//
// Created by jordanhoang on 12/02/19.
//

#ifndef CHESS_CHESSCONTROLLER_H
#define CHESS_CHESSCONTROLLER_H


#include <string>

/**
 * Takes user input and sends it to board.
 */
class MoveValidator {
    public:
        void readChessMove(std::string &input);



    private:
        int convertCharColToInt(char input);
        int convertChessRowToInt(char input);
        void processChessMove( int startCol ,int startRow, int finishCol ,int finishRow ) ;




};


#endif //CHESS_CHESSCONTROLLER_H
