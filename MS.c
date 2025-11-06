#include <stdio.h>
#include <stdlib.h>

// Function to merge two sorted sub-arrays (used repeatedly in the DBMS merge phase)
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    int L[n1], R[n2];

    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temp arrays back into arr[left...right]
    i = 0; // Initial index of first sub-array
    j = 0; // Initial index of second sub-array
    k = left; // Initial index of merged sub-array

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Main function that sorts arr[left...right] using merge()
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        // Same as (left + right) / 2, but avoids overflow for large left and right
        int mid = left + (right - left) / 2;

        // Sort first and second halves (the divide/sort phase in DBMS)
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves (the combine/merge phase)
        merge(arr, left, mid, right);
    }
}

// Function to print an array
void printArray(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Driver program to test the code
int main() {
    // An example array (representing a chunk of data from a large database table)
    int arr[] = {70, 50, 30, 10, 20, 40, 60};
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    printf("Original array (representing a chunk of data):\n");
    printArray(arr, arr_size);

    // Apply Merge Sort
    mergeSort(arr, 0, arr_size - 1);

    printf("\nSorted array (representing the sorted chunk):\n");
    printArray(arr, arr_size);
    return 0;
}
