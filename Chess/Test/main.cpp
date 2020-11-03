#include <SFML/Graphics.hpp>
#include <iostream>
#include "Figure.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Pawn.h"
#include <map>
#include <iterator>
#include <memory>
#include "Connector.hpp"
#include <cstdlib>


//////////////////////////////////////////////////////////////////////
//																	//
//																	//
//																	//
//																	//
//					  Developed by Andrew Savchuk					//
//																	//
//					 e-mail: andriy2000hh@gmail.com					//
//																	//
//																	//
//																	//
//																	//
//////////////////////////////////////////////////////////////////////


std::vector <int> convertedY = {7, 6, 5, 4, 3, 2, 1, 0};
std::vector<std::vector<int>> board(8, std::vector<int>(8, 0));
std::map<int, std::shared_ptr<Figure>> figures;

enum class FIGURES {
	ROOK = 1,
	KNIGHT = 2,
	BISHOP = 3,
	QUEEN = 4,
	KING = 5,
	PAWN = 6
};
	
enum class COMMANDS {
	QUIT,
	PLAY_AGAIN,
	PLAY_AGAIN_COMPUTER,
	VS_PLAYER,
	VS_COMPUTER,
	MENU
};

enum class STATE {
	CHECK,
	CHECKMATE,
	OK
};

using namespace sf;

bool operator==(const PointInt& p1, const PointInt& p2) {
	if (p1.x == p2.x && p1.y == p2.y) return true;
	else return false;
}

const float width = 840, height = 840;
Vector2f targetSize(width, height);
Vector2f offset(0, 0);

void changeSpriteScale(Sprite& sprite) {
	sprite.setScale(
		(targetSize.x / 12) / sprite.getLocalBounds().width,
		(targetSize.y / 12) / sprite.getLocalBounds().height);
}

void updateFigurs(int x, int y, int newX, int newY) {
	int newPos = newX * 10 + newY;
	int pos = x * 10 + y;
	figures[newPos] = figures[pos];
	figures.erase(pos);
}

PointInt findIntPoint(Vector2i pos) {
	PointInt p;
	p.x = int((pos.x - 40) / 100);
	p.y = int((pos.y - 40) / 100);
	return p;
}

void setPos(sf::Sprite &sprite, int x, int y) {
	Point p;
	p.x = float(30 + 100 * x);
	p.y = float(7 + 100 * y);
	sprite.setPosition(p.x, p.y);
}

std::string toChessNote(int x, int y)
{
	std::string s = "";
	s += char(x + 97);
	s += char(convertedY[y] + 49);
	return s;
}

Vector2i toCoord(char a, char b)
{
	int x = int(a) - 97;
	int y = 7 - (7 - int(b) + 49);
	//std::cout << "Y " << y << '\n';
	y = convertedY[y];
	return Vector2i(x, y);
}

std::vector<PointInt> getAllMoves(int team) { //finds all moves that enemy team can make
	std::vector<PointInt> allMoves;

	for (auto i : figures) {
		if (i.second->getTeam() != team) {
			i.second->findAvaliableCells();
			for (auto j : i.second->getAvaliableCells()) {
				allMoves.push_back(j);
			}
		}
	}
	return allMoves;
}

std::vector<PointInt> getAllMovesWithNoKing(int team) { //finds all moves that enemy team can make, if there is enemy king on the board
	int x, y;

	for (auto it : figures) {
		if (it.second->getFigureType() == FIGURES::KING && it.second->getTeam() == team) {
			x = it.second->getX();
			y = it.second->getY();
			break;
		}
	}

	int pos = x * 10 + y;
	auto king = figures[pos];
	int posValue = board[x][y];
	board[x][y] = 0;
	figures.erase(pos);

	std::vector<PointInt> allMoves = getAllMoves(team);

	figures[pos] = (king);
	board[x][y] = posValue;
	
	return allMoves;
}

