#include "Board_Piece.h"
#define WHITE_SQUARE 0xDB
#define BLACK_SQUARE 0xFF

// initializes board to 0 state
Board::Board() {
	initBoard();
}
// sets up 2D array which holds all pieces
void Board::initBoard() {
	Board::curBoard = { {Piece(Type::ROOK, Color::BLACK), Piece(Type::KNIGHT, Color::BLACK), Piece(Type::BISHOP, Color::BLACK),
		Piece(Type::KING, Color::BLACK), Piece(Type::QUEEN, Color::BLACK), Piece(Type::BISHOP, Color::BLACK),
		Piece(Type::KNIGHT, Color::BLACK), Piece(Type::ROOK, Color::BLACK)} ,
		{Piece(Type::PAWN, Color::BLACK), Piece(Type::PAWN, Color::BLACK), Piece(Type::PAWN, Color::BLACK),
			Piece(Type::PAWN, Color::BLACK), Piece(Type::PAWN, Color::BLACK), Piece(Type::PAWN, Color::BLACK),
			Piece(Type::PAWN, Color::BLACK), Piece(Type::PAWN, Color::BLACK)} ,
			{Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece()},
			{Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece()},
			{Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece()},
			{Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece()},
			{Piece(Type::PAWN, Color::WHITE), Piece(Type::PAWN, Color::WHITE), Piece(Type::PAWN, Color::WHITE),
				Piece(Type::PAWN, Color::WHITE), Piece(Type::PAWN, Color::WHITE), Piece(Type::PAWN, Color::WHITE),
				Piece(Type::PAWN, Color::WHITE), Piece(Type::PAWN, Color::WHITE)},
				{Piece(Type::ROOK, Color::WHITE), Piece(Type::KNIGHT, Color::WHITE), Piece(Type::BISHOP, Color::WHITE),
					Piece(Type::KING, Color::WHITE), Piece(Type::QUEEN, Color::WHITE), Piece(Type::BISHOP, Color::WHITE),
					Piece(Type::KNIGHT, Color::WHITE), Piece(Type::ROOK, Color::WHITE)} };
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			curBoard[r][c].setLocation(Point(r, c));
		}
	}
}
// prints 2D array out as formatted board
void Board::printBoard(string boardType) {
	if (boardType == "c") {
		printBoardFormat();
		return;
	}
	cout << endl << endl;
	for (int i = 0; i < 8; i++) {
		printf("%6s", boardLabelsX[i].c_str());
	}
	cout << endl;
	for (int r = 0; r < 8; r++) {
		cout << boardLabelsY[r] << " ";
		for (int c = 0; c < 8; c++) {
			cout << "| " << curBoard[r][c].getBoardName() << " |";
		}
		cout << endl << endl;
	}
	cout << endl;
}
void Board::printBoardFormat() {
	int r = 0;
	int c = 0;

	for (int i = 0; i < 8; i++) {
		printf("%9s", boardLabelsX[i].c_str());
	}
	cout << endl;

	int yLabel = 0;

	for (int k = 0; k < 4; k++) {

		cout << boardLabelsY[yLabel] << "   ";
		for (int j = 0; j < 5; j++) {

			bool toggle = false;

			if (j == 2) {
				int tempI = 0;
				cout << "    ";
				for (int i = 0; i < 70; i++) {
					if (i % 9 == 0) {
						toggle = !toggle;
						tempI = 0;
					}
					tempI++;
					if (tempI == 4) {
						if (curBoard[r][c].getType() != Type::EMPTY) {
							cout << curBoard[r][c].getBoardName();
						}
						else {
							if (toggle) {
								cout << char(WHITE_SQUARE);
								cout << char(WHITE_SQUARE);
							}
							else {
								cout << char(BLACK_SQUARE);
								cout << char(BLACK_SQUARE);
							}
						}
						if (c < 7) {
							c++;
						}
						else {
							c = 0;
							r++;
						}
						i++;
					}
					else {
						if (toggle)
							cout << char(WHITE_SQUARE);
						else
							cout << char(BLACK_SQUARE);
					}
				}
			}
			else {
				if(j != 0)
					cout << "    ";
				for (int i = 0; i < 70; i++) {
					if (i % 9 == 0)
						toggle = !toggle;
					if (toggle)
						cout << char(WHITE_SQUARE);
					else
						cout << char(BLACK_SQUARE);
				}
			}

			cout << endl;
		}
		yLabel++;

		cout << boardLabelsY[yLabel] << "   ";
		for (int j = 0; j < 5; j++) {

			bool toggle = false;

			if (j == 2) {
				int tempI = 0;
				cout << "    ";
				for (int i = 0; i < 70; i++) {
					if (i % 9 == 0) {
						toggle = !toggle;
						tempI = 0;
					}
					tempI++;
					if (tempI == 4) {
						if (curBoard[r][c].getType() != Type::EMPTY) {
							cout << curBoard[r][c].getBoardName();
						}
						else {
							if (toggle) {
								cout << char(BLACK_SQUARE);
								cout << char(BLACK_SQUARE);
							}
							else {
								cout << char(WHITE_SQUARE);
								cout << char(WHITE_SQUARE);
							}
						}
						if (c < 7) {
							c++;
						}
						else {
							c = 0;
							r++;
						}
						i++;
					}
					else {
						if (toggle)
							cout << char(BLACK_SQUARE);
						else
							cout << char(WHITE_SQUARE);
					}
				}
			}
			else {
				if (j != 0)
					cout << "    ";
				for (int i = 0; i < 70; i++) {
					if (i % 9 == 0)
						toggle = !toggle;
					if (toggle)
						cout << char(BLACK_SQUARE);
					else
						cout << char(WHITE_SQUARE);
				}
			}

			cout << endl;
		}
		yLabel++;
	}




}
// sets this board to another board
void Board::setBoard(vector<vector<Piece>> board) {
	curBoard = board;
}
// returns the 2D array of this board
vector<vector<Piece>> Board::returnBoard() {
	return curBoard;
}
// checks whether a given point is in bounds of the board (8x8)
bool Board::checkBounds(Point p) {
	if (!(p.row >= 0 && p.row <= 7))
		return false;
	if (!(p.col >= 0 && p.col <= 7))
		return false;
	return true;
}

