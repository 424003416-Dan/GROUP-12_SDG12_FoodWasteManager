#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>

// THIS IS A UTILITY CLASS WITH HELPER FUNCTIONS AND CONSTANTS FOR THE PROGRAM
// IT HAS METHODS FOR SCREEN STUFF, DATE CALCULATIONS, AND INPUT CHECKING
class Utilities {
public:
    // METHODS FOR MANAGING THE SCREEN

    // CLEARS THE TERMINAL SCREEN - WORKS ON WINDOWS AND OTHER SYSTEMS
    static void clearScreen();

    // PAUSES THE PROGRAM UNTIL USER PRESSES ENTER KEY
    static void pauseScreen();

    // METHODS FOR WORKING WITH DATES

    // GETS TODAYS DATE AS A STRING FORMAT
    static std::string getCurrentDate();

    // FIGURES OUT HOW MANY DAYS UNTIL FOOD EXPIRES
    // TAKES EXPIRY DATE AND GIVES BACK DAYS COUNT
    static int calculateDaysToExpiry(const std::string& expiryDate);

    // METHOD FOR GETTING GOOD INPUT FROM USER

    // ASKS USER FOR A NUMBER AND MAKES SURE ITS BETWEEN MIN AND MAX
    // KEEPS ASKING UNTIL USER GIVES VALID NUMBER
    static int getValidatedInt(const std::string& prompt, int min = 0, int max = 2147483647);

    // COLORS FOR MAKING TERMINAL OUTPUT LOOK BETTER
    // THESE ARE SPECIAL CODES THAT CHANGE TEXT COLOR

    static const std::string RESET;   // GOES BACK TO NORMAL TEXT COLOR
    static const std::string RED;     // MAKES TEXT RED COLOR
    static const std::string GREEN;   // MAKES TEXT GREEN COLOR
    static const std::string YELLOW;  // MAKES TEXT YELLOW COLOR
    static const std::string CYAN;    // MAKES TEXT CYAN COLOR

    // CONSTANT VALUES USED IN DIFFERENT PARTS OF PROGRAM

    static const std::string CATEGORIES[6];  // DIFFERENT TYPES OF FOOD
    static const std::string REASONS[4];     // WHY FOOD WAS THROWN AWAY
    static const int MAX_ITEMS;              // HOW MANY ITEMS WE CAN STORE
    static const int MAX_WASTE;              // HOW MANY WASTE RECORDS WE KEEP
    static const int STACK_SIZE;             // FOR UNDO AND REDO OPERATIONS
};

// STRUCT FOR FOOD ITEM DATA
// HOLDS ALL INFO ABOUT ONE FOOD ITEM IN INVENTORY

struct FoodItem {
    std::string name;      // WHAT THE FOOD IS CALLED
    int quantity;          // HOW MUCH WE HAVE
    std::string expiry;    // WHEN IT GOES BAD - DATE FORMAT
    std::string category;  // WHAT KIND OF FOOD IT IS
    int daysToExpiry;      // DAYS LEFT UNTIL EXPIRY - CALCULATED
};

// STRUCT FOR WASTE LOG ENTRIES
// RECORDS WHEN FOOD IS THROWN AWAY AND WHY

struct WasteLog {
    std::string itemName;  // NAME OF FOOD THAT WAS WASTED
    int quantity;          // HOW MUCH WAS WASTED
    std::string reason;    // WHY IT WAS WASTED
    std::string date;      // WHEN IT WAS WASTED
};

#endif
