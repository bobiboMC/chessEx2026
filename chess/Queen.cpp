#include "Queen.h"
#include "Queen.h"

Queen::Queen(Player* player, int row, int col, Board* brd): Piece(player, 'q', row, col, brd)
{
}

bool Queen::isLegalMove(int dstRow, int dstCol) const
{
	int distRows = dstRow - _row;
	int distCols = dstCol - _col;
	int absDistRows = std::abs(distRows);
	int absDistCols = std::abs(distCols);
	bool isDiagonal = absDistRows == absDistCols;
	//	Queen can only move on same column, same row or same diagonal
	if (_col == dstCol || _row == dstRow || isDiagonal) {
		// Queen can move safely
		if (isWayFree(dstRow, dstCol))
			return true;
	}
	return false;
}
