#pragma once
#include <string>
#include <map>

class WordMatchBingo {
	std::string wordleWord = "Test";
	std::string displayWordleWord = "";
	const static int totalAttempts = 5;
	int attemptsCount = 0;
	bool wordleComplete = false;
	std::string attempts[totalAttempts];
	std::map<char, int> charCount;
public:
    bool  WordMatchBingo::isDiacritic(char32_t c);
	
    bool  WordMatchBingo::hasDiacritics(const std::string &input);

    void  WordMatchBingo::selectBingoWordPool();

    void WordMatchBingo::selectBingoCard();

    void startGame(){}

    friend class WordleTest;
};