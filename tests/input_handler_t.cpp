#include "test_utils.h"
#include "input_handler.h"
#include "input_handler_t.h"
#include <stdio.h>
#include <string.h>
// #include <Windows.h>

/* For using windows keyboard input handling
// Mock key state function for testing
int mock_key_state(int key) {
    // Simulate that the 'A' key (0x41) is pressed
    // You can adjust this function to simulate different keys
    if (key == get_virtual_keycode("UP")) {
        return 0x8000; // Simulate key press
    }
    return 0;
}
*/

/*
int capture_keypress_t() {
    // Capture the key press and get the virtual key code

    char key = capture_keypress();

    // Optionally map the virtual key code to a string description
    if (key == VK_UP) {
        return 0;
    }
    else {
        return 1;
    }
}
*/

// TODO : Test method to check that the capture keypress method is working
int capture_keypress_t() {
    
    return 0;
    /*
    char expected_output[] = "HELLO";
    char actual_output[128];

    // Redirect stdout to a temporary file
    char temp_filename[L_tmpnam];
    tmpnam(temp_filename);
    // FILE* temp_file = tmpfile(temp_filename); // Create a temporary file
    // if (temp_file == NULL) {
    //     perror("tmpfile");
    //     return 1;
    // }

    // Store the current buffer and redirect stdout
    FILE* original_stdout = stdout;

    

    // Duplicate the file descriptor of the temp file and assign it to stdout
    fflush(stdout); // Flush any existing output

    FILE* temp_file = freopen(temp_filename, "w", stdout);
    if (temp_file == NULL) {
        perror("freopen");
        return 1;
    }

    printf("Running unit test...\n");
    start_capture_keypress();
    printf("Unit test completed.\n");

    // Restore the original stdout
    fflush(stdout);

    // Rewind the temporary file to the beginning
    rewind(temp_file);

    // Read the captured output from the file
    fread(actual_output, sizeof(char), sizeof(actual_output) - 1, temp_file);
    actual_output[sizeof(actual_output) - 1] = '\0'; // Null-terminate the buffer

    printf(actual_output);

    // freopen("/dev/tty", "w", stdout); // For Unix-like systems
    freopen("CON", "w", stdout); // For Unix-like systems

    // Close the temporary file
    fclose(temp_file);
    remove(temp_filename);

    return strcmp(actual_output, expected_output); //if it is 0, they are equal (this is the expected behaviour), else they are not equal, the method is not working
    */
}
