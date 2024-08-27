#include <string>
#include <unordered_map>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()
#include "get_data.h"
#include "wordfind.h"


Wordfind::Wordfind() {
    
}

int Wordfind::datagentest() {
	DataGenerator dg;

		std::pair < std::string, std::string> randword = dg.get_random_entry();
		std::cout << "Random word: " << randword.first << "\n";
		std::cout << "Definition: " << randword.second << "\n";
		return 0;
}

// Function to initialize the grid with random letters
void Wordfind::initializeGrid(std::vector<std::vector<char>>& grid) {
    const char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int numLetters = sizeof(letters) - 1; // Exclude null terminator

    for (int i = 0; i < Wordfind::GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            grid[i][j] = letters[rand() % numLetters];
        }
    }
}

// Function to print the grid
void Wordfind::printGrid(const std::vector<std::vector<char>>& grid) {
    for (const auto& row : grid) {
        for (char cell : row) {
            std::cout << cell << ' ';
        }
        std::cout << std::endl;
    }
}

// Function to place a word in the grid
bool Wordfind::placeWord(std::vector<std::vector<char>>& grid, const std::string& word, int row, int col, int dRow, int dCol, std::unordered_set<Position, PositionHash, PositionEqual>& occupiedPositions) {
    int len = word.length();
    std::vector<Position> wordPositions;

    // Check if the word fits in the grid
    for (int i = 0; i < len; ++i) {
        int r = row + i * dRow;
        int c = col + i * dCol;
        Position pos = { r, c };

        if (r < 0 || r >= GRID_SIZE || c < 0 || c >= GRID_SIZE) return false;
        if (occupiedPositions.find(pos) != occupiedPositions.end() && grid[r][c] != word[i]) return false;

        wordPositions.push_back(pos);
    }

    // Place the word in the grid and mark positions
    for (int i = 0; i < len; ++i) {
        int r = row + i * dRow;
        int c = col + i * dCol;
        Position pos = { r, c };
        grid[r][c] = word[i];
        occupiedPositions.insert(pos);
    }

    return true;
}

// Function to add words to the grid
void Wordfind::addWordsToGrid(std::vector<std::vector<char>>& grid, const std::vector<std::string>& words) {
    std::srand(std::time(0)); // Seed for randomness
    const int directions[8][2] = { {1, 0}, {0, 1}, {1, 1}, {-1, 1}, {0, -1}, {-1, 0}, {1, -1}, {-1, -1} };

    std::unordered_set<Position, PositionHash, PositionEqual> occupiedPositions;
    
    for (const auto& word : words) {
        bool placed = false;
        while (!placed) {
            int row = rand() % GRID_SIZE;
            int col = rand() % GRID_SIZE;
            int dir = rand() % 8;
            int dRow = directions[dir][0];
            int dCol = directions[dir][1];
            placed = placeWord(grid, word, row, col, dRow, dCol, occupiedPositions);
        }
    }
}

void waitForEnter() {
    std::string dummy = "";
    std::cout << "Press Enter to continue...";

    while (dummy.empty()) {
        // Wait for user input
        std::getline(std::cin, dummy);
    }
    
    
}


int Wordfind::startGame() {
	//DataGenerator dg;
	//datagentest();

	//datagentest();

    //test strings
    std::vector<std::string> words = { "HELLO", "WORLD", "PUZZLE", "CPLUSPLUS" };

    std::vector<std::vector<char>> grid(Wordfind::GRID_SIZE, std::vector<char>(Wordfind::GRID_SIZE, ' ')); //the grid

    printf("Starting the game up!\n");

    initializeGrid(grid);
 
    addWordsToGrid(grid, words);
    
    printGrid(grid);

    waitForEnter();

	return 0;
}