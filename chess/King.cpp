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
			if (std::tolower(currPiece->getSign()) == 'b')
			{

			}
			// check if the piece is owned by the other player
			// also check if piece is not NullPiece
			if (currPiece->getPlayer() && currPiece->getPlayer()->isWhite() != getPlayer()->isWhite())
			{
				//if Rooks doing check
				if (_row == row || _col == col)
				{
					if (std::tolower(currPiece->getSign()) == 'r')
						return true;
				}
				//if Bishops doing check
				else if (std::abs(col - _col) == std::abs(row - _row))
				{
					if (std::tolower(currPiece->getSign()) == 'b')
						return true;
				}
				
			}
	}
	return false;
}
