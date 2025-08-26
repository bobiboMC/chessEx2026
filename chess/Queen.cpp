#include "Queen.h"
#include "Queen.h"

Queen::Queen(Player* player, int row, int col, Board* brd): Piece(player, 'q', row, col, brd)
{
}

bool Queen::isLegalMove(int, int) const
{
    return false;
}
