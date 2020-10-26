#pragma once
#include "Figure.h"
#include <SFML/Graphics.hpp>
#include "Board.h"

class Rook : public Figure
{
public:

	Rook();

	Rook(int x, int y, FIGURES figureType, int team, sf::Sprite sprite);

	virtual void findAvaliableCells();
};