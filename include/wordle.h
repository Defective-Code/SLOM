#pragma once
#pragma execution_character_set( "utf-8" )
#include <string>
#include <map>
#include "game.h"

class Wordle : private Game{
	const static int MAX_ATTEMPTS = 5;
	const int WORD_LENGTH = 5;

	std::string wordleWord = "Test";
	std::string displayWordleWord = "";
	
	std::string attempts[MAX_ATTEMPTS];
	std::map<char, int> charCount;
public:
		/**
		 * Method used to start the game. This is called when the user selects Wordle as their game of choice.
		 * 
		 */
	int startGame() override;

private:
	int attemptsCount = 0;

	bool wordleComplete = false;

	std::string wordToGuess;

	std::string wordDef;

	void giveHint() override;

		/**
		 * Method used to receive user input (their Wordle guess).
		 * 
		 * @return string containing the user's input.
		 */
	std::string receiveUserInput();

		/**
		 * Method used to get the next Wordle game state (display state of the current game) based on userGuess compared to the Wordle word.
		 * 
		 * @param string containing the user's guess.
		 */
	void getNextGameState(const std::string userGuess);

	void setup() override;

	/**
     * Method to reset the game state to its initial configuration.
     */
    void reset() override;

	bool menu() override;

	std::string generate() override;

	void display() override;

	friend class WordleTest;
};