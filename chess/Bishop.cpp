#include "Bishop.h"

Bishop::Bishop(Player* player, int row, int col, Board* brd): Piece(player, 'b', row, col, brd)
{
}

bool Bishop::isLegalMove(int dstRow, int dstCol) const
{
	int distRows = dstRow - _row;
	int distCols = dstCol - _col;
	int absDistRows = std::abs(distRows);
	int absDistCols = std::abs(distCols);
	bool isJumpLegal = absDistRows == absDistCols;
	//	Bishops can only move on diagonal
	if (isJumpLegal) {
		// Bishops can move safely
		if (isWayFree(dstRow, dstCol))
			return true;
	}
	return false;
}
