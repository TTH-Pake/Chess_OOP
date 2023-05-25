#include "Pawn.h"

Pawn::Pawn(int pieceValue)
{
	this->pieceValue = pieceValue;
}

Pawn::~Pawn()
{

}

int Pawn::getPieceValue()
{
	return this->pieceValue;
}

bool Pawn::check_legal_move(Chessboard& Board, BoardStatus status, sf::Vector2i Coord, PieceColor color)
{
	Board.getPieceColor(Coord);
	Board.getPieceID(Coord);
	int x = Coord.x;
	int y = Coord.y;

	//left---------------
	if (x - 1 >= 0 && x - 1 <= 7) {
		if (status == BoardStatus::Occupied &&
			Board.getPieceColor(Coord) != color &&
			Board.getPieceID(Coord) == PieceID::Pawn)
			return true;
	}

	//right
	if (x + 1 >= 0 && x + 1 <= 7) {
		if (status == BoardStatus::Occupied &&
			Board.getPieceColor(Coord) != color &&
			Board.getPieceID(Coord) == PieceID::Pawn)
			return true;
	}

	//up
	if (y - 1 >= 0 && y - 1 <= 7) {
		if (status == BoardStatus::Occupied &&
			Board.getPieceColor(Coord) != color &&
			Board.getPieceID(Coord) == PieceID::Pawn)
			return true;
	}

	//down
	if (y + 1 >= 0 && y + 1 <= 7) {
		if (status == BoardStatus::Occupied &&
			Board.getPieceColor(Coord) != color &&
			Board.getPieceID(Coord) == PieceID::Pawn)
			return true;
	}

	//top-left---------------
	if (x - 1 >= 0 && x - 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {

		if (status == BoardStatus::Occupied &&
			Board.getPieceColor(Coord) != color) {

			if (Board.getPieceID(Coord) == PieceID::Pawn)
				return true;
		}
	}


	//top-right---------------
	if (x + 1 >= 0 && x + 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
		if (status == BoardStatus::Occupied &&
			Board.getPieceColor(Coord) != color) {

			if (Board.getPieceID(Coord) == PieceID::Pawn)
				return true;

		}
	}

	//bottom-left---------------
	if (x - 1 >= 0 && x - 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {

		if (status == BoardStatus::Occupied &&
			Board.getPieceColor(Coord) != color) {

			if (Board.getPieceID(Coord) == PieceID::Pawn)
				return true;
		}
	}

	//bottom-right---------------
	if (x + 1 >= 0 && x + 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
		if (status == BoardStatus::Occupied &&
			Board.getPieceColor(Coord) != color) {

			if (Board.getPieceID(Coord) == PieceID::Pawn)
				return true;
		}
	}

	return false;
}


