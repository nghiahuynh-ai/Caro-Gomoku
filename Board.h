#pragma once
#include "Common.h"
#include <iostream>
#include <vector>
using namespace std;

#define BOARD_SIZE	21
#define BLUE		9
#define RED			12
#define WHITE		15

class Board
{
private:
	int boardSize = BOARD_SIZE;
	int** board;
	int player;
	int totalMoves = 0;
	void goLeft();				// move cursor to the left
	void goRight();				// move cursor to the right
	void goUp();				// move cursor up
	void goDown();				// move cursor down
	void printLabel();			// print "O" if player = 1, "X" if player = -1 
	void printLayout();			// draw a grid
	int xConverter(int);		// convert cursor's latitude to row index
	int yConverter(int);		// convert cursor's longtitude to column index
	void toggle();				// toggle player between 1 and -1 after every single move
	bool isValid(int, int);		// check if a position of the board is occupied or not
	bool isFull();				// check if the board is full or not
	void makeMove(int, int);	// update the board with current player value at chosen position
	bool isWin(int, int);		// check if current player has won with the last move or not

public:
	Board();
	~Board();
	int getBoardSize();
	void play();
};

Board::Board() {
	srand(time(NULL));
	int firstMove = rand() % 2;
	if (firstMove) player = 1;
	else player = -1;

	board = new int* [boardSize];
	for (int i = 0; i < boardSize; i++) {
		board[i] = new int[boardSize];
		for (int j = 0; j < boardSize; j++) {
			board[i][j] = 0;
		}
	}
}

Board::~Board() {}

int Board::getBoardSize() {
	return boardSize;
}

void Board::goLeft() {
	int x = getX(), y = getY();
	if (x >= 4) x -= 4;
	gotoXY(x, y);
}

void Board::goRight() {
	int x = getX(), y = getY();
	if (x <= (boardSize * 4 - 5)) x += 4;
	gotoXY(x, y);
}

void Board::goUp() {
	int x = getX(), y = getY();
	if (y >= 2) y -= 2;
	gotoXY(x, y);
}

void Board::goDown() {
	int x = getX(), y = getY();
	if (y <= (boardSize * 2 - 2)) y += 2;
	gotoXY(x, y);
}

void Board::printLabel() {
	if (player == 1) {
		setColor(BLUE);
		cout << "O";
	}
	else {
		setColor(RED);
		cout << "X";
	}
	setColor(WHITE);
}

void Board::printLayout() {
	int ceil = 1;

	cout << char(218);
	for (int i = 0; i < boardSize - 1; i++) cout << char(196) << char(196) << char(196) << char(194);
	cout << char(196) << char(196) << char(196) << char(191);

	gotoXY(0, ceil);
	ceil++;
	for (int i = 0; i < boardSize - 1; i++) {
		for (int i = 0; i <= boardSize; i++) cout << char(179) << "   ";
		gotoXY(0, ceil);
		ceil++;

		cout << char(195);
		for (int i = 0; i < boardSize - 1; i++) cout << char(196) << char(196) << char(196) << char(197);
		cout << char(196) << char(196) << char(196) << char(180);
		gotoXY(0, ceil);
		ceil++;
	}

	for (int i = 0; i <= boardSize; i++) cout << char(179) << "   ";

	gotoXY(0, ceil);
	ceil++;
	cout << char(192);
	for (int i = 0; i < boardSize - 1; i++) cout << char(196) << char(196) << char(196) << char(193);
	cout << char(196) << char(196) << char(196) << char(217);
}

int Board::xConverter(int x) {
	return (x + 2) / 4 - 1;
}

int Board::yConverter(int y) {
	return (y - 1) / 2;
}

void Board::toggle() {
	player *= -1;
}

bool Board::isValid(int x, int y) {
	if (x < 0 || x >= boardSize || y < 0 || y >= boardSize || board[x][y] != 0) return 0;
	return 1;
}

bool Board::isFull() {
	if (totalMoves == boardSize * boardSize) return 1;
	else return 0;
}

void Board::makeMove(int x, int y) {
	board[x][y] = player;
	totalMoves++;
}

