#include <stdio.h>
#include <windows.h> // Required for Windows API functions

// Function to clear the screen (works on Windows)
void clear_screen() {
    system("cls");
}

// Function to get terminal dimensions (Windows specific, console)
void get_terminal_size(int *cols, int *rows) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    *cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    *rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

// Function to display text centered in the terminal (Windows specific, console)
void display_centered(const char *text) {
    int cols, rows;
    get_terminal_size(&cols, &rows);

    int text_length = strlen(text);
    int start_col = (cols - text_length) / 2;
    int start_row = rows / 2;

    // Clear the screen
    clear_screen();

    // Set console cursor position
    COORD coord;
    coord.X = start_col;
    coord.Y = start_row;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    // Print the text
    printf("%s\n", text);
}

int main() {
    char greeting[] = "Hello, World!";

    // Display "Hello, World!" centered in the terminal (console)
    display_centered(greeting);

    // Pause before exiting (optional)
    // system("pause");
    getchar();

    // Clear the screen before exiting
    clear_screen();

    return 0;
}
