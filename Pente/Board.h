#pragma once
#include "stdafx.h"

class Board {
public:
	void printBoard(char symbol);
	//bool isValidMove(string move);
	void placeStone(string move,char symbol);

	bool isEmptyCell(int row, int col) const;

private:
	int board[19][19] = { 0 };
	
};