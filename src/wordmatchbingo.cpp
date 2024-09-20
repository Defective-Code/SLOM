#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility> // For std::pair
#include <random>  // For std::shuffle and random number engine
#include "wordmatchbingo.h"
#include "get_data.h"

// class WordMatchBingo {
// public:
//     void selectBingoCard();
//     void startGame();
//     void selectBingoWordPool();
//     void receiveUserInput();
//     void displayBingoCard();
//     void displayCurrentBingoWord();
//     bool compareUserInputToBingoCard(const std::string& userInput);
//     void updateWordWithStrikethrough(std::string& word);

// private:
//     std::vector<std::pair<std::string, std::string>> bingoWordPool;
//     std::vector<std::pair<std::string, std::string>> bingoCard; a
//     std::pair<std::string, std::string> currentBingoWord = {"", ""};
//     std::string userGuess = "";
// };

// Define constants
// In WordMatchBino.cpp


// Function definitions

void WordMatchBingo::reset() {
    // Clear the bingo word pool and bingo card
    bingoWordPool.clear();
    bingoCard.clear();
    
    // Reset the current bingo word and user guess
    currentBingoWord = {"", ""};
    userGuess = "";

    // Reset the count of words found
    wordsFound = 0;
}


//Function to check if a character is a diacritic
bool WordMatchBingo::isDiacritic(char32_t c) {
    if (c >= 0x0300 && c <= 0x036F) return true;
    if (c >= 0x1DC0 && c <= 0x1DFF) return true;
    //Latin Extended-A (includes macrons)
    if (c >= 0x0100 && c <= 0x017F) return true;
    return false;
}

//Function to check if the string contains any diacritic
bool WordMatchBingo::hasDiacritics(const std::string& input) {
    std::u32string utf32Str;

    //Convert UTF-8 string to UTF-32 to handle multi-byte characters
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

    //Check each character in the string
    for (char32_t c : utf32Str) {
        if (isDiacritic(c)) {
            return true;
        }
    }

    return false;
}

void WordMatchBingo::selectBingoWordPool() {
    std::vector<std::pair<std::string, std::string>> allWords;

    DataGenerator generator; // Assuming DataGenerator is defined and accessible
    std::string result;

    // Generate a sufficient number of words ensuring no diacritics
    while (allWords.size() < bingoWordPoolCount) {
        auto entry = generator.get_random_entry();
        result = entry.first;

        // Check if the word has diacritics
        if (!hasDiacritics(result)) {
            // Trim trailing whitespace
            auto endPos = std::find_if(result.rbegin(), result.rend(), [](char ch) {
                return !std::isspace(static_cast<unsigned char>(ch));
            }).base();
            result.erase(endPos, result.end());

            // Add the valid entry to allWords
            allWords.push_back(entry);
        }
    }

    // Shuffle the collected valid words
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(allWords.begin(), allWords.end(), g);

    // Assign the selected words to bingoWordPool
    bingoWordPool.assign(allWords.begin(), allWords.begin() + bingoWordPoolCount);
}

void WordMatchBingo::updateWordWithStrikethrough(std::string& word) {
    word = "\033[9m" + word + "\033[0m";  // Add strikethrough formatting using ANSI codes
}


void WordMatchBingo::selectBingoCard() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(bingoWordPool.begin(), bingoWordPool.end(), g);
    bingoCard.assign(bingoWordPool.begin(), bingoWordPool.begin() + bingoCardCount);

}

size_t getDisplayLength(const std::string& word) {
    size_t length = 0;
    bool inEscapeCode = false;
    for (char ch : word) {
        if (ch == '\033') {
            inEscapeCode = true;
        } else if (ch == 'm') {
            inEscapeCode = false;
        } else if (!inEscapeCode) {
            ++length;
        }
    }
    return length;
}

