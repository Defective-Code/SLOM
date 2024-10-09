#include "hangman.h"
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
    static void testGuessLetter();
    static void testGenerate();
    static void testGiveHint();
    static void testSetup();
    static void testReset();
    static void testMenu();
    static void testCheckGameEnd();

    // Helper functions for the tests
    static void setupHangman(Hangman& hangman, const std::string& answer);
};

// Implementation of HangmanTest methods

void HangmanTest::setupHangman(Hangman& hangman, const std::string& answer) {
    hangman.answer = answer;
    hangman.current_stage = 0;
    hangman.correct_letters.clear();
    hangman.seen_letters.clear();
}


// Test method for generate()
void HangmanTest::testGenerate() {
    Hangman hangman;

    // Setup for the test with a word, guessed letters, and current stage
    {
        setupHangman(hangman, "hangman");  // Initialize the game with the word "hangman"
        hangman.correct_letters = {'H', 'A', 'N'};  // Letters correctly guessed
        //hangman.seen_letters = {'H', 'A', 'X', 'Z'};  // Letters already guessed
        hangman.seen_letters.insert('h');
        hangman.seen_letters.insert('a');
        hangman.seen_letters.insert('x');
        hangman.seen_letters.insert('z');
        hangman.current_stage = 2;  // Current stage of the hangman (assuming 3 means partially drawn)

        // for (char ch : hangman.seen_letters) {
        //     std::cout << ch << " "; // Print each character followed by a space
        // }
        
        
        std::string result = hangman.generate();

        //std::cout << result << std::endl;
        
        // Check if the banner is present
        assert(result.find("+===================================================+") != std::string::npos);
        
        // Check if the hangman stage is rendered correctly
        std::vector<std::string> expectedStage = splitStringOnNewline(hangman.hangman_stages[2]);  // The 3rd stage of hangman
        for (const auto& line : expectedStage) {
            assert(result.find(line) != std::string::npos);  // Ensure each line of the stage appears in the result
        }
        
        // Check if the "Used Letters" section is displayed properly
        assert(result.find("Used Letters") != std::string::npos);
        assert(result.find("a ") != std::string::npos);  // Correctly guessed letters 'A'
        assert(result.find("h ") != std::string::npos);  // Correctly guessed letters 'H'
        assert(result.find("x") != std::string::npos);  // Incorrectly guessed letters 'X', 'Z'
        assert(result.find("z") != std::string::npos);  // Incorrectly guessed letters 'X', 'Z'
        
        // Check if the correct underscore word is shown
        //assert(result.find("Guess: HAN__AN") != std::string::npos);  // Correct guesses and blanks !!! TOFIX
        
        // Check if user options are present
        assert(result.find("Guess a letter") != std::string::npos);
        assert(result.find("Guess the word") != std::string::npos);
        assert(result.find("Press q to quit") != std::string::npos);
        
        // Output the test result
        std::cout << "testGenerate passed." << std::endl;
    }
}


// Test method for get_letter()
void HangmanTest::testGuessLetter() {
    Hangman hangman;

    // Test correct letter
    {
        setupHangman(hangman, "hangman");

        bool result = hangman.guessLetter('a');
        assert(result == true);
        assert(hangman.correct_letters.count('a') == 1);
        assert(hangman.seen_letters.empty());
        std::cout << "testGetLetter (correct letter) passed." << std::endl;
    }

    // Test incorrect letter
    {
        setupHangman(hangman, "hangman");
        // std::istringstream input("x"); // Simulate user input
        // std::cin.rdbuf(input.rdbuf()); // Redirect std::cin to the input stream

        bool result = hangman.guessLetter('x');
        assert(result == false);
        assert(hangman.correct_letters.empty());
        assert(hangman.seen_letters.count('x') == 1);
        std::cout << "testGetLetter (incorrect letter) passed." << std::endl;
    }

    // Reset cin
    //std::cin.rdbuf(nullptr);
}

// Test method for guessWord()
void HangmanTest::testGuessWord() {
    Hangman hangman;

    // Setup with a word
    hangman.setup();
    hangman.answer = "hangman";

    // Test case: Correct word guess (exact match)
    {
        std::string guess = "hangman";
        bool result = hangman.guessWord(guess);
        assert(result == true);  // Should return true for a correct guess
        std::cout << "testGuessWord (correct guess) passed." << std::endl;
    }

    // Test case: Incorrect word guess
    {
        std::string guess = "wrongword";
        bool result = hangman.guessWord(guess);
        assert(result == false);  // Should return false for an incorrect guess
        std::cout << "testGuessWord (incorrect guess) passed." << std::endl;
    }

    // Test case: Case-insensitive correct word guess
    {
        std::string guess = "HaNgMaN";
        bool result = hangman.guessWord(toLowerCase(guess));  // Convert input to lowercase
        assert(result == true);  // Should return true for a correct guess, even if in different case
        std::cout << "testGuessWord (case-insensitive guess) passed." << std::endl;
    }

    // Test case: Word with extra spaces (should fail)
    {
        std::string guess = "hangman ";
        bool result = hangman.guessWord(toLowerCase(guess));  // Remove whitespace if necessary
        assert(result == false);  // Should return false due to extra space
        std::cout << "testGuessWord (word with extra spaces) passed." << std::endl;
    }
}

// Test method for setup()
void HangmanTest::testSetup() {
    Hangman hangman;

    // Call the setup method
    hangman.setup();

    // Ensure the answer is not empty (not null)
    assert(!hangman.answer.empty() && "Answer should not be null");

    // Ensure the answer is all lowercase
    for (char c : hangman.answer) {
        assert(islower(c) && "Answer should be all lowercase");
    }

    // Ensure the answer contains no spaces
    assert(hangman.answer.find(' ') == std::string::npos && "Answer should not contain any spaces");

    // Output the test result
    std::cout << "testSetup passed." << std::endl;
}

