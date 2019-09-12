
//Tests the chessGame itself

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ChessController.h"
#include "Board.h"

using std::string;

//first parameter is name of grouping, 2nd parameter is the name of the test
//Test's the pawns in the chess game
TEST(BoardTest,  pawn){

    ChessController move;
    std::string input = "a2";
    std::string target= "a3";

    ChessErrorCode isValid = move.executeMove(input, target) ;
    EXPECT_EQ(isValid, ChessErrorCode::VALID_MOVE);

    //Move red pawn from a3 to a5 move is invalid cannot jump 2 squares
    input = "a3";
    target = "a5";
    isValid = move.executeMove(input, target);
    EXPECT_EQ(isValid, ChessErrorCode::INVALID_MOVE);

    //Move blue pawn in 'a' column down valid
    input = "a7";
    target = "a6";
    isValid = move.executeMove(input, target);
    EXPECT_EQ(isValid, ChessErrorCode::VALID_MOVE);

    input = "a3";
    target = "a4";
    isValid = move.executeMove(input, target);
    EXPECT_EQ(isValid, ChessErrorCode::VALID_MOVE);

    input = "a4";
    target = "a5";
    isValid = move.executeMove(input, target);
    EXPECT_EQ(isValid, ChessErrorCode::VALID_MOVE);

    //Invalid move pawns can only kill diagonally
    input = "a5";
    target = "a6";
    isValid = move.executeMove(input, target);
    EXPECT_EQ(isValid, ChessErrorCode::INVALID_MOVE);

    input = "h7";
    target = "h5";
    isValid = move.executeMove(input, target);
    EXPECT_EQ(ChessErrorCode::VALID_MOVE,isValid);


    input = "h2";
    target = "h4";
    isValid = move.executeMove(input, target);
    EXPECT_EQ(ChessErrorCode::VALID_MOVE,isValid);

    //Now move the attempt to move the pawns directly on top of each other, should be invalid.
    input = "h4";
    target = "h5";
    isValid = move.executeMove(input, target);
    EXPECT_EQ(ChessErrorCode::INVALID_MOVE, isValid);


    input = "h5";
    target = "h4";
    isValid = move.executeMove(input, target);
    EXPECT_EQ(ChessErrorCode::INVALID_MOVE, isValid);

}

TEST(BoardTest, pawnDiagonal){

    ChessController move;
    //move.getBoardView();

    std::string moveFrom = "a2";
    std::string moveTo = "a4";
    move.executeMove(moveFrom, moveTo);

    moveFrom = "b7";
    moveTo = "b5";
    move.executeMove(moveFrom, moveTo);

    //See if red can kill blue diagonally.
    moveFrom = "a4";
    moveTo = "b5";
    ChessErrorCode isValid = move.executeMove(moveFrom, moveTo);
    EXPECT_EQ(ChessErrorCode::VALID_MOVE,isValid);

    moveFrom = "a7";
    moveTo = "a6";
    move.executeMove(moveFrom, moveTo);

    //move.getBoardView();

    moveFrom = "b5";
    moveTo = "a6";
    isValid = move.executeMove(moveFrom, moveTo);

    EXPECT_EQ(isValid,ChessErrorCode::VALID_MOVE);

    //move.getBoardView();

    //Now testing the blue side
    moveFrom = "b2";
    moveTo = "b4";
    move.executeMove(moveFrom, moveTo);

    moveFrom = "c7";
    moveTo = "c5";
    move.executeMove(moveFrom, moveTo);
    // move.getBoardView();

    moveFrom = "c5";
    moveTo = "b4";
    isValid = move.executeMove(moveFrom, moveTo);
    EXPECT_EQ(ChessErrorCode::VALID_MOVE, isValid);
    // move.getBoardView();

    moveFrom = "c2";
    moveTo = "c3";
    move.executeMove(moveFrom, moveTo);

    //move.getBoardView();

    moveFrom = "b4";
    moveTo = "c3";
    isValid = move.executeMove(moveFrom, moveTo);
    EXPECT_EQ(ChessErrorCode::VALID_MOVE,isValid);

}

