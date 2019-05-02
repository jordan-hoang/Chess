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
    return  _gameBoard.getBoardView();
}

const std::string ChessController::getReverseBoardView() const{
    return _gameBoard.getReverseBoardView();
}


/**
 * Checks to see if the input is valid.
 * @param startPos - The position you are starting from
 * @param finishPos - The position you expect to finish at.
 */
ChessErrorCode ChessController::processChessMove(const ChessCoordinate &startPos, const ChessCoordinate &finishPos) {

    if(startPos.col <= -1 || startPos.row <= -1 || finishPos.col <= -1 || finishPos.row <= -1){
        return ChessErrorCode::INVALID_INPUT;
    }

    if(startPos.col >= 8 || startPos.row >= 8 || finishPos.row >= 8 || finishPos.col >= 8){
        return ChessErrorCode::INVALID_INPUT;
    }

    return  _gameBoard.movePiece(startPos, finishPos);
}


/**
 * @return A message on how to play the game
 */
std::string ChessController::helpMessage() const{
    return "insert helpful message here";
}


/**
 * Checks if the chessGame has ended
 * @return True  - If the last piece killed is a king.
 */
bool ChessController::isGameFinished() const {
    const Piece &a = _gameBoard.getLastPieceKilled();
    if(a.getPieceUnit() == PieceUnit::KING){
        return true;
    }
    return false;
}

//Should be called after isGameFinished.
std::string ChessController::gameOverMessage() const {

    std::string stream = "";
    const Piece &piece = _gameBoard.getLastPieceKilled();

    if(piece.getPieceUnit() != PieceUnit::KING){
        assert(-1 && "This function shouldn't be called yet! game hasn't ended");
    }
    else if( piece.getColor() == Color::RED_LOWERCASE ){
        stream =  "Blue wins!";
    } else {
        stream = "Red wins";
    }
    return stream;
}



void ChessController::initializeSide(const std::string &playerOne, const std::string &playerTwo) {

    this->_playerOne.playerName  = playerOne;
    this->_playerOne.playerColor = Color::RED_LOWERCASE;

    this->_playerTwo.playerName  = playerTwo;
    this->_playerTwo.playerColor = Color::BLUE_UPPERCASE;

}


//Checks to see if a red player doesn't attempt to move a piece that doesn't belong to them.
bool ChessController::validatePlayer(const std::string &playerName, const Color &color) const {

    if(_playerOne.playerName == playerName){
        return (_playerOne.playerColor == color);
    }
    if(_playerTwo.playerName == playerName){
        return (_playerTwo.playerColor == color);
    }

    return false;
}




/**
 * Player inputs move into this function.
 * @param input - Player's input
 * @param player - The playerName that has entered this input
 * @return - Code on whether it was sucessful or not
 */
ChessErrorCode ChessController::readInput(std::string &input, const std::string &player) {

    std::vector<std::string> result;

    if(input.size() >= 10){
        return ChessErrorCode::INVALID_INPUT;
    }
    boost::trim(input);
    boost::split(result,input,boost::is_any_of(","));

    if(result.size() != 2  || result.at(0).size() != 2 || result.at(1).size() != 2 ){
        //print out error message
        return ChessErrorCode::INVALID_INPUT;
    }

    if(result.size() != 2  || result.at(0).size() != 2 || result.at(1).size() != 2 ){
        return ChessErrorCode::INVALID_INPUT;
    }

    return executeMove(result.at(0),result.at(1),player);
}

/**
 * Helper function for both versions of executeMove since they share alot of duplicate code.
 * @param moveFrom - Starting piece
 * @param moveTo  - Ending coordinate of starting piece
 * @param startPos - Converts moveFrom to a ChessCoordinate
 * @param finishPos - ""
 * @return
 */
ChessErrorCode ChessController::executeMoveHelper(std::string &moveFrom, std::string &moveTo, ChessCoordinate &startPos,
                                                  ChessCoordinate &finishPos)  {
    std::vector<std::string> result;
    result.push_back(moveFrom);
    result.push_back(moveTo);

    if(result.size() > 2  || result.at(0).size() != 2 || result.at(1).size() != 2 ){
        return ChessErrorCode::INVALID_INPUT;
    }

    int sCol = convertCharColToInt(result.at(0).at(0));
    int sRow = convertChessRowToInt(result.at(0).at(1));
    if(sCol == -1 || sRow == -1){
        return ChessErrorCode::INVALID_INPUT;
    }

    startPos.row = sRow;
    startPos.col = sCol;


    int finishPositionColumn = convertCharColToInt(result.at(1).at(0));
    int finishPositionRow = convertChessRowToInt(result.at(1).at(1));
    if(finishPositionColumn == -1 || finishPositionRow == -1){
        return ChessErrorCode::INVALID_INPUT;
    }

    finishPos.row = finishPositionRow;
    finishPos.col = finishPositionColumn;

    return ChessErrorCode::VALID_MOVE;
}


/**
 * @param input - Takes in a chess move. First specify the location of a piece then specify the
 * end spot next.
 *
 */
ChessErrorCode ChessController::executeMove(std::string &moveFrom, std::string &moveTo, const std::string &player) {

    ChessCoordinate startPos = {-1,-1};
    ChessCoordinate finishPos = {-1,-1};

    ChessErrorCode chessCode = executeMoveHelper(moveFrom, moveTo, startPos, finishPos);
    if(chessCode != ChessErrorCode::VALID_MOVE) {
        return chessCode;
    }

    const Color &pieceColor = _gameBoard.requestPiece(startPos).getColor();
    if( !validatePlayer(player, pieceColor) ) {
        return ChessErrorCode::INVALID_PIECE;
    }
    return processChessMove( startPos, finishPos );

}


/**
 * Move's piece regardless of color, left here for test class, but can also be used to replay matches
 * @param moveFrom - ChessCoordinate you are from
 * @param moveTo   - ChessCoordinate you are moving to.
 */
ChessErrorCode ChessController::executeMove(std::string &moveFrom, std::string &moveTo) {
    ChessCoordinate startPos = {-1,-1};
    ChessCoordinate finishPos = {-1,-1};
    executeMoveHelper(moveFrom, moveTo, startPos, finishPos);
    return processChessMove( startPos, finishPos );

}


void ChessController::undoMove() {
    _gameBoard.undoMove();
}



//Constructor that generates the game
ChessController::ChessController() {
    this->_playerOne = ChessPlayer( "playerOne", Color::RED_LOWERCASE  );
    this->_playerTwo = ChessPlayer( "playerTwo", Color::BLUE_UPPERCASE );
    this->_gameBoard  = Board();
}

//Constructor used for testing
ChessController::ChessController(vector<vector<Piece>> a) {
    this->_playerOne = ChessPlayer( "playerOne", Color::RED_LOWERCASE  );
    this->_playerTwo = ChessPlayer( "playerTwo", Color::BLUE_UPPERCASE );
    this->_gameBoard = Board(a);
}