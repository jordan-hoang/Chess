//
// Created by jordanhoang on 11/02/19.
//

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <vector>
#include <array>
#include "Piece.h"
#include <unordered_map>

using std::vector;

//Contains an instance of a game
class Board {
public:
    Board();
    void drawBoard() const;


private:
    std::vector<Piece> blackPieces;
    std::vector<Piece> whitePieces;
    vector< vector<PieceType> > boardView;

   void initializeGame(vector<vector<PieceType>> &boardView);
   void createBackRank(Color myColor, vector<vector<PieceType>> &boardView) ;
   void drawRow(vector<PieceType> &listPieceId) const;

   const static std::unordered_map <PieceUnit, char> PieceLookUp;

};


#endif //CHESS_BOARD_H
