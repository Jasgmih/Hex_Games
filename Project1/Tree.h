#pragma once
#include <iostream>
#include <vector>
#include "Board.h"



class Node {

public:
	Node(int score, int alpha, int beta);

public:
	int score;
	int alpha;
	int beta;
	std::vector <Node*> ChildNodes;
	Node *ParentNode;
};

class Tree {


public:
	
	std::vector <std::vector <Node>> Nodes;
};
