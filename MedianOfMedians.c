/* ========================================================================= *
 * MedianOfMedians
 * Implementation of the median of medians selection algorithm
 * ========================================================================= */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "Select.h"

static int medianOfMedians(int *array, int start, int end);
static int* insertionSort(int* array, int length); 
static int** divide(int *array, int nb_sub_array, int start, int end);
static int median(int *array, int start, int end); 
static int getNumberSubArray(int length); 
static int quickselect(int * array, int start, int end, int k, int total_length); 
static void partition(int* array, int start, int end, int pivot);
static void swap(int* array, int firstIndex, int lastIndex);

int select(int* array, size_t length, size_t k)
{
    int quickselect_answer = quickselect(array, 0, (int)length-1, (int)k, (int)length);

    return quickselect_answer;
}

static int getNumberSubArray(int length)
{
    int nb_sub_array = length/5;

    //if something is left after division, there is another array of length € [1;4]
    if(length%5)
        nb_sub_array++;
    return nb_sub_array;
}

static int* insertionSort (int* array, int length)
{
    for (int j = 1; j<length; j++)
    {
        int key = array[j];
        int i = j-1;

        while (i>=0 && array[i] > key)
        {
            array[i+1] = array[i];
            i--;
        }
        array[i+1] = key;
    }
    return array;
}

static int median(int* array, int start, int end)
{
    int length = end-start+1;

    array = insertionSort(array, length);

    if (length%2 == 0)
        return array[start+(length/2)];
    else
        return array[start+((length+1)/2)-1];
}

/* Divides the array into arrays of length 5 and an array of length € [1;4]
   if the length is not a multiple of 5*/
static int** divide(int* array, int nb_sub_array, int start, int end)
{
    int length = end-start+1;

    // Creating the sub-arrays
    int** div_array = malloc(nb_sub_array*sizeof(int*));
    if (!(div_array))
    {
        fprintf(stderr, "Unable to allocate memory\n");
        free(div_array);
        return NULL;
    }
    for(int i=0; i<nb_sub_array; i++)
    {
        // Check if we have a last array of length € [1;4]
        if (length%5 != 0)
        {
            // Check if we are in the last array of length € [1;4]
            if (i == nb_sub_array-1)
            {
                div_array[i] = (int*)malloc((length%5)*sizeof(int));
                if(!div_array[i])
                {
                    fprintf(stderr, "Unable to allocate memory\n");
                    free(div_array);
                    return NULL;
                }
            }
            else
            {
                div_array[i] = (int*)malloc(5*sizeof(int));
                if(!div_array[i])
                {
                    fprintf(stderr, "Unable to allocate memory\n");
                    free(div_array);
                    return NULL;
                }
            }
        }
        else
        {
            div_array[i] = (int*)malloc(5*sizeof(int));
            if(!div_array[i])
            {
                fprintf(stderr, "Unable to allocate memory\n");
                free(div_array);
                return NULL;
            }
        }
    }

    // Filling the sub-arrays with the values of the prime array
    for(int i = 0, index = start ; i < nb_sub_array; i++) 
    {
        for(int j = 0; j < 5; j++)
        {
            // Check if we have a last array of length € [1;4]
            if (length%5 != 0)
            {
                // Check if we are in the last array of length € [1;4]
                if (i == nb_sub_array-1)
                {
                    // Verify the j in order to not put some values out of the array
                    if (j < length%5) 
                    {
                        div_array[i][j] = array[index];
                        index++;
                    }
                    else
                        continue;
                }
                else
                {
                    div_array[i][j] = array[index];
                    index++;
                }
            }
            else
            {
                div_array[i][j] = array[index];
                index++;
            }
        }
    }
    return div_array;
}

static int medianOfMedians(int *array, int start, int end)
{
    int length = end-start+1;
    int pivot = -1; 
    if(length<5)
        pivot = median(array, start, end);
    else
    {
        int nb_sub_array = getNumberSubArray(length); 
        int* median_array = malloc(sizeof(int)*nb_sub_array); 
        int** div_array = divide(array, nb_sub_array, start, end);
        
        for(int i = 0; i < nb_sub_array; i++)
        {
            // Check if we have a last array of length € [1;4]
            if (length%5 != 0)
            {
                // Check if we are in the last array of length € [1;4]
                if (i == nb_sub_array-1)
                    median_array[i] = median(div_array[i],0,(length%5)-1);
                else
                    median_array[i] = median(div_array[i],0,4);
            }
            else
                median_array[i] = median(div_array[i],0,4);
        }

        pivot = medianOfMedians(median_array, 0, nb_sub_array-1);

        free(median_array);
        for(int i = 0; i < nb_sub_array; i++)
            free(div_array[i]);
        free(div_array);

    }
    return pivot;
}

static int quickselect(int* array, int start, int end, int k, int total_length)
{
    int length = end-start+1;
    int quickselect_answer = -1;
    int tab_id_pivot = -1;

    int pivot = medianOfMedians(array, start, end);

    for(int i=start; i <= end; i++) 
    {
        if (array[i] == pivot)
            tab_id_pivot = i;
    }

    swap(array, end, tab_id_pivot);

    partition(array, start, end, pivot);

    for(int i=start; i <= end; i++) 
    {
        if (array[i] == pivot)
            tab_id_pivot = i;
    }
    
    if(tab_id_pivot == k)
        quickselect_answer = array[tab_id_pivot];
    else if(tab_id_pivot < k)
    {
        // To manage specific case
        if (length == 2)
            quickselect_answer = array[tab_id_pivot+1];
        // To manage specific case (length==1)
        else if (tab_id_pivot+1 == end)
            quickselect_answer = array[tab_id_pivot+1];
        // Base case
        else if (tab_id_pivot+1<end)
            quickselect_answer = quickselect(array, tab_id_pivot+1, end, k, total_length);
    }
    // Same comments here
    else
    {
        if (length == 2)
            quickselect_answer = array[tab_id_pivot-1];
        else if (tab_id_pivot-1 == start)
            quickselect_answer = array[tab_id_pivot-1];
        else if (start<tab_id_pivot-1)
            quickselect_answer = quickselect(array, start, tab_id_pivot-1, k, total_length);
    }
    return quickselect_answer; 
}

static void partition(int* array, int start, int end, int pivot)
{
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
}

static void swap(int* array, int firstIndex, int lastIndex)
{
    int intermediate = array[firstIndex];
    array[firstIndex] = array[lastIndex];
    array[lastIndex] = intermediate;
}
