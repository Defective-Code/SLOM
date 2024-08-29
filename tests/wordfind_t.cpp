
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
	return 0;
}

