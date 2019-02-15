//
// Created by jordanhoang on 11/02/19.
//

#include <iostream>
#include "../header/Piece.h"
#include "assert.h"


//PRIVATE



/**Validates a pawn's movement, check for attempting to move a NONE piece or onto piece of same colored performed
 * in Board.cpp
 * @param start - starting position
 * @param finish - finish position
 * @param target - the color of the target you are moving to
 * @return true if valid else false
 */
bool Piece::validatePawn(const ChessCoordinate &start, const ChessCoordinate &finish, const Color &target) const {

    //+ means goes up -1 means goes down the chess board
    int directionTravel = (this->pieceColor == RED) ? 1 : -1;

    //Code for checking if your piece can move forward



    //Works if the path is clear
        if (start.row + directionTravel == finish.row) {
            return true; //GENERIC PAWN CODE SHOULD WORK FOR BOTH
        } else if (start.row == 1 && directionTravel == 1 && (start.row + directionTravel * 2) == finish.row) {
            return true; //CODE FOR RED
        } else if (start.row == 6 && directionTravel == -1 && (start.row + directionTravel * 2) == finish.row) {
            return true; //CODE FOR BLUE
        }




    //prevent diagonal movement
    if(target == COLORLESS ){

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

bool Piece::checkMovementIsValid(const ChessCoordinate &start, const ChessCoordinate &finish,const  Color &targetColor) const {


    PieceUnit  piece = pieceId;


    if(piece == KING){


    } else if ( piece == BISHOP ){



    } else if ( piece == ROOK ){



    } else if ( piece == PAWN ){
        return validatePawn(start,finish,targetColor);

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