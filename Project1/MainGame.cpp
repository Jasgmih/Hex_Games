#include "MainGame.h"
int Infinity = std::numeric_limits<int>::max();

void MainGame::update(sf::RenderWindow& window, Hexagons HexagonsGame) {

	
	int totalNumber = TOTAL_NUMBER;
	HexagonsGame.drawHexs(window);
	VictoryResult victoryResult;

	sf::Font Font;
	if (!Font.loadFromFile("BebasNeue-Regular.ttf"))
	{
		std::cout << "Error load font file" << std::endl;
		system("pause");
	}
	sf::Text WhiteScore;
	WhiteScore.setFont(Font);
	WhiteScore.setFillColor(sf::Color::Red);
	WhiteScore.setCharacterSize(70);
	WhiteScore.setPosition(sf::Vector2f(0.0f, 500.0f));
	//Text.setStyle(sf::Text::Style::Bold | sf::Text::Style::Underlined);
	//Text.setOutlineColor(sf::Color::Yellow);
	//Text.setOutlineThickness(10);
	//Text.setColor(sf::Color::Red);

	sf::Text BlackScore;
	BlackScore.setFont(Font);
	BlackScore.setFillColor(sf::Color::Red);
	BlackScore.setCharacterSize(70);
	BlackScore.setPosition(sf::Vector2f(0.0f, 600.0f));

	sf::Text TextWinner;
	TextWinner.setFont(Font);
	TextWinner.setFillColor(sf::Color::Red);
	TextWinner.setCharacterSize(70);
	TextWinner.setPosition(sf::Vector2f(0.0f, 700.0f));
	string winner;

	victoryResult = GetScore(HexagonsGame);
	if (victoryResult.resultScore[COLOR_WHITE] > victoryResult.resultScore[COLOR_BLACK])
		winner = "WHITE WIN";
	else if (victoryResult.resultScore[COLOR_WHITE] < victoryResult.resultScore[COLOR_BLACK])
		winner = "BLACK WIN";
	else winner = "DRAW";

	WhiteScore.setString(to_string(victoryResult.resultScore[COLOR_WHITE]));
	BlackScore.setString(to_string(victoryResult.resultScore[COLOR_BLACK]));
	TextWinner.setString(winner);

	window.draw(WhiteScore);
	window.draw(BlackScore);
	if (gameOverCheck(HexagonsGame)) window.draw(TextWinner);

}
VictoryResult MainGame::GetScore(Hexagons HexagonsGame)
{
	VictoryResult checkVictory;
	int num;
	int q0, r0;
	int scoreWhite = 1;
	int scoreBlack = 1;
	
	for (int i = 0; i < TOTAL_NUMBER; i++)
	{
		
		if (HexagonsGame.hexagons[i].color == COLOR_WHITE)
		{
			num = 1;
			q0 = HexagonsGame.hexagons[i].qCoordinate;
			r0 = HexagonsGame.hexagons[i].rCoordinate;
			CheckAround(&HexagonsGame, q0, r0, &num, COLOR_WHITE, COLOR_WHITE_CHECKED);

			if (num == 1) num = 2;
			scoreWhite *= num-1;
		}
	}
	for (int i = 0; i < TOTAL_NUMBER; i++)
	{
		
		if (HexagonsGame.hexagons[i].color == COLOR_BLACK)
		{
			num = 1;
			q0 = HexagonsGame.hexagons[i].qCoordinate;
			r0 = HexagonsGame.hexagons[i].rCoordinate;
			CheckAround(&HexagonsGame, q0, r0, &num, COLOR_BLACK, COLOR_BLACK_CHECKED);
			if (num == 1) num = 2;
			scoreBlack *= num-1;
		}
	}
	checkVictory.resultScore.emplace(COLOR_WHITE, scoreWhite);
	checkVictory.resultScore.emplace(COLOR_BLACK, scoreBlack);
	if (checkVictory.resultScore[COLOR_WHITE] < checkVictory.resultScore[COLOR_BLACK])
		checkVictory.victoryColor = COLOR_BLACK;
	if (checkVictory.resultScore[COLOR_WHITE] > checkVictory.resultScore[COLOR_BLACK])
		checkVictory.victoryColor = COLOR_WHITE;
	else checkVictory.victoryColor = "It is draw!";
	
	return checkVictory;
}
void MainGame::CheckAround(Hexagons* HexagonsGame, int q0, int r0, int *num, string Color,string colorChecked)
{
	if (!scope(q0, r0))
		return;
	else
	{
		if (scope(q0, r0 - 1) )
			if(HexagonsGame->hexagons[HexagonsGame->hexSequence(q0, r0 - 1)].color == Color)
			{
			*num = *num + 1;
			HexagonsGame->hexagons[HexagonsGame->hexSequence(q0, r0 - 1)].color = colorChecked;
			CheckAround(HexagonsGame, q0, r0 - 1, num, Color, colorChecked);
			}
	
		if (scope(q0 +1, r0 - 1))
			if( HexagonsGame->hexagons[HexagonsGame->hexSequence(q0 + 1, r0 - 1)].color == Color)
			{
			*num = *num + 1;
			HexagonsGame->hexagons[HexagonsGame->hexSequence(q0 + 1, r0 - 1)].color = colorChecked;
			CheckAround(HexagonsGame, q0 + 1, r0 - 1, num, Color, colorChecked);
			}
		
		if (scope(q0-1, r0))
			if( HexagonsGame->hexagons[HexagonsGame->hexSequence(q0 - 1, r0)].color == Color)
			{
			*num = *num + 1;
			HexagonsGame->hexagons[HexagonsGame->hexSequence(q0 - 1, r0)].color = colorChecked;
			CheckAround(HexagonsGame, q0 - 1, r0, num, Color, colorChecked);
			}
		
		if (scope(q0+1, r0))
			if( HexagonsGame->hexagons[HexagonsGame->hexSequence(q0 + 1, r0)].color == Color)
			{
			*num = *num + 1;
			HexagonsGame->hexagons[HexagonsGame->hexSequence(q0 + 1, r0)].color = colorChecked;
			CheckAround(HexagonsGame, q0 + 1, r0, num, Color, colorChecked);
			}
		
		if (scope(q0-1, r0 + 1))
			if( HexagonsGame->hexagons[HexagonsGame->hexSequence(q0 - 1, r0 + 1)].color == Color)
			{
			*num = *num + 1;
			HexagonsGame->hexagons[HexagonsGame->hexSequence(q0 - 1, r0 + 1)].color = colorChecked;
			CheckAround(HexagonsGame, q0 - 1, r0 + 1, num, Color, colorChecked);
			}
		
		if (scope(q0, r0 + 1))
			if( HexagonsGame->hexagons[HexagonsGame->hexSequence(q0, r0 + 1)].color == Color)
			{
			*num = *num + 1;
			HexagonsGame->hexagons[HexagonsGame->hexSequence(q0, r0 + 1)].color = colorChecked;
			CheckAround(HexagonsGame, q0, r0 + 1, num, Color, colorChecked);
			}
	}
}
bool MainGame::scope(int q0, int r0)
{
	bool scope1 = (0 <= r0) && (r0 <= (NUM_COLUMN - 1)) &&
		((1 - NUM_COLUMN) <= q0) && (q0 <= (NUM_COLUMN - 1 - r0));

	bool scope2 = ((1 - NUM_COLUMN) <= r0) && (r0 <= 0) &&
		((1 - NUM_COLUMN - r0) <= q0) && (q0 <= (NUM_COLUMN - 1));

	if (scope1 || scope2)
		return true;
	else
		return false;
}


