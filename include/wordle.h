#pragma once
#include <string>
#include <map>
#include "game.h"

class Wordle : private Game{
	const static int MAX_ATTEMPTS = 5;

	std::string wordleWord = "Test";
	std::string displayWordleWord = "";
	
	std::string attempts[MAX_ATTEMPTS];
	std::map<char, int> charCount;
public:
		/**
		 * Method used to start the game. This is called when the user selects Wordle as their game of choice.
		 * 
		 */
	int startGame();


private:
	int attemptsCount = 0;
	bool wordleComplete = false;
	std::string wordToGuess;

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

	void setup();

	/**
     * Method to reset the game state to its initial configuration.
     */
    void reset();

	void menu();

	std::string generate();

	void display();

	friend class WordleTest;
};