TEST(BoardTest,pawnDiagonalTwo){

    ChessController move;
    std::string input = "c2";
    std::string target = "c4";
    move.executeMove(input, target);

    input = "d7";
    target = "d5";
    move.executeMove(input, target);

    // move.getBoardView();

    //Illegal move pawn cannot move in this direction.
    input = "d5,e4";
    target = "e4";
    ChessErrorCode isValid = move.executeMove(input, target);
    //move.getBoardView();
    EXPECT_EQ(isValid,ChessErrorCode::INVALID_INPUT);

    input = "d5";
    target = "e6";
    isValid = move.executeMove(input, target);
    EXPECT_EQ(isValid,ChessErrorCode::INVALID_MOVE);

}

//To see where the pieces are use move.getBoardView()
TEST(BoardTest, Rook){


    ChessController move;

    string input = "a8";
    string target = "a7";
    ChessErrorCode isValid = move.executeMove(input, target);



    EXPECT_EQ(ChessErrorCode::INVALID_PIECE, isValid);

    input = "a7";
    target = "a5";
    move.executeMove(input, target);

    input = "a8";
    target = "a6";
    isValid = move.executeMove(input, target);
    EXPECT_EQ(isValid,ChessErrorCode::VALID_MOVE);

    input = "a6";
    target = "h6";
    isValid = move.executeMove(input, target);
    EXPECT_EQ(ChessErrorCode::VALID_MOVE,isValid);


    input = "h6";
    target = "h2";
    isValid = move.executeMove(input, target);
    EXPECT_EQ(isValid,ChessErrorCode::VALID_MOVE);

    //Now attempt to have rook attack piece behind it.
    input = "h2";
    target = "f2";
    isValid = move.executeMove(input, target);

    // move.getBoardView();
    EXPECT_EQ(ChessErrorCode::INVALID_MOVE,isValid);

    //Now test if the red rook can "Illegaly go through the blue rook. If you want to see the board do move.getBoardView//
    input = "h1";
    target = "h4";
    isValid = move.executeMove(input, target);
    EXPECT_EQ(ChessErrorCode::INVALID_MOVE,isValid);

    input = "h2";
    target = "g2";
    isValid = move.executeMove(input, target);
    EXPECT_EQ(ChessErrorCode::VALID_MOVE,isValid);


    input = "h1";
    target = "h2";
    isValid = move.executeMove(input, target);
    EXPECT_EQ(ChessErrorCode::VALID_MOVE,isValid);

    input = "g7";
    target = "g6";
    isValid = move.executeMove(input, target);

    //Attempt to go through blue pawn
    input = "g2";
    target = "g6";
    isValid = move.executeMove(input, target);
    EXPECT_EQ(ChessErrorCode::INVALID_PIECE,isValid);


}

TEST(BoardTest, knight){
    ChessController move;
    //TESTING ALL THE POSSIBLE MOVES OF THE KNIGHT

    string input = "b1";
    string target = "c3";
    ChessErrorCode isValid = move.executeMove(input, target);
    EXPECT_EQ(ChessErrorCode::VALID_MOVE,isValid);

    input = "c3";
    target = "b1";
    isValid = move.executeMove(input, target);
    EXPECT_EQ(ChessErrorCode::VALID_MOVE,isValid);

    input = "b1";
    target = "a3";
    isValid = move.executeMove(input, target);
    EXPECT_EQ(ChessErrorCode::VALID_MOVE,isValid);

    input = "a3";
    target = "b1";
    isValid = move.executeMove(input, target);
    EXPECT_EQ(ChessErrorCode::VALID_MOVE,isValid);

    //Duplicate move
    input = "b1";
    target = "a3";
    isValid = move.executeMove(input, target);
    EXPECT_EQ(ChessErrorCode::VALID_MOVE,isValid);


    input = "a3";
    target = "c4";
    isValid = move.executeMove(input, target);
    EXPECT_EQ(ChessErrorCode::VALID_MOVE,isValid);

    input = "c4";
    target = "e3";
    isValid = move.executeMove(input, target);
    EXPECT_EQ(ChessErrorCode::VALID_MOVE,isValid);


    input = "e3";
    target = "g4";
    isValid = move.executeMove(input, target);
    EXPECT_EQ(isValid,ChessErrorCode::VALID_MOVE);
    //move.getBoardView();

    input = "g4";
    target = "e3";
    isValid = move.executeMove(input, target);
    EXPECT_EQ(isValid,ChessErrorCode::VALID_MOVE);

    input = "e3";
    target = "c4";
    isValid = move.executeMove(input, target);
    EXPECT_EQ(isValid,ChessErrorCode::VALID_MOVE);

}


