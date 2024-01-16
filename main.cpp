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
    void customerCheckIn() {
        // Implement customer check-in logic
        cout << "Customer check-in functionality" << endl;
    }

    void customerCheckOut() {
        // Implement customer check-out logic
        cout << "Customer check-out functionality" << endl;
    }

    void foodOrder() {
        // Implement food ordering logic
        cout << "Food order functionality" << endl;
    }

    void eventRegistration() {
        // Implement event registration logic
        cout << "Event registration functionality" << endl;
    }

    void eventParticipation() {
        // Implement event participation logic
        cout << "Event participation functionality" << endl;
    }

    void billing() {
        // Implement billing logic
        cout << "Billing functionality" << endl;
    }
};

int main() {
    HotelManagementSystem hotelSystem("Hotel Management System");
    hotelSystem.displayCenteredTitle();

    int option;
    do {
        cout << "\nOptions:"
             << "\n1. Customer Check-In"
             << "\n2. Customer Check-Out"
             << "\n3. Food Order"
             << "\n4. Event Registration"
             << "\n5. Event Participation"
             << "\n6. Billing"
             << "\n0. Exit"
             << "\nEnter your choice: ";
        cin >> option;

        switch (option) {
            case 1:
                hotelSystem.customerCheckIn();
                break;
            case 2:
                hotelSystem.customerCheckOut();
                break;
            case 3:
                hotelSystem.foodOrder();
                break;
            case 4:
                hotelSystem.eventRegistration();
                break;
            case 5:
                hotelSystem.eventParticipation();
                break;
            case 6:
                hotelSystem.billing();
                break;
            case 0:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid option. Please try again.\n";
        }

    } while (option != 0);

    return 0;
}
