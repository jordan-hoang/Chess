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


//Private Functions
void Board::createBackRank(Color color, vector<vector<Piece>> &boardView) {

    vector<Piece> tmp;
    tmp.reserve(8);

        tmp.emplace_back(Piece{ROOK,color});
        tmp.emplace_back(Piece{KNIGHT,color});
        tmp.emplace_back(Piece{BISHOP,color});


        tmp.emplace_back(Piece{QUEEN,color});
        tmp.emplace_back(Piece{KING,color});


        tmp.emplace_back(Piece{BISHOP,color});
        tmp.emplace_back(Piece{KNIGHT,color});
        tmp.emplace_back(Piece{ROOK,color});


    boardView.push_back(tmp);
}

void Board::initializeGame(vector<vector<Piece>> &boardView) {


    //Doing red side
    createBackRank(RED_LOWERCASE,boardView);

    std::vector<Piece> blackPawn;
    blackPawn.assign(8, Piece{PAWN,RED_LOWERCASE});
    boardView.push_back(blackPawn);


    for (int i = 2; i < 6; i++){
        std::vector<Piece> tmp;
        tmp.assign(8,Piece{NONE,COLORLESS});
        boardView.push_back(tmp);
    }

    //Doing blue side
    std::vector<Piece> whitePawn;
    whitePawn.assign(8,Piece{PAWN,BLUE_UPPERCASE});
    boardView.push_back(whitePawn);

    createBackRank(BLUE_UPPERCASE,boardView);


}


void Board::drawRow(const vector<Piece> &listPieceId, std::stringstream &stream) const {
    for(Piece iter: listPieceId){
        auto search = PieceLookUp.find( iter.getPieceUnit() );

        //Since printing out color doesn't work, we will make 1 side lower case
        switch(iter.getColor())
        {
            case RED_LOWERCASE:
                stream  << (char)tolower(search->second);
                break;
            case BLUE_UPPERCASE:
                stream << search->second;
                break;
            default:
                stream << search->second ;
        }

    }
    stream << '\n';
}

void Board::drawRowReverse(const vector<Piece> &listPieceId, std::stringstream &stream) const {

    for(int i = 7; i >= 0 ; i--){
        auto iter = listPieceId.at(i);
        auto search = PieceLookUp.find(iter.getPieceUnit());
        //Since printing out color doesn't work, we will make 1 side lower case
        switch(iter.getColor())
        {
            case RED_LOWERCASE:
                stream  << (char)tolower(search->second);
                break;
            case BLUE_UPPERCASE:
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
 * @return True if NONE was not found else returns false.
 *
 */
bool Board::checkHorizontalPath(const ChessCoordinate &start, const ChessCoordinate &finish) const {


    const vector<Piece> &handle = boardView.at(start.row);
    const auto iterBegin = handle.begin() + std::min(start.col,finish.col ) + 1 ;
    const auto iterEnd = handle.begin() + std::max(start.col,finish.col) ;

    //We are only searching w/e the path specifies
    const auto result = std::find_if(iterBegin,iterEnd,
            [&](auto i) { return i.getPieceUnit() != NONE ;} );


    //If enum NONE was not found result will be set to iterEnd.
    return (result == iterEnd);
}

/**
 * Determines w/e the path is free vertically
 * @param start
 * @param finish
 */
bool Board::checkVerticalPath(const ChessCoordinate &start, const ChessCoordinate &finish) const {

    int begin = std::min(start.row,finish.row);
    int end = std::max(start.row,finish.row);


    // + 1 for the space in front of it
    for(int i = begin + 1; i < end ; i++){
        if(requestUnit({i,start.col}) != NONE ){
            return false;
        }
    }
    return true;

}

//2 slopes + or - and 2 ways to traverse them so 4 ways in total....
bool Board::checkDiagonalPath(const ChessCoordinate &start, const ChessCoordinate &finish) const{

    // A bishop's diagonal can be defined by y = x or y = -x
    int endIter = abs(finish.col - start.col);

    int curX = start.col;
    int curY = start.row;

    int changeX = ( (finish.col - start.col) > 0 ) ? 1 : -1;
    int changeY = ( (finish.row - start.row) > 0 ) ? 1 : -1;


    for(int i = 0; i < endIter - 1; i++){
        curX += changeX;
        curY += changeY;
        if(requestUnit({curY,curX}) != NONE   ){
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
       return checkHorizontalPath(start,finish);
    }

    // You are moving vertical
    else if( start.row != finish.row && start.col == finish.col ) {
       return checkVerticalPath(start,finish);
    }

    else if( diffRow == diffCol ){
        return checkDiagonalPath(start,finish);
    }


    return false;
}

//Automatically promotes pawn at edge of board.
void Board::promotePawnToQueen(Piece &source, const ChessCoordinate &target){
    if( (target.row == 0 || target.row == 7) && (source.getPieceUnit() == PAWN) ){
        source.setPiece(QUEEN,source.getColor());
    }

}
/////END PRIVATE //////

// BEGIN PUBLIC METHODS ///
const std::string Board::getBoardView() const {

    std::stringstream stream;

    stream << "   abcdefgh\n___________\n";

    int num = 1;
    for(const vector<Piece> row : boardView){
        stream << num << "| ";
        drawRow(row,stream);
        num++;
    }
    stream << "___________\n";

    return std::move(stream.str());
}


const std::string Board::getReverseBoardView() const {
    std::stringstream stream;

    stream << "   hgfedcba\n___________\n";

    for(int num = 8 ; num > 0 ; num--){
        stream << num << "| ";
        const vector<Piece> &row = boardView.at(num - 1);
        drawRowReverse(row,stream);
    }

    return std::move(stream.str());

}



bool Board::movePiece(const ChessCoordinate &start, const ChessCoordinate &finish) {

    Piece &sourcePiece = requestPiece(start);
    Piece &targetPiece = requestPiece(finish);

    if( ( sourcePiece.getColor() == targetPiece.getColor() ) || sourcePiece.getPieceUnit() == NONE    ){
        return false;
    }

    // If Piece is a Knight path is meaningless since they can jump over units
    bool pathClear = (sourcePiece.getPieceUnit() == KNIGHT);

    if(!pathClear) { pathClear = isPathClear(start,finish); }
    if(!pathClear) {  return false; }

    bool isValid = sourcePiece.checkMovementIsValid(start,finish,targetPiece.getColor());

    if(isValid){
        promotePawnToQueen(sourcePiece, finish);
        lastPieceKilled.setPiece( targetPiece.getPieceUnit() , targetPiece.getColor() );
        sourcePiece.updatePiece(sourcePiece,targetPiece);
        return true;
    } else{
        return false;
    }

}

/**
 *  Enter's in a coordinate and returns the piece at that location
 */
Piece& Board::requestPiece(const ChessCoordinate &position) {
    return boardView.at( position.row ).at( position.col );
}

const PieceUnit Board::requestUnit(const ChessCoordinate &position) const {
    Piece a = boardView.at(position.row).at(position.col);
    return a.getPieceUnit();
}

//Constructor
Board::Board() {
    boardView.reserve(8);
    initializeGame(boardView);
    lastPieceKilled = Piece{NONE,COLORLESS};
}


const std::unordered_map<PieceUnit, char> Board::PieceLookUp = {
        {NONE,         '-'},
        {PAWN,         'P'},
        {KNIGHT,       'N'},
        {BISHOP,       'B'},
        {ROOK,         'R'},
        {KING,         'K'},
        {QUEEN,        'Q'},
};
