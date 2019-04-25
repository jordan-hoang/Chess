//
// Created by jordanhoang on 12/02/19.
//

#ifndef CHESS_CHESSCONTROLLER_H
#define CHESS_CHESSCONTROLLER_H


#include <string>
#include "Board.h"


struct ChessPlayer {
    std::string playerName;
    Color playerColor;

    ChessPlayer() : playerName(""),playerColor(RED_LOWERCASE){};
    explicit ChessPlayer( std::string playerName, Color color) :
        playerName(std::move(playerName)),playerColor(color){};

};


/**
 * Takes user input and sends it to board.
 */
class ChessController {
    public:

        bool readInput(std::string &input, const std::string &player);

        bool executeMove(std::string &moveFrom, std::string &moveTo);
        bool executeMove(std::string &moveFrom, std::string &moveTo,
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


        int convertCharColToInt(char input);
        int convertChessRowToInt(char input);
        bool validatePlayer(const std::string &playerName, const Color &color) const;
        bool validatePlayerInput(std::string &input, std::vector<std::string> &result);
        bool processChessMove(const ChessCoordinate &startPos,const ChessCoordinate &finishPos ) ;

};


#endif //CHESS_CHESSCONTROLLER_H
