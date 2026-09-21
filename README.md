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

//Check if the vector isSorted
bool isSorted(const vector<int>& values){
    for (int i = 1; i < values.size(); i++) {
        if (values[i - 1] > values[i]) {
            return false;
        }
    }
    return true;
}

//Bubble Sort
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

//Selection Sort
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

//Insertion Sort
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
    //Find middle
    int middle = low + (high - low) / 2;
    //Use the middle as the pivot value
    int pivot = values[middle];
    bool done = false;
    //while it is not done
    while (!done) {
        //Move low to the right while the value is smaller than the pivot
        while (values[low] < pivot) {
            low++;
        }
        //Move high to the left while the value is bigger than the pivot
        while (pivot < values[high]) {
            high--;
        }
        //Stop if low and high meet or cross
        if (low >= high) {
            done = true;
        } else{
            //Swap the value at high and low
            int temp = values[low];
            values[low] = values[high];
            values[high] = temp;
            //Move low right and high left
            low++;
            high--;
        }
    }
    //Return the value that uses to split
    return high;
}

void quickSortR(vector<int>& values, int low, int high) {
    if (high <= low) {
        return;
    }
    //Split the vector into two parts
    int split = quickSortHelper(values, low, high);
    //Sort the left side
    quickSortR(values, low, split);
    //Sort the right side
    quickSortR(values, split + 1, high);
}

void quickSort(vector<int>& values) {
    //start from first to last index
    quickSortR(values, 0, values.size() - 1);
}

