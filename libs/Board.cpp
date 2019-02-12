//
// Created by jordanhoang on 11/02/19.
//

#include "Board.h"
#include <vector>
#include <iostream>
#include "../termcolor.hpp"

template <typename T>
void printCont(T const& container){

    for(auto it = container.begin() ; it!=container.end() ; it++){
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

}




//Private Functions
void Board::createBackRank(Color color, vector<vector<PieceType>> &boardView) {

    vector<PieceType> tmp;
    tmp.reserve(8);


        tmp.push_back(PieceType{ROOK,color});
        tmp.push_back(PieceType{KNIGHT,color});
        tmp.push_back(PieceType{BISHOP,color});


        tmp.push_back(PieceType{QUEEN,color});
        tmp.push_back(PieceType{KING,color});


        tmp.push_back(PieceType{BISHOP,color});
        tmp.push_back(PieceType{KNIGHT,color});
        tmp.push_back(PieceType{ROOK,color});


    boardView.push_back(tmp);
}


void Board::initializeGame(vector<vector<PieceType>> &boardView) {

    bool isBlack = true;

    //Doing red side
    createBackRank(RED,boardView);

    std::vector<PieceType> blackPawn;
    blackPawn.assign(8,PieceType{PAWN,RED});
    boardView.push_back(blackPawn);


    for (int i = 2; i < 6; i++){
        std::vector<PieceType> tmp;
        tmp.assign(8,PieceType{NONE,COLORLESS});
        boardView.push_back(tmp);
    }

    //Doing blue side
    std::vector<PieceType> whitePawn;
    whitePawn.assign(8,PieceType{PAWN,BLUE});
    boardView.push_back(whitePawn);

    createBackRank(BLUE,boardView);


}


void Board::drawRow(vector<PieceType> &listPieceId) const {

    for(PieceType iter: listPieceId){
        auto search = PieceLookUp.find( iter.MyId );
        //We also need to know the color.....

        switch(iter.mycolor)
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


//Constructor
Board::Board() {
    boardView.reserve(8);
    initializeGame(boardView);
}




void Board::drawBoard() const {
    for(vector<PieceType> p : boardView){
        drawRow(p);
    }
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