# cs210-assignment03
## Code
```cpp
/*AI Disclose:
I used AI to help me understand each sorting method,
and learn how to write an algorithm for each sorting method.
I also used AI to learn how to do benchmark using chrono library
*/
#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>

using namespace std;
using namespace chrono;

bool isSorted(const vector<int>& values){
    for (int i = 1; i < values.size(); i++) {
        if (values[i - 1] > values[i]) {
            return false;
        }
    }
    return true;
}

void bubbleSort(vector<int>& values) {
    // Rounds
    for (int i = 0; i < values.size() - 1; i++) {
        // Move the indices that are comparing
        for (int j = 0; j < values.size() - 1 - i; j++) {
            // Compare the current value and the value in next index
            if (values[j] > values[j + 1]) {
                int temp = values[j];
                values[j] = values[j + 1];
                values[j + 1] = temp;
            }
        }
    }
}

void selectionSort(vector<int>& values) {
    for (int i = 0; i < values.size() - 1; i++) {
        int smallest = i;
        // Compare the value in next index of i
        for (int j = i + 1; j < values.size(); j++) {
            // if the value is smaller than the value in smallest then set it to j
            if (values[j] < values[smallest]) {
                smallest = j;
            }
        }
        //swap the value in current index with the smallest value
        int temp = values[i];
        values[i] = values[smallest];
        values[smallest] = temp;
    }
}

void insertionSort(vector<int>& values) {
    for (int i = 1; i < values.size(); i++) {
        //save the current number
        int cur = values[i];
        //the value to the left of the current value
        int j = i - 1;
        while (j >= 0 && values[j] > cur) {
            values[j + 1] = values[j];
            j--; // to stop the while loop
        }
        values[j + 1] = cur;
    }
}

int quickSortHelper(vector<int>& values, int low, int high) {
    int middle = low + (high - low) / 2;
    int pivot = values[middle];
    bool done = false;
    while (!done) {
        while (values[low] < pivot) {
            low++;
        }
        while (pivot < values[high]) {
            high--;
        }
        if (low >= high) {
            done = true;
        } else{
            int temp = values[low];
            values[low] = values[high];
            values[high] = temp;

            low++;
            high--;
        }
    }
    return high;
}

void quickSortR(vector<int>& values, int low, int high) {
    if (high <= low) {
        return;
    }
    int split = quickSortHelper(values, low, high);
    quickSortR(values, low, split);
    quickSortR(values, split + 1, high);
}

void quickSort(vector<int>& values) {
    quickSortR(values, 0, values.size() - 1);
}

double benchmark(void (*sortFunction)(vector<int>&), const vector<int>& orginal) {
    double totalTime = 0;

    // Run 5 times
    for (int i = 0; i < 5; i++) {
        // A copy of the orginal vector
        vector<int> values = orginal;
        auto start = high_resolution_clock:: now();
        sortFunction(values);
        auto end = high_resolution_clock::now();
        double time = duration<double, milli>(end - start).count();
        totalTime = totalTime + time;
        //Print each run's time count
        cout << "Run " << i + 1 << ": "
             << time << " ms" << endl;
        if (!isSorted(values)) {
            cout << "ERROR: It is not sorted" << endl;
        }
    }
    double average = totalTime / 5;
    cout << "Average Time: " << average << " ms" << endl;
    return average;
}

int main() {
    vector<int> sizes = {1000, 5000, 10000};
    for (int s = 0; s < sizes.size(); s++) {
        int size = sizes[s];
        vector<int> randomValues(size);
        vector<int> sortedValues(size);
        vector<int> reverseValues(size);
        // Create random input
        for (int i = 0; i < size; i++) {
            randomValues[i] = rand() % 10000;
        }
        // Create sorted input
        for (int i = 0; i < size; i++) {
            sortedValues[i] = i;
        }
        // Create reverse sorted input
        for (int i = 0; i < size; i++) {
            reverseValues[i] = size - i;
        }
        cout << "\n-------" << endl;
        cout << "Size: " << size << endl;
        cout << "-------" << endl;

        // Random input
        cout << "\nRandom Input" << endl;
        // Bubble Sort Run Time
        cout << "\nBubble Sort" << endl;
        benchmark(bubbleSort, randomValues);
        // Selection Sort Run Time
        cout << "\nSelection Sort" << endl;
        benchmark(selectionSort, randomValues);
        // Insertion Sort Run Time
        cout << "\nInsertion Sort" << endl;
        benchmark(insertionSort, randomValues);
        // Quick Sort Run Time
        cout << "\nQuick Sort" << endl;
        benchmark(quickSort, randomValues);

        // Sorted input
        cout << "\nSorted Input" << endl;
        // Bubble Sort Run Time
        cout << "\nBubble Sort" << endl;
        benchmark(bubbleSort, sortedValues);
        // Selection Sort Run Time
        cout << "\nSelection Sort" << endl;
        benchmark(selectionSort, sortedValues);
        // Insertion Sort Run Time
        cout << "\nInsertion Sort" << endl;
        benchmark(insertionSort, sortedValues);
        // Quick Sort Run Time
        cout << "\nQuick Sort" << endl;
        benchmark(quickSort, sortedValues);

        // Reverse sorted input
        cout << "\nReverse Input" << endl;
        // Bubble Sort Run Time
        cout << "\nBubble Sort" << endl;
        benchmark(bubbleSort, reverseValues);
        // Selection Sort Run Time
        cout << "\nSelection Sort" << endl;
        benchmark(selectionSort, reverseValues);
        // Insertion Sort Run Time
        cout << "\nInsertion Sort" << endl;
        benchmark(insertionSort, reverseValues);
        // Quick Sort Run Time
        cout << "\nQuick Sort" << endl;
        benchmark(quickSort, reverseValues);
    }
    return 0;
}
```
## Output
```
-------
Size: 1000
-------

Random Input

Bubble Sort
Run 1: 7.7085 ms
Run 2: 8.27992 ms
Run 3: 7.63846 ms
Run 4: 6.65867 ms
Run 5: 6.35842 ms
Average Time: 7.32879 ms

Selection Sort
Run 1: 2.60075 ms
Run 2: 2.72363 ms
Run 3: 2.61575 ms
Run 4: 2.24492 ms
Run 5: 2.50738 ms
Average Time: 2.53848 ms

Insertion Sort
Run 1: 1.16171 ms
Run 2: 1.21554 ms
Run 3: 1.00942 ms
Run 4: 1.0255 ms
Run 5: 1.17304 ms
Average Time: 1.11704 ms

Quick Sort
Run 1: 0.109334 ms
Run 2: 0.100334 ms
Run 3: 0.095125 ms
Run 4: 0.092458 ms
Run 5: 0.090834 ms
Average Time: 0.097617 ms

Sorted Input

Bubble Sort
Run 1: 2.14404 ms
Run 2: 2.10012 ms
Run 3: 1.96854 ms
Run 4: 1.90542 ms
Run 5: 2.02346 ms
Average Time: 2.02832 ms

Selection Sort
Run 1: 2.01367 ms
Run 2: 1.74658 ms
Run 3: 1.8135 ms
Run 4: 1.95 ms
Run 5: 2.20621 ms
Average Time: 1.94599 ms

Insertion Sort
Run 1: 0.004917 ms
Run 2: 0.004958 ms
Run 3: 0.005083 ms
Run 4: 0.005041 ms
Run 5: 0.005041 ms
Average Time: 0.005008 ms

Quick Sort
Run 1: 0.027125 ms
Run 2: 0.026333 ms
Run 3: 0.0265 ms
Run 4: 0.025458 ms
Run 5: 0.025208 ms
Average Time: 0.0261248 ms

Reverse Input

Bubble Sort
Run 1: 3.97867 ms
Run 2: 4.46604 ms
Run 3: 3.89487 ms
Run 4: 4.19433 ms
Run 5: 3.851 ms
Average Time: 4.07698 ms

Selection Sort
Run 1: 2.06421 ms
Run 2: 2.0305 ms
Run 3: 1.98392 ms
Run 4: 1.91821 ms
Run 5: 2.10442 ms
Average Time: 2.02025 ms

Insertion Sort
Run 1: 2.27129 ms
Run 2: 1.9 ms
Run 3: 1.92013 ms
Run 4: 2.43279 ms
Run 5: 1.95679 ms
Average Time: 2.0962 ms

Quick Sort
Run 1: 0.02775 ms
Run 2: 0.026708 ms
Run 3: 0.026667 ms
Run 4: 0.026625 ms
Run 5: 0.026708 ms
Average Time: 0.0268916 ms

-------
Size: 5000
-------

Random Input

Bubble Sort
Run 1: 106.395 ms
Run 2: 98.8812 ms
Run 3: 96.9357 ms
Run 4: 97.1905 ms
Run 5: 97.0389 ms
Average Time: 99.2882 ms

Selection Sort
Run 1: 40.5516 ms
Run 2: 40.9535 ms
Run 3: 41.177 ms
Run 4: 41.3012 ms
Run 5: 41.1615 ms
Average Time: 41.029 ms

Insertion Sort
Run 1: 22.9693 ms
Run 2: 22.5078 ms
Run 3: 21.8717 ms
Run 4: 21.9319 ms
Run 5: 21.9078 ms
Average Time: 22.2377 ms

Quick Sort
Run 1: 0.53025 ms
Run 2: 0.51775 ms
Run 3: 0.505166 ms
Run 4: 0.502584 ms
Run 5: 0.50225 ms
Average Time: 0.5116 ms

Sorted Input

Bubble Sort
Run 1: 40.9919 ms
Run 2: 42.2595 ms
Run 3: 40.0017 ms
Run 4: 39.8597 ms
Run 5: 40.0328 ms
Average Time: 40.6291 ms

Selection Sort
Run 1: 40.1435 ms
Run 2: 40.215 ms
Run 3: 40.0352 ms
Run 4: 39.8998 ms
Run 5: 39.9973 ms
Average Time: 40.0582 ms

Insertion Sort
Run 1: 0.023875 ms
Run 2: 0.023625 ms
Run 3: 0.0235 ms
Run 4: 0.023459 ms
Run 5: 0.0235 ms
Average Time: 0.0235918 ms

Quick Sort
Run 1: 0.142042 ms
Run 2: 0.14625 ms
Run 3: 0.135791 ms
Run 4: 0.13575 ms
Run 5: 0.140917 ms
Average Time: 0.14015 ms

Reverse Input

Bubble Sort
Run 1: 87.877 ms
Run 2: 86.362 ms
Run 3: 87.9938 ms
Run 4: 89.2492 ms
Run 5: 87.6514 ms
Average Time: 87.8267 ms

Selection Sort
Run 1: 43.109 ms
Run 2: 42.4101 ms
Run 3: 41.797 ms
Run 4: 42.0995 ms
Run 5: 41.5761 ms
Average Time: 42.1983 ms

Insertion Sort
Run 1: 43.2374 ms
Run 2: 42.7353 ms
Run 3: 42.9278 ms
Run 4: 42.8565 ms
Run 5: 42.9873 ms
Average Time: 42.9489 ms

Quick Sort
Run 1: 0.149834 ms
Run 2: 0.145875 ms
Run 3: 0.146167 ms
Run 4: 0.150166 ms
Run 5: 0.145875 ms
Average Time: 0.147583 ms

-------
Size: 10000
-------

Random Input

Bubble Sort
Run 1: 390.735 ms
Run 2: 389.967 ms
Run 3: 390.326 ms
Run 4: 390.67 ms
Run 5: 392.124 ms
Average Time: 390.764 ms

Selection Sort
Run 1: 161.42 ms
Run 2: 162.042 ms
Run 3: 160.647 ms
Run 4: 159.591 ms
Run 5: 160.729 ms
Average Time: 160.886 ms

Insertion Sort
Run 1: 86.0407 ms
Run 2: 86.1341 ms
Run 3: 85.98 ms
Run 4: 85.6513 ms
Run 5: 85.8575 ms
Average Time: 85.9327 ms

Quick Sort
Run 1: 1.10912 ms
Run 2: 1.09296 ms
Run 3: 1.13288 ms
Run 4: 1.09654 ms
Run 5: 1.09442 ms
Average Time: 1.10518 ms

Sorted Input

Bubble Sort
Run 1: 160.526 ms
Run 2: 160.183 ms
Run 3: 160.238 ms
Run 4: 158.656 ms
Run 5: 159.305 ms
Average Time: 159.781 ms

Selection Sort
Run 1: 158.715 ms
Run 2: 158.972 ms
Run 3: 159.356 ms
Run 4: 158.956 ms
Run 5: 159.647 ms
Average Time: 159.129 ms

Insertion Sort
Run 1: 0.048 ms
Run 2: 0.047917 ms
Run 3: 0.047833 ms
Run 4: 0.047708 ms
Run 5: 0.047875 ms
Average Time: 0.0478666 ms

Quick Sort
Run 1: 0.317209 ms
Run 2: 0.340167 ms
Run 3: 0.346708 ms
Run 4: 0.375417 ms
Run 5: 0.29525 ms
Average Time: 0.33495 ms

Reverse Input

Bubble Sort
Run 1: 348.114 ms
Run 2: 346.136 ms
Run 3: 345.388 ms
Run 4: 346.205 ms
Run 5: 347.603 ms
Average Time: 346.689 ms

Selection Sort
Run 1: 167.808 ms
Run 2: 168.062 ms
Run 3: 168.023 ms
Run 4: 171.833 ms
Run 5: 171.27 ms
Average Time: 169.399 ms

Insertion Sort
Run 1: 173.751 ms
Run 2: 171.002 ms
Run 3: 172.045 ms
Run 4: 175.679 ms
Run 5: 173.015 ms
Average Time: 173.098 ms

Quick Sort
Run 1: 0.315209 ms
Run 2: 0.311917 ms
Run 3: 0.309125 ms
Run 4: 0.36425 ms
Run 5: 0.319417 ms
Average Time: 0.323984 ms
```
