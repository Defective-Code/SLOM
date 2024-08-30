#pragma once
#include <string>
#include <map>

class Wordle {
	std::string wordleWord = "Test";
	std::string displayWordleWord = "";
	const static int totalAttempts = 5;
	int attemptsCount = 0;
	bool wordleComplete = false;
	std::string attempts[totalAttempts];
	std::map<char, int> charCount;
public:

	/**
		 * Method to check if character is a diacritic
		 * 
		 * @param char32_t the char to be checked
		 * @return bool whether the character has diacritics
		*/
	bool isDiacritic(char32_t c);

		/**
		 * Method to check if string contains diacritics
		 * 
		 * @param string input word
		 * return bool whether the string contains diacritics
		*/
	bool hasDiacritics(const std::string& input);

		/**
		 * Method used to initialise the game.
		 */
	void initialiseGame();

		/**
		 * Method used to select a random Maori word to be used as the Wordle word.
		 * 
		 * @return string containing the selected Maori word.
		 */
	std::string selectWordleWord();

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

		/**
		 * Method used to display the current game state.
		 * 
		 */
	void displayGameState();

		/**
		 * Method used to start the game. This is called when the user selects Wordle as their game of choice.
		 * 
		 */
	void startGame();

	/**
     * Method to reset the game state to its initial configuration.
     */
    void resetGameState();

	friend class WordleTest;
};