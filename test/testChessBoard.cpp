
//Tests the chessGame itself

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "MoveValidator.h"
#include "Board.h"

using std::string;



//first parameter is name of grouping, 2nd parameter is the name of the test
//Test's the pawns in the chess game
TEST(BoardTest,  pawn){

    MoveValidator move;
    std::string input = "a2";
    std::string target= "a3";

    bool isValid = move.readChessMove(input,target) ;
    EXPECT_EQ(isValid, true);

    //Move red pawn from a3 to a5 move is invalid cannot jump 2 squares
    input = "a3";
    target = "a5";
    isValid = move.readChessMove(input,target);
    EXPECT_EQ(isValid, false);

    //Move blue pawn in 'a' column down valid
    input = "a7";
    target = "a6";
    isValid = move.readChessMove(input,target);
    EXPECT_EQ(isValid, true);

    input = "a3";
    target = "a4";
    isValid = move.readChessMove(input,target);
    EXPECT_EQ(isValid, true);

    input = "a4";
    target = "a5";
    isValid = move.readChessMove(input,target);
    EXPECT_EQ(isValid, true);

    //Invalid move pawns can only kill diagonally
    input = "a5";
    target = "a6";
    isValid = move.readChessMove(input,target);
    EXPECT_EQ(isValid, false);
    // move.getBoardView();


    input = "h7";
    target = "h5";
    isValid = move.readChessMove(input,target);
    EXPECT_EQ(true,isValid);


    input = "h2";
    target = "h4";
    isValid = move.readChessMove(input,target);
    EXPECT_EQ(true,isValid);

    //Now move the attempt to move the pawns directly on top of each other, should be invalid.
    input = "h4";
    target = "h5";
    isValid = move.readChessMove(input,target);
    EXPECT_EQ(true,!isValid);


    input = "h5";
    target = "h4";
    isValid = move.readChessMove(input,target);
    EXPECT_EQ(true,!isValid);

}

TEST(BoardTest, pawnDiagonal){

    MoveValidator move;
    //move.getBoardView();

    std::string moveFrom = "a2";
    std::string moveTo = "a4";
    move.readChessMove(moveFrom,moveTo);

    moveFrom = "b7";
    moveTo = "b5";
    move.readChessMove(moveFrom,moveTo);

    //See if red can kill blue diagonally.
    moveFrom = "a4";
    moveTo = "b5";
    bool isValid = move.readChessMove(moveFrom,moveTo);
    EXPECT_EQ(true,isValid);

    moveFrom = "a7";
    moveTo = "a6";
    move.readChessMove(moveFrom,moveTo);

    //move.getBoardView();

    moveFrom = "b5";
    moveTo = "a6";
    isValid = move.readChessMove(moveFrom,moveTo);

    EXPECT_EQ(isValid,true);

    //move.getBoardView();

    //Now testing the blue side
    moveFrom = "b2";
    moveTo = "b4";
    move.readChessMove(moveFrom,moveTo);

    moveFrom = "c7";
    moveTo = "c5";
    move.readChessMove(moveFrom,moveTo);
    // move.getBoardView();

    moveFrom = "c5";
    moveTo = "b4";
    isValid = move.readChessMove(moveFrom,moveTo);
    EXPECT_EQ(true, isValid);
    // move.getBoardView();

    moveFrom = "c2";
    moveTo = "c3";
    move.readChessMove(moveFrom,moveTo);

    //move.getBoardView();

    moveFrom = "b4";
    moveTo = "c3";
    isValid = move.readChessMove(moveFrom,moveTo);
    EXPECT_EQ(true,isValid);

}

TEST(BoardTest,pawnDiagonalTwo){

    MoveValidator move;
    std::string input = "c2";
    std::string target = "c4";
    move.readChessMove(input,target);

    input = "d7";
    target = "d5";
    move.readChessMove(input,target);

    // move.getBoardView();

    //Illegal move pawn cannot move in this direction.
    input = "d5,e4";
    target = "e4";
    bool isValid = move.readChessMove(input,target);
    //move.getBoardView();
    EXPECT_EQ(isValid,false);

    input = "d5";
    target = "e6";
    isValid = move.readChessMove(input,target);
    EXPECT_EQ(isValid,false);

}

//To see where the pieces are use move.getBoardView()
TEST(BoardTest, Rook){


    MoveValidator move;

    string input = "a8";
    string target = "a7";
    bool isValid = move.readChessMove(input,target);
    EXPECT_EQ(false,isValid);

    input = "a7";
    target = "a5";
    move.readChessMove(input,target);

    input = "a8";
    target = "a6";
    isValid = move.readChessMove(input,target);
    EXPECT_EQ(isValid,true);

    input = "a6";
    target = "h6";
    isValid = move.readChessMove(input,target);
    EXPECT_EQ(true,isValid);


    input = "h6";
    target = "h2";
    isValid = move.readChessMove(input,target);
    EXPECT_EQ(isValid,true);

    //Now attempt to have rook attack piece behind it.
    input = "h2";
    target = "f2";
    isValid = move.readChessMove(input,target);

    // move.getBoardView();
    EXPECT_EQ(false,isValid);

    //Now test if the red rook can "Illegaly go through the blue rook. If you want to see the board do move.getBoardView//
    input = "h1";
    target = "h4";
    isValid = move.readChessMove(input,target);
    EXPECT_EQ(false,isValid);

    input = "h2";
    target = "g2";
    isValid = move.readChessMove(input,target);
    EXPECT_EQ(true,isValid);


    input = "h1";
    target = "h2";
    isValid = move.readChessMove(input,target);
    EXPECT_EQ(true,isValid);

    input = "g7";
    target = "g6";
    isValid = move.readChessMove(input,target);

    //Attempt to go through blue pawn
    input = "g2";
    target = "g6";
    isValid = move.readChessMove(input,target);
    EXPECT_EQ(false,isValid);


}

