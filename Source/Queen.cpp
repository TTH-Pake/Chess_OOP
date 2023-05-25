#include "Queen.h"

Queen::Queen(int pieceValue)
{
	this->pieceValue = pieceValue;
}

Queen::~Queen()
{

}

int Queen::getPieceValue()
{
	return this->pieceValue;
}

bool Queen::check_legal_move(Chessboard& Board, BoardStatus status, sf::Vector2i Coord, PieceColor color)
{
	Board.getPieceColor(Coord);
	Board.getPieceID(Coord);
	int x = Coord.x;
	int y = Coord.y;

	//left---------------
	while (x - 1 >= 0 && x - 1 <= 7) {

		if (status == BoardStatus::Empty ||
			status == BoardStatus::Occupied) {

			if (status == BoardStatus::Occupied) {
				if (Board.getPieceColor(Coord) != color) {
					if (Board.getPieceID(Coord) == PieceID::Queen) {
						return true;
					}
					else break;
				}
				else break;
			}
		}
		x--;
	}


	//right
	x = Coord.x;
	y = Coord.y;
	while (x + 1 >= 0 && x + 1 <= 7) {

		if (status == BoardStatus::Empty ||
			status == BoardStatus::Occupied) {

			if (status == BoardStatus::Occupied) {
				if (Board.getPieceColor(Coord) != color) {
					if (Board.getPieceID(Coord) == PieceID::Queen) {
						return true;
					}
					else break;
				}
				else break;
			}

		}

		x++;
	}

	//up
	x = Coord.x;
	y = Coord.y;
	while (y - 1 >= 0 && y - 1 <= 7) {

		if (status == BoardStatus::Empty ||
			status == BoardStatus::Occupied) {

			if (status == BoardStatus::Occupied) {
				if (Board.getPieceColor(Coord) != color) {
					if (Board.getPieceID(Coord) == PieceID::Queen) {
						return true;
					}
					else break;
				}
				else break;
			}
		}
		y--;

	}

	//down
	x = Coord.x;
	y = Coord.y;
	while (y + 1 >= 0 && y + 1 <= 7) {

		if (status == BoardStatus::Empty ||
			status == BoardStatus::Occupied) {

			if (status == BoardStatus::Occupied) {
				if (Board.getPieceColor(Coord) != color) {
					if (Board.getPieceID(Coord) == PieceID::Queen) {
						return true;
					}
					else break;
				}
				else break;
			}
		}

		y++;
	}


	//top-left---------------
	x = Coord.x;
	y = Coord.y;

	while (x - 1 >= 0 && x - 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {

		if (status == BoardStatus::Empty ||
			status == BoardStatus::Occupied) {

			if (status == BoardStatus::Occupied) {
				if (Board.getPieceColor(Coord) != color) {
					if (Board.getPieceID(Coord) == PieceID::Queen) {
						return true;
					}
					else break;
				}
				else break;
			}
		}


		x--; y--;
	}

	//top-right---------------

	x = Coord.x;
	y = Coord.y;

	while (x + 1 >= 0 && x + 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {

		if (status == BoardStatus::Empty ||
			status == BoardStatus::Occupied) {

			if (status == BoardStatus::Occupied) {
				if (Board.getPieceColor(Coord) != color) {
					if (Board.getPieceID(Coord) == PieceID::Queen) {
						return true;
					}
					else break;
				}
				else break;
			}
		}

		x++; y--;
	}

	//bottom-left---------------

	x = Coord.x;
	y = Coord.y;

	while (x - 1 >= 0 && x - 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {

		if (status == BoardStatus::Empty ||
			status == BoardStatus::Occupied) {

			if (status == BoardStatus::Occupied) {
				if (Board.getPieceColor(Coord) != color) {
					if (Board.getPieceID(Coord) == PieceID::Queen) {
						return true;
					}
					else break;
				}
				else break;
			}

		}

		x--; y++;
	}

	//bottom-right---------------

	x = Coord.x;
	y = Coord.y;

	while (x + 1 >= 0 && x + 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {

		if (status == BoardStatus::Empty ||
			status == BoardStatus::Occupied) {

			if (status == BoardStatus::Occupied) {
				if (Board.getPieceColor(Coord) != color) {
					if (Board.getPieceID(Coord) == PieceID::Queen) {
						return true;
					}
					else break;
				}
				else break;
			}
		}

		x++; y++;
	}
	return false;
}
