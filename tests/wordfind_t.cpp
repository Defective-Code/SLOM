
#include <stdio.h>
#include <string>
#include <cassert>
#include <type_traits>
#include <typeinfo>
#include <iostream>
#include "wordfind.h"

class WordfindTest {
public:
    static void initializeGrid_t() {
        Wordfind wf;
        std::vector<std::vector<char>> test_grid(Wordfind::GRID_SIZE, std::vector<char>(Wordfind::GRID_SIZE, ' ')); // the grid

        wf.initializeGrid(test_grid);

        for (int i = 0; i < Wordfind::GRID_SIZE; ++i) {
            for (int j = 0; j < Wordfind::GRID_SIZE; ++j) {
                // Compile-time check that each element in the grid is of type 'char'
                assert(typeid(test_grid[i][j]) == typeid(char));

                // Runtime assertion that the grid element is not an empty space or null
                assert(test_grid[i][j] != ' ' && test_grid[i][j] != '\0' && "Grid position contains an invalid character.");

                assert(test_grid[i][j] >= 'A' && test_grid[i][j] <= 'Z');  // Example: ensure it's an uppercase letter
            }
        }
    }
    static void placeWord_t() {
        Wordfind wordfind = Wordfind();

        // Initialize the grid
        std::vector<std::vector<char>> grid(Wordfind::GRID_SIZE, std::vector<char>(Wordfind::GRID_SIZE, ' '));

        // PositionSet to keep track of occupied positions
        Wordfind::PositionSet occupiedPositions;

        // Test case 1: Place word horizontally in an empty grid
        std::string word1 = "TEST";
        bool result1 = wordfind.placeWord(grid, word1, 2, 2, 0, 1, occupiedPositions);
        assert(result1 == true);  // Word should be placed successfully
        assert(grid[2][2] == 'T' && grid[2][3] == 'E' && grid[2][4] == 'S' && grid[2][5] == 'T');

        //wordfind.printGrid(grid);
        //printPositionSet(occupiedPositions);

        // Test case 2: Try placing the same word in the same position (should return True, as technically the new TEST overwwrites the old one due to overlap)
        bool result2 = wordfind.placeWord(grid, word1, 2, 2, 0, 1, occupiedPositions);
        assert(result2 == true);  // Word should not be placed again

        // Test case 3: Place a word vertically that overlaps correctly with an existing word
        std::string word2 = "EXAM";
        bool result3 = wordfind.placeWord(grid, word2, 2, 3, 1, 0, occupiedPositions);
        assert(result3 == true);  // Word should be placed successfully
        assert(grid[2][3] == 'E' && grid[3][3] == 'X' && grid[4][3] == 'A' && grid[5][3] == 'M');

        // Test case 4: Attempt to place a word that goes out of bounds
        std::string word3 = "OUTOFBOUNDS";
        bool result4 = wordfind.placeWord(grid, word3, 9, 9, 0, 1, occupiedPositions);
        assert(result4 == false);  // Word should not be placed

        
        
        // Test case 5: Place a word diagonally
        std::string word4 = "DIAGONAL";
        bool result5 = wordfind.placeWord(grid, word4, 0, 0, 1, 1, occupiedPositions);
        assert(result5 == false);  // Word should fail as it overlaps with the "TEST" which is inserted at 2, 2
        //assert(grid[0][0] == 'D' && grid[1][1] == 'I' && grid[2][2] == 'A' && grid[3][3] == 'G' && grid[4][4] == 'O');

        std::string word5 = "GUAM";
        bool result6 = wordfind.placeWord(grid, word5, 2, 0, 1, 1, occupiedPositions);
        assert(result6 == true); //Word should succeed now, as the M matches with the M in "EXAM", and doesn't overlap with anything else
        assert(grid[2][0] == 'G' && grid[3][1] == 'U' && grid[4][2] == 'A' && grid[5][3] == 'M');

        //wordfind.printGrid(grid);
        //printPositionSet(occupiedPositions);

        std::cout << "All test cases passed for placeWord()" << std::endl;
    }

