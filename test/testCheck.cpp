//
// Created by jordan on 29/05/19.
//
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ChessController.h"
#include "Board.h"


/**
 *
 * Validates that the king cannot enter squares that can be attacked by an enemy knight, and enemies pawn.
 * Has a quick test for killing pawns diagonally backwards
 *
 */

/*
TEST(TestCheck, check) {


    ChessController a;
    std::string input;
    std::string p1 = "playerOne";
    std::string p2 = "playerTwo";

    input = "e2,e4";

    a.readInput(input,p1);

    input = "e1,e2";
    a.readInput(input,p1);

    input = "e2,e3";
    a.readInput(input,p1);

    input = "e3,d4";
    a.readInput(input,p1);

    input = "d4,d5";
    a.readInput(input,p1);

    input = "e7,e6";
    a.readInput(input,p2);

    input = "d5,e6";
    a.readInput(input,p1);

    input = "d5,d4";
    a.readInput(input,p1);

    std::cout << a.getBoardView();

}
*/

/*
TEST(CHECK_MATE, foolsMate){

    ChessController game;

    std::string p1 = "playerOne";
    std::string p2 = "playerTwo";
    std::string move;

    move = "f2,f3";
    EXPECT_EQ(game.readInput(move,p1), ChessErrorCode::VALID_MOVE);


    move = "g2,g4";
    EXPECT_EQ(game.readInput(move,p1), ChessErrorCode::VALID_MOVE);


    move = "e7,e5";
    EXPECT_EQ(game.readInput(move,p2), ChessErrorCode::VALID_MOVE);

    move = "d8,h4";
    EXPECT_EQ(game.readInput(move,p2), ChessErrorCode::CHECK_MATED);


    std::cout << game.getBoardView();

}
*/

TEST(CHECK_MATE, foolsMateDirect){
    Board a;

    ChessCoordinate start;
    ChessCoordinate finish;
    start = {1,5};
    finish = {2,5};

    a.movePiece(start,finish);

    start = {1,6};
    finish= {3,6};

    a.movePiece(start,finish);

    start={6,4};
    finish={4,4};

    a.movePiece(start,finish);

    start={7,3};
    finish={3,7};

    a.movePiece(start,finish);

    std::cout << a.getBoardView();







}