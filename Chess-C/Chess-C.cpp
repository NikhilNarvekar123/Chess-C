#include <iostream>
#include <string>
#include "Board_Piece.h"
#include "BoardManager.h"
#include "AI.h"


using namespace std;


void twoPlayer() {

	BoardManager boardManager;
	Board board;

	string userIn;
	string startSquare;
	string endSquare;

	cout << "welcome to 2-player chess! enter input as shown: squareToStart squareToEnd" << endl;
	cout << "for example, to move the piece at A1 to B2, you would type:\n";
	cout << "A1 B2" << endl;
	cout << "enter 'exit' to leave the mode" << endl << endl;
	
	cout << "would you like to use the pretty standard chessboard ('c') or a simple text one ('t')" << endl;
	bool valid = false;
	while (!valid) {
		cin >> userIn;
		char c = tolower(userIn.at(0));
		if (userIn.size() == 1 && (c == 'c' || c == 't')) {
			cout << "Board display option " << c << " chosen!\n" << endl;
			userIn = c;
			valid = true;
		}
		else {
			cout << "invalid input entered! try again." << endl;
		}
	}

	string boardType = userIn;
	board.printBoard(boardType);

	while (userIn != "exit") {

		cout << "Player1, enter square with piece you are going to move." << endl;
		cin >> startSquare;
		if (startSquare == "exit")
			break;
		boardManager.actionCheck(startSquare);
		cout << "Player1, enter square piece will be moved to." << endl;
		cin >> endSquare;
		boardManager.actionCheck(endSquare);

		cout << "Player1, you have decided to move " << startSquare << " to " << endSquare << endl << endl;
		string res = boardManager.makeMove(startSquare, endSquare, "white", board);
		cout << res << endl;
		board.printBoard(boardType);

		Color winner = board.printWinner();
		if (winner == Color::BLACK || winner == Color::WHITE)
			break;

		cout << "Player2, enter square with piece you are going to move." << endl;
		cin >> startSquare;
		if (startSquare == "exit")
			break;
		boardManager.actionCheck(startSquare);
		cout << "Player2, enter square piece will be moved to." << endl;
		cin >> endSquare;
		boardManager.actionCheck(endSquare);

		cout << "Player2, you have decided to move " << startSquare << " to " << endSquare << endl << endl;
		res = boardManager.makeMove(startSquare, endSquare, "black", board);
		cout << res << endl;
		board.printBoard(boardType);

		winner = board.printWinner();
		if (winner == Color::BLACK || winner == Color::WHITE)
			break;
	}
}

void onePlayer() {

	Board board;
	BoardManager boardManager;
	AI ai;
	string userIn;
	string startSquare;
	string endSquare;

	cout << "welcome to 1-player chess! enter input as shown: squareToStart squareToEnd" << endl;
	cout << "you will play as white while the AI plays as black." << endl;
	cout << "for example, to move the piece at A1 to B2, you would type:\n";
	cout << "A1 B2" << endl;
	cout << "enter 'exit' to leave the mode" << endl;
	
	cout << "what's your AI difficulty? ('e' = easy, 'r' = regular, 'h' = hard)" << endl;
	bool valid = false;
	while (!valid) {
		cin >> userIn;
		char c = tolower(userIn.at(0));
		if (userIn.size() == 1 && (c == 'e' || c == 'r' || c == 'h')) {
			cout << "Board display option " << c << " chosen!\n" << endl;
			userIn = c;
			valid = true;
		}
		else {
			cout << "invalid input entered! try again." << endl;
		}
	}
	if (userIn == "e")
		ai.setDifficulty(2);
	else if (userIn == "h")
		ai.setDifficulty(4);
	else
		ai.setDifficulty(3);

	cout << endl;

	board.printBoard();

	while (userIn != "exit") {

		cout << "Player1, enter square with piece you are going to move." << endl;
		cin >> startSquare;
		if (startSquare == "exit")
			break;
		boardManager.actionCheck(startSquare);
		cout << "Player1, enter square piece will be moved to." << endl;
		cin >> endSquare;
		boardManager.actionCheck(endSquare);

		cout << "Player1, you have decided to move " << startSquare << " to " << endSquare << endl << endl;
		string res = boardManager.makeMove(startSquare, endSquare, "white", board);
		cout << res << endl;
		board.printBoard();

		Color winner = board.printWinner();
		if (winner == Color::BLACK || winner == Color::WHITE)
			break;

		cout << "AI is making their move! Analyzing board..." << endl;
		ai.makeMove(board, "black");
		cout << "AI, has moved. " << endl;
		board.printBoard();

		winner = board.printWinner();
		if (winner == Color::BLACK || winner == Color::WHITE)
			break;
	}
}

void zeroplayer() {
	Board board;
	BoardManager boardManager;
	AI ai1;
	AI ai2;

	string userIn;
	string startSquare;
	string endSquare;

	cout << "welcome to 0-player chess!" << endl;
	cout << "the AI will play against another AI agent. Type anything to advance the AI turn." << endl;
	cout << "enter 'exit' to leave the mode" << endl << endl;
	board.printBoard();

	while (userIn != "exit") {

		cin >> userIn;
		if (userIn == "exit")
			break;
		cout << "AI is making their move! Analyzing board..." << endl;
		ai1.makeMove(board, "white");
		cout << "AI, has moved. " << endl;
		board.printBoard();

		Color winner = board.printWinner();
		if (winner == Color::BLACK || winner == Color::WHITE)
			break;

		cin >> userIn;
		if (userIn == "exit")
			break;
		cout << "AI is making their move! Analyzing board..." << endl;
		ai2.makeMove(board, "black");
		cout << "AI, has moved. " << endl;
		board.printBoard();

		winner = board.printWinner();
		if (winner == Color::BLACK || winner == Color::WHITE)
			break;
	}
}



int main()
{

	string title = R"(
                _                                      
	    ___| |__   ___  ___ ___    ___ _ __  _ __
	   / __| '_ \ / _ \/ __/ __|  / __| '_ \| '_ \ 
	  | (__| | | |  __/\__ \__ \ | (__| |_) | |_) |
	   \___|_| |_|\___||___/___/  \___| .__/| .__/ 
				          |_|   |_|    	
  
    )";

	while (true) {

		cout << title << endl;
		cout << "Welcome to Chess-C! Choose an option below:" << endl << endl;
		cout << "a. 2-player" << endl;
		cout << "b. 1-player (you vs AI)" << endl;
		cout << "c. 0-player (AI vs AI)" << endl;
		cout << "d. exit game :(" << endl << endl;

		string userIn;
		bool valid = false;

		while (!valid) {
			cin >> userIn;
			char c = tolower(userIn.at(0));
			if (userIn.size() == 1 && (c == 'a' || c == 'b' || c == 'c' || c =='d')) {
				cout << "Starting option " << c << " chosen!\n" << endl;
				userIn = c;
				valid = true;
			}
			else {
				cout << "invalid input entered! try again." << endl;
			}
		}

		if (userIn == "a") {
			twoPlayer();
		}
		else if (userIn == "b") {
			onePlayer();
		}
		else if (userIn == "c") {
			zeroplayer();
		}
		else if (userIn == "d") {
			break;
		}

	}

	return 0;
}
