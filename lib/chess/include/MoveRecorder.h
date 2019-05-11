//
// Created by jordan on 30/04/19.
//

#ifndef CHESS_MOVERECORDER_H
#define CHESS_MOVERECORDER_H


#include <utility>
#include "Piece.h"
#include <vector>
#include <string>
#include <memory>

using std::pair;
using std::vector;


struct ChessMove{
    pair<ChessCoordinate,ChessCoordinate> move;
    Piece pieceKilled;
};



/**
 * A class that records moves, and also checks for move reptition
 */
class MoveRecorder {
    public:
        void addMove(ChessCoordinate, ChessCoordinate, Piece killedPiece);
        void removeLastMove();
        void undoMove(vector<vector<Piece>> &board);

        std::string printMoves();

        bool hasMove() const;
        ChessMove  const * getLastMove() const;

        MoveRecorder();


    private:
        vector< std::unique_ptr<ChessMove> > m_listOfGameMoves;


};


#endif //CHESS_MOVERECORDER_H
