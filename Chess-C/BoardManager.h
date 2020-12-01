#ifndef BOARDMANAGERCLASS
#define BOARDMANAGERCLASS

#include <string>
#include <iostream>
#include <vector>
#include <regex>
#include "CommonData.h"
#include "Board_Piece.h"

using namespace std;

class BoardManager {
public:

	// Default constructor
	BoardManager();

	Point translateInput(string input);
	string makeMove(string userStartPt, string userEndPt, string playerColor, Board &board);
	void actionCheck(string& input);
	void displayScore();


private:
	int player1Score;
	int player2Score;

	vector<string> boardLabelsX = { "A","B", "C", "D", "E", "F","G","H" };
	vector<string> boardLabelsY = { "8", "7", "6", "5", "4", "3", "2", "1" };

};

#endif