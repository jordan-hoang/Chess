//
// Created by jordanhoang on 11/02/19.
//

#include "Piece.h"


//Getters and setters
int Piece::getRowPosition() const {
    return rowPosition;
}
void Piece::setRowPosition(int rowPosition) {
    Piece::rowPosition = rowPosition;
}
int Piece::getColPosition() const {
    return colPosition;
}
void Piece::setColPosition(int colPosition) {
    Piece::colPosition = colPosition;
}
char Piece::getColCharPosition() const {
    return colCharPosition;
}
void Piece::setColCharPosition(char colCharPosition) {
    Piece::colCharPosition = colCharPosition;
}



void Piece::setTypeOfPiece(PieceType typeOfPiece) {
    Piece::typeOfPiece = typeOfPiece;
}

//Constructors
//Piece::Piece(int rowPosition, int colPosition, char colCharPosition, PieceType typeOfPiece) : rowPosition(
  //      rowPosition), colPosition(colPosition), colCharPosition(colCharPosition), typeOfPiece(typeOfPiece) {}
