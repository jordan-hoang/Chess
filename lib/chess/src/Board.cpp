//
// Created by jordanhoang on 11/02/19.
//

#include "Board.h"
#include <vector>
#include <iostream>
#include <assert.h>
#include <algorithm>


//getters and setters
const Piece Board::getLastPieceKilled() const {
    return lastPieceKilled;
}

/**
 * Helper method for initializeGame
 * @param color - Chess piece color
 * @param boardView - The board itself. Called chessBoard.
 */
void Board::createBackRank(Color color, vector<vector<Piece>> &boardView) {

    vector<Piece> tmp;
    tmp.reserve(8);

        tmp.emplace_back(Piece{PieceUnit::ROOK,color});
        tmp.emplace_back(Piece{PieceUnit::KNIGHT,color});
        tmp.emplace_back(Piece{PieceUnit::BISHOP,color});


        tmp.emplace_back(Piece{PieceUnit::QUEEN,color});
        tmp.emplace_back(Piece{PieceUnit::KING,color});


        tmp.emplace_back(Piece{PieceUnit::BISHOP,color});
        tmp.emplace_back(Piece{PieceUnit::KNIGHT,color});
        tmp.emplace_back(Piece{PieceUnit::ROOK,color});


        boardView.push_back(tmp);
}

/**
 * Initializes the chess game by setting all the pieces.
 * @param chessBoard
 */
void Board::initializeGame(vector<vector<Piece>> &chessBoard) {


    //Doing red side
    createBackRank(Color::RED_LOWERCASE,chessBoard);

    std::vector<Piece> blackPawn;
    blackPawn.assign(8, Piece{PieceUnit::PAWN, Color::RED_LOWERCASE});
    chessBoard.push_back(blackPawn);


    for (int i = 2; i < 6; i++){
        std::vector<Piece> tmp;
        tmp.assign(8,Piece{PieceUnit::NONE, Color::COLORLESS});
        chessBoard.push_back(tmp);
    }

    //Doing blue side
    std::vector<Piece> whitePawn;
    whitePawn.assign(8,Piece{PieceUnit::PAWN, Color::BLUE_UPPERCASE});
    chessBoard.push_back(whitePawn);

    createBackRank(Color::BLUE_UPPERCASE,chessBoard);


}

/**
 * Draw's a row of chess pieces to a stringstream.
 */
void Board::drawRow(const vector<Piece> &listPieceId, std::stringstream &stream) const {
    for(Piece iter: listPieceId){
        auto search = PieceLookUp.find( iter.getPieceUnit() );

        //Since printing out color doesn't work, we will make 1 side lower case
        switch(iter.getColor())
        {
            case Color::RED_LOWERCASE:
                stream  << (char)tolower(search->second);
                break;
            case Color::BLUE_UPPERCASE:
                stream << search->second;
                break;
            default:
                stream << search->second ;
        }

    }
    stream << '\n';
}

/**
 * Draw's a row backward. Helper method for getReverseBoardView().
 * @param listPieceId - A row of chess pieces.
 * @param stream
 */
void Board::drawRowReverse(const vector<Piece> &listPieceId, std::stringstream &stream) const {

    for(int i = 7; i >= 0 ; i--){
        auto iter = listPieceId.at(i);
        auto search = PieceLookUp.find(iter.getPieceUnit());
        //Since printing out color doesn't work, we will make 1 side lower case
        switch(iter.getColor())
        {
            case Color::RED_LOWERCASE:
                stream  << (char)tolower(search->second);
                break;
            case Color::BLUE_UPPERCASE:
                stream << search->second;
                break;
            default:
                stream << search->second ;
        }
    }
    stream << '\n';

}

/**
 * @param start
 * @param finish
 * @return True if the path is clear (no units were found).
 *
 */
