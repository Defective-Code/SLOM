#include <stdio.h>
#include <iostream> 
#include <chrono>
#include <sstream>
#include <thread>
#include <algorithm> // for using transform 
#include <cctype> // for using toupper 

#include "hangman.h"
#include "get_data.h"
#include "io_handler.h"



std::string Hangman::generate() {
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
	std::vector<std::string> split = splitStringOnNewline(hangman_stages[current_stage]);

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

void Hangman::display() {
	clearScreen();
	std::string output = generate();
	std::cout << output << std::endl;
}



void Hangman::setup() {
	DataGenerator dg = DataGenerator();
	std::pair<std::string, std::string> answer_pair = dg.get_random_entry();

	answer = answer_pair.first;
}

void Hangman::menu() {
	char ch = getSingleCharacter();
	bool result; //variable to store the result of a guess
	switch (ch) {
	case '1': {
		char c_input = getSingleCharacter();
		result = guessLetter(c_input);
		if (!result) {
			current_stage++;
		}
		break;
	}
	case '2':
	{
		std::string w_input = getWord();
		result = guessWord(w_input);
		if (result != true) {
			current_stage++;
			break;
		}
		else {
			printf("Well done!");
			std::this_thread::sleep_for(std::chrono::seconds(3));
			return;
		}
	}
	case 'q':
	{
		printf("Quitting.....");
		return;
	}
	default:
	{
		printf("Please select a valid option\n");
	}
	}
}

//function to handle getting a word in lowercase
bool Hangman::guessWord(std::string input) {

	return input.compare(answer) == 0;
}

bool Hangman::guessLetter(char input) {

	
	//seen_letters.insert(input);

	int x = std::count(answer.begin(), answer.end(), input);

	//if x > 0, then it exists in the word and is a correct letter, else it is an incorrect letter
	if (x > 0) {
		correct_letters.insert(input);
		return true;
	}
	else {
		seen_letters.insert(input);
		return false;
	}
}

void Hangman::giveHint() {

}

int Hangman::startGame() {
	
	//seen_letters.clear(); //clear the set between games
	setup();

	//loop until the stage is the max stage and the hangman is done
	while (current_stage != MAX_STAGE) {
		//system("CLS"); // Clear the terminal screen
		
		std::cout << answer << std::endl; //here for testing purposes

		display();
		menu();
		

	}
	
}

void Hangman::reset() {
	correct_letters.clear();
	current_stage = 0;
	seen_letters.clear();
}



