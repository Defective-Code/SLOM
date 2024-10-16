﻿#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <locale>
#include <codecvt>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <thread>
#include <random>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time

#include "get_data.h"
#include "io_handler.h"
#include "wordfind.h"


// Function to initialize the grid with random letters
void Wordfind::initializeGrid() {
    grid = std::vector<std::vector<char>>(Wordfind::GRID_SIZE, std::vector<char>(Wordfind::GRID_SIZE, ' ')); //initialize the grid.
    const char letters[] = "ABCDEFGHIKLMNOPRSTUVW";
    const int numLetters = sizeof(letters) - 1; // Exclude null terminator

    for (int i = 0; i < Wordfind::GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            grid[i][j] = letters[rand() % numLetters];
        }
    }
}

// Function to place a word in the grid
bool Wordfind::placeWord(const std::string& word, int row, int col, int dRow, int dCol, PositionSet& occupiedPositions) {
    size_t len = word.length();

    // Check if the word fits in the grid
    for (int i = 0; i < len; ++i) {
        int r = row + i * dRow;
        int c = col + i * dCol;
        Position pos = { r, c };

        if (r < 0 || r >= GRID_SIZE || c < 0 || c >= GRID_SIZE) return false;
        if (occupiedPositions.find(pos) != occupiedPositions.end() && grid[r][c] != word[i]) return false;

        
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
        if(i == 0) wordPositions.push_back(pos);
    }

    return true;
}

// Function to add words to the grid
void Wordfind::addWordsToGrid() {
    std::srand(static_cast<unsigned int>(std::time(0)));; // Seed for randomness
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
            placed = placeWord(word, row, col, dRow, dCol, occupiedPositions);
        }
    }
}

