//
// Created by jordanhoang on 11/02/19.
//

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <vector>
#include <array>
#include "Piece.h"
#include <unordered_map>
#include <sstream>






using std::vector;

//Contains an instance of a game
class Board {
public:
    Board();

    Board(vector<vector<Piece>> &chessBoard); // Pass in your own chessBoard, used for testing.
    const std::string getBoardView() const;
    const std::string getReverseBoardView() const;

    Piece& requestPiece(const ChessCoordinate &position);
    const Piece &getPiece(const ChessCoordinate &position) const;
    const PieceUnit requestUnit(const ChessCoordinate &position) const;
    const Color getPieceColor(const ChessCoordinate &position) const;


    ChessErrorCode movePiece(const ChessCoordinate &start, const ChessCoordinate &finish);

    const Piece getLastPieceKilled() const;

private:
    vector< vector<Piece> > chessBoard;
    Piece lastPieceKilled;

   void initializeGame(vector<vector<Piece>> &chessBoard);
   void createBackRank(Color myColor, vector<vector<Piece>> &boardView) ;
   void drawRow(const vector<Piece> &listPieceId, std::stringstream &stream) const;
   void drawRowReverse(const vector<Piece> &listPieceId, std::stringstream &stream) const;


   bool isHorizontalPathClear(const ChessCoordinate &start, const ChessCoordinate &finish) const;
   bool isVerticalPathClear(const ChessCoordinate &start, const ChessCoordinate &finish) const;
   bool isDiagonalPathClear(const ChessCoordinate &start, const ChessCoordinate &finish) const;
   bool isPathClear(const ChessCoordinate &start, const ChessCoordinate &finish) const;

   bool isAttackedHorizontally(const ChessCoordinate &start, const Color &kingColor) const;
   bool isAttackedVertically(const ChessCoordinate &start, const Color &kingColor) const;
   bool isAttackedDiagonally(const ChessCoordinate &start, const Color &kingColor) const;
   bool isSquareUnderAttack(const ChessCoordinate &position, const Color enemyColor) const;



   void promotePawnToQueen(Piece &source, const ChessCoordinate &target);
   ChessErrorCode executeCastle(const ChessCoordinate &start, const ChessCoordinate &finish);

   const static std::unordered_map <PieceUnit, char> PieceLookUp;

};


#endif //CHESS_BOARD_H
