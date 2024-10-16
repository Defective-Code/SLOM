/**
* Class to encapsulate Wordfind game functionality.
* Contains methods to display the game, handle input, and generate the set of words to use.
*/
#pragma once

#include <string.h>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <utility>  // For std::pair

#include "game.h" //extend the this abstract class

class Wordfind : private Game {

	//Here just defining some more useful names to certain data structures.

	const static int GRID_SIZE = 10; // Adjust as needed

	const static int WORD_COUNT = 4;

	const static int COIN_AMOUNT = 8;

	// A type alias for storing the coordinates of placed words
	using Position = std::pair<int, int>;
	
	struct PositionHash {
		std::size_t operator()(const Position& pos) const {
			std::size_t h1 = std::hash<int>()(pos.first);
			std::size_t h2 = std::hash<int>()(pos.second);
			return h1 ^ (h2 << 1); // Combine the two hash values
		}
	};

	using PositionSet = std::unordered_set<Position, PositionHash>; //use whenever you want to declare a set of unordered Positions

	public:
		/***
		* @brief Method that starts the game, 
		*
		* @param words The real words to be placed in the wordfind
		*/
		int startGame() override;

	private:

		/**
		 * @brief A vector of words to be found in the game.
		 */
		std::vector<std::string> words;

		/**
		 * @brief An unordered map of word and definition pairs, where the key is the word 
		 * and the value is its definition.
		 */
		std::unordered_map<std::string, std::string> wordDefs;

		/**
		 * @brief A vector of words that have already been found by the player.
		 */
		std::vector<std::string> wordsFound;

		/**
		 * @brief A vector of indices representing the words for which hints have been given.
		 */
		std::vector<int> hintsGiven;

		/**
		 * @brief A set of coordinates representing the positions of the first letters of the hinted words.
		 */
		PositionSet hintCoords;

		/**
		 * @brief A vector representing the positions of each corresponding word in the grid. 
		 * Each position stores the x and y coordinates of the first letter of the word.
		 */
		std::vector<Position> wordPositions;

		/**
		 * @brief A set of positions that have been found by the player.
		 */
		PositionSet wordsFoundCoordinates;

		/**
		 * @brief An unordered map that associates each word with a set of positions 
		 * on the grid, representing where the word is located.
		 */
		std::unordered_map<std::string, PositionSet> wordToPositionMap;

		/**
		 * @brief A 2D vector representing the grid of letters in the game.
		 */
		std::vector<std::vector<char>> grid;


		/**
		 * @brief method to give hint to user 
		*/
		void giveHint() override;

		/**
		 * @brief method to get random words from data generator
		 * 
		 * @return string representation of random word 
		*/
		std::vector<std::string> getRandomWords();

		/**
		 * @brief Initializes the grid with random letters from A to Z.
		 * @brief Each cell in the grid is filled with a random uppercase letter.
		 *
		 * @param grid A reference to a 2D vector of characters representing the grid to be initialized.
		*/
		void initializeGrid();

		/**
		 * @brief Creates a string of the grid 
		 * @brief Each row of the grid is printed on a new line, with characters separated by spaces.
		 *
		 * @param grid A constant reference to a 2D vector of characters representing the grid to be printed.
		 */
		std::string printGrid();

		/**
		 * @brief Tries to place a word in the grid at a specified position and direction.
		 *
		 * This method checks if the word can fit in the grid starting from a given position
		 * and moving in a specified direction. It also ensures that the word does not overlap
		 * with previously placed words unless the overlapping cells match the current word's
		 * characters.
		 *
		 * @param grid A reference to a 2D vector of characters representing the word search grid.
		 * @param word The word to be placed in the grid.
		 * @param row The starting row index for placing the word.
		 * @param col The starting column index for placing the word.
		 * @param dRow The direction of movement in the row dimension (positive or negative).
		 * @param dCol The direction of movement in the column dimension (positive or negative).
		 * @param occupiedPositions A reference to an unordered set of positions that are already occupied by previously placed words.
		 *
		 * @return true if the word was successfully placed in the grid; false otherwise.
		*/
		bool placeWord(const std::string& word, int row, int col, int dRow, int dCol, PositionSet& occupiedPositions);

		/**
		 * @brief Adds a list of words to the grid, placing each word at a random position and direction.
		 *
		 * This method attempts to place each word from the provided list into the grid. It uses
		 * random positions and directions for placing the words and ensures that words do not
		 * overlap with previously placed words inappropriately. The method will retry placing a
		 * word if it cannot be placed in the initially chosen position and direction.
		 *
		 * @param grid A reference to a 2D vector of characters representing the word search grid.
		 * @param words A vector of strings representing the words to be added to the grid.
		*/
		void addWordsToGrid();

		/**
		 * @brief method to take user input word guess and check if correct
		 * 
		 * @param string input from user
		*/
		void guessWord(std::string input);

		/** 
		 * @brief Takes a word that has been found, and updates vector of positions found for print grid 
		 * @brief method to utilise / print found words as green
		 * 
		 * @param string key the key for the Map of the word that has been found and it's positions 
		 in the grid
		*/
		void updateWordVector(const std::string& key);

		/**
		 * @brief function to display menu
		*/
		bool menu() override;

		/**
		 * @brief function to set up initial game state 
		*/
		void setup() override;

		/**
		 * @brief Function to reset game state
		 * 
		 * Clears all data held within variable from previous game.
		*/
		void reset() override; 

		/**
		 * @brief function to generate game 
		*/
		std::string generate() override;

		/**
		 * @brief function to display screen
		*/
		void display() override;

		friend class WordfindTest;
};