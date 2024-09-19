#include <string.h>
#include <vector>
#include <string>
#include <unordered_map>
#include <stdio.h>
#include <algorithm>
#include <random>
#include <iostream>
#include "get_data.h"
#include "wordscapes.h"

// Constructor to initialise crossword
Wordscapes::Wordscapes(int size) {
	crossword.resize(size, std::vector<char>(size, '.'));

	wordmap = dg.get_wordmap();

	//selectRandomLetters(10);
	std::string letters = "aehikmnoprtuw";
	letterSubset.assign(letters.begin(), letters.end());
}

// Method to choose random letters with which to select words
void Wordscapes::selectRandomLetters(int numLetters) {
	std::string letters = "AEHIKMNOPRTUW";
	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(letters.begin(), letters.end(), g);

	letterSubset.assign(letters.begin(), letters.begin() + numLetters);
	std::cout << "Letters: ";
	for (char c : letters) {
		std::cout << c << " ";
	}
	std::cout << std::endl;
}

 // Checks if word is valid (i.e. formed from randomly chosen letters)
bool Wordscapes::isValid(const std::string& word) {
	std::unordered_map<char, int> letterCount;
	if (word.length < 3) {
		return false;
	}
	for (char c : letterSubset) {
		letterCount[c]++;
	}

	for (char c : word) {
		if (letterCount[c] == 0) {
			return false;
		}
	}
	for (const auto& pair : letterCount) {
		
		std::cout << word << pair.first << pair.second << std::endl;
	}
	return true;

}

// Function to remove macrons
char Wordscapes::removeMacron(char c) {
	if (c == '\u0101') {  // ā
		return 'a';
	}
	else if (c == '\u0113') {  // ē
		return 'e';
	}
	else if (c == '\u012B') {  // ī
		return 'i';
	}
	else if (c == '\u014D') {  // ō
		return 'o';
	}
	else if (c == '\u016B') {  // ū
		return 'u';
	}
	else {
		return c;
	}
}

// Function to normalize a word (remove diacritics)
std::string Wordscapes::convertWord(const std::string& word) {
	std::string converted;
	for (char c : word) {
		converted += removeMacron(c);  
	}
	return converted;
}

 // Method to place first word in centre
void Wordscapes::placeFirstWord(const std::string& word) {
	int gridSize = crossword.size();
	int len = word.length();
	int centerRow = gridSize / 2;
	int startCol = (gridSize - len) / 2;

	// Place the word horizontally in the center
	for (int i = 0; i < len; ++i) {
		crossword[centerRow][startCol + i] = word[i];
	}

	std::cout << "Placed first word horizontally at center: " << word << std::endl;
}

bool Wordscapes::canIntersect(const std::string& word, bool& isHorizontal, int& row, int& col) {
	int gridSize = crossword.size();
	int len = word.length();
	bool foundIntersection = false;

	// Check for horizontal placement
	for (int r = 0; r < gridSize; ++r) {
		for (int c = 0; c <= gridSize - len; ++c) {
			bool canPlace = true;
			bool hasIntersection = false;

			// Check if the word can be placed horizontally
			for (int i = 0; i < len; ++i) {
				if (crossword[r][c + i] != '.' && crossword[r][c + i] != word[i]) {
					canPlace = false;
					break;
				}
				if (crossword[r][c + i] == word[i]) {
					hasIntersection = true;
				}
			}

			if (canPlace && hasIntersection) {
				row = r;
				col = c;
				isHorizontal = true;
				foundIntersection = true;
				break;
			}
		}
		if (foundIntersection) break;
	}

	// Check for vertical placement if not found horizontally
	if (!foundIntersection) {
		for (int c = 0; c < gridSize; ++c) {
			for (int r = 0; r <= gridSize - len; ++r) {
				bool canPlace = true;
				bool hasIntersection = false;

				// Check if the word can be placed vertically
				for (int i = 0; i < len; ++i) {
					if (crossword[r + i][c] != '.' && crossword[r + i][c] != word[i]) {
						canPlace = false;
						break;
					}
					if (crossword[r + i][c] == word[i]) {
						hasIntersection = true;
					}
				}

				if (canPlace && hasIntersection) {
					row = r;
					col = c;
					isHorizontal = false;
					foundIntersection = true;
					break;
				}
			}
			if (foundIntersection) break;
		}
	}

	return foundIntersection;
}



bool Wordscapes::placeWordWithIntersection(const std::string& word) {
	bool isHorizontal;
	int row, col;

	if (canIntersect(word, isHorizontal, row, col)) {
		if (isHorizontal) {
			for (int i = 0; i < word.length(); ++i) {
				crossword[row][col + i] = word[i];
			}
		}
		else {
			for (int i = 0; i < word.length(); ++i) {
				crossword[row + i][col] = word[i];
			}
		}
		return true;
	}

	return false;
}


 // method to place word horizontally
bool Wordscapes::placeWordHorizontally(const std::string& word) {
	int gridSize = crossword.size();
	int len = word.length();

	for (int row = 0; row < gridSize; ++row) {
		for (int col = 0; col <= gridSize - len; ++col) {
			bool canPlace = true;
			for (int i = 0; i < len; ++i) {
				if (crossword[row][col + i] != '.' && crossword[row][col + i] != word[i]) {
					canPlace = false;
					break;
				}
			}

			if (canPlace) {
				for (int i = 0; i < len; ++i) {
					crossword[row][col + i] = word[i];
				}
				return true;
			}
		}
	}

	return false;
}


 // Method to place word vertically
bool Wordscapes::placeWordVertically(const std::string& word) {
	int gridSize = crossword.size();
	int len = word.length();

	for (int col = 0; col < gridSize; ++col) {
		for (int row = 0; row <= gridSize - len; ++row) {
			bool canPlace = true;
			for (int i = 0; i < len; ++i) {
				if (crossword[row + i][col] != '.' && crossword[row + i][col] != word[i]) {
					canPlace = false;
					break;
				}
			}

			if (canPlace) {
				for (int i = 0; i < len; ++i) {
					crossword[row + i][col] = word[i];
				}
				return true;
			}
		}
	}

	return false;
}



 // Generates crossword by adding valid words
void Wordscapes::makeCrossword() {
	bool firstWordPlaced = false;

	for (const auto& entry : wordmap) {
		const std::string& word = entry.first;

		if (!firstWordPlaced) {
			placeFirstWord(word);
			firstWordPlaced = true;
		}
		else {
			if (placeWordWithIntersection(word)) {
				std::cout << "Placed word with intersection: " << word << std::endl;
			}
		}
	}
}

// Displays crossword 
void Wordscapes::displayCrossword() {
	for (const auto& row : crossword) {
		for (char c : row) {
			std::cout << c << " ";
		}
		std::cout << std::endl;
	}
}

 // Runs game loop
void Wordscapes::runGame() {

	std::transform(letterSubset.begin(), letterSubset.end(), letterSubset.begin(), [](unsigned char c) {
		return std::tolower(c);
	});	
	makeCrossword();
	displayCrossword();

	while (true) {
		char ch = getchar();
		if (ch == 'q') {
			break;
		}
	}

}
