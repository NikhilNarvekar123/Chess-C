// Chess-C.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

using namespace std;



string actionCheck() {
	return "";
}

void twoPlayer() 
	
	fillBoard();

	string userIn;
	string piece;
	string square;
	string result;

	cout << "welcome to 2-player chess! enter input as shown: piecename, square" << endl;
	while (userIn != "exit") {

		cout << "Player1, enter piece to move and square to move it to." << endl;
		cin >> piece >> square;
		//input validation
		cout << "Player1, you have decided to move " << piece << " to " << square << endl;
		//move validation
		modifyBoard(piece, square);
		fillBoard();

		//capture/win validation
		result = actionCheck();

		cout << "Player2, enter piece to move and square to move it to." << endl;
		cin >> piece >> square;
		//input validation
		cout << "Player2, you have decided to move " << piece << " to " << square << endl;
		//move validation
		modifyBoard(piece, square);
		fillBoard();
		
		//capture/win validation
		result = actionCheck();
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

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