bool Board::isHorizontalPathClear(const ChessCoordinate &start, const ChessCoordinate &finish) const {


    const vector<Piece> &handle = chessBoard.at(start.row);
    const auto iterBegin = handle.begin() + std::min(start.col,finish.col ) + 1 ;
    const auto iterEnd = handle.begin() + std::max(start.col,finish.col) ;

    //We are only searching w/e the path specifies
    const auto result = std::find_if(iterBegin,iterEnd,
            [&](auto i) { return i.getPieceUnit() != PieceUnit ::NONE ;} );


    //If enum NONE was not found result will be set to iterEnd.
    return (result == iterEnd);
}

/**
 * NEEDS TESTING
 * @param start - coordinates of the square you want to check is under attack
 * @param finish - end/begin of the row
 * @return True if can be attacked else returns false.
 */
bool Board::isAttackedHorizontally(const ChessCoordinate &start, const ChessCoordinate &finish, const Color &kingColor) const {

    const vector<Piece> &handle = chessBoard.at(start.row);
    const auto iterBegin = handle.begin() + std::min(start.col,finish.col ) + 1 ;
    const auto iterEnd = handle.begin() + std::max(start.col,finish.col) ;


    //If the piece you are looking for is not None and the piece isn't the attack piece then......
    //Stops looking if it finds a piece that isn't none
    const auto result = std::find_if(iterBegin,iterEnd,
                                     [&](auto i) { return i.getPieceUnit() != PieceUnit::NONE ;} );

    //Now we check for the piece that we are supposed to be looking for
    if( result == iterEnd){
        return false;
    }

    PieceUnit foundPiece = (*result).getPieceUnit();
    //They belong on the same team so impossible for them to attack each other.
    if( (*result).getColor() == kingColor){
        return false;
    }

    return ( foundPiece == PieceUnit::ROOK || foundPiece == PieceUnit::QUEEN ) ;

}

/**
 *
 * @param start - The square you want to check
 * @param kingColor - Color of the king that is trying to castle.
 * @return - If that square can be attacked
 */
bool Board::isAttackedVertically(const ChessCoordinate &start, const Color &kingColor) const {

    //We need to check vertically upwards, then vertically downwards, from the position START
    for(int i = start.row ; i < 8 ; i++) {
        Piece tmp = chessBoard.at(i).at(start.col);
        if(tmp.getPieceUnit() == PieceUnit::ROOK || tmp.getPieceUnit() == PieceUnit::QUEEN){
            if(tmp.getColor() != kingColor){
                return true;
            }
        } if(tmp.getPieceUnit() != PieceUnit::NONE){  //but we need to stop checking if the piece we encounter is not
            break;
        }
    }

    //Now we check downwards, almost duplicated code, only for parameters changed
    for(int i = start.row ; i >= 0; i--) {
        Piece tmp = chessBoard.at(i).at(start.col);
        if(tmp.getPieceUnit() == PieceUnit::ROOK || tmp.getPieceUnit() == PieceUnit::QUEEN){
            if(tmp.getColor() != kingColor && tmp.getColor() != Color::COLORLESS){
                return true;
            }
        } if(tmp.getPieceUnit() != PieceUnit::NONE){  //but we need to stop checking if the piece we encounter is not
          break;
        }
    }

    return false;

}


