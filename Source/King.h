#pragma once

#include "ChessPiece.h"
#include "Chessboard.h"

class King : public ChessPiece
{
private:
	int pieceValue;

public:
	King(int pieceValue);
	~King();
	int getPieceValue();
	bool check_legal_move(Chessboard& Board, BoardStatus status, sf::Vector2i Coord, PieceColor color);
};

