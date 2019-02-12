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
    vector< vector<PieceId> > boardView;

   void initializeGame(vector<vector<PieceId>> &boardView);
   void createBackRank(bool IS_BLACK, vector<vector<PieceId>> &boardView) ;
   void drawRow(vector<PieceId> &listPieceId) const;

   const static std::unordered_map <PieceId, char> PieceLookUp;

};


#endif //CHESS_BOARD_H
