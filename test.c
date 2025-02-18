#include "test.h"

#include <stdio.h>
#include <stdlib.h>

int SHOW_PASSES = 0;

int random_Range(int lower_bound, int upper_bound /* not inclusive */)
{
	if (lower_bound > upper_bound) {
		int temp = upper_bound;
		upper_bound = lower_bound;
		lower_bound = temp;
	}
	int modulus = upper_bound - lower_bound;
	if (modulus == 0)
		return lower_bound;
	return lower_bound + (rand() % modulus);
}

void test_Exists(const char *id, void *ptr)
{
	if (ptr == NULL) {
		fprintf(stderr, "FAIL: %s does not exist\n", id);
		fprintf(stderr, "ABORTING TEST\n");
		exit(0);
	} else if (SHOW_PASSES) {
		fprintf(stderr, "PASS: %s exists\n", id);
	}
}

void test_NotExists(const char *id, void *ptr)
{
	if (ptr != NULL)
		fprintf(stderr, "FAIL: %s exists\n", id);
	else if (SHOW_PASSES)
		fprintf(stderr, "PASS: %s does not exist\n", id);
}

void test_Equal(const char *id, int real, int expected)
{
	if (real != expected)
		fprintf(stderr, "FAIL: %s != %d (%d received)\n", id, expected, real);
	else if (SHOW_PASSES)
		fprintf(stderr, "PASS: %s == %d\n", id, expected);
}

void test_NotEqual(const char *id, int real, int expected)
{
	if (real == expected)
		fprintf(stderr, "FAIL: %s == %d (%d received)\n", id, expected, real);
	else if (SHOW_PASSES)
		fprintf(stderr, "PASS: %s != %d\n", id, expected);
}

void test_InRange(const char *id, int real, int lower_bound, int upper_bound /* not inclusive */)
{
	if (real < lower_bound || real >= upper_bound)
		fprintf(stderr, "FAIL: %s is not between %d and %d (%d received)\n", id, lower_bound, upper_bound, real);
	else if (SHOW_PASSES)
		fprintf(stderr, "PASS: %d <= %s < %d\n", lower_bound, id, upper_bound);
}

void test_NotInRange(const char *id, int real, int lower_bound, int upper_bound /* not inclusive */)
{
	if (real >= lower_bound && real < upper_bound)
		fprintf(stderr, "FAIL: %d <= %s < %d (%d received)\n", lower_bound, id, upper_bound, real);
	else if (SHOW_PASSES)
		fprintf(stderr, "PASS: %s is not between %d and %d\n", id, lower_bound, upper_bound);
}

arraylist_test_t arraylist_test_Create(int array_size)
{
	arraylist_test_t alt;
	alt.array_size = array_size;
	alt.array = malloc(array_size * sizeof(int));
	return alt;
}

arraylist_test_t arraylist_test_Copy(const arraylist_test_t *alt)
{
	if (!alt) {
		arraylist_test_t empty = {0};
		return empty;
	}
	arraylist_test_t new_alt;
	new_alt.array_size = alt->array_size;
	new_alt.array = malloc(alt->array_size * sizeof(int));
	for (int i = 0; i < alt->array_size; ++i) {
		new_alt.array[i] = alt->array[i];
	}
	return new_alt;
}

int arraylist_test_Destroy(arraylist_test_t *alt)
{
	if (!alt)
		return 1;
	if (alt->array) {
		free(alt->array);
		alt->array = NULL;
	}
	return 0;
}

int arraylist_test_FillRandom(arraylist_test_t *alt)
{
	if (!alt)
		return 1;
	if (!alt->array)
		return 1;
	for (int i = 0; i < alt->array_size; ++i) {
		alt->array[i] = random_Range(0, 10);
	}
	return 0;
}
