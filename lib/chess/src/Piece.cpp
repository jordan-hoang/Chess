//
// Created by jordanhoang on 11/02/19.
//

#include <iostream>
#include "assert.h"
#include "Piece.h"


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


    //prevent diagonal movement when there is no enemy on that spot
    if(target != COLORLESS ){
        int diffX  = abs(finish.row - start.row);
        int diffY  = abs(finish.col - start.col);

        //A pawn can travel at most 1 unit diagonally therefore there xPos,yPos must have changed by 1.
        if(diffX != 1 || diffY != 1){
            return false;
        } else{
            return true;
        }

    }

    return false;
}


/**
 * Check's to see if the Rook can move in this way, Path checked in Board.cpp already
 */
bool Piece::validateRook(const ChessCoordinate &start, const ChessCoordinate &finish) const {

    if( start.row == finish.row && start.col != finish.col ){
        return true;
    }
        // You are moving vertical
    else if( start.row != finish.row && start.col == finish.col ) {
        return true;
    }

    return false;
}

bool Piece::validateKnight(const ChessCoordinate &start, const ChessCoordinate &finish) const {

    //A knight has 8 possible moves from it's current position.
    //If any of those 8 moves matches finish than it is a valid move.
    ChessCoordinate initial = start;

    // All possible moves of a knight
    int X[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    int Y[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };


    for(int i = 0; i < 8 ; i++){
        int row = start.row + Y[i];
        int col = start.col + X[i];
        if( ChessCoordinate{row,col} == finish ){
            return true;
        }
    }
    return false;

}


bool Piece::validateBishop(const ChessCoordinate &start, const ChessCoordinate &finish) const {





}

bool Piece::validateKing(const ChessCoordinate &start, const ChessCoordinate &finish) const {



}

bool Piece::validateQueen(const ChessCoordinate &start, const ChessCoordinate &finish) const {
    return ( validateRook(start,finish) || validateBishop(start,finish) );
}


//Replaces the piece at destination with source, and source set to be empty
void Piece::updatePiece(Piece &source, Piece &destination) {

    destination.pieceId = source.pieceId;
    destination.pieceColor = source.pieceColor;

    source.pieceId = NONE;
    source.pieceColor = COLORLESS;

}


//PUBLIC
bool Piece::checkMovementIsValid(const ChessCoordinate &start, const ChessCoordinate &finish,const  Color &targetColor) const {


    PieceUnit  piece = pieceId;

    switch(piece){
        case PAWN:
            return validatePawn(start,finish,targetColor);
        case ROOK:
            return validateRook(start,finish);
        case KNIGHT:
            return validateKnight(start,finish);
        case BISHOP:
            return validateBishop(start,finish);
        case KING:
            return validateKing(start,finish);
        case QUEEN:
            return validateQueen(start,finish);
        case NONE:
            return false;
        default:
            assert(-1);
    }

    return false;
}