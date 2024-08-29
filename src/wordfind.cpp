#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <iterator>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time
#ifdef _WIN32       // Check if windows so that it's cross-platform
#include <Windows.h>
#else
#include <unistd.h>
#endif
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
    system("CLS"); //clear the terminal screen
    /*
    for (int i = 0; i <= grid.size(); i++) {
        for (int j = 0; j <= grid[i].size(); j++) {
            if (i == 0 && j == 0) {
                std::cout << " | " << std::endl;
            }
            else if (i == 0 ) {
                std::cout << " Test " << std::endl;
            } 
            else if (j == 0 || j == grid[i].size()) {
                std::cout << " - " << std::endl;
            }
            else {
                std::cout << grid[i][j] << ' ';
            }
        }
        std::cout << std::endl;
    }
    */
    
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {

            std::cout << grid[i][j] << ' ';
        }
        
    }
    
    /*
    for (const auto& row : grid) {
        for (char cell : row) {

            std::cout << cell << ' ';
        }
        std::cout << std::endl;
    }
    */
    
}

// Function to place a word in the grid
bool Wordfind::placeWord(std::vector<std::vector<char>>& grid, const std::string& word, int row, int col, int dRow, int dCol, std::unordered_set<Position, PositionHash, PositionEqual>& occupiedPositions) {
    int len = word.length();

    // Check if the word fits in the grid
    for (int i = 0; i < len; ++i) {
        int r = row + i * dRow;
        int c = col + i * dCol;
        Position pos = { r, c };

        if (r < 0 || r >= GRID_SIZE || c < 0 || c >= GRID_SIZE) return false;
        if (occupiedPositions.find(pos) != occupiedPositions.end() && grid[r][c] != word[i]) return false;

        wordPositions.push_back(pos);
    }

    wordToPositionMap[word] = std::unordered_set<Position>();

    // Place the word in the grid and mark positions
    for (int i = 0; i < len; ++i) {
        int r = row + i * dRow;
        int c = col + i * dCol;
        Position pos = { r, c };
        grid[r][c] = word[i];
        occupiedPositions.insert(pos);
        wordToPositionMap[word].insert(pos);
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


 // Function to clear last N lines in terminal
void Wordfind::clearLastNLines(int n) {
    for (int i = 0; i < n; ++i) {
        // Move cursor up one line and clear the line
        std::cout << "\033[A\033[2K";
    }
}


void Wordfind::waitForEnter() {
    std::cout << "Enter a word...\n";

    while (true){
        std::string dummy = "";

        while (dummy.empty()) {
            // Wait for user input
            std::getline(std::cin, dummy);
            // Convert word to uppercase
            std::transform(dummy.begin(), dummy.end(), dummy.begin(), [](unsigned char c) {return std::toupper(c);  });
        }
        int correctGuess = count(words.begin(), words.end(), dummy);

        if (correctGuess > 0) {
            wordsFound.push_back(dummy);
            updateWordVector(dummy);
            return;
        }
        else {
            clearLastNLines(1);
        }
    }
    
}


void Wordfind::updateWordVector(const std::string& key) {
    auto it = wordToPositionMap.find(key);
    if (it != wordToPositionMap.end()) {
        for (const Position& pos : it->second) {
            wordsFoundCoordinates.insert(pos);
        }
    }
    else {
        std::cout << "Key not found in wordToPositionMap: " << key << std::endl;
    }
}




 // Function to check if all words have been found
bool Wordfind::checkGameEnd() {
    return words.size() == wordsFound.size();
}

int Wordfind::startGame() {

    bool runGame = true;

    //test strings

    words = { "HELLO", "WORLD", "PUZZLE", "CPLUSPLUS" };

    std::vector<std::vector<char>> grid(Wordfind::GRID_SIZE, std::vector<char>(Wordfind::GRID_SIZE, ' ')); //the grid


    printf("Starting the game up!\n");

    initializeGrid(grid);
 
    addWordsToGrid(grid, words);

    while (runGame) {
        printGrid(grid);
        for (const auto& entry : wordToPositionMap) {
            std::cout << "Word: " << entry.first << "\n";
            std::cout << "Positions:\n";
            for (const auto& pos : entry.second) {
                std::cout << "  (" << pos.first << ", " << pos.second << ")\n";
            }
            std::cout << "\n";
        }
        waitForEnter();

        runGame = !checkGameEnd();
        int linesToClear = GRID_SIZE + 2;
        std::cout << "Nice job!";
        #ifdef _WIN32
                Sleep(1000);  // Sleep for 1000 milliseconds (2 seconds) on Windows
        #else
                sleep(1);     // Sleep for 1 seconds on Unix-based systems
        #endif
    
        clearLastNLines(linesToClear);
    }
	return 0;
}