STATE checkOrCheckmate(int team) {
	int x, y;
	
	for (auto it : figures) {
		if (it.second->getFigureType() == FIGURES::KING && it.second->getTeam() == team) {
			x = it.second->getX();
			y = it.second->getY();
			break;
		}
	}

	int pos = x * 10 + y;
	auto king = figures[pos];
	king->findAvaliableCells();
	auto kingMoves = king->getAvaliableCells();
	
	for (auto J : figures)
		std::cout << J.first << ' ';
	std::cout << '\n';

	std::vector<PointInt> allMoves = getAllMovesWithNoKing(team);

	for (auto J : figures)
		std::cout << J.first << ' ';
	std::cout << std::endl;

	PointInt p = { king->getX(), king->getY() };

	if (std::find(allMoves.begin(), allMoves.end(), p) == allMoves.end()) {
		return STATE::OK;
	}

	bool check1 = false;
	for (auto j : kingMoves) {
		if (std::find(allMoves.begin(), allMoves.end(), j) == allMoves.end()) {
			check1 = true;
		}
	}

	if (check1) return STATE::CHECK;

	PointInt kingPos = { x, y }; // king`s x and y
	for (auto it : figures) {
		if (it.second->getTeam() == team) {
			it.second->findAvaliableCells();
			
			for (auto i : it.second->getAvaliableCells()) {
				bool check2 = false;
				int posValue = board[i.x][i.y];
				int oldX = it.second->getX();
				int oldY = it.second->getY();
				int oldPos = oldX * 10 + oldY;
				int newPos = i.x * 10 + i.y;

				/*std::shared_ptr<Figure> someFigure = nullptr; //save the figure that we are going delete temporarily
				if (figures[newPos] != nullptr) {
					someFigure = figures[newPos];
				}*/

				std::map<const int, std::shared_ptr<Figure>>::iterator n;
				
				/*n = figures.lower_bound(oldPos);
				updateFigurs(n->second->getX(), n->second->getY(), i.x, i.y);
				n = figures.lower_bound(newPos);
				n->second->updateBoard(i.x, i.y);*/


				allMoves = getAllMoves(team);
				
				if (std::find(allMoves.begin(), allMoves.end(), kingPos) == allMoves.end())
					check2 = true;

				/*updateFigurs(n->second->getX(), n->second->getY(), oldX, oldY);
				n = figures.lower_bound(oldPos);
				n->second->updateBoard(oldX, oldY);

				if (someFigure != nullptr)
					figures[newPos] = someFigure;

				board[i.x][i.y] = posValue;
				//std::cout << it.first << '\n';*/
				if (check2) return STATE::CHECK;
			}
		}
	}
	if (!check1)
		return STATE::CHECKMATE;
	else
		return STATE::CHECK;
}


