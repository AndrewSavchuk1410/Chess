#pragma once
#include "Figure.h"
#include <SFML/Graphics.hpp>
#include "Board.h"

class King : public Figure
{
public:

	King();

	King(int x, int y, FIGURES figureType, int team, sf::Sprite sprite);

	virtual void findAvaliableCells();
};

