#pragma once

#include "ChessPiece.h"
#include "Chessboard.h"

class Pawn : public ChessPiece
{
private:
	int pieceValue;

public:
	Pawn(int pieceValue);
	~Pawn();
	int getPieceValue();
	bool check_legal_move(Chessboard& Board, BoardStatus status, sf::Vector2i Coord, PieceColor color);
};

