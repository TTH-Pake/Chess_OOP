#pragma once

#include "ChessPiece.h"
#include "Chessboard.h"

class Bishop :public ChessPiece
{
private:
	int pieceValue;

public:
	Bishop(int pieceValue);
	~Bishop();
	int getPieceValue();
	bool check_legal_move(Chessboard& Board, BoardStatus status, sf::Vector2i Coord, PieceColor color);

};


