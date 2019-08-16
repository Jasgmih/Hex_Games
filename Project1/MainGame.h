#pragma once
#include <map>
#include <string>
#include <limits>
#include "Tree.h"
#define COLOR_WHITE_CHECKED "whiteChecked"
#define COLOR_BLACK_CHECKED "blackChecked"

class VictoryResult {
public:
	map <string, int> resultScore;
	string victoryColor;
};

class MainGame {
public:
	void update(sf::RenderWindow& window, Hexagons HexagonsGame);
	sf::Vector2i bestMove(Hexagons HexagonsGame);
	bool gameOverCheck(Hexagons HexagonsGame);

private:
	
	string otherColor() {
		if (CHOOSE_COLOR == COLOR_WHITE) return COLOR_BLACK;
		else return COLOR_WHITE;
	}

	VictoryResult GetScore(Hexagons HexagonsGame);
	void CheckAround(Hexagons* HexagonsGame, int q, int r,int *num, string color, string colorChecked);
	bool scope(int q0, int r0);
	sf::Vector2i getHexagonNum(vector <vector <Node>> AllNodes, vector <vector <Hexagons>> AllHexs,int depth);
	Node updateNode(Node node, bool max);
	Node updateNodeScore(Node node, bool max, int child);

};
 
