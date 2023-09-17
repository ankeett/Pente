#include "Serialization.h"

Serialization::Serialization(Board & B) : board(B){}


Serialization::~Serialization()
{
	
}

void Serialization::readBoard(Board& B) {

	cout<<"Enter the name of the file you want to read from: ";
	string fileName;

	cin >> fileName;

	ifstream file(fileName);

	if (file.is_open()) {
		cout << "File opened successfully" << endl;
	}
	else {
		cout << "File could not be opened" << endl;
		return;
	}

	string line;
	std::pair<std::string, std::string> playerPair;

	while (getline(file, line)) {
		cout << line << endl;
		playerPair = findColor(line);
	}

	cout<<playerPair.first<<endl;
	cout<<playerPair.second<<endl;
	//find human and computer stone
	setNextPlayer(playerPair.first);
	cout<<getNextPlayer()<<endl;
	if (playerPair.first == "Human") {
		if (playerPair.second == "White") {

			//set the human stone to white
			setHumanColor('W');
			setComputerColor('B');

		}
		else {
			//set the human stone to black
			setHumanColor('B');
			setComputerColor('W');
		}
	}
	else {
		if (playerPair.second == "White") {
		cout<<"I'm here"<<endl;
			//set the computer stone to white
			setComputerColor('W');
			setHumanColor('B');
		}
		else {
			//set the computer stone to black
			setComputerColor('B');
			setHumanColor('W');
		}
	}
	file.close();
	file.clear(); // Reset the file stream's state
	file.seekg(0); // Seek to the beginning of the file	bool isBoardSection = false;
	ifstream file1(fileName);

	cout<<getHumanColor()<<endl;
	int row = 1;
	bool isBoardSection = false;
	//write from the file into the board
	while (getline(file1, line)) {
		// Check if we have entered the board section
		if (line.find("Board:") != std::string::npos) {
			isBoardSection = true;
			continue; // Skip the "Board:" line
		}

		// Check if we are still in the board section
		if (isBoardSection) {
			// Process the board state line
			for (int col = 0; col <19; col++) {
				char symbol = line[col];

				// Convert the character symbol to an integer (1 or 2)
				//human is always 1, computer is always 2
				int intValue;

				if (symbol == 'W') {
					if (getHumanColor() == 'W') {

						intValue = 1;
					}
					else {

						intValue = 2;
					}

				}
				else if (symbol == 'B') {
					if (getHumanColor() == 'B') {

						intValue = 1;
					}
					else {

						intValue = 2;
					}
				}
				else {

					intValue = 0;
				}

				// Update the board using your setBoard function
				B.setBoard(row, col, intValue);
			}
			row++; // Increment the row counter
			if (row >= 19) {
				break; // Stop reading the file if we have reached the end of the board
			}
		}

	}


	// Read capturing and scoring information
bool readingPlayerInfo = false;
int humanCaptures = 0, humanScore = 0, computerCaptures = 0, computerScore = 0;

while (getline(file1, line)) {
    if (line.find("Human:") != std::string::npos) {
        // Start reading player information

        readingPlayerInfo = true;
    } else if (line.find("Computer:") != std::string::npos) {
        // Stop reading player information
        readingPlayerInfo = false;
    } else if (readingPlayerInfo) {
        size_t posCaptures = line.find("Captured pairs:");
        size_t posScore = line.find("Score:");

        if (posCaptures != std::string::npos) {
            // Read human's captured pairs
            humanCaptures = std::stoi(line.substr(posCaptures + 15)); // 15 is the length of "Captured pairs:"
        } else if (posScore != std::string::npos) {
            // Read human's score
            humanScore = std::stoi(line.substr(posScore + 6)); // 6 is the length of "Score:"
        }
    } else if (!readingPlayerInfo) {
        size_t posCaptures = line.find("Captured pairs:");
        size_t posScore = line.find("Score:");

        if (posCaptures != std::string::npos) {
            // Read computer's captured pairs
            computerCaptures = std::stoi(line.substr(posCaptures + 15)); // 15 is the length of "Captured pairs:"
        } else if (posScore != std::string::npos) {
            // Read computer's score
            computerScore = std::stoi(line.substr(posScore + 6)); // 6 is the length of "Score:"
        }
    }
	else {
			cout<<"I'm here"<<endl;
	}
}


	// Set captured pairs and scores in the Serialization object
	setHumanCaptures(humanCaptures);
	setComputerCaptures(computerCaptures);
	setHumanScore(humanScore);
	setComputerScore(computerScore);

	B.printBoard(getHumanColor());

	file1.close();

}



pair<string, string> Serialization::findColor(const string line) {
	size_t pos = line.find("Next Player:");

	pair<string, string> playerPair;

	if (pos != std::string::npos) {
		// Find the substring after "Next Player:" and split it into two parts
		std::string remaining = line.substr(pos + 12); // 12 is the length of "Next Player:"
		size_t hyphenPos = remaining.find('-');

		if (hyphenPos != std::string::npos) {
			std::string player1 = remaining.substr(0, hyphenPos);
			std::string player2 = remaining.substr(hyphenPos + 1);

			//trim whitespace from player names if needed
			 player1 = trim(player1);
			 player2 = trim(player2);

			// Update the playerPair with the extracted player names
			playerPair.first = player1;
			playerPair.second = player2;
		}
	}
	return playerPair;
}

string Serialization::trim(const string& str) {
	size_t first = str.find_first_not_of(' ');
	if (std::string::npos == first) {
		return str;
	}
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));
}

void Serialization::writeIntoFile(Board& B) {

	//get the name of the file
	cout<<"Enter the name of the file you want to write to: ";
	string fileName;

	cin >> fileName;

	ofstream file(fileName);

	if (file.is_open()) {
		cout << "File opened successfully" << endl;
	}
	else {
		cout << "File could not be opened" << endl;
		return;
	}

	//write the board into the file

	// Write the board state
	file << "Board:" << endl;

	for (int row = 1; row <= 19; row++) {
		for (int col = 0; col < 19; col++) {
			int value = B.getBoard(row, col);

			if (value == 1) {
				if (getHumanColor() == 'W') {
					file << 'W';
				}
				else {
					file << 'B';
				}
			}
			else if (value == 2) {
				if (getHumanColor() == 'B') {
					file << 'W';
				}
				else {
					file << 'B';
				}
			}
			else {
				file << '.';
			}
		}

		file << endl;
	}	


}
