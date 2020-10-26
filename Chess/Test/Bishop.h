#pragma once
#include "Figure.h"
#include "Board.h"
#include <SFML/Graphics.hpp>

class Bishop : public Figure
{
public:

	Bishop();

	Bishop(int x, int y, FIGURES figureType, int team, sf::Sprite sprite);

	virtual void findAvaliableCells();
};