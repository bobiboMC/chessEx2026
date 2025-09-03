#include "Knight.h"


Knight::Knight(Player* player, int row, int col, Board* brd) : Piece(player, 'n', row, col, brd)
{
}

bool Knight::isLegalMove(int dstRow, int dstCol) const
{
	int distRows = dstRow - _row;
	int distCols = dstCol - _col;
	int absDistRows = std::abs(distRows);
	int absDistCols = std::abs(distCols);
	bool absDistColss = std::abs(distCols);
	bool isJumpLegal = (absDistRows + absDistCols == Knight::SUM_DIST_ROW_COL) && absDistRows != 0 && absDistCols != 0;
	//	Knights can only jump like L shape (for example: two square down one square left/right
	if (isJumpLegal) {
		// Knights can move safely
		return true;
	}
	return false;
}
