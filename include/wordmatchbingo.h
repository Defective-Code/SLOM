#pragma once
#include <string>
#include <map>
#include <vector>

#include "game.h"


class WordMatchBingo {
	const static int totalAttempts = 5;
	const int bingoWordPoolCount = 10;
	int totalTime = 30; // 60 seconds for guessing
	int remainingTime = totalTime;
	
	std::string wordleWord = "Test";
	std::string displayWordleWord = ""; 
	
	int attemptsCount = 0;
	int wordsFound = 0;
	int bingoCardCount = 10;
	
	bool wordleComplete = false;
	std::string attempts[totalAttempts];
	std::map<char, int> charCount;

	
    
    std::pair<std::string, std::string> currentBingoWord = {"", ""};
    std::string userGuess = "";

	// public:


	// 	void  WordMatchBingo::selectBingoWordPool();

	// 	void WordMatchBingo::selectBingoCard();

	// 	void startGame();

	// 	void clearLastNLines(int n);

	// 	friend class WordleTest;
	public:
		int startGame();
		void getHint();
		
	private:

		std::vector<std::pair<std::string, std::string>> bingoCard;
		std::vector<std::pair<std::string, std::string>> bingoCardPool;

		void selectBingoCard();
		void receiveUserInput();
		void displayBingoCard();
		void displayCurrentBingoWord();
		bool compareUserInputToBingoCard(const std::string& userInput);
		void updateWordWithStrikethrough(std::string& word);
		size_t getDisplayLength(const std::string& word);
		
		void reset();
		void setup();

		friend class WordMatchBingoTest;
};