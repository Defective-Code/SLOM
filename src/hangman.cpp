#include <stdio.h>
#include <iostream> 
#include <chrono>
#include <sstream>
#include <thread>
#include <algorithm> // for using transform 
#include <cctype> // for using toupper 

#include "hangman.h"
#include "get_data.h"

std::vector<std::string> Hangman::splitStringOnNewline(const std::string& input) {
	std::vector<std::string> lines;
	std::stringstream ss(input);
	std::string line;

	// Use std::getline to extract lines
	while (std::getline(ss, line, '\n')) {
		lines.push_back(line);
	}

	return lines;
}

/*
void Hangman::display(int stage) {
	system("CLS"); // Clear the terminal screen
	std::cout << R"(

	   +===================================================+
	   |   _   _                                           |
	   |  | | | | __ _ _ __   __ _ _ __ ___   __ _ _ __    |
	   |  | |_| |/ _` | '_ \ / _` | '_ ` _ \ / _` | '_ \   |
	   |  |  _  | (_| | | | | (_| | | | | | | (_| | | | |  |
	   |  |_| |_|\__,_|_| |_|\__, |_| |_| |_|\__,_|_| |_|  |
	   |                     |___/                         |
	   +===================================================+

	)" << std::endl;


	//std::cout << answer << std::endl;

	std::vector<std::string> seen_letters_box;
	seen_letters_box.push_back("+---------+");

	std::vector<char> temp;
	for (const char& seen_letter : seen_letters) {
		temp.push_back(seen_letter);

	}

	
	int counter = 0;
	std::string line = "| ";
	for (int i = 0; i < 26; i++)
	{	
		if (seen_letters.count(alphabet[i]) > 0) {
			
			line += (alphabet[i]);
			line += " ";
		}
		else {
			line += "  ";
		}

		counter++;

		if (counter >= 4) {
			line += "|";
			seen_letters_box.push_back(line);
			line = "| ";
			counter = 0;
		}
		

	}

	line += "    |";
	seen_letters_box.push_back(line);
	line = "+---------+";
	seen_letters_box.push_back(line);

	//std::cout << hangman_stages[stage] << std::endl;

	std::vector<std::string> split = splitStringOnNewline(hangman_stages[stage]);


	std::cout << "                                        Used Letters" << std::endl;

	for (int i = 0; i < split.size(); i++)
	{
		std::cout << split[i] << "		" << seen_letters_box[i] << std::endl;
	}

	std::string underscore_word;
	for (int i = 0; i < answer.length(); i++) {
		if (correct_letters.count(answer[i])) {
			underscore_word += answer[i];
		}
		else {
			underscore_word += "_";
		}
	}

	std::cout << "\n          Guess: " + underscore_word + "\n" << std::endl;



	
	std::cout << "\nPress the corresponding key in the bracket to select that option.\n1) Guess a letter\n2) Guess the word\n\nPress q to quit..." << std::endl;
}
*/

std::string Hangman::display(int stage) {
	std::ostringstream oss;

	oss << R"(

       +===================================================+
       |   _   _                                           |
       |  | | | | __ _ _ __   __ _ _ __ ___   __ _ _ __    |
       |  | |_| |/ _` | '_ \ / _` | '_ ` _ \ / _` | '_ \   |
       |  |  _  | (_| | | | | (_| | | | | | | (_| | | | |  |
       |  |_| |_|\__,_|_| |_|\__, |_| |_| |_|\__,_|_| |_|  |
       |                     |___/                         |
       +===================================================+

    )" << std::endl;

	// Building the seen_letters_box
	std::vector<std::string> seen_letters_box;
	seen_letters_box.push_back("+---------+");

	std::vector<char> temp;
	for (const char& seen_letter : seen_letters) {
		temp.push_back(seen_letter);
	}

	int counter = 0;
	std::string line = "| ";
	for (int i = 0; i < 26; i++) {
		if (seen_letters.count(alphabet[i]) > 0) {
			line += (alphabet[i]);
			line += " ";
		}
		else {
			line += "  ";
		}

		counter++;

		if (counter >= 4) {
			line += "|";
			seen_letters_box.push_back(line);
			line = "| ";
			counter = 0;
		}
	}

	line += "    |";
	seen_letters_box.push_back(line);
	line = "+---------+";
	seen_letters_box.push_back(line);

	// Append the hangman stage
	std::vector<std::string> split = splitStringOnNewline(hangman_stages[stage]);

	oss << "                                      Used Letters" << std::endl;

	for (size_t i = 0; i < split.size(); i++) {
		if (i < seen_letters_box.size()) {
			oss << split[i] << "        " << seen_letters_box[i] << std::endl;
		}
	}

	// Building the underscore_word
	std::string underscore_word;
	for (char c : answer) {
		if (correct_letters.count(toupper(c))) {
			underscore_word += c;
		}
		else {
			underscore_word += "_";
		}
	}

	oss << "\n          Guess: " + underscore_word + "\n" << std::endl;

	// Append options for the user
	oss << "\nPress the corresponding key in the bracket to select that option.\n1) Guess a letter\n2) Guess the word\n\nPress q to quit..." << std::endl;

	return oss.str();
}

bool Hangman::guess_word() {
	std::cin >> word_input; // Get user input from the keyboard
	std::transform(word_input.begin(), word_input.end(), word_input.begin(), [](unsigned char c) { return std::tolower(c); });

	return word_input.compare(answer) == 0;
}

bool Hangman::get_letter() {
	
	std::cin >> char_input;
	char_input = tolower(char_input);
	//seen_letters.insert(input);

	int x = std::count(answer.begin(), answer.end(), char_input);

	if (x > 0) {
		correct_letters.insert(toupper(char_input));
		return true;
	}
	else {
		seen_letters.insert(toupper(char_input));
		return false;
	}
}

void Hangman::startGame() {
	int stage = 0;
	bool result;
	seen_letters.clear(); //clear the set between games;
	DataGenerator dg = DataGenerator();
	std::pair<std::string, std::string> answer_pair = dg.get_random_entry();

	answer = answer_pair.first;

	while (stage != MAX_STAGE) {
		//system("CLS"); // Clear the terminal screen
		std::cout << answer << std::endl;

		std::string output = display(stage);
		std::cout << output << std::endl;

		char ch = '0'; //variable to store user input

		std::cin >> ch;

		switch (ch) {
		case '1':
			result = get_letter();
			if (!result) {
				stage++;
			}
			break;
		case '2':
			result = guess_word();
			if (result != true) {
				stage++;
				break;
			}
			else {
				printf("Well done!");
				std::this_thread::sleep_for(std::chrono::seconds(3));
				return;
			}
		case 'q':
			printf("Quitting.....");
			return;
		default:
			printf("Please select a valid option\n");
		}

	}
	
	
	

}



