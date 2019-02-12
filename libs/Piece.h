//
// Created by jordanhoang on 11/02/19.
//

#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#endif //CHESS_PIECE_H
enum PieceId{
    PAWN,
    BISHOP,
    KNIGHT,
    ROOK,
    KING,
    QUEEN,
    WHITE_PAWN,
    WHITE_BISHOP,
    WHITE_KNIGHT,
    WHITE_ROOK,
    WHITE_KING,
    WHITE_QUEEN,
    NONE
};


class Piece{
public:
    Piece(int rowPosition, int colPosition, char colCharPosition, PieceId typeOfPiece);
    int getRowPosition() const;
    void setRowPosition(int rowPosition);
    int getColPosition() const;
    void setColPosition(int colPosition);
    char getColCharPosition() const;
    void setColCharPosition(char colCharPosition);
    PieceId getTypeOfPiece() const;
    void setTypeOfPiece(PieceId typeOfPiece);


private:

    int rowPosition;
    int colPosition;
    char colCharPosition;
    PieceId typeOfPiece;

};