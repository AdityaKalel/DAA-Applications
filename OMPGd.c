#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// A structure to represent a Min Heap Node for file sizes
struct MinHeapNode {
    int size;
};

// A structure to represent a Min Heap
struct MinHeap {
    int size;
    int capacity;
    struct MinHeapNode* arr;
};

// Function to create a min heap
struct MinHeap* createMinHeap(int capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->arr = (struct MinHeapNode*)malloc(minHeap->capacity * sizeof(struct MinHeapNode));
    return minHeap;
}

// Function to swap two heap nodes
void swapMinHeapNode(struct MinHeapNode* a, struct MinHeapNode* b) {
    struct MinHeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// The standard minHeapify function
void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->arr[left].size < minHeap->arr[smallest].size)
        smallest = left;

    if (right < minHeap->size && minHeap->arr[right].size < minHeap->arr[smallest].size)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->arr[smallest], &minHeap->arr[idx]);
        minHeapify(minHeap, smallest);
    }
}

// Function to check if size of heap is 1 or less
int isSizeOne(struct MinHeap* minHeap) {
    return (minHeap->size == 1);
}

// Function to extract minimum value from heap
struct MinHeapNode extractMin(struct MinHeap* minHeap) {
    struct MinHeapNode temp = minHeap->arr[0];
    minHeap->arr[0] = minHeap->arr[minHeap->size - 1];
    minHeap->size--;
    minHeapify(minHeap, 0);
    return temp;
}

// Function to insert a new node to min heap
void insertMinHeap(struct MinHeap* minHeap, int size) {
    minHeap->size++;
    int i = minHeap->size - 1;
    while (i && minHeap->arr[(i - 1) / 2].size > size) {
        minHeap->arr[i].size = minHeap->arr[(i - 1) / 2].size;
        i = (i - 1) / 2;
    }
    minHeap->arr[i].size = size;
}

// Function to build min heap
void buildMinHeap(struct MinHeap* minHeap) {
    int n = minHeap->size - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

// The main function to find the optimal merge cost
int optimalMergeCost(int files[], int n) {
    int total_cost = 0;
    struct MinHeap* minHeap = createMinHeap(n);

    // Insert all file sizes into the min heap
    for (int i = 0; i < n; ++i) {
        insertMinHeap(minHeap, files[i]);
    }

    // While there is more than one file in the heap
    while (!isSizeOne(minHeap)) {
        // Extract the two smallest file sizes
        struct MinHeapNode first = extractMin(minHeap);
        struct MinHeapNode second = extractMin(minHeap);

        // Calculate the cost of merging them
        int current_merge_cost = first.size + second.size;
        
        // Add the current merge cost to the total cost
        total_cost += current_merge_cost;

        // Insert the new merged file size back into the heap
        insertMinHeap(minHeap, current_merge_cost);
    }
    
    return total_cost;
}

// Driver program to test the function
int main() {
    // Example: Files with record lengths 20, 30, 10, 5, 30.
    int files[] = {20, 30, 10, 5, 30};
    int n = sizeof(files) / sizeof(files[0]);

    printf("File sizes: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", files[i]);
    }
    printf("\n");

    int min_comparisons = optimalMergeCost(files, n);
    printf("Minimum number of record moves (comparisons) for optimal merge pattern is %d\n", min_comparisons);

    return 0;
}
