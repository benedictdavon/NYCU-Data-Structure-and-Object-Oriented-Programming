#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>

using namespace std;

void swapNum(int* num1, int* num2) {
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

void heapify(vector<int> &arr, int n, int i) {
    // Find largest between root, left child and right child
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    // Swap num, check if root is not the largest then heapify again
    if (largest != i) {
        swapNum(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int> &arr, int n) {
    // Make the heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Loop through each element from the heap
    for (int i = n - 1; i > 0; i--) {
        // Swap current root with the end
        swapNum(&arr[0], &arr[i]);
        // Heapify again
        heapify(arr, i, 0);
    }
}

// Partition function place the pivot in the correct position
// then it moves smaller value to it's left and bigget value to it's right
int partition(vector<int> &arr, int low, int high)
{
    int pivot = arr[high]; // pivot
    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high - 1; j++)
        if (arr[j] <= pivot) {
            i++; 
            swapNum(&arr[i], &arr[j]);
        }
    
    swapNum(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Generate random pivot and call the partition function
int partition_r(vector<int> &arr, int low, int high)
{
    srand(time(NULL));
    int random = low + rand() % (high - low); // Generate random number between low and high

    swapNum(&arr[random], &arr[high]);

    return partition(arr, low, high);
}

void quickSort(vector<int> &arr, int low, int high)
{
    if (low < high) {
        int pi = partition_r(arr, low, high); // pi -> partition index

        // Sort element before the partition and after the partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void PrintArray(vector<int>& array) {
    for (int i = 0; i < array.size(); i++) {
        cout << array[i] << " ";
    }
    cout << std::endl;
}

int main() {
    std::fstream file;
    file.open("input2.txt");

    int times = 0;
    file >> times;

    for (int t = 0; t < times; t++) {
        int size = 0;
        file >> size;

        std::vector<int> array1;
        std::vector<int> array2;

        for (int i = 0; i < size; i++) {
            int x;
            file >> x;
            array1.push_back(x);
            array2.push_back(x);
        }

        heapSort(array1, array1.size());
        cout << "Max Heap Sort \t: ";
        PrintArray(array1);

        quickSort(array2, 0, array2.size()-1);
        cout << "Quick Sort \t: ";
        PrintArray(array2);
        cout << endl;
    }
    system("pause");
    return 0;
}