bool Board::isWin(int x, int y) {
	// check row (east - west)
	int E_S = 1;
	bool bound1 = 0, bound2 = 0;
	if (x > 0) {
		for (int i = x - 1; i >= 0; i--) {
			if (board[i][y] == player) E_S++;
			else if (board[i][y] == -player) {
				bound1 = 1;
				break;
			}
			else break;
		}
	}
	if (x < boardSize - 1) {
		for (int i = x + 1; i <= boardSize - 1; i++) {
			if (board[i][y] == player) E_S++;
			else if (board[i][y] == -player) {
				bound2 = 1;
				break;
			}
			else break;
		}
	}
	if (E_S >= 5 && (!bound1 || !bound2)) return 1;

	// check column (north - south) 
	int N_S = 1;
	bound1 = 0;
	bound2 = 0;
	if (y > 0) {
		for (int j = y - 1; j >= 0; j--) {
			if (board[x][j] == player) N_S++;
			else if (board[x][j] == -player) {
				bound1 = 1;
				break;
			}
			else break;
		}
	}
	if (y < boardSize - 1) {
		for (int j = y + 1; j <= boardSize - 1; j++) {
			if (board[x][j] == player) N_S++;
			else if (board[x][j] == -player) {
				bound2 = 1;
				break;
			}
			else break;
		}
	}
	if (N_S >= 5 && (!bound1 || !bound2)) return 1;

	// check northeast - southwest cross
	int NE_SW = 1;
	bound1 = 0;
	bound2 = 0;
	if (x > 0 && y < boardSize - 1) {
		int j = y + 1;
		for (int i = x - 1; i >= 0; i--) {
			if (board[i][j] == player) {
				NE_SW++;
				j++;
				if (j > boardSize - 1) break;
			}
			else if (board[i][j] == -player) {
				bound1 = 1;
				break;
			}
			else break;
		}
	}
	if (x < boardSize - 1 && y > 0) {
		int j = y - 1;
		for (int i = x + 1; i <= boardSize - 1; i++) {
			if (board[i][j] == player) {
				NE_SW++;
				j--;
				if (j < 0) break;
			}
			else if (board[i][j] == -player) {
				bound2 = 1;
				break;
			}
			else break;
		}
	}
	if (NE_SW >= 5 && (!bound1 || !bound2)) return 1;

	// check northwest - southeast cross
	int NW_SE = 1;
	bound1 = 0;
	bound2 = 0;
	if (x < boardSize - 1 && y < boardSize - 1) {
		int j = y + 1;
		for (int i = x + 1; i <= boardSize - 1; i++) {
			if (board[i][j] == player) {
				NW_SE++;
				j++;
				if (j > boardSize - 1) break;
			}
			else if (board[i][j] == -player) {
				bound1 = 1;
				break;
			}
			else break;
		}
	}
	if (x > 0 && y > 0) {
		int j = y - 1;
		for (int i = x - 1; i >= 0; i--) {
			if (board[i][j] == player) {
				NW_SE++;
				j--;
				if (j < 0) break;
			}
			else if (board[i][j] == -player) {
				bound2 = 1;
				break;
			}
			else break;
		}
	}
	if (NW_SE >= 5 && (!bound1 || !bound2)) return 1;
	return 0;
}

void Board::play() {
	printLayout();
	cout << endl << "Turn of ";
	int x = (boardSize * 4 + 1) / 2;
	int y = (boardSize * 2 + 1) / 2;
	int i, j;

	while (true) {
		gotoXY(8, boardSize * 2 + 1);
		printLabel();
		gotoXY(x, y);

		do {
			while (true) {
				int key = getKey();
				if (key == 72) goUp();
				else if (key == 80) goDown();
				else if (key == 75) goLeft();
				else if (key == 77) goRight();
				else if (key == 13) {
					x = getX();
					y = getY();
					i = xConverter(x);
					j = yConverter(y);
					break;
				}
				else continue;
			}
		} while (!isValid(i, j));

		makeMove(i, j);

		printLabel();
		gotoXY(x, y);

		if (isWin(i, j)) {
			gotoXY(0, boardSize * 2 + 1);
			cout << "Player ";
			printLabel();
			cout << " won!" << endl;
			break;
		}
		else if (isFull()) {
			gotoXY(0, boardSize * 2 + 1);
			cout << "Draw!" << endl;
			break;
		}
		else toggle();
	}
}

