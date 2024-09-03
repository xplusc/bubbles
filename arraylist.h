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
 * Return the element at <index> from <list>. Returns a null pointer
 * if <index> is out of bounds.
 */
void *arraylist_At(const ArrayList*, size_t);

/**
 * Update the element at <index> from <list> to be equal to <value>. Reduces
 * to arraylist_Append() if <index> is equal to the number of elements in
 * <list>. Returns 1 if <index> is out of bounds or if appending to <list>
 * failed.
 */
int arraylist_UpdateAt(ArrayList*, size_t, void*);

/**
 * Remove the element at <index> from <list>. Moves all elements after the
 * removed element down by one index and updates <num_elements>. MUST CLEAN
 * UP ELEMENT BEFORE REMOVAL OR THERE WILL BE MEMORY LEAKS. Returns 1 if
 * <index> is out of bounds.
 */
int arraylist_RemoveAt(ArrayList*, size_t);

/**
 * Expand an ArrayList's capacity by doubling it with realloc().
 * Returns 1 if an error occurred while reallocating memory.
 */
int arraylist_Expand(ArrayList*); // TODO: make static?

/**
 * Free the resources used by <list>.
 */
void arraylist_Destroy(ArrayList*);

#endif // ARRAYLIST_H