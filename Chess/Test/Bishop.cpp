#include "Bishop.h"

Bishop::Bishop() {}

Bishop::Bishop(int x, int y, FIGURES figureType, int team, sf::Sprite sprite)
	: Figure(x, y, figureType, team, sprite) {}

void Bishop::findAvaliableCells() {
	int steps = 8;
	avaliableCells.resize(0);
	diagonalSearh(steps);

	/*for (auto i : avaliableCells) {
		std::cout << " x = " << i.x << " y = " << i.y << '\n';
	}
	if (!avaliableCells.size())
		std::cout << "Empty";*/
}