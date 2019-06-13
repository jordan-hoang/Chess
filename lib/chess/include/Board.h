//
// Created by jordanhoang on 11/02/19.
//

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <vector>
#include <array>
#include "Piece.h"
#include "MoveRecorder.h"
#include <unordered_map>
#include <sstream>
#include "CheckMate.h"






using std::vector;


//Contains an instance of a game
class Board {
public:
    Board();
    explicit Board(vector<vector<Piece>> &chessBoard); // Pass in your own _chessBoard, used for testing.
    const std::string getBoardView() const;
    const std::string getReverseBoardView() const;
    const vector< vector<Piece> >& getBoard() const;

    Piece& requestPiece(const ChessCoordinate &position);
    const Piece &getPiece(const ChessCoordinate &position) const;
    const PieceUnit requestUnit(const ChessCoordinate &position) const;
    const Color getPieceColor(const ChessCoordinate &position) const;
    const ChessCoordinate& getRedKing() const {return redKing;   };
    const ChessCoordinate& getBlueKing() const {return blueKing; };



    ChessErrorCode movePiece(const ChessCoordinate &start, const ChessCoordinate &finish);
    void undoMove();
    void printListMove();

    const Piece getLastPieceKilled() const;



private:
    vector<vector<Piece> > _chessBoard;
    MoveRecorder recorder;
    std::unique_ptr<CheckMate> checkmate_system;

    ChessCoordinate redKing;
    ChessCoordinate blueKing;

    static void updatePiece(Piece &source, Piece &destination);

    void initializeGame(vector<vector<Piece>> &chessBoard);
    void createBackRank(Color myColor, vector<vector<Piece>> &boardView, int row) ;
    void drawRow(const vector<Piece> &listPieceId, std::stringstream &stream) const;
    void drawRowReverse(const vector<Piece> &listPieceId, std::stringstream &stream) const;

    bool isHorizontalPathClear(const ChessCoordinate &start, const ChessCoordinate &finish) const;
    bool isVerticalPathClear(const ChessCoordinate &start, const ChessCoordinate &finish) const;
    bool isDiagonalPathClear(const ChessCoordinate &start, const ChessCoordinate &finish) const;
    bool isPathClear(const ChessCoordinate &start, const ChessCoordinate &finish) const;


    ChessErrorCode movePieceHelper(const ChessCoordinate &start, const ChessCoordinate &finish);
    ChessErrorCode canKingDodge(const ChessCoordinate &kingCoordinate);
    ChessErrorCode canBlock(const ChessCoordinate &kingCoordinate, const Color &enemyColor, const vector<ChessCoordinate> &enemyLocations); //Delegate this to CheckMate system perhaps???
    ChessErrorCode canEliminate(const ChessCoordinate &kingCoordinate, const Color &enemyColor, const vector<ChessCoordinate> &enemyLocations);


    bool isCheck(const Color &color);
    ChessErrorCode isCheckMate(const Color &enemyColor);


    ChessErrorCode enPassant(const ChessCoordinate &start, const ChessCoordinate &finish) ;
    void promotePawnToQueen(Piece &source, const ChessCoordinate &target);
    ChessErrorCode executeCastle(const ChessCoordinate &start, const ChessCoordinate &finish);

    const static std::unordered_map <PieceUnit, char> PieceLookUp;

};


#endif //CHESS_BOARD_H
