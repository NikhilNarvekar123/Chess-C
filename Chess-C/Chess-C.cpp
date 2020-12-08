#include <iostream>
#include <string>
#include "Board_Piece.h"
#include "BoardManager.h"
#include "AI.h"

using namespace std;

/* Runs the chess game between 2 different players
*/
void twoPlayer() {

	// game objects
	BoardManager boardManager;
	Board board;

	// variables for user input
	string userIn;
	string startSquare;
	string endSquare;

	// instructions
	cout << "welcome to 2-player chess! enter input as shown: squareToStart squareToEnd" << endl;
	cout << "for example, to move the piece at A1 to B2, you would type:\n";
	cout << "A1 B2" << endl;
	cout << "enter 'exit' to leave the mode" << endl << endl;

	// user options
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

	// main game loop
	while (userIn != "exit") {

		// player 1 turn
		cout << "Player1, enter square with piece you are going to move." << endl;
		cin >> startSquare;
		if (startSquare == "exit")
			break;
		boardManager.actionCheck(startSquare);
		cout << "Player1, enter square piece will be moved to." << endl;
		cin >> endSquare;
		boardManager.actionCheck(endSquare);

		// making p1 move and checking for winner
		cout << "Player1, you have decided to move " << startSquare << " to " << endSquare << endl << endl;
		string res = boardManager.makeMove(startSquare, endSquare, "white", board);
		cout << res << endl;
		board.printBoard(boardType);
		Color winner = board.printWinner();
		if (winner == Color::BLACK || winner == Color::WHITE)
			break;

		// player 2 turn
		cout << "Player2, enter square with piece you are going to move." << endl;
		cin >> startSquare;
		if (startSquare == "exit")
			break;
		boardManager.actionCheck(startSquare);
		cout << "Player2, enter square piece will be moved to." << endl;
		cin >> endSquare;
		boardManager.actionCheck(endSquare);

		// making p2 move and checking for winner
		cout << "Player2, you have decided to move " << startSquare << " to " << endSquare << endl << endl;
		res = boardManager.makeMove(startSquare, endSquare, "black", board);
		cout << res << endl;
		board.printBoard(boardType);
		winner = board.printWinner();
		if (winner == Color::BLACK || winner == Color::WHITE)
			break;
	}
}

/* Runs the chess game between 1 player and an AI agent
*/
void onePlayer() {

	// game objects
	Board board;
	BoardManager boardManager;
	AI ai;

	// user input variables
	string userIn;
	string startSquare;
	string endSquare;

	// instructions
	cout << "welcome to 1-player chess! enter input as shown: squareToStart squareToEnd" << endl;
	cout << "you will play as white while the AI plays as black." << endl;
	cout << "for example, to move the piece at A1 to B2, you would type:\n";
	cout << "A1 B2" << endl;
	cout << "enter 'exit' to leave the mode" << endl << endl;

	// options for AI difficulty
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

	// main game loop
	while (userIn != "exit") {

		// player 1 turn
		cout << "Player1, enter square with piece you are going to move." << endl;
		cin >> startSquare;
		if (startSquare == "exit")
			break;
		boardManager.actionCheck(startSquare);
		cout << "Player1, enter square piece will be moved to." << endl;
		cin >> endSquare;
		boardManager.actionCheck(endSquare);

		// making p1 move and checking for winner
		cout << "Player1, you have decided to move " << startSquare << " to " << endSquare << endl << endl;
		string res = boardManager.makeMove(startSquare, endSquare, "white", board);
		cout << res << endl;
		board.printBoard();
		Color winner = board.printWinner();
		if (winner == Color::BLACK || winner == Color::WHITE)
			break;

		// ai's turn
		cout << "AI is making their move! Analyzing board..." << endl;
		ai.makeMove(board, "black");
		cout << "AI, has moved. " << endl;
		board.printBoard();

		// checking for winner after AI turn
		winner = board.printWinner();
		if (winner == Color::BLACK || winner == Color::WHITE)
			break;
	}
}

/* Runs the chess game between 2 AI agents
*/
void zeroplayer() {

	// game objects
	Board board;
	BoardManager boardManager;
	AI ai1;
	AI ai2;

	// variables for user input
	string userIn;
	string startSquare;
	string endSquare;

	// instructions
	cout << "welcome to 0-player chess!" << endl;
	cout << "the AI will play against another AI agent. Type anything to advance the AI turn." << endl;
	cout << "enter 'exit' to leave the mode" << endl << endl;

	board.printBoard();

	// main game loop
	while (userIn != "exit") {

		// pause after AI 2 turn
		cin >> userIn;
		if (userIn == "exit")
			break;

		// AI 1 turn
		cout << "AI is making their move! Analyzing board..." << endl;
		ai1.makeMove(board, "white");
		cout << "AI, has moved. " << endl;
		board.printBoard();

		// checking for winner
		Color winner = board.printWinner();
		if (winner == Color::BLACK || winner == Color::WHITE)
			break;

		// pause after AI 1 turn
		cin >> userIn;
		if (userIn == "exit")
			break;

		// AI 2 turn
		cout << "AI is making their move! Analyzing board..." << endl;
		ai2.makeMove(board, "black");
		cout << "AI, has moved. " << endl;
		board.printBoard();

		// checking for winner
		winner = board.printWinner();
		if (winner == Color::BLACK || winner == Color::WHITE)
			break;
	}
}

/** Runs the overall program. Maintains a game loop
		which allows users to keep playing one of 3 modes (2p, 1p,
	  0p) until they exit the program.
*/
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
