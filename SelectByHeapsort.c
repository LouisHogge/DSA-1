/* ========================================================================= *
 * SelectByHeapsort
 * Implementation of the selection algorithm using heapsort
 * ========================================================================= */

#include <stddef.h>
#include "Select.h"

static void heapSort(int* array, int length);
static void buildMaxHeap(int* array, int length);
static void maxHeapify(int* array, int length, int start_node);
static void swap(int* array, int firstIndex, int lastIndex);

int select(int* array, size_t length, size_t k)
{
    heapSort(array, (int)length);

    return array[k];
}

static void heapSort(int* array, int length)
{
    buildMaxHeap(array, length);

    for (int i = length-1; i>=0; i--)
    {
        swap(array, 0, i);
        maxHeapify(array, i, 0);
    }
}

static void buildMaxHeap(int* array, int length)
{
    for (int i = (length/2)-1; i>=0; i--)
        maxHeapify(array, length, i);
}

static void maxHeapify(int* array, int length, int start_node)
{
    int largest = start_node;
    int left_child = (2*start_node)+1;
    int right_child = (2*start_node)+2;

    if (left_child < length && array[left_child] > array[largest])
        largest = left_child;

    if (right_child < length && array[right_child] > array[largest])
        largest = right_child;

    if (largest != start_node)
    {
        swap(array, start_node, largest);
        maxHeapify (array, length, largest);
    }
}

static void swap(int* array, int firstIndex, int lastIndex)
{
    int intermediate = array[firstIndex];
    array[firstIndex] = array[lastIndex];
    array[lastIndex] = intermediate;
}
