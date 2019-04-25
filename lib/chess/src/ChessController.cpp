//
// Created by jordanhoang on 12/02/19.
//

#include "ChessController.h"
#include <boost/algorithm/string.hpp>
#include <iostream>

/**
 * Converts a column to a integer Ex. the move a2 will convert the 'a' into a 0
 */
int ChessController::convertCharColToInt(char input){

    input = std::tolower(input);

   // std::cout << "input is " << input << "\n";
    switch(input){
        case 'a':
            return 0;
        case 'b':
            return 1;
        case 'c':
            return 2;
        case 'd':
            return 3;
        case 'e':
            return 4;
        case 'f':
            return 5;
        case 'g':
            return 6;
        case 'h':
            return 7;
    }

    return -1;
}

/**
 * @param input
 * @return The int for the vector to handle.
 */
int ChessController::convertChessRowToInt(char input){
    int result = input - '0';
    if(result < 0 || result > 8){
        return -1;
    }
    return result - 1;
}

/**
 *
 * @return A string that you can use to draw the board
 */
const std::string ChessController::getBoardView() const {
    return  gameBoard.getBoardView();
}

const std::string ChessController::getReverseBoardView() const{
    return gameBoard.getReverseBoardView();
}


/**
 * Checks to see if the input is valid.
 * @param startPos - The position you are starting from
 * @param finishPos - The position you expect to finish at.
 */
bool ChessController::processChessMove(const ChessCoordinate &startPos, const ChessCoordinate &finishPos) {

    if(startPos.col <= -1 || startPos.row <= -1 || finishPos.col <= -1 || finishPos.row <= -1){
        return false;
    }

    if(startPos.col >= 8 || startPos.row >= 8 || finishPos.row >= 8 || finishPos.col >= 8){
        return false;
    }

    return  gameBoard.movePiece(startPos, finishPos);
}


/**
 * @return A message on how to play the game
 */
std::string ChessController::helpMessage() const{

    //std::string msg = stringManager.getString(Internationalization::STRING_CODE::MINIGAME_CHESS_WELCOME_MESSAGE);
    return "insert helpful message here";

}


/**
 * Checks if the chessGame has ended
 * @return True  - If the last piece killed is a king.
 */
bool ChessController::isGameFinished() const {
    const Piece &a = gameBoard.getLastPieceKilled();
    if(a.getPieceUnit() == KING){
        return true;
    }
    return false;
}

//Should be called after isGameFinished.
std::string ChessController::gameOverMessage() const {

    std::string stream = "";
    const Piece &piece = gameBoard.getLastPieceKilled();

    if(piece.getPieceUnit() != KING){
        //send message here
    }
    else if( piece.getColor() == RED_LOWERCASE ){
        //
    } else {
        //
    }
    return std::move(stream);
}



void ChessController::initializeSide(const std::string &playerOne, const std::string &playerTwo) {

    this->_playerOne.playerName  = playerOne;
    this->_playerOne.playerColor = RED_LOWERCASE;

    this->_playerTwo.playerName  = playerTwo;
    this->_playerTwo.playerColor = BLUE_UPPERCASE;

}


//Checks to see if a red player doesn't attempt to move a piece that doesn't belong to them.
bool ChessController::validatePlayer(const std::string &playerName, const Color &color) const {

    if(_playerOne.playerName == playerName){
        return (_playerOne.playerColor == color);
    }
    if(_playerTwo.playerName == playerName){
        return (_playerTwo.playerColor == color);
    }

    static_assert(-1 && "No playerId matches the one assigned to this game???? you shouldn't see this message");
    return false;
}


bool ChessController::validatePlayerInput(std::string &input, std::vector<std::string> &result) {

    if(input.size() >= 10){
        return false;
    }
    boost::trim(input);
    boost::split(result,input,boost::is_any_of(","));

    if(result.size() != 2  || result.at(0).size() != 2 || result.at(1).size() != 2 ){
        //print out error message
        return false;
    }

    return true;
}


bool ChessController::readInput(std::string &input, const std::string &player) {

    std::vector<std::string> result;
    validatePlayerInput(input, result);

    if(result.size() != 2  || result.at(0).size() != 2 || result.at(1).size() != 2 ){
        return false;
    }

    return executeMove(result.at(0),result.at(1),player);
}



/**
 * @param input - Takes in a chess move. First specify the location of a piece then specify the
 * end spot next.
 *
 */
bool ChessController::executeMove(std::string &moveFrom, std::string &moveTo, const std::string &player) {

    std::vector<std::string> result;
    result.push_back(moveFrom);
    result.push_back(moveTo);

    if(result.size() > 2  || result.at(0).size() != 2 || result.at(1).size() != 2 ){
        return false;
    }


    int sCol =  convertCharColToInt(result.at(0).at(0));
    int sRow = convertChessRowToInt(result.at(0).at(1));
    if(sCol == -1 || sRow == -1){
        return false;
    }


    ChessCoordinate startPos{sRow,sCol};

    int finishPositionColumn = convertCharColToInt(result.at(1).at(0));
    int finishPositionRow = convertChessRowToInt(result.at(1).at(1));
    if(finishPositionColumn == -1 || finishPositionRow == -1){
        return false;
    }

    ChessCoordinate finishPos{ finishPositionRow,finishPositionColumn };

    const Color &pieceColor = gameBoard.requestPiece(startPos).getColor();
    if( !validatePlayer(player, pieceColor) ) {
        return false ;
    }
    return processChessMove( startPos, finishPos );

}


/**
 * Move's piece regardless of color, left here for test class.
 * @param moveFrom - ChessCoordinate you are from
 * @param moveTo   - ChessCoordinate you are moving to.
 */
bool ChessController::executeMove(std::string &moveFrom, std::string &moveTo) {

    std::vector<std::string> result;
    result.push_back(moveFrom);
    result.push_back(moveTo);


    if(result.size() > 2  || result.at(0).size() != 2 || result.at(1).size() != 2 ){
        return false;
    }

    int sCol =  convertCharColToInt(result.at(0).at(0));
    int sRow = convertChessRowToInt(result.at(0).at(1));

    if(sCol == -1 || sRow == -1){
        return false;
    }

    ChessCoordinate startPos{sRow,sCol};

    int finishPositionColumn = convertCharColToInt(result.at(1).at(0));
    int finishPositionRow = convertChessRowToInt(result.at(1).at(1));

    if(finishPositionColumn == -1 || finishPositionRow == -1){
        return false;
    }
    ChessCoordinate finishPos{ finishPositionRow,finishPositionColumn };

    return processChessMove( startPos, finishPos );
}


//Constructor
ChessController::ChessController() {
    this->_playerOne = ChessPlayer( "playerOne", RED_LOWERCASE  );
    this->_playerTwo = ChessPlayer( "playerTwo", BLUE_UPPERCASE );
    this->gameBoard  = Board();
}