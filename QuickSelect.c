/* ========================================================================= *
 * QuickSelect
 * Implementation of the QuickSelect algorithm
 * ========================================================================= */

#include <stddef.h>
#include <stdlib.h>
#include "Select.h"
#include <time.h>

static int quickselect(int * array, int start, int end, int k, int total_length);
static int partition(int* array, int start, int end);
static void swap(int* array, int firstIndex, int lastIndex);

int select(int* array, size_t length, size_t k)
{
    srand(time(NULL));

    int quickselect_answer = quickselect(array, 0, (int)length-1, (int)k, (int)length);

    return quickselect_answer;
}

static int quickselect(int* array, int start, int end, int k, int total_length)
{
    int pivot = -1;
    int length = end-start+1;
    int quickselect_answer = -1;
    if (length>1)
    {
        // A random element is choosen as the pivot
        int r = (rand() % (end-start)) + start;
        swap(array, r, end);
        pivot = partition(array, start, end);
    }

    if(pivot == k) 
        quickselect_answer = array[pivot];
    else if(pivot < k)
    {
        // To manage specific case
        if (length == 2)
            quickselect_answer = array[pivot+1];
        // To manage specific case (length==1)
        else if (pivot+1 == end)
            quickselect_answer = array[pivot+1];
        // Base case
        else if (pivot+1<end)
            quickselect_answer = quickselect(array, pivot+1, end, k, total_length);
    }
    // Same comments here
    else
    {
        if (length == 2)
            quickselect_answer = array[pivot-1];
        else if (pivot-1 == start)
            quickselect_answer = array[pivot-1];
        else if (start<pivot-1)
            quickselect_answer = quickselect(array, start, pivot-1, k, total_length);
    }
    return quickselect_answer;
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

static void swap(int* array, int firstIndex, int lastIndex)
{
    int intermediate = array[firstIndex];
    array[firstIndex] = array[lastIndex];
    array[lastIndex] = intermediate;
}
