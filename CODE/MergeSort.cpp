#include "MergeSort.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>

using namespace std;

// CONSTRUCTOR - STARTS WITH NO WASTE LOGS
MergeSort::MergeSort() : wasteCount(0) {}

// ADDS A WASTE LOG TO THE ARRAY IF THERE IS SPACE
void MergeSort::addLog(const WasteLog& log) {
    if (wasteCount < 1000) {            // CHECK IF ARRAY IS NOT FULL
        wasteLogs[wasteCount] = log;    // PUT LOG AT END OF ARRAY
        wasteCount++;                   // INCREASE THE COUNT
    }
}

// RETURNS HOW MANY WASTE LOGS ARE IN ARRAY
int MergeSort::getWasteCount() const {
    return wasteCount;
}

// MERGE FUNCTION - PART OF MERGE SORT ALGORITHM
// COMBINES TWO SORTED PARTS INTO ONE SORTED PART
void MergeSort::merge(WasteLog arr[], int left, int mid, int right) {
    // CALCULATE SIZES OF TWO PARTS
    int n1 = mid - left + 1;   // SIZE OF LEFT PART
    int n2 = right - mid;      // SIZE OF RIGHT PART

    // MAKE TEMP ARRAYS FOR LEFT AND RIGHT PARTS
    WasteLog* leftArr = new WasteLog[n1];
    WasteLog* rightArr = new WasteLog[n2];

    // COPY DATA TO TEMP ARRAYS
    for (int i = 0; i < n1; i++) leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++) rightArr[j] = arr[mid + 1 + j];

    // MERGE THE TEMP ARRAYS BACK INTO MAIN ARRAY
    int i = 0;      // INDEX FOR LEFT ARRAY
    int j = 0;      // INDEX FOR RIGHT ARRAY
    int k = left;   // INDEX FOR MAIN ARRAY

    // COMPARE AND MERGE UNTIL ONE SIDE RUNS OUT
    while (i < n1 && j < n2) {
        // SORT IN DESCENDING ORDER (BIGGEST QUANTITY FIRST)
        if (leftArr[i].quantity >= rightArr[j].quantity) {
            arr[k] = leftArr[i];  // TAKE FROM LEFT ARRAY
            i++;
        } else {
            arr[k] = rightArr[j]; // TAKE FROM RIGHT ARRAY
            j++;
        }
        k++;
    }

    // COPY ANY LEFT OVER FROM LEFT ARRAY
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    // COPY ANY LEFT OVER FROM RIGHT ARRAY
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    // CLEAN UP TEMP ARRAYS
    delete[] leftArr;
    delete[] rightArr;
}

// RECURSIVE MERGE SORT FUNCTION
// SPLITS ARRAY AND THEN MERGES BACK SORTED
void MergeSort::mergeSort(WasteLog arr[], int left, int right) {
    if (left < right) {  // STOP WHEN PART HAS ONLY ONE ELEMENT
        // FIND MIDDLE POINT TO SPLIT ARRAY
        int mid = left + (right - left) / 2;

        // SORT LEFT HALF
        mergeSort(arr, left, mid);
        // SORT RIGHT HALF
        mergeSort(arr, mid + 1, right);

        // MERGE THE TWO SORTED HALVES
        merge(arr, left, mid, right);
    }
}

// PUBLIC METHOD TO SORT ALL WASTE LOGS BY QUANTITY
void MergeSort::sortByQuantity() {
    if (wasteCount > 0) {  // ONLY SORT IF WE HAVE DATA
        mergeSort(wasteLogs, 0, wasteCount - 1);
    }
}

