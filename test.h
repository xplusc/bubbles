#ifndef TEST_H
#define TEST_H

extern int SHOW_PASSES;

int random_Range(int, int);
void test_Exists(const char*, void*);
void test_NotExists(const char*, void*);
void test_Equal(const char*, int, int);
void test_NotEqual(const char*, int, int);
void test_InRange(const char*, int, int, int);
void test_NotInRange(const char*, int, int, int);

struct arraylist_test_data {
	int  array_size;
	int *array;
};
typedef struct arraylist_test_data arraylist_test_t;

arraylist_test_t arraylist_test_Create(int);
arraylist_test_t arraylist_test_Copy(const arraylist_test_t*);
int arraylist_test_Destroy(arraylist_test_t*);
int arraylist_test_FillRandom(arraylist_test_t*);

#endif // TEST_H
