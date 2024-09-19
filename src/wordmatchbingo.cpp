//testing...
#include <iostream>
#include <cctype>
#include <vector>
#include <string>
#include <map>
#include "wordmatchbingo.h"
#include "get_data.h"

const int bingoWordPoolCount = 15;
std::vector<std::string> bingoWordPool;

const int bingoWordCount = 5;
std::string bingoCard[bingoWordCount];

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

void WordMatchBingo::selectBingoWordPool(){
    printf("Welcome to Word Match BINGOOOO! \n");
    DataGenerator generator;
    std::string result = "";
    for(int i = 0; i < bingoWordPoolCount; i++){
        do {
            auto entry = generator.get_random_entry();
            result = entry.first;
        } while (hasDiacritics(result));
        bingoWordPool.push_back(result);
    }
    // Print the contents of bingoWordPool
    std::cout << "Bingo Word Pool: \n";
    for (const auto& word : bingoWordPool) {
        std::cout << word << std::endl;
    }
}

void WordMatchBingo::selectBingoCard(){
    
}

void WordMatchBingo::clearLastNLines(int n)
{
	for (int i = 0; i < n; ++i)
	{
		//Move cursor up one line and clear the line
		std::cout << "\033[A\033[2K";
	}
}

void WordMatchBingo::startGame(){
    clearLastNLines(11); 
	selectBingoWordPool();
    printf("TESTTTTTTT");

}


