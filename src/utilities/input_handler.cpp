/**
* This class contains methods that capture user input, and handle it in some way without interfering with the underlying terminal. 
* E.g by capturing arrow keypresses to navigate a menu
*/

// Defining the macro TESTING for testing purposes

#ifdef TESTING
int _getch() {
    static const char test_input[] = { 'H', 'e', 'l', 'l', 'o', 27 };
    static int index = 0;
    return test_input[index++];
}
#else
#include <conio.h>  // For the real _getch()
#endif


#include "input_handler.h"
#include <stdio.h>
// #include <conio.h> 

int capturing = 0; //int to hold the capturing flag

// Function to capture keypresses
void capture_keypresses() {
    int ch;

    while (capturing) {
        ch = _getch();  // Capture keypress without waiting for Enter

        if (ch == 27) {  // ESC key to stop capturing
            end_capture_keypress();
        }
        else {
            printf("Here : %c\n", ch);
        }
    }
}

void start_capture_keypress() {
    capturing = 1; // Set capturing to true
    capture_keypresses();
}

void end_capture_keypress() {
    capturing = 0;
}




/*
char* capture_word() {
    return "Hello";
}
*/


/**
* Method that captures a keypress, and what key it was. Modified slightly for easier testing
*/

// Default key state function using GetAsyncKeyState
/*
int default_key_state(int key) {
    return GetAsyncKeyState(key);
}

int capture_keypress(KeyStateFunc key_state_func) {
    while (true) {
        for (int key = 8; key <= 255; ++key) {
            if (key_state_func(key) & 0x8000) {
                return key;
            }
        }
        Sleep(50);
    }
}*/

