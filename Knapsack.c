#include <stdio.h>
#include <stdlib.h>

double* calculate_ratios(int *weights, int *values, int num) {
    double *ratios = malloc(num * sizeof(double));
    for (int i = 0; i < num; i++) {
        ratios[i] = (double)values[i] / weights[i];
    }
    return ratios;
}

void selection_sort_value(double *arr, int *sorted_index, int num) {
    for (int i = 0; i < num - 1; i++) {
        int max = i;
        for (int j = i + 1; j < num; j++) {
            if (arr[j] > arr[max]) {
                max = j;
            }
        }
        // Swap ratio values
        double temp = arr[max];
        arr[max] = arr[i];
        arr[i] = temp;

        // Swap corresponding indices in sorted_index array
        int temp_index = sorted_index[max];
        sorted_index[max] = sorted_index[i];
        sorted_index[i] = temp_index;
    }
}

void selection_sort_weight(int *arr, int *sorted_index, int num) {
    for (int i = 0; i < num - 1; i++) {
        int max = i;
        for (int j = i + 1; j < num; j++) {
            if (arr[j] > arr[max]) {
                max = j;
            }
        }
        // Swap ratio values
        double temp = arr[max];
        arr[max] = arr[i];
        arr[i] = temp;

        // Swap corresponding indices in sorted_index array
        int temp_index = sorted_index[max];
        sorted_index[max] = sorted_index[i];
        sorted_index[i] = temp_index;
    }
}

void max_value(int *weights, int *values, int num, int capacity) {
    double total_value = 0;
    double *ratios = calculate_ratios(weights, values, num);

    int sorted_index[num];
    for (int i = 0; i < num; i++) {
        sorted_index[i] = i;
    }

    selection_sort_value(ratios, sorted_index, num);

    int fill = 0;
    double overall_value = 0;

    printf("The used items are: \n");
    for (int i = 0; i < num; i++) {
        if (fill + weights[sorted_index[i]] <= capacity) {
            total_value = values[sorted_index[i]];
            fill += weights[sorted_index[i]];
        } else if (fill + weights[sorted_index[i]] > capacity) {
            total_value = ratios[sorted_index[i]] * (capacity - fill);
            printf("Remaining Capacity filled with Item %d\n", sorted_index[i] + 1);
            fill = capacity;
        } else{
            printf("Capacity full\n");
            break;
        }
        printf("Item %d: Value: %.2f\n", sorted_index[i] + 1, total_value); // Adding 1 to match item numbering
        overall_value += total_value;
    }
    printf("Overall Value is: %.2f\n", overall_value);

    free(ratios);
}

void max_weight(int *weights, int *values, int num, int capacity) {
    // Create a copy of weights and values arrays to preserve the original
    int sorted_weights[num];
    int sorted_values[num];
    int sorted_index[num];
    for (int i = 0; i < num; i++) {
        sorted_weights[i] = weights[i];
        sorted_values[i] = values[i];
        sorted_index[i] = i;
    }
	
	selection_sort_weight(sorted_weights, sorted_index, num);
    // Fill the capacity using the highest weight items first
    int fill = 0;
    double overall_value = 0;
    printf("The used items are: \n");
    for (int i = 0; i < num; i++) {
        double total_value = 0;
        if (fill + sorted_weights[i] < capacity) {
            total_value = sorted_weights[i] * (double)sorted_values[i] / weights[i];
            fill += sorted_weights[i];
        } else if (fill + sorted_weights[i] > capacity) {
            total_value = (capacity - fill) * (double)sorted_values[i] / weights[i];
            printf("Remaining Capacity filled with Item %d\n", sorted_index[i] + 1);
            fill = capacity;
        } else  if (fill + weights[sorted_index[i]] == capacity){
            printf("Capacity full\n");
            break;
        }
        printf("Item %d: Weight: %d, Value: %.2f\n", sorted_index[i] + 1, sorted_weights[i], total_value);
        overall_value += total_value;
    }
    printf("Overall Value is: %.2f\n", overall_value);
}


int main() {
    // Variables for user input
    int capacity;
    int num; // num of items

    // User input prompt
    printf("Enter the maximum capacity: ");
    scanf("%d", &capacity);
    printf("Enter number of items: ");
    scanf("%d", &num);

    // Arrays to store weights and values for each item
    int weight[num];
    int value[num];

    // Input size and value for each item
    printf("Enter size and value for each item: \n");
    for (int i = 0; i < num; i++) {
        printf("\nItem %d: \n", i + 1);
        printf("Weight: ");
        scanf("%d", &weight[i]);
        printf("Value: ");
        scanf("%d", &value[i]);
    }

    // Find the items to fill the capacity using max_value function
    printf("\nUsing max_value function:\n");
    max_value(weight, value, num, capacity);

    printf("\n");

    // Find the items to fill the capacity using max_weight function
    printf("\nUsing max_weight function:\n");
    max_weight(weight, value, num, capacity);

    return 0;
}
