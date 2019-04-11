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

    ChessPlayer() : playerName(""),playerColor(RED_LOWERCASE){}

};


/**
 * Takes user input and sends it to board.
 */
class MoveValidator {
    public:
        bool readChessMove(std::string &moveFrom, std::string &moveTo);

        bool readChessMove(std::string &moveFrom, std::string &moveTo,
                const std::string &player);


    void initializeSide(const std::string &playerOne, const std::string &playerTwo);

        bool isGameFinished() const;
        std::string gameOverMessage() const;
        const std::string getBoardView() const;
        const std::string getReverseBoardView() const;

        std::string helpMessage() const;
        void setPlayerOne(const std::string &playerOne);
        void setPlayerTwo(const std::string &playerTwo);

        MoveValidator(const std::string &playerOne);
        MoveValidator(const std::string &playerOne, const std::string &playerTwo);
        MoveValidator();


private:
        Board gameBoard;
        ChessPlayer playerOne;
        ChessPlayer playerTwo;


        int convertCharColToInt(char input);
        int convertChessRowToInt(char input);
        bool validatePlayer(const std::string &playerName, const Color &color) const;
        bool processChessMove(const ChessCoordinate &startPos,const ChessCoordinate &finishPos ) ;

};


#endif //CHESS_CHESSCONTROLLER_H
