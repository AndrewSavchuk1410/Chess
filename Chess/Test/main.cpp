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

using namespace sf;

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


	for (int i = 0; i < 8; i++) {
		Pawn WhitePawn(i, 6, FIGURES::PAWN, 1, PawnWhite);
		figures[(i * 10 + 6)] = std::make_shared<Pawn>(WhitePawn);
	}

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

	//WhiteKing.outBoard();

	for (int i = 0; i < 8; i++) {
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
	figures[50] = std::make_shared<Bishop>(BlackRightBishop);

	Queen BlackQueen(3, 0, FIGURES::QUEEN, -1, QueenBlack);
	figures[30] = std::make_shared<Queen>(BlackQueen);
	King BlackKing(4, 0, FIGURES::KING, -1, KingBlack);
	figures[40] = std::make_shared<King>(BlackKing);



	/*for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			std::cout << board[i][j] << ' ';
		}
		std::cout << '\n';
	}*/

	/*for (auto it : figures) {
		std::cout << it.second.x << ' ' << it.second.y << ' '
			<< it.second.name << ' ' << it.second.sprite.getPosition().x <<
			' ' << it.second.sprite.getPosition().y << '\n';
	}*/

	bool isMove = false, correctClick = false, victoryAchived = false, showTurn = 1,
		showPrompts = false;
	float dx = 0, dy = 0;
	Vector2f oldPos, newPos;
	Vector2i oldPos2, newPos2;
	std::map<const int, std::shared_ptr<Figure>>::iterator n;
	int team = 1, winTeam = 0;
	COMMANDS nextCommand = COMMANDS::QUIT;
	std::vector <PointInt> prompts;
	std::string position = "", prevS = "";

	int a = 0;
	while (window.isOpen())
	{

		if (versusComputer && team == -1 && !victoryAchived) {
			
			Vector2i kingPos;
			for (auto i : figures) {
				if (i.second->getFigureType() == FIGURES::KING
					&& i.second->getTeam() == 1) {
					kingPos.x = i.second->getX();
					kingPos.y = i.second->getY();
				}
			}

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

			if (!victoryAchived) {
				std::string s = getNextMove(position);
				oldPos2 = toCoord(s[0], s[1]);
				newPos2 = toCoord(s[2], s[3]);

				int pos2 = newPos2.x * 10 + newPos2.y;
				updateFigurs(oldPos2.x, oldPos2.y, newPos2.x, newPos2.y);
				auto choosenFigure = figures.lower_bound(pos2);
				position += (s + ' ');
				//std::cout << "Position: " << position << '\n';
				//std::cout << " YEEEEEEEEES " << newPos2.x << ' ' << newPos2.y << '\n';

				choosenFigure->second->updateBoard(newPos2.x, newPos2.y);

				choosenFigure->second->setPos();

				team = 1;
				prevS = s;
			}
		}

		Vector2i pos = Mouse::getPosition(window) - Vector2i(offset);
		if (a == 1000) {
			//std::cout << pos.x << ' ' << pos.y << '\n';
			a = 0;
		} a++;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left) {
					auto it = figures.begin();
					for (int i = 0; i < figures.size(); i++) {
						if (it->second->getSprite().getGlobalBounds().contains(pos.x, pos.y))
						{
							std::cout << "left and top: " << it->second->getSprite().getGlobalBounds().left
								<< ' ' << it->second->getSprite().getGlobalBounds().top << ' '
								<< "Mouse x and y: " << pos.x << ' ' << pos.y << " Sprite x and y: "
								<< it->second->getSprite().getPosition().x <<
								' ' << it->second->getSprite().getPosition().y << '\n';

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

					if (sQuit.getGlobalBounds().contains(pos.x, pos.y)) {
						window.close();
						nextCommand = COMMANDS::QUIT;
						return nextCommand;
					}

					if (sPlayAgain.getGlobalBounds().contains(pos.x, pos.y) && victoryAchived) {
						window.close();
						nextCommand = (versusComputer) ? COMMANDS::PLAY_AGAIN_COMPUTER 
							: COMMANDS::PLAY_AGAIN;
						CloseConnection();
						return nextCommand;
					}

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
						n->second->findAvaliableCells();
						bool f = false;
						for (auto j : n->second->getAvaliableCells()) {
							if (j.x == p.x && j.y == p.y) {
								f = true;
								//std::cout << "YEEEEEEEEEEEEEEEEEEES\n";
								break;

							}
						}

						if (f)
						{
							if (n->second->getTeam() == 1) team = -1;
							else team = 1;
							int pos = p.x * 10 + p.y;
							if (figures[pos] != nullptr &&
								figures[pos]->getFigureType() == FIGURES::KING) {
								victoryAchived = true; 
								showTurn = false;
								winTeam = n->second->getTeam();
							}
							updateFigurs(n->second->getX(), n->second->getY(), p.x, p.y);

							n = figures.lower_bound(pos);
							n->second->updateBoard(p.x, p.y);
							
							n->second->setPos();
							if (n->second->getFigureType() == FIGURES::PAWN && !n->second->ifHasMoved()) {
								n->second->updateHasMoved(true);
							}

							showPrompts = false;
							//n->second->outBoard();
							
							if (versusComputer)
								position += (toChessNote(oldPos2.x, oldPos2.y)
								+ toChessNote(n->second->getX(), n->second->getY()) + ' ');
						}
						else
						{
							n->second->updateSprite(oldPos.x, oldPos.y);
							prompts = n->second->getAvaliableCells();
							showPrompts = true;
						}
						isMove = false;
						correctClick = false;
					}
				}

			if (isMove && !victoryAchived) n->second->updateSprite(pos.x - dx, pos.y - dy);

		}


		sf::Color color(49, 46, 43);
		window.clear(color);
		window.draw(sBoard);

		if (showPrompts && !prompts.empty()) {
			for (auto j : prompts) {
				Sprite sPrompt(prompt);
				setPos(sPrompt, j.x, j.y);
				window.draw(sPrompt);
			}
		}


		if (showTurn) {
			if (team == 1)
				window.draw(sWhitesTurn);
			else if (team == -1 && !versusComputer)
				window.draw(sBlacksTurn);
		}

		auto it = figures.begin();
		for (int i = 0; i < figures.size(); i++) {
			window.draw(it->second->getSprite());
			it++;
		}

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
		//window.draw(WhiteKing.sprite);
		//std::cout << "start\n";
		//WhiteKing.findAvaliableCells();
		//std::cout << "fin\n";
		//window.draw(WhiteQueen.sprite);
		//Queen.findAvaliableCells();
		//return 0;
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
					if (event.key.code == Mouse::Left) {
						if (sQuit.getGlobalBounds().contains(pos.x, pos.y)) {
							window.close();
							nextCommand = COMMANDS::QUIT;
							return nextCommand;
						}

						if (sVsPlayer.getGlobalBounds().contains(pos.x, pos.y)) {
							window.close();
							nextCommand = COMMANDS::VS_PLAYER;
							return nextCommand;
						}

						if (sVsComputer.getGlobalBounds().contains(pos.x, pos.y)) {
							window.close();
							nextCommand = COMMANDS::VS_COMPUTER;
							return nextCommand;
						}
					}
				}

				//if (event.type == Event::Closed)
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
	COMMANDS nextCommand;
	nextCommand = startMenu();

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