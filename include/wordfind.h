/**
* Class to encapsulate Wordfind game functionality.
* Contains methods to display the game, handle input, and generate the set of words to use.
*/

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
		* Method that starts the game, 
		*
		* @param words The real words to be placed in the wordfind
		*/
		int startGame();

	private:

		std::vector<std::string> words; //vector of the words to find
		std::vector<std::string> wordsFound; //vector of the words that have been found
		std::vector<Position> wordPositions; //vector of each corresponding words position in the grid. Each position is the x,y of the first 
		PositionSet wordsFoundCoordinates;  //set of positions that have been found.
		std::unordered_map <std::string, PositionSet> wordToPositionMap; 

		std::vector<std::vector<char>> grid; //the grid of letters


		std::vector<std::string> getRandomWords();

		/**
		 * Initializes the grid with random letters from A to Z.
		 * Each cell in the grid is filled with a random uppercase letter.
		 *
		 * @param grid A reference to a 2D vector of characters representing the grid to be initialized.
		*/
		void initializeGrid();

		/**
		 * Prints the grid to the standard output.
		 * Each row of the grid is printed on a new line, with characters separated by spaces.
		 *
		 * @param grid A constant reference to a 2D vector of characters representing the grid to be printed.
		 */
		std::string printGrid();

		/**
		 * Tries to place a word in the grid at a specified position and direction.
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
		 * Adds a list of words to the grid, placing each word at a random position and direction.
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

		void guessWord(std::string input);

		/** 
		 * Takes a word that has been found, and updates vector of positions found for print grid 
		 * method to utilise / print found words as green
		 * 
		 * @param string key the key for the Map of the word that has been found and it's positions 
		 in the grid
		*/
		void updateWordVector(const std::string& key);

		void menu();

		void setup();

		/**
		 * Function to reset game state
		 * 
		 * Clears all data held within variable from previous game.
		*/
		void reset();

		std::string generate();

		void display();

		friend class WordfindTest;
};