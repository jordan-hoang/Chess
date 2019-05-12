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
#include <iostream>
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

    ChessMove() = default;

    ChessMove(const ChessMove &move){
        this->move = move.move;
        this->pieceKilled = pieceKilled;
    }
    ChessMove(const ChessCoordinate &start, const ChessCoordinate &finish){
        move.first = start;
        move.second = finish;
        pieceKilled = Piece{PieceUnit::NONE, Color::COLORLESS};
    }

    virtual ~ChessMove() = default;

};

struct ChessCastle : public ChessMove {

    ChessMove rookMoved;

    void undoMove(vector<vector<Piece>> &board) const override {


        const ChessCoordinate &start = move.first;
        const ChessCoordinate &end =  move.second;

        Piece &moveFromKing = board[end.row][end.col];
        Piece &moveToKing   = board[start.row][start.col];
        Piece::updatePiece(moveFromKing,moveToKing);
        moveToKing.setHasMoved(false);


        //Repeat for rook
        const ChessCoordinate &startRook = rookMoved.move.first;
        const ChessCoordinate &endRook =  rookMoved.move.second;
        Piece::updatePiece( board[endRook.row][endRook.col], board[startRook.row][startRook.col] );
        board[startRook.row][startRook.col].setHasMoved(false);


        //std::cout << "For debugging the coordinates of rook and king are \n";
        //std::cout << "King  : " << start << ", " << end << "\n";
        //std::cout << "Rook : " << startRook << ", " <<  endRook << "\n";

    }




    ChessCastle(const ChessMove &rook, const ChessMove &king){
        rookMoved = rook;
        move.first = king.move.first;

        pieceKilled = Piece{PieceUnit::NONE,Color::COLORLESS};
        move.second = king.move.second;


    }
    ~ChessCastle() override = default;

private:
    ChessCastle() = default;


};



/**
 * A class that records moves, and also checks for move reptition
 */
class MoveRecorder {
    public:
        void addMove(ChessCoordinate, ChessCoordinate, Piece killedPiece);
        void addMove( std::unique_ptr<ChessCastle> chessMove );
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
