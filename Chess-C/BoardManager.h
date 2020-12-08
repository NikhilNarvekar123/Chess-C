#include <string>
#include <iostream>
#include <vector>
#include <regex>
#include "CommonData.h"
#include "Board_Piece.h"

using namespace std;

class BoardManager {

public:
	BoardManager();
	Point translateInput(string input);
	string makeMove(string userStartPt, string userEndPt, string playerColor, Board &board);
	void actionCheck(string& input);

private:
	vector<string> boardLabelsX = { "A","B", "C", "D", "E", "F","G","H" };
	vector<string> boardLabelsX2 = { "a", "b", "c", "d", "e", "f", "g", "h" };
	vector<string> boardLabelsY = { "8", "7", "6", "5", "4", "3", "2", "1" };

};