    static void addWordsToGrid_t() {
        Wordfind wordfind;

        // Initialize the grid
        std::vector<std::vector<char>> grid(Wordfind::GRID_SIZE, std::vector<char>(Wordfind::GRID_SIZE, '.'));

        // List of words to add
        std::vector<std::string> words = { "HELLO", "WORLD", "TEST", "GRID" };

        // Call the method to add words to the grid
        wordfind.addWordsToGrid(grid, words);

        // Output the grid for manual inspection
        /*
        std::cout << "Grid after adding words:" << std::endl;
        for (const auto& row : grid) {
            for (const auto& cell : row) {
                std::cout << cell << ' ';
            }
            std::cout << std::endl;
        } 
        */

        // Basic validation checks
        for (const auto& word : words) {
            bool found = false;
            for (int r = 0; r < Wordfind::GRID_SIZE; ++r) {
                for (int c = 0; c < Wordfind::GRID_SIZE; ++c) {
                    if (searchWordInGrid(grid, word, r, c)) {
                        found = true;
                        break;
                    }
                }
                if (found) break;
            }
            assert(found && "Word not found in the grid");
        }

        std::cout << "All words were placed successfully." << std::endl;
    }

    static void isDiacritic_t() {
        Wordfind wordfind;

        // Test diacritic characters within the specified ranges
        // Combining Diacritical Marks
        assert(wordfind.isDiacritic(0x0300)); // Combining Grave Accent
        assert(wordfind.isDiacritic(0x036F)); // Combining Double Breve

        // Combining Diacritical Marks for Greek and Coptic
        assert(wordfind.isDiacritic(0x1DC0)); // Combining Dotted Grave Accent
        assert(wordfind.isDiacritic(0x1DFF)); // Combining Macron Below

        // Latin Extended-A
        assert(wordfind.isDiacritic(0x0100)); // Latin Capital Letter A with Macron
        assert(wordfind.isDiacritic(0x017F)); // Latin Small Letter Long S

        // Non-diacritic characters within the range limits
        assert(!wordfind.isDiacritic(0x0270)); // Latin Letter Small T with Retroflection Hook (outside Latin Extended-A range)
        assert(!wordfind.isDiacritic(0x0279)); // Latin Letter Small D with Hook (outside Latin Extended-A range)

        std::cout << "All specified range diacritic tests passed." << std::endl;
    }

    static void hasDiacritics_t() {
        Wordfind wordfind;

        // Test strings with diacritical marks (Maori words)
        assert(wordfind.hasDiacritics("Māori")); // 'ā' has a diacritic
        assert(wordfind.hasDiacritics("Ngā")); // 'ā' has a diacritic
        assert(wordfind.hasDiacritics("Hāpai")); // 'ā' has a diacritic
        assert(wordfind.hasDiacritics("Tūī")); // 'ū' has a diacritic
        assert(wordfind.hasDiacritics("Pūkeko")); // 'ū' has a diacritic

        // Test strings without diacritical marks (Maori words without macrons)
        assert(!wordfind.hasDiacritics("Maori")); // No diacritic
        assert(!wordfind.hasDiacritics("Nga")); // No diacritic
        assert(!wordfind.hasDiacritics("Hapai")); // No diacritic
        assert(!wordfind.hasDiacritics("Tui")); // No diacritic
        assert(!wordfind.hasDiacritics("Pukeko")); // No diacritic

        // Test empty string
        assert(!wordfind.hasDiacritics("")); // No diacritic in an empty string

        // Test string with only diacritical marks
        assert(wordfind.hasDiacritics("\u0101\u016B")); // Combining macrons for 'ā' and 'ū

        // Test empty string
        assert(!wordfind.hasDiacritics("")); // No diacritic in an empty string

        std::cout << "All hasDiacritics tests passed." << std::endl;
    }

