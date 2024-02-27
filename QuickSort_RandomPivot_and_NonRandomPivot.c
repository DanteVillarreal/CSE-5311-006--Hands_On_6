//This is the quicksort impelementing both random and last element pivots. 




#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swapElements(int* firstElement, int* secondElement)
{
    int temporary = *firstElement;
    *firstElement = *secondElement;
    *secondElement = temporary;
}

int partitionArray(int array[], int lowIndex, int highIndex, int isRandomPivot)
{
    int pivotIndex;
    if (isRandomPivot)
    {
        pivotIndex = lowIndex + rand() % (highIndex - lowIndex);
    }
    else
    {
        pivotIndex = highIndex; // Non-random pivot is the last element
    }
    swapElements(&array[pivotIndex], &array[highIndex]);
    int pivot = array[highIndex];
    int i = (lowIndex - 1);

    for (int j = lowIndex; j <= highIndex - 1; j++)
    {
        if (array[j] < pivot)
        {
            i++;
            swapElements(&array[i], &array[j]);
        }
    }
    swapElements(&array[i + 1], &array[highIndex]);
    return (i + 1);
}

void quicksortArray(int array[], int lowIndex, int highIndex, int isRandomPivot)
{
    if (lowIndex < highIndex)
    {
        int partitionIndex = partitionArray(array, lowIndex, highIndex, isRandomPivot);
        quicksortArray(array, lowIndex, partitionIndex - 1, isRandomPivot);
        quicksortArray(array, partitionIndex + 1, highIndex, isRandomPivot);
    }
}

int main() {
    srand(time(NULL)); // Seed the random number generator

    int array_sizes[] = {10, 50, 100, 250, 500, 1250, 3000, 6250, 9000, 15000, 
    18000, 22000, 25000, 27000, 30000};
    int num_arrays = sizeof(array_sizes) / sizeof(array_sizes[0]);

    for (int i = 0; i < num_arrays; i++) {
        // Generate a new array for each case and each sorting operation
        for (int isRandom = 0; isRandom <= 1; isRandom++) {
            int* arr_best = malloc(array_sizes[i] * sizeof(int));
            int* arr_worst = malloc(array_sizes[i] * sizeof(int));
            int* arr_avg = malloc(array_sizes[i] * sizeof(int));

            for (int j = 0; j < array_sizes[i]; j++) {
                arr_best[j] = j; // Best-case: array is already sorted
                arr_worst[j] = array_sizes[i] - j; // Worst-case: array is sorted in reverse order
                arr_avg[j] = rand() % (2 * array_sizes[i]); // Average-case: random numbers between 0 and the size of the array * 2
            }

            // Time the pivot version for each case
            clock_t start = clock();
            quicksortArray(arr_best, 0, array_sizes[i] - 1, isRandom);
            clock_t end = clock();
            double time_best = ((double) (end - start)) / CLOCKS_PER_SEC;

            start = clock();
            quicksortArray(arr_worst, 0, array_sizes[i] - 1, isRandom);
            end = clock();
            double time_worst = ((double) (end - start)) / CLOCKS_PER_SEC;

            start = clock();
            quicksortArray(arr_avg, 0, array_sizes[i] - 1, isRandom);
            end = clock();
            double time_avg = ((double) (end - start)) / CLOCKS_PER_SEC;

            printf("Array size %d (%s Pivot): Best-case time = %.6f, Worst-case time = %.6f, Average-case time = %.6f\n", array_sizes[i], isRandom ? "Random" : "Non-Random", time_best, time_worst, time_avg);

            free(arr_best);
            free(arr_worst);
            free(arr_avg);
        }
    }

    return 0;
}
