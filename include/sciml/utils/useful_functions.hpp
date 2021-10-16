#ifndef USEFUL_FUNCTIONS
#define USEFUL_FUNCTIONS
#include <iostream>
#include <sciml/utils/constants.hpp>
#include <stdarg.h>
#include <stdlib.h>

int prod_all_elements(int *arr, int l) {
  int i;
  int o = 1;
  for (i = 0; i < l; i++)
    o *= arr[i];
  return o;
}

int *shift_left(int *arr, int l, int val) {
  int i;
  int *o = (int *)malloc(sizeof(int) * l);
  for (i = 0; i < l - 1; i++) {
    o[i] = arr[i + 1];
  }
  o[l - 1] = val;
  return o;
}

int *shift_right(int *arr, int l, int val) {
  int i;
  int *o = (int *)malloc(sizeof(int) * l);
  for (i = 1; i < l; i++) {
    o[i] = arr[i - 1];
  }
  o[0] = val;
  return o;
}

int *args_to_list(va_list vl, int first_val, int *l) {
  int i = 0;
  int *o = (int *)malloc(sizeof(int));
  int val = first_val;
  while (val != END_OF_LIST) {
    o[i++] = val;
    o = (int *)realloc(o, sizeof(int) * (i + 1));
    val = va_arg(vl, int);
  }
  *l = i;
  return o;
}

int list_dot_list(int *a, int *b, int l) {
  int idx = 0;
  int i;
  for (i = 0; i < l; i++)
    idx += a[i] * b[i];
  return idx;
}

#endif
