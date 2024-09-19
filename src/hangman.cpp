#include <stdio.h>
#include <iostream> 
#include <chrono>
#include <sstream>
#include <thread>

#include "hangman.h"
#include "get_data.h"


void Hangman::display(int stage) {
	// system("CLS"); // Clear the terminal screen
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

	vector<string> seen_letters_box;
	seen_letters_box.push_back("+---------+");

	vector<string> letters;
	for (const char& seen_letter : seen_letters) {

	}

	vector<char> temp;
	for (const char& seen_letter : seen_letters) {
		temp.push_back(seen_letter);
	}

	while (temp.size() < 26) {
		
	}

	//std::cout << hangman_stages[stage] << std::endl;
	std::vector<std::string> split = splitStringOnNewline(hangman_stages[stage]);
	for each (string line in split)
	{
		cout << 
	}
}

void Hangman::startGame() {
	int stage = 0;
	
	DataGenerator dg = DataGenerator();
	std::pair<std::string, std::string> answer = dg.get_random_entry();

	std::cout << answer.first << std::endl;

	while (stage != MAX_STAGE) {
		display(stage);

		std::string input;
		std::cin >> input; // Get user input from the keyboard

		for each (char letter in input) //save the used the letters in the set
		{
			seen_letters.insert(letter);
		}

		if (input.compare(answer.first) != 0) {
			stage++;
		}
		else {
			printf("Well done!");
			break;
		}
	}
	
	std::this_thread::sleep_for(std::chrono::seconds(3));
	

}

std::vector<std::string> splitStringOnNewline(const std::string& input) {
	std::vector<std::string> lines;
	std::stringstream ss(input);
	std::string line;

	// Use std::getline to extract lines
	while (std::getline(ss, line, '\n')) {
		lines.push_back(line);
	}

	return lines;
}
};