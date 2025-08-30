#include "Board.h"
#include "NullPiece.h"
#include "Pawn.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include <map>
#include <iostream>

#define POSITION_STILL_NOT_EXIST -1

Board::Board(Player* player1, Player* player2)
{

	std::map<Row, Player*> uniqePiecesRows = {
		{ Row::FirstRow, player1 },
		{ Row::EighthRow, player2 }
	};

	for (int row = Row::SecondRow; row < Row::EighthRow; row++)
		for (int col = 0; col < BOARD_SIZE; col++)
		{
			switch (row) {
			/*
			case Row::SecondRow:
				_brd[row][col] = new Pawn(player1, row, col, this);
				break;
			case Row::SeventhRow:
				_brd[row][col] = new Pawn(player2, row, col, this);
				break;
				// There is no pieces in rows 3-6 when we start the game
			*/
			default:
				_brd[row][col] = new NullPiece(row, col);
			}
		}

	// special pieces
	for (auto& row : uniqePiecesRows)
		for (int col = 0; col < BOARD_SIZE; col++)
		{
			switch (col) {
			case Col::FirstCol:
				_brd[row.first][col] = new Rook(row.second, row.first, col, this);
				break;
			case Col::SecondCol:
				_brd[row.first][col] = new Bishop(row.second, row.first, col, this);
				break;
			case Col::ThirdCol:
				_brd[row.first][col] = new Knight(row.second, row.first, col, this);
				break;
			case Col::ForthCol:
				_brd[row.first][col] = new Queen(row.second, row.first, col, this);
				break;
			case Col::FifthCol:
			{
				King* kng = new King(row.second, row.first, col, this);
				_brd[row.first][col] = kng;
				row.second->setKing(kng);
				break;
			}
			case Col::SixthCol:
				_brd[row.first][col] = new Bishop(row.second, row.first, col, this);
				break;		
			case Col::SeventhCol:
				_brd[row.first][col] = new Knight(row.second, row.first, col, this);
				break;
			case Col::EighthCol:
				_brd[row.first][col] = new Rook(row.second, row.first, col, this);
				break;
			default:
				_brd[row.first][col] = new NullPiece(row.first, col);
				break;
			}
		}


	this->_lastSrcRow = POSITION_STILL_NOT_EXIST;
	this->_lastSrcCol = POSITION_STILL_NOT_EXIST;
	this->_lastDstRow = POSITION_STILL_NOT_EXIST;
	this->_lastDstCol = POSITION_STILL_NOT_EXIST;
	this->_lastPiece = nullptr;


}

Board::~Board()
{
	for (int row = 0; row < BOARD_SIZE; row++)
		for (int col = 0; col < BOARD_SIZE; col++)
			delete _brd[row][col];
}

void Board::print() const
{
	std::cout << "  a b c d e f g h" << std::endl;
	for (int i = 0; i < BOARD_SIZE; i++) {
		cout << BOARD_SIZE - i << " ";
		for (int j = 0; j < BOARD_SIZE; j++) {
			std::cout << _brd[i][j]->getSign() << " ";
		}
		std::cout << BOARD_SIZE - i << std::endl;
	}
	std::cout << "  a b c d e f g h" << std::endl;
}

void Board::getString(char res[]) const
{
	int k = 0;
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			res[k] = _brd[i][j]->getSign();
			k++;
		}
	}
	res[k] = Player::WHITE;
	k += 1;
	res[k] = '\0';
}

bool Board::isPieceOfPlayer(int row, int col, Player* player) const
{
	char squareSign;
	squareSign = _brd[row][col]->getSign();
	//white piece
	if (player->isWhite() && std::isupper(squareSign))
		return true;
	//black piece
	else if (!player->isWhite() && std::islower(squareSign))
		return true;

	return false;
}

bool Board::tryMove(int srcRow, int srcCol, int dstRow, int dstCol) const
{
	if (_brd[srcRow][srcCol]->isLegalMove(dstRow, dstCol))
		return true;
	return false;
}

Piece** Board::getBoard() const
{
	return (Piece**)_brd;

}

void Board::Move(int srcRow, int srcCol, int dstRow, int dstCol)
{
	// In case No Piece was allocated to this square
	if (!_brd[dstRow][dstCol]) throw std::invalid_argument("No piece was allocated to this square");

	this->_lastPiece = _brd[dstRow][dstCol];
	_brd[srcRow][srcCol]->setPosition(dstRow, dstCol);
	_brd[dstRow][dstCol] = _brd[srcRow][srcCol];
	_brd[srcRow][srcCol] = new NullPiece(srcRow, srcCol);


	this->_lastSrcRow = srcRow;
	this->_lastSrcCol = srcCol;
	this->_lastDstRow = dstRow;
	this->_lastDstCol = dstCol;

}

void Board::undoLastMove()
{
	delete _brd[_lastSrcRow][_lastSrcCol];
	_brd[_lastDstRow][_lastDstCol]->setPosition(_lastSrcRow, _lastSrcCol);
	_brd[_lastSrcRow][_lastSrcCol] = _brd[_lastDstRow][_lastDstCol];
	_brd[_lastDstRow][_lastDstCol] = this->_lastPiece;
}
