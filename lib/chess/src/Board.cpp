//
// Created by jordanhoang on 11/02/19.
//

#include "Board.h"
#include <vector>
#include <iostream>
#include <cassert>
#include <algorithm>



/**
 * Helper method for initializeGame
 * @param color - Chess piece color
 * @param boardView - The board itself. Called chessBoard.
 */
void Board::createBackRank(Color color, vector<vector<Piece>> &boardView,int row) {

    vector<Piece> tmp;
    tmp.reserve(8);

        tmp.emplace_back(Piece{PieceUnit::ROOK,color, {row,0}   });
        tmp.emplace_back(Piece{PieceUnit::KNIGHT,color, {row,1} });
        tmp.emplace_back(Piece{PieceUnit::BISHOP,color, {row,2} });

        tmp.emplace_back(Piece{PieceUnit::QUEEN,color, {row,3} });
        tmp.emplace_back(Piece{PieceUnit::KING,color, {row,4}  });

        tmp.emplace_back(Piece{PieceUnit::BISHOP,color, {row,5} });
        tmp.emplace_back(Piece{PieceUnit::KNIGHT,color, {row,6} });
        tmp.emplace_back(Piece{PieceUnit::ROOK,color, {row,7}   });

        boardView.push_back(tmp);
}
/**
 * Initializes the chess game by setting all the pieces.
 * @param chessBoard
 */
void Board::initializeGame(vector<vector<Piece>> &chessBoard) {


    //Doing red side
    createBackRank(Color::RED_LOWERCASE,chessBoard, 0);

    std::vector<Piece> blackPawn;
    for(int col = 0; col < 8 ; ++col){
        blackPawn.emplace_back( Piece{PieceUnit::PAWN, Color::RED_LOWERCASE, {1,col} }  );
    }
    chessBoard.push_back(blackPawn);


    for (int row = 2; row < 6; ++row) {
        std::vector<Piece> tmp;
        for (int col = 0; col < 8; ++col) {
            tmp.emplace_back(Piece{PieceUnit::NONE, Color::COLORLESS, {row,col} } );
        }
        chessBoard.push_back(tmp);
    }

    //Doing blue side
    std::vector<Piece> whitePawn;
    for(int col = 0 ; col < 8; ++col){
        whitePawn.emplace_back(Piece{PieceUnit::PAWN, Color::BLUE_UPPERCASE, {6,col}});
    }
    chessBoard.push_back(whitePawn);
    createBackRank(Color::BLUE_UPPERCASE,chessBoard,7);

}
/**
 * Draw's a row of chess pieces to a stringstream.
 */
void Board::drawRow(const vector<Piece> &listPieceId, std::stringstream &stream) const {
    for(Piece iter: listPieceId){
        auto search = PieceLookUp.find( iter.getPieceUnit() );

        //Since printing out color doesn't work, we will make 1 side lower case
        switch(iter.getColor())
        {
            case Color::RED_LOWERCASE:
                stream  << (char)tolower(search->second);
                break;
            case Color::BLUE_UPPERCASE:
                stream << search->second;
                break;
            default:
                stream << search->second ;
        }

    }
    stream << '\n';
}
/**
 * Draw's a row backward. Helper method for getReverseBoardView().
 * @param listPieceId - A row of chess pieces.
 * @param stream
 */
void Board::drawRowReverse(const vector<Piece> &listPieceId, std::stringstream &stream) const {

    for(int i = 7; i >= 0 ; i--){
        auto iter = listPieceId.at(i);
        auto search = PieceLookUp.find(iter.getPieceUnit());
        //Since printing out color doesn't work, we will make 1 side lower case
        switch(iter.getColor())
        {
            case Color::RED_LOWERCASE:
                stream  << (char)tolower(search->second);
                break;
            case Color::BLUE_UPPERCASE:
                stream << search->second;
                break;
            default:
                stream << search->second ;
        }
    }
    stream << '\n';



}



/**
 * @param start
 * @param finish
 * @return True if the path is clear (no units were found).
 *
 */
