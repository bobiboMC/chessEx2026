#include "King.h"
#include <cctype>


King::King(Player* player, int row, int col, Board* brd) : Piece(player, 'k', row, col, brd)
{
}


bool King::isLegalMove(int dstRow, int dstCol) const
{
	// King can only jump one square from its current position:
	// Left, Right, Up, Down, Diagonal
	int distRows = dstRow - _row;
	int distCols = dstCol - _col;
	int absDistRows = std::abs(distRows);
	int absDistCols = std::abs(distCols);
	int isJumpBigger = (absDistRows > King::MAX_JUMP_KING || absDistCols > King::MAX_JUMP_KING);
	if (isJumpBigger || closeToOppKing(dstRow, dstCol))
		return false;
	return true;
}

bool King::inCheck()
{
	for (int row = 0; row < BOARD_SIZE; row++)
		for (int col = 0; col < BOARD_SIZE; col++)
		{
			Piece** matBoard = _brd->getBoard();
			Piece* currPiece = nullptr;
			currPiece = *(matBoard + row * BOARD_SIZE + col);
			int distRows = row - _row;
			int distCols = col - _col;
			int absDistRows = std::abs(distRows);
			int absDistCols = std::abs(distCols);
			bool isOneSquareDiagonal = (absDistRows == 1 && absDistCols == 1);
			// check if the piece is owned by the other player
			// also check if piece is not NullPiece
			if (!_brd->isPieceOfPlayer(row, col, this->getPlayer()))
			{
				//if Queen doing check
				if (std::tolower(currPiece->getSign()) == 'q')
				{
					if (currPiece->isLegalMove(_row, _col))
						return true;
				}
				//if Rooks doing check
				if (std::tolower(currPiece->getSign()) == 'r')
				{
					if (currPiece->isLegalMove(_row, _col))
						return true;
				}
				//if Bishops doing check
				if (std::tolower(currPiece->getSign()) == 'b')
				{
					if (currPiece->isLegalMove(_row, _col))
						return true;
				}
				//if Knights doing check
				else if (std::tolower(currPiece->getSign()) == 'n')
				{
					if (currPiece->isLegalMove(_row, _col))
						return true;
				}

				//if Pawns doing check
				else if (std::tolower(currPiece->getSign()) == 'p') {
					if (isOneSquareDiagonal)
						return true;
				}

			}
	}
	return false;
}


bool King::defendCheck(int defendedRow, int defendedCol)
{
	Piece** matBoard = _brd->getBoard();
	Piece* currPiece = nullptr;
	for (int row = 0; row < BOARD_SIZE; row++) {
		for (int col = 0; col < BOARD_SIZE; col++)
		{
			currPiece = *(matBoard + row * BOARD_SIZE + col);
			// must be the defender pieces for defending and legality of the move
			if (currPiece != this && _brd->isPieceOfPlayer(row, col, this->getPlayer()) && currPiece->isLegalMove(defendedRow, defendedCol)) {
				_brd->Move(row, col, defendedRow, defendedCol);
				if (this->inCheck()) {
					_brd->undoLastMove();
				}
				else {
					_brd->undoLastMove();
					return true;
				}
			}
		}
	}
	return false;
}

bool King::isMate()
{
	const int ROW_BEFORE = _row - 1 >= Board::FirstRow ? _row - 1 : Board::FirstRow;
	const int ROW_AFTER = _row + 1 < BOARD_SIZE ? _row + 1 : BOARD_SIZE - 1;
	const int col_BEFORE = _col - 1 >= Board::A_Col ? _col - 1 : Board::A_Col;
	const int col_AFTER = _col + 1 < BOARD_SIZE ? _col + 1 : BOARD_SIZE - 1;
	for (int row = ROW_BEFORE; row <= ROW_AFTER; row++)
		for (int col = col_BEFORE; col <= col_AFTER; col++) {
			// if player's king can move into square to evade check
			if (!_brd->isPieceOfPlayer(row, col, this->getPlayer()))
			{
				_brd->Move(_row, _col, row, col);
				// if even one square safe then it's not mate
				if (!this->inCheck()) {
					_brd->undoLastMove();
					return false;
				}

				_brd->undoLastMove();
			}
			// check if other pieces can defend from check
			// not including king itself
			if (defendCheck(row, col)) {
				return false;

			}
		}
			
	return true;

}

bool King::closeToOppKing(int dstRow, int dstCol) const
{
	// King cannot move to square close to opponent's King (distance = 1)
	Piece** matBoard = _brd->getBoard();
	Piece* currPiece = nullptr;
	const int ROW_BEFORE = std::max(dstRow - 1, static_cast<int>(Board::FirstRow));
	const int ROW_AFTER = std::min(dstRow + 1, static_cast<int>(BOARD_SIZE - 1));
	const int COL_BEFORE = std::max(dstCol - 1, static_cast<int>(Board::A_Col));
	const int COL_AFTER = std::min(dstCol + 1, static_cast<int>(BOARD_SIZE - 1));
	for (int row = ROW_BEFORE; row <= ROW_AFTER; row++)
	{
		for (int col = COL_BEFORE; col <= COL_AFTER; col++) {
			currPiece = *(matBoard + row * BOARD_SIZE + col);
			if (currPiece != this && std::tolower(currPiece->getSign()) == 'k')
				return true;
		}
	}
	return false;
}

