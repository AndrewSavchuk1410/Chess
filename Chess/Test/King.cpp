#include "King.h"
#include <iostream>

King::King() {}

King::King(int x, int y, FIGURES figureType, int team, sf::Sprite sprite)
	: Figure(x, y, figureType, team, sprite) {}

void King::findAvaliableCells() {
	int steps = 1;
	avaliableCells.resize(0);
	horizontalSearh(steps);
	verticalSearh(steps);
	diagonalSearh(steps);

	/*for (auto i : avaliableCells) {
		std::cout << " x = " << i.x << " y = " << i.y << '\n';
	}
	if (!avaliableCells.size())
		std::cout << "Empty";*/
}