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