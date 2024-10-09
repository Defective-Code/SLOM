#include <iostream>
#include <sstream>
#include <cassert>
#include <regex>
#include "wordle.h"

class WordleTest {
public:
    
    // static auto changeCout() {
    //     std::ostringstream captureStream;
    //     auto originalBuffer = std::cout.rdbuf(captureStream.rdbuf());
    //     return originalBuffer;
    // }

    // static void returnCout(auto originalBuffer) {
    //     std::cout.rdbuf(originalBuffer);
    // }


    static void reset_t() {
        // Initialize a Wordle object
        Wordle wordle;

        // Simulate some state changes
        wordle.wordleWord = "HELLO";         // Set a custom word
        wordle.displayWordleWord = "H _ L _"; // Set a partially guessed word
        wordle.attemptsCount = 3;            // Simulate 3 attempts made
        wordle.wordleComplete = true;        // Set the game to completed
        wordle.attempts[0] = "H E L _ _";    // Set an attempt
        wordle.charCount['H'] = 1;           // Set a character count map entry

        // Call the reset method
        wordle.reset();

        // Verify that wordleWord is set to the default
        assert(wordle.wordleWord == "Test" && "wordleWord should be reset to 'Test'");

        // Verify that displayWordleWord is cleared
        assert(wordle.displayWordleWord.empty() && "displayWordleWord should be cleared");

        // Verify that attemptsCount is reset to 0
        assert(wordle.attemptsCount == 0 && "attemptsCount should be reset to 0");

        // Verify that wordleComplete is reset to false
        assert(wordle.wordleComplete == false && "wordleComplete should be reset to false");

        // Verify that the attempts array is reset correctly
        for (int i = 0; i < Wordle::MAX_ATTEMPTS; ++i) {
            assert(wordle.attempts[i] == std::string(wordle.wordleWord.length() * 2, '_') &&
                "Attempts array should be reset");
        }

        // Verify that the character count map is cleared
        assert(wordle.charCount.empty() && "charCount map should be cleared");

        std::cout << "Test passed: Wordle reset method works as expected." << std::endl;
    }


    static void generate_t() {
        Wordle wordle;

        // Simulate initial state
        wordle.wordleWord = "test"; // The word to guess
        wordle.attempts[0] = "t__t"; // First guess with some correct letters
        wordle.attempts[1] = "_e__"; // Second guess with a different set of correct letters
        wordle.attemptsCount = 2; // Two attempts have been made

        // Call the generate method
        std::string generatedOutput = wordle.generate();

        // Check if the generated output contains the expected ASCII art header
        assert(generatedOutput.find("+======================================+") != std::string::npos && "ASCII art header not found");
        
        // Check if it includes the two attempts
        assert(generatedOutput.find("t__t") != std::string::npos && "First attempt not found");
        assert(generatedOutput.find("_e__") != std::string::npos && "Second attempt not found");

        // Check if the instructions to guess or quit are present
        assert(generatedOutput.find("Press 1) to guess a word") != std::string::npos && "Guess option not found");
        assert(generatedOutput.find("Press q to quit") != std::string::npos && "Quit option not found");

        // Print success message if all assertions passed
        std::cout << "testGenerate passed." << std::endl;
    }

    static void display_t() {
        Wordle wordle;

        // Simulate initial state
        wordle.wordleWord = "test"; // The word to guess
        wordle.attempts[0] = "t__t"; // First guess with some correct letters
        wordle.attempts[1] = "_e__"; // Second guess with a different set of correct letters
        wordle.attemptsCount = 2; // Two attempts have been made

        // Redirect std::cout to a stringstream to capture the output
        std::ostringstream outputCapture;
        std::streambuf* originalCout = std::cout.rdbuf(); // Save original buffer
        std::cout.rdbuf(outputCapture.rdbuf()); // Redirect std::cout to outputCapture

        // Call the display function
        wordle.display();

        // Restore std::cout buffer to original
        std::cout.rdbuf(originalCout);

        // Get the captured output as a string
        std::string capturedOutput = outputCapture.str();

        // Check if the generated output contains the expected ASCII art header
        assert(capturedOutput.find("+======================================+") != std::string::npos && "ASCII art header not found");
        
        // Check if it includes the two attempts
        assert(capturedOutput.find("t__t") != std::string::npos && "First attempt not found");
        assert(capturedOutput.find("_e__") != std::string::npos && "Second attempt not found");

        // Check if the instructions to guess or quit are present
        assert(capturedOutput.find("Press 1) to guess a word") != std::string::npos && "Guess option not found");
        assert(capturedOutput.find("Press q to quit") != std::string::npos && "Quit option not found");

        // Print success message if all assertions passed
        std::cout << "testDisplay passed." << std::endl;
    }

