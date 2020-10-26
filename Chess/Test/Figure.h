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


	void horizontalSearh(int steps); //   finds all cells that lie horizontally and are
									 //   reachable from position of chosen figure

	void verticalSearh(int steps);   //   finds all cells that lie vertically and are
									 //   reachable from position of chosen figure

	void diagonalSearh(int steps);   //   finds all cells that lie diagonally and are
									 //   reachable from position of chosen figure


	void setPos();
	void updateBoard(int x, int y);
	virtual void findAvaliableCells();

	void outBoard();
};
