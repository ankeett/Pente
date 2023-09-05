#pragma once

#include "stdafx.h"
#include "Board.h"

class Player {
public:
	Player(char symbol);

	virtual void makeMove(Board& B) = 0; //pure virtual function
	char getSymbol() const;
	void setSymbol(char newSymbol);

protected:
	bool isValidMove(const Board& B, int row, int col) const;

private:

	char symbol;
};

class HumanPlayer : public Player {
public:
	HumanPlayer(char symbol);

	void makeMove(Board& B) override;
};

class ComputerPlayer :public Player {
public:
	ComputerPlayer(char symbol);

	void makeMove(Board& B) override;
};