bool Board::isHorizontalPathClear(const ChessCoordinate &start, const ChessCoordinate &finish) const {

    const vector<Piece> &handle = _chessBoard.at(start.row);
    const auto iterBegin = handle.begin() + std::min(start.col,finish.col ) + 1 ;
    const auto iterEnd = handle.begin() + std::max(start.col,finish.col) ;

    //We are only searching w/e the path specifies
    const auto result = std::find_if(iterBegin,iterEnd,
            [&](auto i) { return i.getPieceUnit() != PieceUnit ::NONE ;} );


    //If enum NONE was not found result will be set to iterEnd.
    return (result == iterEnd);
}
/**
 * Determines w/e the path is free vertically
 * @param start
 * @param finish
 */
bool Board::isVerticalPathClear(const ChessCoordinate &start, const ChessCoordinate &finish) const {

    int begin = std::min(start.row,finish.row);
    int end = std::max(start.row,finish.row);

    // + 1 for the space in front of it
    for(int i = begin + 1; i < end ; ++i){
        if(requestUnit({i,start.col}) != PieceUnit::NONE ){
            return false;
        }
    }
    return true;

}
//2 slopes + or - and 2 ways to traverse them so 4 ways in total....
bool Board::isDiagonalPathClear(const ChessCoordinate &start, const ChessCoordinate &finish) const{

    // A bishop's diagonal can be defined by y = x or y = -x
    int endIter = abs(finish.col - start.col);

    int curX = start.col;
    int curY = start.row;

    int changeX = ( (finish.col - start.col) > 0 ) ? 1 : -1;
    int changeY = ( (finish.row - start.row) > 0 ) ? 1 : -1;

    for(int i = 0; i < endIter - 1; ++i){
        curX += changeX;
        curY += changeY;
        if(requestUnit({curY,curX}) != PieceUnit::NONE   ){
            return false;
        }
    }

    return true;
}
/**
 * A method that checks to see w/e the distance between 2 path's is clear.
 * You can only do vertical, horizontal, or diagonal only lines.
 *
 * Ex. (2,4) to (3,4) // (3,5) to (3,7) // or (3,3) to (5,5)
 *
 * @param start - Starting coordinate
 * @param finish - Finishing coordinate
 * @return
 */
bool Board::isPathClear(const ChessCoordinate &start, const ChessCoordinate &finish) const {

    int diffRow = abs( finish.row - start.row);
    int diffCol = abs( finish.col - start.col);

    // You are moving horizontally
    if( start.row == finish.row && start.col != finish.col ){
        return isHorizontalPathClear(start, finish);
    }

        // You are moving vertical
    else if( start.row != finish.row && start.col == finish.col ) {
        return isVerticalPathClear(start, finish);
    }

    else if( diffRow == diffCol ){
        return isDiagonalPathClear(start, finish);
    }


    return false;
}



void Board::promotePawnToQueen(Piece &source, const ChessCoordinate &target){
    if( (target.row == 0 || target.row == 7) && (source.getPieceUnit() == PieceUnit::PAWN) ){
        source.setPiece(PieceUnit::QUEEN,source.getColor());
    }
}

ChessErrorCode Board::executeCastle(const ChessCoordinate &start, const ChessCoordinate &finish){

    // We also need to check if the path is clear here

     //INPUT THE CORRECT COORDINATES

    int dirSquare  = (finish.col - start.col > 0 ) ? 1 : -1;

    bool isAttacked = checkmate_system->isSquareUnderAttack({start.row, start.col + dirSquare}, getPieceColor(start), getBoard());
    if(isAttacked){
        return ChessErrorCode::INVALID_CASTLE;
    }
    isAttacked =  checkmate_system->isSquareUnderAttack({start.row, start.col + dirSquare*2}, getPieceColor(start), getBoard());
    if(isAttacked){
        return ChessErrorCode::INVALID_CASTLE;
    }


    int direction = start.col - finish.col;
    int rookRow = 0;
    rookRow = (direction > 0) ? 1 : -1;
    int rookCol = (rookRow == 1) ? 0 : 7;

    ChessCoordinate rookStart{finish.row,rookCol};
    ChessCoordinate rookFinish{finish.row,finish.col + rookRow};

    Piece &rookPiece = requestPiece({finish.row,rookCol});
    Piece &endSpot = requestPiece({finish.row,finish.col + rookRow});


    if(rookPiece.getHasMoved() || rookPiece.getPieceUnit() != PieceUnit::ROOK){
        return ChessErrorCode::INVALID_CASTLE;
    }


     //THE MOVE IS VALID SO MOVE THE PIECES/UPDATE THEIR POSITIONS.
    Piece &sourcePiece = requestPiece(start);
    Piece &targetPiece = requestPiece(finish);
    updatePiece(sourcePiece, targetPiece);
    updatePiece(rookPiece,endSpot);




    if(targetPiece.getColor() == Color::RED_LOWERCASE){
        redKing = targetPiece.getCoordinate();
    } else if(targetPiece.getColor() == Color::BLUE_UPPERCASE){
        blueKing = targetPiece.getCoordinate();
    } else if(targetPiece.getColor() == Color::COLORLESS){
        assert(-1 && " undoMove of king failure");
    }


    //NOW WE NEED TO RECORD THIS "CASTLE"
    ChessMove king{start,finish};
    ChessMove rook{rookStart,rookFinish};

    auto p1 = std::make_unique<ChessCastle>(rook,king);
    recorder.addMove( std::move(p1) );


    return ChessErrorCode::VALID_MOVE;

}


