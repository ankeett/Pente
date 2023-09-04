#pragma once

#include "Board.h"

class Interface {
public:
	Interface();
	~Interface();

	void startMenu();
	void startGame(Board B);



private:
	Board B;
};