sf::Vector2i MainGame::bestMove(Hexagons HexagonsGame) {

	sf::Vector2i vector2i;
	vector <vector <Node>> AllNodes;
	vector <Node> NodeRow;  // alpha,beta,score

	vector <vector <Hexagons>> AllHexs;
	vector <Hexagons> HexRow;
	Hexagons HexSingle; // blue,white,black
	HexSingle.init();

	vector <VictoryResult> victoryResult_Row;
	VictoryResult victoryResultSingle;

	int rowNum;
	vector <int> sizeRowNode;

	int aa = 0;
	int Depth;
	for (int i = 0; i < TOTAL_NUMBER; i++) {
		if (HexagonsGame.hexagons[i].color == COLOR_BLUE)
			aa++;
	}
	cout << "blue left: " << aa << endl;
	if (aa >= int(1*TOTAL_NUMBER / 2)) Depth = 1;
	if (aa < int(1 * TOTAL_NUMBER / 2)) Depth = 1;



	/////////////////////////The row0 begin////////////////////////////////////////////////
	for (int i = 0; i < TOTAL_NUMBER; i++)
	{
		HexSingle.hexagons[i].color = HexagonsGame.hexagons[i].color;
	}
	NodeRow.emplace_back(Infinity, -Infinity, Infinity);
	AllNodes.emplace_back(NodeRow);

	sizeRowNode.emplace_back(NodeRow.size());


	HexRow.emplace_back(HexSingle);
	AllHexs.emplace_back(HexRow);

	NodeRow.clear();
	HexRow.clear();
	HexSingle.hexagons.clear();
	/////////////////////The row0 end //////////////////////////////////////////////


	////////////////////////////////row all-all begin//////////////////////////////////////////
	int AllRowNum = 0;
	
	for (int AllRowNum = 0; AllRowNum < Depth; AllRowNum++) {
		victoryResult_Row.clear();
		rowNum = 0;
		int aa = 0;
		for (int rowNumber = 0; rowNumber < sizeRowNode[AllRowNum]; rowNumber++) {
		
			for (int i = 0; i < TOTAL_NUMBER; i++)
			{
				if (AllHexs[AllRowNum][rowNumber].hexagons[i].color == COLOR_BLUE) {
					AllHexs[AllRowNum][rowNumber].hexagons[i].color = COLOR_WHITE;
					for (int j = 0; j < TOTAL_NUMBER; j++)
					{
						if (AllHexs[AllRowNum][rowNumber].hexagons[j].color == COLOR_BLUE) {
							AllHexs[AllRowNum][rowNumber].hexagons[j].color = COLOR_BLACK;

							NodeRow.emplace_back(-Infinity, -Infinity, Infinity);
							rowNum++;
							for (int m = 0; m < TOTAL_NUMBER; m++)
							{
								HexSingle.hexagons.emplace_back(AllHexs[AllRowNum][rowNumber].hexagons[m]);
							}

							//////////////////////////evaluation//////////////
							victoryResultSingle = GetScore(HexSingle);
							victoryResult_Row.emplace_back(victoryResultSingle);


							HexRow.emplace_back(HexSingle);
							HexSingle.hexagons.clear();
							AllHexs[AllRowNum][rowNumber].hexagons[j].color = COLOR_BLUE;
						}
					}
					AllHexs[AllRowNum][rowNumber].hexagons[i].color = COLOR_BLUE;
				}
			}
		}
		

		AllNodes.emplace_back(NodeRow);
		sizeRowNode.emplace_back(NodeRow.size());
		AllHexs.emplace_back(HexRow);
		NodeRow.clear();
		HexRow.clear();

		int kk = AllNodes[AllRowNum].size();
		int pp = AllNodes[AllRowNum + 1].size();
		int ppp = int(pp / kk);
		int kkk = 0;

		for (int rowNumber = 0; rowNumber < sizeRowNode[AllRowNum]; rowNumber++) {
		
			for (int i = 0; i < ppp; i++) {


				AllNodes[AllRowNum + 1][kkk].ParentNode
					= &AllNodes[AllRowNum][rowNumber];
				AllNodes[AllRowNum][rowNumber].ChildNodes.emplace_back(
					&AllNodes[AllRowNum + 1][kkk]);
			
				kkk++;
			}
		}

	}
	//////////////////////////////row all-all end/////////////////////////////////////////////
 

	///////////////////////// alpha-beta search begin //////////////////////////

	if (victoryResult_Row.size() != AllNodes[Depth].size()) 
		std::cout << "Size has gone wrong" << std::endl;
	else {
		for (int i = 0; i < victoryResult_Row.size(); i++) {
			AllNodes[Depth][i].score = victoryResult_Row[i].resultScore[CHOOSE_COLOR] - 
				victoryResult_Row[i].resultScore[otherColor()];
		}

		////////////////////////////////ALL BEGINE/////////////////////////////////////////////////////////
		if (Depth == 1) {
			vector2i = getHexagonNum(AllNodes, AllHexs,Depth);
			cout << "depth = 1" << endl;
		}
		/////////////////////////////////   1 - end //////////////////////////////////////////

		if (Depth == 2) {
			cout << "depth = 2" << endl;
			for (int k = 0; k < AllNodes[Depth - 1].size(); k++) {
				AllNodes[Depth - 1][k].alpha = AllNodes[Depth - 1][k].ParentNode->alpha;
				AllNodes[Depth - 1][k].beta = AllNodes[Depth - 1][k].ParentNode->beta;
				
				for (int m = 0; m < AllNodes[Depth - 1][k].ChildNodes.size(); m++) {
					if (AllNodes[Depth - 1][k].score == -Infinity)
						AllNodes[Depth - 1][k].score = AllNodes[Depth - 1][k].ChildNodes[m]->score;
					else if (AllNodes[Depth - 1][k].score < (AllNodes[Depth - 1][k].ChildNodes[m]->score))
						AllNodes[Depth - 1][k].score = AllNodes[Depth - 1][k].ChildNodes[m]->score;

					if (AllNodes[Depth - 1][k].ChildNodes[m]->score > AllNodes[Depth - 1][k].alpha)
						AllNodes[Depth - 1][k].alpha = AllNodes[Depth - 1][k].ChildNodes[m]->score;

					if (AllNodes[Depth - 1][k].alpha >= AllNodes[Depth - 1][k].beta)
						break;
				}
			}
			vector2i = getHexagonNum(AllNodes, AllHexs,Depth);
		}
		/////////////////////////////////  2 - end  ////////////////////////////////////////

		if (Depth == 3) {
			cout << "depth = 3" << endl;
			for (int i = 0; i < AllNodes[Depth - 2].size(); i++) {


				for (int j = 0; j < AllNodes[Depth-2][i].ChildNodes.size(); j++) {

					*AllNodes[Depth - 2][i].ChildNodes[j] = updateNode(*AllNodes[Depth - 2][i].ChildNodes[j], false);
					AllNodes[Depth - 2][i] = updateNodeScore(AllNodes[Depth - 2][i], true, j);

					if (AllNodes[Depth - 2][i].alpha >= AllNodes[Depth - 2][i].beta)
						break;
				}

			}
			vector2i = getHexagonNum(AllNodes, AllHexs, Depth);
		}
		///////////////////////////////   3 - end  ////////////////////////////////////////////

		if (Depth == 4) {

			for (int k = 0; k < AllNodes[Depth - 3].size(); k++) {
				for (int i = 0; i < AllNodes[Depth - 3][k].ChildNodes.size(); i++) {
					AllNodes[Depth - 3][k].ChildNodes[i]->alpha = AllNodes[Depth - 3][k].alpha;
					AllNodes[Depth - 3][k].ChildNodes[i]->beta = AllNodes[Depth - 3][k].beta;
					
					for (int j = 0; j < AllNodes[Depth - 3][k].ChildNodes[i]->ChildNodes.size(); j++) {
						*AllNodes[Depth - 3][k].ChildNodes[i]->ChildNodes[j] = updateNode(
							*AllNodes[Depth - 3][k].ChildNodes[i]->ChildNodes[j], true);
						*AllNodes[Depth - 3][k].ChildNodes[i] = updateNodeScore(
							*AllNodes[Depth - 3][k].ChildNodes[i], false, j);
						if (AllNodes[Depth - 3][k].ChildNodes[i]->alpha >= AllNodes[Depth - 3][k].ChildNodes[i]->beta)
							break;
					}
					
					AllNodes[Depth - 3][k] = updateNodeScore(AllNodes[Depth - 3][k], true, i);
					if (AllNodes[Depth - 3][k].alpha >= AllNodes[Depth - 3][k].beta)
						break;
				}
			}
			vector2i = getHexagonNum(AllNodes, AllHexs, Depth);
		}
		//////////////////////////////   4 - end  /////////////////////////////////////
		if (Depth == 5) {
			for (int m = 0; m < AllNodes[Depth - 4].size(); m++) {
				for (int k = 0; k < AllNodes[Depth - 4][m].ChildNodes.size(); k++) {
					AllNodes[Depth - 4][m].ChildNodes[k]->alpha = AllNodes[Depth - 4][m].alpha;
					AllNodes[Depth - 4][m].ChildNodes[k]->beta = AllNodes[Depth - 4][m].beta;
					for (int i = 0; i < AllNodes[Depth - 4][m].ChildNodes[k]->ChildNodes.size();i++) {
						AllNodes[Depth - 4][m].ChildNodes[k]->ChildNodes[i]->alpha = AllNodes[Depth - 4][m].ChildNodes[k]->alpha;
						AllNodes[Depth - 4][m].ChildNodes[k]->ChildNodes[i]->beta = AllNodes[Depth - 4][m].ChildNodes[k]->beta;
						for (int j = 0; j < AllNodes[Depth - 4][m].ChildNodes[k]->ChildNodes[i]->ChildNodes.size();j++) {
							*AllNodes[Depth - 4][m].ChildNodes[k]->ChildNodes[i]->ChildNodes[j] = updateNode(
								*AllNodes[Depth - 4][m].ChildNodes[k]->ChildNodes[i]->ChildNodes[j], false);
							*AllNodes[Depth - 4][m].ChildNodes[k]->ChildNodes[i] = updateNodeScore(
								*AllNodes[Depth - 4][m].ChildNodes[k]->ChildNodes[i], true, j);
							if (AllNodes[Depth - 4][m].ChildNodes[k]->ChildNodes[i]->alpha >= 
								AllNodes[Depth - 4][m].ChildNodes[k]->ChildNodes[i]->beta)
								break;
						}
						*AllNodes[Depth - 4][m].ChildNodes[k] = updateNodeScore(*AllNodes[Depth - 4][m].ChildNodes[k], false, i);
						if (AllNodes[Depth - 4][m].ChildNodes[k]->alpha >= AllNodes[Depth - 4][m].ChildNodes[k]->beta)
							break;
					}
					AllNodes[Depth - 4][m] = updateNodeScore(AllNodes[Depth - 4][m], true, k);
					if (AllNodes[Depth - 4][m].alpha >= AllNodes[Depth - 4][m].beta)
						break;
				}
			}
			vector2i = getHexagonNum(AllNodes, AllHexs, Depth);
		}
		////////////////////////////  5 - end /////////////////////////////////////////
		if (Depth > 5) std::cout << "Depth can not bigger than 5" << endl;
	}
	//////////////////////// alpha-beta search done ///////////////////////////

	

	std::cout << "AI Search Done" << std::endl;
	/* add time here, every time to plue ++
	*/
	return vector2i;
}