TEST(BoardTest, testBishop){


    //Code should have been tested this way to begin with, but too lazy to rewrite all the methods above.
    Board bishop;

    bishop.movePiece({1,1},{2,1});
    PieceUnit  tmp = bishop.requestUnit({2,1});
    EXPECT_EQ(tmp,PieceUnit::PAWN);

    bishop.movePiece({0,2},{2,0});
    EXPECT_EQ(bishop.requestUnit({2,0}),PieceUnit::BISHOP);


    bishop.movePiece({2,0},{7,4});
    EXPECT_EQ(bishop.requestUnit({2,0}), PieceUnit::BISHOP);


    bishop.movePiece({2,0},{7,5});
    EXPECT_EQ(bishop.requestUnit({2,0}), PieceUnit::BISHOP); //Move should have failed bishop cannot go through units.

    bishop.movePiece({2,0},{6,4});
    EXPECT_EQ(bishop.requestUnit({2,0}),PieceUnit::NONE);


}


TEST(BoardTest, testPromotionAndKillKing){

    Board board;

    board.movePiece({1,1},{3,1});
    board.movePiece({3,1},{4,1});
    board.movePiece({4,1},{5,1});
    board.movePiece({5,1},{6,2});
    board.movePiece({6,2},{7,3});


    EXPECT_EQ(board.requestUnit({7,3}), PieceUnit::QUEEN );

}


TEST(MoveValidatorTest, testTurn){

    std::string p1 = "playerOne";
    std::string p2 = "playerTwo";

    ChessController testGame;

    //PLAYER 1 is red_LOWERCASE, PLAYER 2 is blue_UPPERCASE
    testGame.initializeSide(p1,p2);

    string source = "a7";
    string target = "a6";
    ChessErrorCode isValid = testGame.executeMove(source, target, p1);
    EXPECT_EQ(isValid,ChessErrorCode::INVALID_PIECE);

    //Execute the same move, but with the proper player executing it
    isValid = testGame.executeMove(source, target, p2);
    EXPECT_EQ(isValid,ChessErrorCode::VALID_MOVE);

    source = "a2";
    target = "a4";
    isValid = testGame.executeMove(source, target, p2);
    EXPECT_EQ(isValid,ChessErrorCode::INVALID_PIECE);


    isValid = testGame.executeMove(source, target, p1);
    EXPECT_EQ(isValid,ChessErrorCode::VALID_MOVE);


}

//You need to validate this with your own eyes
TEST(MoveValidatorTest, reversePrint){

    std::string p1 = "playerOne";
    std::string p2 = "playerTwo";

    ChessController testGame;

    //PLAYER 1 is red_LOWERCASE, PLAYER 2 is blue_UPPERCASE
    testGame.initializeSide(p1,p2);

    string source = "a7";
    string target = "a6";
    ChessErrorCode isValid = testGame.executeMove(source, target, p1);
    EXPECT_EQ(isValid,ChessErrorCode::INVALID_PIECE); //????????



    source = "a2";
    target = "a4";
    isValid = testGame.executeMove(source, target);

    source = "g2";
    target = "g4";
    isValid = testGame.executeMove(source, target);
    //   std::cout << testGame.getBoardView() ;
//    std::cout << testGame.getReverseBoardView();





}

// Queen is RookAndBishop combined so we don't really need to test, since we reuse function/method.

TEST(InvalidInputTest, invalidMoveInput) {
    ChessController test;
    std::string start, finish, player;

    start = "12";
    finish = "12";
    player = "tester";
//    EXPECT_FALSE(test.executeMove(start, finish, player));

    start = "a2";
    finish = "12";
    player = "tester";
 //   EXPECT_FALSE(test.executeMove(start, finish, player));

    start = "12";
    finish = "a2";
    player = "tester";
   // EXPECT_FALSE(test.executeMove(start, finish, player));
}


