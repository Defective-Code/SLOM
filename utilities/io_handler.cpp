#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>  // For std::remove

#include "io_handler.h"

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

char getSingleCharacter() {
	char input;
	std::cout << "Enter a character: ";
	std::cin >> input;  // This skips leading whitespace
	return input;
}

std::string getWord() {
	std::string input;
	std::cout << "Enter a word: ";
	std::cin >> input;  // Reads input until the first space or newline

	// Remove any whitespace characters (just in case the word includes spaces/newlines)
	input.erase(std::remove_if(input.begin(), input.end(), ::isspace), input.end());

	return input;
}