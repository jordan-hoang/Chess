//
// Created by jordanhoang on 11/02/19.
//

#include "Board.h"
#include <vector>
#include <iostream>
#include <assert.h>
#include <algorithm>

#include "termcolor.hpp"



template <typename T>
void printCont(T const& container){

    for(auto it = container.begin() ; it!=container.end() ; it++){
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

}

//Private Functions
void Board::createBackRank(Color color, vector<vector<Piece>> &boardView) {

    vector<Piece> tmp;
    tmp.reserve(8);


        tmp.push_back(Piece{ROOK,color});
        tmp.push_back(Piece{KNIGHT,color});
        tmp.push_back(Piece{BISHOP,color});


        tmp.push_back(Piece{QUEEN,color});
        tmp.push_back(Piece{KING,color});


        tmp.push_back(Piece{BISHOP,color});
        tmp.push_back(Piece{KNIGHT,color});
        tmp.push_back(Piece{ROOK,color});


    boardView.push_back(tmp);
}

void Board::initializeGame(vector<vector<Piece>> &boardView) {


    //Doing red side
    createBackRank(RED,boardView);

    std::vector<Piece> blackPawn;
    blackPawn.assign(8, Piece{PAWN,RED});
    boardView.push_back(blackPawn);


    for (int i = 2; i < 6; i++){
        std::vector<Piece> tmp;
        tmp.assign(8,Piece{NONE,COLORLESS});
        boardView.push_back(tmp);
    }

    //Doing blue side
    std::vector<Piece> whitePawn;
    whitePawn.assign(8,Piece{PAWN,BLUE});
    boardView.push_back(whitePawn);

    createBackRank(BLUE,boardView);


}

//Shouldn't be here responsibility of the view
void Board::drawRow(vector<Piece> &listPieceId) const {

    for(Piece iter: listPieceId){
        auto search = PieceLookUp.find( iter.getPieceUnit() );
        //We also need to know the color.....

        //MOVE THIS TO THE VIEW CLASS BUT LEAVE HERE FOR EASY ACCESS FOR NOW
        switch(iter.getColor())
        {
            case RED:
                std::cout << termcolor::red << search->second;
                std::cout << termcolor::reset;
                break;
            case BLUE:
                std::cout << termcolor::blue << search->second;
                std::cout << termcolor::reset;
                break;
            default:
                std::cout << search->second ;
        }

    }

    std::cout << std::endl;

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
        std::cout << "Horizontally \n";
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



/////END PRIVATE //////

void Board::drawBoard() const {

    std::cout << "   abcdefgh\n___________\n";

    int num = 1;
    for(vector<Piece> p : boardView){
        std :: cout << num << "| ";
        drawRow(p);
        num++;
    }
    std::cout << "___________\n";


}

char Board::pieceLookUp(Piece piece){
  return  PieceLookUp.find(piece.getPieceUnit())->second;
}


bool Board::movePiece(const ChessCoordinate &start, const ChessCoordinate &finish) {

    //Perhaps have to requestPieces??????
    Piece &sourcePiece = requestPiece(start);
    Piece &targetPiece = requestPiece(finish);

 //   std::cout << " sourcePiece is a " << pieceLookUp(sourcePiece) << " \n"; //debug
 //   std::cout << " targetPiece is a " << pieceLookUp(targetPiece) << " \n"; //debug


    if( ( sourcePiece.getColor() == targetPiece.getColor() ) || sourcePiece.getPieceUnit() == NONE    ){
        std::cout << "ERROR MOVING PIECE OF SAME UNIT ON TOP OF ITSELF OR ATTEMPTING TO MOVE NOTHING \n";
        return false;
    }


    // If Piece is a Knight path is meaningless since they can jump over units
    bool pathClear = (sourcePiece.getPieceUnit() == KNIGHT);

    if(!pathClear) { pathClear = isPathClear(start,finish); }
    if(!pathClear) {  return false; }

    bool isValid = sourcePiece.checkMovementIsValid(start,finish,targetPiece.getColor());

    if(isValid){
        sourcePiece.updatePiece(sourcePiece,targetPiece);
     //   std::cout << "Updated start unit is : " << pieceLookUp(  requestPiece(start) ) << "\n";
     //   std::cout << "Updated finish unit is : " << pieceLookUp( requestPiece(finish) ) << " \n"; //debug
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