    static void menu_t() {
        Wordle wordle;

        std::ostringstream captureStream;
        auto originalBuffer = std::cout.rdbuf(captureStream.rdbuf());
        
        // Test case: Simulating user input to guess a word (option '1')
        {
            // Set up initial game state
            wordle.wordleWord = "test";
            wordle.attemptsCount = 0;

            // Simulate the input for option '1' and a word guess
            std::istringstream inputSimulator("1\nbest\n");
            auto cin_rdbuf = std::cin.rdbuf(inputSimulator.rdbuf()); // Redirect std::cin to simulate input

            

            // Call the menu function
            bool continueGame = wordle.menu();

            // Verify that the game continues after guessing
            assert(continueGame == true && "The game should continue after guessing a word.");

            // Check if a word guess is processed (by checking attemptsCount)
            assert(wordle.attemptsCount == 1 && "Attempts count should increase after a valid guess.");

            std::cin.rdbuf(cin_rdbuf);
            
        }
        
        // Test case: Simulating user input to quit the game (option 'q')
        {
            // Simulate the input for option 'q'
            std::istringstream inputSimulator("q\n");
            auto cin_rdbuf = std::cin.rdbuf(inputSimulator.rdbuf()); // Redirect std::cin to simulate input

            std::ostringstream captureStream;
            auto originalBuffer = std::cout.rdbuf(captureStream.rdbuf());

            // Call the menu function
            bool continueGame = wordle.menu();

            // Verify that the game ends after selecting 'q'
            assert(continueGame == false && "The game should end when 'q' is selected.");
            std::cin.rdbuf(cin_rdbuf);
            std::cout.rdbuf(originalBuffer);
        }

        // Test case: Simulating invalid input
        {
            // Simulate the input for an invalid option
            std::istringstream inputSimulator("x\n");
            auto cin_rdbuf = std::cin.rdbuf(inputSimulator.rdbuf()); // Redirect std::cin to simulate input

            std::ostringstream captureStream;
            auto originalBuffer = std::cout.rdbuf(captureStream.rdbuf());

            // Call the menu function
            bool continueGame = wordle.menu();

            // Verify that the game continues after an invalid input
            assert(continueGame == true && "The game should continue after an invalid option.");

            // Optionally check if the message "Please select a valid option" is printed
            std::cin.rdbuf(cin_rdbuf);
            std::cout.rdbuf(originalBuffer);
        } 

        std::cout.rdbuf(originalBuffer);

        // Print success message if all assertions passed
        std::cout << "testMenu passed." << std::endl;
    }

    static void recieveUserInput_t() {
        Wordle wordle;

        std::ostringstream captureStream;
        auto originalBuffer = std::cout.rdbuf(captureStream.rdbuf());

        // Set the expected word length
        wordle.wordleWord = "test"; // The word to guess
        wordle.wordleComplete = false; // The game is not complete

        // Simulate valid input
        {
            // Redirect std::cin to simulate input
            std::istringstream inputCapture("test\n");
            std::streambuf* originalCin = std::cin.rdbuf();  // Save original input buffer
            std::cin.rdbuf(inputCapture.rdbuf());  // Redirect std::cin to simulate valid input

            // Call receiveUserInput to test valid input
            std::string input = wordle.receiveUserInput();

            // Restore original std::cin buffer
            std::cin.rdbuf(originalCin);

            // Check if the returned input is correct
            assert(input == "test" && "The input should be 'test' for valid input.");
        }

        // Simulate invalid input
        {
            // Redirect std::cin to simulate invalid input followed by valid input
            std::istringstream inputCapture("wrong\nwrong\ntext\n");
            std::streambuf* originalCin = std::cin.rdbuf();  // Save original input buffer
            std::cin.rdbuf(inputCapture.rdbuf());  // Redirect std::cin to simulate invalid input

            // Call receiveUserInput to test handling of invalid input
            std::string input = wordle.receiveUserInput();

            // Restore original std::cin buffer
            std::cin.rdbuf(originalCin);

            // Check if the returned input is correct
            assert(input == "text" && "The input should be 'text' for valid input after two invalid attempts.");
        }

        std::cout.rdbuf(originalBuffer);

        // Print success message if all assertions passed
        std::cout << "testReceiveUserInput passed." << std::endl;
    }

