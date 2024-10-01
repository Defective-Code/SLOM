#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>  // For std::remove
#include <unordered_map>
#include <codecvt>

#include "io_handler.h"

void clearScreen() {
	std::cout << "\033[2" << std::endl; //clear the terminal screen
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
	input = tolower(input);
	return input;
}

std::string getWord() {
	std::string input;
	std::cin >> input;  // Reads input until the first space or newline
	input = removeWhitespace(input);
	std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c) { return std::tolower(c); });
	return input;
}

// Function to clear last N lines in terminal
void clearLastNLines(int n) {
	for (int i = 0; i < n; ++i) {
		// Move cursor up one line and clear the line
		std::cout << "\033[A\033[2K";
	}
}

// Function to convert a string with macrons to a normal string
std::wstring convertMacronsToNormal(const std::wstring& input) {
	std::wstring output;
	for (wchar_t ch : input) {
		// Check if the character is in the macron map and replace it
		if (macron_map.find(ch) != macron_map.end()) {
			output += macron_map[ch];
		}
		else {
			output += ch;  // Keep the character if it's not macronized
		}
	}
	return output;
}

// Function to remove invisible characters (like extra bytes, combining marks)
std::wstring removeInvisibleCharacters(const std::wstring& input) {
	std::wstring output;
	for (wchar_t ch : input) {
		if (ch >= 32) {  // Remove control characters and invisible characters (below 32 in Unicode)
			output += ch;
		}
	}
	return output;
}

// Function to remove all whitespaces from a string
std::string removeWhitespace(const std::string& input) {
	std::string output;
	// Copy all non-whitespace characters to the output string
	std::copy_if(input.begin(), input.end(), std::back_inserter(output), [](char c) {
		return !std::isspace(c);  // Check if the character is not a whitespace
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


std::string wstringToString(const std::wstring& wstr) {
	// Use wstring_convert to convert wstring (wide string) to string (narrow string)
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.to_bytes(wstr);
}

std::wstring stringToWstring(const std::string& str) {
	// Use wstring_convert to convert string (narrow string) to wstring (wide string)
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(str);
}