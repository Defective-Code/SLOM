
#include <stdio.h>
#include <string>
#include <cassert>
#include <type_traits>
#include <typeinfo>
#include <iostream>
#include <algorithm>
#include <sstream>
#include "wordfind.h"

// Helper function to redirect std::cout and std::cin
class StreamRedirector {
public:
    StreamRedirector(std::streambuf* new_cin, std::streambuf* new_cout)
        : old_cin(std::cin.rdbuf(new_cin)), old_cout(std::cout.rdbuf(new_cout)) {}

    ~StreamRedirector() {
        std::cin.rdbuf(old_cin);
        std::cout.rdbuf(old_cout);
    }

private:
    std::streambuf* old_cin;
    std::streambuf* old_cout;
};

class WordfindTest {
public:
    static void initializeGrid_t() {
        Wordfind wf;
        std::vector<std::vector<char>> test_grid(Wordfind::GRID_SIZE, std::vector<char>(Wordfind::GRID_SIZE, ' ')); // the grid

        wf.initializeGrid();

        for (int i = 0; i < Wordfind::GRID_SIZE; ++i) {
            for (int j = 0; j < Wordfind::GRID_SIZE; ++j) {
                // Compile-time check that each element in the grid is of type 'char'
                assert(typeid(wf.grid[i][j]) == typeid(char));

                // Runtime assertion that the grid element is not an empty space or null
                assert(wf.grid[i][j] != ' ' && wf.grid[i][j] != '\0' && "Grid position contains an invalid character.");

                assert(wf.grid[i][j] >= 'A' && wf.grid[i][j] <= 'Z');  // Example: ensure it's an uppercase letter
            }
        }
    }
    static void placeWord_t() {
        Wordfind wordfind = Wordfind();

        // Initialize the grid
        std::vector<std::vector<char>> grid(Wordfind::GRID_SIZE, std::vector<char>(Wordfind::GRID_SIZE, ' '));

        // PositionSet to keep track of occupied positions
        Wordfind::PositionSet occupiedPositions;

        // Test case 1: Place word horizontally in an empty grid
        std::string word1 = "TEST";
        bool result1 = wordfind.placeWord(word1, 2, 2, 0, 1, occupiedPositions);
        assert(result1 == true);  // Word should be placed successfully
        assert(grid[2][2] == 'T' && grid[2][3] == 'E' && grid[2][4] == 'S' && grid[2][5] == 'T');

        //wordfind.printGrid(grid);
        //printPositionSet(occupiedPositions);

        // Test case 2: Try placing the same word in the same position (should return True, as technically the new TEST overwwrites the old one due to overlap)
        bool result2 = wordfind.placeWord(word1, 2, 2, 0, 1, occupiedPositions);
        assert(result2 == true);  // Word should not be placed again

        // Test case 3: Place a word vertically that overlaps correctly with an existing word
        std::string word2 = "EXAM";
        bool result3 = wordfind.placeWord(word2, 2, 3, 1, 0, occupiedPositions);
        assert(result3 == true);  // Word should be placed successfully
        assert(grid[2][3] == 'E' && grid[3][3] == 'X' && grid[4][3] == 'A' && grid[5][3] == 'M');

        // Test case 4: Attempt to place a word that goes out of bounds
        std::string word3 = "OUTOFBOUNDS";
        bool result4 = wordfind.placeWord(word3, 9, 9, 0, 1, occupiedPositions);
        assert(result4 == false);  // Word should not be placed

        
        
        // Test case 5: Place a word diagonally
        std::string word4 = "DIAGONAL";
        bool result5 = wordfind.placeWord(word4, 0, 0, 1, 1, occupiedPositions);
        assert(result5 == false);  // Word should fail as it overlaps with the "TEST" which is inserted at 2, 2
        //assert(grid[0][0] == 'D' && grid[1][1] == 'I' && grid[2][2] == 'A' && grid[3][3] == 'G' && grid[4][4] == 'O');

        std::string word5 = "GUAM";
        bool result6 = wordfind.placeWord(word5, 2, 0, 1, 1, occupiedPositions);
        assert(result6 == true); //Word should succeed now, as the M matches with the M in "EXAM", and doesn't overlap with anything else
        assert(grid[2][0] == 'G' && grid[3][1] == 'U' && grid[4][2] == 'A' && grid[5][3] == 'M');

        //wordfind.printGrid(grid);
        //printPositionSet(occupiedPositions);

        std::cout << "All test cases passed for placeWord()" << std::endl;
    }

