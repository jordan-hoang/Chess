//
// Created by jordanhoang on 11/02/19.
//


#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#endif //CHESS_PIECE_H

enum Color{ RED,BLUE,COLORLESS };

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
};



class Piece {
    private:
        PieceUnit pieceId;
        Color pieceColor;
        bool validatePawn(const ChessCoordinate &start, const ChessCoordinate &finish);
        void updatePiece(Piece &source, Piece &destination);

    public:
        PieceUnit getPieceUnit() { return pieceId; };
        Color getColor(){ return pieceColor; };
        bool checkMovementIsValid(const ChessCoordinate &start, const ChessCoordinate &finish);






        //Color getColor(return pieceColor);

        Piece(PieceUnit unit, Color color) :
            pieceId(unit), pieceColor(color){}

};

