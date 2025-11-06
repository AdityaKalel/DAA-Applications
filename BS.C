#include <stdio.h>

// Recursive binary search function to find a product ID
int binarySearchProduct(int productIDs[], int low, int high, int targetID) {
    // Base case: If the search space is exhausted, the product is not found
    if (low > high) {
        return -1;
    }

    // Calculate the middle index
    int mid = low + (high - low) / 2;

    // If the targetID is found at the middle
    if (productIDs[mid] == targetID) {
        return mid;
    }

    // If the targetID is smaller than the middle element, search the left half
    else if (targetID < productIDs[mid]) {
        return binarySearchProduct(productIDs, low, mid - 1, targetID);
    }

    // If the targetID is larger than the middle element, search the right half
    else {
        return binarySearchProduct(productIDs, mid + 1, high, targetID);
    }
}

int main() {
    // In a real-world e-commerce system, this array would be a large,
    // dynamically managed database index, sorted by product ID.
    int productIDs[] = {101, 205, 312, 450, 567, 601, 720, 899, 945, 1024};
    int n = sizeof(productIDs) / sizeof(productIDs[0]);
    int targetID;
    int resultIndex;

    printf("Available Product IDs: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", productIDs[i]);
    }
    printf("\n\nEnter the Product ID to search for: ");
    scanf("%d", &targetID);

    // Perform the binary search
    resultIndex = binarySearchProduct(productIDs, 0, n - 1, targetID);

    // Output the result
    if (resultIndex != -1) {
        printf("\nOutput:\nProduct ID %d found at index %d (database record %d).\n", targetID, resultIndex, resultIndex + 1);
    } else {
        printf("\nOutput:\nProduct ID %d not found in the inventory.\n", targetID);
    }

    return 0;
}