/* moves a piece from a valid startpt to a valid endpt for a given player.
	 first checks whether the piece at the startpt exists and is the player's color.
	 then generates all valid moves for that piece, and checks if the given endpt
	 is in that set of valid moves. If it is, then move is made.
*/
Piece Board::movePiece(Point startPt, Point endPt, Color playerColor) {

	Piece startPiece = curBoard[startPt.row][startPt.col];
	Piece endPiece = curBoard[endPt.row][endPt.col];

	if (startPiece.getType() == Type::EMPTY)
		return Piece(-1);
	if (startPiece.getColor() == Color::WHITE && playerColor != Color::WHITE)
		return Piece(-1);
	if (startPiece.getColor() == Color::BLACK && playerColor != Color::BLACK)
		return Piece(-1);
	if (startPt.row == endPt.row && startPt.col == endPt.col)
		return Piece(-1);

	vector<Point> validMoves = startPiece.generateMoves(*this);

	// for testing purposes prints out all moves on given board
	/*for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			vector<Point> moves = curBoard[r][c].generateMoves(*this);
			string cold;

			switch (curBoard[r][c].getColor()) {
			case Color::EMPTY:
				cold = "empty";
				break;
			case Color::WHITE:
				cold = "white";
				break;
			case Color::BLACK:
				cold = "black";
				break;
			}

			string s = "";
			switch (curBoard[r][c].getStatus()) {
			case Status::EMPTY:
				s = "empty";
				break;
			case Status::INGAME:
				s = "ingame";
				break;
			case Status::SPAWN:
				s = "spawn";
				break;
			}

			cout << curBoard[r][c].returnBoardName() << " " << cold << " " << s <<  8 - curBoard[r][c].getLocation().row << curBoard[r][c].getLocation().col << endl;
			for (int i = 0; i < moves.size(); i++) {
				cout << 8 - moves[i].row << "//" << moves[i].col << "    " << endl;
			}
			cout << endl;
		}
	}*/

	bool validMatch = false;
	for (Point validMove : validMoves) {
		if (endPt.row == validMove.row && endPt.col == validMove.col) {
			validMatch = true;
			break;
		}
	}

	// if user-endpt was in the valid moveset, make move
	if (validMatch) {
		startPiece.setLocation(Point(endPt.row, endPt.col));
		startPiece.setStatus(Status::INGAME);
		curBoard[endPt.row][endPt.col] = startPiece;
		Piece replacePiece;
		replacePiece.setLocation(Point(startPt.row, endPt.col));
		curBoard[startPt.row][startPt.col] = replacePiece;
	}
	else {
		// otherwise, return an invalid piece holder
		return Piece(-1);
	}

	// if user-endpt was occupied by enemy, then update taken piece
	if (endPiece.getType() != Type::EMPTY) {
		endPiece.setLocation(Point(-1, -1));
		endPiece.setStatus(Status::TAKEN);
	}

	// return either taken or empty location
	return endPiece;
}
// retrieves a given piece from the board
Piece Board::getPiece(int row, int col) {
	bool valid = checkBounds(Point(row, col));
	if (valid)
		return curBoard[row][col];
	return Piece(-1);
}

