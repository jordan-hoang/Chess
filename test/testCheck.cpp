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

vector<Piece> emptyRowTwo(){
    vector<Piece> tmp;
    for(int i = 0; i < 8; i++){
        tmp.emplace_back( Piece(PieceUnit::NONE, Color::COLORLESS) );
    }

    return tmp;
}

ChessController game(){

    vector<vector<Piece>> a;

    vector<Piece> backRow;
    Color c = Color::BLUE_UPPERCASE;


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
        a.emplace_back(emptyRowTwo());
    }

    vector<Piece> otherRow;
    otherRow.emplace_back(Piece{PieceUnit::ROOK,Color::RED_LOWERCASE});
    otherRow.emplace_back( Piece(PieceUnit::NONE, Color::COLORLESS) );
    otherRow.emplace_back( Piece(PieceUnit::NONE, Color::COLORLESS) );
    otherRow.emplace_back(Piece{PieceUnit::KING,Color::RED_LOWERCASE});
    for(int i = 0; i < 3; i++){
        otherRow.emplace_back( Piece(PieceUnit::NONE, Color::COLORLESS) );
    }

    otherRow.emplace_back(Piece{PieceUnit::ROOK,Color::RED_LOWERCASE});

    a.emplace_back(otherRow);


    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            a[i][j].setCoordinate({i,j});
        }
    }


    ChessController chessGame(a);
    return chessGame;

}

TEST(Horizontal, simpleTest){

    ChessController chessGame = game();

    std::string p1 = "playerOne";
    std::string p2 = "playerTwo";
    std::string input = "";


    input = "h8,h1";
    EXPECT_EQ(chessGame.readInput(input,p1), ChessErrorCode::VALID_MOVE);



    input = "d1,d2";
    EXPECT_EQ(chessGame.readInput(input,p2), ChessErrorCode::VALID_MOVE);


    input = "a8,a2";
    EXPECT_EQ(chessGame.readInput(input,p1), ChessErrorCode::VALID_MOVE);


}


/**
 * Test to see if the king can castle if the direction he is wants to castle has enemies attacking that square
 */
