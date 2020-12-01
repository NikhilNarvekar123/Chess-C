
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
	board.printBoard();

	while (userIn != "exit") {

		cout << "Player1, enter square with piece you are going to move." << endl;
		cin >> startSquare;
		boardManager.actionCheck(startSquare);
		cout << "Player1, enter square piece will be moved to." << endl;
		cin >> endSquare;
		boardManager.actionCheck(endSquare);

		cout << "Player1, you have decided to move " << startSquare << " to " << endSquare << endl << endl;
		string res = boardManager.makeMove(startSquare, endSquare, "white", board);
		cout << res << endl;
		board.printBoard();

		// add logic to check if game is over

		cout << "Player2, enter square with piece you are going to move." << endl;
		cin >> startSquare;
		boardManager.actionCheck(startSquare);
		cout << "Player2, enter square piece will be moved to." << endl;
		cin >> endSquare;
		boardManager.actionCheck(endSquare);

		cout << "Player2, you have decided to move " << startSquare << " to " << endSquare << endl << endl;
		res = boardManager.makeMove(startSquare, endSquare, "black", board);
		cout << res << endl;
		board.printBoard();

		// add logic to check if game is over
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
	board.printBoard();

	while (userIn != "exit") {

		cout << "Player1, enter square with piece you are going to move." << endl;
		cin >> startSquare;
		boardManager.actionCheck(startSquare);
		cout << "Player1, enter square piece will be moved to." << endl;
		cin >> endSquare;
		boardManager.actionCheck(endSquare);

		cout << "Player1, you have decided to move " << startSquare << " to " << endSquare << endl << endl;
		string res = boardManager.makeMove(startSquare, endSquare, "white", board);
		cout << res << endl;
		board.printBoard();

		// add logic to check if game is over

		cout << "AI is making their move! Analyzing board..." << endl;
		ai.makeMove(board, "black");
		cout << "AI, has moved. " << endl;
		board.printBoard();

		// add logic to check if game is over
	}
}

void zeroplayer() {

}



int main()
{
	cout << "Welcome to Chess-C! Choose an option below:" << endl;
	cout << "a. 2-player" << endl;
	cout << "b. 1-player (n/a at the time!)" << endl;
	cout << "c. 0-player (n/a at the time!)" << endl << endl;

	string userIn = "b"; //for debug
	bool valid = false;

	/*while (!valid) {
		cin >> userIn;
		char c = tolower(userIn.at(0));
		if (userIn.size() == 1 && (c == 'a' || c == 'b' || c == 'c')) {
			cout << "Starting option " << c << " chosen!\n" << endl;
			userIn = c;
			valid = true;
		}
		else {
			cout << "invalid input entered! try again." << endl;
		}
	}*/

	if (userIn == "a") {
		twoPlayer();
	}
	else if (userIn == "b") {
		onePlayer();
	}
	else if (userIn == "c") {
		zeroplayer();
	}

	return 0;
}
