#ifndef AIMANAGER
#define AIMANAGER

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

	void makeMove(Board &board, string aiColor);
	vector<Board> generateMoves(Board board, Color color);
	vector<int> returnValuation(Board board);

private:
	int runMinmax(Board loopboard, Color player, int curDepth, int maxDepth);

};

#endif