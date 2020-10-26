#include "Pawn.h"

Pawn::Pawn() {}

Pawn::Pawn(int x, int y, FIGURES figureType, int team, sf::Sprite sprite)
	: Figure(x, y, figureType, team, sprite) {}

void Pawn::findAvaliableCells() {
	avaliableCells.resize(0);
	if (team == 1) {
		if (y - 1 >= 0 && board[x][y - 1] == 0)
			avaliableCells.push_back({ x, y - 1 });
		int pos = (x - 1) * 10 + y - 1;
		if (figures.find(pos) != figures.end() && figures[pos]->getTeam() != team &&
			y - 1 >= 0 && x - 1 >= 0)
			avaliableCells.push_back({ x - 1, y - 1 });
		pos = (x + 1) * 10 + y - 1;
		if (figures.find(pos) != figures.end() && figures[pos]->getTeam() != team &&
			y - 1 >= 0 && x + 1 < 8)
			avaliableCells.push_back({ x + 1, y - 1 });
		if (!hasMoved && board[x][y - 1] == 0) {
			if (y - 2 >= 0 && board[x][y - 2] == 0)
				avaliableCells.push_back({ x, y - 2 });
		}
	}
	else if (team == -1) {
		if (y + 1 < 8 && board[x][y + 1] == 0 )
			avaliableCells.push_back({ x, y + 1 });
		int pos = (x - 1) * 10 + y + 1;
		if (figures.find(pos) != figures.end() && figures[pos]->getTeam() != team &&
			x - 1 >= 0 && y + 1 < 8)
			avaliableCells.push_back({ x - 1, y + 1 });
		pos = (x + 1) * 10 + y + 1;
		if (figures.find(pos) != figures.end() && figures[pos]->getTeam() != team &&
			x + 1 < 8 && y + 1 < 8)
			avaliableCells.push_back({ x + 1, y + 1 });
		if (!hasMoved && board[x][y + 1] == 0) {
			if (y + 2 < 8 && board[x][y + 2] == 0)
				avaliableCells.push_back({ x, y + 2 });
		}
	}
	/*for (auto i : avaliableCells) {
		std::cout << " x = " << i.x << " y = " << i.y << '\n';
	}
	if (!avaliableCells.size())
		std::cout << "Empty";*/
}