//Benchmark
double benchmark(void (*sortFunction)(vector<int>&), const vector<int>& original) {
    double totalTime = 0;

    // Run 5 times
    for (int i = 0; i < 5; i++) {
        // A copy of the original vector
        vector<int> values = original;
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
Run 1: 7.08921 ms
Run 2: 6.44025 ms
Run 3: 6.22167 ms
Run 4: 5.97767 ms
Run 5: 5.06329 ms
Average Time: 6.15842 ms

Selection Sort
Run 1: 2.5195 ms
Run 2: 2.35887 ms
Run 3: 2.10508 ms
Run 4: 2.15721 ms
Run 5: 2.50913 ms
Average Time: 2.32996 ms

Insertion Sort
Run 1: 0.991 ms
Run 2: 1.09754 ms
Run 3: 1.08167 ms
Run 4: 1.08937 ms
Run 5: 1.21417 ms
Average Time: 1.09475 ms

Quick Sort
Run 1: 0.251125 ms
Run 2: 0.182875 ms
Run 3: 0.111834 ms
Run 4: 0.101458 ms
Run 5: 0.103958 ms
Average Time: 0.15025 ms

Sorted Input

Bubble Sort
Run 1: 2.10379 ms
Run 2: 1.83946 ms
Run 3: 1.86096 ms
Run 4: 2.21175 ms
Run 5: 2.26183 ms
Average Time: 2.05556 ms

Selection Sort
Run 1: 2.02467 ms
Run 2: 1.74842 ms
Run 3: 2.62779 ms
Run 4: 1.95646 ms
Run 5: 1.82563 ms
Average Time: 2.03659 ms

Insertion Sort
Run 1: 0.004959 ms
Run 2: 0.004916 ms
Run 3: 0.004875 ms
Run 4: 0.004875 ms
Run 5: 0.004875 ms
Average Time: 0.0049 ms

Quick Sort
Run 1: 0.029834 ms
Run 2: 0.025958 ms
Run 3: 0.025959 ms
Run 4: 0.025958 ms
Run 5: 0.025958 ms
Average Time: 0.0267334 ms

Reverse Input

Bubble Sort
Run 1: 4.71037 ms
Run 2: 4.24117 ms
Run 3: 4.95021 ms
Run 4: 4.36896 ms
Run 5: 4.35412 ms
Average Time: 4.52497 ms

Selection Sort
Run 1: 1.99362 ms
Run 2: 2.10167 ms
Run 3: 2.03683 ms
Run 4: 1.99796 ms
Run 5: 1.8905 ms
Average Time: 2.00412 ms

Insertion Sort
Run 1: 2.02771 ms
Run 2: 1.95112 ms
Run 3: 2.07258 ms
Run 4: 1.95946 ms
Run 5: 2.00062 ms
Average Time: 2.0023 ms

Quick Sort
Run 1: 0.02925 ms
Run 2: 0.029625 ms
Run 3: 0.066125 ms
Run 4: 0.107416 ms
Run 5: 0.029375 ms
Average Time: 0.0523582 ms

-------
Size: 5000
-------

Random Input

Bubble Sort
Run 1: 107.516 ms
Run 2: 102.119 ms
Run 3: 98.8868 ms
Run 4: 97.278 ms
Run 5: 96.6002 ms
Average Time: 100.48 ms

Selection Sort
Run 1: 40.4186 ms
Run 2: 40.0565 ms
Run 3: 40.2474 ms
Run 4: 40.2374 ms
Run 5: 40.0948 ms
Average Time: 40.2109 ms

Insertion Sort
Run 1: 22.0487 ms
Run 2: 22.2286 ms
Run 3: 21.9711 ms
Run 4: 21.7693 ms
Run 5: 21.8789 ms
Average Time: 21.9793 ms

Quick Sort
Run 1: 0.542166 ms
Run 2: 0.52275 ms
Run 3: 0.510833 ms
Run 4: 0.618334 ms
Run 5: 0.661375 ms
Average Time: 0.571092 ms

Sorted Input

Bubble Sort
Run 1: 40.6416 ms
Run 2: 39.647 ms
Run 3: 39.977 ms
Run 4: 39.67 ms
Run 5: 39.5528 ms
Average Time: 39.8977 ms

Selection Sort
Run 1: 39.8802 ms
Run 2: 39.6882 ms
Run 3: 39.5398 ms
Run 4: 41.1707 ms
Run 5: 41.1542 ms
Average Time: 40.2866 ms

Insertion Sort
Run 1: 0.023708 ms
Run 2: 0.023459 ms
Run 3: 0.023625 ms
Run 4: 0.023542 ms
Run 5: 0.0235 ms
Average Time: 0.0235668 ms

Quick Sort
Run 1: 0.140792 ms
Run 2: 0.139208 ms
Run 3: 0.1355 ms
Run 4: 0.1355 ms
Run 5: 0.1355 ms
Average Time: 0.1373 ms

Reverse Input

Bubble Sort
Run 1: 87.7547 ms
Run 2: 85.9575 ms
Run 3: 85.8395 ms
Run 4: 85.8153 ms
Run 5: 85.5684 ms
Average Time: 86.1871 ms

Selection Sort
Run 1: 41.9613 ms
Run 2: 41.6112 ms
Run 3: 41.6793 ms
Run 4: 41.5985 ms
Run 5: 41.5881 ms
Average Time: 41.6877 ms

Insertion Sort
Run 1: 43.2285 ms
Run 2: 42.9099 ms
Run 3: 42.8175 ms
Run 4: 42.7052 ms
Run 5: 42.7535 ms
Average Time: 42.8829 ms

Quick Sort
Run 1: 0.150375 ms
Run 2: 0.149292 ms
Run 3: 0.148167 ms
Run 4: 0.148625 ms
Run 5: 0.148208 ms
Average Time: 0.148933 ms

-------
Size: 10000
-------

Random Input

Bubble Sort
Run 1: 392.83 ms
Run 2: 386.667 ms
Run 3: 387.428 ms
Run 4: 393.723 ms
Run 5: 390.287 ms
Average Time: 390.187 ms

Selection Sort
Run 1: 159.86 ms
Run 2: 160.004 ms
Run 3: 158.724 ms
Run 4: 158.468 ms
Run 5: 158.386 ms
Average Time: 159.088 ms

Insertion Sort
Run 1: 85.6922 ms
Run 2: 85.4701 ms
Run 3: 85.3173 ms
Run 4: 85.2059 ms
Run 5: 85.3326 ms
Average Time: 85.4036 ms

Quick Sort
Run 1: 1.10821 ms
Run 2: 1.09304 ms
Run 3: 1.13721 ms
Run 4: 1.12604 ms
Run 5: 1.09942 ms
Average Time: 1.11278 ms

Sorted Input

Bubble Sort
Run 1: 158.821 ms
Run 2: 157.624 ms
Run 3: 157.776 ms
Run 4: 158.316 ms
Run 5: 158.208 ms
Average Time: 158.149 ms

Selection Sort
Run 1: 157.95 ms
Run 2: 157.698 ms
Run 3: 158.69 ms
Run 4: 157.894 ms
Run 5: 158.224 ms
Average Time: 158.091 ms

Insertion Sort
Run 1: 0.056667 ms
Run 2: 0.048834 ms
Run 3: 0.046875 ms
Run 4: 0.046917 ms
Run 5: 0.049792 ms
Average Time: 0.049817 ms

Quick Sort
Run 1: 0.28475 ms
Run 2: 0.283375 ms
Run 3: 0.283334 ms
Run 4: 0.284625 ms
Run 5: 0.409584 ms
Average Time: 0.309134 ms

Reverse Input

Bubble Sort
Run 1: 344.553 ms
Run 2: 346.422 ms
Run 3: 348.464 ms
Run 4: 343.26 ms
Run 5: 344.095 ms
Average Time: 345.359 ms

Selection Sort
Run 1: 166.111 ms
Run 2: 165.711 ms
Run 3: 165.988 ms
Run 4: 165.7 ms
Run 5: 165.991 ms
Average Time: 165.9 ms

Insertion Sort
Run 1: 170.468 ms
Run 2: 170.071 ms
Run 3: 169.941 ms
Run 4: 170.453 ms
Run 5: 170.015 ms
Average Time: 170.19 ms

Quick Sort
Run 1: 0.305167 ms
Run 2: 0.303625 ms
Run 3: 0.303542 ms
Run 4: 0.311167 ms
Run 5: 0.303583 ms
Average Time: 0.305417 ms
```
## Timing Table
|Size|Input|Bubble Sort (ms)|Selection Sort (ms)|Insertion Sort (ms)|Quick Sort (ms)|
|---|---|---|---|---|---|
|1000|Random|6.158|2.330|1.095|0.150|
|1000|Sorted|2.056|2.037|0.005|0.027|
|1000|Reverse|4.525|2.004|2.002|0.052|
|5000|Random|100.480|40.211|21.979|0.571|
|5000|Sorted|39.898|40.287|0.024|0.137|
|5000|Reverse|86.187|41.688|42.883|0.149|
|10000|Random|390.187|159.088|85.404|1.113|
|10000|Sorted|158.149|158.091|0.050|0.309|
|10000|Reverse|345.359|165.900|170.190|0.305|

Bubble sort has O(n²) best, average, and worst time because it always runs through the nested loops. Sorted input was still faster because no swaps were needed. Random and reverse input required more swaps, so they took longer.

Selection sort is O(n²) for the best, average, and worst cases. It always searches through the remaining values to find the smallest value. This can be seen in the results because random, sorted, and reverse inputs had similar runtimes.

Insertion sort has a best case of O(n) when the input is already sorted because the values do not need to move. Its average and worst cases are O(n²). Reverse-sorted input is the worst because each value may need to move through most of the vector. This is why sorted input was extremely fast while reverse input was much slower.

Quicksort has a best and average case of O(n log n) and a worst case of O(n²). My implementation uses the middle value as the pivot, which worked well for random, sorted, and reverse input in these tests. Quicksort was the fastest algorithm overall, especially as the input size became larger.

## Complexity
|Sorting Method|Best Case|Average|Worst Case|
|---|---|---|---|
|Bubble Sort|O(n²)|O(n²)|O(n²)|
|Selection Sort|O(n²)|O(n²)|O(n²)|
|Insertion Sort|O(n)|O(n²)|O(n²)|
|Quick Sort|O(n log n)|O(n log n)|O(n²)|