COMMANDS playGame(bool versusComputer = false) {
	
	char path[14] = "stockfish.exe";
	ConnectToEngine(path);

	figures.clear();

	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			board[i][j] = 0;
		}
	}

	RenderWindow window(VideoMode(width + 400, height), "Chess", sf::Style::Close);
	Texture _board, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, whitesTurn, blacksTurn,
		menu, playAgain, quit, prompt;
	
	//   load textures
	_board.loadFromFile("images/Board.png");
	whitesTurn.loadFromFile("images/WHITES_TURN.png");
	blacksTurn.loadFromFile("images/BLACKS_TURN.png");
	menu.loadFromFile("images/MENU.png");
	quit.loadFromFile("images/QUIT.png");
	playAgain.loadFromFile("images/PLAY_AGAIN.png");
	prompt.loadFromFile("images/prompt.png");

	t1.loadFromFile("images/KingWhite.png");
	t2.loadFromFile("images/QueenWhite.png");			
	t3.loadFromFile("images/BishopWhite.png");
	t4.loadFromFile("images/KnightWhite.png");
	t5.loadFromFile("images/RookWhite.png");
	t6.loadFromFile("images/PawnWhite.png");
	t7.loadFromFile("images/KingBlack.png");
	t8.loadFromFile("images/QueenBlack.png");
	t9.loadFromFile("images/BishopBlack.png");
	t10.loadFromFile("images/KnightBlack.png");
	t11.loadFromFile("images/RookBlack.png");
	t12.loadFromFile("images/PawnBlack.png");

	whitesTurn.setSmooth(true);
	blacksTurn.setSmooth(true);
	menu.setSmooth(true);
	playAgain.setSmooth(true);
	prompt.setSmooth(true);
	t1.setSmooth(true);
	t2.setSmooth(true);
	t3.setSmooth(true);
	t4.setSmooth(true);
	t5.setSmooth(true);
	t6.setSmooth(true);
	t7.setSmooth(true);
	t8.setSmooth(true);
	t9.setSmooth(true);
	t10.setSmooth(true);
	t11.setSmooth(true);
	t12.setSmooth(true);

	// create sprites

	Sprite sBoard(_board);
	sBoard.setScale(
		(targetSize.x) / sBoard.getLocalBounds().width,
		(targetSize.y) / sBoard.getLocalBounds().height);

	Sprite sWhitesTurn(whitesTurn);
	Sprite sBlacksTurn(blacksTurn);

	sWhitesTurn.setPosition(840 + (400 - sWhitesTurn.getGlobalBounds().width) / 2,
		600 + (200 - sWhitesTurn.getGlobalBounds().height) / 2);

	sBlacksTurn.setPosition(840 + (400 - sBlacksTurn.getGlobalBounds().width) / 2,
		(200 - sBlacksTurn.getGlobalBounds().height) / 2);


	Sprite sMenu(menu);
	Sprite sPlayAgain(playAgain);
	Sprite sQuit(quit);

	sMenu.setPosition(840 + (400 - sMenu.getGlobalBounds().width) / 2,
		 (400 + sMenu.getGlobalBounds().height) / 2);

	sPlayAgain.setPosition(840 + (400 - sPlayAgain.getGlobalBounds().width) / 2,
		370 + (400 - sPlayAgain.getGlobalBounds().height) / 2);

	sQuit.setPosition(840 + (400 - sQuit.getGlobalBounds().width) / 2,
		(550 + sQuit.getGlobalBounds().height) / 2);

	Sprite KingWhite(t1);
	changeSpriteScale(KingWhite);

	Sprite QueenWhite(t2);
	changeSpriteScale(QueenWhite);

	Sprite BishopWhite(t3);
	changeSpriteScale(BishopWhite);

	Sprite KnightWhite(t4);
	changeSpriteScale(KnightWhite);

	Sprite RookWhite(t5);
	changeSpriteScale(RookWhite);

	Sprite PawnWhite(t6);
	changeSpriteScale(PawnWhite);

	Sprite KingBlack(t7);
	changeSpriteScale(KingBlack);

	Sprite QueenBlack(t8);
	changeSpriteScale(QueenBlack);

	Sprite BishopBlack(t9);
	changeSpriteScale(BishopBlack);

	Sprite KnightBlack(t10);
	changeSpriteScale(KnightBlack);

	Sprite RookBlack(t11);
	changeSpriteScale(RookBlack);

	Sprite PawnBlack(t12);
	changeSpriteScale(PawnBlack);


	// make map of all figures

	/*for (int i = 0; i < 8; i++) {
		Pawn WhitePawn(i, 6, FIGURES::PAWN, 1, PawnWhite);
		figures[(i * 10 + 6)] = std::make_shared<Pawn>(WhitePawn);
	}*/

	Rook WhiteLeftRook(0, 7, FIGURES::ROOK, 1, RookWhite);
	figures[7] = std::make_shared<Rook>(WhiteLeftRook);
	Rook WhiteRightRook(7, 7, FIGURES::ROOK, 1, RookWhite);
	figures[77] = std::make_shared<Rook>(WhiteRightRook);

	Knight WhiteLeftKnight(1, 7, FIGURES::KNIGHT, 1, KnightWhite);
	figures[17] = std::make_shared<Knight>(WhiteLeftKnight);
	Knight WhiteRightKnight(6, 7, FIGURES::KNIGHT, 1, KnightWhite);
	figures[67] = std::make_shared<Knight>(WhiteRightKnight);

	Bishop WhiteLeftBishop(2, 7, FIGURES::BISHOP, 1, BishopWhite);
	figures[27] = std::make_shared<Bishop>(WhiteLeftBishop);
	Bishop WhiteRightBishop(5, 7, FIGURES::BISHOP, 1, BishopWhite);
	figures[57] = std::make_shared<Bishop>(WhiteRightBishop);

	Queen WhiteQueen(3, 7, FIGURES::QUEEN, 1, QueenWhite);
	figures[37] = std::make_shared<Queen>(WhiteQueen);
	King WhiteKing(4, 7, FIGURES::KING, 1, KingWhite);
	figures[47] = std::make_shared<King>(WhiteKing);

	/*for (int i = 0; i < 8; i++) {
		Pawn BlackPawn(i, 1, FIGURES::PAWN, -1, PawnBlack);
		figures[(i * 10 + 1)] = std::make_shared<Pawn>(BlackPawn);
	}

	Rook BlackLeftRook(0, 0, FIGURES::ROOK, -1, RookBlack);
	figures[0] = std::make_shared<Rook>(BlackLeftRook);
	Rook BlackRightRook(7, 0, FIGURES::ROOK, -1, RookBlack);
	figures[70] = std::make_shared<Rook>(BlackRightRook);

	Knight BlackLeftKnight(1, 0, FIGURES::KNIGHT, -1, KnightBlack);
	figures[10] = std::make_shared<Knight>(BlackLeftKnight);
	Knight BlackRightKnight(6, 0, FIGURES::KNIGHT, -1, KnightBlack);
	figures[60] = std::make_shared<Knight>(BlackRightKnight);

	Bishop BlackLeftBishop(2, 0, FIGURES::BISHOP, -1, BishopBlack);
	figures[20] = std::make_shared<Bishop>(BlackLeftBishop);
	Bishop BlackRightBishop(5, 0, FIGURES::BISHOP, -1, BishopBlack);
	figures[50] = std::make_shared<Bishop>(BlackRightBishop);*/

	Queen BlackQueen(3, 0, FIGURES::QUEEN, -1, QueenBlack);
	figures[30] = std::make_shared<Queen>(BlackQueen);
	King BlackKing(4, 0, FIGURES::KING, -1, KingBlack);
	figures[40] = std::make_shared<King>(BlackKing);



	bool isMove = false, correctClick = false, victoryAchived = false, showTurn = 1,
		showPrompts = false;
	float dx = 0, dy = 0;
	Vector2f oldPos, newPos;
	Vector2i oldPos2, newPos2;
	std::map<const int, std::shared_ptr<Figure>>::iterator n;
	int team = 1, winTeam = 0;
	COMMANDS nextCommand = COMMANDS::QUIT;
	std::vector <PointInt> prompts;
	std::string position = "";


	while (window.isOpen())
	{

		// AI move
		if (versusComputer && team == -1 && !victoryAchived) {
			

			// find enemy king position to find out
			// if there is checkmate

			//find king position
			Vector2i kingPos; 
			for (auto i : figures) {
				if (i.second->getFigureType() == FIGURES::KING
					&& i.second->getTeam() == 1) {
					kingPos.x = i.second->getX();
					kingPos.y = i.second->getY();
				}
			}

			//find out if there is a checkmate
			for (auto i : figures) {
				if (i.second->getTeam() == -1) {
					i.second->findAvaliableCells();
					std::vector <PointInt> cells = i.second->getAvaliableCells();
					for (auto j : cells) {
						if (j.x == kingPos.x && j.y == kingPos.y) {
							victoryAchived = true;
							winTeam = -1;
							break;
						}
					}
				}
				if (victoryAchived) break;
			}

			//if there was not checkmate, make AI move

			if (!victoryAchived) {
				std::string s = getNextMove(position); //get AI move
				if (s == "error") {
					victoryAchived = true;
					winTeam = 1;
					continue;
				}
				//std::string s = "e8c8";
				oldPos2 = toCoord(s[0], s[1]);
				newPos2 = toCoord(s[2], s[3]);

				if (oldPos2.x == 4 && oldPos2.y == 0 && newPos2.x == 6 && newPos2.y == 0) {
					int KingNewPos = (newPos2.x) * 10 + newPos2.y;
					int RookNewPos = (newPos2.x - 1) * 10 + newPos2.y;
					
					updateFigurs(oldPos2.x, oldPos2.y, newPos2.x, newPos2.y);
					updateFigurs(7, 0, newPos2.x - 1, newPos2.y);

					auto chosenKing = figures.lower_bound(KingNewPos);
					auto chosenRook = figures.lower_bound(RookNewPos);

					chosenKing->second->updateBoard(newPos2.x, newPos2.y);
					chosenKing->second->setPos();
					chosenRook->second->updateBoard(newPos2.x - 1, newPos2.y);
					chosenRook->second->setPos();
				}
				else if (oldPos2.x == 4 && oldPos2.y == 0 && newPos2.x == 2 && newPos2.y == 0) {
					int KingNewPos = (newPos2.x) * 10 + newPos2.y;
					int RookNewPos = (newPos2.x + 1) * 10 + newPos2.y;

					updateFigurs(oldPos2.x, oldPos2.y, newPos2.x, newPos2.y);
					updateFigurs(0, 0, newPos2.x + 1, newPos2.y);

					auto chosenKing = figures.lower_bound(KingNewPos);
					auto chosenRook = figures.lower_bound(RookNewPos);

					chosenKing->second->updateBoard(newPos2.x, newPos2.y);
					chosenKing->second->setPos();
					chosenRook->second->updateBoard(newPos2.x + 1, newPos2.y);
					chosenRook->second->setPos();
				}
				else {
					int pos2 = newPos2.x * 10 + newPos2.y; // compute new key for figure

					updateFigurs(oldPos2.x, oldPos2.y, newPos2.x, newPos2.y);
					auto chosenFigure = figures.lower_bound(pos2);

					chosenFigure->second->updateBoard(newPos2.x, newPos2.y);
					chosenFigure->second->setPos();
				}
				position += (s + ' '); 
				std::cout << position << '\n';
				team = 1;
			}
		}

		Vector2i pos = Mouse::getPosition(window) - Vector2i(offset);


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left) {
					auto it = figures.begin();
					for (int i = 0; i < figures.size(); i++) { // find out what figure choose player
						if (it->second->getSprite().getGlobalBounds().contains(pos.x, pos.y))
						{
							std::cout << "left and top: " << it->second->getSprite().getGlobalBounds().left
								<< ' ' << it->second->getSprite().getGlobalBounds().top << ' '
								<< "Mouse x and y: " << pos.x << ' ' << pos.y << " Sprite x and y: "
								<< it->second->getSprite().getPosition().x <<
								' ' << it->second->getSprite().getPosition().y << '\n';

							// check if the chosen figure`s team equal equal to team,
							//which must make a move
							if (team == it->second->getTeam()) {
								isMove = true; n = it;
								oldPos2.x = n->second->getX();
								oldPos2.y = n->second->getY();
								dx = pos.x - it->second->getSprite().getPosition().x;
								dy = pos.y - it->second->getSprite().getPosition().y;
								oldPos = it->second->getSprite().getPosition();
								correctClick = true;
							}
						}
						it++;
					}
					
					// quit
					if (sQuit.getGlobalBounds().contains(pos.x, pos.y)) {
						window.close();
						nextCommand = COMMANDS::QUIT;
						return nextCommand;
					}

					//this botton will appear after checkmate
					if (sPlayAgain.getGlobalBounds().contains(pos.x, pos.y) && victoryAchived) {
						window.close();
						nextCommand = (versusComputer) ? COMMANDS::PLAY_AGAIN_COMPUTER 
							: COMMANDS::PLAY_AGAIN;
						CloseConnection();
						return nextCommand;
					}

					//back to menu
					if (sMenu.getGlobalBounds().contains(pos.x, pos.y)) {
						window.close();
						nextCommand = COMMANDS::MENU;
						CloseConnection();
						return nextCommand;
					}

				}

			if (event.type == Event::MouseButtonReleased)
				if (event.key.code == Mouse::Left) {
					if ((correctClick) && !victoryAchived) {
						PointInt p = findIntPoint(pos);
						n->second->findAvaliableCells(); //find all cells, that are reachable from
														 //chosen figure position
						bool f = false;
						for (auto j : n->second->getAvaliableCells()) {
							if (j.x == p.x && j.y == p.y) {
								f = true; // if position whith choose player is in vector of 
										  // reacheble cells
								break;

							}
						}

						if (f)
						{

							if (n->second->getFigureType() == FIGURES::KING && std::abs(oldPos2.x - p.x) > 1) {
								if (team == 1) {
									if (p.x == 6) {
										int KingNewPos = (p.x) * 10 + p.y;
										int RookNewPos = (p.x - 1) * 10 + p.y;

										updateFigurs(oldPos2.x, oldPos2.y, p.x, p.y);
										updateFigurs(7, 7, p.x - 1, p.y);
										std::cout << "YES";
										auto chosenKing = figures.lower_bound(KingNewPos);
										auto chosenRook = figures.lower_bound(RookNewPos);
										chosenKing->second->updateHasMoved(true);
										chosenRook->second->updateHasMoved(true);

										chosenKing->second->updateBoard(p.x, p.y);
										chosenKing->second->setPos();
										chosenRook->second->updateBoard(p.x - 1, p.y);
										chosenRook->second->setPos();
										n = figures.lower_bound(KingNewPos);
									}
									else if (p.x == 2) {
										int KingNewPos = (p.x) * 10 + p.y;
										int RookNewPos = (p.x + 1) * 10 + p.y;

										updateFigurs(oldPos2.x, oldPos2.y, p.x, p.y);
										updateFigurs(0, 7, p.x + 1, p.y);
										std::cout << "YES2";
										auto chosenKing = figures.lower_bound(KingNewPos);
										auto chosenRook = figures.lower_bound(RookNewPos);
										chosenKing->second->updateHasMoved(true);
										chosenRook->second->updateHasMoved(true);

										chosenKing->second->updateBoard(p.x, p.y);
										chosenKing->second->setPos();
										chosenRook->second->updateBoard(p.x + 1, p.y);
										chosenRook->second->setPos();
										n = figures.lower_bound(KingNewPos);
									}
								}
								else if (team == -1) {
									if (p.x == 6) {
										int KingNewPos = (p.x) * 10 + p.y;
										int RookNewPos = (p.x - 1) * 10 + p.y;

										updateFigurs(oldPos2.x, oldPos2.y, p.x, p.y);
										updateFigurs(7, 0, p.x - 1, p.y);
										std::cout << "YES";
										auto chosenKing = figures.lower_bound(KingNewPos);
										auto chosenRook = figures.lower_bound(RookNewPos);
										chosenKing->second->updateHasMoved(true);
										chosenRook->second->updateHasMoved(true);

										chosenKing->second->updateBoard(p.x, p.y);
										chosenKing->second->setPos();
										chosenRook->second->updateBoard(p.x - 1, p.y);
										chosenRook->second->setPos();
										n = figures.lower_bound(KingNewPos);
									}
									else if (p.x == 2) {
										int KingNewPos = (p.x) * 10 + p.y;
										int RookNewPos = (p.x + 1) * 10 + p.y;

										updateFigurs(oldPos2.x, oldPos2.y, p.x, p.y);
										updateFigurs(0, 0, p.x + 1, p.y);
										std::cout << "YES2";
										auto chosenKing = figures.lower_bound(KingNewPos);
										auto chosenRook = figures.lower_bound(RookNewPos);
										chosenKing->second->updateHasMoved(true);
										chosenRook->second->updateHasMoved(true);

										chosenKing->second->updateBoard(p.x, p.y);
										chosenKing->second->setPos();
										chosenRook->second->updateBoard(p.x + 1, p.y);
										chosenRook->second->setPos();
										n = figures.lower_bound(KingNewPos);
									}
								}
							}
							else {
								int pos = p.x * 10 + p.y;
								//if one of players(not AI) made checkmate
								if (figures[pos] != nullptr &&
									figures[pos]->getFigureType() == FIGURES::KING) {
									victoryAchived = true;
									showTurn = false;
									winTeam = n->second->getTeam();
								}
								updateFigurs(n->second->getX(), n->second->getY(), p.x, p.y);

								n = figures.lower_bound(pos);
								n->second->updateBoard(p.x, p.y);
								n->second->updateHasMoved(true);

								n->second->setPos();
								if (n->second->getFigureType() == FIGURES::PAWN && !n->second->ifHasMoved()) {
									n->second->updateHasMoved(true);
								}
							}

							if (n->second->getTeam() == 1) team = -1; // change turn to make move
							else team = 1;
							showPrompts = false; // the move is correct, dont need to show prompts
							
							STATE state = checkOrCheckmate(team);
							if (state == STATE::OK)
								std::cout << "OK\n";
							else if (state == STATE::CHECK)
								std::cout << "CHECK\n";
							else
								std::cout << "CHECKMATE\n";

							//add move to comutation string for AI
							if (versusComputer)
								position += (toChessNote(oldPos2.x, oldPos2.y)
								+ toChessNote(n->second->getX(), n->second->getY()) + ' ');
						}
						else
						{
							n->second->updateSprite(oldPos.x, oldPos.y); // moves sprite to it old
																		 // position
							prompts = n->second->getAvaliableCells();    // find prompts
							showPrompts = true;
						}
						isMove = false;
						correctClick = false;
					}
				}

			//moves sprite
			if (isMove && !victoryAchived) n->second->updateSprite(pos.x - dx, pos.y - dy);

		}


		sf::Color color(49, 46, 43);
		window.clear(color);
		window.draw(sBoard);

		//if the player made mistake, shows prompts
		if (showPrompts && !prompts.empty()) {
			for (auto j : prompts) {
				Sprite sPrompt(prompt);
				setPos(sPrompt, j.x, j.y);
				window.draw(sPrompt);
			}
		}


		//shows turn
		if (showTurn) {
			if (team == 1)
				window.draw(sWhitesTurn);
			else if (team == -1 && !versusComputer)
				window.draw(sBlacksTurn);
		}

		//shows figurs on the board
		auto it = figures.begin();
		for (int i = 0; i < figures.size(); i++) {
			window.draw(it->second->getSprite());
			it++;
		}

		//shows who won and shows victory menu
		if (victoryAchived) {
			Texture victoryT;
			if (winTeam == 1)
				victoryT.loadFromFile("images/WHITES_VICTORY.png");
			if (winTeam == -1)
				victoryT.loadFromFile("images/BLACKS_VICTORY.png");
			victoryT.setSmooth(true);
			Sprite victoryS(victoryT);
		
			victoryS.setPosition(840 + (400 - victoryS.getGlobalBounds().width) / 2,
				(600 - victoryS.getGlobalBounds().height) / 2);
			window.draw(victoryS);
			sMenu.setPosition(840 + (400 - sMenu.getGlobalBounds().width) / 2,
				270 + (400 - sMenu.getGlobalBounds().height) / 2);
			window.draw(sMenu);
			window.draw(sPlayAgain);
			sQuit.setPosition(840 + (400 - sQuit.getGlobalBounds().width) / 2,
				470 + (400 - sQuit.getGlobalBounds().height) / 2);
			
			
		}
		
		window.draw(sQuit);
		window.draw(sMenu);
		window.display();
	}
	CloseConnection();
	return nextCommand;
}

