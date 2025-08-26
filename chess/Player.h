#pragma once

#include <vector>
#include "Piece.h"
using namespace std;

class Piece;
class King;

class Player
{
public:
	static const int WHITE = 0;
	static const int BLACK = 1;
	Player(bool isWhite);
	Player(bool isWhite, bool isUp);
	~Player();
	void setKing(King*);
	King* getKing() const;
	bool isWhite() const;
	bool isGoingUp() const;
private:
	King* _myKing;
	bool _isWhite;
	bool _isGoingUp;
};

