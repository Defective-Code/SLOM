#include "Hangman.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <locale>
#include <fstream>

std::string filepath = TEST_RESOURCES_FILE_PATH + std::string("output.txt");

// Utility function to trim leading and trailing whitespace
std::string trim(const std::string& s) {
    auto start = s.find_first_not_of(" \t\n\r\f\v");
    auto end = s.find_last_not_of(" \t\n\r\f\v");
    return (start == std::string::npos || end == std::string::npos) ? "" : s.substr(start, end - start + 1);
}

void printCharValues(const std::string& s) {
    for (char c : s) {
        std::cout << "[" << static_cast<int>(c) << "]";
    }
    std::cout << std::endl;
}

/*
// Function to write a string to a file
void writeStringToFile(const std::string& filename, const std::string& content) {
    // Create an output file stream object
    std::ofstream outFile(filename);

    // Check if the file was opened successfully
    if (!outFile) {
        std::cerr << "Error: Could not open the file " << filename << std::endl;
        return;
    }

    // Write the string content to the file
    outFile << content;

    // Check if writing succeeded
    if (!outFile.good()) {
        std::cerr << "Error: Failed to write to the file " << filename << std::endl;
    }

    // Close the file
    outFile.close();

    // Create a text string, which is used to output the text file
    std::string myText;

    // Read from the text file
    std::ifstream MyReadFile(filename);

    // Use a while loop together with the getline() function to read the file line by line
    while (getline(MyReadFile, myText)) {
        // Output the text from the file
        std::cout << myText;
    }

    // Close the file
    MyReadFile.close();
}
*/

// Function to read the entire content of a file into a string
std::string readFileToString(const std::string& filename) {
    std::ifstream file(filename);
    std::stringstream buffer;

    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file " << filename << std::endl;
        return "";
    }

    buffer << file.rdbuf();
    file.close();

    return buffer.str();
}


// Function to compare file content with a string
bool compareFileContentToString(const std::string& filename, const std::string& contentToCompare) {
    std::string fileContent = readFileToString(filename);

    if (fileContent.empty()) {
        std::cerr << "Error: File is empty or could not be read." << std::endl;
        return false;
    }

    return fileContent == contentToCompare;
}


// Definition of HangmanTest class
class HangmanTest {
public:
    static void runTests();

private:
    static void testGuessWord();
    static void testGetLetter();
    static void testDisplay();

    // Helper functions for the tests
    static void setupHangman(Hangman& hangman, const std::string& answer);
};

// Implementation of HangmanTest methods

void HangmanTest::setupHangman(Hangman& hangman, const std::string& answer) {
    hangman.answer = answer;
    hangman.correct_letters.clear();
    hangman.seen_letters.clear();
}


// Test method for get_letter()
void HangmanTest::testGetLetter() {
    Hangman hangman;

    // Test correct letter
    {
        setupHangman(hangman, "hangman");
        std::istringstream input("a"); // Simulate user input
        std::cin.rdbuf(input.rdbuf()); // Redirect std::cin to the input stream

        bool result = hangman.get_letter();
        assert(result == true);
        assert(hangman.correct_letters.count('A') == 1);
        assert(hangman.seen_letters.empty());
        std::cout << "testGetLetter (correct letter) passed." << std::endl;
    }

    // Test incorrect letter
    {
        setupHangman(hangman, "hangman");
        std::istringstream input("x"); // Simulate user input
        std::cin.rdbuf(input.rdbuf()); // Redirect std::cin to the input stream

        bool result = hangman.get_letter();
        assert(result == false);
        assert(hangman.correct_letters.empty());
        assert(hangman.seen_letters.count('X') == 1);
        std::cout << "testGetLetter (incorrect letter) passed." << std::endl;
    }

    // Reset cin
    std::cin.rdbuf(nullptr);
}


// Test method for guess_word()
void HangmanTest::testGuessWord() {
    Hangman hangman;

    // Test correct guess
    {
        setupHangman(hangman, "hangman");
        std::istringstream input("hangman"); // Simulate user input
        std::cin.rdbuf(input.rdbuf()); // Redirect std::cin to the input stream

        bool result = hangman.guess_word();
        assert(result == true);
        std::cout << "testGuessWord (correct guess) passed." << std::endl;
    }

    // Test incorrect guess
    {
        setupHangman(hangman, "hangman");
        std::istringstream input("wrong"); // Simulate user input
        std::cin.rdbuf(input.rdbuf()); // Redirect std::cin to the input stream

        bool result = hangman.guess_word();
        assert(result == false);
        std::cout << "testGuessWord (incorrect guess) passed." << std::endl;
    }

    // Reset cin
    std::cin.rdbuf(nullptr);
}

void HangmanTest::testDisplay() {

    Hangman hangman;
    setupHangman(hangman, "hangman");
    // This would be more complex since `display` involves I/O operations.
    // Here we'll assume it's tested manually or using other methods.
    // This function can be enhanced to capture and compare the console output.
    //std::cout << "testDisplay needs to be tested manually or by capturing output." << std::endl;
    /*
    std::string expected_output =
        R"(

       +===================================================+
       |   _   _                                           |
       |  | | | | __ _ _ __   __ _ _ __ ___   __ _ _ __    |
       |  | |_| |/ _` | '_ \ / _` | '_ ` _ \ / _` | '_ \   |
       |  |  _  | (_| | | | | (_| | | | | | | (_| | | | |  |
       |  |_| |_|\__,_|_| |_|\__, |_| |_| |_|\__,_|_| |_|  |
       |                     |___/                         |
       +===================================================+

    
                                      Used Letters
                                      +---------+
                   +---+              |         |
                   |   |              |         |
                       |              |         |
                       |              |         |
                       |              |         |
                       |              |         |
                =========             |         |
                                      +---------+

          Guess: _______


Press the corresponding key in the bracket to select that option.
1) Guess a letter
2) Guess the word

Press q to quit...

)";
*/

    std::string actual_output = hangman.display(0);

    //std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
    //std::cout << expected_output << std::endl;
    //std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
    //std::cout << actual_output << std::endl;
    //std::cout << "-----------------------------------------------------------------------------------------" << std::endl;

    // Output ASCII values for debugging
    //std::cout << "Expected Output ASCII Values:\n";
    //printCharValues(expected_output);
    //std::cout << "Actual Output ASCII Values:\n";
    //printCharValues(actual_output);

    //writeStringToFile("output.txt", actual_output);

    assert(compareFileContentToString(filepath, actual_output));
}

void HangmanTest::runTests() {
    testGuessWord();
    testGetLetter();
    testDisplay(); //TODO: Curretnly the expected output is missing some features
}

// To execute the tests, you can call HangmanTest::runTests() from your main function or another driver.
int main() {
    HangmanTest::runTests();
    return 0;
}