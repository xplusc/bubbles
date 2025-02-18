#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "test.h"
#include "arraylist.h"

int main(int argc, char *argv[])
{	
	// initialize
	srand(time(NULL));
	SHOW_PASSES = 1;
	
	// arraylist test
	ArrayList *list = arraylist_Create(sizeof(arraylist_test_t));
	test_Exists("list", list);
	test_Exists("list->data", list->data);
	test_Equal("list->element_size", list->element_size, sizeof(arraylist_test_t));
	test_Equal("list->num_elements", list->num_elements, 0);
	test_Equal("list->capacity", list->capacity, 16);
	
	arraylist_test_t alt = arraylist_test_Create(random_Range(4, 16));
	arraylist_test_FillRandom(&alt);
	arraylist_Append(list, &alt);
	test_Equal("list->num_elements", list->num_elements, 1);
	test_InRange("list->data[0].array[0]", ((arraylist_test_t*) list->data)[0].array[0], 0, 10);
	
	alt = arraylist_test_Copy(&((arraylist_test_t*) list->data)[0]);
	alt.array[0] = random_Range(10, 20);
	arraylist_Append(list, &alt);
	test_Equal("list->num_elements", list->num_elements, 2);
	test_NotEqual("list->data[0].array[0]", ((arraylist_test_t*) list->data)[0].array[0], ((arraylist_test_t*) list->data)[1].array[0]);
	
	alt = arraylist_test_Copy(&((arraylist_test_t*) list->data)[0]);
	arraylist_test_Destroy(&((arraylist_test_t*) list->data)[1]);
	test_NotExists("list->data[1].array", ((arraylist_test_t*) list->data)[1].array);
	//fprintf(stderr, "list->data[1].array: %p\n", (void*) ((arraylist_test_t*) list->data)[1].array);
	//fprintf(stderr, "alt.array: %p\n", (void*) alt.array);
	arraylist_UpdateAt(list, 1, &alt);
	test_Equal("list->data[0].array[0]", ((arraylist_test_t*) list->data)[0].array[0], ((arraylist_test_t*) list->data)[1].array[0]);
	
	((arraylist_test_t*) list->data)[1].array[0] = random_Range(10, 20);
	test_NotInRange("list->data[0].array[0]", ((arraylist_test_t*) list->data)[0].array[0], 10, 20);
	arraylist_test_Destroy(&((arraylist_test_t*) list->data)[0]);
	arraylist_RemoveAt(list, 0);
	test_Equal("list->num_elements", list->num_elements, 1);
	test_InRange("list->data[0].array[0]", ((arraylist_test_t*) list->data)[0].array[0], 10, 20);
	
	for (int i = 0; i < 16; ++i) {
		alt = arraylist_test_Copy(&((arraylist_test_t*) list->data)[0]);
		arraylist_Append(list, &alt);
	}
	test_Exists("list->data", list->data);
	test_Equal("list->capacity", list->capacity, 32);
	test_Equal("list->num_elements", list->num_elements, 17);
	
	for (int i = list->num_elements - 1; i >= 0; --i) {
		arraylist_RemoveAt(list, i);
	}
	test_Equal("list->num_elements", list->num_elements, 0);
	
	arraylist_Destroy(&list);
	test_NotExists("list", list);
	
	return 0;
}
