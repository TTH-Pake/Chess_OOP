#pragma once
#include "ChessPiece.h"
#include "Chessboard.h"

class Knight : public ChessPiece
{
private:
	int pieceValue;

public:
	Knight(int pieceValue);
	~Knight();
	int getPieceValue();
	bool check_legal_move(Chessboard& Board, BoardStatus status, sf::Vector2i Coord, PieceColor color);
};
