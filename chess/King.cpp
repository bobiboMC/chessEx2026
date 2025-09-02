#include "King.h"
#include <cctype>
#include "Knight.h"


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
	if (!isJumpBigger)
		return true;
	return false;
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
			if (currPiece->getPlayer() && currPiece->getPlayer()->isWhite() != getPlayer()->isWhite())
			{
				//if Queen doing check
				if ((_row == row || _col == col || absDistCols == absDistRows) && isWayFree(row, col))
				{
					if (std::tolower(currPiece->getSign()) == 'q')
						return true;
				}
				//if Rooks doing check
				if (_row == row || _col == col)
				{
					if (std::tolower(currPiece->getSign()) == 'r' && isWayFree(row, col))
						return true;
				}
				//if Bishops doing check
				if (absDistCols == absDistRows && isWayFree(row, col))
				{
					if (std::tolower(currPiece->getSign()) == 'b')
						return true;
				}
				//if Knights doing check
				else if (absDistCols + absDistRows == Knight::SUM_DIST_ROW_COL && absDistRows != 0 && absDistCols != 0)
				{
					if (std::tolower(currPiece->getSign()) == 'n')
						return true;
				}

				//if Pawns doing check
				else if (isOneSquareDiagonal) {
					if (std::tolower(currPiece->getSign()) == 'p')
						return true;
				}

			}
	}
	return false;
}

bool King::isMate()
{
	const int ROW_BEFORE = _row - 1 >= Board::FirstRow ? _row - 1 : Board::FirstRow;
	const int ROW_AFTER = _row + 1 < BOARD_SIZE ? _row + 1 : BOARD_SIZE - 1;
	const int col_BEFORE = _col - 1 >= Board::FirstCol ? _col - 1 : Board::FirstCol;
	const int col_AFTER = _col + 1 < BOARD_SIZE ? _col + 1 : BOARD_SIZE - 1;
	for (int row = ROW_BEFORE; row <= ROW_AFTER; row++)
		for (int col = col_BEFORE; col <= col_AFTER; col++)
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
	return true;

}