//this method checks if a given input string is in the words vector
void Wordfind::guessWord(std::string input) {
   
    int64_t correctGuess = std::count(words.begin(), words.end(), input);
    if (correctGuess > 0) {
        wordsFound.push_back(input);
        updateWordVector(input);
    }
    else {
        clearLastNLines(2);
        
        std::cout << "Try again... \n" << std::flush;

        std::this_thread::sleep_for(std::chrono::seconds(2));
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



// Function that sets up initial game state
void Wordfind::setup() {
    DataGenerator dg;
    while (words.size() < Wordfind::WORD_COUNT) {
        std::string nextWord = "";
        std::string nextDef = "";
        do {
            std::pair<std::string, std::string> wordDef = dg.get_random_entry();
            nextWord = wordDef.first;
            nextDef = wordDef.second;
            //std::cout << "|" + wordDef.first + "|" << std::endl;
            nextWord = removeWhitespace(nextWord); //remove spaces before and after the word to prevent display errors
            
            //std::cout << "|" + nextWord + "|" << std::endl;
        } //while (hasDiacritics(nextWord) || nextWord.size() >= GRID_SIZE || nextWord.size() <= 2);
        while (nextWord.size() >= GRID_SIZE || nextWord.size() <= 2);

        //std::transform(nextWord.begin(), nextWord.end(), nextWord.begin(), [](unsigned char c) { return std::tolower(c); });
        nextWord = toLowerCase(nextWord);
        //std::cout << nextWord << std::endl;
        
        wordDefs.insert({ nextWord, nextDef }); //add to definition map

        words.push_back(nextWord);
    }


    initializeGrid();

    //printGrid(grid); this is a test print to check if the grid has been filled with random letters correctly

    addWordsToGrid();
}

// Function to print the grid
std::string Wordfind::printGrid() {
    std::ostringstream oss;
    int r = 0;
    for (int i = 0; i <= GRID_SIZE; i++) {
        oss << "\033[36m" << "__" << "\033[0m";
    }
    oss << "\033[36m" << "_" << "\033[0m";
    
    oss << std::endl;
    for (const auto& row : grid) {
        int c = 0;
        oss << "\033[36m" << "|" << "\033[0m" << ' ';
        for (char cell : row) {
            Position pos = { r, c };
            auto it = wordsFoundCoordinates.find(pos);
            auto it2 = hintCoords.find(pos);
            char up_cell = toupper(cell);
            if (it != wordsFoundCoordinates.end() || it2 != hintCoords.end()) { //case if hint is given but word hasn't been found yet
                oss << "\033[32m" << up_cell << "\033[0m" << ' ';
            } 
            else {
                oss << up_cell << ' ';
            }
            c++;
        }
        oss << "\033[36m" << "|" << "\033[0m" << std::endl;
        r++;
    }
    for (int i = 0; i <= GRID_SIZE; i++) {
        oss << "\033[36m" << "--" << "\033[0m";
    }
    oss << "\033[36m" << "-" << "\033[0m";
    oss << std::endl;

    return oss.str();
}

// Function that generates the string to be displayed, this is seperate from the display method for testing purposes
std::string Wordfind::generate() {
    std::ostringstream oss;

    //this prints the words for testing purposes
    /*
    for (const auto& word : words)
    {
        oss << word << "\n";
    }
    */

    oss << R"(
+=================================================+
|   __        __            _  __ _           _   |
|   \ \      / /__  _ __ __| |/ _(_)_ __   __| |  |
|    \ \ /\ / / _ \| '__/ _` | |_| | '_ \ / _` |  |
|     \ V  V / (_) | | | (_| |  _| | | | | (_| |  |
|      \_/\_/ \___/|_|  \__,_|_| |_|_| |_|\__,_|  |
|                                                 |
+=================================================+
)" << std::endl;

    size_t wordsRemaining = words.size() - wordsFound.size();
    oss << "Words left to find: " << wordsRemaining << "\n";

    oss << "Words Found so far :\n";
    for (const std::string& word : wordsFound)
    {
    oss << word << " : " << wordDefs.at(word) << "\n";
    }


    oss << printGrid() << std::endl;

    oss << "Press 1) to guess a word\nPress 2) to get a hint\nPress q to quit" << std::endl;

    return oss.str();
}

// function to display screen
void Wordfind::display() {
    clearScreen();
    std::cout << generate() << std::endl;

}

// function to display menu
bool Wordfind::menu() {
    char ch = getSingleCharacter();
    //std::cout << ch << std::endl;
    switch (ch) {
    case '1':
    {
        std::string input = getWord();
        guessWord(input);
        break;
    }
    case '2':
    {
        giveHint();
        break;
    }
    case 'q':
        printf("Quitting.....\n");
        return false;
    default:
        printf("Please select a valid option\n");
    }

    return true;
}

// function to give hint to user
void Wordfind::giveHint() {

    if(hintsGiven.size() >= WORD_COUNT) {
        std::cout << "All hints already given, sorry" << std::endl; 
        return;
    }
    
    // Create a random number generator
    std::random_device rd;  // Seed for the random number engine
    std::mt19937 gen(rd()); // Mersenne Twister engine initialized with rd()

    // Define a distribution from 0 to WORD_COUNT  
    std::uniform_int_distribution<> distrib(0, WORD_COUNT-1); //between 0 and WORD_COUNT-1 inclusive
    
    int random_number = 0;
    std::vector<int>::iterator it;
    //std::string word = "";

    //this loop iterates until it finds an index that has not already been assigned a hint.
    do {
        
        random_number = distrib(gen); // Generate a random index
        it = std::find(hintsGiven.begin(), hintsGiven.end(), random_number);
        //word = words[random_number]; // Get the word corresponding to the random index

    } while(it != hintsGiven.end());
    //std::cout << wordPositions.size() << random_number << std::endl;
    // Retrieve the set of coordinates for the word
    Position coord = wordPositions[random_number]; // Get the coordinates set for the word

    hintCoords.insert(coord); //add the coord to display in the grid

    hintsGiven.push_back(random_number); //add the index to the hint given vector 

    //std::string& word = words[random_number]; // Get the reference to the word

    // std::cout << random_number << std::endl;
    // std::cout << word << std::endl;

    // ANSI escape code for green text
    //std::string green = "\033[32m";
    // ANSI escape code to reset text color
    //std::string reset = "\033[0m";

    // Modify the first character of the word in place
    //word = green + word[0] + reset + word.substr(1); // Modify the original word
    //std::cout << word << std::endl;

}

// function to start game 
int Wordfind::startGame() {

    setup();

    while (wordsFound.size() < words.size()) { //looping until player has found all words
        display();
        if(!menu()) {
            reset();
            return 0;
        }
    }
    display();

    std::cout << "Well done for finding all the words!" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    reset();
	return COIN_AMOUNT;
}

 // Function to reset game state
void Wordfind::reset() {
    words.clear();
    wordsFound.clear();
    wordPositions.clear();
    wordsFoundCoordinates.clear();
    wordToPositionMap.clear();
    hintsGiven.clear();
    hintCoords.clear();
}