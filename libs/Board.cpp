//
// Created by jordanhoang on 11/02/19.
//

#include "Board.h"
#include <vector>
#include <iostream>

template <typename T>
void printCont(T const& container){

    for(auto it = container.begin() ; it!=container.end() ; it++){
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

}




//Private Functions
void Board::createBackRank(bool IS_BLACK, vector<vector<PieceId>> &boardView) {

    vector<PieceId> tmp;
    tmp.reserve(8);
    if(IS_BLACK){
        tmp.push_back(ROOK);
        tmp.push_back(KNIGHT);
        tmp.push_back(BISHOP);
        tmp.push_back(QUEEN);
        tmp.push_back(KING);
        tmp.push_back(BISHOP);
        tmp.push_back(KNIGHT);
        tmp.push_back(ROOK);
    } else{
        tmp.push_back(WHITE_ROOK);
        tmp.push_back(WHITE_KNIGHT);
        tmp.push_back(WHITE_BISHOP);
        tmp.push_back(WHITE_QUEEN);
        tmp.push_back(WHITE_KING);
        tmp.push_back(WHITE_BISHOP);
        tmp.push_back(WHITE_KNIGHT);
        tmp.push_back(WHITE_ROOK);
    }
    boardView.push_back(tmp);
}


void Board::initializeGame(vector<vector<PieceId>> &boardView) {

    bool isBlack = true;

    //Doing blackSide
    createBackRank(isBlack,boardView);

    std::vector<PieceId> blackPawn;
    blackPawn.assign(8,PAWN);
    boardView.push_back(blackPawn);


    for (int i = 2; i < 6; i++){
        std::vector<PieceId> tmp;
        tmp.assign(8,NONE);
        boardView.push_back(tmp);
    }

    //Doing white side
    std::vector<PieceId> whitePawn;
    whitePawn.assign(8,WHITE_PAWN);
    boardView.push_back(whitePawn);

    createBackRank(!isBlack,boardView);


}


void Board::drawRow(vector<PieceId> &listPieceId) const {


    for(PieceId iter: listPieceId){
        auto search = PieceLookUp.find(iter);
        //We also need to know the color.....

        std::cout << search->second ;
    }

    std::cout << std::endl;

}





//Non-private functions

//Constructor
Board::Board() {
    Piece pawn(1,0,'A',PAWN);
    boardView.reserve(8);
    initializeGame(boardView);





}




void Board::drawBoard() const {

    for(vector<PieceId> p : boardView){
        drawRow(p);
    }

}

const std::unordered_map<PieceId, char> Board::PieceLookUp = {
        {NONE,         '-'},
        {PAWN,         'P'},
        {KNIGHT,       'N'},
        {BISHOP,       'B'},
        {ROOK,         'R'},
        {KING,         'K'},
        {QUEEN,        'Q'},
        {WHITE_PAWN,   'P'},
        {WHITE_BISHOP, 'B'},
        {WHITE_KNIGHT, 'N'},
        {WHITE_ROOK  , 'R'},
        {WHITE_KING  , 'K'},
        {WHITE_QUEEN , 'Q'}
};