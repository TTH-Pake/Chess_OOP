#include "Knight.h"

Knight::Knight(int pieceValue)
{
	this->pieceValue = pieceValue;
}

Knight::~Knight()
{

}

int Knight::getPieceValue()
{
	return this->pieceValue;
}

bool Knight::check_legal_move(Chessboard& Board, BoardStatus status, sf::Vector2i Coord, PieceColor color)
{
	Board.getPieceColor(Coord);
	Board.getPieceID(Coord);
	int x = Coord.x;
	int y = Coord.y;

	if ((x - 1 >= 0 && y - 2 >= 0)) {
		if (status == BoardStatus::Occupied) {
			if (Board.getPieceColor(Coord) != color) {
				if (Board.getPieceID(Coord) == PieceID::Knight) return true;
			}
		}
	}

	//top - right----------------------
	if ((x + 1 <= 7 && y - 2 >= 0)) {

		if ((x + 1 >= 0 && y - 2 >= 0)) {
			if (status == BoardStatus::Occupied) {
				if (Board.getPieceColor(Coord) != color) {
					if (Board.getPieceID(Coord) == PieceID::Knight) return true;
				}
			}
		}
	}

	//bottom - left----------------------
	if ((x - 1 >= 0 && y + 2 <= 7)) {

		if ((x - 1 >= 0 && y + 2 >= 0)) {
			if (status == BoardStatus::Occupied) {
				if (Board.getPieceColor(Coord) != color) {
					if (Board.getPieceID(Coord) == PieceID::Knight) return true;
				}
			}
		}
	}

	//bottom - right----------------------
	if ((x + 1 <= 7 && y + 2 <= 7)) {

		if ((x + 1 >= 0 && y + 2 >= 0)) {
			if (status == BoardStatus::Occupied) {
				if (Board.getPieceColor(Coord) != color) {
					if (Board.getPieceID(Coord) == PieceID::Knight) return true;
				}
			}
		}
	}



	//left - bottom----------------------
	if ((x - 2 >= 0 && y + 1 <= 7)) {

		if ((x - 2 >= 0 && y + 1 >= 0)) {
			if (status == BoardStatus::Occupied) {
				if (Board.getPieceColor(Coord) != color) {
					if (Board.getPieceID(Coord) == PieceID::Knight) return true;
				}
			}
		}
	}

	//left - top----------------------
	if ((x - 2 >= 0 && y - 1 >= 0)) {

		if ((x - 2 >= 0 && y - 1 >= 0)) {
			if (status == BoardStatus::Occupied) {
				if (Board.getPieceColor(Coord) != color) {
					if (Board.getPieceID(Coord) == PieceID::Knight) return true;
				}
			}
		}
	}

	//right - top------------------
	if ((x + 2 <= 7 && y + 1 <= 7)) {

		if ((x + 2 >= 0 && y + 1 >= 0)) {
			if (status == BoardStatus::Occupied) {
				if (Board.getPieceColor(Coord) != color) {
					if (Board.getPieceID(Coord) == PieceID::Knight) return true;
				}
			}
		}
	}

	//right - bottom------------------
	if ((x + 2 <= 7 && y - 1 >= 0)) {

		if ((x + 2 >= 0 && y - 1 >= 0)) {
			if (status == BoardStatus::Occupied) {
				if (Board.getPieceColor(Coord) != color) {
					if (Board.getPieceID(Coord) == PieceID::Knight) return true;
				}
			}
		}
	}

	return false;
}


