#ifndef ALERTSTACK_H
#define ALERTSTACK_H

#include <string>

// CLASS FOR MANAGING ALERT MESSAGES USING A STACK
// THIS IS A LIFO (LAST IN, FIRST OUT) DATA STRUCTURE
class AlertStack {
private:
    std::string alerts[50];  // FIXED-SIZE ARRAY TO STORE ALERT MESSAGES - MAX 50
    int top;                 // TRACKS THE INDEX OF THE TOP ITEM IN STACK

public:
    // CONSTRUCTOR - MAKES EMPTY STACK
    AlertStack();

    // BASIC STACK OPERATIONS

    // ADDS NEW ALERT TO TOP OF STACK
    void push(std::string alert);

    // REMOVES AND RETURNS TOP ALERT FROM STACK
    std::string pop();

    // CHECKS IF STACK HAS NO ALERTS
    bool isEmpty() const;

    // DISPLAY METHOD

    // SHOWS MOST RECENT ALERTS (FROM TOP OF STACK)
    void displayRecent() const;

    // FILE OPERATIONS

    // SAVES ALL ALERTS TO A FILE
    void saveToFile(const std::string& filename) const;

    // LOADS ALERTS FROM A FILE
    void loadFromFile(const std::string& filename);

private:
    // HELPER FUNCTION - MOVES ALL ALERTS DOWN ONE SPOT
    // USED AFTER REMOVING AN ALERT FROM MIDDLE
    void shiftDown();
};

#endif
