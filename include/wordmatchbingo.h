#pragma once
#include <string>
#include <map>
#include <vector>

#include "game.h"


class WordMatchBingo : private Game {
	const static int totalAttempts = 5;
	const int bingoWordPoolCount = 10;
	
	std::string wordleWord = "Test";
	std::string displayWordleWord = ""; 
	
	int attemptsCount = 0;
	int wordsFound = 0;
	int bingoCardCount = 4;
	
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
		int startGame() override;
		void getHint();
		
	private:

		std::vector<std::pair<std::string, std::string>> bingoWordPool;
		std::vector<std::pair<std::string, std::string>> bingoCard;

		void selectBingoCard();
		void generateBingoWordPool();
		void receiveUserInput();
		void displayBingoCard();
		void displayCurrentBingoWord();
		bool compareUserInputToBingoCard(const std::string& userInput);
		void updateWordWithStrikethrough(std::string& word);
		
		void giveHint() override;
		void reset() override;
		void setup() override;
		std::string generate() override; 
		void display() override;
		void menu() override;

		friend class WordMatchBingoTest;
};