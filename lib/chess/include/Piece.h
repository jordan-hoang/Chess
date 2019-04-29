//
// Created by jordanhoang on 11/02/19.
//


#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#endif //CHESS_PIECE_H

/**Chess error codes,
 * INVALID_MOVE means that piece can't move in that way
 * INVALID_INPUT - Bad input from user
 * INVALID_PIECE - Attempting to move a piece that isn't yours, moving a piece that is "NONE"
 */
enum class ChessErrorCode {INVALID_MOVE, INVALID_INPUT, INVALID_PIECE, VALID_MOVE, CASTLE, INVALID_CASTLE, INVALID_KING_MOVE};

/**
 * The color of the piece
 */
enum class Color{ RED_LOWERCASE,BLUE_UPPERCASE,COLORLESS };

/**
 * The unit of a piece
 */
enum class PieceUnit{
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

    bool isValid(){
        if(row < 0 || row >= 8){
            return false;
        }
        if(col < 0 || col >= 8 ){
            return false;
        }
        return true;
    }


};

class Piece {
    private:
        PieceUnit pieceId;
        Color pieceColor;
        bool hasMoved = false;

        enum ChessErrorCode validatePawn(const ChessCoordinate &start, const ChessCoordinate &finish, const Color &target) const;
        enum ChessErrorCode validateRook(const ChessCoordinate &start, const ChessCoordinate &finish) const;
        enum ChessErrorCode validateBishop(const ChessCoordinate &start, const ChessCoordinate &finish) const;
        enum ChessErrorCode validateKnight(const ChessCoordinate &start, const ChessCoordinate &finish) const;
        enum ChessErrorCode validateKing(const ChessCoordinate &start, const ChessCoordinate &finish) const ;
        enum ChessErrorCode validateQueen(const ChessCoordinate &start, const ChessCoordinate &finish) const;

    public:
        const enum PieceUnit getPieceUnit() const { return pieceId; };
        const enum Color getColor() const { return pieceColor; };
        const bool getHasMoved() const { return hasMoved; } ;

        enum ChessErrorCode checkMovementIsValid(const ChessCoordinate &start, const ChessCoordinate &finish,const Color &targetColor) const   ;
        static void updatePiece(Piece &source, Piece &destination);
        void setPiece(PieceUnit pieceUnit, Color color);


    Piece();
    Piece(PieceUnit unit, Color color) :
            pieceId(unit), pieceColor(color),hasMoved(false){}

};

