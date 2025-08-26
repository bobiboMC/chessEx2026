#include "Bishop.h"

Bishop::Bishop(Player* player, int row, int col, Board* brd): Piece(player, 'b', row, col, brd)
{
}

bool Bishop::isLegalMove(int, int) const
{
	return false;
}
