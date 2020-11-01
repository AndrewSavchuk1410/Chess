#include "King.h"
#include <iostream>
#include <set>

enum class FIGURES {
	ROOK = 1,
	KNIGHT = 2,
	BISHOP = 3,
	QUEEN = 4,
	KING = 5,
	PAWN = 6
};

King::King() {}

King::King(int x, int y, FIGURES figureType, int team, sf::Sprite sprite)
	: Figure(x, y, figureType, team, sprite) {}


void King::findAvaliableCells() {
	int steps = 1;
	avaliableCells.resize(0);
	horizontalSearh(steps);
	verticalSearh(steps);
	diagonalSearh(steps);
	

	if (team == 1 && x == 4 && y == 7 && !hasMoved && !board[5][7] && !board[6][7]
		&& board[7][7] == 1 && figures[77]->ifHasMoved() == false) {
		std::vector <sf::Vector2i> positions;
		positions.push_back({ 4,7 });
		positions.push_back({ 5,7 });
		positions.push_back({ 6,7 });


		std::vector <sf::Vector2i> S;
		for (auto it : figures) {
			if (it.second->getTeam() == -1 && it.second->getFigureType() != FIGURES::KING) {
				it.second->findAvaliableCells();
				for (auto j : it.second->getAvaliableCells())
					S.push_back({ j.x, j.y });
			}
		}
		
		bool flag = true;
		for (auto j : positions) {
			if (std::find(S.begin(), S.end(), j) != S.end()) {
				flag = false;
				break;
			}
		}

		if (flag) avaliableCells.push_back({ 6,7 });
	}

	if (team == 1 && x == 4 && y == 7 && !hasMoved && !board[3][7] && !board[2][7]
		&& board[0][7] == 1 && figures[7]->ifHasMoved() == false) {
		std::vector <sf::Vector2i> positions;
		positions.push_back({ 4,7 });
		positions.push_back({ 3,7 });
		positions.push_back({ 2,7 });

		std::vector <sf::Vector2i> S;
		for (auto it : figures) {
			if (it.second->getTeam() == -1 && it.second->getFigureType() != FIGURES::KING) {
				it.second->findAvaliableCells();
				for (auto j : it.second->getAvaliableCells())
					S.push_back({ j.x, j.y });
			}
		}

		bool flag = true;
		for (auto j : positions) {
			if (std::find(S.begin(), S.end(), j) != S.end()) {
				flag = false;
				break;
			}
		}

		if (flag) avaliableCells.push_back({ 2,7 });
	}

	if (team == -1 && x == 4 && y == 0 && !hasMoved && !board[3][0] && !board[2][0]
		&& board[0][0] == -1 && figures[0]->ifHasMoved() == false) {
		std::vector <sf::Vector2i> positions;
		positions.push_back({ 4,0 });
		positions.push_back({ 3,0 });
		positions.push_back({ 2,0 });

		std::vector <sf::Vector2i> S;
		for (auto it : figures) {
			if (it.second->getTeam() == 1 && it.second->getFigureType() != FIGURES::KING) {
				it.second->findAvaliableCells();
				for (auto j : it.second->getAvaliableCells())
					S.push_back({ j.x, j.y });
			}
		}

		bool flag = true;
		for (auto j : positions) {
			if (std::find(S.begin(), S.end(), j) != S.end()) {
				flag = false;
				break;
			}
		}

		if (flag) avaliableCells.push_back({ 2,0 });
	}

	if (team == -1 && x == 4 && y == 0 && !hasMoved && !board[5][0] && !board[6][0]
		&& board[7][0] == -1 && figures[70]->ifHasMoved() == false) {
		std::vector <sf::Vector2i> positions;
		positions.push_back({ 4,0 });
		positions.push_back({ 5,0 });
		positions.push_back({ 6,0 });

		std::vector <sf::Vector2i> S;
		for (auto it : figures) {
			if (it.second->getTeam() == 1 && it.second->getFigureType() != FIGURES::KING) {
				it.second->findAvaliableCells();
				for (auto j : it.second->getAvaliableCells())
					S.push_back({ j.x, j.y });
			}
		}

		bool flag = true;
		for (auto j : positions) {
			if (std::find(S.begin(), S.end(), j) != S.end()) {
				flag = false;
				break;
			}
		}

		if (flag) avaliableCells.push_back({ 6,0 });
	}
	

	/*for (auto i : avaliableCells) {
		std::cout << " x = " << i.x << " y = " << i.y << '\n';
	}
	if (!avaliableCells.size())
		std::cout << "Empty";*/
}