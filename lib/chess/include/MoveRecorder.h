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

/// Note polymorphism not actually needed to be used here at all
/// Since the difference between singleChessMove and MultiChessMove is irrelevant
/// I only chose to use polymorphism because I wanted to try using it at least once in C++.

struct ChessMove{
    pair<ChessCoordinate,ChessCoordinate> move;
    Piece pieceKilled;

    virtual void undoMove(vector<vector<Piece>> &board) const {

        const ChessCoordinate &start = move.first;
        const ChessCoordinate &end =  move.second;

        Piece &moveFrom = board[end.row][end.col];
        Piece &moveTo   = board[start.row][start.col];

        Piece::updatePiece(moveFrom,moveTo);
        moveFrom.setPiece(pieceKilled);

    }

};

struct SingleChessMove : public ChessMove {



};


struct MultiChessMove : public ChessMove {
    vector <ChessMove> multipleMoves;

    virtual void undoMove()  {


    }

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