void setUpCastling(ChessController &a){
    std::string p1 = "playerOne";
    std::string p2 = "playerTwo";

    std::string move = "a2,a4";
    a.readInput(move,p1);
    //std::cout << a.getBoardView();

    move = "a7,a5";
    a.readInput(move,p2);
    //std::cout << a.getBoardView();

    move = "b1,c3";
    a.readInput(move,p1);
    //std::cout << a.getBoardView();


    move = "d7,d6";
    a.readInput(move,p2);
    //std::cout << a.getBoardView();


    move = "d7,d6";
    a.readInput(move,p2);
    //std::cout << a.getBoardView();


    move = "d2,d3";
    a.readInput(move,p1);
    //std::cout << a.getBoardView();


    move = "c8,e6";
    a.readInput(move,p2);
    //std::cout << a.getBoardView();


    move = "c1,e3";
    a.readInput(move,p1);
    //std::cout << a.getBoardView();


    move = "d8,d7";
    a.readInput(move,p2);
    //std::cout << a.getBoardView();


    move = "d1,d2";
    a.readInput(move,p1);
    //std::cout << a.getBoardView();


    move = "b8,c6";
    a.readInput(move,p2);
    //std::cout << a.getBoardView();

}

/**
 * Test a castle
 */
TEST(CASTLING, testCastle){

    ChessController a;

    std::string p1 = "playerOne";
    std::string p2 = "playerTwo";
    std::string move;

    setUpCastling(a);

    //MOVED ROOK, EXECUTED CASTLE HERE!
    move = "e1,c1";
    EXPECT_EQ(a.readInput(move,p1), ChessErrorCode::VALID_MOVE);

    //MOVED ROOK!
    move = "e8,c8";
    EXPECT_EQ(a.readInput(move,p2), ChessErrorCode::VALID_MOVE);

}

/**
 * Test if the game will let you castle if the king has moved.
 */
TEST(CASTLING, movedKing){
    ChessController a;

    std::string p1 = "playerOne";
    std::string p2 = "playerTwo";
    std::string move;

    setUpCastling(a);

    move = "e1,d1";
    EXPECT_EQ(a.readInput(move,p1), ChessErrorCode::VALID_MOVE);

    move = "d1,e1";
    EXPECT_EQ(a.readInput(move,p1), ChessErrorCode::VALID_MOVE);

    move = "e1,c1";
    EXPECT_EQ(a.readInput(move,p1), ChessErrorCode::INVALID_MOVE);


}

/**
 * Test if game lets you castle if you have moved the rook. Castle should not be allowed to work
 */
TEST(CASTLING, testKing){
    ChessController a;
    std::string p1 = "playerOne";
    std::string p2 = "playerTwo";

    std::string move = "a2,a4";
    EXPECT_EQ(a.readInput(move,p1), ChessErrorCode::VALID_MOVE);
    //std::cout << a.getBoardView();

    move = "a7,a5";
    EXPECT_EQ(a.readInput(move,p2), ChessErrorCode::VALID_MOVE);
    //std::cout << a.getBoardView();

    //MOVED ROOK!
    move = "a1,a3";
    a.readInput(move,p1);

    //MOVED ROOK!
    move = "a8,a6";
    a.readInput(move,p2);



    setUpCastling(a);

    ///// Entire row has been moved! ///// Now we can finally castle, but first we must move rook back. (Castle should
    ///// fail since we moved the rook).

    //MOVED ROOK!
    move = "a3,a1";
    a.readInput(move,p1);

    //MOVED ROOK!
    move = "a6,a8";
    a.readInput(move,p2);


    //Invalid move because the rook has already moved.
    move = "e1,c1";
    EXPECT_EQ(a.readInput(move,p1), ChessErrorCode::INVALID_CASTLE);
    //std::cout << a.getBoardView();

    move = "e8,c8";
    EXPECT_EQ(a.readInput(move,p2), ChessErrorCode::INVALID_CASTLE);
    // std::cout << a.getBoardView();


}


vector<Piece> emptyRow(){
    vector<Piece> tmp;

    for(int i = 0; i < 8; i++){
        tmp.emplace_back( Piece(PieceUnit::NONE, Color::COLORLESS) );
    }

    return tmp;
}

/**
 * Test to see if the king can castle if the direction he is wants to castle has enemies attacking that square
 */
