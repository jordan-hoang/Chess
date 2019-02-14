//
// Created by jordanhoang on 11/02/19.
//

#include "../header/Board.h"
#include <vector>
#include <iostream>
#include <assert.h>
#include "../../termcolor.hpp"




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

    bool isBlack = true;

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

    Piece &sourcePiece = requestPiece(start);
    Piece &targetPiece = requestPiece(finish);


//    std::cout << " sourcePiece is a " << pieceLookUp(sourcePiece) << " \n"; //debug
//    std::cout << " targetPiece is a " << pieceLookUp(targetPiece) << " \n"; //debug


    if( ( sourcePiece.getColor() == targetPiece.getColor() ) || sourcePiece.getPieceUnit() == NONE    ){
        std::cout << "ERROR MOVING PIECE OF SAME UNIT ON TOP OF ITSELF OR ATTEMPTING TO MOVE NOTHING \n";
        return false;
    }

    bool isValid = sourcePiece.checkMovementIsValid(start,finish);

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


vector<vector<Piece>> &Board::getBoard() {
    return boardView;
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