#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include "Board.h"

class Board;

struct Point
{
	float x, y;
};

struct PointInt
{
	int x, y;
};

class Figure
{
protected:
	FIGURES figureType;
	int x, y, team;
	sf::Sprite sprite;
	std::vector <PointInt> avaliableCells;
	bool hasMoved = false;
public:
	Figure() {}

	Figure(int x, int y, FIGURES figureType, int team, sf::Sprite sprite) {
		this->x = x;
		this->y = y;
		this->team = team;
		this->figureType = figureType;
		this->sprite = sprite;
		board[x][y] = team * static_cast<int>(figureType);
		setPos();
		
	}

	static std::shared_ptr<Figure> create() {
		struct make_shared_enabler : Figure {};
		return std::make_shared<make_shared_enabler>();
	}


	int getX();
	void setX(int _x);
	int getY();
	void setY(int _y);
	int getTeam();
	FIGURES getFigureType();
	sf::Sprite getSprite();
	void updateSprite(float _x, float _y);
	std::vector <PointInt> getAvaliableCells();
	bool ifHasMoved();
	void updateHasMoved(bool f);

	void horizontalSearh(int steps);
	void verticalSearh(int steps);
	void diagonalSearh(int steps);

	void setPos();
	void updateBoard(int x, int y);
	virtual void findAvaliableCells();

	void outBoard();
};