void WordMatchBingo::displayCurrentBingoWord() {
    if (bingoWordPool.empty()) {
        std::cout << "No more words in the pool.\n";
        return;
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<> dis(0, bingoWordPool.size() - 1);
    int index = dis(g);

    auto selectedWord = bingoWordPool[index];
    currentBingoWord = selectedWord;

    std::cout << "\nSelected Word: " << selectedWord.first << std::endl;
    std::cout << "Definition: " << selectedWord.second << std::endl;

    bingoWordPool.erase(bingoWordPool.begin() + index);
}

void WordMatchBingo::displayBingoCard() {
    size_t maxWordLength = 0;
    for (const auto& pair : bingoCard) {
        maxWordLength = std::max(maxWordLength, getDisplayLength(pair.first));
    }

    size_t boxWidth = maxWordLength + 4;

    std::cout << std::string(boxWidth, '-') << std::endl;

    for (const auto& pair : bingoCard) {
        size_t wordLength = getDisplayLength(pair.first);
        size_t padding = (boxWidth - wordLength - 2) / 2;
        std::string paddingSpaces = std::string(padding, ' ');
        size_t rightPadding = boxWidth - 2 - wordLength - padding;
        std::cout << "| " << paddingSpaces << pair.first << std::string(rightPadding, ' ') << " |" << std::endl;
    }

    std::cout << std::string(boxWidth, '-') << std::endl;
}

void WordMatchBingo::receiveUserInput() {
    bool lastWasHint = false;
    while (true) {
        std::string userInput;
        std::cout << "Enter a word (or 'Hint' for a hint): ";
        std::cin >> userInput;

        // Check for valid input or commands
        if (userInput == "Hint"){
            if(lastWasHint){
               clearLastNLines(1); 
            }
            clearLastNLines(1);
            getHint();
            lastWasHint = true;
        }else{
            userGuess = userInput;
            break;
        }
    }
}


// Helper function to convert a string to lowercase
std::string toLowerCase(const std::string& str) {
    std::string lowerStr;
    for (char ch : str) {
        lowerStr += std::tolower(static_cast<unsigned char>(ch));  // Ensure correct conversion for all characters
    }
    return lowerStr;
}

bool WordMatchBingo::compareUserInputToBingoCard(const std::string& userInput) {
    // Check if the userInput matches the currentBingoWord.first
    if (toLowerCase(currentBingoWord.first) == toLowerCase(userInput)) {
        // Now check if it's in the bingoCard
        auto it = std::find_if(bingoCard.begin(), bingoCard.end(),
            [&userInput](const std::pair<std::string, std::string>& pair) {
                return toLowerCase(pair.first) == toLowerCase(userInput);
            });

        if (it != bingoCard.end()) {
            updateWordWithStrikethrough(it->first); // Update word with strikethrough
            wordsFound += 1;
            return true;
        }
    }

    return false;
}


void WordMatchBingo::clearLastNLines(int n)
{
	for (int i = 0; i < n; ++i)
	{
		//Move cursor up one line and clear the line
		std::cout << "\033[A\033[2K";
	}
}

void WordMatchBingo::getHint() {
    if (!currentBingoWord.first.empty()) {
        std::cout << "Hint: The first letter of the current word is '" 
                  << currentBingoWord.first[0] << "'.\n";
    } else {
        std::cout << "No current bingo word available for a hint.\n";
    }
}



void WordMatchBingo::startGame() {
    clearLastNLines(13); 
    selectBingoWordPool();
    selectBingoCard();
    while (!bingoCard.empty() && !bingoWordPool.empty() && wordsFound < bingoCardCount) {
        displayCurrentBingoWord();
        displayBingoCard();
        receiveUserInput();
        
        
        bool matchResult = compareUserInputToBingoCard(userGuess);
        
        clearLastNLines(15);
    }

    std::cout << "Game over! All words have been guessed.\n\n";
    reset();
}

// int main() {
//     WordMatchBingo game;
//     game.selectBingoWordPool(); // Populate the word pool
//     game.selectBingoCard(); // Populate the bingo card
//     game.startGame(); // Start the game
//     return 0;
// }"