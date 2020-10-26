#include "Knight.h"
#include <vector>

Knight::Knight() {}

Knight::Knight(int x, int y, FIGURES figureType, int team, sf::Sprite sprite)
	: Figure(x, y, figureType, team, sprite) {}

void Knight::knightSearch() {
	if (x + 2 < 8) {
		if (y + 1 < 8) {
			if (board[x + 2][y + 1] == 0)
				avaliableCells.push_back({ x + 2, y + 1 });
			int pos = (x + 2) * 10 + y + 1;
			if (figures.find(pos) != figures.end() && figures[pos]->getTeam() != team) {
				avaliableCells.push_back({ x + 2, y + 1 });
			}
		}

		if (y - 1 >= 0) {
			if (board[x + 2][y - 1] == 0)
				avaliableCells.push_back({ x + 2, y - 1 });
			int pos = (x + 2) * 10 + y - 1;
			if (figures.find(pos) != figures.end() && figures[pos]->getTeam() != team) {
				avaliableCells.push_back({ x + 2, y - 1 });
			}
		}
	}

	if (x - 2 >= 0) {
		if (y + 1 < 8) {
			if (board[x - 2][y + 1] == 0)
				avaliableCells.push_back({ x - 2, y + 1 });
			int pos = (x - 2) * 10 + y + 1;
			if (figures.find(pos) != figures.end() && figures[pos]->getTeam() != team) {
				avaliableCells.push_back({ x - 2, y + 1 });
			}
		}

		if (y - 1 >= 0) {
			if (board[x - 2][y - 1] == 0)
				avaliableCells.push_back({ x - 2, y - 1 });
			int pos = (x - 2) * 10 + y - 1;
			if (figures.find(pos) != figures.end() && figures[pos]->getTeam() != team) {
				avaliableCells.push_back({ x - 2, y - 1 });
			}
		}
	}

	if (y + 2 < 8) {
		if (x + 1 < 8) {
			if (board[x + 1][y + 2] == 0)
				avaliableCells.push_back({ x + 1, y + 2 });
			int pos = (x + 1) * 10 + y + 2;
			if (figures.find(pos) != figures.end() && figures[pos]->getTeam() != team) {
				avaliableCells.push_back({ x + 1, y + 2 });
			}
		}
			
		if (x - 1 >= 0) {
			if (board[x - 1][y + 2] == 0)
				avaliableCells.push_back({ x - 1 , y + 2 });
			int pos = (x - 1) * 10 + y + 2;
			if (figures.find(pos) != figures.end() && figures[pos]->getTeam() != team) {
				avaliableCells.push_back({ x - 1 , y + 2 });
			}
		}		
	}

	if (y - 2 >= 0) {
		if (x + 1 < 8) {
			if (board[x + 1][y - 2] == 0)
				avaliableCells.push_back({ x + 1, y - 2 });
			int pos = (x + 1) * 10 + y - 2;
			if (figures.find(pos) != figures.end() && figures[pos]->getTeam() != team) {
				avaliableCells.push_back({ x + 1, y - 2 });
			}
		}

		if (x - 1 >= 0) {
			if (board[x - 1][y - 2] == 0)
				avaliableCells.push_back({ x - 1 , y - 2 });
			int pos = (x - 1) * 10 + y - 2;
			if (figures.find(pos) != figures.end() && figures[pos]->getTeam() != team) {
				avaliableCells.push_back({ x - 1 , y - 2 });
			}
		}
		
		if (x + 1 < 8 && board[x + 1][y - 2] == 0)
			avaliableCells.push_back({ x + 1, y - 2 });
		if (x - 1 >= 0 && board[x - 1][y - 2] == 0)
			avaliableCells.push_back({ x - 1 , y - 2 });
	}
}

void Knight::findAvaliableCells() {
	avaliableCells.resize(0);
	knightSearch();
	/*for (auto i : avaliableCells) {
		std::cout << " x = " << i.x << " y = " << i.y << '\n';
	}
	if (!avaliableCells.size())
		std::cout << "Empty";*/
}