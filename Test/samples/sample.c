#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define WORD_LENGTH 5
#define MAX_TRIES 6

// Function to clear the screen (works on Unix-like systems)
void clear_screen() {
    printf("\033[2J\033[H");
}

// Function to get a random word for the game
const char *get_random_word() {
    const char *words[] = {"apple", "banana", "cherry", "orange", "grape", "melon", "pear", "peach", "plum"};
    int num_words = sizeof(words) / sizeof(words[0]);
    int random_index = rand() % num_words;
    return words[random_index];
}

// Function to display current state of guessed letters
void display_word(const char *secret_word, const bool *guessed, int word_length) {
    for (int i = 0; i < word_length; ++i) {
        if (guessed[i]) {
            printf("%c ", secret_word[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

// Function to check if the player has won
bool has_won(const char *secret_word, const bool *guessed, int word_length) {
    for (int i = 0; i < word_length; ++i) {
        if (!guessed[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    const char *secret_word = get_random_word();
    int word_length = strlen(secret_word);

    // Allocate memory dynamically for guessed array
    bool *guessed = (bool *)malloc(word_length * sizeof(bool));
    if (guessed == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    memset(guessed, false, word_length * sizeof(bool));

    int tries = 0;

    clear_screen();
    printf("Welcome to Wordle!\n");
    printf("Guess the %d-letter word.\n", word_length);

    while (tries < MAX_TRIES) {
        printf("\n");
        display_word(secret_word, guessed, word_length);

        char guess;
        printf("Enter a letter guess: ");
        scanf(" %c", &guess);
        guess = tolower(guess);

        bool found = false;
        for (int i = 0; i < word_length; ++i) {
            if (secret_word[i] == guess) {
                guessed[i] = true;
                found = true;
            }
        }

        if (!found) {
            tries++;
            printf("Incorrect guess. Tries left: %d\n", MAX_TRIES - tries);
        } else {
            printf("Correct guess!\n");
        }

        if (has_won(secret_word, guessed, word_length)) {
            printf("\nCongratulations! You guessed the word: %s\n", secret_word);
            break;
        }
    }

    if (tries >= MAX_TRIES) {
        printf("\nSorry, you've run out of tries. The word was: %s\n", secret_word);
    }

    // Free dynamically allocated memory
    free(guessed);

    return 0;
}
