#pragma once

#include "Piece.h"

class Pawn : public Piece
{
public:
	static constexpr int MAX_JUMP_PAWN = 2;
	static constexpr int JUMP_ONE_SQUARE = 1;
	static constexpr int JUMP_TWO_SQUARE = 2;
	static constexpr int BLACK_DIRECTION = -1;
	static constexpr int WHITE_DIRECTION = 1;
	static constexpr int ILLEGAL_MOVE_DIRECTION = 0;
	Pawn(Player*, int row, int col, Board*);

	virtual bool isLegalMove(int, int) const;
private:
	int checkMoveDirection(bool, int) const;
};