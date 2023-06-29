/* ========================================================================= *
 * Select
 * ========================================================================= */

#ifndef _SELECT_H_
#define _SELECT_H_

#include <stddef.h>


/* ------------------------------------------------------------------------- *
 * Return the value of the k-th smallest value (starting at 0) in an array 
 * of integers. The function may permute the elements in the array.
 *
 * PARAMETERS
 * array        The array to select from
 * length       Number of elements in the array
 * k            The rank of the element to select (an integer in {0,...,lenght-1})
 * 
 * RETURN
 * q            The k-th smallest element in the array
 * ------------------------------------------------------------------------- */
int select(int* array, size_t length, size_t k);


#endif // !_SELECT_H_
