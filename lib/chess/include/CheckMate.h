//
// Created by jordan on 30/05/19.
//

#ifndef CHESS_CHECKMATE_H
#define CHESS_CHECKMATE_H


#include <Piece.h>
#include <vector>
#include <memory>

using std::vector;

//A class that determines whether or not a square is under attack and can also determine checkmate.
class CheckMate {

    public:
        CheckMate(const Color playerOne, Color playerTwo); //is used in std::make_unique()
        ~CheckMate();

        void addMove(const ChessCoordinate &enemyPosition, const vector<vector<Piece> > &m_chessBoard);
        const vector<ChessCoordinate>& getAttackers(const Color &color);
        bool isSquareUnderAttack(const ChessCoordinate &position, const Color &friendlyColor, const vector<vector<Piece> > &m_chessBoard) ;


    private:
        struct kingAttackers; //Make this private only this class should know
        std::unique_ptr<kingAttackers> teamAlpha;
        std::unique_ptr<kingAttackers> teamBeta;
        CheckMate();

        void clearEnemies(); //Should be called at the beginning of every move.
        bool isAttackedHorizontally(const ChessCoordinate &start, const Color &friendlyColor, const vector<vector<Piece> > &m_chessBoard) ;
        bool isAttackedVertically(const ChessCoordinate &start, const Color &friendlyColor,   const vector<vector<Piece> > &m_chessBoard) ;
        bool isAttackedDiagonally(const ChessCoordinate &start, const Color &kingColor,   const vector<vector<Piece> > &m_chessBoard) ;
        bool isAttackedByPawn(const ChessCoordinate &start, const Color &kingColor,       const vector<vector<Piece> > &m_chessBoard) ;



};


#endif //CHESS_CHECKMATE_H
