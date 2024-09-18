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


std::vector<std::vector<char>>crossword;
std::vector<char> letterSubset;
DataGenerator dg;

// Constructor to initialise crossword
Wordscapes::Wordscapes(int size) {
	crossword.resize(size, std::vector<char>(size, '.'));

	wordmap = dg.get_wordmap();

	selectRandomLetters(4);
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

 // Checks if word is valud (i.e. formed from randomly chosen letters)
bool Wordscapes::isValid(const std::string& word) {
	std::unordered_map<char, int> letterCount;
	for (char c : letterSubset) {
		letterCount[c]++;
	}

	for (char c : word) {
		if (letterCount[c] == 0) {
			return false;
		}
		letterCount[c]--;
	}
	return true;

}

// Tries to place word in crossword grid
bool Wordscapes::placeWord(const std::string& word) {
	int gridSize = crossword.size();
	int len = word.length();

	for (int row = 0; row < gridSize; ++row) {
		if (len <= gridSize) {
			bool place = true;
			for (int i = 0; i < len; ++i) {
				if (crossword[row][i] != '.') {
					place = false;
					break;
				}
			}

			if (place) {
				for (int i = 0; i < len; ++i) {
					crossword[row][i] = word[i];
				}
				return true;
			}
		}
	}
	return false;
}

 // Generates crossword by adding valid words
void Wordscapes::makeCrossword() {
	for (const auto& entry : wordmap){
		const std::string& word = entry.first;
		if (isValid(word)) {
			if (placeWord(word)) {
				std::cout << "Placed word: " << word << std::endl;
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
	makeCrossword();
	displayCrossword();
}
