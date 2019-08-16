#include "Board.h"

Hex::Hex(string colors, int r_coordinate, int q_coordinate) {
	this->color = colors;
	this->rCoordinate = r_coordinate;
	this->qCoordinate = q_coordinate;
}

int Hexagons::getNumHex() const {
	return (3 * NUM_COLUMN*NUM_COLUMN - 3 * NUM_COLUMN + 1);
}

void Hexagons::init() {

	for (int j = 0; j < NUM_COLUMN; j++) {
		for (int i = 0; i < NUM_COLUMN + j; i++) {
			hexagons.emplace_back(Hex(COLOR_BLUE, j - NUM_COLUMN + 1, -j + i));
		}
	}

	for (int j = 0; j < NUM_COLUMN - 1; j++) {
		for (int i = 0; i < 2 * NUM_COLUMN - 2 - j; i++) {
			hexagons.emplace_back(Hex(COLOR_BLUE, j + 1, -NUM_COLUMN + 1 + i));
		}
	}

}

void Hexagons::drawHexs(sf::RenderWindow & window)
{
	vector <sf::RectangleShape> lines;
	sf::Font Font;
	if (!Font.loadFromFile("BebasNeue-Regular.ttf"))
	{
		std::cout << "Error load font file" << std::endl;
		system("pause");
	}
	sf::Text hexaNumQ;
	hexaNumQ.setFont(Font);
	hexaNumQ.setFillColor(sf::Color::Red);
	hexaNumQ.setCharacterSize(25);
	sf::Text hexaNumR;
	hexaNumR.setFont(Font);
	hexaNumR.setFillColor(sf::Color::Red);
	hexaNumR.setCharacterSize(25);


	float lengthInit = 3.0 /float(NUM_COLUMN) * SCREEN_HEIGHT/10.0;
	float startPoint_x = 0.5*SCREEN_WIDTH - sqrt(3.0) / 2.0*lengthInit*float(NUM_COLUMN);
	float startPoint_y = 0.5*SCREEN_HEIGHT - (6.0*float(NUM_COLUMN) - 3.0)/4.0*lengthInit;
	float singleStartPoint_x;
	float singleStartPoint_y;

	for (int k = 0; k < NUM_COLUMN; k++)
	{
		singleStartPoint_x = startPoint_x -sqrt(3.0)/2.0*lengthInit*float(k) ;
		singleStartPoint_y = startPoint_y + 3.0 / 2.0*lengthInit*float(k);
		for (int j = 0; j < NUM_COLUMN + k; j++)
		{
			float length = lengthInit;
			float point1_x = singleStartPoint_x + sqrt(3.0)*length *float(j);
			float point1_y = singleStartPoint_y;
			float point2_x = point1_x + sqrt(3.0)*length;
			float point2_y = point1_y;
			float point3_x = point1_x + sqrt(3.0)*length / 2.0;
			float point3_y = point1_y + 3.0 / 2.0*length;

			for (int i = 0; i < 6; i++)
			{
				lines.emplace_back(sf::Vector2f(length, 3.5f));
				lines[i].setFillColor(sf::Color::Black);
			}

			lines[0].setPosition(sf::Vector2f(point1_x, point1_y));
			lines[0].setRotation(-30.0f);

			lines[1].setPosition(sf::Vector2f(point1_x, point1_y));
			lines[1].setRotation(90.0f);

			lines[2].setPosition(sf::Vector2f(point2_x, point2_y));
			lines[2].setRotation(-150.0f);

			lines[3].setPosition(sf::Vector2f(point2_x, point2_y));
			lines[3].setRotation(90.0f);

			lines[4].setPosition(sf::Vector2f(point3_x, point3_y));
			lines[4].setRotation(-30.0f);

			lines[5].setPosition(sf::Vector2f(point3_x, point3_y));
			lines[5].setRotation(-150.0f);


			for (int i = 0; i < 6; i++)
				window.draw(lines[i]);

			hexaNumQ.setString(to_string(j));
			hexaNumQ.setPosition(sf::Vector2f(point1_x + sqrt(3.0) / 2.0*lengthInit, point1_y + 1. / 2.0*lengthInit));

			window.draw(hexaNumQ);

		}
		
		
	}

	for (int k = NUM_COLUMN ; k > 1; k--)
	{
		int l = 0;
		l++;
		singleStartPoint_x = singleStartPoint_x + sqrt(3.0) / 2.0*lengthInit*float(l);
		singleStartPoint_y = singleStartPoint_y + 3.0 / 2.0*lengthInit*float(l);
		for (int j = 0; j < NUM_COLUMN + k -2; j++)
		{
			float length = lengthInit;
			float point1_x = singleStartPoint_x + sqrt(3.0)*length *float(j);
			float point1_y = singleStartPoint_y;
			float point2_x = point1_x + sqrt(3.0)*length;
			float point2_y = point1_y;
			float point3_x = point1_x + sqrt(3.0)*length / 2.0;
			float point3_y = point1_y + 3.0 / 2.0*length;

			for (int i = 0; i < 6; i++)
			{
				lines.emplace_back(sf::Vector2f(length, 3.5f));
				lines[i].setFillColor(sf::Color::Black);
			}

			lines[0].setPosition(sf::Vector2f(point1_x, point1_y));
			lines[0].setRotation(-30.0f);

			lines[1].setPosition(sf::Vector2f(point1_x, point1_y));
			lines[1].setRotation(90.0f);

			lines[2].setPosition(sf::Vector2f(point2_x, point2_y));
			lines[2].setRotation(-150.0f);

			lines[3].setPosition(sf::Vector2f(point2_x, point2_y));
			lines[3].setRotation(90.0f);

			lines[4].setPosition(sf::Vector2f(point3_x, point3_y));
			lines[4].setRotation(-30.0f);

			lines[5].setPosition(sf::Vector2f(point3_x, point3_y));
			lines[5].setRotation(-150.0f);

			for (int i = 0; i < 6; i++)
				window.draw(lines[i]);

			hexaNumQ.setString(to_string(j));
			hexaNumQ.setPosition(sf::Vector2f(point1_x + sqrt(3.0) / 2.0*lengthInit, point1_y + 1. / 2.0*lengthInit));

			window.draw(hexaNumQ);
		}
	}

}

int Hexagons::hexSequence(int q, int r)
{
	int num;
	if (r <= 0)
		num = 0.5*(3 * NUM_COLUMN + r - 2)*(NUM_COLUMN + r - 1) + q + NUM_COLUMN + r - 1;
	if (r > 0)
	{
		num = 0.5*(3 * NUM_COLUMN - r - 2)*(NUM_COLUMN - r - 1) - q + NUM_COLUMN - r - 1;
		num = TOTAL_NUMBER - num - 1;
	}
	return num;
}

