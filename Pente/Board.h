#pragma once
#include "stdafx.h"

class Board {
public:
	void printBoard(char symbol);

	void placeStone(string move,char symbol);

	bool isEmptyCell(int row, int col) const;

	bool checkFive(int row,int col, int symbol);

	int checkDirection(int row, int col, int symbol, int deltaRow, int deltaColumn);

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

	

private:
	int board[19][19] = { 0 };
	bool gameOver = false;
	
	int humanCaptures = 0;
	int computerCaptures = 0;

	//scores
	//captures
	
	//set who is the winner, winner is the one who puts 5 stones in a row
	//1 for human
	//2 for computer
	int winner = 0;
};