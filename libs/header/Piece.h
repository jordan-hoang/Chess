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

class PieceType {
    private:
        PieceUnit MyId;
        Color mycolor;


    public:
        PieceUnit getPieceUnit() { return MyId; };
        Color getColor(){ return mycolor; };

        //Color getColor(return mycolor);

        PieceType(PieceUnit unit, Color color) :
            MyId(unit), mycolor(color){}

};








class Piece{
public:
    PieceType getTypeOfPiece() const;
    void setTypeOfPiece(PieceType typeOfPiece);
private:
    char colCharPosition;
    PieceType typeOfPiece;

};