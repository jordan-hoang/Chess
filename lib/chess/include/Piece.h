//
// Created by jordanhoang on 11/02/19.
//


#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#endif //CHESS_PIECE_H



enum Color{ RED_LOWERCASE,BLUE_UPPERCASE,COLORLESS };

enum PieceUnit{
    PAWN,
    BISHOP,
    KNIGHT,
    ROOK,
    KING,
    QUEEN,
    NONE
};

struct ChessCoordinate {
    int row;
    int col;

    bool operator==(const ChessCoordinate a) const {
        return ( row == a.row  && col == a.col );
    }

};

class Piece {
    private:
        PieceUnit pieceId;
        Color pieceColor;
        bool validatePawn(const ChessCoordinate &start, const ChessCoordinate &finish, const Color &target) const;
        bool validateRook(const ChessCoordinate &start, const ChessCoordinate &finish) const;
        bool validateBishop(const ChessCoordinate &start, const ChessCoordinate &finish) const;
        bool validateKnight(const ChessCoordinate &start, const ChessCoordinate &finish) const;
        bool validateKing(const ChessCoordinate &start, const ChessCoordinate &finish) const ;
        bool validateQueen(const ChessCoordinate &start, const ChessCoordinate &finish) const;

    public:
        const PieceUnit getPieceUnit() const { return pieceId; };
        const Color getColor() const { return pieceColor; };
        bool checkMovementIsValid(const ChessCoordinate &start, const ChessCoordinate &finish,const Color &targetColor) const   ;
        void updatePiece(Piece &source, Piece &destination);
        void setPiece(PieceUnit pieceUnit, Color color);


    Piece();
    Piece(PieceUnit unit, Color color) :
            pieceId(unit), pieceColor(color){}

};