// checks if white is in check
bool Board::isInCheckWhite(Piece whiteKing, Board givenBoard) {

	vector<vector<Piece>> board = givenBoard.returnBoard();
	int kwRow = whiteKing.getLocation().row;
	int kwCol = whiteKing.getLocation().col;

	// downward check
	for (int r = kwRow; r < 8; r++) {
		Piece otherPiece = board[r][kwCol];
		if (otherPiece.getColor() == Color::WHITE && kwRow != r)
			break;
		if (otherPiece.getColor() == Color::BLACK) {
			if (otherPiece.getType() == Type::ROOK || otherPiece.getType() == Type::QUEEN)
				return true;
			break;
		}
	}

	// upward check
	for (int r = kwRow; r >= 0; r--) {
		Piece otherPiece = board[r][kwCol];
		if (otherPiece.getColor() == Color::WHITE && kwRow != r)
			break;
		if (otherPiece.getColor() == Color::BLACK) {
			if (otherPiece.getType() == Type::ROOK || otherPiece.getType() == Type::QUEEN)
				return true;
			break;
		}
	}

	// rightward check
	for (int c = kwCol; c < 8; c++) {
		Piece otherPiece = board[kwRow][c];
		if (otherPiece.getColor() == Color::WHITE && kwCol != c)
			break;
		if (otherPiece.getColor() == Color::BLACK) {
			if (otherPiece.getType() == Type::ROOK || otherPiece.getType() == Type::QUEEN)
				return true;
			break;
		}
	}

	// leftward check
	for (int c = kwCol; c >= 0; c--) {
		Piece otherPiece = board[kwRow][c];
		if (otherPiece.getColor() == Color::WHITE && kwCol != c)
			break;
		if (otherPiece.getColor() == Color::BLACK) {
			if (otherPiece.getType() == Type::ROOK || otherPiece.getType() == Type::QUEEN)
				return true;
			break;
		}
	}

	// southeast check
	int tempCol = kwCol;
	for (int r = kwRow; r < 8; r++) {
		if (kwRow == r)
			continue;
		tempCol++;
		if (!checkBounds(Point(r, tempCol)))
			break;

		Piece otherPiece = board[r][tempCol];
		if (otherPiece.getColor() == Color::WHITE)
			break;
		if (otherPiece.getColor() == Color::BLACK) {
			if (otherPiece.getType() == Type::QUEEN || otherPiece.getType() == Type::BISHOP)
				return true;
			break;
		}
	}

	// northeast check
	tempCol = kwCol;
	for (int r = kwRow; r >= 0; r--) {
		if (kwRow == r)
			continue;
		tempCol++;
		if (!checkBounds(Point(r, tempCol)))
			break;

		Piece otherPiece = board[r][tempCol];
		if (otherPiece.getColor() == Color::WHITE)
			break;
		if (otherPiece.getColor() == Color::BLACK) {
			if (otherPiece.getType() == Type::QUEEN || otherPiece.getType() == Type::BISHOP)
				return true;
			if (otherPiece.getType() == Type::PAWN) {
				if (r == kwRow - 1)
					return true;
			}
			break;
		}
	}

	// southwest check
	tempCol = kwCol;
	for (int r = kwRow; r < 8; r++) {
		if (kwRow == r)
			continue;
		tempCol--;
		if (!checkBounds(Point(r, tempCol)))
			break;

		Piece otherPiece = board[r][tempCol];
		if (otherPiece.getColor() == Color::WHITE)
			break;
		if (otherPiece.getColor() == Color::BLACK) {
			if (otherPiece.getType() == Type::QUEEN || otherPiece.getType() == Type::BISHOP)
				return true;
			break;
		}
	}

	// northwest check
	tempCol = kwCol;
	for (int r = kwRow; r >= 0; r--) {
		if (kwRow == r)
			continue;
		tempCol--;
		if (!checkBounds(Point(r, tempCol)))
			break;

		Piece otherPiece = board[r][tempCol];
		if (otherPiece.getColor() == Color::WHITE)
			break;
		if (otherPiece.getColor() == Color::BLACK) {
			if (otherPiece.getType() == Type::QUEEN || otherPiece.getType() == Type::BISHOP)
				return true;
			if (otherPiece.getType() == Type::PAWN) {
				if (r == kwRow - 1)
					return true;
			}
			break;
		}
	}

	// knight capture check
	vector<Point> possibleKnightLoc;
	possibleKnightLoc.push_back(Point(kwRow + 2, kwCol + 1));
	possibleKnightLoc.push_back(Point(kwRow + 2, kwCol - 1));
	possibleKnightLoc.push_back(Point(kwRow + 1, kwCol + 2));
	possibleKnightLoc.push_back(Point(kwRow + 1, kwCol - 2));
	possibleKnightLoc.push_back(Point(kwRow - 2, kwCol + 1));
	possibleKnightLoc.push_back(Point(kwRow - 2, kwCol - 1));
	possibleKnightLoc.push_back(Point(kwRow - 1, kwCol + 2));
	possibleKnightLoc.push_back(Point(kwRow - 1, kwCol - 2));

	for (int i = 0; i < possibleKnightLoc.size(); i++) {
		if (!checkBounds(possibleKnightLoc[i]))
			continue;
		int r = possibleKnightLoc[i].row;
		int c = possibleKnightLoc[i].col;
		if (board[r][c].getType() == Type::KNIGHT && board[r][c].getColor() == Color::BLACK) {
			return true;
			break;
		}
	}

	return false;
}
// checks if black is in check
bool Board::isInCheckBlack(Piece blackKing, Board givenBoard) {

	vector<vector<Piece>> board = givenBoard.returnBoard();
	int kbRow = blackKing.getLocation().row;
	int kbCol = blackKing.getLocation().col;

	// downward check
	for (int r = kbRow; r < 8; r++) {
		Piece otherPiece = board[r][kbCol];
		if (otherPiece.getColor() == Color::BLACK && kbRow != r)
			break;
		if (otherPiece.getColor() == Color::WHITE) {
			if (otherPiece.getType() == Type::ROOK || otherPiece.getType() == Type::QUEEN)
				return true;
			break;
		}
	}

	// upward check
	for (int r = kbRow; r >= 0; r--) {
		Piece otherPiece = board[r][kbCol];
		if (otherPiece.getColor() == Color::BLACK && kbRow != r)
			break;
		if (otherPiece.getColor() == Color::WHITE) {
			if (otherPiece.getType() == Type::ROOK || otherPiece.getType() == Type::QUEEN)
				return true;
			break;
		}
	}

	// rightward check
	for (int c = kbCol; c < 8; c++) {
		Piece otherPiece = board[kbRow][c];
		if (otherPiece.getColor() == Color::BLACK && kbCol != c)
			break;
		if (otherPiece.getColor() == Color::WHITE) {
			if (otherPiece.getType() == Type::ROOK || otherPiece.getType() == Type::QUEEN)
				return true;
			break;
		}
	}

	// leftward check
	for (int c = kbCol; c >= 0; c--) {
		Piece otherPiece = board[kbRow][c];
		if (otherPiece.getColor() == Color::BLACK && kbCol != c)
			break;
		if (otherPiece.getColor() == Color::WHITE) {
			if (otherPiece.getType() == Type::ROOK || otherPiece.getType() == Type::QUEEN)
				return true;
			break;
		}
	}

	// southeast check
	int tempCol = kbCol;
	for (int r = kbRow; r < 8; r++) {
		if (kbRow == r)
			continue;
		tempCol++;

		if (!checkBounds(Point(r, tempCol)))
			break;

		Piece otherPiece = board[r][tempCol];
		if (otherPiece.getColor() == Color::BLACK)
			break;
		if (otherPiece.getColor() == Color::WHITE) {
			if (otherPiece.getType() == Type::QUEEN || otherPiece.getType() == Type::BISHOP)
				return true;
			if (otherPiece.getType() == Type::PAWN) {
				if (r == kbRow + 1)
					return true;
			}
			break;
		}
	}

	// northeast check
	tempCol = kbCol;
	for (int r = kbRow; r >= 0; r--) {
		if (kbRow == r)
			continue;
		tempCol++;
		if (!checkBounds(Point(r, tempCol)))
			break;

		Piece otherPiece = board[r][tempCol];
		if (otherPiece.getColor() == Color::BLACK)
			break;
		if (otherPiece.getColor() == Color::WHITE) {
			if (otherPiece.getType() == Type::QUEEN || otherPiece.getType() == Type::BISHOP)
				return true;
			break;
		}
	}

	// southwest check
	tempCol = kbCol;
	for (int r = kbRow; r < 8; r++) {
		if (kbRow == r)
			continue;
		tempCol--;
		if (!checkBounds(Point(r, tempCol)))
			break;

		Piece otherPiece = board[r][tempCol];
		if (otherPiece.getColor() == Color::BLACK)
			break;
		if (otherPiece.getColor() == Color::WHITE) {
			if (otherPiece.getType() == Type::QUEEN || otherPiece.getType() == Type::BISHOP)
				return true;
			if (otherPiece.getType() == Type::PAWN) {
				if (r == kbRow + 1)
					return true;
			}
			break;
		}
	}

	// northwest check
	tempCol = kbCol;
	for (int r = kbRow; r >= 0; r--) {
		if (kbRow == r)
			continue;
		tempCol--;
		if (!checkBounds(Point(r, tempCol)))
			break;

		Piece otherPiece = board[r][tempCol];
		if (otherPiece.getColor() == Color::BLACK)
			break;
		if (otherPiece.getColor() == Color::WHITE) {
			if (otherPiece.getType() == Type::QUEEN || otherPiece.getType() == Type::BISHOP)
				return true;
			break;
		}
	}

	// knight capture check
	vector<Point> possibleKnightLoc;
	possibleKnightLoc.push_back(Point(kbRow + 2, kbCol + 1));
	possibleKnightLoc.push_back(Point(kbRow + 2, kbCol - 1));
	possibleKnightLoc.push_back(Point(kbRow + 1, kbCol + 2));
	possibleKnightLoc.push_back(Point(kbRow + 1, kbCol - 2));
	possibleKnightLoc.push_back(Point(kbRow - 2, kbCol + 1));
	possibleKnightLoc.push_back(Point(kbRow - 2, kbCol - 1));
	possibleKnightLoc.push_back(Point(kbRow - 1, kbCol + 2));
	possibleKnightLoc.push_back(Point(kbRow - 1, kbCol - 2));

	for (int i = 0; i < possibleKnightLoc.size(); i++) {
		if (!checkBounds(possibleKnightLoc[i]))
			continue;
		int r = possibleKnightLoc[i].row;
		int c = possibleKnightLoc[i].col;
		if (board[r][c].getType() == Type::KNIGHT && board[r][c].getColor() == Color::WHITE) {
			return true;
			break;
		}
	}

	return false;
}
// checks if white is in checkmate (uses check method for all possible king moves)
bool Board::isInCheckmateWhite(Piece whiteKing) {

	bool stillCheck = false;
	vector<Point> kingMoves = whiteKing.generateMoves(*this);
	for (int i = 0; i < kingMoves.size(); i++) {
		Board newBoard;
		newBoard.setBoard(this->returnBoard());
		newBoard.movePiece(whiteKing.getLocation(), kingMoves[i], Color::WHITE);
		stillCheck = isInCheckBlack(whiteKing, newBoard);
		if (stillCheck == false)
		break;
	}

	return stillCheck;
}
// checks if black is in checkmate (uses check method for all possible king moves)
bool Board::isInCheckmateBlack(Piece blackKing) {

	bool stillCheck = false;
	vector<Point> kingMoves = blackKing.generateMoves(*this);
	for (int i = 0; i < kingMoves.size(); i++) {
		Board newBoard;
		newBoard.setBoard(this->returnBoard());
		newBoard.movePiece(blackKing.getLocation(), kingMoves[i], Color::BLACK);
		stillCheck = isInCheckBlack(blackKing, newBoard);
		if (stillCheck == false)
			break;
	}

	return stillCheck;
}
// checks if a game has been won (or is in check)
Color Board::checkWin() {

	bool blackHasKing = false;
	bool whiteHasKing = false;
	Piece blackKing;
	Piece whiteKing;

	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			if (curBoard[r][c].getBoardName() == "kw") {
				whiteHasKing = true;
				whiteKing = curBoard[r][c];
			}

			if (curBoard[r][c].getBoardName() == "kb") {
				blackHasKing = true;
				blackKing = curBoard[r][c];
			}

			if (blackHasKing && whiteHasKing)
			break;
		}
	}

	if (!blackHasKing) {
		return Color::WHITE;
	}
	if (!whiteHasKing) {
		return Color::BLACK;
	}

	// check & checkmate functionality
	bool whiteInCheck = isInCheckWhite(whiteKing, *this);
	bool blackInCheck = isInCheckBlack(blackKing, *this);

	if (blackInCheck) {
		if (isInCheckmateBlack(blackKing))
			return Color::WHITE;
		else
			return Color::CHECK_BLACK;
	}

	if (whiteInCheck) {
		if (isInCheckmateWhite(whiteKing))
			return Color::BLACK;
		else
			return Color::CHECK_WHITE;
	}

	return Color::EMPTY;
}
// prints winner based on results of checkWin()
Color Board::printWinner() {
	Color winner = checkWin();
	if (winner == Color::WHITE) {
		cout << "WHITE has won!";
		return Color::WHITE;
	}
	else if (winner == Color::BLACK) {
		cout << "BLACK has won!";
		return Color::BLACK;
	}
	else if (winner == Color::CHECK_BLACK) {
		cout << "BLACK in check!";
	}
	else if (winner == Color::CHECK_WHITE) {
		cout << "WHITE in check!";
	}
	cout << endl;
	return Color::EMPTY;
}
