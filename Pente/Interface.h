#pragma once

#include "Board.h"
#include "Player.h"

class Interface {
public:
	Interface();
	~Interface();

	void startMenu();
	void startGame(Board B);



private:
	Board B;
	HumanPlayer human;
	ComputerPlayer computer;
};