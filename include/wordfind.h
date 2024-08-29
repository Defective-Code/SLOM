/**
* Class to encapsulate Wordfind game functionality.
* Contains methods to display the game, handle input, and generate the set of words to use.
*/

#include <string.h>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <utility>  // For std::pair

class Wordfind {

	const int GRID_SIZE = 10; // Adjust as needed
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

		int datagentest();

		/***
		* Method that starts the game, 
		*
		* @param words The real words to be placed in the wordfind
		*/
		int startGame();

		/**
		* The default constructor, initializes the game state
		*/
		Wordfind();

	private:

		std::vector<std::string> getRandomWords();
		std::vector<std::string> words;
		std::vector<std::string> wordsFound;
		std::vector<Position> wordPositions;
		PositionSet wordsFoundCoordinates;
		std::unordered_map <std::string, PositionSet> wordToPositionMap;


		/**
		 * Initializes the grid with random letters from A to Z.
		 * Each cell in the grid is filled with a random uppercase letter.
		 *
		 * @param grid A reference to a 2D vector of characters representing the grid to be initialized.
		*/
		void initializeGrid(std::vector<std::vector<char>>& grid);

		/**
		 * Prints the grid to the standard output.
		 * Each row of the grid is printed on a new line, with characters separated by spaces.
		 *
		 * @param grid A constant reference to a 2D vector of characters representing the grid to be printed.
		 */
		void printGrid(const std::vector<std::vector<char>>& grid);

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
		bool placeWord(std::vector<std::vector<char>>& grid, const std::string& word, int row, int col, int dRow, int dCol, PositionSet& occupiedPositions);

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
		void addWordsToGrid(std::vector<std::vector<char>>& grid, const std::vector<std::string>& words);


		/**
		 * Checks if game has ended / all words have been found
		 * 
		 * @return bool: whether all words have been found or not
		*/
		bool checkGameEnd();


		/** 
		 * Takes a word that has been found, and updates vector of positions found for print grid 
		 * method to utilise / print found words as green
		 * 
		 * @param string key the key for the Map of the word that has been found and it's positions 
		 in the grid
		*/
		void updateWordVector(const std::string& key);



		/**
		 * Moves cursor up and clear line N times
		 * 
		 * @param int n the number of lines to clear
		 * 
		*/
		void clearLastNLines(int n);


		/**
		 * Function to reset game state
		 * 
		 * Clears all data held within variable from previous game.
		*/
		void resetGameState();

		/**
		 * Takes user input and checks if it is amongst words contained within the grid
		 * 
		 * If word entered is in grid then returns to reprint grid with word highlighted
		 * 
		*/
		void waitForEnter();
};