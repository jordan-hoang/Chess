//
// Created by jordan on 30/04/19.
//

#include "MoveRecorder.h"
#include <sstream>

MoveRecorder::MoveRecorder() = default;

//Add
void MoveRecorder::addMove(ChessCoordinate startPos,  ChessCoordinate finisHPos) {
    m_listOfGameMoves.emplace_back(std::make_pair(startPos,finisHPos));
}

void MoveRecorder::removeLastMove() {
    m_listOfGameMoves.pop_back();
}

std::pair<ChessCoordinate,ChessCoordinate> MoveRecorder::getLastMove(){
    return m_listOfGameMoves.back();
}

std::string MoveRecorder::printMoves() {

    std::stringstream outputStream;
    for(std::pair<ChessCoordinate,ChessCoordinate> myPair : m_listOfGameMoves){
        outputStream << myPair.first << " , " << myPair.second;
    }

    return outputStream.str();
}