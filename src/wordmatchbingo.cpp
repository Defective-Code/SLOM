#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility> // For std::pair
#include <random>  // For std::shuffle and random number engine
#include <chrono>  // For std::chrono to track time
#include <thread>  // For std::this_thread::sleep_for to implement a delay

#include "wordmatchbingo.h"
#include "get_data.h"
#include "io_handler.h"

// Function definitions

void WordMatchBingo::reset() {
    // Clear the bingo word pool and bingo card
    bingoCard.clear();
    
    // Reset the current bingo word and user guess
    currentBingoWord = {"", ""};
    userGuess = "";

    // Reset the count of words found
    wordsFound = 0;
    remainingTime = totalTime;
}

// Function that selects random words and generates the wordpool of bingo words.
void WordMatchBingo::selectBingoCard() {
    std::vector<std::pair<std::string, std::string>> allWords;

    DataGenerator generator; // Assuming DataGenerator is defined and accessible
    std::string result;

    // Generate a sufficient number of words ensuring no diacritics
    while (allWords.size() < bingoWordPoolCount) {
        auto entry = generator.get_random_entry();
        result = entry.first;

        // Check if the word has diacritics

        result = removeWhitespace(result);        

        // Add the valid entry to allWords
        allWords.push_back(entry);
    }

    // Shuffle the collected valid words
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(allWords.begin(), allWords.end(), g);

    // Assign the selected words to bingoWordPool
    bingoCard.assign(allWords.begin(), allWords.begin() + bingoWordPoolCount);
    bingoCardPool = bingoCard;
}

void WordMatchBingo::setup() {
    selectBingoCard();
}

void WordMatchBingo::updateWordWithStrikethrough(std::string& word) {
    word = "\033[9m" + word + "\033[0m";  // Add strikethrough formatting using ANSI codes
}



size_t WordMatchBingo::getDisplayLength(const std::string& word) {
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

    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<> dis(0, bingoCardPool.size() - 1);
    int index = dis(g);

    auto selectedWord = bingoCardPool[index];
    currentBingoWord = selectedWord;

    std::cout << "\nSelected Word: " << selectedWord.first << std::endl;
    std::cout << "Definition: " << selectedWord.second << std::endl;

    bingoCardPool.erase(bingoCardPool.begin() + index);

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
    std::string userInput;

    while (true) {
        std::cout << "Enter a word (or 'Hint' for a hint): ";
        std::cin >> userInput;

        // Check for valid input or commands
        if (userInput == "Hint") {
            if (lastWasHint) {
                clearLastNLines(1);
            }
            clearLastNLines(1);
            getHint();
            lastWasHint = true;
        } else {
            userGuess = userInput;
            break;
        }
    }
}

bool WordMatchBingo::compareUserInputToBingoCard(const std::string& userInput) {
    // Check if the userInput matches the currentBingoWord.first
    if (toLowerCase(currentBingoWord.first) == toLowerCase(userInput)) {
        // Now check if it's in the bingoCard
        
        auto it = std::find_if(bingoCard.begin(), bingoCard.end(),
            [&userInput](const std::pair<std::string, std::string>& pair) {
                //std::cout << pair.first << std::endl;
                // if(userInput == "BANANA" && pair.first == "banana") {
                //     std::cout << (toLowerCase(pair.first) == toLowerCase(userInput)) << std::endl;
                //     std::cout << (toLowerCase("banana") == toLowerCase("BANANA")) << std::endl;
                // }
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

void WordMatchBingo::getHint() {
    if (!currentBingoWord.first.empty()) {
        std::cout << "Hint: The first letter of the current word is '" 
                  << currentBingoWord.first[0] << "'.\n";
    } else {
        std::cout << "No current bingo word available for a hint.\n";
    }
}

int WordMatchBingo::startGame() {
    clearLastNLines(13);
    setup();

    // Start the timer
    auto startTime = std::chrono::steady_clock::now();
    auto elapsedTime = std::int64_t{ 0 };

    while (!bingoCard.empty() && !bingoCardPool.empty() && bingoWordPoolCount && remainingTime > 0) {
        // Check the elapsed time
        auto currentTime = std::chrono::steady_clock::now();
        elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();

        remainingTime = std::max(std::int64_t{ 0 }, (totalTime - elapsedTime));
        displayCurrentBingoWord();
        displayBingoCard();
        printf("Time left: %lld seconds\n", remainingTime);
        receiveUserInput();
        

        // Print the remaining time

        bool matchResult = compareUserInputToBingoCard(userGuess);
        clearLastNLines(15);
        remainingTime = totalTime - elapsedTime;
    }

    std::cout << "Game over! You found " << wordsFound << " words.\n\n";
    reset();

    return 0;
}