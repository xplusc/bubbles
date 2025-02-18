#!/bin/bash
gcc -o bubbles_test \
	-W -Wall -Wextra -pedantic \
	test_main.c \
	test.c \
	arraylist.c \
