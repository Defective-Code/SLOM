#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>  // For std::remove
#include <unordered_map>
#include <locale>
#include <codecvt>

#include "io_handler.h"

extern std::unordered_map<wchar_t, wchar_t> macron_map = {
    {L'ā', L'a'}, {L'ē', L'e'}, {L'ī', L'i'},
    {L'ō', L'o'}, {L'ū', L'u'}, {L'Ā', L'A'},
    {L'Ē', L'E'}, {L'Ī', L'I'}, {L'Ō', L'O'},
    {L'Ū', L'U'}
};

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
	std::copy_if(input.begin(), input.end(), std::back_inserter(output), [](unsigned char c) {
		// Only apply std::isspace to ASCII characters (single-byte characters < 128)
		return !(c < 128 && std::isspace(c));
		});
	return output;
}

std::size_t utf8Length(const std::string& input) {
	std::size_t length = 0;
	for (std::size_t i = 0; i < input.size(); ++i) {
		// Check if the byte is a starting byte of a UTF-8 character
		unsigned char c = input[i];
		if ((c & 0xC0) != 0x80) {
			// It's not a continuation byte (0x80 to 0xBF), so it's the start of a new character
			++length;
		}
	}
	return length;
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

