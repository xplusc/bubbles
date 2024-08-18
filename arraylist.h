/**
 * The Array List. This data structure stores an array of data and
 * automatically expands its capacity when needed.
 */

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stdlib.h>
#include <string.h>

extern const size_t ARRAYLIST_DEFAULT_CAPACITY;

struct array_list {
	void  *data;
	size_t capacity;
	size_t num_elements;
	size_t element_size;
};
typedef struct array_list ArrayList;

/**
 * Create an ArrayList to store elements of the specified size.
 * Capacity defaults to ARRAYLIST_DEFAULT_CAPACITY.
 */
ArrayList *arraylist_Create(size_t);

/**
 * Append the given element to the list. Requires a pointer to the ArrayList
 * and to the element. Automatically expands the ArrayList's capacity
 * if adding the element would exceed its current capacity.
 * Returns 1 if an error occurred while reallocating memory.
 */
int arraylist_Append(ArrayList*, void*);

/**
 * Expand an ArrayList's capacity by doubling it with realloc().
 * Returns 1 if an error occurred while reallocating memory.
 */
int arraylist_Expand(ArrayList*);

/**
 * Free the resources used by the specified ArrayList.
 */
void arraylist_Destroy(ArrayList*);

#endif // ARRAYLIST_H