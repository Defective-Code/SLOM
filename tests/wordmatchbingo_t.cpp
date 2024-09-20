#include <iostream>
#include <sstream>
#include <cassert>
#include "wordmatchbingo.h"

class WordMatchBingoTest {
public:
    static void testIsDiacritic() {
        WordMatchBingo bingo;

        // Valid diacritic characters
        assert(bingo.isDiacritic(0x0300)); // Combining grave accent
        assert(bingo.isDiacritic(0x1DC0)); // Combining diacritical marks
        assert(bingo.isDiacritic(0x0100)); // Latin Extended-A

        // Invalid diacritic characters
        assert(!bingo.isDiacritic(0x0041)); // 'A'
        assert(!bingo.isDiacritic(0x007A)); // 'z'

        std::cout << "testIsDiacritic passed." << std::endl;
    }

    static void testHasDiacritics() {
        WordMatchBingo bingo;

        // Words with diacritics
        assert(bingo.hasDiacritics("café"));
        assert(bingo.hasDiacritics("naïve"));
        assert(bingo.hasDiacritics("résumé"));

        // Words without diacritics
        assert(!bingo.hasDiacritics("hello"));
        assert(!bingo.hasDiacritics("world"));

        std::cout << "testHasDiacritics passed." << std::endl;
    }

    static void testSelectBingoWordPool() {
        WordMatchBingo bingo;

        bingo.selectBingoWordPool();
        
        // Ensure the bingoWordPool has the correct number of entries
        assert(bingo.bingoWordPool.size() == bingo.bingoWordPoolCount);

        // Check that none of the words have diacritics
        for (const auto& pair : bingo.bingoWordPool) {
            assert(!bingo.hasDiacritics(pair.first));
        }

        std::cout << "testSelectBingoWordPool passed." << std::endl;
    }

    static void testSelectBingoCard() {
        WordMatchBingo bingo;

        bingo.selectBingoWordPool();
        bingo.selectBingoCard();
        
        // Ensure the bingoCard has the correct number of entries
        assert(bingo.bingoCard.size() == bingo.bingoCardCount);

        // Ensure all words in the bingoCard are from the bingoWordPool
        for (const auto& pair : bingo.bingoCard) {
            auto it = std::find_if(bingo.bingoWordPool.begin(), bingo.bingoWordPool.end(),
                                   [&pair](const std::pair<std::string, std::string>& poolPair) {
                                       return poolPair.first == pair.first;
                                   });
            assert(it != bingo.bingoWordPool.end());
        }

        std::cout << "testSelectBingoCard passed." << std::endl;
    }

    static void testDisplayCurrentBingoWord() {
        WordMatchBingo bingo;

        bingo.selectBingoWordPool();
        bingo.displayCurrentBingoWord();

        // Ensure the currentBingoWord is updated and exists in the bingoWordPool
        auto it = std::find_if(bingo.bingoWordPool.begin(), bingo.bingoWordPool.end(),
                               [&bingo](const std::pair<std::string, std::string>& pair) {
                                   return pair.first == bingo.currentBingoWord.first;
                               });
        assert(it != bingo.bingoWordPool.end());

        std::cout << "testDisplayCurrentBingoWord passed." << std::endl;
    }

    static void testCompareUserInputToBingoCard() {
        WordMatchBingo bingo;

        bingo.selectBingoWordPool();
        bingo.selectBingoCard();
        bingo.displayCurrentBingoWord();

        // Use the first word in the bingo card for testing
        std::string userInput = bingo.bingoCard[0].first;
        bool result = bingo.compareUserInputToBingoCard(userInput);

        // Check that the word is marked as found
        assert(result == true);
        assert(bingo.wordsFound == 1);

        std::cout << "testCompareUserInputToBingoCard passed." << std::endl;
    }

    static void testStartGame() {
        WordMatchBingo bingo;

        // Mock the input/output streams
        std::stringstream inputStream;
        std::stringstream outputStream;
        std::streambuf* cinBuf = std::cin.rdbuf();
        std::streambuf* coutBuf = std::cout.rdbuf();
        std::cin.rdbuf(inputStream.rdbuf());
        std::cout.rdbuf(outputStream.rdbuf());

        // Prepare mocked input for the game
        inputStream.str("test\n"); // Simulate user input

        bingo.startGame();

        // Check for game over message
        std::string output = outputStream.str();
        assert(output.find("Game over!") != std::string::npos);

        // Restore original streams
        std::cin.rdbuf(cinBuf);
        std::cout.rdbuf(coutBuf);
        std::cout << "testStartGame passed." << std::endl;
    }
};

int main() {
    WordMatchBingoTest::testIsDiacritic();
    //WordMatchBingoTest::testHasDiacritics();
    WordMatchBingoTest::testSelectBingoWordPool();
    WordMatchBingoTest::testSelectBingoCard();
    //WordMatchBingoTest::testDisplayCurrentBingoWord();
    //WordMatchBingoTest::testCompareUserInputToBingoCard();
    WordMatchBingoTest::testStartGame();

    return 0;
}