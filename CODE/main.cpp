#include "FoodArray.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

// CONSTRUCTOR - MAKES EMPTY ARRAY WITH 0 ITEMS
FoodArray::FoodArray() : itemCount(0) {}

// ADDS NEW ITEM TO END OF ARRAY IF THERE IS SPACE
void FoodArray::addItem(const FoodItem& item) {
    if (itemCount >= 1000) {
        cout << Utilities::RED << "INVENTORY IS FULL!\n" << Utilities::RESET;
        return;
    }
    inventory[itemCount] = item;  // PUT ITEM AT END
    itemCount++;                  // INCREASE COUNTER
}

// REMOVES ITEM FROM ARRAY BY INDEX
void FoodArray::removeItem(int index) {
    if (index < 0 || index >= itemCount) return;  // CHECK IF INDEX IS GOOD
    shiftItemsLeft(index);  // FILL THE GAP
    itemCount--;            // ONE LESS ITEM NOW
}

// HELPER FUNCTION - MOVES ITEMS TO FILL EMPTY SPOT
void FoodArray::shiftItemsLeft(int startIndex) {
    // LOOP FROM REMOVED SPOT TO END OF ARRAY
    for (int i = startIndex; i < itemCount - 1; i++) {
        inventory[i] = inventory[i + 1];  // MOVE EACH ITEM ONE LEFT
    }
}

// CHANGES HOW MANY OF AN ITEM WE HAVE
void FoodArray::updateQuantity(int index, int newQuantity) {
    if (index >= 0 && index < itemCount) {
        inventory[index].quantity = newQuantity;  // JUST CHANGE THE NUMBER
    }
}

// GETS ITEM FROM ARRAY BY INDEX - RETURNS POINTER OR NULL
FoodItem* FoodArray::getItem(int index) {
    if (index >= 0 && index < itemCount) {
        return &inventory[index];  // GIVE ADDRESS OF ITEM
    }
    return nullptr;  // RETURN NULL IF BAD INDEX
}

// TELLS HOW MANY ITEMS ARE IN ARRAY
int FoodArray::getItemCount() const {
    return itemCount;
}

// SHOWS ALL ITEMS IN NICE TABLE FORMAT
void FoodArray::displayAll() const {
    // PRINT TABLE HEADER WITH COLORS
    cout << Utilities::CYAN << "+----+------------------------+----------+------------+------------+------------+\n";
    cout << "| NO | ITEM NAME              | QUANTITY | EXPIRY     | CATEGORY   | DAYS LEFT  |\n";
    cout << "+----+------------------------+----------+------------+------------+------------+\n" << Utilities::RESET;

    // CHECK IF ARRAY IS EMPTY
    if (itemCount == 0) {
        cout << "|" << setw(60) << "NO ITEMS IN INVENTORY" << setw(15) << "|\n";
        cout << Utilities::CYAN << "+----+------------------------+----------+------------+------------+------------+\n" << Utilities::RESET;
        return;
    }

    // LOOP THROUGH ALL ITEMS AND PRINT EACH ONE
    for (int i = 0; i < itemCount; i++) {
        string color = Utilities::GREEN;  // DEFAULT GREEN COLOR
        string status;  // TEXT FOR DAYS LEFT COLUMN

        // DECIDE COLOR AND TEXT BASED ON HOW SOON IT EXPIRES
        if (inventory[i].daysToExpiry < 0) {
            color = Utilities::RED;
            status = "EXPIRED";
        } else if (inventory[i].daysToExpiry == 0) {
            color = Utilities::RED;
            status = "TODAY";
        } else if (inventory[i].daysToExpiry <= 3) {
            color = Utilities::RED;
            status = to_string(inventory[i].daysToExpiry);
        } else if (inventory[i].daysToExpiry <= 7) {
            color = Utilities::YELLOW;
            status = to_string(inventory[i].daysToExpiry);
        } else {
            status = to_string(inventory[i].daysToExpiry);
        }

        // PRINT ONE ROW OF TABLE WITH FORMATTING
        cout << "| " << setw(2) << i+1 << " | ";
        cout << left << setw(22) << inventory[i].name << " | ";
        cout << right << setw(8) << inventory[i].quantity << " | ";
        cout << left << setw(10) << inventory[i].expiry << " | ";
        cout << left << setw(10) << inventory[i].category << " | ";
        cout << color << setw(10) << status << Utilities::RESET << " |\n";
    }

    // PRINT TABLE BOTTOM LINE
    cout << Utilities::CYAN << "+----+------------------------+----------+------------+------------+------------+\n" << Utilities::RESET;
}

