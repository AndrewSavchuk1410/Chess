#include "Queen.h"
#include <iostream>

Queen::Queen() {}

Queen::Queen(int x, int y, FIGURES figureType, int team, sf::Sprite sprite)
	: Figure(x, y, figureType, team, sprite) {}

void Queen::findAvaliableCells() {
	int steps = 8;
	avaliableCells.resize(0);
	horizontalSearh(steps);
	verticalSearh(steps);
	diagonalSearh(steps);
}