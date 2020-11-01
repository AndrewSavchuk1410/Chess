#include "Figure.h"
#include <vector>
#include <string>


int Figure::getX() { return x; }

void Figure::setX(int _x) { x = _x; }

int Figure::getY() { return y; }

void Figure::setY(int _y) { y = _y; }

int Figure::getTeam() { return team; }

FIGURES Figure::getFigureType() { return figureType; }

sf::Sprite Figure::getSprite() { return sprite; }

void Figure::updateSprite(float _x, float _y) { sprite.setPosition(_x, _y); }

std::vector <PointInt> Figure::getAvaliableCells() { return avaliableCells; }

bool Figure::ifHasMoved() { return hasMoved; }

void Figure::updateHasMoved(bool f) { hasMoved = f; }

void Figure::horizontalSearh(int steps) {
	int dx = x, dy = y, i = 0;
	
	while (dx + 1 < 8 && i < steps) {
		if (board[dx + 1][dy] == 0) {
			avaliableCells.push_back({ dx + 1, dy });
		}
		int pos = (dx + 1) * 10 + dy;
		if (figures.find(pos) != figures.end() && figures[pos]->team != team) {
			avaliableCells.push_back({ dx + 1, dy });
			break;
		}
		if (figures.find(pos) != figures.end() && figures[pos]->team == team)
			break;
		dx++; i++;
	}

	dx = x; i = 0;

	while (dx - 1 >= 0 && i < steps) {
		if (board[dx - 1][dy] == 0) {
			avaliableCells.push_back({ dx - 1, dy });
		}
		int pos = (dx - 1) * 10 + dy;
		if (figures.find(pos) != figures.end() && figures[pos]->team != team) {
			avaliableCells.push_back({ dx - 1, dy });
			break;
		}
		if (figures.find(pos) != figures.end() && figures[pos]->team == team)
			break;
		dx--; i++;
	}
}

void Figure::verticalSearh(int steps) {
	int dx = x, dy = y, i = 0;

	while (dy + 1 < 8 && i < steps) {
		if (board[dx][dy + 1] == 0) {
			avaliableCells.push_back({ dx, dy + 1 });
		}
		int pos = dx * 10 + dy + 1;
		if (figures.find(pos) != figures.end() && figures[pos]->team != team) {
			avaliableCells.push_back({ dx, dy + 1 });
			break;
		}
		if (figures.find(pos) != figures.end() && figures[pos]->team == team)
			break;
		dy++; i++;
	}

	dy = y; i = 0;

	while (dy - 1 >= 0 && i < steps) {
		if (board[dx][dy - 1] == 0) {
			avaliableCells.push_back({ dx, dy - 1 });
		}
		int pos = dx * 10 + dy - 1;
		if (figures.find(pos) != figures.end() && figures[pos]->team != team) {
			avaliableCells.push_back({ dx, dy - 1 });
			break;
		}
		if (figures.find(pos) != figures.end() && figures[pos]->team == team)
			break;
		dy--; i++;
	}
}

void Figure::diagonalSearh(int steps) {
	int dx = x, dy = y, i = 0;

	while (dx + 1 < 8 && dy + 1 < 8 &&  i < steps) {
		if (board[dx + 1][dy + 1] == 0) {
			avaliableCells.push_back({ dx + 1, dy + 1 });
		}
		int pos = (dx + 1) * 10 + dy + 1;
		if (figures.find(pos) != figures.end() && figures[pos]->team != team) {
			avaliableCells.push_back({ dx + 1, dy + 1 });
			break;
		}
		if (figures.find(pos) != figures.end() && figures[pos]->team == team)
			break;
		dx++; dy++; i++;
	}
	
	dx = x; dy = y; i = 0;

	while (dx - 1 >= 0 && dy - 1 >= 0 && i < steps) {
		if (board[dx - 1][dy - 1] == 0) {
			avaliableCells.push_back({ dx - 1, dy - 1 });
		}
		
		int pos = (dx - 1) * 10 + dy - 1;
		if (figures.find(pos) != figures.end() && figures[pos]->team != team) {
			avaliableCells.push_back({ dx - 1, dy - 1 });
			break;
		}
		if (figures.find(pos) != figures.end() && figures[pos]->team == team)
			break;
		dx--; dy--; i++;
	}

	dx = x; dy = y; i = 0;

	while (dx + 1 < 8 && dy - 1 >= 0 && i < steps) {
		if (board[dx + 1][dy - 1] == 0) {
			avaliableCells.push_back({ dx + 1, dy - 1 });
		}
		int pos = (dx + 1) * 10 + dy - 1;
		if (figures.find(pos) != figures.end() && figures[pos]->team != team) {
			avaliableCells.push_back({ dx + 1, dy - 1 });
			break;
		}
		if (figures.find(pos) != figures.end() && figures[pos]->team == team)
			break;
		dx++; dy--; i++;
	}

	dx = x; dy = y; i = 0;

	while (dx - 1 >= 0 && dy + 1 < 8 && i < steps) {
		if (board[dx - 1][dy + 1] == 0) {
			avaliableCells.push_back({ dx - 1, dy + 1 });
		}
		int pos = (dx - 1) * 10 + dy + 1;
		if (figures.find(pos) != figures.end() && figures[pos]->team != team) {
			avaliableCells.push_back({ dx - 1, dy + 1 });
			break;
		}
		if (figures.find(pos) != figures.end() && figures[pos]->team == team)
			break;
		dx--; dy++; i++;
	}
}

void Figure::findAvaliableCells() { std::cout << "YEEEEEEEEEEEEEEEES"; }

void Figure::setPos() {
	Point p;
	p.x = float(44 + 100 * x);
	p.y = float(20 + 100 * y);
	this->sprite.setPosition(p.x, p.y);
}

void Figure::updateBoard(int _x, int _y) {
	outBoard();
	int k = board[x][y];
	board[x][y] = 0;
	board[_x][_y] =k;
	x = _x;
	y = _y;

}

void Figure::outBoard() {
	std::cout << "board\n";
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			std::cout << board[i][j] << ' ';
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}