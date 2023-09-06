#pragma once
#include "stdafx.h"

class Board {
public:
	void printBoard(char symbol);
	//bool isValidMove(string move);
	void placeStone(string move,char symbol);

	bool isEmptyCell(int row, int col) const;

	bool checkFive(int row,int col, int symbol);

	bool checkDirection(int row, int col, int symbol, int deltaRow, int deltaColumn);

	void setGameOver(bool isOver) {
		gameOver = isOver;
	}

	bool isGameOver() const {
		return gameOver;
	}
	bool checkCapture(int row, int col, int symbol);
	bool checkCaptureDirection(int row, int col, int symbol, int deltaRow, int deltaColumn);
private:
	int board[19][19] = { 0 };
	bool gameOver = false;
	
};