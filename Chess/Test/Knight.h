#pragma once
#include "Figure.h"
#include "vector"
#include <SFML/Graphics.hpp>
#include "Board.h"

class Knight : public Figure
{
public:

	Knight();

	Knight(int x, int y, FIGURES figureType, int team, sf::Sprite sprite);

	void knightSearch();
	
	virtual void findAvaliableCells();
};

