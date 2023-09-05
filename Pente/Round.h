#pragma once
#include "stdafx.h"
#include "Board.h"
#include "Player.h"

class Round {
public:
	Round();
	~Round();

	void startRound(Board B, Player& human, Player& computer);
	bool checkWin(Board B, Player& human, Player& computer);
	void checkCapture(Board B, Player& human, Player& computer);
	void checkFive(Board B, Player& human, Player& computer);
	void checkThree(Board B, Player& human, Player& computer);
	void checkFour(Board B, Player& human, Player& computer);
	void checkOpenFour(Board B, Player& human, Player& computer);
	void checkOpenThree(Board B, Player& human, Player& computer);
	void checkOpenTwo(Board B, Player& human, Player& computer);
	void checkOpenOne(Board B, Player& human, Player& computer);
	void checkClosedFour(Board B, Player& human, Player& computer);
	void checkClosedThree(Board B, Player& human, Player& computer);
	void checkClosedTwo(Board B, Player& human, Player& computer);
	
	void calculateScore(Board B, Player& human, Player& computer);

	private:
		
};