    static void getNextGameState_t() {
        Wordle wordle;

        // Setup the game state with a known word
        wordle.wordleWord = "test";  // Assume this is the word to guess
        wordle.attemptsCount = 0;     // Reset attempts count
        wordle.wordleComplete = false; // Reset game completion status
        
        // Test correct guess
        std::string userGuess = "test";
        wordle.getNextGameState(userGuess);
        assert(wordle.wordleComplete == true && "The game should be complete for a correct guess.");
        assert(wordle.attemptsCount == 1 && "There should be one attempt recorded.");
        assert(wordle.attempts[0] == "\033[38;5;10mt\033[0m \033[38;5;10me\033[0m \033[38;5;10ms\033[0m \033[38;5;10mt\033[0m " &&
            "Display should show all characters in green for a correct guess.");

        // Reset for next test
        wordle.wordleWord = "test";  // Assume this is the word to guess
        wordle.attemptsCount = 0;     // Reset attempts count
        wordle.wordleComplete = false; // Reset game completion status

        // Test incorrect guess
        userGuess = "tens"; // Incorrect guess
        wordle.getNextGameState(userGuess);
        assert(wordle.wordleComplete == false && "The game should not be complete for an incorrect guess.");
        assert(wordle.attemptsCount == 1 && "There should be one attempt recorded for incorrect guess.");

        std::string expectedOutput = "\033[38;5;10mt\033[0m \033[38;5;10me\033[0m \033[38;5;250mn\033[0m \033[38;5;226ms\033[0m ";
        //std::cout << wordle.attempts[0] << std::endl;
        //std::cout << expectedOutput << std::endl;

        // Check the display for 't' (correct position), 'e' (wrong position), 'n' (not in word), 's' (not in word)
        assert(wordle.attempts[0] == expectedOutput &&
            "Display should show 't' in green, 'e' in yellow, and 'n' and 's' in grey.");

        // Reset for next test
        wordle.wordleWord = "test";  // Assume this is the word to guess
        wordle.attemptsCount = 0;     // Reset attempts count
        wordle.wordleComplete = false; // Reset game completion status

        // Test partial match
        userGuess = "tart"; // 't' is correct, 'a' is not in the word, 'r' is not in the word, 't' in the correct position
        wordle.getNextGameState(userGuess);
        assert(wordle.wordleComplete == false && "The game should not be complete for a partial match.");
        assert(wordle.attemptsCount == 1 && "There should be one attempt recorded for partial match.");
        
        // Check the display: 't' (correct), 'a' (not in word), 'r' (not in word), 't' (correct)
        assert(wordle.attempts[0] == "\033[38;5;10mt\033[0m \033[38;5;250ma\033[0m \033[38;5;250mr\033[0m \033[38;5;10mt\033[0m " &&
            "Display should show 't' in green, 'a' and 'r' in grey, and second 't' in green.");
            

        // Print success message if all assertions passed
        std::cout << "testWordleGetNextGameState passed." << std::endl;
    }


    static void setup_t() {
        Wordle wordle;

        std::ostringstream captureStream;
        auto originalBuffer = std::cout.rdbuf(captureStream.rdbuf());
        
        // Simulate setting the random word to a known value.
        // You can modify the DataGenerator to return a predictable value for testing.
        wordle.setup(); // Call the setup method to initialize the game state.

        // Check that wordleWord is correctly set
        assert(wordle.wordleWord.length() == wordle.WORD_LENGTH && "The word length should match WORD_LENGTH.");
        
        // Check that displayWordleWord is initialized to the correct format
        std::string expectedDisplay;
        for (size_t i = 0; i < wordle.wordleWord.length(); ++i) {
            expectedDisplay += "_ "; // Each character should be displayed as an underscore
        }
        assert(wordle.displayWordleWord == expectedDisplay && "The displayWordleWord should be initialized with underscores.");
        
        // Check that the attempts array is correctly initialized
        for (size_t i = 0; i < Wordle::MAX_ATTEMPTS; ++i) {
            assert(wordle.attempts[i] == expectedDisplay && "Each attempt should be initialized to the display format.");
        }
        std::cout.rdbuf(originalBuffer);

        // Print success message if all assertions passed
        std::cout << "testWordleSetup passed." << std::endl;
    }
};

int main() {
    WordleTest::reset_t();
    WordleTest::generate_t();
    WordleTest::menu_t();
    WordleTest::recieveUserInput_t();
    WordleTest::getNextGameState_t();
    WordleTest::setup_t();
    WordleTest::display_t();
    return 0;
}