    static void addWordsToGrid_t() {
        Wordfind wordfind;

        // Initialize the grid
        std::vector<std::vector<char>> grid(Wordfind::GRID_SIZE, std::vector<char>(Wordfind::GRID_SIZE, '.'));

        // List of words to add
        std::vector<std::string> words = { "HELLO", "WORLD", "TEST", "GRID" };
        wordfind.words = words;

        // Call the method to add words to the grid
        wordfind.addWordsToGrid();

        // Output the grid for manual inspection
        /*
        std::cout << "Grid after adding words:" << std::endl;
        for (const auto& row : grid) {
            for (const auto& cell : row) {
                std::cout << cell << ' ';
            }
            std::cout << std::endl;
        } 
        */

        // Basic validation checks
        for (const auto& word : words) {
            bool found = false;
            for (int r = 0; r < Wordfind::GRID_SIZE; ++r) {
                for (int c = 0; c < Wordfind::GRID_SIZE; ++c) {
                    if (searchWordInGrid(grid, word, r, c)) {
                        found = true;
                        break;
                    }
                }
                if (found) break;
            }
            assert(found && "Word not found in the grid");
        }

        std::cout << "All words were placed successfully." << std::endl;
    }

    // Test method for Wordfind::guessWord
    static void guessWord_t() {
        Wordfind wordfind;

        // Sample words to add to Wordfind
        wordfind.words = { "HELLO", "WORLD", "TEST", "GRID" };

        // Test with a correct guess
        std::string correctGuess = "HELLO";
        wordfind.guessWord(correctGuess);

        // Check if the word was added to wordsFound
        assert(std::find(wordfind.wordsFound.begin(), wordfind.wordsFound.end(), correctGuess) != wordfind.wordsFound.end() &&
            "Correct guess was not added to wordsFound!");

        // Test with an incorrect guess
        std::string incorrectGuess = "INVALID";

        // Use a mock function to prevent actual console output during testing
        //auto mockClearLastNLines = [](int n) {
            // Placeholder for clearing lines; in real implementation, it would modify console output
        //    };
        //wordfind.clearLastNLines = mockClearLastNLines;

        // Capture the output for the incorrect guess
        std::ostringstream oss;
        std::streambuf* originalCoutBuffer = std::cout.rdbuf(oss.rdbuf()); // Redirect std::cout to oss

        wordfind.guessWord(incorrectGuess);

        // Restore original cout buffer
        std::cout.rdbuf(originalCoutBuffer);

        // Check if the output contains the expected message
        std::string expectedMessage = "Try again...";
        assert(oss.str().find(expectedMessage) != std::string::npos &&
            "Expected message for incorrect guess was not printed!");

        // Check that wordsFound has not been updated
        assert(std::find(wordfind.wordsFound.begin(), wordfind.wordsFound.end(), incorrectGuess) == wordfind.wordsFound.end() &&
            "Incorrect guess should not have been added to wordsFound!");

        std::cout << "All guessWord tests passed successfully." << std::endl;
    }


    static void reset_t() {
        Wordfind wordfind;

        // Set initial state with some dummy data
        wordfind.words = { "word1", "word2" };
        wordfind.wordsFound = { "word1" };
        wordfind.wordPositions = { {0, 0}, {1, 1} };
        wordfind.wordsFoundCoordinates.insert({ 2, 2 });
        wordfind.wordToPositionMap["word2"] = { {3, 3}, {4, 4} };

        // Ensure the state is set
        assert(!wordfind.words.empty());
        assert(!wordfind.wordsFound.empty());
        assert(!wordfind.wordPositions.empty());
        assert(!wordfind.wordsFoundCoordinates.empty());
        assert(!wordfind.wordToPositionMap.empty());

        // Call the resetGameState method
        wordfind.reset();

        // Test that all internal state variables are cleared
        assert(wordfind.wordsFound.empty());
        assert(wordfind.wordPositions.empty());
        assert(wordfind.wordsFoundCoordinates.empty());
        assert(wordfind.wordToPositionMap.empty());

        std::cout << "resetGameState test passed." << std::endl;
    }

