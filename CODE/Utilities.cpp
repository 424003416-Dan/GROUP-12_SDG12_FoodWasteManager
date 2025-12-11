#include "Utilities.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <limits>

using namespace std;

// SETTING UP THE COLOR CODES FOR TERMINAL
// THESE ARE SPECIAL CODES THAT CHANGE TEXT COLOR
const string Utilities::RESET = "\033[0m";
const string Utilities::RED = "\033[31m";
const string Utilities::GREEN = "\033[32m";
const string Utilities::YELLOW = "\033[33m";
const string Utilities::CYAN = "\033[36m";

// LIST OF ALL FOOD CATEGORIES THE PROGRAM KNOWS ABOUT
const string Utilities::CATEGORIES[6] = {
    "MEAT", "DAIRY", "FRUIT", "VEGETABLE", "GRAINS", "BAKERY"
};

// REASONS WHY FOOD MIGHT BE THROWN AWAY
const string Utilities::REASONS[4] = {
    "EXPIRED", "OVERBOUGHT", "SPOILED", "DAMAGED"
};

// MAXIMUM NUMBERS FOR DIFFERENT PARTS OF THE PROGRAM
const int Utilities::MAX_ITEMS = 1000;   // HOW MANY FOOD ITEMS WE CAN HAVE
const int Utilities::MAX_WASTE = 1000;   // HOW MANY WASTE RECORDS WE CAN KEEP
const int Utilities::STACK_SIZE = 50;    // FOR UNDO AND REDO FEATURES

// CLEARS THE TERMINAL SCREEN USING SPECIAL CHARACTERS
// \033[2J CLEARS SCREEN, \033[1;1H MOVES CURSOR TO TOP
void Utilities::clearScreen() {
    cout << "\033[2J\033[1;1H";
}

// PAUSES PROGRAM AND WAITS FOR USER TO PRESS ENTER
// USEFUL FOR LETTING USER READ INFORMATION BEFORE CONTINUING
void Utilities::pauseScreen() {
    cout << YELLOW << "\n[PRESS ENTER TO CONTINUE]" << RESET;
    cin.clear();  // CLEARS ANY ERROR FLAGS ON CIN
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // IGNORES ALL INPUT UNTIL ENTER
}

// GETS TODAYS DATE FROM COMPUTERS CLOCK
// RETURNS DATE IN YYYY-MM-DD FORMAT
string Utilities::getCurrentDate() {
    time_t now = time(0);          // GET CURRENT TIME FROM SYSTEM
    tm* ltm = localtime(&now);     // CONVERT TO LOCAL TIME STRUCTURE

    // EXTRACT YEAR, MONTH, DAY FROM TIME STRUCT
    int year = 1900 + ltm->tm_year;  // tm_year IS YEARS SINCE 1900
    int month = 1 + ltm->tm_mon;     // tm_mon IS 0-11 SO ADD 1
    int day = ltm->tm_mday;          // tm_mday IS DAY OF MONTH

    // MAKE SURE MONTH AND DAY HAVE TWO DIGITS (ADD LEADING ZERO IF NEEDED)
    string monthStr = (month < 10) ? "0" + to_string(month) : to_string(month);
    string dayStr = (day < 10) ? "0" + to_string(day) : to_string(day);

    // PUT TOGETHER IN YYYY-MM-DD FORMAT
    return to_string(year) + "-" + monthStr + "-" + dayStr;
}

// CALCULATES HOW MANY DAYS UNTIL FOOD EXPIRES
// SIMPLE CALCULATION - NOT SUPER ACCURATE BUT GOOD ENOUGH
int Utilities::calculateDaysToExpiry(const string& expiryDate) {
    string currentDate = getCurrentDate();  // GET TODAYS DATE

    // IF FOOD ALREADY EXPIRED, RETURN -1
    if (currentDate > expiryDate) return -1;

    // BREAK DATES INTO YEAR, MONTH, DAY PARTS
    int currentYear = stoi(currentDate.substr(0, 4));
    int currentMonth = stoi(currentDate.substr(5, 2));
    int currentDay = stoi(currentDate.substr(8, 2));

    int expiryYear = stoi(expiryDate.substr(0, 4));
    int expiryMonth = stoi(expiryDate.substr(5, 2));
    int expiryDay = stoi(expiryDate.substr(8, 2));

    // SIMPLE DAYS CALCULATION - ASSUMES 30 DAYS PER MONTH
    int days = (expiryYear - currentYear) * 365;
    days += (expiryMonth - currentMonth) * 30;
    days += (expiryDay - currentDay);

    // MAKE SURE WE DONT RETURN LESS THAN -1
    return max(days, -1);
}

// GETS A NUMBER FROM USER AND CHECKS IF ITS VALID
// KEEPS ASKING UNTIL USER GIVES GOOD NUMBER
int Utilities::getValidatedInt(const string& prompt, int min, int max) {
    int value;  // WILL HOLD USER INPUT

    // LOOP UNTIL WE GET GOOD INPUT
    while (true) {
        cout << prompt;  // SHOW PROMPT TO USER
        cin >> value;    // GET INPUT

        // IF CIN FAILED (USER TYPED WORDS INSTEAD OF NUMBER)
        if (cin.fail()) {
            cin.clear();  // CLEAR ERROR FLAG
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // CLEAR BAD INPUT
            cout << RED << "INVALID INPUT! ENTER A NUMBER.\n" << RESET;
        }
        // IF NUMBER IS TOO SMALL OR TOO BIG
        else if (value < min || value > max) {
            cout << RED << "VALUE MUST BE BETWEEN " << min << " AND " << max << "\n" << RESET;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // CLEAR EXTRA INPUT
        }
        // IF EVERYTHING IS GOOD
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // CLEAR NEWLINE
            return value;  // RETURN THE GOOD NUMBER
        }
    }
}
