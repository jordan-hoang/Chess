//
// Created by jordan on 30/04/19.
//

#include "MoveRecorder.h"
#include <sstream>
#include <Board.h>

MoveRecorder::MoveRecorder() = default;

//Add
void MoveRecorder::addMove(ChessCoordinate startPos,  ChessCoordinate finishPos, Piece killed) {

    std::unique_ptr<ChessMove> tmp(new ChessMove());
    tmp->move = std::make_pair(startPos,finishPos);
    tmp->pieceKilled = killed;
    m_listOfGameMoves.emplace_back( std::move(tmp) ); //You need to use std::move to transfer ownership.

}

void MoveRecorder::removeLastMove() {
    m_listOfGameMoves.pop_back();
}

ChessMove const * MoveRecorder::getLastMove() const{
    if(hasMove()){
        return m_listOfGameMoves.back().get();
    }
    ChessMove * tmp = nullptr;
    return tmp;  //////////JANKY CODE REMOVE LATER
}

bool MoveRecorder::hasMove() const {
    return !m_listOfGameMoves.empty();
}


std::string MoveRecorder::printMoves() {
    std::stringstream outputStream;
    for( const auto &myPair : m_listOfGameMoves) {
        outputStream << myPair->move.first << ", " << myPair->move.second << "\n";
    }
    return outputStream.str();
}


/**
 *Janky code
 * @param board The board on which you want to "undo a move on"
 */
void MoveRecorder::undoMove(vector<vector<Piece>> &board) {
    if(!hasMove()){
        return;
    }

    ChessMove const * lastMove = getLastMove();

    // Here do lastMove.execute() polymorphic code should handle it.

    /*
    const ChessCoordinate &start = lastMove->move.first;
    const ChessCoordinate &end = lastMove->move.second;

    //We need to undo a move so we take the piece at end and set it back to start,
    //and we place the original piece back at start.

    Piece &moveFrom = board[end.row][end.col];
    Piece &moveTo   = board[start.row][start.col];

    Piece::updatePiece(moveFrom,moveTo);
    moveFrom.setPiece(lastMove->pieceKilled);
     */


    lastMove->undoMove(board);


    removeLastMove();


}