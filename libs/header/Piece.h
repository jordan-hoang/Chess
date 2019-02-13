//
// Created by jordanhoang on 11/02/19.
//


#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#endif //CHESS_PIECE_H

enum Color{ RED,BLUE,COLORLESS };

enum PieceUnit{
    PAWN,
    BISHOP,
    KNIGHT,
    ROOK,
    KING,
    QUEEN,
    NONE
};

struct PieceType
{
    PieceUnit MyId;
    Color mycolor;
};




class Piece{
public:
    PieceType getTypeOfPiece() const;
    void setTypeOfPiece(PieceType typeOfPiece);
private:
    char colCharPosition;
    PieceType typeOfPiece;

};