#pragma once
#include "stdafx.h"

#include "Board.h"

class Strategy {
public:
	Strategy(Board& B, int playerSymbol);

	~Strategy();

	void setPlayerScore(int score) {
		tempPlayerScore = score;
	}

	void setOpponentScore(int score) {
		tempOpponentScore = score;
	}

	int getPlayerScore() const {
		return tempPlayerScore;
	}

	int getOpponentScore() const {
		return tempOpponentScore;
	}


	//evaluate all the possible cases and give best result
	pair<int, int> evaluateAllCases(Board B, int playerSymbol);
	pair<int,int> evaluateSecondMove(Board B, int playerSymbol);

	pair<int,int> evaluateOffense(Board B, int playerSymbol);
	pair<int,int> evaluateDefense(Board B, int playerSymbol);



private:
	pair<int,int> findWinningMove(Board B,int playerSymbol);
	pair<int, int> defendWinningMove(Board B, int playerSymbol);
	pair<int, int> captureOpponent(Board B, int playerSymbol);
	pair<int, int> defendCapture(Board B, int playerSymbol);
	pair<int, int> randomMove(Board B, int playerSymbol);
	pair<int, int> defendFour(Board B, int playerSymbol); 
	pair<int, int> maxConsecutive(Board B, int playerSymbol);
	pair<int, int> controlCenter(Board B, int playerSymbol);

	Board board;
	int playerSymbol;

	int tempPlayerScore = 0;
	int tempOpponentScore = 0;
};