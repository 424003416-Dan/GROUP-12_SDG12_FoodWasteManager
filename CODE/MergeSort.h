#ifndef MERGESORT_H
#define MERGESORT_H

#include "Utilities.h"
#include <string>

// CLASS FOR SORTING WASTE LOGS USING MERGE SORT ALGORITHM
// THIS CLASS STORES WASTE LOGS AND CAN SORT THEM BY QUANTITY
class MergeSort {
private:
    WasteLog wasteLogs[1000];  // ARRAY TO HOLD WASTE LOG RECORDS - MAX 1000
    int wasteCount;            // HOW MANY WASTE LOGS ARE CURRENTLY IN ARRAY

public:
    // CONSTRUCTOR - STARTS WITH NO WASTE LOGS
    MergeSort();

    // METHODS FOR ADDING AND GETTING WASTE LOGS

    // ADDS NEW WASTE LOG TO THE ARRAY
    void addLog(const WasteLog& log);

    // TELLS HOW MANY WASTE LOGS ARE IN ARRAY
    int getWasteCount() const;

    // MERGE SORT METHODS

    // SORTS ALL WASTE LOGS BY QUANTITY (SMALLEST TO LARGEST)
    void sortByQuantity();

    // SHOWS ALL WASTE LOGS IN SORTED ORDER
    void displaySorted() const;

    // FILE OPERATIONS

    // SAVES ALL WASTE LOGS TO A FILE
    void saveToFile(const std::string& filename);

    // LOADS WASTE LOGS FROM A FILE
    void loadFromFile(const std::string& filename);

    // PERFORMANCE TESTING

    // TESTS HOW FAST THE SORTING ALGORITHM WORKS
    void performanceTest() const;

private:
    // HELPER FUNCTIONS FOR MERGE SORT ALGORITHM

    // COMBINES TWO SORTED PARTS OF ARRAY INTO ONE SORTED PART
    void merge(WasteLog arr[], int left, int mid, int right);

    // RECURSIVE FUNCTION THAT DOES THE ACTUAL SORTING
    void mergeSort(WasteLog arr[], int left, int right);
};

#endif