/**
 * @return A picture of the board as a string to output to console.
 */
const std::string Board::getBoardView() const {

    std::stringstream stream;

    stream << "   abcdefgh\n___________\n";

    int num = 1;
    for(const vector<Piece> &row : _chessBoard){
        stream << num << "| ";
        drawRow(row,stream);
        num++;
    }
    stream << "___________\n";

    return stream.str();
}

/**
 * Gets a flipped view of the board for the second player to look at.
 */
const std::string Board::getReverseBoardView() const {
    std::stringstream stream;

    stream << "   hgfedcba\n___________\n";

    for(int num = 8 ; num > 0 ; num--){
        stream << num << "| ";
        const vector<Piece> &row = _chessBoard.at(num - 1);
        drawRowReverse(row,stream);
    }

    return stream.str();

}

/*Get the array of vectors for some purpose (Graphics)*/
const vector< vector<Piece> >& Board::getBoard() const {
    return _chessBoard;
}


/**
 *  Enter's in a coordinate and returns the piece at that location
 */
Piece& Board::requestPiece(const ChessCoordinate &position) {
    return _chessBoard.at( position.row ).at( position.col );
}

const Piece& Board::getPiece(const ChessCoordinate &position) const {
    return _chessBoard.at( position.row ).at( position.col );
}

const PieceUnit Board::requestUnit(const ChessCoordinate &position) const {
    Piece a = _chessBoard.at(position.row).at(position.col);
    return a.getPieceUnit();
}

const Color Board::getPieceColor(const ChessCoordinate &position) const {
    return _chessBoard.at(position.row).at(position.col).getColor();
}

//getters and setters
const Piece Board::getLastPieceKilled() const {
    if(!recorder.hasMove()){
        return Piece{PieceUnit::NONE, Color::COLORLESS, {-1,-1} };
    }

    return recorder.getLastMove()->pieceKilled;
}

//Should have overloaded version that takes in ChessCoordinates.
void Board::updatePiece(Piece &source, Piece &destination) {
    destination.setPieceId(source.getPieceUnit());
    destination.setPieceColor(source.getColor());
    destination.setHasMoved(true);

    source.setPieceId(PieceUnit::NONE);
    source.setPieceColor(Color::COLORLESS);
    source.setHasMoved(false);
}


ChessErrorCode Board::canKingDodge(const ChessCoordinate &kingCoordinate) {
    ChessCoordinate kingMoves[8] = { {-1,1}, {0,1}, {1,1}, {1,0}, {-1,0}, {-1,-1}, {0,-1}, {1,-1} };
    ChessErrorCode  code;
    for(const auto &iter : kingMoves){
        code = movePieceHelper(kingCoordinate, iter);
        if(code == ChessErrorCode::VALID_MOVE){
            undoMove();
            return code;
        }

    }
    return code;
}

