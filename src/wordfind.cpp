#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <locale>
#include <codecvt>
#include <iterator>
#include <algorithm>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time
#ifdef _WIN32       // Check if windows so that it's cross-platform
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include "get_data.h"
#include "wordfind.h"

#pragma execution_character_set( "utf-8" )

// Function to remove all whitespaces from a string
std::string removeWhitespace(const std::string& input) {
    std::string output;
    // Copy all non-whitespace characters to the output string
    std::copy_if(input.begin(), input.end(), std::back_inserter(output), [](char c) {
        return !std::isspace(c);  // Check if the character is not a whitespace
        });
    return output;
}

std::string wstringToString(const std::wstring& wstr) {
    // Use wstring_convert to convert wstring (wide string) to string (narrow string)
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.to_bytes(wstr);
}

std::wstring stringToWstring(const std::string& str) {
    // Use wstring_convert to convert string (narrow string) to wstring (wide string)
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(str);
}


Wordfind::Wordfind() {
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
    std::cout << "\033[36m" << "-" << "\033[0m";
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


// Function to receive player input
bool Wordfind::waitForEnter() {
    std::cout << "Enter a word (or 'q' to quit)...\n";

    while (true) {
        std::string input;

        std::getline(std::cin, input);

        // Check if the user wants to quit
        if (input == "q" || input == "Q") {
            std::cout << "Quitting...\n";
            return true; // Exit the function
        }

        // Continue if input is empty
        if (input.empty()) {
            continue;
        }

        // Convert input to uppercase
        std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c) { return std::toupper(c); });

        // Check if the input matches any word in the list
        int correctGuess = std::count(words.begin(), words.end(), input);

        if (correctGuess > 0) {
            wordsFound.push_back(input);
            updateWordVector(input);
            return false; // Exit the function after successful input
        }
        else {
            clearLastNLines(2);
            std::cout << "Try again... \n";
        }
    }
    return true;
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

// Function to check if a character is a diacritic
bool Wordfind::isDiacritic(char32_t c) {
    if (c >= 0x0300 && c <= 0x036F) return true;
    if (c >= 0x1DC0 && c <= 0x1DFF) return true;
    // Latin Extended-A (includes macrons)
    if (c >= 0x0100 && c <= 0x017F) return true;
    return false;
}

// Function to check if the string contains any diacritic

bool Wordfind::hasDiacritics(const std::string& input) {
	std::u32string utf32Str;

	// Convert UTF-8 string to UTF-32 to handle multi-byte characters
	for (size_t i = 0; i < input.size();) {
		char32_t c;
		unsigned char byte = input[i];
		if (byte < 0x80) {
			c = byte;
			++i;
		}
		else if (byte < 0xE0) {
			c = (byte & 0x1F) << 6;
			c |= (input[++i] & 0x3F);
			++i;
		}
		else if (byte < 0xF0) {
			c = (byte & 0x0F) << 12;
			c |= (input[++i] & 0x3F) << 6;
			c |= (input[++i] & 0x3F);
			++i;
		}
		else {
			c = (byte & 0x07) << 18;
			c |= (input[++i] & 0x3F) << 12;
			c |= (input[++i] & 0x3F) << 6;
			c |= (input[++i] & 0x3F);
			++i;
		}
		utf32Str += c;
	}

	// Check each character in the string
	for (char32_t c : utf32Str) {
		if (isDiacritic(c)) {
			return true;
		}
	}

	return false;
}


// Mapping of macronized characters to their normal equivalents
std::unordered_map<wchar_t, wchar_t> macron_map = {
    {L'ā', L'a'}, {L'ē', L'e'}, {L'ī', L'i'},
    {L'ō', L'o'}, {L'ū', L'u'}, {L'Ā', L'A'},
    {L'Ē', L'E'}, {L'Ī', L'I'}, {L'Ō', L'O'},
    {L'Ū', L'U'}
};

// Function to convert a string with macrons to a normal string
std::wstring convertMacronsToNormal(const std::wstring& input) {
    std::wstring output;
    for (wchar_t ch : input) {
        // Check if the character is in the macron map and replace it
        if (macron_map.find(ch) != macron_map.end()) {
            output += macron_map[ch];
        }
        else {
            output += ch;  // Keep the character if it's not macronized
        }
    }
    return output;
}

// Function to remove invisible characters (like extra bytes, combining marks)
std::wstring removeInvisibleCharacters(const std::wstring& input) {
    std::wstring output;
    for (wchar_t ch : input) {
        if (ch >= 32) {  // Remove control characters and invisible characters (below 32 in Unicode)
            output += ch;
        }
    }
    return output;
}


 // Function to check if all words have been found
bool Wordfind::checkGameEnd() {
    return words.size() == wordsFound.size();
}

int Wordfind::startGame() {

    //std::wstring macronWord = L"kōrero";
    //std::wstring normalWord = convertMacronsToNormal(macronWord);

    //std::cout << "Original word: " << wstringToString(macronWord) << std::endl;
    //std::cout << "Converted word: " << wstringToString(normalWord) << std::endl;
    //std::cout << normalWord.length() << std::endl;

    bool runGame = true;
    DataGenerator dg; 
    int wordCount = 4;
    
    while (words.size() < wordCount) {
        std::wstring temp = L"";
        std::string nextWord = "";
        do {
            std::pair<std::string, std::string> wordDef = dg.get_random_entry();
            //nextWord = wordDef.first;
            //std::cout << "|" + wordDef.first + "|" << std::endl;
            temp = convertMacronsToNormal(stringToWstring(wordDef.first));
            nextWord = wstringToString(temp);
            nextWord = removeWhitespace(nextWord); //remove spaces before and after the word to prevent display errors

            //std::cout << "|" + nextWord + "|" << std::endl;
        } //while (hasDiacritics(nextWord) || nextWord.size() >= GRID_SIZE || nextWord.size() <= 2);
        while (nextWord.size() >= GRID_SIZE || nextWord.size() <= 2);

        std::transform(nextWord.begin(), nextWord.end(), nextWord.begin(), [](unsigned char c) { return std::toupper(c); });
        std::cout << nextWord << std::endl;;
        words.push_back(nextWord);
    }   

    std::vector<std::vector<char>> grid(Wordfind::GRID_SIZE, std::vector<char>(Wordfind::GRID_SIZE, ' ')); //the grid


    printf("Starting the game up!\n");

    initializeGrid(grid);

    printGrid(grid);
 
    addWordsToGrid(grid, words);

    while (runGame) {

        system("CLS"); // Clear the terminal screen

        std::cout << R"(
+=================================================+
|   __        __            _  __ _           _   |
|   \ \      / /__  _ __ __| |/ _(_)_ __   __| |  |
|    \ \ /\ / / _ \| '__/ _` | |_| | '_ \ / _` |  |
|     \ V  V / (_) | | | (_| |  _| | | | | (_| |  |
|      \_/\_/ \___/|_|  \__,_|_| |_|_| |_|\__,_|  |
|                                                 |
+=================================================+
)" << std::endl;
        printGrid(grid);
        
        bool value = waitForEnter();

        if (value) {
            std::cout << "See you later!" << std::endl;
            return 0;
        }

        runGame = !checkGameEnd();
        int linesToClear = GRID_SIZE + 3;
        std::cout << "Nice job!" << std::endl;
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