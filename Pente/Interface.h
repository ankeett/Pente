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
	Player* playerList[2];
	int currentPlayerIndex;
};