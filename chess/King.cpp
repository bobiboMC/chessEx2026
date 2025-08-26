#include "King.h"

King::King(Player* player, int row, int col, Board* brd) : Piece(player, 'k', row, col, brd)
{
}

bool King::isLegalMove(int, int) const
{
	return false;
}

bool King::isChess()
{
	return false;
}
