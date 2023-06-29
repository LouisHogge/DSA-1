/* ========================================================================= *
 * SelectByQuicksort
 * Implementation of the selection algorithm using quicksort
 * ========================================================================= */

#include <stddef.h>
#include "Select.h"
#include <stdlib.h>
#include <time.h>

static void quickSort(int* array, int start, int end);
static int partition(int* array, int start, int end);
static void insertionSort(int* array, int start, int end);
static void swap(int* array, int firstIndex, int lastIndex);

int select(int* array, size_t length, size_t k)
{
    srand(time(NULL));

    quickSort(array, 0, (int)length-1);

    return array[k];
}

static void quickSort(int* array, int start, int end)
{
    /* When the size of the table is <=5 we use Insertionsort because Quicksort
       is too onerous for such table */
    if (start<end && end-start+1 <= 5)
        insertionSort(array, start, end);
    else if (start<end)
    {
        // A random element is choosen as the pivot
        int r = (rand() % (end-start)) + start; 
        swap(array, r, end); 

        int pivot = partition(array, start, end);

        quickSort(array, start, pivot-1);
        quickSort(array, pivot+1, end);
    }
}

static int partition(int* array, int start, int end)
{
    int pivot = array[end];
    int i = start-1;

    for (int j = start; j <= end-1; j++)
    {
        if (array[j] <= pivot)
        {
            i++;
            swap(array, i, j);
        }
    }
    swap(array, i+1, end);
    return i+1;
}

static void insertionSort(int* array, int start, int end)
{
    for (int j = start+1; j<end+1; j++)
    {
        int key = array[j];
        int i = j-1;

        while (i>=start && array[i] > key)
        {
            array[i+1] = array[i];
            i = i-1;
        }
        array[i+1] = key;
    }
}

static void swap(int* array, int firstIndex, int lastIndex)
{
    int intermediate = array[firstIndex];
    array[firstIndex] = array[lastIndex];
    array[lastIndex] = intermediate;
}
