#pragma once

#include <string>
#include <vector>
#include <set>

//using namespace std;

class Hangman {

    const int MAX_STAGE = 7;

    std::string answer;

    const std::vector<std::string> hangman_stages = {
            R"(                             
                   +---+
                   |   |
                       |
                       |
                       |
                       |
                =========
                              )",

            R"(                             
                   +---+
                   |   |
                   O   |
                       |
                       |
                       |
                =========
                             )",

            R"(                             
                   +---+
                   |   |
                   O   |
                   |   |
                       |
                       |
                =========
                             )",

            R"(                             
                   +---+
                   |   |
                   O   |
                  /|   |
                       |
                       |
                =========
                             )",

            R"(                             
                   +---+
                   |   |
                   O   |
                  /|\  |
                       |
                       |
                =========
                             )",

            R"(                             
                   +---+
                   |   |
                   O   |
                  /|\  |
                  /    |
                       |
                =========
                             )",

            R"(                             
                   +---+
                   |   |
                   O   |
                  /|\  |
                  / \  |
                       |
                =========
                             )"
    };

    const std::vector<char> alphabet = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
        'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
        'U', 'V', 'W', 'X', 'Y', 'Z'
    };

    

    public:
        void startGame();

    private:
        void display(int stage);
        std::set<char> seen_letters;
        std::set<char> correct_letters;
        std::vector<std::string> splitStringOnNewline(const std::string& input);
        bool get_letter();
        bool guess_word();
};
        