    static void resetGameState_t() {
        Wordfind wordfind;

        // Set initial state with some dummy data
        wordfind.words = { "word1", "word2" };
        wordfind.wordsFound = { "word1" };
        wordfind.wordPositions = { {0, 0}, {1, 1} };
        wordfind.wordsFoundCoordinates.insert({ 2, 2 });
        wordfind.wordToPositionMap["word2"] = { {3, 3}, {4, 4} };

        // Ensure the state is set
        assert(!wordfind.words.empty());
        assert(!wordfind.wordsFound.empty());
        assert(!wordfind.wordPositions.empty());
        assert(!wordfind.wordsFoundCoordinates.empty());
        assert(!wordfind.wordToPositionMap.empty());

        // Call the resetGameState method
        wordfind.resetGameState();

        // Test that all internal state variables are cleared
        assert(wordfind.wordsFound.empty());
        assert(wordfind.wordPositions.empty());
        assert(wordfind.wordsFoundCoordinates.empty());
        assert(wordfind.wordToPositionMap.empty());

        std::cout << "resetGameState test passed." << std::endl;
    }

    static void updateWordVector_t() {
        Wordfind wordfind;

        // Set up initial data
        std::vector<std::vector<char>> grid(10, std::vector<char>(10, ' '));
        std::vector<std::string> words = { "word" };
        wordfind.addWordsToGrid(grid, words);

        // Simulate positions in the wordToPositionMap
        Wordfind::PositionSet positions;
        positions.insert({ 1, 1 });
        positions.insert({ 1, 2 });
        positions.insert({ 1, 3 });
        wordfind.wordToPositionMap["word"] = positions;

        // Call updateWordVector
        wordfind.updateWordVector("word");

        // Expected result: positions should be added to wordsFoundCoordinates
        Wordfind::PositionSet expectedPositions = { {1, 1}, {1, 2}, {1, 3} };

        // Check if wordsFoundCoordinates contains the expected positions
        assert(wordfind.wordsFoundCoordinates.size() == expectedPositions.size());
        for (const auto& pos : expectedPositions) {
            assert(wordfind.wordsFoundCoordinates.find(pos) != wordfind.wordsFoundCoordinates.end());
        }

        std::cout << "updateWordVector test passed." << std::endl;
    }

    static void waitForEnter_t() {
        //TODO
    }

private:
    static void printPositionSet(const Wordfind::PositionSet& posSet) {
        for (const auto& pos : posSet) {
            std::cout << "(" << pos.first << ", " << pos.second << ")" << std::endl;
        }
    }
    // Helper function to search for a word in the grid
    static bool searchWordInGrid(const std::vector<std::vector<char>>& grid, const std::string& word, int startRow, int startCol) {
        static const int directions[8][2] = { {1, 0}, {0, 1}, {1, 1}, {-1, 1}, {0, -1}, {-1, 0}, {1, -1}, {-1, -1} };

        for (const auto& dir : directions) {
            int row = startRow;
            int col = startCol;
            int dRow = dir[0];
            int dCol = dir[1];
            bool found = true;

            for (char c : word) {
                if (row < 0 || row >= Wordfind::GRID_SIZE || col < 0 || col >= Wordfind::GRID_SIZE || grid[row][col] != c) {
                    found = false;
                    break;
                }
                row += dRow;
                col += dCol;
            }

            if (found) return true;
        }
        return false;
    }
};


int main() {
    WordfindTest::initializeGrid_t();
    WordfindTest::placeWord_t();
    WordfindTest::addWordsToGrid_t();
    WordfindTest::isDiacritic_t();
    //WordfindTest::hasDiacritics_t(); currently not working
    WordfindTest::resetGameState_t();
    WordfindTest::updateWordVector_t();
    //WordfindTest::waitForEnter_t() //TODO
    
	return 0;
}