// SHOWS ALL WASTE LOGS IN A NICE TABLE FORMAT
void MergeSort::displaySorted() const {
    // PRINT TABLE HEADER
    cout << Utilities::GREEN << "+----+----------------------------+----------+--------------+------------+\n";
    cout << "| NO | ITEM NAME                   | QUANTITY | REASON       | DATE       |\n";
    cout << "+----+----------------------------+----------+--------------+------------+\n" << Utilities::RESET;

    // CHECK IF ARRAY IS EMPTY
    if (wasteCount == 0) {
        cout << "|" << setw(60) << "NO WASTE DATA AVAILABLE" << setw(15) << "|\n";
        cout << Utilities::GREEN << "+----+----------------------------+----------+--------------+------------+\n" << Utilities::RESET;
        return;
    }

    // LOOP THROUGH ALL WASTE LOGS AND PRINT EACH ONE
    int totalWaste = 0;  // KEEP TRACK OF TOTAL WASTED QUANTITY
    for (int i = 0; i < wasteCount; i++) {
        cout << "| " << setw(2) << i+1 << " | ";
        cout << left << setw(26) << wasteLogs[i].itemName << " | ";
        cout << right << setw(8) << wasteLogs[i].quantity << " | ";
        cout << left << setw(12) << wasteLogs[i].reason << " | ";
        cout << left << setw(10) << wasteLogs[i].date << " |\n";

        totalWaste += wasteLogs[i].quantity;  // ADD TO TOTAL
    }

    // PRINT TABLE BOTTOM
    cout << Utilities::GREEN << "+----+----------------------------+----------+--------------+------------+\n" << Utilities::RESET;

    // SHOW SUMMARY INFORMATION
    cout << "TOTAL WASTE: " << totalWaste << " UNITS | ";
    cout << "RECORDS: " << wasteCount << endl;
}

// SAVES ALL WASTE LOGS TO A TEXT FILE
void MergeSort::saveToFile(const string& filename) {
    ofstream file(filename);  // OPEN FILE FOR WRITING
    if (!file) {
        cout << Utilities::RED << "ERROR SAVING WASTE LOGS!\n" << Utilities::RESET;
        return;
    }

    file << wasteCount << endl;  // SAVE HOW MANY LOGS FIRST

    // SAVE EACH LOG, ONE FIELD PER LINE
    for (int i = 0; i < wasteCount; i++) {
        file << wasteLogs[i].itemName << endl;
        file << wasteLogs[i].quantity << endl;
        file << wasteLogs[i].reason << endl;
        file << wasteLogs[i].date << endl;
    }

    file.close();  // CLOSE FILE
}

// LOADS WASTE LOGS FROM A TEXT FILE
void MergeSort::loadFromFile(const string& filename) {
    ifstream file(filename);  // OPEN FILE FOR READING
    if (!file) return;        // IF CANT OPEN, JUST RETURN

    file >> wasteCount;  // READ HOW MANY LOGS
    file.ignore();       // IGNORE NEWLINE AFTER NUMBER

    // READ EACH LOG FROM FILE
    for (int i = 0; i < wasteCount && i < 1000; i++) {
        getline(file, wasteLogs[i].itemName);   // READ ITEM NAME
        file >> wasteLogs[i].quantity;          // READ QUANTITY
        file.ignore();                          // IGNORE NEWLINE
        getline(file, wasteLogs[i].reason);     // READ REASON
        getline(file, wasteLogs[i].date);       // READ DATE
    }

    file.close();  // CLOSE FILE
}

// TESTS HOW FAST THE MERGE SORT ALGORITHM WORKS
void MergeSort::performanceTest() const {
    if (wasteCount == 0) return;  // NEED DATA TO TEST

    // MAKE A COPY OF THE DATA SO WE DONT MESS UP ORIGINAL
    WasteLog temp[1000];
    for (int i = 0; i < wasteCount; i++) temp[i] = wasteLogs[i];

    // TIME THE SORTING PROCESS
    clock_t start = clock();  // START TIMER

    // USE CONST_CAST TO CALL NON-CONST METHOD FOR TESTING
    const_cast<MergeSort*>(this)->mergeSort(temp, 0, wasteCount - 1);

    clock_t end = clock();    // STOP TIMER

    // CALCULATE TIME TAKEN
    double sortTime = double(end - start) / CLOCKS_PER_SEC;

    // PRINT RESULTS
    cout << "MERGE SORT TIME: " << fixed << setprecision(3) << sortTime << "S\n";
    cout << "ITEMS SORTED: " << wasteCount << endl;
    cout << "TIME COMPLEXITY: O(n log n)\n";
}
