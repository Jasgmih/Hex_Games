#include <iostream>
#include <SFML/Graphics.hpp>
#include "MainGame.h"
#include "Draw.h"

int main() {

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "HexagonGame", 
		sf::Style::Close | sf::Style::Titlebar);
	MainGame mainGame;
	Hexagons HexagonsGame;
	HexagonsGame.init(); 
	sf::Vector2i vector2i;
	
	bool pressBlack;
	bool pressWhite;
	if (AI_PLAY_FIRST) {
		pressBlack = true;
		pressWhite = true;
	}
	else {
		pressBlack = false;
		pressWhite = false;
	}

	sf::Text gameOver;
	sf::Font Font1;
	if (!Font1.loadFromFile("BebasNeue-Regular.ttf"))
	{
		std::cout << "Error load font file" << std::endl;
		system("pause");
	}
	gameOver.setFont(Font1);
	gameOver.setFillColor(sf::Color::Red);
	gameOver.setCharacterSize(120);
	gameOver.setPosition(sf::Vector2f(0.0f, 400.0f));
	gameOver.setString("Game over");
	

	vector <sf::CircleShape> circles;
	float size = 3.0 / float(NUM_COLUMN)*50.0;
	for (int i = 0; i < TOTAL_NUMBER; i++)
	{
		circles.emplace_back(size);
		circles[i].setFillColor(sf::Color(3, 74, 166)); //
	}


	float lengthInit = 3.0 / float(NUM_COLUMN) * SCREEN_HEIGHT / 10.0;
	float startPoint_x = 0.5*SCREEN_WIDTH - sqrt(3.0) / 2.0*lengthInit*float(NUM_COLUMN);
	float startPoint_y = 0.5*SCREEN_HEIGHT - (6.0*float(NUM_COLUMN) - 3.0) / 4.0*lengthInit;
	float circleStatePoint_x = startPoint_x + sqrt(3.0) / 2.0*lengthInit - size;
	float circleStatePoint_y = startPoint_y + 0.5*lengthInit - size;
	int circleNum = 0;

	for (int j = 0; j < NUM_COLUMN; j++)
	{
		for (int i = 0; i < NUM_COLUMN +j ; i++)
		{
			circles[circleNum].setPosition(circleStatePoint_x + (float)i* sqrt(3.0)*lengthInit
				- (float)j * sqrt(3.0) / 2.0*lengthInit,
				circleStatePoint_y + (float)j * 3.0 / 2.0*lengthInit);
			circleNum++;
		}
	}

	for (int j = 0; j < NUM_COLUMN -1; j++)
	{
		for (int i = 0; i < 2*NUM_COLUMN-2-j; i++)
		{
			circles[circleNum].setPosition(circleStatePoint_x + (float)(i+j/2.0+1- NUM_COLUMN/2.0)*
				sqrt(3.0)*lengthInit,
				circleStatePoint_y + (float)(j+ NUM_COLUMN) * 3.0 / 2.0*lengthInit);
			circleNum++;
		}
	}
	
	while (window.isOpen())
	{
		window.clear(sf::Color(3, 74, 166));
		
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			switch (Event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					sf::Vector2i mousePos = sf::Mouse::getPosition(window);
					sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
					for (int i = 0; i < TOTAL_NUMBER; i++)
					{ 
						if (circles[i].getGlobalBounds().contains(mousePosF))
						{
							if (HexagonsGame.hexagons[i].color == COLOR_BLUE && !pressWhite && !pressBlack
								&& !mainGame.gameOverCheck(HexagonsGame)) {
								
								circles[i].setFillColor(sf::Color::White);
								HexagonsGame.hexagons[i].color = COLOR_WHITE;
								pressWhite = true;
							}
							else cout << "You can't put a stone here" << endl;
						}
					}
				}

				if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
					sf::Vector2i mousePos = sf::Mouse::getPosition(window);
					sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
					for (int i = 0; i < TOTAL_NUMBER; i++)
					{
						if (circles[i].getGlobalBounds().contains(mousePosF))
						{
							if (HexagonsGame.hexagons[i].color == COLOR_BLUE && !pressBlack && pressWhite) {
								
								circles[i].setFillColor(sf::Color::Black);
								HexagonsGame.hexagons[i].color = COLOR_BLACK;
								pressBlack = true;
								
							}
							else cout << "You can't put a stone here" << endl;
						}
					}
				}
				if (pressWhite && pressBlack && !mainGame.gameOverCheck(HexagonsGame)) {
				
					if (!mainGame.gameOverCheck(HexagonsGame))
					cout << "mouse was pressed" << endl;

					vector2i = mainGame.bestMove(HexagonsGame);
					if (HexagonsGame.hexagons[vector2i.x].color == COLOR_BLUE
						&& HexagonsGame.hexagons[vector2i.y].color == COLOR_BLUE) {

						HexagonsGame.hexagons[vector2i.x].color = COLOR_WHITE;
						circles[vector2i.x].setFillColor(sf::Color::White);

						HexagonsGame.hexagons[vector2i.y].color = COLOR_BLACK;
						circles[vector2i.y].setFillColor(sf::Color::Black);

					}
					else cout << "bestMove return the wrong number" << endl;

					pressWhite = false;
					pressBlack = false;
					
					
				}
			}
			break;
			}
		}
		
		
		for (int i = 0; i < TOTAL_NUMBER; i++)
		{
			window.draw(circles[i]);
		}

		if (mainGame.gameOverCheck(HexagonsGame)) {
			window.draw(gameOver);
		}
		mainGame.update(window, HexagonsGame);
	
		window.display();
		
	}
	return EXIT_SUCCESS;
}
