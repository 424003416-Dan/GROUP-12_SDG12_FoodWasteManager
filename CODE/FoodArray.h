#ifndef FOODARRAY_H
#define FOODARRAY_H

#include "Utilities.h"
#include <string>

// CLASS FOR MANAGING FOOD ITEMS USING AN ARRAY
// THIS CLASS HANDLES ADDING, REMOVING, AND DISPLAYING FOOD ITEMS
class FoodArray {
private:
    FoodItem inventory[1000];  // MAIN ARRAY TO STORE ALL FOOD ITEMS - FIXED SIZE
    int itemCount;             // KEEPS TRACK OF HOW MANY ITEMS ARE IN THE ARRAY

public:
    // CONSTRUCTOR - SETS UP EMPTY ARRAY
    FoodArray();

    // BASIC ARRAY OPERATIONS

    // ADDS NEW FOOD ITEM TO END OF ARRAY
    void addItem(const FoodItem& item);

    // REMOVES ITEM FROM ARRAY AT SPECIFIC INDEX
    void removeItem(int index);

    // CHANGES QUANTITY OF ITEM AT GIVEN INDEX
    void updateQuantity(int index, int newQuantity);

    // GETS POINTER TO ITEM AT SPECIFIC INDEX
    FoodItem* getItem(int index);

    // RETURNS HOW MANY ITEMS ARE IN ARRAY
    int getItemCount() const;

    // METHODS TO SHOW INFORMATION TO USER

    // SHOWS ALL ITEMS IN INVENTORY WITH FORMATTING
    void displayAll() const;

    // SHOWS ONLY ITEMS THAT ARE ABOUT TO EXPIRE SOON
    void displayExpiryAlerts() const;

    // SEARCHING AND FINDING ITEMS

    // FINDS REAL ARRAY INDEX FROM USER-FRIENDLY DISPLAY NUMBER
    int findItemIndex(int displayNumber) const;

    // WORKING WITH FILES

    // SAVES ALL ITEMS TO A FILE FOR LATER USE
    void saveToFile(const std::string& filename);

    // LOADS ITEMS FROM A FILE BACK INTO ARRAY
    void loadFromFile(const std::string& filename);

private:
    // HELPER FUNCTION TO FILL GAP AFTER REMOVING ITEM
    // MOVES ALL ITEMS AFTER REMOVED ITEM ONE SPOT LEFT
    void shiftItemsLeft(int startIndex);
};

#endif
