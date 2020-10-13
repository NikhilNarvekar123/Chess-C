// Chess-C.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include "Board.h"


using namespace std;

bool inputValidifier(string input) {
	regex format("[A-Z][1-8]");
	regex format2("[a-z][1-8]");
	if (regex_match(input, format) || regex_match(input, format))
		return true;
	else
		return false;
}

void actionCheck(string& input) {
	bool isValid = inputValidifier(input);
	
	while (!isValid) {
		cout << "Incorrect input was entered. Make sure to follow the format \"A1\" " << endl;
		cin >> input;
		isValid = inputValidifier(input);
	}
}


void twoPlayer() {

	Board board;

	string userIn;
	string startSquare;
	string endSquare;
	string result;


	cout << "welcome to 2-player chess! enter input as shown: squareToStart squareToEnd" << endl;
	cout << "for example, to move the piece at A1 to B2, you would type:\n";
	cout << "A1 B2" << endl;
	board.initialize();

	while (userIn != "exit") {

		cout << "Player1, enter square with piece you are going to move." << endl;
		cin >> startSquare;
		actionCheck(startSquare);
		cout << "Player1, enter square piece will be moved to." << endl;
		cin >> endSquare;
		actionCheck(endSquare);
		
		cout << "Player1, you have decided to move " << startSquare << " to " << endSquare << endl;
		board.movePiece(startSquare, endSquare);
		board.initialize();
			
		// add logic to check if game is over 

		cout << "Player2, enter square with piece you are going to move." << endl;
		cin >> startSquare;
		actionCheck(startSquare);
		cout << "Player2, enter square piece will be moved to." << endl;
		cin >> endSquare;
		actionCheck(endSquare);

		cout << "Player2, you have decided to move " << startSquare << " to " << endSquare << endl;
		board.movePiece(startSquare, endSquare);
		board.initialize();

		// add logic to check if game is over
	}



}





int main()
{
	cout << "Welcome to Chess-C! Choose an option below:" << endl;
	cout << "a. 2-player" << endl;
	cout << "b. 1-player (n/a at the time!)" << endl;
	cout << "c. 0-player (n/a at the time!)" << endl << endl;
	
	string userIn;
	bool valid = false;
	
	while (!valid) {
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
	}
	
	if (userIn == "a") {
		twoPlayer();
	}


	return 0;
	


}
