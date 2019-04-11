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
    const std::string getBoardView() const;
    const std::string getReverseBoardView() const;

    Piece& requestPiece(const ChessCoordinate &position);
    const PieceUnit requestUnit(const ChessCoordinate &position) const;


    bool movePiece(const ChessCoordinate &start, const ChessCoordinate &finish);

    const Piece getLastPieceKilled() const;

private:
    vector< vector<Piece> > boardView;
    Piece lastPieceKilled;

   void initializeGame(vector<vector<Piece>> &boardView);
   void createBackRank(Color myColor, vector<vector<Piece>> &boardView) ;
   void drawRow(const vector<Piece> &listPieceId, std::stringstream &stream) const;
   void drawRowReverse(const vector<Piece> &listPieceId, std::stringstream &stream) const;


   bool checkHorizontalPath(const ChessCoordinate &start, const ChessCoordinate &finish) const;
   bool checkVerticalPath(const ChessCoordinate &start, const ChessCoordinate &finish) const;
   bool checkDiagonalPath(const ChessCoordinate &start, const ChessCoordinate &finish) const;
   bool isPathClear(const ChessCoordinate &start, const ChessCoordinate &finish) const;

   void promotePawnToQueen(Piece &source, const ChessCoordinate &target);

   const static std::unordered_map <PieceUnit, char> PieceLookUp;

};


#endif //CHESS_BOARD_H
