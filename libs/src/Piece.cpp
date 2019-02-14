//
// Created by jordanhoang on 11/02/19.
//

#include <iostream>
#include "../header/Piece.h"
#include "assert.h"


//PRIVATE



bool Piece::validatePawn(const ChessCoordinate &start, const ChessCoordinate &finish) {

    //+ means goes up -1 means goes down the chess
    int directionTravel = (this->pieceColor == RED) ? 1 : -1;


    if(start.row + directionTravel == finish.row){
        return true; //GENERIC PAWN CODE SHOULD WORK FOR BOTH
    } else if(start.row == 1 && directionTravel == 1 &&  (start.row + directionTravel*2)==finish.row ){
        return true; //CODE FOR RED
    } else if(start.row == 6 && directionTravel == -1 &&  (start.row + directionTravel*2)==finish.row   ){
        return true; //CODE FOR BLUE
    }



    return false;

}


void Piece::updatePiece(Piece &source, Piece &destination) {

    destination.pieceId = source.pieceId;
    destination.pieceColor = source.pieceColor;

    source.pieceId = NONE;
    source.pieceColor = COLORLESS;

}

//PUBLIC

bool Piece::checkMovementIsValid(const ChessCoordinate &start, const ChessCoordinate &finish) {


    PieceUnit  piece = pieceId;


    if(piece == KING){


    } else if ( piece == BISHOP ){



    } else if ( piece == ROOK ){



    } else if ( piece == PAWN ){
        return validatePawn(start,finish);

    } else if ( piece == QUEEN ){


    } else if ( piece ==  KNIGHT) {



    } else if ( piece == NONE ){
        return false;
    } else {

        std::cout << "Somehow you are moving that a piece that doesn't have a class\n";
        static_assert(-1);
        return false;

    }



    return false;
}