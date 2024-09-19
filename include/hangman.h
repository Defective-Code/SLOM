#pragma once

#include <string>
#include <vector>
#include <set>

//using namespace std;

class Hangman {

    const int MAX_STAGE = 7;

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

    std::set<char> seen_letters;

    public:
        void startGame();

    private:
        void display(int stage);

        std::vector<std::string> splitStringOnNewline(const std::string& input);

};
        


