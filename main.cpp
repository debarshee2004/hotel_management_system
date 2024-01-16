#include <iostream>
#include <cstdlib> // For system() function

#if defined(_WIN32) || defined(_WIN64)
    #define CLEAR "cls"
    #include <windows.h> // For GetConsoleScreenBufferInfo
#elif defined(__unix__) || defined(__APPLE__)
    #define CLEAR "clear"
    #include <sys/ioctl.h> // For ioctl system call
#else
    #error "Unsupported platform"
#endif

using namespace std;

// Terminal class for handling terminal-related functions
class Terminal {
public:
    Terminal() {}

    // Function to clear the terminal screen
    static void clearScreen() {
        system(CLEAR);
    }

    // Function to get the terminal width
    static int getTerminalWidth() {
    #if defined(_WIN32) || defined(_WIN64)
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        return csbi.srWindow.Right - csbi.srWindow.Left + 1;
    #elif defined(__unix__) || defined(__APPLE__)
        struct winsize size;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
        return size.ws_col;
    #endif
    }
};

// HotelManagementSystem class
class HotelManagementSystem {
private:
    string title;

public:
    HotelManagementSystem(const string& title) : title(title) {}

    // Function to display title centered on the terminal
    void displayCenteredTitle() {
        Terminal::clearScreen();

        int terminalWidth = Terminal::getTerminalWidth();
        int padding = (terminalWidth - title.length()) / 2;

        for (int i = 0; i < padding; ++i) {
            cout << " ";
        }

        cout << title << endl;
    }

    // Your other hotel management system functions can be added here...
};

int main() {
    HotelManagementSystem hotelSystem("Hotel Management System");
    hotelSystem.displayCenteredTitle();

    // Your other code goes here...

    return 0;
}
