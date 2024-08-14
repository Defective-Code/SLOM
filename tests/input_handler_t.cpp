#include <Windows.h>
#include "test_utils.h"
#include "input_handler.h"
#include "input_handler_t.h"


// Mock key state function for testing
int mock_key_state(int key) {
    // Simulate that the 'A' key (0x41) is pressed
    // You can adjust this function to simulate different keys
    if (key == get_virtual_keycode("DOWN")) {
        return 0x8000; // Simulate key press
    }
    return 0;
}

int capture_keypress_t() {
    // Capture the key press and get the virtual key code

    int key = capture_keypress(mock_key_state);

    // Optionally map the virtual key code to a string description
    if (key == VK_UP) {
        return 0;
    }
    else {
        return 1;
    }
}