    static void updateWordVector_t() {
        Wordfind wordfind;

        // Set up initial data
        std::vector<std::vector<char>> grid(10, std::vector<char>(10, ' '));
        std::vector<std::string> words = { "word" };
        wordfind.words = words;
        wordfind.addWordsToGrid();

        // Simulate positions in the wordToPositionMap
        Wordfind::PositionSet positions;
        positions.insert({ 1, 1 });
        positions.insert({ 1, 2 });
        positions.insert({ 1, 3 });
        wordfind.wordToPositionMap["word"] = positions;

        // Call updateWordVector
        wordfind.updateWordVector("word");

        // Expected result: positions should be added to wordsFoundCoordinates
        Wordfind::PositionSet expectedPositions = { {1, 1}, {1, 2}, {1, 3} };

        // Check if wordsFoundCoordinates contains the expected positions
        assert(wordfind.wordsFoundCoordinates.size() == expectedPositions.size());
        for (const auto& pos : expectedPositions) {
            assert(wordfind.wordsFoundCoordinates.find(pos) != wordfind.wordsFoundCoordinates.end());
        }

        std::cout << "updateWordVector test passed." << std::endl;
    }

    // Test method for Wordfind::setup
    static void setup_t() {
        Wordfind wordfind;

        // Mock DataGenerator to provide controlled output
        DataGenerator mockGenerator;
        
        // Call setup to populate words and initialize the grid
        wordfind.setup();

        // Validate that the words vector is populated correctly
        assert(wordfind.words.size() == Wordfind::WORD_COUNT && "Word count mismatch!");

        // Check if the words are valid (not empty and of correct size)
        for (const auto& word : wordfind.words) {
            assert(word.size() < Wordfind::GRID_SIZE && word.size() > 2 && "Word size is not valid!");
            assert(std::all_of(word.begin(), word.end(), ::islower) && "Word must be in lowercase!");
        }

        // Check if the grid is initialized correctly (the actual check will depend on your implementation)
        assert(!wordfind.grid.empty() && "Grid should not be empty!");
        assert(wordfind.grid.size() == Wordfind::GRID_SIZE && "Grid size mismatch!");

        std::cout << "All setup tests passed successfully." << std::endl;
    }


    // Method that tests the print method for the wordfind class
    static void printGrid_t() {
        Wordfind wf;

        // Define test grid and expected output
        std::vector<std::vector<char>> grid = {
            {'A', 'B', 'C'},
            {'D', 'E', 'F'},
            {'G', 'H', 'I'}
        };

        wf.grid = grid;

        // Redirect cout to a string stream
        std::stringstream ss;
        std::streambuf* oldCoutBuffer = std::cout.rdbuf(ss.rdbuf());

        // Call the method
        wf.printGrid();

        // Reset cout
        std::cout.rdbuf(oldCoutBuffer);

        // Get the output and check it
        std::string output = ss.str();
        std::string expectedOutput =
            "\033[36m__\033[0m\033[36m__\033[0m\033[36m__\033[0m\033[36m__\033[0m\033[36m__\033[0m\033[36m__\033[0m\033[36m__\033[0m\033[36m__\033[0m\033[36m__\033[0m\033[36m__\033[0m\033[36m__\033[0m\033[36m_\033[0m\n"
            "\033[36m|\033[0m A B C \033[36m|\033[0m\n"
            "\033[36m|\033[0m D E F \033[36m|\033[0m\n"
            "\033[36m|\033[0m G H I \033[36m|\033[0m\n"
            "\033[36m--\033[0m\033[36m--\033[0m\033[36m--\033[0m\033[36m--\033[0m\033[36m--\033[0m\033[36m--\033[0m\033[36m--\033[0m\033[36m--\033[0m\033[36m--\033[0m\033[36m--\033[0m\033[36m--\033[0m\033[36m-\033[0m\n";

        assert(output == expectedOutput);
        // std::cout << (output) << std::endl;
        // std::cout << (expectedOutput) << std::endl;

        // std::cout << (output == expectedOutput) << std::endl;
    }