//Only 1 enemy that is attacking the king so...
ChessErrorCode Board::canEliminate(const ChessCoordinate &kingCoordinate, const Color &enemyColor) {
    const auto &enemyLocations = checkmate_system->getAttackers(enemyColor);
    const auto enemyCoordinate = enemyLocations.at(0);

    ChessErrorCode result = ChessErrorCode::INVALID_MOVE; //Doesn't matter what his is initialized to as long as it isn't valid move
    const Color &teamColor = getPieceColor(kingCoordinate);
    const auto &boardRef = getBoard();

    for(int i = 0; i < boardRef.size(); i++){
        for(int j = 0; j < boardRef.at(i).size(); j++){
            if(getPieceColor({i,j}) == teamColor){
                result = movePieceHelper({i,j}, {enemyCoordinate});
                undoMove();
            }
            if(result == ChessErrorCode::VALID_MOVE){
                return result;
            }

        }
    }

    return ChessErrorCode::INVALID_MOVE;


}

ChessErrorCode Board::canBlock(const ChessCoordinate &kingCoordinate, const Color &enemyColor) {

    const auto &enemyLocations = checkmate_system->getAttackers(enemyColor);
    const auto enemyCoordinate = enemyLocations.at(0);

    ChessErrorCode result = ChessErrorCode::INVALID_MOVE; //Doesn't matter what his is initialized to as long as it isn't valid move
    const Color &teamColor = getPieceColor(kingCoordinate);
    const auto &boardRef = getBoard();

    //The unit must me a rook or bishop.

    ChessCoordinate dTravel = kingCoordinate - enemyCoordinate;
    vector<ChessCoordinate> blockingSquares;

    //A diagonal piece is attacking you!
    if(dTravel.row == dTravel.col){
        dTravel.row = dTravel.row / std::abs(dTravel.row);
        dTravel.col = dTravel.col / std::abs(dTravel.col);
    } else {
        dTravel = dTravel.toOne();
    }

    for(ChessCoordinate i = enemyCoordinate; !(i == kingCoordinate) ; ++i){
        blockingSquares.emplace_back(enemyCoordinate + dTravel);
        ++dTravel;
    }


    for(const auto &blockSpots : blockingSquares) {
        for (int i = 0; i < boardRef.size(); i++) {
            for (int j = 0; j < boardRef.at(i).size(); j++) {
                if (getPieceColor({i, j}) == teamColor) {
                    result = movePieceHelper({i, j}, {blockSpots});
                    undoMove();
                }
                if (result == ChessErrorCode::VALID_MOVE) {
                    return result;
                }

            }
        }
    }

    return ChessErrorCode::INVALID_MOVE;

}


//Color of the enemy
ChessErrorCode Board::isCheckMate(const Color &enemyColor){
    const auto &enemyLocations = checkmate_system->getAttackers(enemyColor);
    assert(enemyLocations.size() != -1);
    bool canBlockOrEliminate = enemyLocations.size() == 1;

    ChessErrorCode code;
    ChessCoordinate currentKing;
    if(enemyColor == Color::RED_LOWERCASE){
        currentKing = blueKing;
    } else if(enemyColor == Color::BLUE_UPPERCASE){
        currentKing = redKing;
    }

    code = canKingDodge(currentKing);
    if(code == ChessErrorCode::VALID_MOVE)
        return code;

    /*
    if(!canBlockOrEliminate){
        return ChessErrorCode::CHECK_MATED;
    }

    if(canEliminate(currentKing, enemyColor) == ChessErrorCode::VALID_MOVE){
        return ChessErrorCode::VALID_MOVE;
    }

    /////We can't move or kill the piece, and if the piece is a knight it is impossible to block therefore.
    if(requestUnit(enemyLocations.at(0)) == PieceUnit::KNIGHT){
        return ChessErrorCode::CHECK_MATED;
    }
    else if(canBlock(currentKing, enemyColor) == ChessErrorCode::VALID_MOVE){
        return ChessErrorCode::VALID_MOVE;
    }
    */

    return ChessErrorCode::CHECK_MATED;

}

/**
 * @param personMoving - The color of the pieces that are considered enemies, will check if say pieces
 * of the color 'x' are atacking the opposite color
 * @return - True if your being checked else false;
 */
bool Board::isCheck(const Color &personMoving) {


    if(personMoving == Color::RED_LOWERCASE){
        checkmate_system->isSquareUnderAttack(redKing, Color::RED_LOWERCASE, getBoard());
    } else if(personMoving == Color::BLUE_UPPERCASE){
        checkmate_system->isSquareUnderAttack(blueKing, Color::BLUE_UPPERCASE, getBoard());
    }

    const auto& enemies = checkmate_system->getAttackers(personMoving);

    if(enemies.empty()){
        return false;
    }

    std::cout << "Attackers: to king \n";
    for(const auto &iter : enemies){
        std:: cout << iter << "\n";
    }

    return true;

}


