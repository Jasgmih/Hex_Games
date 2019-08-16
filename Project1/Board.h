#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <limits>
using namespace std;
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 800
#define TOTAL_NUMBER (3 * NUM_COLUMN*NUM_COLUMN - 3 * NUM_COLUMN + 1)
#define COLOR_WHITE "White"
#define COLOR_BLACK "Black"
#define COLOR_BLUE "blue"

#define DEPTH 2  // not include the root//
#define AI_PLAY_FIRST false 
#define CHOOSE_COLOR  COLOR_BLACK

const int NUM_COLUMN = 5;
const int PLAYER = 2;

class Hex {
public:
	Hex(string colors, int r_coordinate, int q_coordinate);
	string color;
	int rCoordinate; 
	int qCoordinate;
};


class Hexagons {
public:
	void init();
	int getNumHex() const;
	void drawHexs(sf::RenderWindow & window);
	vector <Hex> hexagons;
	int hexSequence(int q, int r);
};


