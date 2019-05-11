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
/// You can instead have a vector that stores  a vector of moves and do away with this structure
/// -Having a vector of vectors is also more flexible and better but lets just use polymorphism for castling

struct ChessMove {
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

    virtual ~ChessMove() = default;

};

struct ChessCastle : public ChessMove {

    ChessMove rookMoved;

    void undoMove(vector<vector<Piece>> &board) const override {

        const ChessCoordinate &start = move.first;
        const ChessCoordinate &end =  move.second;

        Piece &moveFrom = board[end.row][end.col];
        Piece &moveTo   = board[start.row][start.col];

        Piece::updatePiece(moveFrom,moveTo);
        moveFrom.setPiece(pieceKilled);


        //Repeat for rook

        const ChessCoordinate &startRook = rookMoved.move.first;
        const ChessCoordinate &endRook =  rookMoved.move.second;

        moveFrom = board[endRook.row][endRook.col];
        moveTo   = board[startRook.row][startRook.col];
        Piece::updatePiece(moveFrom,moveTo);
        moveFrom.setPiece(pieceKilled);


    }

    ~ChessCastle() override = default;


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
