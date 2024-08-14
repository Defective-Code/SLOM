/**
* This class contains methods that capture user input, and handle it in some way without interfering with the underlying terminal. 
* E.g by capturing arrow keypresses to navigate a menu
*/

#include <Windows.h>
#include "input_handler.h"

char* capture_word() {
    return "Hello";
}


/**
* Method that captures a keypress, and what key it was. Modified slightly for easier testing
*/


// Default key state function using GetAsyncKeyState
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
}