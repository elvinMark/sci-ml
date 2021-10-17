#include <iostream>
#include <sciml/utils/useful_functions.hpp>

using namespace std;

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

int *reverse_list(int *s, int l) {
  int i;
  int *o = (int *)malloc(sizeof(int) * l);
  for (i = 0; i < l; i++)
    o[i] = s[l - i - 1];
  return o;
}

int list_less_than_list(int *a, int *b, int l) {
  int i;
  for (i = 0; i < l; i++)
    if (a[i] >= b[i])
      return FALSE;
  return TRUE;
}

void assert_error(int error_code) {
  if (error_code == DIM_SIZE_MISMATCH)
    cout << "ERROR: Input dimension does not match the size of the data"
         << endl;
  else if (error_code == NOT_ENOUGH_INDEXES)
    cout
        << "ERROR: Not enough indexes were input or too much indexes were input"
        << endl;
  else if (error_code == OUTSIDE_RANGE)
    cout << "ERROR: Input indexes are outside range" << endl;
  else if (error_code == STRIDES_SIZE_MISMATCH)
    cout << "ERROR: Input strides does not match the size of the ndarray"
         << endl;
  else if (error_code == SHAPE_SIZE_MISMATCH)
    cout << "ERROR: Input shape does not match the size of the ndarray" << endl;
  else
    cout << "ERROR: Unknown";
  exit(-1);
}
