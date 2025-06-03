#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "footballer.h"

#ifdef REDDY_GO

int main() {
    srand(time(NULL));
    int sizes[] = {10, 100, 1000, 10000, 30000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("Comparison of sorting time:\n");
    printf("%-10s | %-15s | %-15s | %-15s\n", "Size", "Insertion", "Merge", "Heap");
    printf("--------------------------------------------------------------\n");

    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        Footballer *arr = malloc(n * sizeof(Footballer));
        for (int j = 0; j < n; j++) generateFootballer(&arr[j]);

        if (n <= 10) {
            printf("\nGenerated (unsorted) array of %d footballers:\n", n);
            printFootballers(arr, n);

            Footballer *copy1 = malloc(n * sizeof(Footballer));
            memcpy(copy1, arr, n * sizeof(Footballer));
            insertionSort(copy1, n);
            printf("\nSorted (insertionSort) array:\n");
            printFootballers(copy1, n);
            free(copy1);

            Footballer *copy2 = malloc(n * sizeof(Footballer));
            memcpy(copy2, arr, n * sizeof(Footballer));
            mergeSortWrapper(copy2, n);
            printf("\nSorted (mergeSortWrapper) array:\n");
            printFootballers(copy2, n);
            free(copy2);

            Footballer *copy3 = malloc(n * sizeof(Footballer));
            memcpy(copy3, arr, n * sizeof(Footballer));
            heapSort(copy3, n);
            printf("\nSorted (heapSort) array:\n");
            printFootballers(copy3, n);
            free(copy3);
        }

        double t1 = measureSortingTime(insertionSort, arr, n);
        double t2 = measureSortingTime(mergeSortWrapper, arr, n);
        double t3 = measureSortingTime(heapSort, arr, n);

        printf("\n");
        printf("%-10d | %-15.6f | %-15.6f | %-15.6f\n", n, t1, t2, t3);

        free(arr);
    }

    return 0;
}

// Ветку #else оставил без изменений — она работает корректно

#else

int main() {
    srand(time(NULL));
    int sizes[] = {100, 1000, 10000, 50000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("Choose sorting algorithm:\n");
    printf("B - Insertion Sort\nE - Merge Sort\nG - Heap Sort\n> ");
    
    char algo;
    scanf(" %c", &algo);
    printf("Sorting order (1 for ascending, -1 for descending): ");
    scanf("%d", &sort_order);

    void (*sortFunction)(Footballer[], int) = NULL;
    switch(algo) {
        case 'B': sortFunction = insertionSort; break;
        case 'E': sortFunction = mergeSortWrapper; break;
        case 'G': sortFunction = heapSort; break;
        default: printf("Invalid choice!\n"); return 1;
    }

    FILE *csv_file = fopen("results/sort_results.csv", "w");
    if (!csv_file) {
        printf("Error creating file!\n");
        return 1;
    }

    if (ftell(csv_file) == 0) {
        fputs("\xEF\xBB\xBF", csv_file);
        fprintf(csv_file, "Algorithm;Order;Size;Time (sec)\n");
    }

    printf("\n%-10s | %-10s\n", "Size", "Time");
    printf("--------------------\n");

    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        Footballer *arr = malloc(n * sizeof(Footballer));

        for (int j = 0; j < n; j++) {
            generateFootballer(&arr[j]);
        }

        double time = measureSortingTime(sortFunction, arr, n);
        printf("%-10d | %-10.3f\n", n, time);
        fprintf(csv_file, "%c;%d;%d;%.3f\n", algo, sort_order, n, time);

        free(arr);
    }

    fclose(csv_file);
    printf("\nResults saved to sort_results.csv\n");

    return 0;
}

#endif