TEST(BoardTest, knight){
    MoveValidator move;
    //TESTING ALL THE POSSIBLE MOVES OF THE KNIGHT

    string input = "b1";
    string target = "c3";
    bool isValid = move.readChessMove(input,target);
    EXPECT_EQ(true,isValid);

    input = "c3";
    target = "b1";
    isValid = move.readChessMove(input,target);
    EXPECT_EQ(true,isValid);

    input = "b1";
    target = "a3";
    isValid = move.readChessMove(input,target);
    EXPECT_EQ(true,isValid);

    input = "a3";
    target = "b1";
    isValid = move.readChessMove(input,target);
    EXPECT_EQ(true,isValid);

    //Duplicate move
    input = "b1";
    target = "a3";
    isValid = move.readChessMove(input,target);
    EXPECT_EQ(true,isValid);


    input = "a3";
    target = "c4";
    isValid = move.readChessMove(input,target);
    EXPECT_EQ(true,isValid);

    input = "c4";
    target = "e3";
    isValid = move.readChessMove(input,target);
    EXPECT_EQ(true,isValid);


    input = "e3";
    target = "g4";
    isValid = move.readChessMove(input,target);
    EXPECT_EQ(isValid,true);
    //move.getBoardView();

    input = "g4";
    target = "e3";
    isValid = move.readChessMove(input,target);
    EXPECT_EQ(isValid,true);

    input = "e3";
    target = "c4";
    isValid = move.readChessMove(input,target);
    EXPECT_EQ(isValid,true);

}


TEST(BoardTest, testBishop){


    //Code should have been tested this way to begin with, but too lazy to rewrite all the methods above.
    Board bishop;

    bishop.movePiece({1,1},{2,1});
    PieceUnit  tmp = bishop.requestUnit({2,1});
    EXPECT_EQ(tmp,PAWN);

    bishop.movePiece({0,2},{2,0});
    EXPECT_EQ(bishop.requestUnit({2,0}),BISHOP);


    bishop.movePiece({2,0},{7,4});
    EXPECT_EQ(bishop.requestUnit({2,0}), BISHOP);


    bishop.movePiece({2,0},{7,5});
    EXPECT_EQ(bishop.requestUnit({2,0}), BISHOP); //Move should have failed bishop cannot go through units.

    bishop.movePiece({2,0},{6,4});
    EXPECT_EQ(bishop.requestUnit({2,0}),NONE);


}

TEST(BoardTest, testPromotionAndKillKing){

    Board board;

    board.movePiece({1,1},{3,1});
    board.movePiece({3,1},{4,1});
    board.movePiece({4,1},{5,1});
    board.movePiece({5,1},{6,2});
    board.movePiece({6,2},{7,3});

    EXPECT_EQ(board.requestUnit({7,3}), QUEEN );


    board.movePiece({6,4},{4,4});

    board.movePiece({4,4},{3,4});
    board.movePiece({3,4},{2,4});
    board.movePiece({2,4},{1,3});
    board.movePiece({1,3},{0,2});


    EXPECT_EQ(board.requestUnit({0,2}), QUEEN );



    board.movePiece({0,2},{0,3});

    EXPECT_EQ(board.getLastPieceKilled().getPieceUnit(), QUEEN);


    board.movePiece({0,3},{0,4});


    EXPECT_EQ(board.getLastPieceKilled().getPieceUnit(),KING);





}



TEST(MoveValidatorTest, testTurn){

    std::string p1 = "playerOne";
    std::string p2 = "playerTwo";

    MoveValidator testGame;

    //PLAYER 1 is red_LOWERCASE, PLAYER 2 is blue_UPPERCASE
    testGame.initializeSide(p1,p2);

    string source = "a7";
    string target = "a6";
    bool isValid = testGame.readChessMove(source, target ,p1 );
    EXPECT_EQ(isValid,false);

    //Execute the same move, but with the proper player executing it
    isValid = testGame.readChessMove(source, target ,p2 );
    EXPECT_EQ(isValid,true);

    source = "a2";
    target = "a4";
    isValid = testGame.readChessMove(source, target ,p2 );
    EXPECT_EQ(isValid,false);


    isValid = testGame.readChessMove(source, target ,p1 );
    EXPECT_EQ(isValid,true);


}

//You need to validate this with your own eyes
TEST(MoveValidatorTest, reversePrint){

    std::string p1 = "playerOne";
    std::string p2 = "playerTwo";

    MoveValidator testGame;

    //PLAYER 1 is red_LOWERCASE, PLAYER 2 is blue_UPPERCASE
    testGame.initializeSide(p1,p2);

    string source = "a7";
    string target = "a6";
    bool isValid = testGame.readChessMove(source, target ,p1 );
    EXPECT_EQ(isValid,false);



    source = "a2";
    target = "a4";
    isValid = testGame.readChessMove(source, target );

    source = "g2";
    target = "g4";
    isValid = testGame.readChessMove(source, target );
 //   std::cout << testGame.getBoardView() ;
//    std::cout << testGame.getReverseBoardView();





}

// Queen is RookAndBishop combined so we don't really need to test, since we reuse function/method.

TEST(InvalidInputTest, invalidMoveInput) {
    MoveValidator test;
    std::string start, finish, player;

    start = "12";
    finish = "12";
    player = "tester";
    EXPECT_FALSE(test.readChessMove(start, finish, player));

    start = "a2";
    finish = "12";
    player = "tester";
    EXPECT_FALSE(test.readChessMove(start, finish, player));

    start = "12";
    finish = "a2";
    player = "tester";
    EXPECT_FALSE(test.readChessMove(start, finish, player));
}