#pragma once

#include "ChessPiece.h"
#include "Chessboard.h"

class Queen : public ChessPiece
{
private:
	int pieceValue;

public:
	Queen(int pieceValue);
	~Queen();
	int getPieceValue();
	bool check_legal_move(Chessboard& Board, BoardStatus status, sf::Vector2i Coord, PieceColor color);
};