bool Board::isAttackedDiagonally(const ChessCoordinate &start, const Color &kingColor) const {

    //Need code for bishops and pawns,pawns are special case.
    //RED PAWNS Travel upwards, BLUE PAWNS Travel downwards from Piece.cpp

    if(kingColor == Color::BLUE_UPPERCASE){

        //bottom left of start and bottom right of start if contain pawn will mean that spot is dangerous
        ChessCoordinate bottomLeft{start.row - 1, start.col - 1};
        if(bottomLeft.isValid()){
            Piece tmp = getPiece(bottomLeft);

            if(tmp.getColor() == Color::RED_LOWERCASE && tmp.getPieceUnit() == PieceUnit::PAWN){
                return true;
            }
        }

        ChessCoordinate bottomRight{start.row - 1, start.col + 1};
        if(bottomRight.isValid()) {
            Piece tmp = getPiece(bottomRight);
            if (tmp.getColor() == Color::RED_LOWERCASE && tmp.getPieceUnit() == PieceUnit::PAWN) {
                return true;
            }
        }

    } else if(kingColor == Color::RED_LOWERCASE){

        //watch out for pawns coming from above!
        ChessCoordinate topLeft{start.row + 1, start.col - 1};
        if(topLeft.isValid()){
            Piece tmp = getPiece(topLeft);
            if(tmp.getColor() == Color::BLUE_UPPERCASE && tmp.getPieceUnit() == PieceUnit::PAWN){
                return true;
            }
        }
        ChessCoordinate topRight{start.row + 1, start.col + 1};
        if(topRight.isValid()){
            Piece tmp = getPiece(topRight);
            if(tmp.getPieceUnit() == PieceUnit::PAWN && tmp.getColor() == Color::BLUE_UPPERCASE){
                return true;
            }
        }

    }

    //Check + slope for bishops and queens that can kill you.
    //Check - slope for bishops and queens that can kill you.
    //All possible directions diagonally to check in.
    int dirX[4] = {1,-1,1,-1};
    int dirY[4] = {1,-1,-1,1};


    for(int i = 0 ; i < 4; i++){
        ChessCoordinate startingPosition{start.row,start.col};
        bool isValid = true;

        while( isValid && startingPosition.isValid()){
            if(getPieceColor(startingPosition) != kingColor) {
                if ((requestUnit(startingPosition) == PieceUnit::QUEEN) ||
                    requestUnit(startingPosition) == PieceUnit::BISHOP) {
                    return true;
                }
            } if(getPiece(startingPosition).getPieceUnit() != PieceUnit::NONE){
                isValid = false;
            }
            startingPosition.row += dirX[i];
            startingPosition.col += dirY[i];
        }

    }


    return false;
}



/**
 * Determines w/e the path is free vertically
 * @param start
 * @param finish
 */
bool Board::isVerticalPathClear(const ChessCoordinate &start, const ChessCoordinate &finish) const {

    int begin = std::min(start.row,finish.row);
    int end = std::max(start.row,finish.row);

    // + 1 for the space in front of it
    for(int i = begin + 1; i < end ; i++){
        if(requestUnit({i,start.col}) != PieceUnit::NONE ){
            return false;
        }
    }
    return true;

}

//2 slopes + or - and 2 ways to traverse them so 4 ways in total....
bool Board::isDiagonalPathClear(const ChessCoordinate &start, const ChessCoordinate &finish) const{

    // A bishop's diagonal can be defined by y = x or y = -x
    int endIter = abs(finish.col - start.col);

    int curX = start.col;
    int curY = start.row;

    int changeX = ( (finish.col - start.col) > 0 ) ? 1 : -1;
    int changeY = ( (finish.row - start.row) > 0 ) ? 1 : -1;

    for(int i = 0; i < endIter - 1; i++){
        curX += changeX;
        curY += changeY;
        if(requestUnit({curY,curX}) != PieceUnit::NONE   ){
            return false;
        }
    }

    return true;
}

/**
 * A method that checks to see w/e the distance between 2 path's is clear.
 * You can only do vertical, horizontal, or diagonal only lines.
 *
 * Ex. (2,4) to (3,4) // (3,5) to (3,7) // or (3,3) to (5,5)
 *
 * @param start - Starting coordinate
 * @param finish - Finishing coordinate
 * @return
 */
bool Board::isPathClear(const ChessCoordinate &start, const ChessCoordinate &finish) const {

    int diffRow = abs( finish.row - start.row);
    int diffCol = abs( finish.col - start.col);

    // You are moving horizontally
    if( start.row == finish.row && start.col != finish.col ){
       return isHorizontalPathClear(start, finish);
    }

    // You are moving vertical
    else if( start.row != finish.row && start.col == finish.col ) {
       return isVerticalPathClear(start, finish);
    }

    else if( diffRow == diffCol ){
        return isDiagonalPathClear(start, finish);
    }


    return false;
}


