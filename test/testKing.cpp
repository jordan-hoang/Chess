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
TEST(KING,kingMovement){

ChessController game;
std::string p1 = "playerOne";
std::string p2 = "playerTwo";

std::string input = "d7,d5";
game.readInput(input,p2);

input = "e8,d7";
game.readInput(input,p2);

input = "d7,d6";
game.readInput(input,p2);


input = "g1,f3";
game.readInput(input,p1);


//Now we test all possible combinations of squares that knight can attack
input = "d6,e5";
EXPECT_EQ(game.readInput(input,p2),ChessErrorCode::INVALID_KING_MOVE);

input = "d6,e6";
EXPECT_EQ(game.readInput(input,p2),ChessErrorCode::VALID_MOVE);

input = "e6,f6";
EXPECT_EQ(game.readInput(input,p2),ChessErrorCode::VALID_MOVE);

input = "f6,g5";
EXPECT_EQ(game.readInput(input,p2),ChessErrorCode::INVALID_KING_MOVE);

input = "f3,e5";
EXPECT_EQ(game.readInput(input,p1),ChessErrorCode::VALID_MOVE);

input = "f6,g6";
EXPECT_EQ(game.readInput(input,p2),ChessErrorCode::INVALID_KING_MOVE);

input = "f6,g5";
EXPECT_EQ(game.readInput(input,p2),ChessErrorCode::VALID_MOVE);


input = "g5,g4";
EXPECT_EQ(game.readInput(input,p2),ChessErrorCode::INVALID_KING_MOVE);

input = "g5,f4";
EXPECT_EQ(game.readInput(input,p2),ChessErrorCode::VALID_MOVE);

input = "f4,e4";
EXPECT_EQ(game.readInput(input,p2),ChessErrorCode::VALID_MOVE);

input = "e4,d4";
EXPECT_EQ(game.readInput(input,p2),ChessErrorCode::VALID_MOVE);

input = "d4,c4";
EXPECT_EQ(game.readInput(input,p2),ChessErrorCode::INVALID_KING_MOVE);

input = "d4,c5";
EXPECT_EQ(game.readInput(input,p2),ChessErrorCode::VALID_MOVE);

input = "c5,c6";
EXPECT_EQ(game.readInput(input,p2),ChessErrorCode::INVALID_KING_MOVE);


input = "e5,d7";
EXPECT_EQ(game.readInput(input,p1),ChessErrorCode::VALID_MOVE);



//input = "c5,d6";
//EXPECT_EQ(game.readInput(input,p2),ChessErrorCode::INVALID_MOVE);


std::cout << game.getBoardView();

input = "c5,b5";
EXPECT_EQ(game.readInput(input,p2),ChessErrorCode::VALID_MOVE);

std::cout << game.getBoardView();

/*
input = "d6,c5";
EXPECT_EQ(game.readInput(input,p2),ChessErrorCode::INVALID_KING_MOVE);

input = "d6,e5";
EXPECT_EQ(game.readInput(input,p2),ChessErrorCode::INVALID_KING_MOVE);
//All possible knight combinations.


//Now checking pawns
input = "d8,d7";
EXPECT_EQ(game.readInput(input,p2),ChessErrorCode::VALID_MOVE);



input = "e2,e4";
EXPECT_EQ(game.readInput(input,p1),ChessErrorCode::VALID_MOVE);

input = "e4,d5";
EXPECT_EQ(game.readInput(input,p1),ChessErrorCode::VALID_MOVE);


input = "d6,e6";
EXPECT_EQ(game.readInput(input,p2),ChessErrorCode::INVALID_KING_MOVE);


input = "d6,c6";
EXPECT_EQ(game.readInput(input,p2),ChessErrorCode::INVALID_KING_MOVE);
//Alright now we are going to check if the other king is responsive to the other teams pawns.


input = "e7,e5";
EXPECT_EQ(game.readInput(input,p2),ChessErrorCode::VALID_MOVE);


input = "e5,e4";
EXPECT_EQ(game.readInput(input,p2),ChessErrorCode::VALID_MOVE);


// Attempting to kill the pawn diagonally backwards
input = "d5,e4";
EXPECT_EQ(game.readInput(input,p1),ChessErrorCode::INVALID_MOVE);
//

input = "e1,e2";
EXPECT_EQ(game.readInput(input,p1),ChessErrorCode::VALID_MOVE);

input = "e2,e3";
EXPECT_EQ(game.readInput(input,p1),ChessErrorCode::VALID_MOVE);

input = "e3,d3";
EXPECT_EQ(game.readInput(input,p1),ChessErrorCode::INVALID_KING_MOVE);

input = "e3,f3";
EXPECT_EQ(game.readInput(input,p1),ChessErrorCode::INVALID_KING_MOVE);
 */

}