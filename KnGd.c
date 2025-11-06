#include <stdio.h>
#include <stdlib.h>

// Structure to represent an item with its value, weight, and value-to-weight ratio
struct Item {
    float value;
    float weight;
    float ratio;
};

// Comparison function for sorting items by ratio in descending order
int compareItems(const void* a, const void* b) {
    struct Item* itemA = (struct Item*)a;
    struct Item* itemB = (struct Item*)b;
    // We want descending order, so we can return > 0 if A's ratio is less than B's
    if (itemB->ratio > itemA->ratio) return 1;
    if (itemB->ratio < itemA->ratio) return -1;
    return 0;
}

// Function to solve the fractional knapsack problem
void fractionalKnapsack(float capacity, struct Item items[], int n) {
    int i;
    float totalValue = 0.0;
    float currentWeight = 0.0;

    // Calculate value-to-weight ratios
    for (i = 0; i < n; i++) {
        items[i].ratio = items[i].value / items[i].weight;
    }

    // Sort items based on their ratios in descending order
    qsort(items, n, sizeof(struct Item), compareItems);

    printf("Loading Plan:\n");
    for (i = 0; i < n; i++) {
        // If the entire item can be added
        if (currentWeight + items[i].weight <= capacity) {
            currentWeight += items[i].weight;
            totalValue += items[i].value;
            printf("  Loaded full Item %d (Weight: %.2f, Value: %.2f)\n", i + 1, items[i].weight, items[i].value);
        } else {
            // If only a fraction of the item can be added
            float remainingCapacity = capacity - currentWeight;
            float fraction = remainingCapacity / items[i].weight;
            float valueToAdd = fraction * items[i].value;

            currentWeight += remainingCapacity;
            totalValue += valueToAdd;
            printf("  Loaded %.2f%% of Item %d (Weight: %.2f, Value: %.2f)\n", fraction * 100, i + 1, remainingCapacity, valueToAdd);
            break; // Knapsack is full
        }
    }

    printf("\nTotal Weight Loaded: %.2f\n", currentWeight);
    printf("Maximum Total Value: %.2f\n", totalValue);
}

int main() {
    // Example data: 3 items with values and weights
    struct Item items[] = {{60, 10, 0}, {100, 20, 0}, {120, 30, 0}};
    float capacity = 50.0;
    int n = sizeof(items) / sizeof(items[0]);

    fractionalKnapsack(capacity, items, n);

    return 0;
}
