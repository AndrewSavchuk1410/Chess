#pragma once
#include "Figure.h"
#include <SFML/Graphics.hpp>
#include "Board.h"

class Pawn : public Figure
{
public:

	Pawn();

	Pawn(int x, int y, FIGURES figureType, int team, sf::Sprite sprite);

	virtual void findAvaliableCells();
};