#pragma once

#include "Piece.h"

class Pawn : public Piece
{
public:
	static constexpr int MAX_JUMP_PAWN = 2;
	static constexpr int JUMP_ONE_SQUARE = 1;
	Pawn(Player*, int row, int col, Board*);

	virtual bool isLegalMove(int, int) const;
private:
};