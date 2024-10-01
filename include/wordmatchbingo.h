#pragma once
#include <string>
#include <map>
#include <vector>


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
		void startGame();
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
		
		void reset();
		void setup();
		std::string generate();
		void menu();

		friend class WordMatchBingoTest;
};