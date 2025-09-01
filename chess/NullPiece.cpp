#include "NullPiece.h"

NullPiece::NullPiece(int row, int col) : Piece(nullptr, '#', row, col, nullptr)
{

}

bool NullPiece::isLegalMove(int row, int col) const
{
	return false;
}