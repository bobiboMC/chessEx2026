#include "Rook.h"

Rook::Rook(Player* player, int row, int col, Board* brd) : Piece(player, 'r', row, col, brd)
{
}

bool Rook::isLegalMove(int dstRow, int dstCol) const
{

	//	Rooks can only move on same column or same row
	if (_col == dstCol || _row == dstRow) {
		// Rooks can move safely
		if (isWayFree(dstRow, dstCol))
			return true;
	}
	return false;
}
