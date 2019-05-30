//
// Created by jordan on 30/05/19.
//

#include <assert.h>
#include <algorithm>
#include "CheckMate.h"


//https://en.wikipedia.org/wiki/Opaque_pointer #C++
//Also known as the Bridge Pattern, in design patterns.
struct CheckMate::kingAttackers{
    Color colorVector;
    std::vector<ChessCoordinate> enemyCoordinates;

    kingAttackers(const Color color):colorVector(color){
        enemyCoordinates.reserve(4);
    };



};


CheckMate::~CheckMate() = default;
CheckMate::CheckMate() = default;

CheckMate::CheckMate(const Color playerOne, const Color playerTwo) {
    teamAlpha = std::make_unique<CheckMate::kingAttackers>(playerOne);
    teamBeta =  std::make_unique<CheckMate::kingAttackers>(playerTwo);
}




void CheckMate::addMove(const ChessCoordinate &enemyPosition, const vector<vector<Piece> > &m_chessBoard) {



    const auto &friendlyColor = m_chessBoard[enemyPosition.row][enemyPosition.col].getColor();

    if(teamAlpha->colorVector != friendlyColor){
        CheckMate::teamAlpha->enemyCoordinates.emplace_back(enemyPosition);
    } else if (teamBeta->colorVector != friendlyColor){
        CheckMate::teamBeta->enemyCoordinates.emplace_back(enemyPosition);
    } else {
        assert(-1 && "Error attempted to add a unit with an invalid color to CheckMate.cpp");
    }

}



bool CheckMate::isAttackedByPawn(const ChessCoordinate &start, const Color &kingColor,
                                 const vector<vector<Piece> > &m_chessBoard) {

    bool flag = false;

    if(kingColor == Color::BLUE_UPPERCASE){

        //bottom left of start and bottom right of start if contain pawn will mean that spot is dangerous
        ChessCoordinate bottomLeft{start.row - 1, start.col - 1};
        if(bottomLeft.isValid()){
            Piece tmp = m_chessBoard[bottomLeft.row][bottomLeft.col];

            if(tmp.getColor() == Color::RED_LOWERCASE && tmp.getPieceUnit() == PieceUnit::PAWN){
               addMove(ChessCoordinate{start.row - 1, start.col -1}, m_chessBoard);
                flag = true;
            }
        }

        ChessCoordinate bottomRight{start.row - 1, start.col + 1};
        if(bottomRight.isValid()) {
            Piece tmp = m_chessBoard[bottomRight.row][bottomRight.col];
            if (tmp.getColor() == Color::RED_LOWERCASE && tmp.getPieceUnit() == PieceUnit::PAWN) {
                addMove(ChessCoordinate{start.row - 1, start.col + 1}, m_chessBoard);
                flag = true;
            }
        }

    } else if(kingColor == Color::RED_LOWERCASE){
        //watch out for pawns coming from above!
        ChessCoordinate topLeft{start.row + 1, start.col - 1};
        if(topLeft.isValid()){
            Piece tmp = m_chessBoard[topLeft.row][topLeft.col];
            if(tmp.getColor() == Color::BLUE_UPPERCASE && tmp.getPieceUnit() == PieceUnit::PAWN){
                addMove(ChessCoordinate{start.row + 1, start.col - 1}, m_chessBoard);
                flag = true;
            }
        }
        ChessCoordinate topRight{start.row + 1, start.col + 1};
        if(topRight.isValid()){
            Piece tmp = m_chessBoard[topRight.row][topRight.col];
            if(tmp.getPieceUnit() == PieceUnit::PAWN && tmp.getColor() == Color::BLUE_UPPERCASE){
                addMove(ChessCoordinate{start.row + 1, start.col + 1}, m_chessBoard);
                flag = true;
            }
        }
    }

    return flag;


}

/**
 * NEEDS TESTING
 * @param start - coordinates of the square you want to check is under attack
 * @param finish - end/begin of the row
 * @return True if can be attacked else returns false.
 */
bool CheckMate::isAttackedHorizontally(const ChessCoordinate &start, const Color &friendlyColor,  const vector<vector<Piece> > &m_chessBoard)  {

    const vector<Piece> &handle = m_chessBoard.at(start.row);
    auto iterBegin = handle.begin() + start.col ;
    auto iterEnd = handle.end();

    //If the piece you are looking for is not None and the piece isn't the attack piece then......
    //Stops looking if it finds a piece that isn't none

    //Checking forwards towards the right, so --x-------a-----b--  "Piece a would look towards 'b' to find a rook or queen"
    auto result = std::find_if(iterBegin,iterEnd,
                               [&](auto i ) {return i.getPieceUnit() != PieceUnit::NONE ;} );

    if(result != iterEnd){
        if((*result).getColor() != friendlyColor &&  ((*result).getPieceUnit() == PieceUnit::ROOK ||
                                                  (*result).getPieceUnit() == PieceUnit::QUEEN )){
            addMove((*result).getCoordinate(), m_chessBoard);
            return true;
        }
    }


    //Checking backwards towards the left, so    --x-----a---- "Piece a would be checking towards x to find a rook or queen---
    const auto rIter = handle.rbegin() + start.col ;
    const auto resultTwo = std::find_if(rIter, handle.rend(),
                                        [&](auto i ) {return i.getPieceUnit() != PieceUnit::NONE ;} );

    if(resultTwo != handle.rend()){
        if((*resultTwo).getColor() != friendlyColor &&  ((*resultTwo).getPieceUnit() == PieceUnit::ROOK ||
                                                     (*resultTwo).getPieceUnit() == PieceUnit::QUEEN )){
            addMove((*resultTwo).getCoordinate(), m_chessBoard);
            return true;
        }
    }


    return false;
}

