#include <iostream>
#include "CommonData.h"
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include "Board_Piece.h"

using namespace std;

class AI {

public:
	AI();
	void setDifficulty(int diff);
	void makeMove(Board &board, string aiColor);
	vector<Board> generateMoves(Board board, Color color);
	int returnValuation(Board board);

private:
	int runMinmax(Board loopboard, Color player, int curDepth, int maxDepth, int alpha, int beta);
	int difficulty;

};
