#pragma once


#include "Piece.h"

class Piece;
class Player;
class Board;

class King : public Piece
{
public:
	static constexpr int MAX_JUMP_KING = 1;
	King(Player*, int row, int col, Board*);
	virtual bool isLegalMove(int, int) const;
	bool inCheck();

private:

};