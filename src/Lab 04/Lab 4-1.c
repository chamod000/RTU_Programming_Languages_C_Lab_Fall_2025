/*
 * week4_1_dynamic_array.c
 *233AEB022
 * chamod chirantha Dilshan
 * Description:
 *   Demonstrates creation and usage of a dynamic array using malloc.
 *   Students should allocate memory for an integer array, fill it with data,
 *   compute something (e.g., average), and then free the memory.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    int *arr = NULL;

    // Ask user for number of elements
    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid size.\n");
        return 1;
    }

    // Allocate memory for n integers using malloc
    arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Read n integers from user input
    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("Invalid input.\n");
            free(arr);  // Free allocated memory before exit
            return 1;
        }
    }

    // Compute sum and average
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    float average = (float)sum / n;

    // Print the results
    printf("Sum = %d\n", sum);
    printf("Average = %.2f\n", average);

    // Free allocated memory
    free(arr);

    return 0;
}
