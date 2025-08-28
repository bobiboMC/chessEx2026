#include "Pawn.h"
#include <cmath>   // std::abs
#include <cctype>
#include <iostream>



Pawn::Pawn(Player* player, int row, int col, Board* brd) : Piece(player, 'p', row, col, brd)
{

}

bool Pawn::isLegalMove(int dstRow, int dstCol) const
{
	//	Pawns can only move on same column (unless eat situation and en passo)
	if (_col == dstCol) {
		int distRows = dstRow - _row;
		int absDistRows = std::abs(distRows);
		int isJumpBigger = (absDistRows > Pawn::MAX_JUMP_PAWN); // can max jump 2 squares (depending on where pawn is located)
		if (!isJumpBigger) {
			// on starting square when game started, can jump one or two squares
			// or
			// pawn already moved from starting square, so can jump only one square
			if (_startRow == _row || absDistRows == Pawn::JUMP_ONE_SQUARE)
				// black pawn can only move up in board and down in indexes
				// and
				// white pawn can only move down in board and up in indexes
				if ((getPlayer()->isGoingUp() && distRows < 0) ||
					(!getPlayer()->isGoingUp() && distRows > 0))
				{
					// Pawns can move safely
					if (isWayFree(dstRow + distRows, dstCol))
						return true;
				}

		}
	}
	return false;
}

