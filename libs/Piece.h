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
    Piece(int rowPosition, int colPosition, char colCharPosition, PieceType typeOfPiece);
    int getRowPosition() const;
    void setRowPosition(int rowPosition);
    int getColPosition() const;
    void setColPosition(int colPosition);
    char getColCharPosition() const;
    void setColCharPosition(char colCharPosition);
    PieceType getTypeOfPiece() const;
    void setTypeOfPiece(PieceType typeOfPiece);


private:

    int rowPosition;
    int colPosition;
    char colCharPosition;
    PieceType typeOfPiece;

};