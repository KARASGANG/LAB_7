#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "footballer.h"

int sort_order = 1; // 1 для возрастающего порядка, -1 для убывающего

const char* fullNames[] = {"Mukhin Jaromir", "Prytkov Roman", "Slastnikov Sergey", "Bober Stanislav", "Shchur Lev", "Kochetkov Yuri", "Volkova Tatiana"};
const char* clubNames[] = {"MIEM", "FCS", "MSU", "VSU", "MIPT", "MISIS", "ITMO"};
const char* positions[] = {"forward", "midfielder", "defender", "goalkeeper"};

void generateFootballer(Footballer *f) {
    strcpy(f->fullName, fullNames[rand() % 7]);
    strcpy(f->clubName, clubNames[rand() % 7]);
    strcpy(f->position, positions[rand() % 4]);
    f->age = 18 + rand() % 23;
    f->matchesPlayed = rand() % 100;
    f->goalsScored = rand() % 50;
}

void printFootballers(Footballer arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%-20s | %-20s | %-10s | Age: %2d | Matches: %3d | Goals: %2d\n",
               arr[i].fullName, arr[i].clubName, arr[i].position,
               arr[i].age, arr[i].matchesPlayed, arr[i].goalsScored);
    }
}

int compareFootballers(const Footballer *a, const Footballer *b) {
    int result = strcmp(a->fullName, b->fullName);
    if (result != 0) return result * sort_order;

    result = strcmp(a->clubName, b->clubName);
    if (result != 0) return result * sort_order;

    result = strcmp(a->position, b->position);
    if (result != 0) return result * sort_order;

    result = a->age - b->age;
    if (result != 0) return result * sort_order;

    result = a->matchesPlayed - b->matchesPlayed;
    if (result != 0) return result * sort_order;

    result = a->goalsScored - b->goalsScored;
    return result * sort_order;
}

void insertionSort(Footballer arr[], int n) {
    for (int i = 1; i < n; i++) {
        Footballer key = arr[i];
        int j = i - 1;
        while (j >= 0 && compareFootballers(&arr[j], &key) > 0) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void merge(Footballer arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    Footballer *L = malloc(n1 * sizeof(Footballer));
    Footballer *R = malloc(n2 * sizeof(Footballer));

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (compareFootballers(&L[i], &R[j]) <= 0) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSort(Footballer arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void mergeSortWrapper(Footballer arr[], int n) {
    mergeSort(arr, 0, n - 1);
}

void heapify(Footballer arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && compareFootballers(&arr[left], &arr[largest]) > 0)
        largest = left;

    if (right < n && compareFootballers(&arr[right], &arr[largest]) > 0)
        largest = right;

    if (largest != i) {
        Footballer temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heapSort(Footballer arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        Footballer temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

double measureSortingTime(void (*sortFunc)(Footballer[], int), Footballer arr[], int n) {
    Footballer *arr_copy = malloc(n * sizeof(Footballer));
    memcpy(arr_copy, arr, n * sizeof(Footballer));
    clock_t start = clock();
    sortFunc(arr_copy, n);
    clock_t end = clock();
    free(arr_copy);
    return (double)(end - start) / CLOCKS_PER_SEC;
}

void printResults(const char *fullName, double time) {
    printf("%-33s | %.6f sec\n", fullName, time);
}