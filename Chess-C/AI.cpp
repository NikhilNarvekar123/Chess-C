#include "AI.h"

vector<vector<Piece>> AI::simulateMove(Point startPt, Point endpt, vector<vector<Piece>> board) {
	Piece startPiece = board[startPt.row][startPt.col];
	Piece endPiece = board[endpt.row][endpt.col];

	board[endpt.row][endpt.col] = startPiece;
	board[startPt.row][startPt.col] = Piece();

	return board;
}

vector<vector<Piece>> AI::makeMove(vector<vector<Piece>> boardState) {

	boardStates = generateMoves(boardState, Color::BLACK);
	int maxMoveVal = INT_MIN;
	vector<vector<Piece>> bestBoardState;
	for (int i = 0; i < boardStates.size(); i++) {
		
		int value = runMinmax(1, boardStates[i], 0, 3);
		
		if (value > maxMoveVal) {
			maxMoveVal = value;
			bestBoardState = boardStates[i];
		}
	}

	return bestBoardState;
}


int AI::runMinmax(int player, vector<vector<Piece>> loopBoard, int curDepth, int maxDepth) {

	int winner = checkWin(loopBoard);
	if (winner == 1) {
		return -100;
	}
	else if (winner == 2) {
		return 100;
	}

	if (curDepth == maxDepth) {
		vector<int> valuations = returnValuation(loopBoard);
		return valuations[0] + valuations[1];
	}


	// human player
	if (player == 1) {

		boardStates = generateMoves(loopBoard, Color::WHITE);
	
		int minMoveValue = INT_MAX;
		vector<vector<Piece>> bestBoardState;
		for (int i = 0; i < boardStates.size(); i++) {
			int value = runMinmax(2, boardStates[i], curDepth + 1, 3);
			if (value < minMoveValue) {
				minMoveValue = value;
				bestBoardState = boardStates[i];
			}
		}

		return minMoveValue;

	}
	// ai player
	else {

		boardStates = generateMoves(loopBoard, Color::BLACK);
		
		int maxMoveValue = INT_MIN;
		vector<vector<Piece>> bestBoardState;
		for (int i = 0; i < boardStates.size(); i++) {
			int value = runMinmax(1, boardStates[i], curDepth + 1, 3);
			if (value > maxMoveValue) {
				maxMoveValue = value;
				bestBoardState = boardStates[i];
			}
		}

		return maxMoveValue;
	}




}


vector<vector<vector<Piece>>> AI::generateMoves(vector<vector<Piece>> boardState, Color color) {
	
	// fills in all possible moves for board
	
	boardStates = {};
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			Piece piece = boardState[r][c];
			Point curLocation;
			curLocation.row = r;
			curLocation.col = c;
			vector<vector<vector<Piece>>> tempList;
			if (piece.returnColor() == color) {
				if (piece.returnType() == Type::BISHOP)
					tempList = bishopMoves(boardState, piece, curLocation);
				if (piece.returnType() == Type::ROOK)
					tempList = rookMoves(boardState, piece, curLocation);
				if (piece.returnType() == Type::KING)
					tempList = kingMoves(boardState, piece, curLocation);
				if (piece.returnType() == Type::QUEEN)
					tempList = queenMoves(boardState, piece, curLocation);
				if (piece.returnType() == Type::KNIGHT)
					tempList = knightMoves(boardState, piece, curLocation);
				if (piece.returnType() == Type::PAWN)
					tempList = pawnMoves(boardState, piece, curLocation);
			}
			//cout << tempList.size() << " " << r << " " << c << "               ";
			for (int i = 0; i < tempList.size(); i++) {
				boardStates.push_back(tempList[i]);
			}
		}
	}

	return boardStates;
}

vector<vector<vector<Piece>>> AI::rookMoves(vector<vector<Piece>> boardState, Piece curPiece, Point startPt) {


	vector<vector<vector<Piece>>> tempList;

	// adding all valid moves in current column
	for (int r = 0; r < 8; r++) {

		Point endPt;
		endPt.row = r;
		endPt.col = startPt.col;

		if (curPiece.movePiece(startPt, endPt, boardState)) {
			if (startPt.row != endPt.row && startPt.col != endPt.col){
				tempList.push_back(simulateMove(startPt, endPt, boardState));
			}
		}
	}

	// adding all valid moves in current row
	for (int c = 0; c < 8; c++) {
		Point endPt;
		endPt.row = c;
		endPt.col = startPt.row;

		if (curPiece.movePiece(startPt, endPt, boardState)) {
			if (startPt.row != endPt.row && startPt.col != endPt.col)
				tempList.push_back(simulateMove(startPt, endPt, boardState));
		}
	}

	//cout << "rook passed" << endl;
	return tempList;

}

vector<vector<vector<Piece>>> AI::knightMoves(vector<vector<Piece>> boardState, Piece curPiece, Point startPt) {
	 
	vector<vector<vector<Piece>>> tempList;

	vector<Point> validEndpts;

	validEndpts.push_back(Point(startPt.row + 2, startPt.col + 1));
	validEndpts.push_back(Point(startPt.row + 2, startPt.col - 1));
	validEndpts.push_back(Point(startPt.row - 2, startPt.col - 1));
	validEndpts.push_back(Point(startPt.row - 2, startPt.col + 1));
	validEndpts.push_back(Point(startPt.row + 1, startPt.col - 2));
	validEndpts.push_back(Point(startPt.row + 1, startPt.col + 2));
	validEndpts.push_back(Point(startPt.row - 1, startPt.col - 2));
	validEndpts.push_back(Point(startPt.row - 1, startPt.col + 2));
	
	for (int i = 0; i < validEndpts.size(); i++) {
		if (!curPiece.checkBounds(validEndpts[i])) {
			continue;
		}
		if (curPiece.movePiece(startPt, validEndpts[i], boardState)) {
			if (startPt.row != validEndpts[i].row && startPt.col != validEndpts[i].col)
				tempList.push_back(simulateMove(startPt, validEndpts[i], boardState));
		}
	}

	//cout << "knight passed" << endl;
	return tempList;
}

