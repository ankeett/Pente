#pragma once

#include "Board.h"
#include "Player.h"
#include "Serialization.h"

class Round {
public:
	Round(Player * playerList[2]);
	~Round();

	void startMenu();
	void continueMenu();
	void startGame(Board& B);
	void continueGame(Board& B);
	void calculateScores(Board& B);
	void printScores() const;


	int getHumanScore() const {
		return humanScore;
	}

	int getComputerScore() const {
		return computerScore;
	}

	void setHumanScore(int score) {
		humanScore = score;
	}

	void setComputerScore(int score) {
		computerScore = score;
	}

	void setWinner(int winner) {
		this->winner = winner;
	}

	int getWinner() const {
		return winner;
	}


	//quit the tournament or not
	bool quitTournament() const {
		return quit;
	}

	void setQuit(bool quit) {
		this->quit = quit;
	}

	void setHumanColor(char color) {
			humanColor = color;
	}

	char getHumanColor() const {
		return humanColor;
	}

	void setCurrentPlayerIndex(int index) {
			currentPlayerIndex = index;
	}

	int getCurrentPlayerIndex() const {
		return currentPlayerIndex;
	}

	Board getBoard() const {
		return B;
	}

	int getHumanCapture() const {
		return B.getHumanCaptures();
	}

	int getComputerCapture() const {
		return B.getComputerCaptures();
	}



	//for serialization scores
	int getTournamentHumanScore() const {
		return tournamentHumanScore;
	}

	int getTournamentComputerScore() const {
		return tournamentComputerScore;
	}

	void setTournamentHumanScore(int score) {
		tournamentHumanScore = score;
	}

	void setTournamentComputerScore(int score) {
		tournamentComputerScore = score;
	}

private:
	Board B;
	Player* playerList[2];

	//scores
	int humanScore = 0;
	int computerScore = 0;	


	//needed while getting tournament score from Serialization
	int tournamentHumanScore = 0;
	int tournamentComputerScore = 0;
	
	int winner = 0;

	char humanColor = ' ';

	//quit the tournament or not
	bool quit = false;


	//white player is always at index 0
	int currentPlayerIndex = 0;
};