COMMANDS startMenu() {
	RenderWindow window(VideoMode(900, 600), "Menu", sf::Style::Close);
	Texture backGround, quit, vsPlayer, vsComputer, chess;
	COMMANDS nextCommand = COMMANDS::QUIT;

	backGround.loadFromFile("images/BACKGROUND.png");
	vsPlayer.loadFromFile("images/VS_PLAYER.png");
	vsComputer.loadFromFile("images/VS_COMPUTER.png");
	quit.loadFromFile("images/QUIT.png");
	chess.loadFromFile("images/CHESS.png");

	backGround.setSmooth(true);
	vsPlayer.setSmooth(true);
	vsComputer.setSmooth(true);
	quit.setSmooth(true);
	chess.setSmooth(true);

	Sprite sBackGround(backGround);
	Sprite sVsPlayer(vsPlayer);
	Sprite sVsComputer(vsComputer);
	Sprite sQuit(quit);
	Sprite sChess(chess);

	sChess.setPosition((900 - sChess.getGlobalBounds().width) / 2,
		(-20 + sChess.getGlobalBounds().height) / 2);

	sVsPlayer.setPosition((900 - sVsPlayer.getGlobalBounds().width) / 2,
		(240 + sVsPlayer.getGlobalBounds().height) / 2);

	sVsComputer.setPosition((900 - sVsComputer.getGlobalBounds().width) / 2,
		(390 + sVsComputer.getGlobalBounds().height) / 2);

	sQuit.setPosition((900 - sQuit.getGlobalBounds().width) / 2,
		(54 * 10 + sQuit.getGlobalBounds().height) / 2);
	//Sprite sBackGround(backGround);

	while (window.isOpen())
	{
		Vector2i pos = Mouse::getPosition(window) - Vector2i(offset);
		Event event;

		int a = 0;
		/*if (a == 1000) {
			std::cout << pos.x << ' ' << pos.y << ' ' << sQuit.getGlobalBounds().left 
				<< ' ' << sQuit.getGlobalBounds().top << ' ' 
				<< sQuit.getGlobalBounds().width << ' ' << sQuit.getGlobalBounds().height <<  '\n';
			a = 0;
			
		} a++;*/


		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			
				if (event.type == Event::MouseButtonPressed) {
					
					//quit
					if (event.key.code == Mouse::Left) {
						if (sQuit.getGlobalBounds().contains(pos.x, pos.y)) {
							window.close();
							nextCommand = COMMANDS::QUIT;
							return nextCommand;
						}

						//play versus player
						if (sVsPlayer.getGlobalBounds().contains(pos.x, pos.y)) {
							window.close();
							nextCommand = COMMANDS::VS_PLAYER;
							return nextCommand;
						}

						//play versus AI
						if (sVsComputer.getGlobalBounds().contains(pos.x, pos.y)) {
							window.close();
							nextCommand = COMMANDS::VS_COMPUTER;
							return nextCommand;
						}

						if (event.type == Event::Closed) {
							window.close();
							nextCommand = COMMANDS::QUIT;
							return nextCommand;
						}
					}
				}

				
		}
		window.clear();
		window.draw(sBackGround);
		window.draw(sChess);
		window.draw(sVsPlayer);
		window.draw(sVsComputer);
		window.draw(sQuit);
		window.display();
	}

	

	return nextCommand;
}

int main()
{
	//starts menu
	COMMANDS nextCommand;
	nextCommand = startMenu();

	//program
	while (nextCommand != COMMANDS::QUIT) {
		if (nextCommand == COMMANDS::VS_PLAYER)
			nextCommand = playGame();
		if (nextCommand == COMMANDS::MENU)
			nextCommand = startMenu();
		if (nextCommand == COMMANDS::PLAY_AGAIN)
			nextCommand = playGame();
		if (nextCommand == COMMANDS::VS_COMPUTER)
			nextCommand = playGame(true);
		if (nextCommand == COMMANDS::PLAY_AGAIN_COMPUTER)
			nextCommand = playGame(true);
	}
}