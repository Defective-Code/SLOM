#pragma once

/**
* This class contains methods that capture user input, and handle it in some way without interfering with the underlying terminal.
* E.g by capturing arrow keypresses to navigate a menu
*/

char* capture_word();

typedef int (*KeyStateFunc)(int);
int capture_keypress(KeyStateFunc key_state_func);