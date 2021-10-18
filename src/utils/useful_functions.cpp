#include <iostream>
#include <sciml/utils/useful_functions.hpp>

using namespace std;

int *create_list(int l) { return (int *)malloc(sizeof(int) * l); }

int *random_list(int lo, int hi, int l) {
  int *o = create_list(l);
  int diff = (hi - lo);
  srand(time(NULL));
  for (int i = 0; i < l; i++)
    o[i] = lo + (rand() % diff);
  return o;
}

void print_list(int *arr, int l) {
  for (int i = 0; i < l; i++)
    cout << arr[i] << " ";
  cout << endl;
}

void fill_zeros_list(int *arr, int l) {
  int i;
  for (i = 0; i < l; i++)
    arr[i] = 0;
}

int increase_list_by_one(int *arr, int *limit, int l) {
  int i;
  int tmp;
  int flag = 1;
  for (i = l - 1; i >= 0; i--) {
    tmp = arr[i] + flag;
    flag = tmp / limit[i];
    arr[i] = tmp % limit[i];
  }
  return flag;
}

int check_format_indexes(int *shape1, string idx_fmt1, int *shape2,
                         string idx_fmt2) {
  int idx;
  for (int i = 0; i < idx_fmt1.length(); i++) {
    idx = idx_fmt2.find(idx_fmt1[i]);
    if (idx != string::npos && shape2[idx] != shape1[i])
      return FALSE;
  }
  return TRUE;
}

void einsum_format_indexes(string idx_fmt1, string idx_fmt2,
                           string *result_idxs, string *sum_idxs) {
  *result_idxs = "";
  *sum_idxs = "";

  for (int i = 0; i < idx_fmt1.length(); i++) {
    if (idx_fmt2.find(idx_fmt1[i]) == string::npos)
      (*result_idxs).push_back(idx_fmt1[i]);
    else
      (*sum_idxs).push_back(idx_fmt1[i]);
  }

  for (int i = 0; i < idx_fmt2.length(); i++)
    if (idx_fmt1.find(idx_fmt2[i]) == string::npos)
      (*result_idxs).push_back(idx_fmt2[i]);
}

int *create_list_from_idx_fmt(string idx_fmt, int *info) {
  int *new_list = create_list(idx_fmt.length());
  int i = 0;
  for (char &ch : idx_fmt)
    new_list[i++] = info[ch - 'i'];
  return new_list;
}

void update_list_indexes(int *shape, string idx_fmt, int *info) {
  int i = 0;
  for (char &ch : idx_fmt)
    info[ch - 'i'] = shape[i++];
}

void update_list_from_idx_fmt(string idx_fmt, int *info, int *arr) {
  int i = 0;
  for (char &ch : idx_fmt)
    arr[i++] = info[ch - 'i'];
}

int prod_all_elements(int *arr, int l) {
  int i;
  int o = 1;
  for (i = 0; i < l; i++)
    o *= arr[i];
  return o;
}

int *shift_left(int *arr, int l, int val) {
  int i;
  int *o = create_list(l);
  for (i = 0; i < l - 1; i++) {
    o[i] = arr[i + 1];
  }
  o[l - 1] = val;
  return o;
}

int *shift_right(int *arr, int l, int val) {
  int i;
  int *o = create_list(l);
  for (i = 1; i < l; i++) {
    o[i] = arr[i - 1];
  }
  o[0] = val;
  return o;
}

int *args_to_list(va_list vl, int first_val, int *l) {
  int i = 0;
  int *o = create_list(1);
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
  int *o = create_list(l);
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
  else if (error_code == EXCEED_MAX_NUM_DIM)
    cout << "ERROR: Exceed the maximum number of dimensions supported" << endl;
  else if (error_code == IDX_FMT_DIM_MISMATCH)
    cout << "ERRO: Indexes pattern does not match dimension of the ndarray"
         << endl;
  else if (error_code == COMMON_IDX_SIZE_MISMATCH)
    cout << "ERROR: Common index does not match size" << endl;
  else
    cout << "ERROR: Unknown";
  exit(-1);
}
