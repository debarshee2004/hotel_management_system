#include <iostream>
#include <chrono> // For date manipulation
#include <sstream> // For string manipulation
#include <ctime> // For date manipulation
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

class Guest {
private:
    int user_id;
    string user_name;
    string user_dob;
    string user_address;
    string user_phone;
    int hotel_room_no;
    string check_in_date;
    string check_out_date;

public:
    // Function to calculate the number of days the guest will stay
    // FIXME: The days calculator is not working.
    int calculateStayDuration() const {
        // Convert string dates to integers
        int date1 = std::stoi(check_in_date);
        int date2 = std::stoi(check_out_date);

        // Extract day, month, and year from the input dates
        int day1 = date1 % 100;
        int month1 = (date1 / 100) % 100;
        int year1 = date1 / 10000;

        int day2 = date2 % 100;
        int month2 = (date2 / 100) % 100;
        int year2 = date2 / 10000;

        // Create tm structures for each date
        std::tm tm1 = {0, 0, 0, day1, month1 - 1, year1 - 1900};
        std::tm tm2 = {0, 0, 0, day2, month2 - 1, year2 - 1900};

        // Convert tm structures to time_t
        std::time_t time1 = std::mktime(&tm1);
        std::time_t time2 = std::mktime(&tm2);

        // Calculate the difference in seconds
        std::time_t difference = std::difftime(time2, time1);

        // Convert the difference to days
        int daysDifference = difference / (60 * 60 * 24);

        return static_cast<int>(daysDifference);
    };

public:
    // Constructor to initialize member variables
    Guest(int id, const string& name, const string& dob, const string& address,
          const string& phone, int room_no, const string& check_in, const string& check_out)
        : user_id(id), user_name(name), user_dob(dob), user_address(address),
          user_phone(phone), hotel_room_no(room_no), check_in_date(check_in), check_out_date(check_out) {}

    // Getter functions
    int getUserId() const {
        return user_id;
    }

    string getUserName() const {
        return user_name;
    }

    string getUserDOB() const {
        return user_dob;
    }

    string getUserAddress() const {
        return user_address;
    }

    string getUserPhone() const {
        return user_phone;
    }

    int getHotelRoomNo() const {
        return hotel_room_no;
    }

    string getCheckInDate() const {
        return check_in_date;
    }

    string getCheckOutDate() const {
        return check_out_date;
    }

    // Display guest information
    // TODO: Modify the Output display.
    void displayGuestInfo() const {
        cout << "\nGuest Information:"
             << "\nUser ID: " << user_id
             << "\nName: " << user_name
             << "\nDate of Birth: " << user_dob
             << "\nAddress: " << user_address
             << "\nPhone: " << user_phone
             << "\nRoom Number: " << hotel_room_no
             << "\nCheck-in Date: " << check_in_date
             << "\nCheck-out Date: " << check_out_date
             << "\n";
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
        Terminal::clearScreen();

        int userId, roomNo;
        string userName, userDob, userAddress, userPhone, checkInDate, checkOutDate;

        cout << "Enter User ID: ";
        cin >> userId;

        cout << "Enter User Name: ";
        cin.ignore();
        getline(cin, userName);

        cout << "Enter Date of Birth (DDMMYYYY): ";
        cin >> userDob;

        cout << "Enter Address: ";
        cin.ignore();
        getline(cin, userAddress);

        cout << "Enter Phone: ";
        cin >> userPhone;

        cout << "Enter Room Number: ";
        cin >> roomNo;

        cout << "Enter Check-in Date (DDMMYYYY): ";
        cin >> checkInDate;

        cout << "Enter Check-out Date (DDMMYYYY): ";
        cin >> checkOutDate;

        // Create a Guest object with the entered information
        Guest newGuest(userId, userName, userDob, userAddress, userPhone, roomNo, checkInDate, checkOutDate);

        int stayDuration = newGuest.calculateStayDuration();
        cout << "Number of days the guest will stay: " << stayDuration << " days\n";

        // Display the information of the newly checked-in guest
        newGuest.displayGuestInfo();
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