ChessErrorCode Board::movePieceHelper(const ChessCoordinate &start, const ChessCoordinate &finish) {

    if(!start.isValid() || !finish.isValid()){
        return ChessErrorCode::INVALID_MOVE;
    }


    Piece &sourcePiece = requestPiece(start);
    Piece &targetPiece = requestPiece(finish);

    if( ( sourcePiece.getColor() == targetPiece.getColor() ) || sourcePiece.getPieceUnit() == PieceUnit::NONE    ){
        return ChessErrorCode::INVALID_PIECE;
    }

    // If Piece is a Knight path is meaningless since they can jump over units
    bool pathClear = (sourcePiece.getPieceUnit() == PieceUnit::KNIGHT);
    if(!pathClear) { pathClear = isPathClear(start,finish); }
    if(!pathClear) {  return ChessErrorCode::INVALID_MOVE; }

    ////Code for moving the king specifically
    ////Can possibly cause the game to never end if stalemate is possible. (should disable this code or finish it off)
    if(sourcePiece.getPieceUnit() == PieceUnit::KING){
        bool isSquareAttacked = checkmate_system->isSquareUnderAttack(finish,sourcePiece.getColor(), getBoard());
        if(isSquareAttacked){
            return ChessErrorCode::INVALID_KING_MOVE;
        }
    }


    ChessErrorCode ChessCode = sourcePiece.checkMovementIsValid(start, finish, targetPiece.getColor() );
    if(ChessCode == ChessErrorCode::ENPASSANT){
        ChessCode = enPassant(start,finish);
    }

        //Special case for when user attempts to CASTLE
    else if(ChessCode == ChessErrorCode::CASTLE) {
        ChessCode = executeCastle(start, finish);
        return ChessCode;
    } else if(ChessCode == ChessErrorCode::VALID_MOVE){
        //We need to check if the move will place the user in check?

        promotePawnToQueen(sourcePiece, finish);
        recorder.addMove(start,finish, targetPiece);
        updatePiece(sourcePiece,targetPiece);

        if(targetPiece.getPieceUnit() == PieceUnit::KING && targetPiece.getColor() == Color::BLUE_UPPERCASE){
            blueKing = targetPiece.getCoordinate();
        } else if(targetPiece.getPieceUnit() == PieceUnit::KING && targetPiece.getColor() == Color::RED_LOWERCASE){
            redKing = targetPiece.getCoordinate();
        }

        //Checks to see if you are executing a move that would place you in check, if you did, undo it since
        //Placing yourself in check is illegal.
        if( isCheck(targetPiece.getColor()) ){
            undoMove();
            ChessCode =  ChessErrorCode::INVALID_MOVE;
        }
    }

    return ChessCode;
}


/***
 *
 * @param start - The coordinates of the piece you want to move
 * @param finish - The spot you want to want that piece to end up at.
 * @return - An ChessErrorCode that specifies whether the move succeded or failed
 */
ChessErrorCode Board::movePiece(const ChessCoordinate &start, const ChessCoordinate &finish) {

    ChessErrorCode ChessCode = movePieceHelper(start, finish);
    Piece &targetPiece = requestPiece(finish);


    Color enemyColor;
    bool checked = false;

    //Now we need to see if we checkmated the other player. The target piece here has been updated already. So
    //It must have a color.
    if(targetPiece.getColor() == Color::RED_LOWERCASE){
        enemyColor = Color::BLUE_UPPERCASE;
        checked = isCheck(Color::BLUE_UPPERCASE);
    } else {
        enemyColor = Color::RED_LOWERCASE;
        checked =isCheck(Color::RED_LOWERCASE);
    }

    if(checked){
        ChessCode = isCheckMate(enemyColor);
    }

    return ChessCode;

}