TEST(CASTLING, testPathBlocked){
    //Also test vertical and horizontal attackers


    vector<vector<Piece>> a;

    vector<Piece> backRow;
    Color c = Color::WHITE;


    backRow.emplace_back(Piece{PieceUnit::ROOK,c});
    backRow.emplace_back(Piece{PieceUnit::BISHOP,c});
    backRow.emplace_back(Piece{PieceUnit::KNIGHT,c});
    backRow.emplace_back(Piece{PieceUnit::KING, c});
    backRow.emplace_back(Piece{PieceUnit::ROOK,c});

    c = Color::COLORLESS;
    backRow.emplace_back(Piece{PieceUnit::NONE,c});
    backRow.emplace_back(Piece{PieceUnit::NONE,c});
    backRow.emplace_back(Piece{PieceUnit::NONE,c});

    a.push_back(backRow);

    for(int i = 0; i < 6; i++){
        a.emplace_back(emptyRow());
    }

    vector<Piece> otherRow;
    otherRow.emplace_back(Piece{PieceUnit::ROOK,Color::BLACK});
    otherRow.emplace_back( Piece(PieceUnit::NONE, Color::COLORLESS) );
    otherRow.emplace_back( Piece(PieceUnit::NONE, Color::COLORLESS) );
    otherRow.emplace_back(Piece{PieceUnit::KING,Color::BLACK});
    for(int i = 0; i < 3; i++){
        otherRow.emplace_back( Piece(PieceUnit::NONE, Color::COLORLESS) );
    }

    otherRow.emplace_back(Piece{PieceUnit::ROOK,Color::BLACK});

    a.emplace_back(otherRow);



    ChessController chessGame(a);

  //  std::cout << chessGame.getBoardView();

    std::string input = "d8,f8";
    std::string p1 = "playerOne";
    std::string p2 = "playerTwo";



    //User should not be able to castle since the path is under attak by the enemy rook.
    EXPECT_EQ(chessGame.readInput(input,p1),ChessErrorCode::INVALID_CASTLE);

    input="d8,e8";
    EXPECT_EQ(chessGame.readInput(input,p1),ChessErrorCode::INVALID_KING_MOVE);

    input="h8,e8";
    EXPECT_EQ(chessGame.readInput(input,p1),ChessErrorCode::VALID_MOVE);


    input="e8,e7";
    EXPECT_EQ(chessGame.readInput(input,p1),ChessErrorCode::VALID_MOVE);



    EXPECT_EQ(chessGame.readInput(input,p1),ChessErrorCode::INVALID_PIECE); //Somehow this causes crash/error to happen


    input="d1,e2";
    EXPECT_EQ(chessGame.readInput(input,p2),ChessErrorCode::INVALID_KING_MOVE);

    input="e1,e3";
    EXPECT_EQ(chessGame.readInput(input,p2),ChessErrorCode::VALID_MOVE);

    input="d1,e1";
    EXPECT_EQ(chessGame.readInput(input,p2),ChessErrorCode::VALID_MOVE);

    input="e1,e2";
    EXPECT_EQ(chessGame.readInput(input,p2),ChessErrorCode::VALID_MOVE);

    input = "a8,a2";
    EXPECT_EQ(chessGame.readInput(input,p1), ChessErrorCode::VALID_MOVE);

    input = "a1,a2";
    EXPECT_EQ(chessGame.readInput(input,p2), ChessErrorCode::VALID_MOVE);


    input = "a2,h2";
    EXPECT_EQ(chessGame.readInput(input,p2), ChessErrorCode::INVALID_MOVE);


}

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



    input = "c5,d6";
    EXPECT_EQ(game.readInput(input,p2),ChessErrorCode::VALID_MOVE);

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


}


TEST(CoordinateInitialization, coordiantePiece){

    Board a;
    a.movePiece({1,1},{2,1});

    const vector< vector<Piece> > handle = a.getBoard();

    for(int i = 0; i < 8 ; i++){
        for(int col = 0 ; col < 8; col++){
            const Piece &a = handle.at(i).at(col);
            ChessCoordinate c{i,col};
            EXPECT_EQ(a.getCoordinate(), c );
        }
    }

}

