#pragma once
#include <string>
#include <map>
#include <vector>


class WordMatchBingo {
	std::string wordleWord = "Test";
	std::string displayWordleWord = ""; 
	const static int totalAttempts = 5;
	int attemptsCount = 0;
	int wordsFound = 0;
	int bingoCardCount = 4;
	int bingoWordPoolCount = 10;
	bool wordleComplete = false;
	std::string attempts[totalAttempts];
	std::map<char, int> charCount;

	std::vector<std::pair<std::string, std::string>> bingoWordPool;
    std::vector<std::pair<std::string, std::string>> bingoCard;
    std::pair<std::string, std::string> currentBingoWord = {"", ""};
    std::string userGuess = "";

	// public:


	// 	void  WordMatchBingo::selectBingoWordPool();

	// 	void WordMatchBingo::selectBingoCard();

	// 	void startGame();

	// 	void clearLastNLines(int n);

	// 	friend class WordleTest;
	public:
		void selectBingoCard();
		void startGame();
		void selectBingoWordPool();
		void receiveUserInput();
		void displayBingoCard();
		void displayCurrentBingoWord();
		bool compareUserInputToBingoCard(const std::string& userInput);
		void updateWordWithStrikethrough(std::string& word);
		void clearLastNLines(int n);
	 	bool isDiacritic(char32_t c);
	 	bool hasDiacritics(const std::string &input);
		void reset();
		void getHint();

		friend class WordMatchBingoTest;
};