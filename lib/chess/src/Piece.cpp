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
ChessErrorCode Piece::validatePawn(const ChessCoordinate &start, const ChessCoordinate &finish, const Color &target) const {

    //+ means goes up -1 means goes down the chess board
    int directionTravel = (this->pieceColor == Color::RED_LOWERCASE) ? 1 : -1;

    int difY = finish.row - start.row;
    int difX = finish.col - start.col;

    //Works if the path is clear
    if(target == Color::COLORLESS) {

        if (start.row + directionTravel == finish.row && ( difX == 0 || difY == 0 ) ) {
            return ChessErrorCode::VALID_MOVE; //GENERIC PAWN CODE SHOULD WORK FOR BOTH


        } else if (start.row == 1 && directionTravel == 1 && (start.row + directionTravel * 2) == finish.row) {
            return ChessErrorCode::VALID_MOVE; //CODE FOR RED
        } else if (start.row == 6 && directionTravel == -1 && (start.row + directionTravel * 2) == finish.row) {
            return ChessErrorCode::VALID_MOVE; //CODE FOR BLUE
        } else{
            return ChessErrorCode::INVALID_MOVE;
        }

    }
    else{
        // Handling diagonal movement, should be invalid if travelling backwards though
        int diffX  = abs(finish.row - start.row);
        int diffY  = abs(finish.col - start.col);

        int rst = diffX * diffY;

        //A pawn can travel at most 1 unit diagonally therefore there xPos,yPos must have changed by 1.
        if(diffX == 1 && diffY == 1){
            if(start.row + directionTravel == finish.row ) {
                return ChessErrorCode::VALID_MOVE;
            }
        }
        return ChessErrorCode::INVALID_MOVE;
    }


}

/**
 * Check's to see if the Rook can move in this way, Path checked in Board.cpp already, is here for consistency???
 */
ChessErrorCode Piece::validateRook(const ChessCoordinate &start, const ChessCoordinate &finish) const {
    return ChessErrorCode::VALID_MOVE;
}

ChessErrorCode Piece::validateKnight(const ChessCoordinate &start, const ChessCoordinate &finish) const {

    //A knight has 8 possible moves from it's current position.
    //If any of those 8 moves matches finish than it is a valid move.
    int moveX[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    int moveY[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };


    for(int i = 0; i < 8 ; i++){
        int row = start.row + moveY[i];
        int col = start.col + moveX[i];
        if( ChessCoordinate{row,col} == finish ){
            return ChessErrorCode::VALID_MOVE;
        }
    }
    return ChessErrorCode::INVALID_MOVE;

}

ChessErrorCode Piece::validateBishop(const ChessCoordinate &start, const ChessCoordinate &finish) const {
    return ChessErrorCode::VALID_MOVE; //This method doesn't really need to exist validateDiagonal in Board determines if move is allowed
}

ChessErrorCode Piece::validateKing(const ChessCoordinate &start, const ChessCoordinate &finish) const {

    int moveX[8] = { 0, 0, 1 , 1 , 1 , -1 , -1 ,-1 };
    int moveY[8] = { 1, -1, 0, 1 , -1,  1,  0 ,-1  };

    //There are 8 possible moves you can do
    for(int i = 0; i < 8; i++){
        int row = start.row + moveY[i];
        int col = start.col + moveX[i];
        if(ChessCoordinate{row,col} == finish){
            return ChessErrorCode::VALID_MOVE;
        }
    }


    //Implement castling here
    if(!hasMoved){
        if( ( (start.col - 2 == finish.col) || (start.col + 2 == finish.col) ) && (finish.row == start.row) ){
            return ChessErrorCode::CASTLE;
        }
    }




    return ChessErrorCode::INVALID_MOVE;

}

ChessErrorCode Piece::validateQueen(const ChessCoordinate &start, const ChessCoordinate &finish) const {

    if( (validateRook(start,finish) == ChessErrorCode::VALID_MOVE) || validateBishop(start,finish) == ChessErrorCode::VALID_MOVE ){
        return ChessErrorCode::VALID_MOVE;
    }
    return ChessErrorCode::VALID_MOVE;
}

// All the validate methods above do the same thing
// they validate to see if the move is possible then send a code when it happens
// All of them are helper methods of checkMovementIsValid

void Piece::setPiece(PieceUnit pieceUnit, Color color) {
    this->pieceId = pieceUnit;
    this->pieceColor = color;
}


//Replaces the piece at destination with source, and source set to be empty
//Note that you can just actually use std::swap..... instead of having this function.
//This function shouldn't need a piece to be executed
void Piece::updatePiece(Piece &source, Piece &destination) {

    destination.pieceId = source.pieceId;
    destination.pieceColor = source.pieceColor;
    destination.hasMoved = true;

    source.pieceId = PieceUnit::NONE;
    source.pieceColor = Color::COLORLESS;
    source.hasMoved = false; //Empty squares "can't move"

}

/***
 * Check's to see if that piece can move in that way.
 * @param start - startCoordinate of the piece you want to move.
 * @param finish  - EndCoordinate of where the piece should end up
 * @param targetColor - Color of the endCoordinate.
 * @return
 */
ChessErrorCode Piece::checkMovementIsValid(const ChessCoordinate &start, const ChessCoordinate &finish,const  Color &targetColor) const {

    PieceUnit piece = pieceId;

    switch(piece){
        case PieceUnit::PAWN:
            return validatePawn(start,finish,targetColor);
        case PieceUnit::ROOK:
            return validateRook(start,finish);
        case PieceUnit::KNIGHT:
            return validateKnight(start,finish);
        case PieceUnit::BISHOP:
            return validateBishop(start,finish); //this code is unneccessary fix in future
        case PieceUnit::KING:
            return validateKing(start,finish);
        case PieceUnit::QUEEN:
            return validateQueen(start,finish);
        case PieceUnit::NONE:
            return ChessErrorCode::INVALID_PIECE;
        default:
            assert(false && "Somehow there is an invalid piece");
    }

}


Piece::Piece() {
    this->pieceColor = Color::COLORLESS;
    this->pieceId = PieceUnit::NONE;
    this->hasMoved = false;
}
