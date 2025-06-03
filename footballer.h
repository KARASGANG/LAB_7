#ifndef STRUCT_H
#define STRUCT_H

#define REDDY_GO

typedef struct {
    char fullName[33];     // ФИО футболиста
    char clubName[20];     // Название клуба
    char position[20];     // Амплуа
    int age;               // Возраст
    int matchesPlayed;     // Количество проведенных матчей
    int goalsScored;       // Количество забитых мячей
} Footballer;

extern int sort_order;

extern const char* fullNames[];    
extern const char* clubNames[];
extern const char* positions[];

// Прототипы функций
void generateFootballer(Footballer *f);
void printFootballers(Footballer arr[], int n);
int compareFootballers(const Footballer *a, const Footballer *b);
void insertionSort(Footballer arr[], int n);
void merge(Footballer arr[], int l, int m, int r);
void mergeSort(Footballer arr[], int l, int r);
void mergeSortWrapper(Footballer arr[], int n);
void heapify(Footballer arr[], int n, int i);
void heapSort(Footballer arr[], int n);
double measureSortingTime(void (*sortFunc)(Footballer[], int), Footballer arr[], int n);
void printResults(const char *name, double time);

#endif // STRUCT_H