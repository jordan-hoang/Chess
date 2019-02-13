//
// Created by jordanhoang on 12/02/19.
//

#ifndef CHESS_CHESSCONTROLLER_H
#define CHESS_CHESSCONTROLLER_H


#include <string>
#include "Board.h"

/**
 * Takes user input and sends it to board.
 */
class MoveValidator {
    public:
        bool readChessMove(std::string &input);

    private:
        Board gameBoard;

        int convertCharColToInt(char input);
        int convertChessRowToInt(char input);
        bool processChessMove( int startCol ,int startRow, int finishCol ,int finishRow ) ;
        bool processChessClass(int startCol, int startRow, int finishCol, int finishRow, PieceUnit piece);

};


#endif //CHESS_CHESSCONTROLLER_H
