#include "Serialization.h"

Serialization::Serialization(Board & B) : board(B){}


Serialization::~Serialization()
{
	
}


/* *********************************************************************
Function Name: Serialization::readBoard
Purpose: Read and deserialize game board and player information from a file.
Parameters:
   - 'Board B': A reference to the Board object where the board state will be stored.
Return Value: None
Algorithm:
1. Prompt the user to enter the name of the file to read from.
2. Attempt to open the specified file.
3. If the file is successfully opened, proceed with reading its contents; otherwise, print an error message.
4. Create a pair of strings called 'playerPair' to store player color information.
5. Read each line from the file:
   a. Output the line to the console (for debugging).
   b. Call 'findColor' function to extract and split player color information.
6. Close the file after reading player color information.
7. Reopen the same file for reading board data.
8. Initialize 'row' and 'isBoard' for tracking board state.
9. Iterate through each line in the file:
   a. Check if the line contains "Board:". If it does, set 'isBoard' to 'true'.
   b. If 'isBoard' is 'true', ensure the board row is valid.
   c. Iterate through each character in the line to process the board state:
	  i. Extract the character symbol.
	  ii. Convert the character symbol to an integer based on player colors.
	  iii. Update the board using 'B.setBoard' with the row, column, and integer value.
	  iv. Increment the row counter.
	  v. Break if 'row' exceeds 19.
10. Read capturing and scoring information from the second part of the file.
11. Parse and store human's and computer's captured pairs and scores.
12. Print the board using 'B.printBoard' with the human's color.
13. Close the file.
Assistance Received: None
********************************************************************* */
void Serialization::readBoard(Board& B) {

	string fileName;
	ifstream file; 

	while (true) {
		cout << "Enter the name of the file you want to read from: ";
		cin >> fileName;

		// Attempt to open the file
		file.open(fileName); 

		if (file.is_open()) {
			cout << "File opened successfully" << endl;
			// Exit the loop if the file is successfully opened
			break; 
		}
		else {
			cout << "File could not be opened" << endl;
			file.clear();
		}
	}


	string line;
	std::pair<std::string, std::string> playerPair;

	while (getline(file, line)) {
		cout << line << endl;
		findColor(line);
	}

	file.close();

	ifstream file1(fileName);

	int row = 1;
	bool isBoard = false;
	//write from the file into the board
	while (getline(file1, line)) {
		// Check if we have entered the board section
		if (line.find("Board:") != std::string::npos) {
			isBoard = true;
			continue; // Skip the "Board:" line
		}

		// Check if we are still in the board section
		if (isBoard) {

			//make sure the board is valid
			if (row < 19) {
				if (line.length() != 19) {
					cout<<"Invalid board state"<<endl;
					exit(1);
				}
			}

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
			// Increment the row counter
			row++; 
			if (row >= 20) {
				break; 
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


/*********************************************************************
Function Name: Serialization::findColor
Purpose: Extract and parse player color information from a string.
Parameters:
   - 'line' (input string): A string containing player color information.
Return Value: None (void).
Algorithm:
1. Search for the position of the substring "Next Player:" in the input 'line'.
2. If found, extract and split the substring after "Next Player:" into two parts.
3. If two valid player names are extracted, update the player colors in the serialization object:
   a. Set the next player based on 'playerPair.first'.
   b. Determine and set human and computer stone colors based on the extracted values.
   c. Handle cases where 'playerPair.first' and 'playerPair.second' are valid.
Assistance Received: None
*********************************************************************/
void Serialization::findColor(const string line) {
	size_t pos = line.find("Next Player:");

	pair<string, string> playerPair = {"1","1"};

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
	
	// Set the next player and player colors
	if (playerPair.first != "1" && playerPair.second != "1") {

		setNextPlayer(playerPair.first);
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
	}
}

/*********************************************************************
Function Name: Serialization::trim
Purpose: Remove leading and trailing whitespace from a string.
Parameters:
   - 'str' (string, passed by referenced): The string to be trimmed.
Return Value: A new string with leading and trailing whitespace removed.
Algorithm:
1. Find the index of the first non-space character in the input 'str' and store it in 'first'.
2. If no non-space characters are found, return the original 'str'.
3. Find the index of the last non-space character in the input 'str' and store it in 'last'.
4. Extract and return a substring from 'str' starting at 'first' and ending at 'last' (inclusive).
Assistance Received: Internet
*********************************************************************/
string Serialization::trim(const string& str) {
	size_t first = str.find_first_not_of(' ');
	if (std::string::npos == first) {
		return str;
	}
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));
}


/*********************************************************************
Function Name: Serialization::writeIntoFile
Purpose: Write the current game state to a file, including the board state and player information.
Parameters:
   - 'B' (Board object by reference): The current game board state.
Return Value: None.
Algorithm:
1. Prompt the user to enter the name of the file they want to write to.
2. Attempt to open the file for writing.
3. If the file is successfully opened, proceed; otherwise, display an error message and retry.
4. Write the board state to the file, including stone positions and their corresponding players.
5. Write human player information to the file, including the number of captured pairs and the score.
6. Write computer player information to the file, including the number of captured pairs and the score.
7. Write information about the next player to make a move.
Assistance Received: None
*********************************************************************/
void Serialization::writeIntoFile(Board& B) {

	string fileName;
	ofstream file;

	while (true) {
		cout << "Enter the name of the file you want to write to: ";
		cin >> fileName;

		// Attempt to open the file
		file.open(fileName);

		if (file.is_open()) {
			cout << "File opened successfully" << endl;
			// Exit the loop if the file is successfully opened
			break;
		}
		else {
			cout << "File could not be opened" << endl;
			file.clear();
		}
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
				file << 'O';
			}
		}

		file << endl;
	}

	file <<"Human: "<<endl;
	file <<"Captured pairs: "<<getHumanCaptures()<<endl;
	file <<"Score: "<<getHumanScore()<<endl;
	file << endl;

	file <<"Computer: "<<endl;
	file <<"Captured pairs: "<<getComputerCaptures()<<endl;
	file <<"Score: "<<getComputerScore()<<endl;

	file << endl;
	string color;

	if (getNextPlayer() == "Human") {
		color = (getHumanColor() == 'W') ? "White" : "Black";
	}
	else {
		color = (getHumanColor() == 'W') ? "Black" : "White";
	}

	file <<"Next Player: "<<getNextPlayer()<<" - "<< color <<endl;
}
