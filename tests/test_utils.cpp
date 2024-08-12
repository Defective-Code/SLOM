#include <stdio.h>
#include <string.h>
#include <windows.h> // For VK_* constants
#include "test_utils.h"

// Initialize the key mappings for easier referencing later
const KeyMapping keyMap[] = {
    {"A", 0x41},
    {"B", 0x42},
    {"C", 0x43},
    {"D", 0x44},
    {"E", 0x45},
    {"F", 0x46},
    {"G", 0x47},
    {"H", 0x48},
    {"I", 0x49},
    {"J", 0x4A},
    {"K", 0x4B},
    {"L", 0x4C},
    {"M", 0x4D},
    {"N", 0x4E},
    {"O", 0x4F},
    {"P", 0x50},
    {"Q", 0x51},
    {"R", 0x52},
    {"S", 0x53},
    {"T", 0x54},
    {"U", 0x55},
    {"V", 0x56},
    {"W", 0x57},
    {"X", 0x58},
    {"Y", 0x59},
    {"Z", 0x5A},
    {"0", 0x30},
    {"1", 0x31},
    {"2", 0x32},
    {"3", 0x33},
    {"4", 0x34},
    {"5", 0x35},
    {"6", 0x36},
    {"7", 0x37},
    {"8", 0x38},
    {"9", 0x39},
    {"ENTER", VK_RETURN},
    {"ESC", VK_ESCAPE},
    {"TAB", VK_TAB},
    {"SPACE", VK_SPACE},
    {"BACKSPACE", VK_BACK},
    {"DELETE", VK_DELETE},
    {"LEFT", VK_LEFT},
    {"RIGHT", VK_RIGHT},
    {"UP", VK_UP},
    {"DOWN", VK_DOWN}
};

// Function to get the virtual key code from a key name
WORD get_virtual_keycode(const char* keyName) {
    size_t mapSize = sizeof(keyMap) / sizeof(keyMap[0]);
    for (size_t i = 0; i < mapSize; ++i) {
        if (strcmp(keyMap[i].keyName, keyName) == 0) {
            return keyMap[i].virtualKeyCode;
        }
    }
    fprintf(stderr, "Key name not found: %s\n", keyName);
    return 0; // Return 0 if the key name is not found
}

void simulate_keypress(WORD key) {
    INPUT ip;

    // Set up a generic keyboard event.
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0; // hardware scan code for key
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;

    // Press the key
    ip.ki.wVk = key; // virtual-key code for the "A" key
    ip.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));

    // Release the key
    ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
    SendInput(1, &ip, sizeof(INPUT));
}