void Board::promotePawnToQueen(Piece &source, const ChessCoordinate &target){
    if( (target.row == 0 || target.row == 7) && (source.getPieceUnit() == PieceUnit::PAWN) ){
        source.setPiece(PieceUnit::QUEEN,source.getColor());
    }

}

//Check's if a square is under attack
bool Board::isSquareUnderAttack(const ChessCoordinate &position, Color kingColor) const {


    //Function doesn't cover attacks from pawns, and other kings.
    //Now we need to test the position vertically, horizontally, and attacks from knights.


    //All possible moves of a knight
    int knightMoveX[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    int knightMoveY[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

    //Checking if any of these squares has an enemy knight
    for(int i = 0; i < 8; i++){
        int row = knightMoveX[i] + position.row;
        int col = knightMoveY[i] + position.col;
        if(row >= 0 && row <= 7 && col >= 0 && col <= 7){
            Piece potentialEnemy = chessBoard.at(row).at(col);
            if( potentialEnemy.getColor() != kingColor && potentialEnemy.getPieceUnit() == PieceUnit::KNIGHT){
                return true;
            }
        }
    }


    /*
    if( isAttackedHorizontally(position, ChessCoordinate{position.row,7}, kingColor  ) ){
        return true;
    }if( isAttackedHorizontally(position, ChessCoordinate{position.row,0}, kingColor) ){
        return true;
    } */

    if( isAttackedVertically(position, kingColor) ){
        return true;
    }

     if(isAttackedDiagonally(position, kingColor)){
        return true;
    }





    return false;
}

ChessErrorCode Board::executeCastle(const ChessCoordinate &start, const ChessCoordinate &finish){

    // We also need to check if the path is clear here

     //INPUT THE CORRECT COORDINATES
     int dirSquare  = (finish.col - start.col > 0 ) ? 1 : -1;

     bool isAttacked = isSquareUnderAttack({start.row, start.col + dirSquare}, getPieceColor(start));
     if(isAttacked){
        return ChessErrorCode::INVALID_CASTLE;
     }
     isAttacked = isSquareUnderAttack({start.row, start.col + dirSquare*2}, getPieceColor(start));
     if(isAttacked){
        return ChessErrorCode::INVALID_CASTLE;
     }



     int direction = start.col - finish.col;
     int rookRow = 0;
     rookRow = (direction > 0) ? 1 : -1;
     int rookCol = (rookRow == 1) ? 0 : 7;

     Piece &rookPiece = requestPiece({finish.row,rookCol});
     Piece &endSpot = requestPiece({finish.row,finish.col + rookRow});

     if(rookPiece.getHasMoved() || rookPiece.getPieceUnit() != PieceUnit::ROOK){
        return ChessErrorCode::INVALID_CASTLE;
     }

     Piece::updatePiece(rookPiece,endSpot);
     return ChessErrorCode::VALID_MOVE;

}


/////END PRIVATE          //////


/// -------------------------------- BEGIN PUBLIC METHODS ------------------------------------////

/**
 * @return A picture of the board as a string to output to console.
 */
const std::string Board::getBoardView() const {

    std::stringstream stream;

    stream << "   abcdefgh\n___________\n";

    int num = 1;
    for(const vector<Piece> row : chessBoard){
        stream << num << "| ";
        drawRow(row,stream);
        num++;
    }
    stream << "___________\n";

    return std::move(stream.str());
}

/**
 * Gets a flipped view of the board for the second player to look at.
 */
const std::string Board::getReverseBoardView() const {
    std::stringstream stream;

    stream << "   hgfedcba\n___________\n";

    for(int num = 8 ; num > 0 ; num--){
        stream << num << "| ";
        const vector<Piece> &row = chessBoard.at(num - 1);
        drawRowReverse(row,stream);
    }

    return std::move(stream.str());

}


/***
 *
 * @param start - The coordinates of the piece you want to move
 * @param finish - The spot you want to want that piece to end up at.
 * @return - An ChessErrorCode that specifies whether the move succeded or failed
 */
ChessErrorCode Board::movePiece(const ChessCoordinate &start, const ChessCoordinate &finish) {

    Piece &sourcePiece = requestPiece(start);
    Piece &targetPiece = requestPiece(finish);

    if( ( sourcePiece.getColor() == targetPiece.getColor() ) || sourcePiece.getPieceUnit() == PieceUnit::NONE    ){
        return ChessErrorCode::INVALID_PIECE;
    }

    // If Piece is a Knight path is meaningless since they can jump over units
    bool pathClear = (sourcePiece.getPieceUnit() == PieceUnit::KNIGHT);

    if(!pathClear) { pathClear = isPathClear(start,finish); }
    if(!pathClear) {  return ChessErrorCode::INVALID_MOVE; }

    //Code for king movement, since king have special rules.
    if(sourcePiece.getPieceUnit() == PieceUnit::KING){
        bool isSquareAttacked = isSquareUnderAttack(finish,sourcePiece.getColor());
        if(isSquareAttacked){
            return ChessErrorCode::INVALID_KING_MOVE;
        }
    }


    ChessErrorCode ChessCode = sourcePiece.checkMovementIsValid(start,finish,targetPiece.getColor());

    //Special case for when user attempts to CASTLE
    if(ChessCode == ChessErrorCode::CASTLE) {
        ChessCode = executeCastle(start, finish);
        if (ChessCode == ChessErrorCode::VALID_MOVE) {
            Piece::updatePiece(sourcePiece, targetPiece);
        }
        return ChessCode;
    } else if(ChessCode == ChessErrorCode::VALID_MOVE){
        promotePawnToQueen(sourcePiece, finish);
        lastPieceKilled.setPiece( targetPiece.getPieceUnit() , targetPiece.getColor() );
        sourcePiece.updatePiece(sourcePiece,targetPiece);
        return ChessCode;
    }

    return ChessCode;

}

/**
 *  Enter's in a coordinate and returns the piece at that location
 */
Piece& Board::requestPiece(const ChessCoordinate &position) {
    return chessBoard.at( position.row ).at( position.col );
}

const Piece& Board::getPiece(const ChessCoordinate &position) const {
    return chessBoard.at( position.row ).at( position.col );
}



const PieceUnit Board::requestUnit(const ChessCoordinate &position) const {
    Piece a = chessBoard.at(position.row).at(position.col);
    return a.getPieceUnit();
}


const Color Board::getPieceColor(const ChessCoordinate &position) const {
    return chessBoard.at(position.row).at(position.col).getColor();
}

//Constructor
Board::Board() {
    chessBoard.reserve(8);
    initializeGame(chessBoard);
    lastPieceKilled = Piece{PieceUnit::NONE,Color::COLORLESS};
}

Board::Board(vector<vector<Piece>> &chessBoard) {
    this->chessBoard = chessBoard;
    lastPieceKilled = Piece{PieceUnit::NONE, Color::COLORLESS};


    assert(chessBoard.size() == 8);
    for(int i = 0; i<7; i++){
        assert(chessBoard.at(i).size() == 8);
    }

}


const std::unordered_map<PieceUnit, char> Board::PieceLookUp = {
        {PieceUnit::NONE,         '-'},
        {PieceUnit::PAWN,         'P'},
        {PieceUnit::KNIGHT,       'N'},
        {PieceUnit::BISHOP,       'B'},
        {PieceUnit::ROOK,         'R'},
        {PieceUnit::KING,         'K'},
        {PieceUnit::QUEEN,        'Q'},
};
