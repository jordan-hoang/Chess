//
// Created by jordanhoang on 12/02/19.
//

#ifndef CHESS_CHESSCONTROLLER_H
#define CHESS_CHESSCONTROLLER_H


#include <string>
#include "Board.h"

/**Originally was used for online play in "TextAdventure"
 * Main program just passes in 2 seperate players.
 */
struct ChessPlayer {
    std::string playerName;
    Color playerColor;

    ChessPlayer() : playerName(""),playerColor(Color::RED_LOWERCASE){};
    explicit ChessPlayer( std::string playerName, Color color) :
        playerName(std::move(playerName)),playerColor(color){};

};


/**
 * Takes user input and manipulates the board(model).
 */
class ChessController {
    public:

        ChessErrorCode readInput(std::string &input, const std::string &player);

        ChessErrorCode executeMove(std::string &moveFrom, std::string &moveTo);
        ChessErrorCode executeMove(std::string &moveFrom, std::string &moveTo,
                         const std::string &player);

        void initializeSide(const std::string &playerOne, const std::string &playerTwo);
        bool isGameFinished() const;
        std::string gameOverMessage() const;
        const std::string getBoardView() const;
        const std::string getReverseBoardView() const;
        std::string helpMessage() const;

        ChessController();

private:
        Board _gameBoard;
        ChessPlayer _playerOne;
        ChessPlayer _playerTwo;


        ChessErrorCode executeMoveHelper(std::string &moveFrom, std::string &moveTo, ChessCoordinate &startPos,
                                         ChessCoordinate &finishPos);
        int convertCharColToInt(char input);
        int convertChessRowToInt(char input);
        bool validatePlayer(const std::string &playerName, const Color &color) const;
        ChessErrorCode processChessMove(const ChessCoordinate &startPos,const ChessCoordinate &finishPos ) ;

};


#endif //CHESS_CHESSCONTROLLER_H