bool MainGame::gameOverCheck(Hexagons HexagonsGame) 
{
	int remainder = TOTAL_NUMBER % (PLAYER*PLAYER);
	int num = 0;
	for (int i = 0; i < TOTAL_NUMBER; i++)
	{
		if (HexagonsGame.hexagons[i].color == COLOR_BLUE) {
			num++;
		}
	}

	if (num <= remainder) return true;
	else return false;
}

sf::Vector2i MainGame::getHexagonNum(vector <vector <Node>> AllNodes, vector <vector <Hexagons>> AllHexs,int depth){


	int bestScore = 0;
	int bestScoreNum = 0;
	sf::Vector2i vector2i;

	for (int i = 0; i < AllNodes[depth].size(); i++)
	{
		if (bestScore < AllNodes[depth][i].score) {
			bestScore = AllNodes[depth][i].score;
			bestScoreNum = i;
		}
	}

	for (int i = 0; i < TOTAL_NUMBER; i++) {
		if (AllHexs[0][0].hexagons[i].color != AllHexs[depth][bestScoreNum].hexagons[i].color)
			if (AllHexs[depth][bestScoreNum].hexagons[i].color == COLOR_WHITE)
				vector2i.x = i;
			else vector2i.y = i;
	}
	
	return vector2i;
}

