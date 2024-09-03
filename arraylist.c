#include "arraylist.h"

const size_t ARRAYLIST_DEFAULT_CAPACITY = 16;

ArrayList *arraylist_Create(size_t element_size)
{
	ArrayList *list = malloc(sizeof(ArrayList));
	if (!list) {
		return NULL;
	}
	list->capacity = ARRAYLIST_DEFAULT_CAPACITY;
	list->num_elements = 0;
	list->element_size = element_size;
	list->data = malloc(element_size * ARRAYLIST_DEFAULT_CAPACITY);
	if (!list->data) {
		return NULL;
	}
	return list;
}

int arraylist_Append(ArrayList *list, void *element)
{
	if (list->num_elements >= list->capacity) {
		if (arraylist_Expand(list)) {
			return 1;
		}
	}
	memcpy((char*) list->data + list->element_size * list->num_elements, element, list->element_size);
	list->num_elements++;
	return 0;
}

void *arraylist_At(const ArrayList *list, size_t index)
{
	void *element = NULL;
	if (list->num_elements <= index) {
		return NULL; // index out of bounds
	}
	memcpy(element, (char*) list->data + index * list->element_size, list->element_size);
	return element;
}

int arraylist_UpdateAt(ArrayList *list, size_t index, void *value)
{
	if (list->num_elements < index) {
		return 1; // index out of bounds
	} else if (list->num_elements == index) {
		return arraylist_Append(list, value);
	}
	memcpy((char*) list->data + index * list->element_size, value, list->element_size);
	return 0;
}

int arraylist_RemoveAt(ArrayList *list, size_t index)
{
	if (list->num_elements <= index) {
		return 1; // index out of bounds
	}
	size_t i = index;
	size_t j = index + 1;
	// move everything after <index> down by one
	while (j < list->num_elements) {
		size_t size = list->element_size;
		memcpy((char*) list->data + i * size, (char*) list->data + j * size, size);
		++i;
		++j;
	}
	list->num_elements--;
	return 0;
}

int arraylist_Expand(ArrayList *list)
{
	void *temp = realloc(list->data, 2 * list->capacity * list->element_size);
	if (temp) {
		list->capacity *= 2;
		list->data = temp;
		return 0;
	} else {
		return 1;
	}
}

void arraylist_Destroy(ArrayList *list)
{
	if (list) {
		free(list->data);
		free(list);
	}
}