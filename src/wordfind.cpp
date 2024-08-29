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
    const char letters[] = "ABCDEFGHIKLMNOPRSTUVW";
    const int numLetters = sizeof(letters) - 1; // Exclude null terminator

    for (int i = 0; i < Wordfind::GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            grid[i][j] = letters[rand() % numLetters];
        }
    }
}

// Function to print the grid
void Wordfind::printGrid(const std::vector<std::vector<char>>& grid) {
    system("CLS"); // Clear the terminal screen
    
    for (const std::string& str : words) {
        std::cout << str << std::endl;
    }

    int r = 0;
    for (int i = 0; i <= GRID_SIZE; i++) {
        std::cout << "\033[36m" << "__" << "\033[0m";
    }
    std::cout << "\033[36m" << "_" << "\033[0m";
    
    std::cout << std::endl;
    for (const auto& row : grid) {
        int c = 0;
        std::cout << "\033[36m" << "|" << "\033[0m" << ' ';
        for (char cell : row) {
            Position pos = { r, c };
            auto it = wordsFoundCoordinates.find(pos);
            if (it != wordsFoundCoordinates.end()) {
                std::cout << "\033[32m" << cell << "\033[0m" << ' ';
            }
            else {
                std::cout << cell << ' ';
            }
            c++;
        }
        std::cout << "\033[36m" << "|" << "\033[0m" << std::endl;
        r++;
    }
    for (int i = 0; i <= GRID_SIZE; i++) {
        std::cout << "\033[36m" << "--" << "\033[0m";
    }
    std::cout << std::endl;
}

// Function to place a word in the grid
bool Wordfind::placeWord(std::vector<std::vector<char>>& grid, const std::string& word, int row, int col, int dRow, int dCol, PositionSet& occupiedPositions) {
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

    wordToPositionMap[word] = PositionSet();

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

    std::unordered_set<Position, PositionHash> occupiedPositions;
    
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


 // Function to update words found set of positions of chars in the grid
void Wordfind::updateWordVector(const std::string& key) {
    auto it = wordToPositionMap.find(key);
    if (it != wordToPositionMap.end()) {
        for (const Position& pos : it->second) {
            wordsFoundCoordinates.insert(pos);
        }
    }
}


 // Function to reset game state
void Wordfind::resetGameState() {
    wordsFound.clear();
    wordPositions.clear();
    wordsFoundCoordinates.clear();
    wordToPositionMap.clear();
}

 // Function to remove accents and macrons from a word 
// Generated by ChatGPT
// Function to remove accents and macrons
std::string Wordfind::removeAccentsAndMacrons(const std::string& input) {
    std::unordered_map<char, char> accentMap = {
        {'Ā', 'A'}, {'ā', 'a'}, {'Ē', 'E'}, {'ē', 'e'}, {'Ī', 'I'}, {'ī', 'i'},
        {'Ō', 'O'}, {'ō', 'o'}, {'Ū', 'U'}, {'ū', 'u'},
    };

    std::string result;
    result.reserve(input.size());

    for (char c : input) {
        if (accentMap.find(c) != accentMap.end()) {
            result += accentMap[c];
        }
        else {
            result += c;
        }
    }

    return result;
}


 // Function to check if all words have been found
bool Wordfind::checkGameEnd() {
    return words.size() == wordsFound.size();
}

int Wordfind::startGame() {

    bool runGame = true;

    DataGenerator dg; 
    int wordCount = 4;

    while (words.size() < wordCount){
        std::pair wordDef = dg.get_random_entry();
        std::string nextWord = wordDef.first;
        if (nextWord.size() < GRID_SIZE && nextWord.size() > 2) {
            std::string accentLessWord = removeAccentsAndMacrons(nextWord);
            std::transform(accentLessWord.begin(), accentLessWord.end(), accentLessWord.begin(), [](unsigned char c) {return std::toupper(c);  });
            words.push_back(accentLessWord);
        }
    }

    std::vector<std::vector<char>> grid(Wordfind::GRID_SIZE, std::vector<char>(Wordfind::GRID_SIZE, ' ')); //the grid


    printf("Starting the game up!\n");

    initializeGrid(grid);
 
    addWordsToGrid(grid, words);

    while (runGame) {
        printGrid(grid);
        
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
    std::cout << "YOU WIN!" << std::endl;
    #ifdef _WIN32
        Sleep(1000);
    #else
        sleep(1);
    #endif
        resetGameState();
	return 0;
}