TEST(TestUndoMove, undoMove){

    ChessController a;
    std::string input ="a2,a4";
    std::string p1 = "playerOne";
    std::string p2 = "playerTwo";

    EXPECT_EQ(a.readInput(input,p1), ChessErrorCode::VALID_MOVE);

    //std::cout << a.getBoardView();
    a.undoMove();
    //std::cout << a.getBoardView();
    a.undoMove();
    //std::cout << a.getBoardView();

    EXPECT_EQ(a.readInput(input,p1), ChessErrorCode::VALID_MOVE);

    input = "a4,a5";
    EXPECT_EQ(a.readInput(input,p1), ChessErrorCode::VALID_MOVE);
   // std::cout << a.getBoardView();


    input = "a5,a6";
    EXPECT_EQ(a.readInput(input,p1), ChessErrorCode::VALID_MOVE);
    //std::cout << a.getBoardView();

    input = "a6,b7";
    EXPECT_EQ(a.readInput(input,p1), ChessErrorCode::VALID_MOVE);
    //std::cout << a.getBoardView();

    a.undoMove();

  //  input = "a6,b7";
  //  EXPECT_EQ(a.readInput(input,p1), ChessErrorCode::VALID_MOVE);
  //  std::cout << a.getBoardView();

}

TEST(TestUndoMove, undoKnight){
    ChessController a;
    std::string input ="b1,c3";
    std::string p1 = "playerOne";
    std::string p2 = "playerTwo";

    EXPECT_EQ(a.readInput(input,p1), ChessErrorCode::VALID_MOVE);

   // std::cout << a.getBoardView();
    a.undoMove();
   // std::cout << a.getBoardView();


}

TEST(TestUndoMove, undoCastle){
    ChessController a;
    std::string input ="b1,c3";
    std::string p1 = "playerOne";
    std::string p2 = "playerTwo";

    a.readInput(input,p1);
  //  std::cout << a.getBoardView();

    input = "a2,a4";
    a.readInput(input,p1);




    input = "b2,b4";
    a.readInput(input,p1);

    input = "c3,b2";
    a.readInput(input,p1);


    input = "c1,a3";
    a.readInput(input,p1);

    input = "d1,b1";
    a.readInput(input,p1);

    input = "b1,b2";
    a.readInput(input,p1);

    input = "e1,c1";

    EXPECT_EQ(a.readInput(input,p1), ChessErrorCode::VALID_MOVE);

    a.undoMove();

    EXPECT_EQ(a.readInput(input,p1), ChessErrorCode::VALID_MOVE);

    input = "h2,h4";
    a.readInput(input,p1);
    a.undoMove();

}

TEST(TestUndoMove, enPassant){
    ChessController a;
    std::string input ="b2,b4";
    std::string p1 = "playerOne";
    std::string p2 = "playerTwo";

    a.readInput(input,p1);

    input = "b4,b5";
    a.readInput(input,p1);

    input = "c7,c5";
    a.readInput(input,p2);

    input = "b5,c6";
    EXPECT_EQ(a.readInput(input,p1), ChessErrorCode::VALID_MOVE);
    a.undoMove();
    EXPECT_EQ(a.readInput(input,p1), ChessErrorCode::VALID_MOVE);

}

TEST(TestKingTracking, track){

    Board a;
    ChessCoordinate b = a.getBlueKing();

    ChessCoordinate tmp = {7,4};
    EXPECT_EQ( b, tmp );

    ChessCoordinate start =  {6,4} ;
    ChessCoordinate finish = {4,4};
    a.movePiece(start, finish);


    start = {7,4};
    finish = {6,4};
    a.movePiece(start,finish);


    tmp = {6,4};
    EXPECT_EQ(a.getBlueKing(), tmp);

    a.undoMove();

    tmp = {7,4};
    EXPECT_EQ(tmp, a.getBlueKing());

    //Since we undid the move we also undid the fact that the king ever moved.
    start = {7 ,5};
    finish = {5,3};

    a.movePiece(start, finish);

    start = {7,6};
    finish = {5,5};
    a.movePiece(start,finish);

    start = {7,4};
    finish = {7,6};
    a.movePiece(start, finish);

    tmp = {7,6};
    EXPECT_EQ( a.getBlueKing(), tmp);

    a.undoMove();

    tmp = {7,4};
    EXPECT_EQ(a.getBlueKing(), tmp);


}