bool CheckMate::isAttackedVertically(const ChessCoordinate &start, const Color &friendlyColor,
                                     const vector<vector<Piece> > &m_chessBoard) {

    //We need to check vertically upwards, then vertically downwards, from the position START
    bool flag = false;

    for(int i = start.row ; i < 8 ; i++) {
        Piece tmp = m_chessBoard.at(i).at(start.col);
        if(tmp.getPieceUnit() == PieceUnit::ROOK || tmp.getPieceUnit() == PieceUnit::QUEEN){
            if(tmp.getColor() != friendlyColor){
                addMove({i,start.col},m_chessBoard);
                flag = true;
            }
        } if(tmp.getPieceUnit() != PieceUnit::NONE){  //but we need to stop checking if the piece we encounter is not
            break;
        }
        if(flag){
            break;
        }
    }

    //Now we check downwards, almost duplicated code, only for parameters changed
    for(int i = start.row ; i >= 0; i--) {
        Piece tmp = m_chessBoard.at(i).at(start.col);
        if(tmp.getPieceUnit() == PieceUnit::ROOK || tmp.getPieceUnit() == PieceUnit::QUEEN){
            if(tmp.getColor() != friendlyColor && tmp.getColor() != Color::COLORLESS){
                addMove({i, start.col}, m_chessBoard);
                flag =  true; //We checked upwards already so we can just return true
            }
        } if(tmp.getPieceUnit() != PieceUnit::NONE){  //but we need to stop checking if the piece we encounter is not
            break;
        }
        if(flag){
            break;
        }
    }

    return flag;


}

bool CheckMate::isAttackedDiagonally(const ChessCoordinate &start, const Color &kingColor,
                                     const vector<vector<Piece> > &m_chessBoard) {

    //Need code for bishops and pawns,pawns are special case.
    //RED PAWNS Travel upwards, BLUE PAWNS Travel downwards from Piece.cpp

    bool flag = false;
    if(isAttackedByPawn(start,kingColor, m_chessBoard)){
        flag = true;
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
            const Piece &tmp = m_chessBoard[startingPosition.row][startingPosition.col];

            if(tmp.getColor() != kingColor) {
                if (tmp.getPieceUnit() == PieceUnit::QUEEN || tmp.getPieceUnit() == PieceUnit::BISHOP) {
                    addMove(startingPosition, m_chessBoard);
                    flag = true;
                }
            } if(tmp.getPieceUnit() != PieceUnit::NONE ){
                isValid = false;
            }
            startingPosition.row += dirX[i];
            startingPosition.col += dirY[i];
        }

    }

    return flag;

}

bool CheckMate::isSquareUnderAttack(const ChessCoordinate &position, const Color &friendlyColor, const vector<vector<Piece> > &m_chessBoard) {


    //Now we need to test the position vertically, horizontally, and attacks from knights.
    //All possible moves of a knight
    std::vector<ChessCoordinate> enemies;


    int knightMoveX[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    int knightMoveY[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

    //Checking if any of these squares has an enemy knight
    for(int i = 0; i < 8; i++){
        int row = knightMoveX[i] + position.row;
        int col = knightMoveY[i] + position.col;
        if(row >= 0 && row <= 7 && col >= 0 && col <= 7){
            Piece potentialEnemy = m_chessBoard.at(row).at(col);
            if( potentialEnemy.getColor() != friendlyColor && potentialEnemy.getPieceUnit() == PieceUnit::KNIGHT){
                return true;
            }
        }
    }


    if( isAttackedHorizontally(position,  friendlyColor, m_chessBoard) ){
        return true;
    }

    if( isAttackedVertically(position, friendlyColor, m_chessBoard) ){
        return true;
    }

    return (isAttackedDiagonally(position, friendlyColor, m_chessBoard));



}




const vector<ChessCoordinate>& CheckMate::getAttackers(const Color &color) {

    if(teamAlpha->colorVector == color){
        return teamAlpha->enemyCoordinates;
    } else if(teamBeta->colorVector == color){
        return teamBeta->enemyCoordinates;
    }


    assert(-1 && "Invalid attackerColor");
    vector<ChessCoordinate> garbage;
    return std::move(garbage);

}

