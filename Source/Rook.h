#pragma once

#include "ChessPiece.h"
#include "Chessboard.h"
class Rook :public ChessPiece
{
private:
	int pieceValue;

public:
	Rook(int pieceValue);
	~Rook();
	int getPieceValue();
	bool check_legal_move(Chessboard& Board, BoardStatus status, sf::Vector2i Coord, PieceColor color);

};