TEST(CASTLING, testPathBlockedTwo){
    //Also test vertical and horizontal attackers
    /*

    vector<vector<Piece>> a;

    vector<Piece> backRow;
    Color c = Color::BLUE_UPPERCASE;


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
        a.emplace_back(emptyRowTwo());
    }

    vector<Piece> otherRow;
    otherRow.emplace_back(Piece{PieceUnit::ROOK,Color::RED_LOWERCASE});
    otherRow.emplace_back( Piece(PieceUnit::NONE, Color::COLORLESS) );
    otherRow.emplace_back( Piece(PieceUnit::NONE, Color::COLORLESS) );
    otherRow.emplace_back(Piece{PieceUnit::KING,Color::RED_LOWERCASE});
    for(int i = 0; i < 3; i++){
        otherRow.emplace_back( Piece(PieceUnit::NONE, Color::COLORLESS) );
    }

    otherRow.emplace_back(Piece{PieceUnit::ROOK,Color::RED_LOWERCASE});

    a.emplace_back(otherRow);

    */

    ChessController chessGame = game();


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



    input = "a8,a3";
    EXPECT_EQ(chessGame.readInput(input,p1), ChessErrorCode::VALID_MOVE);

    input = "a3,a2";
    EXPECT_EQ(chessGame.readInput(input,p1), ChessErrorCode::VALID_MOVE);

    input = "e2,e1";
    EXPECT_EQ(chessGame.readInput(input,p2), ChessErrorCode::VALID_MOVE);




    input = "e1,e2";
    EXPECT_EQ(chessGame.readInput(input,p2), ChessErrorCode::INVALID_KING_MOVE);

    input = "c1,e2";
    EXPECT_EQ(chessGame.readInput(input,p2), ChessErrorCode::VALID_MOVE);


    input = "e1,f1";
    EXPECT_EQ(chessGame.readInput(input,p2), ChessErrorCode::VALID_MOVE);

    input = "f1,f2";
    EXPECT_EQ(chessGame.readInput(input,p2), ChessErrorCode::VALID_MOVE); //another bug found here!!!

    std::cout << chessGame.getBoardView();

    input = "e2,d4";
    EXPECT_EQ(chessGame.readInput(input,p2), ChessErrorCode::INVALID_MOVE);

    std::cout << chessGame.getBoardView();


    //Now we need to test the right side.
    input = "a2,a4";
    EXPECT_EQ(chessGame.readInput(input,p1), ChessErrorCode::VALID_MOVE);

    input = "a4,h4";
    EXPECT_EQ(chessGame.readInput(input,p1), ChessErrorCode::VALID_MOVE);


    input = "e3,g3";
    EXPECT_EQ(chessGame.readInput(input,p2), ChessErrorCode::VALID_MOVE);


    input = "g3,g2";
    EXPECT_EQ(chessGame.readInput(input,p2), ChessErrorCode::VALID_MOVE);

    input = "h4,h2";
    EXPECT_EQ(chessGame.readInput(input,p1), ChessErrorCode::VALID_MOVE);

    input = "g2,g1";
    EXPECT_EQ(chessGame.readInput(input,p2), ChessErrorCode::INVALID_MOVE);

    input = "b1,g6";
    EXPECT_EQ(chessGame.readInput(input,p2), ChessErrorCode::VALID_MOVE);


    input = "e7,f7";
    EXPECT_EQ(chessGame.readInput(input,p1), ChessErrorCode::VALID_MOVE);

    input = "d8,e8";
    EXPECT_EQ(chessGame.readInput(input,p1), ChessErrorCode::VALID_MOVE);


    input = "f7,g7";
    EXPECT_EQ(chessGame.readInput(input,p1), ChessErrorCode::INVALID_MOVE);


    input = "g6,f5";
    EXPECT_EQ(chessGame.readInput(input,p2), ChessErrorCode::VALID_MOVE);

    input = "f7,d7";
    EXPECT_EQ(chessGame.readInput(input,p1), ChessErrorCode::VALID_MOVE);

    input = "f5,e4";
    EXPECT_EQ(chessGame.readInput(input,p2), ChessErrorCode::VALID_MOVE);

    std::cout << chessGame.getBoardView();

    

    input = "e4,c6";
    EXPECT_EQ(chessGame.readInput(input,p2), ChessErrorCode::VALID_MOVE);

    input = "d7,f7";
    EXPECT_EQ(chessGame.readInput(input,p1), ChessErrorCode::INVALID_MOVE);

    input = "c6,d5";
    EXPECT_EQ(chessGame.readInput(input,p2), ChessErrorCode::VALID_MOVE);

    input ="d7,e7";
    EXPECT_EQ(chessGame.readInput(input,p1), ChessErrorCode::VALID_MOVE);

    input = "h2,h3";
    EXPECT_EQ(chessGame.readInput(input,p1), ChessErrorCode::VALID_MOVE);

    input = "h3,e3";
    EXPECT_EQ(chessGame.readInput(input,p1), ChessErrorCode::VALID_MOVE);


    input = "e8,f8";
    EXPECT_EQ(chessGame.readInput(input,p1), ChessErrorCode::VALID_MOVE);

    input = "g2,g3";
    EXPECT_EQ(chessGame.readInput(input,p2), ChessErrorCode::VALID_MOVE);

    input = "g3,e3";
    EXPECT_EQ(chessGame.readInput(input,p2), ChessErrorCode::VALID_MOVE);

    input = "f8,e8";
    EXPECT_EQ(chessGame.readInput(input,p1), ChessErrorCode::VALID_MOVE);

    input = "e7,f7";
    EXPECT_EQ(chessGame.readInput(input,p1), ChessErrorCode::INVALID_MOVE);

    input = "f2,f1";
    EXPECT_EQ(chessGame.readInput(input,p2), ChessErrorCode::VALID_MOVE);

    input = "e3,f3";
    EXPECT_EQ(chessGame.readInput(input,p2), ChessErrorCode::VALID_MOVE);

    input = "e7,f7";
    EXPECT_EQ(chessGame.readInput(input,p1), ChessErrorCode::VALID_MOVE);

    input = "e8,f8";
    EXPECT_EQ(chessGame.readInput(input,p1), ChessErrorCode::VALID_MOVE);


    input = "f1,g1";
    EXPECT_EQ(chessGame.readInput(input,p2), ChessErrorCode::VALID_MOVE);

    input = "g1,f1";
    EXPECT_EQ(chessGame.readInput(input,p2), ChessErrorCode::VALID_MOVE);

    input = "f3,g3";
    EXPECT_EQ(chessGame.readInput(input,p2), ChessErrorCode::INVALID_MOVE);



    /*
     *
     */


}

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



}

*/