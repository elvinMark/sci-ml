#ifndef USEFUL_FUNCTIONS
#define USEFUL_FUNCTIONS
#include <iostream>
#include <sciml/utils/constants.hpp>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

// List Related Functions
int *create_list(int l);
int *random_list(int lo, int hi, int l);
void copy_list_to_list(int *from, int *to, int l);
void print_list(int *arr, int l);
void fill_zeros_list(int *arr, int l);
void fill_elem_list(int *arr, int l, int elem);
int increase_list_by_one(int *arr, int *limit, int l);
int *shift_left(int *arr, int l, int val);
int *shift_right(int *arr, int l, int val);
int *get_strides_from_shape(int *shape, int l);
int *sublist(int lo, int hi, int *arr, int l);
int *replace_elem_list(int *a, int l, int prev_val, int new_val);
int count_elem_list(int *arr, int l, int elem);
int *reduce_list(int *arr, int *mask, int l);
int list_less_than_list(int *a, int *b, int l);
int list_equal_list(int *a, int *b, int l);
int list_dot_list(int *a, int *b, int l);
int prod_all_elements(int *arr, int l);
int *args_to_list(va_list vl, int first_val, int *l);
int *reverse_list(int *s, int l);

// Einsum Indexes related functions
int check_format_indexes(int *shape1, string idx_fmt1, int *shape2,
                         string idx_fmt2);
void einsum_format_indexes(string idx_fmt1, string idx_fmt2,
                           string *result_idxs, string *sum_idxs);
int *create_list_from_idx_fmt(string idx_fmt, int *info);
void update_list_indexes(int *shape, string idx_fmt, int *info);
void update_list_from_idx_fmt(string idx_fmt, int *info, int *arr);

// Error message display and exit code
void assert_error(int error_code);

#endif
