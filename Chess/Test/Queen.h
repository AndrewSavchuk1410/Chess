#pragma once
#include "Figure.h"
#include <SFML/Graphics.hpp>
#include "Board.h"

class Queen : public Figure
{
public:

	Queen();

	Queen(int x, int y, FIGURES figureType, int team, sf::Sprite sprite);

	virtual void findAvaliableCells();
};

