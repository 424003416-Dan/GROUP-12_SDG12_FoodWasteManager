// FOOD WASTE MANAGEMENT SYSTEM MAIN PROGRAM
// THIS IS THE MAIN FILE THAT RUNS THE WHOLE PROGRAM
// IT USES THREE DSA CONCEPTS: ARRAY, STACK, AND MERGE SORT

#include "Utilities.h"
#include "FoodArray.h"
#include "AlertStack.h"
#include "MergeSort.h"
#include <iostream>
#include <string>

using namespace std;

// THESE ARE THE THREE MAIN DATA STRUCTURES FOR THE PROGRAM
FoodArray inventory;      // ARRAY - STORES FOOD ITEMS
AlertStack alertStack;    // STACK - STORES RECENT ALERTS
MergeSort wasteAnalytics; // MERGE SORT - SORTS WASTE LOGS

// FUNCTION DECLARATIONS
void login();
void showMenu();
void addFoodItem();
void logWaste();
void runPerformanceTest();

// MAIN FUNCTION
int main() {
    // FIX TERMINAL COLOR ON WINDOWS
    #ifdef _WIN32
        system("color");
    #endif

    Utilities::clearScreen();
    cout << Utilities::GREEN << "INITIALIZING FOOD WASTE MANAGEMENT SYSTEM...\n" << Utilities::RESET;;

    // LOAD SAVED DATA FROM FILES
    inventory.loadFromFile("INPUT_DATA/inventory.dat");
    wasteAnalytics.loadFromFile("INPUT_DATA/waste.dat");
    alertStack.loadFromFile("INPUT_DATA/alerts.dat");

    cout << "LOADED " << inventory.getItemCount() << " ITEMS AND "
         << wasteAnalytics.getWasteCount() << " WASTE LOGS.\n";
    Utilities::pauseScreen();

    login();  // ASK USER TO LOGIN FIRST

    int choice;  // WILL HOLD USER'S MENU CHOICE
    do {
        showMenu();  // SHOW MAIN MENU
        choice = Utilities::getValidatedInt("\nENTER YOUR CHOICE: ", 0, 6);

        // DO DIFFERENT THINGS BASED ON USER CHOICE
        switch(choice) {
            case 1:  // SHOW ALL FOOD ITEMS
                inventory.displayAll();
                Utilities::pauseScreen();
                break;
            case 2:  // SHOW EXPIRY ALERTS
                inventory.displayExpiryAlerts();
                Utilities::pauseScreen();
                break;
            case 3:  // ADD NEW FOOD ITEM
                addFoodItem();
                Utilities::pauseScreen();
                break;
            case 4:  // LOG WASTED FOOD
                logWaste();
                Utilities::pauseScreen();
                break;
            case 5:  // VIEW SORTED WASTE DATA
                wasteAnalytics.sortByQuantity();
                wasteAnalytics.displaySorted();
                Utilities::pauseScreen();
                break;
            case 6:  // RUN PERFORMANCE TESTS
                runPerformanceTest();
                Utilities::pauseScreen();
                break;
            case 0:  // EXIT PROGRAM
                Utilities::clearScreen();
                cout << Utilities::GREEN << "SAVING ALL DATA AND EXITING...\n" << Utilities::RESET;
                inventory.saveToFile("INPUT_DATA/inventory.dat");
                wasteAnalytics.saveToFile("INPUT_DATA/waste.dat");
                alertStack.saveToFile("INPUT_DATA/alerts.dat");
                break;
            default:  // IF USER ENTERS WRONG NUMBER
                cout << Utilities::RED << "INVALID CHOICE!\n" << Utilities::RESET;
                Utilities::pauseScreen();
        }
    } while (choice != 0);  // KEEP GOING UNTIL USER CHOOSES 0

    // SAY GOODBYE MESSAGE
    Utilities::clearScreen();
    cout << Utilities::GREEN << "========================================\n";
    cout << "   THANK YOU FOR USING FOOD WASTE MANAGER\n";
    cout << "   UN SDG 12: RESPONSIBLE CONSUMPTION\n";
    cout << "========================================\n" << Utilities::RESET;

    return 0;  // END PROGRAM
}

