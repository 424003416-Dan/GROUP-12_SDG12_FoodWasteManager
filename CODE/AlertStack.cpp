#include "AlertStack.h"
#include "Utilities.h"
#include <iostream>
#include <fstream>

using namespace std;

// CONSTRUCTOR - MAKES EMPTY STACK WITH TOP AT -1 (NO ITEMS)
AlertStack::AlertStack() : top(-1) {}

// ADDS NEW ALERT TO TOP OF STACK
void AlertStack::push(string alert) {
    if (top < 49) {  // IF STACK NOT FULL YET
        top++;             // MOVE TOP UP
        alerts[top] = alert;  // PUT ALERT AT NEW TOP
    } else {  // IF STACK IS FULL (50 ALERTS ALREADY)
        shiftDown();   // MOVE ALL ALERTS DOWN TO MAKE SPACE
        top = 49;      // TOP IS LAST SPOT (INDEX 49)
        alerts[top] = alert;  // PUT NEW ALERT AT TOP
    }
}

// REMOVES AND RETURNS TOP ALERT FROM STACK
string AlertStack::pop() {
    if (top >= 0) {  // IF STACK HAS AT LEAST ONE ALERT
        string alert = alerts[top];  // GET THE TOP ALERT
        top--;                       // MOVE TOP DOWN (REMOVE IT)
        return alert;                // GIVE BACK THE ALERT
    }
    return "";  // IF STACK EMPTY, RETURN EMPTY STRING
}

// CHECKS IF STACK IS EMPTY (NO ALERTS)
bool AlertStack::isEmpty() const {
    return top == -1;  // TOP IS -1 WHEN NO ITEMS
}

// SHOWS THE MOST RECENT ALERTS (LATEST 5)
void AlertStack::displayRecent() const {
    if (isEmpty()) {  // IF NO ALERTS AT ALL
        cout << Utilities::YELLOW << "NO RECENT ALERTS.\n" << Utilities::RESET;
        return;
    }

    // PRINT HEADER
    cout << Utilities::CYAN << "\n--- RECENT ALERTS ---\n" << Utilities::RESET;

    int displayCount = 0;  // COUNT HOW MANY WE SHOWED

    // LOOP FROM TOP DOWN, SHOW MAX 5 ALERTS
    for (int i = top; i >= 0 && displayCount < 5; i--, displayCount++) {
        cout << displayCount+1 << ". " << alerts[i] << endl;  // NUMBER AND ALERT
    }
}

// HELPER FUNCTION - MOVES ALL ALERTS DOWN ONE SPOT
// USED WHEN STACK IS FULL AND WE NEED TO MAKE ROOM
void AlertStack::shiftDown() {
    // LOOP THROUGH ARRAY (EXCEPT LAST SPOT)
    for (int i = 0; i < 49; i++) {
        alerts[i] = alerts[i + 1];  // MOVE EACH ALERT DOWN ONE
    }
    // AFTER THIS, SPOT AT INDEX 49 IS FREE FOR NEW ALERT
}

// SAVES ALL ALERTS TO A TEXT FILE
void AlertStack::saveToFile(const string& filename) const {
    ofstream file(filename);  // OPEN FILE FOR WRITING
    if (!file) return;        // IF CANT OPEN, JUST RETURN

    file << top + 1 << endl;  // SAVE HOW MANY ALERTS (TOP INDEX + 1)

    // SAVE EACH ALERT ON ITS OWN LINE
    for (int i = 0; i <= top; i++) {
        file << alerts[i] << endl;
    }

    file.close();  // CLOSE FILE
}

// LOADS ALERTS FROM A TEXT FILE
void AlertStack::loadFromFile(const string& filename) {
    ifstream file(filename);  // OPEN FILE FOR READING
    if (!file) return;        // IF CANT OPEN, JUST RETURN

    int count;          // WILL HOLD HOW MANY ALERTS IN FILE
    file >> count;      // READ COUNT
    file.ignore();      // IGNORE NEWLINE AFTER NUMBER

    top = -1;  // START WITH EMPTY STACK

    // READ EACH ALERT AND PUSH IT TO STACK
    for (int i = 0; i < count && i < 50; i++) {
        string alert;            // TEMP STRING FOR ALERT
        getline(file, alert);    // READ ONE ALERT LINE
        push(alert);             // ADD TO STACK
    }

    file.close();  // CLOSE FILE
}