//Executes an enpassant, a french chess move where a pawn caputures a pawn that jumped 2 squares from it.
ChessErrorCode Board::enPassant(const ChessCoordinate &start, const ChessCoordinate &finish)  {
    const auto lastMove = recorder.getLastMove();

    const ChessCoordinate &pastMoveStart = lastMove->move.first;
    const ChessCoordinate &pastMoveEnd   = lastMove->move.second;

    if( abs(pastMoveEnd.row  - pastMoveStart.row) == 2 &&  requestUnit(pastMoveEnd) == PieceUnit::PAWN   ){

        //However they must finish directly behind that pawn.
        if( getPieceColor(start) == getPieceColor(pastMoveEnd)){
            return ChessErrorCode::INVALID_MOVE;
        }

        if(start.row == pastMoveEnd.row && (start.col + 1 == pastMoveEnd.col || start.col - 1 == pastMoveEnd.col ) ){
            //Now we need to check if pawn moves diagonally correctly
            if( (finish.row == pastMoveEnd.row - 1 || finish.row == pastMoveEnd.row + 1) && finish.col == pastMoveEnd.col ) {

                const auto pawnMove = std::make_pair(start,finish);

                ChessMove pawn{pawnMove, getPiece(pastMoveEnd) };
                ChessCoordinate coordinate{pastMoveEnd};
                auto chessMove = std::make_unique<MoveEnPassant>(pawn,coordinate);


                recorder.addMove( std::move(chessMove) );

                Piece::updatePiece(requestPiece(start), requestPiece(finish));
                _chessBoard[pastMoveEnd.row][pastMoveEnd.col] = Piece{PieceUnit::NONE, Color::COLORLESS, pastMoveEnd};

                return ChessErrorCode::VALID_MOVE;
            }
        }

    }

    return ChessErrorCode::INVALID_MOVE;

}

//Constructor
Board::Board() {
    _chessBoard.reserve(8);
    initializeGame(_chessBoard);

    redKing  = {0, 4};
    blueKing = {7, 4};

    checkmate_system = std::make_unique<CheckMate>(Color::RED_LOWERCASE, Color::BLUE_UPPERCASE);

}

Board::Board(vector<vector<Piece>> &chessBoard) {
    this->_chessBoard = chessBoard;

    checkmate_system = std::make_unique<CheckMate>(Color::RED_LOWERCASE, Color::BLUE_UPPERCASE);




    assert(chessBoard.size() == 8);
    for(int i = 0; i<7; ++i){
        assert(chessBoard.at(i).size() == 8);
    }

    redKing.row = 7;  //Hard coded for testing of 1 function
    redKing.col = 3;  //Hard coded for testing of 1 function

    blueKing.row = 0; //Hard coded for testing of 1 function
    blueKing.col = 3; //Hard coded for testing of 1 function


    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
            if(_chessBoard[i][j].getPieceUnit() == PieceUnit::KING){
                std::cout << i << "\n";
                if(_chessBoard[i][j].getColor() == Color::RED_LOWERCASE){
                    redKing = {i,j};
                } else if(_chessBoard[i][j].getColor() == Color::BLUE_UPPERCASE) {
                    blueKing = {i,j};
                }
            }

            _chessBoard[i][j].setCoordinate({i,j});

        }
    }



    assert(redKing.isValid());
    assert(blueKing.isValid());

}


/**Undo's a move with special attention given to the king
 */
void Board::undoMove() {
    ChessMove const * lastMove= recorder.getLastMove();
    if(lastMove==nullptr){
        return;
    }

    Piece& movedPiece = requestPiece(lastMove->move.second);
    if(movedPiece.getPieceUnit() == PieceUnit::KING){
        if(movedPiece.getColor() == Color::RED_LOWERCASE){
            redKing = lastMove->move.first;
        } else if(movedPiece.getColor() == Color::BLUE_UPPERCASE){
            blueKing = lastMove->move.first;
        } else if(movedPiece.getColor() == Color::COLORLESS){
            assert(-1 && " undoMove of king failure");
        }
    }

    recorder.undoMove(_chessBoard);

}



void Board::printListMove() {
    std::cout << recorder.printMoves();
}


const std::unordered_map<PieceUnit, char> Board::PieceLookUp = {
        {PieceUnit::NONE,         '-'},
        {PieceUnit::PAWN,         'P'},
        {PieceUnit::KNIGHT,       'N'},
        {PieceUnit::BISHOP,       'B'},
        {PieceUnit::ROOK,         'R'},
        {PieceUnit::KING,         'K'},
        {PieceUnit::QUEEN,        'Q'},
};