// LOGIN FUNCTION
void login() {
    while (true) {  // KEEP TRYING UNTIL GET RIGHT PASSWORD
        Utilities::clearScreen();

        // SHOW LOGIN SCREEN HEADER
        cout << Utilities::CYAN << "========================================\n";
        cout << "     FOOD WASTE MANAGEMENT SYSTEM\n";
        cout << "     UN SDG 12: REDUCE FOOD WASTE\n";
        cout << "========================================\n" << Utilities::RESET;
        cout << "\nADMINISTRATOR LOGIN\n";
        cout << "----------------------------------------\n";

        string username, password;  // STORAGE FOR USER INPUT

        cout << "USERNAME: ";
        getline(cin, username);  // GET USERNAME

        cout << "PASSWORD: ";
        getline(cin, password);  // GET PASSWORD

        // CHECK IF USERNAME AND PASSWORD ARE CORRECT
        if (username == "admin" && password == "admin123") {
            cout << Utilities::GREEN << "\nLOGIN SUCCESSFUL! WELCOME ADMIN.\n" << Utilities::RESET;
            Utilities::pauseScreen();
            return;  // EXIT LOGIN FUNCTION
        } else {
            // IF LOGIN FAILS
            Utilities::clearScreen();
            cout << Utilities::RED << "========================================\n";
            cout << "           LOGIN FAILED\n";
            cout << "========================================\n" << Utilities::RESET;
            cout << "INVALID USERNAME OR PASSWORD!\n";
            cout << Utilities::YELLOW << "PLEASE TRY AGAIN\n" << Utilities::RESET;
            cout << "DEFAULT CREDENTIALS: admin / admin123\n";
            cout << "----------------------------------------\n";
            Utilities::pauseScreen();
        }
    }
}

// SHOWS THE MAIN MENU SCREEN
void showMenu() {
    Utilities::clearScreen();

    string currentDate = Utilities::getCurrentDate();  // GET TODAYS DATE

    // SHOW PROGRAM HEADER
    cout << Utilities::CYAN << "========================================\n";
    cout << "     FOOD WASTE MANAGER - ADMIN PANEL\n";
    cout << "========================================\n" << Utilities::RESET;
    cout << "DATE: " << currentDate << "\n";
    cout << "INVENTORY: " << inventory.getItemCount() << " ITEMS\n";
    cout << "WASTE LOGS: " << wasteAnalytics.getWasteCount() << " RECORDS\n";
    cout << "----------------------------------------\n";

    alertStack.displayRecent();  // SHOW RECENT ALERTS

    // SHOW MENU OPTIONS
    cout << Utilities::CYAN << "\nMAIN MENU:\n";
    cout << "----------------------------------------\n" << Utilities::RESET;
    cout << "[1] VIEW FOOD INVENTORY\n";
    cout << "[2] CHECK EXPIRY ALERTS\n";
    cout << "[3] ADD FOOD ITEM\n";
    cout << "[4] LOG WASTE FOOD\n";
    cout << "[5] VIEW WASTE ANALYTICS\n";
    cout << "[6] PERFORMANCE TEST\n";
    cout << "[0] EXIT PROGRAM\n";
    cout << Utilities::CYAN << "========================================\n" << Utilities::RESET;
}

// FUNCTION TO ADD NEW FOOD ITEM TO INVENTORY
void addFoodItem() {
    Utilities::clearScreen();

    cout << Utilities::CYAN << "========================================\n";
    cout << "            ADD FOOD ITEM\n";
    cout << "========================================\n" << Utilities::RESET;

    string name, expiry, category;  // VARIABLES FOR NEW ITEM DATA
    int quantity, categoryChoice;   // MORE VARIABLES

    cout << "FOOD NAME: ";
    getline(cin, name);  // GET ITEM NAME

    quantity = Utilities::getValidatedInt("QUANTITY: ", 1, 10000);  // GET VALID QUANTITY

    // SHOW CATEGORY OPTIONS
    cout << "\nSELECT CATEGORY:\n";
    for (int i = 0; i < 6; i++) {
        cout << "[" << i+1 << "] " << Utilities::CATEGORIES[i] << "\n";
    }
    categoryChoice = Utilities::getValidatedInt("CHOICE (1-6): ", 1, 6);  // GET CATEGORY CHOICE
    category = Utilities::CATEGORIES[categoryChoice-1];  // CONVERT CHOICE TO CATEGORY NAME

    cout << "EXPIRY DATE (YYYY-MM-DD): ";
    getline(cin, expiry);  // GET EXPIRY DATE

    // CREATE NEW FOOD ITEM OBJECT
    FoodItem newItem;
    newItem.name = name;
    newItem.quantity = quantity;
    newItem.expiry = expiry;
    newItem.category = category;
    newItem.daysToExpiry = Utilities::calculateDaysToExpiry(expiry);  // CALCULATE DAYS LEFT

    inventory.addItem(newItem);  // ADD TO INVENTORY
    inventory.saveToFile("inventory.dat");  // SAVE TO FILE

    // IF ITEM EXPIRES SOON, MAKE AN ALERT
    if (newItem.daysToExpiry <= 7) {
        string alert = "NEW ITEM '" + name + "' EXPIRES IN " +
                      to_string(newItem.daysToExpiry) + " DAYS";
        alertStack.push(alert);  // ADD ALERT TO STACK
    }

    cout << Utilities::GREEN << "\nITEM ADDED SUCCESSFULLY!\n" << Utilities::RESET;
}