Node MainGame::updateNode(Node node, bool max)
{
	node.alpha = node.ParentNode->alpha;
	node.beta = node.ParentNode->beta;
	if (max) {

		for (int m = 0; m < node.ChildNodes.size(); m++) {

			if (node.score == -Infinity)
				node.score = node.ChildNodes[m]->score;
			else if (node.score < node.ChildNodes[m]->score)
				node.score = node.ChildNodes[m]->score;

			if (node.ChildNodes[m]->score > node.alpha)
				node.alpha = node.ChildNodes[m]->score;

			if (node.alpha >= node.beta)
				break;
		}
	}
	else {

		for (int m = 0; m < node.ChildNodes.size(); m++) {

			if (node.score == -Infinity)
				node.score = node.ChildNodes[m]->score;
			else if (node.score > node.ChildNodes[m]->score)
				node.score = node.ChildNodes[m]->score;

			if (node.ChildNodes[m]->score < node.beta)
				node.beta = node.ChildNodes[m]->score;

			if (node.alpha >= node.beta)
				break;
		}
	}

	return node;
}

Node MainGame::updateNodeScore(Node node, bool max, int child)
{

	
	if (max) {

		if (node.score == -Infinity)
			node.score = node.ChildNodes[child]->score;
		else if (node.score < node.ChildNodes[child]->score)
			node.score = node.ChildNodes[child]->score;

		if (node.ChildNodes[child]->score > node.alpha)
			node.alpha = node.ChildNodes[child]->score;
	}
	else {

		if (node.score == -Infinity)
			node.score = node.ChildNodes[child]->score;
		else if (node.score > node.ChildNodes[child]->score)
			node.score = node.ChildNodes[child]->score;

		if (node.ChildNodes[child]->score < node.beta)
			node.beta = node.ChildNodes[child]->score;
	}

	return node;
}




