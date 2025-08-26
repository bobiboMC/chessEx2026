#include "Knight.h"

Knight::Knight(Player* player, int row, int col, Board* brd) : Piece(player, 'n', row, col, brd)
{
}

bool Knight::isLegalMove(int, int) const
{
	return false;
}
