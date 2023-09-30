#pragma once
#include "stdafx.h"
#include "Board.h"


class Serialization {

public:
	Serialization(Board& B);
	~Serialization();

	void readBoard(Board& B);

	void findColor(const string line);

	void setHumanColor(char stone) {
		humanColor = stone;
	}

	void setComputerColor(char stone) {
		computerColor = stone;
	}

	char getHumanColor() const {
		return humanColor;
	}

	char getComputerColor() const {
		return computerColor;
	}

	void setHumanCaptures(int captures) {
		humanCaptures = captures;
	}

	void setComputerCaptures(int captures) {
		computerCaptures = captures;
	}

	int getHumanCaptures() const {
		return humanCaptures;
	}

	int getComputerCaptures() const {
		return computerCaptures;
	}

	void setHumanScore(int score) {
		humanScore = score;
	}

	void setComputerScore(int score) {
		computerScore = score;
	}

	int getHumanScore() const {
		return humanScore;
	}

	int getComputerScore() const {
		return computerScore;
	}

	void setNextPlayer(string player) {
		nextPlayer = player;
	}

	string getNextPlayer() const {
		return nextPlayer;
	}

	string trim(const string& str);

	void writeIntoFile(Board& B);
	
	
private:
	Board board;
	char humanColor = 'W';
	char computerColor ='B';

	int humanCaptures = 0;
	int computerCaptures =0;

	int humanScore=0;
	int computerScore=0;

	string nextPlayer = "Human";
};