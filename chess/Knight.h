#pragma once

#include "Piece.h"

class Knight : public Piece
{
public:
	static constexpr int SUM_DIST_ROW_COL = 3;
	Knight(Player*, int row, int col, Board*);
	virtual bool isLegalMove(int, int) const;

private:

};