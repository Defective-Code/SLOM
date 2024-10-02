#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>  // For std::remove
#include <unordered_map>
#include <locale>
#include <codecvt>

#include "io_handler.h"


void clearScreen() {
	std::cout << "\033[2J" << std::endl; //clear the terminal screen
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

char getSingleCharacter() {
	char input;
	std::cin >> input;  // This skips leading whitespace
	//input = tolower(input);
	return input;
}

std::string getWord() {
	std::string input;
	std::cin >> input;  // Reads input until the first space or newline
	input = removeWhitespace(input);
	//std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c) { return std::tolower(c); });
	return input;
}

// Function to clear last N lines in terminal
void clearLastNLines(int n) {
	for (int i = 0; i < n; ++i) {
		// Move cursor up one line and clear the line
		std::cout << "\033[A\033[2K";
	}
}

// Function to remove all whitespaces from a string
std::string removeWhitespace(const std::string& input) {
	std::string output;
	std::copy_if(input.begin(), input.end(), std::back_inserter(output), [](unsigned char c) {
		// Only apply std::isspace to ASCII characters (single-byte characters < 128)
		return !(c < 128 && std::isspace(c));
		});
	return output;
}



// Helper function to convert a string to lowercase
std::string toLowerCase(const std::string& str) {
    std::string lowerStr;
    for (char ch : str) {
        lowerStr += std::tolower(static_cast<unsigned char>(ch));  // Ensure correct conversion for all characters
    }
    return lowerStr;
}


