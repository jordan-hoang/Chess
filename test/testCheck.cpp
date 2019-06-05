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
