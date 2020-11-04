#include "Rook.h"

Rook::Rook() {}

Rook::Rook(int x, int y, FIGURES figureType, int team, sf::Sprite sprite)
	: Figure(x, y, figureType, team, sprite) {}

void Rook::findAvaliableCells() {
	int steps = 8;
	avaliableCells.resize(0);
	horizontalSearh(steps);
	verticalSearh(steps);
	/*std::cout << "ROOK\n";
	for (auto i : avaliableCells) {
		std::cout << " x = " << i.x << " y = " << i.y << '\n';
	}
	if (!avaliableCells.size())
		std::cout << "Empty";*/

}
