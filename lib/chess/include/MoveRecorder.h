//
// Created by jordan on 30/04/19.
//

#ifndef CHESS_MOVERECORDER_H
#define CHESS_MOVERECORDER_H


#include <utility>
#include "Piece.h"
#include <vector>
#include <string>

using std::pair;
using std::vector;


/**
 * A class that records moves, and also checks for move reptition
 */
class MoveRecorder {
    public:
        void addMove(ChessCoordinate, ChessCoordinate);
        void removeLastMove();

        std::string printMoves();






    private:
        vector<pair<ChessCoordinate, ChessCoordinate> > listOfGameMoves;


};


#endif //CHESS_MOVERECORDER_H