vector<vector<vector<Piece>>> AI::bishopMoves(vector<vector<Piece>> boardState, Piece curPiece, Point startPt) {

	vector<vector<vector<Piece>>> tempList;
	Point endPt(startPt.row, startPt.col);


	// northwest
	while (curPiece.checkBounds(endPt)) {
		if (curPiece.movePiece(startPt, endPt, boardState)) {
			if (startPt.row != endPt.row && startPt.col != endPt.col)
				tempList.push_back(simulateMove(startPt, endPt, boardState));
		}
		endPt.row -= 1;
		endPt.col -= 1;
	}

	endPt.row = startPt.row;
	endPt.col = startPt.col;
	
	// southeast
	while (curPiece.checkBounds(endPt)) {
		if (curPiece.movePiece(startPt, endPt, boardState)) {
			if (startPt.row != endPt.row && startPt.col != endPt.col)
				tempList.push_back(simulateMove(startPt, endPt, boardState));
		}
		endPt.row += 1;
		endPt.col += 1;
	}

	endPt.row = startPt.row;
	endPt.col = startPt.col;

	// northeast
	while (curPiece.checkBounds(endPt)) {
		if (curPiece.movePiece(startPt, endPt, boardState)) {
			if (startPt.row != endPt.row && startPt.col != endPt.col)
				tempList.push_back(simulateMove(startPt, endPt, boardState));
		}
		endPt.row -= 1;
		endPt.col += 1;
	}

	endPt.row = startPt.row;
	endPt.col = startPt.col;

	// southwest
	while (curPiece.checkBounds(endPt)) {
		if (curPiece.movePiece(startPt, endPt, boardState)) {
			if (startPt.row != endPt.row && startPt.col != endPt.col)
				tempList.push_back(simulateMove(startPt, endPt, boardState));
		}
		endPt.row += 1;
		endPt.col -= 1;
	}

	//cout << "bids passed" << endl;
	return tempList;

}

vector<vector<vector<Piece>>> AI::queenMoves(vector<vector<Piece>> boardState, Piece curPiece, Point startPt) {

	vector<vector<vector<Piece>>> tempList;
	tempList = bishopMoves(boardState, curPiece, startPt);
	vector<vector<vector<Piece>>> temp = rookMoves(boardState, curPiece, startPt);

	for (int i = 0; i < temp.size(); i++) {
		tempList.push_back(temp[i]);
	}
	/*
	cout << "queen passed" << endl;*/

	return tempList;
}

vector<vector<vector<Piece>>> AI::kingMoves(vector<vector<Piece>> boardState, Piece curPiece, Point startPt) {
	
	vector<vector<vector<Piece>>> tempList;
	vector<Point> validEndpts;

	validEndpts.push_back(Point(startPt.row + 1, startPt.col));
	validEndpts.push_back(Point(startPt.row - 1, startPt.col));
	validEndpts.push_back(Point(startPt.row, startPt.col + 1));
	validEndpts.push_back(Point(startPt.row, startPt.col - 1));
	validEndpts.push_back(Point(startPt.row + 1, startPt.col + 1));
	validEndpts.push_back(Point(startPt.row - 1, startPt.col + 2));
	validEndpts.push_back(Point(startPt.row + 1, startPt.col - 2));
	validEndpts.push_back(Point(startPt.row - 1, startPt.col - 2));

	for (int i = 0; i < validEndpts.size(); i++) {
		if (!curPiece.checkBounds(validEndpts[i])) {
			continue;
		}
		if (curPiece.movePiece(startPt, validEndpts[i], boardState)) {
			if (startPt.row != validEndpts[i].row && startPt.col != validEndpts[i].col)
				tempList.push_back(simulateMove(startPt, validEndpts[i], boardState));
		}
	}

	//cout << "king passed" << endl;
	return tempList;

}

vector<vector<vector<Piece>>> AI::pawnMoves(vector<vector<Piece>> boardState, Piece curPiece, Point startPt) {
	
	vector<vector<vector<Piece>>> tempList;
	
	for (int r = 0; r < 8; r++) {
		Point endPt(r, startPt.col);
		if (curPiece.movePiece(startPt, endPt, boardState)) {
			if (startPt.row != endPt.row && startPt.col != endPt.col)
				tempList.push_back(simulateMove(startPt, endPt, boardState));
		}
	}

	//cout << "pawn passed" << endl;
	return tempList;
}

int AI::checkWin(vector<vector<Piece>> board) {

	bool blackHasKing = false;
	bool whiteHasKing = false;

	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			if (board[r][c].returnBoardName() == "kw")
				whiteHasKing = true;
			if (board[r][c].returnBoardName() == "kb")
				blackHasKing = true;
		}
	}

	if (!blackHasKing) {
		return 1;
	}
	if (!whiteHasKing) {
		return 2;
	}

	// checkmate functionality
	return 0;
}

vector<int> AI::returnValuation(vector<vector<Piece>> board) {

	int blackCount = 0;
	int whiteCount = 0;

	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			if (board[r][c].returnColor() == Color::BLACK) {
				blackCount++;
			}
			else if (board[r][c].returnColor() == Color::WHITE) {
				whiteCount++;
			}
		}
	}
	
	vector<int> values;
	values.push_back(blackCount * 5);
	values.push_back(whiteCount * 5);

	return values;
}
