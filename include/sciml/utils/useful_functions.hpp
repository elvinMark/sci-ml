#ifndef USEFUL_FUNCTIONS
#define USEFUL_FUNCTIONS
#include <iostream>
#include <sciml/utils/constants.hpp>
#include <stdarg.h>
#include <stdlib.h>

int prod_all_elements(int *arr, int l);
int *shift_left(int *arr, int l, int val);
int *shift_right(int *arr, int l, int val);
int *args_to_list(va_list vl, int first_val, int *l);
int list_dot_list(int *a, int *b, int l);
int *reverse_list(int *s, int l);
int list_less_than_list(int *a, int *b, int l);
void assert_error(int error_code);

#endif
