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