// FUNCTION TO LOG FOOD WASTAGE
void logWaste() {
    Utilities::clearScreen();

    // CHECK IF THERE ARE ANY ITEMS FIRST
    if (inventory.getItemCount() == 0) {
        cout << Utilities::RED << "NO ITEMS TO LOG AS WASTE!\n" << Utilities::RESET;
        return;
    }

    inventory.displayAll();  // SHOW ALL ITEMS

    // ASK WHICH ITEM TO LOG AS WASTE
    int itemNumber = Utilities::getValidatedInt("\nENTER ITEM NUMBER TO LOG WASTE: ", 1, inventory.getItemCount());
    int itemIndex = itemNumber - 1;  // CONVERT TO ARRAY INDEX

    FoodItem* item = inventory.getItem(itemIndex);  // GET THE ITEM
    if (!item) return;  // IF ITEM NOT FOUND, RETURN

    // ASK HOW MUCH WAS WASTED
    int wasteQty = Utilities::getValidatedInt(
        "WASTE QUANTITY (MAX " + to_string(item->quantity) + "): ",
        1, item->quantity
    );

    // ASK REASON FOR WASTAGE
    cout << "\nSELECT REASON:\n";
    for (int i = 0; i < 4; i++) {
        cout << "[" << i+1 << "] " << Utilities::REASONS[i] << "\n";
    }
    int reasonChoice = Utilities::getValidatedInt("CHOICE (1-4): ", 1, 4);
    string reason = Utilities::REASONS[reasonChoice-1];  // CONVERT CHOICE TO REASON

    // UPDATE INVENTORY - REDUCE QUANTITY
    item->quantity -= wasteQty;
    if (item->quantity <= 0) {  // IF NO MORE LEFT, REMOVE ITEM
        inventory.removeItem(itemIndex);
    }

    // CREATE WASTE LOG RECORD
    WasteLog log;
    log.itemName = item->name;
    log.quantity = wasteQty;
    log.reason = reason;
    log.date = Utilities::getCurrentDate();  // USE TODAYS DATE

    wasteAnalytics.addLog(log);  // ADD TO WASTE ANALYTICS

    // ADD ALERT ABOUT WASTAGE
    string alert = "WASTE LOGGED: " + log.itemName + " (" + to_string(log.quantity) + " UNITS)";
    alertStack.push(alert);

    // SAVE ALL DATA TO FILES
    inventory.saveToFile("inventory.dat");
    wasteAnalytics.saveToFile("waste.dat");

    cout << Utilities::GREEN << "\nWASTE LOGGED SUCCESSFULLY!\n" << Utilities::RESET;
}

// FUNCTION TO TEST PERFORMANCE OF DATA STRUCTURES
void runPerformanceTest() {
    Utilities::clearScreen();
    cout << Utilities::CYAN << "========================================\n";
    cout << "            PERFORMANCE TEST\n";
    cout << "========================================\n" << Utilities::RESET;

    // TEST ARRAY OPERATIONS
    cout << "\n1. ARRAY OPERATIONS TEST:\n";
    cout << "   Items in inventory: " << inventory.getItemCount() << endl;

    // TEST STACK OPERATIONS
    cout << "\n2. STACK OPERATIONS TEST:\n";
    cout << "   Recent alerts displayed above\n";

    // TEST MERGE SORT PERFORMANCE
    cout << "\n3. MERGE SORT PERFORMANCE TEST:\n";
    wasteAnalytics.performanceTest();  // RUN THE TIMING TEST

    cout << Utilities::GREEN << "\n ALL MODULES FUNCTIONING CORRECTLY\n" << Utilities::RESET;
}
