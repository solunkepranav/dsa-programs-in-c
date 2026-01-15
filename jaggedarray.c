#include <stdio.h>
#include <stdlib.h>

int main() {
    int m = 8; // We want 8 rows of output
    
    // 1. Start with a NULL pointer. This is important!
    int* arr = NULL; 

    printf("Printing sequence using a single resizing 1D array:\n");

    for (int i = 0; i < m; i++) {
        int row_size = i + 1; // Row 0 -> size 1, Row 1 -> size 2, etc.

        // 2. Resize the array to fit the new row.
        //    We use a 'temp' pointer for safety.
        arr = realloc(arr, row_size * sizeof(int));
        
        // 3. Check if realloc was successful
        if (arr == NULL) {
            printf("Failed to reallocate memory!\n");
            free(arr); // Free the original block if realloc failed
            return 1;
        }
        
    

        // 5. Fill the *entire* array with the new sequence
        for (int j = 0; j < row_size; j++) {
            arr[j] = j + 1;
        }

        // 6. Print the current state of the array
        printf("Row %d: ", i);
        for (int j = 0; j < row_size; j++) {
            printf("%d ", arr[j]);
        }
        printf("\n");
    }

    // 7. Free the final, largest block of memory
    free(arr);

    return 0;



     m = 8; // Number of rows

    // 1. Allocate memory for 'm' row pointers
    int **arr = malloc(m * sizeof(int*));
    if (arr == NULL) {
        printf("Failed to allocate main array\n");
        return 1;
    }

    // --- 2. Create and Fill the Array ---
    printf("Allocating and filling array...\n");
    for (int i = 0; i < m; i++) {
        // Row 'i' will have 'i + 1' elements
        int row_size = i + 1;

        // Allocate memory for the current row
        arr[i] = malloc(row_size * sizeof(int));
        if (arr[i] == NULL) {
            printf("Failed to allocate row %d\n", i);
            // In a real app, you should free previously allocated rows
            return 1;
        }

        // Fill the current row
        for (int j = 0; j < row_size; j++) {
            // Fill with 1, 2, 3, ...
            arr[i][j] = j + 1;
        }
    }

    // --- 3. Print the Array ---
    printf("\nPrinting the jagged array:\n");
    for (int i = 0; i < m; i++) {
        int row_size = i + 1; // Get the size for this row
        
        printf("Row %d: ", i);
        for (int j = 0; j < row_size; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n"); // Newline for the next row
    }

    // --- 4. Free the Memory ---
    printf("\nFreeing memory...\n");
    // First, free each individual row
    for (int i = 0; i < m; i++) {
        free(arr[i]);
    }
    // Finally, free the array of pointers
    free(arr);

    return 0;
}