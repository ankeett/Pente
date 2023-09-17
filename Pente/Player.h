#pragma once

#include "stdafx.h"
#include "Board.h"
#include "Strategy.h"

class Player {
public:
	Player(char symbol);
	virtual ~Player(); //default destructor

	virtual void makeMove(Board& B) = 0; //pure virtual function
	char getSymbol() const;
	void setSymbol(char newSymbol);
	void hasQuit(bool quit) {
		quitGame = quit;
	}
	bool getQuit() const {
		return quitGame;
	}

protected:
	bool isValidMove(const Board& B, int row, int col) const;
	
	
private:
	char symbol;
	bool quitGame;

};

class HumanPlayer : public Player {
public:
	HumanPlayer(char symbol);
	~HumanPlayer();

	void makeMove(Board& B) override;
};

class ComputerPlayer :public Player {
public:
	ComputerPlayer(char symbol);
	~ComputerPlayer();

	void makeMove(Board& B) override;
};