// SHOWS ONLY ITEMS THAT EXPIRE SOON (FOR ALERTS)
void FoodArray::displayExpiryAlerts() const {
    // PRINT TABLE HEADER
    cout << Utilities::CYAN << "+----+------------------------+----------+------------+------------+------------+\n";
    cout << "| NO | ITEM NAME              | QUANTITY | EXPIRY     | CATEGORY   | STATUS     |\n";
    cout << "+----+------------------------+----------+------------+------------+------------+\n" << Utilities::RESET;

    bool hasAlerts = false;  // TRACK IF WE FOUND ANY EXPIRING ITEMS
    int alertNum = 1;         // NUMBER FOR DISPLAY (NOT SAME AS INDEX)

    // LOOP THROUGH ALL ITEMS
    for (int i = 0; i < itemCount; i++) {
        // ONLY SHOW IF EXPIRES IN 7 DAYS OR LESS (OR ALREADY EXPIRED)
        if (inventory[i].daysToExpiry <= 7 || inventory[i].daysToExpiry < 0) {
            hasAlerts = true;
            string status;
            string color = Utilities::YELLOW;  // DEFAULT YELLOW

            // DECIDE WHAT TO SAY BASED ON EXPIRY STATUS
            if (inventory[i].daysToExpiry < 0) {
                status = "EXPIRED";
                color = Utilities::RED;
            } else if (inventory[i].daysToExpiry == 0) {
                status = "TODAY";
                color = Utilities::RED;
            } else if (inventory[i].daysToExpiry <= 3) {
                status = "URGENT";
                color = Utilities::RED;
            } else {
                status = "SOON";
                color = Utilities::YELLOW;
            }

            // PRINT ROW FOR THIS ITEM
            cout << "| " << setw(2) << alertNum << " | ";
            cout << left << setw(22) << inventory[i].name << " | ";
            cout << right << setw(8) << inventory[i].quantity << " | ";
            cout << left << setw(10) << inventory[i].expiry << " | ";
            cout << left << setw(10) << inventory[i].category << " | ";
            cout << color << setw(10) << status << Utilities::RESET << " |\n";
            alertNum++;
        }
    }

    // IF NO ITEMS FOUND, SAY SO
    if (!hasAlerts) {
        cout << "|" << setw(60) << "NO ITEMS EXPIRING IN THE NEXT 7 DAYS" << setw(15) << "|\n";
    }

    // PRINT TABLE BOTTOM
    cout << Utilities::CYAN << "+----+------------------------+----------+------------+------------+------------+\n" << Utilities::RESET;
}

// CONVERTS DISPLAY NUMBER (1-BASED) TO ARRAY INDEX (0-BASED)
int FoodArray::findItemIndex(int displayNumber) const {
    return (displayNumber >= 1 && displayNumber <= itemCount) ? displayNumber - 1 : -1;
}

// SAVES ALL ITEMS TO TEXT FILE
void FoodArray::saveToFile(const string& filename) {
    ofstream file(filename);  // OPEN FILE FOR WRITING
    if (!file) {
        cout << Utilities::RED << "ERROR SAVING INVENTORY!\n" << Utilities::RESET;
        return;
    }

    file << itemCount << endl;  // SAVE HOW MANY ITEMS FIRST

    // SAVE EACH ITEM, ONE FIELD PER LINE
    for (int i = 0; i < itemCount; i++) {
        file << inventory[i].name << endl;
        file << inventory[i].quantity << endl;
        file << inventory[i].expiry << endl;
        file << inventory[i].category << endl;
        file << inventory[i].daysToExpiry << endl;
    }
    file.close();  // CLOSE FILE
}

// LOADS ITEMS FROM TEXT FILE
void FoodArray::loadFromFile(const string& filename) {
    ifstream file(filename);  // OPEN FILE FOR READING
    if (!file) return;        // IF CANT OPEN, JUST RETURN

    file >> itemCount;  // READ HOW MANY ITEMS
    file.ignore();      // IGNORE NEWLINE AFTER NUMBER

    // READ EACH ITEM FROM FILE
    for (int i = 0; i < itemCount && i < 1000; i++) {
        getline(file, inventory[i].name);     // READ NAME
        file >> inventory[i].quantity;        // READ QUANTITY
        file.ignore();                        // IGNORE NEWLINE
        getline(file, inventory[i].expiry);   // READ EXPIRY DATE
        getline(file, inventory[i].category); // READ CATEGORY
        file >> inventory[i].daysToExpiry;    // READ DAYS TO EXPIRY
        file.ignore();                        // IGNORE NEWLINE
    }
    file.close();  // CLOSE FILE
}