// Test method for reset()
void HangmanTest::testReset() {
    Hangman hangman;

    // Simulate some game progress
    hangman.correct_letters.insert('a');
    hangman.seen_letters.insert('b');
    hangman.current_stage = 5;

    // Call the reset method
    hangman.reset();

    // Check that correct_letters is cleared
    assert(hangman.correct_letters.empty() && "correct_letters should be empty after reset");

    // Check that seen_letters is cleared
    assert(hangman.seen_letters.empty() && "seen_letters should be empty after reset");

    // Check that current_stage is reset to 0
    assert(hangman.current_stage == 0 && "current_stage should be reset to 0 after reset");

    // Output the test result
    std::cout << "testReset passed." << std::endl;
}


// Test method for menu()
void HangmanTest::testMenu() {
    Hangman hangman;

    // Simulate some game setup
    hangman.setup();
    hangman.current_stage = 0;  // Ensure starting stage is 0

    // Test case: Guess a letter correctly
    {
        setupHangman(hangman, "hangman");
        std::istringstream input("1a");  // Simulate selecting option 1 and guessing 'a'
        std::cin.rdbuf(input.rdbuf());   // Redirect std::cin to the input stream

        bool result = hangman.menu();
        assert(result == false);         // Should not quit
        assert(hangman.correct_letters.count('a') == 1);  // Letter 'a' should be guessed correctly
        assert(hangman.current_stage == 0);               // No incorrect guess, stage should remain 0
        std::cout << "testMenu (guess letter correct) passed." << std::endl;
    }

    // Test case: Guess a letter incorrectly
    {
        setupHangman(hangman, "hangman");
        std::istringstream input("1z");  // Simulate selecting option 1 and guessing 'z' (incorrect)
        std::cin.rdbuf(input.rdbuf());   // Redirect std::cin to the input stream

        bool result = hangman.menu();
        assert(result == false);         // Should not quit
        assert(hangman.correct_letters.count('z') == 0);  // 'z' should not be in the correct letters
        assert(hangman.current_stage == 1);               // Stage should increment due to incorrect guess
        std::cout << "testMenu (guess letter incorrect) passed." << std::endl;
    }

    // Test case: Guess the word correctly
    {
        setupHangman(hangman, "hangman");
        std::istringstream input("2hangman");  // Simulate selecting option 2 and guessing the word
        std::cin.rdbuf(input.rdbuf());         // Redirect std::cin to the input stream

        bool result = hangman.menu();
        assert(result == false);               // Should not quit
        assert(hangman.current_stage == 0);    // No incorrect guess, stage should remain 0
        std::cout << "testMenu (guess word correct) passed." << std::endl;
    }

    // Test case: Guess the word incorrectly
    {
        setupHangman(hangman, "hangman");
        std::istringstream input("2incorrect");  // Simulate selecting option 2 and guessing the wrong word
        std::cin.rdbuf(input.rdbuf());           // Redirect std::cin to the input stream

        bool result = hangman.menu();
        assert(result == false);                 // Should not quit
        assert(hangman.current_stage == 1);      // Stage should increment due to incorrect word guess
        std::cout << "testMenu (guess word incorrect) passed." << std::endl;
    }

    // Test case: Quit the game
    {
        std::istringstream input("q");  // Simulate selecting option 'q' to quit
        std::cin.rdbuf(input.rdbuf());  // Redirect std::cin to the input stream

        bool result = hangman.menu();
        assert(result == true);  // Should quit the game
        std::cout << "testMenu (quit) passed." << std::endl;
    }

    // Reset cin
    std::cin.rdbuf(nullptr);
}


// Test method for checkGameEnd()
void HangmanTest::testCheckGameEnd() {
    Hangman hangman;

    // Setup with a word
    hangman.setup();
    hangman.answer = "hangman";

    // Test case: Game not ended (not all letters guessed)
    {
        setupHangman(hangman, "hangman");
        hangman.correct_letters = {'h', 'a', 'n'}; // Only some letters guessed

        bool result = hangman.checkGameEnd();
        assert(result == false); // Game should not end, as all letters aren't guessed yet
        std::cout << "testCheckGameEnd (game not ended) passed." << std::endl;
    }

    // Test case: Game ended (all letters guessed)
    {
        setupHangman(hangman, "hangman");
        hangman.correct_letters = {'h', 'a', 'n', 'g', 'm'}; // All letters guessed

        bool result = hangman.checkGameEnd();
        assert(result == true); // Game should end, all letters have been guessed
        std::cout << "testCheckGameEnd (game ended) passed." << std::endl;
    }

    // Test case: Game not ended with incorrect guesses (extra incorrect letters present)
    {
        setupHangman(hangman, "hangman");
        hangman.correct_letters = {'h', 'a', 'n', 'x', 'y'}; // Some correct, but extra incorrect

        bool result = hangman.checkGameEnd();
        assert(result == false); // Game should not end, since some letters are still missing
        std::cout << "testCheckGameEnd (incorrect guesses) passed." << std::endl;
    }
}



void HangmanTest::runTests() {
    testGuessWord();
    testGuessLetter();
    testGenerate();
    testSetup();
    //testGiveHint() TODO
    testSetup();
    testReset();
    testMenu();
    testCheckGameEnd();
}

// To execute the tests, you can call HangmanTest::runTests() from your main function or another driver.
int main() {
    HangmanTest::runTests();
    return 0;
}