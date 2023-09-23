#pragma once
#include "stdafx.h"

class Board {
public:
	void printBoard(char symbol);

	void placeStone(string move,char symbol);

	bool isEmptyCell(int row, int col) const;

	bool checkFive(int row,int col, int symbol);
	bool checkFour(int row, int col, int symbol);

	int checkDirection(int row, int col, int symbol, int deltaRow, int deltaColumn,int count);

	void setGameOver(bool isOver) {
		gameOver = isOver;
	}

	bool isGameOver() const {
		return gameOver;
	}
	bool checkCapture(int row, int col, int symbol);
	bool checkCaptureDirection(int row, int col, int symbol, int deltaRow, int deltaColumn);

	int getHumanCaptures() const {
		return humanCaptures;
	}

	int getComputerCaptures() const {
		return computerCaptures;
	}

	void setHumanCaptures(int captures) {
		humanCaptures = captures;
	}

	void setComputerCaptures(int captures) {
		computerCaptures = captures;
	}

	void setWinner(int win) {
		winner = win;
	}

	int getWinner() const {
		return winner;
	}

	void setBoard(int row, int col, int symbol) {
		board[row-1][col] = symbol;
	}

	int getBoard(int row, int col) const {
		return board[row-1][col];
	}
	
	//setter and getter for move count
	void setMoveCount(int count) {
		moveCount = count;
	}

	int getMoveCount() const {
		return moveCount;
	}

	//check if the board is empty and return the total non zero cells
	int checkEmptyBoard() const {
		int count = 0;
		for (int i = 1; i <= 19; i++) {
			for (int j = 0; j < 19; j++) {
				if (board[i-1][j] != 0) {
					cout << board[i - 1][j] << endl;
					count++;
				}
			}
		}
		return count;
	}

	int calculateConsecutiveCount(int row, int col, int playerSymbol);

private:
	int board[19][19] = { 0 };
	/*int board[19][19] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};*/

	bool gameOver = false;
	
	int humanCaptures = 0;
	int computerCaptures = 0;

	int moveCount = 1;

	//scores
	//captures
	
	//set who is the winner, winner is the one who puts 5 stones in a row
	//1 for human
	//2 for computer
	int winner = 0;
};