    static void generate_t() {
        Wordfind wordfind;

        // Setup a mock grid for testing
        wordfind.grid = {
            {'H', 'E', 'L', 'L', 'O'},
            {'W', 'O', 'R', 'L', 'D'},
            {'T', 'E', 'S', 'T', 'S'},
            {'G', 'R', 'I', 'D', 'S'},
            {'A', 'B', 'C', 'D', 'E'}
        };

        // Generate the output string
        std::string output = wordfind.generate();

        // Expected ASCII art header
        std::string expectedHeader = R"(
+=================================================+
|   __        __            _  __ _           _   |
|   \ \      / /__  _ __ __| |/ _(_)_ __   __| |  |
|    \ \ /\ / / _ \| '__/ _` | |_| | '_ \ / _` |  |
|     \ V  V / (_) | | | (_| |  _| | | | | (_| |  |
|      \_/\_/ \___/|_|  \__,_|_| |_|_| |_|\__,_|  |
|                                                 |
+=================================================+
)";

        // Check if the header is present in the output
        assert(output.find(expectedHeader) != std::string::npos && "Header is missing in the output!");

        // Check if the grid is printed correctly
        std::string expectedGrid = "H E L L O\nW O R L D\nT E S T S\nG R I D S\nA B C D E\n"; // Adjust based on your printGrid implementation
        assert(output.find(expectedGrid) != std::string::npos && "Grid is missing or incorrect in the output!");

        // Check for the prompt
        assert(output.find("Press 1) to guess a word") != std::string::npos && "Prompt for guessing a word is missing!");
        assert(output.find("Press q to quit") != std::string::npos && "Quit prompt is missing!");

        std::cout << "All generate tests passed successfully." << std::endl;
    }

    //Code to test the display method

    // Mock class to capture output during testing
    class MockWordfind : public Wordfind {
    public:
        std::string generatedOutput;

        std::string generate() override {
            generatedOutput = Wordfind::generate(); // Call the original method
            return generatedOutput;
        }
    };

    static void display_t() {
        MockWordfind wordfind;

        // Setup a mock grid for testing
        wordfind.grid = {
            {'H', 'E', 'L', 'L', 'O'},
            {'W', 'O', 'R', 'L', 'D'},
            {'T', 'E', 'S', 'T', 'S'},
            {'G', 'R', 'I', 'D', 'S'},
            {'A', 'B', 'C', 'D', 'E'}
        };

        // Call the display method
        wordfind.display();

        // Check if the generated output is not empty
        assert(!wordfind.generatedOutput.empty() && "Generated output is empty!");

        // Check if the header is present in the output
        std::string expectedHeader = R"(
+=================================================+
|   __        __            _  __ _           _   |
|   \ \      / /__  _ __ __| |/ _(_)_ __   __| |  |
|    \ \ /\ / / _ \| '__/ _` | |_| | '_ \ / _` |  |
|     \ V  V / (_) | | | (_| |  _| | | | | (_| |  |
|      \_/\_/ \___/|_|  \__,_|_| |_|_| |_|\__,_|  |
|                                                 |
+=================================================+
)";

        // Check if the header is present in the output
        assert(wordfind.generatedOutput.find(expectedHeader) != std::string::npos && "Header is missing in the output!");

        // Check for the grid in the output
        std::string expectedGrid = "H E L L O\nW O R L D\nT E S T S\nG R I D S\nA B C D E\n"; // Adjust based on your printGrid implementation
        assert(wordfind.generatedOutput.find(expectedGrid) != std::string::npos && "Grid is missing or incorrect in the output!");

        // Check for the prompt
        assert(wordfind.generatedOutput.find("Press 1) to guess a word") != std::string::npos && "Prompt for guessing a word is missing!");
        assert(wordfind.generatedOutput.find("Press q to quit") != std::string::npos && "Quit prompt is missing!");

        std::cout << "All display tests passed successfully." << std::endl;
    }

    static void menu_t() {
        Wordfind wordfind;

        // Test case 1: Valid guess input
        {
            // Set up the initial state
            wordfind.words = { "TEST", "HELLO", "WORLD" }; // Add words to the game
            std::string guess = "TEST"; // Simulated guess input

            // Capture the output for verification
            std::streambuf* originalCout = std::cout.rdbuf(); // Save original buffer
            std::ostringstream oss; // Create a string stream to capture output
            std::cout.rdbuf(oss.rdbuf()); // Redirect std::cout to the string stream

            // Simulate user input
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore any leftover input
            std::cout << "1\n" << guess << std::endl; // Simulate selecting option '1' and inputting the guess

            // Call the menu function
            bool continueGame = wordfind.menu();

            // Verify that the word was guessed correctly
            assert(wordfind.wordsFound.size() == 1 && "The guessed word should be added to wordsFound.");
            assert(wordfind.wordsFound[0] == guess && "The guessed word should be 'TEST'.");
            assert(continueGame == true && "The game should continue after a valid guess.");

            std::cout.rdbuf(originalCout); // Restore original buffer
        }

        // Test case 2: Quit option
        {
            std::streambuf* originalCout = std::cout.rdbuf(); // Save original buffer
            std::ostringstream oss; // Create a string stream to capture output
            std::cout.rdbuf(oss.rdbuf()); // Redirect std::cout to the string stream

            std::cout << "q" << std::endl; // Simulate selecting the quit option

            // Call the menu function
            bool continueGame = wordfind.menu();

            // Verify that the game ends
            assert(continueGame == false && "The game should end after selecting quit.");

            std::cout.rdbuf(originalCout); // Restore original buffer
        }

        // Test case 3: Invalid option
        {
            std::streambuf* originalCout = std::cout.rdbuf(); // Save original buffer
            std::ostringstream oss; // Create a string stream to capture output
            std::cout.rdbuf(oss.rdbuf()); // Redirect std::cout to the string stream

            std::cout << "x" << std::endl; // Simulate pressing an invalid key

            // Call the menu function
            bool continueGame = wordfind.menu();

            // Verify that the game continues
            assert(continueGame == true && "The game should continue after an invalid input.");

            std::cout.rdbuf(originalCout); // Restore original buffer
        }

        std::cout << "All menu tests passed!" << std::endl;
    }



private:
    static void printPositionSet(const Wordfind::PositionSet& posSet) {
        for (const auto& pos : posSet) {
            std::cout << "(" << pos.first << ", " << pos.second << ")" << std::endl;
        }
    }
    // Helper function to search for a word in the grid
    static bool searchWordInGrid(const std::vector<std::vector<char>>& grid, const std::string& word, int startRow, int startCol) {
        static const int directions[8][2] = { {1, 0}, {0, 1}, {1, 1}, {-1, 1}, {0, -1}, {-1, 0}, {1, -1}, {-1, -1} };

        for (const auto& dir : directions) {
            int row = startRow;
            int col = startCol;
            int dRow = dir[0];
            int dCol = dir[1];
            bool found = true;

            for (char c : word) {
                if (row < 0 || row >= Wordfind::GRID_SIZE || col < 0 || col >= Wordfind::GRID_SIZE || grid[row][col] != c) {
                    found = false;
                    break;
                }
                row += dRow;
                col += dCol;
            }

            if (found) return true;
        }
        return false;
    }

    friend class Wordfind;
};



int main() {
    WordfindTest::initializeGrid_t();
    WordfindTest::placeWord_t();
    WordfindTest::addWordsToGrid_t();
    WordfindTest::reset_t();
    WordfindTest::updateWordVector_t();
    WordfindTest::printGrid_t();
    WordfindTest::setup_t();
    WordfindTest::generate_t();
    WordfindTest::display_t();
    WordfindTest::menu_t();


	return 0;
}

