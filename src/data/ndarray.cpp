#include <sciml/data/ndarray.hpp>
#include <sciml/utils/constants.hpp>
#include <sciml/utils/useful_functions.hpp>

// Constructor of the n-dimensional array
ndarray::ndarray(double *data, int size) {
  this->data = data;
  this->size = size;
  this->dim = (int *)malloc(sizeof(int));
  this->dim_length = 1;
  this->dim[0] = size;
  this->strides = shift_left(this->dim, 1, 1);
  this->strides_length = 1;
}

// Constructor of th n-dimensional array with an specific shape
ndarray::ndarray(double *data, int size, int *dim, int l) {
  this->data = data;
  this->size = size;
  this->dim = dim;
  this->dim_length = l;

  if (l > MAX_NUM_DIM) {
    // ERROR
    assert_error(EXCEED_MAX_NUM_DIM);
  }

  this->strides = shift_left(dim, l, 1);
  this->strides_length = l;

  if (prod_all_elements(dim, l) != size) {
    // ERROR
    assert_error(DIM_SIZE_MISMATCH);
  }
}

// Convert strided index into flat index
int ndarray::flat_index(int idx) {
  // TODO
  return idx;
}

// Accessing to the flat version of this ndarray
double ndarray::flat(int idx) { return this->data[this->flat_index(idx)]; }

// Clonning an array
ndarray *ndarray::clone() {
  ndarray *arr = new ndarray(this->data, this->size);
  arr->set_strides(this->strides, this->strides_length);
  return arr;
}

// Getting the element at an specific indexes
double ndarray::at(int idx, ...) {
  int l;
  int *idxs;
  va_list vl;

  va_start(vl, idx);
  idxs = args_to_list(vl, idx, &l);
  va_end(vl);

  return this->at(idxs, l);
}

double ndarray::at(int *idxs, int l) {
  int real_idx;
  if (l != this->strides_length) {
    // ERROR
    assert_error(NOT_ENOUGH_INDEXES);
  }

  if (!list_less_than_list(idxs, this->dim, l)) {
    // ERROR
    assert_error(OUTSIDE_RANGE);
  }

  real_idx = list_dot_list(idxs, this->strides, l);

  if (real_idx >= this->size) {
    // ERROR
    assert_error(OUTSIDE_RANGE);
  }

  return this->flat(real_idx);
}

void ndarray::set(double val, int idx, ...) {
  int l;
  int *idxs;
  va_list vl;

  va_start(vl, idx);
  idxs = args_to_list(vl, idx, &l);
  va_end(vl);

  this->set(val, idxs, l);
}

void ndarray::set(double val, int *idxs, int l) {
  int strided_idx = list_dot_list(idxs, this->strides, l);
  this->data[this->flat_index(strided_idx)] = val;
}

// Get the sub ndarray at the specific indexes
ndarray *ndarray::get_subndarray(int idx, ...) {
  // TODO
  return NULL;
}

// Set values at the specific subsection of the array at the specific
// indexes
void ndarray::set_subndarray(ndarray *arr, int idx, ...) {
  // TODO
}

// Get the shape of the ndarray
int *ndarray::shape() {
  // TODO
  return this->dim;
}

// Set strides of the ndarray
void ndarray::set_strides(int s,
                          ...) { // Just an interface when having args ...
  int *strides;
  int l;
  va_list vl;

  va_start(vl, s);
  strides = args_to_list(vl, s, &l);
  va_end(vl);
  this->set_strides(strides, l);
}

// Set strides of the ndarray
void ndarray::set_strides(int *s, int l) {
  int prod = prod_all_elements(s, l);

  if (this->size % prod) {
    // ERROR
    assert_error(STRIDES_SIZE_MISMATCH);
  }

  if (l > MAX_NUM_DIM) {
    // ERROR
    assert_error(EXCEED_MAX_NUM_DIM);
  }

  this->strides = s;
  this->strides_length = l;
  this->dim = shift_right(s, l, this->size / prod);
  this->dim_length = l;
}

// Set shape (or dim) of the ndarray
void ndarray::reshape(int s, ...) { // Just an interface when having args ...
  int *shapes;
  int l;
  va_list vl;

  va_start(vl, s);
  shapes = args_to_list(vl, s, &l);
  va_end(vl);
  this->reshape(shapes, l);
}

// Set shape (or dim) of the ndarray
void ndarray::reshape(int *s, int l) {
  // FIX
  int prod = prod_all_elements(s, l);

  if (prod != this->size) {
    // ERROR
    assert_error(SHAPE_SIZE_MISMATCH);
  }

  if (l > MAX_NUM_DIM) {
    // ERROR
    assert_error(EXCEED_MAX_NUM_DIM);
  }

  this->dim = s;
  this->dim_length = l;
  this->strides = shift_left(s, l, 1);
  this->strides_length = l;
}

void ndarray::transpose() {
  this->dim = reverse_list(this->dim, this->dim_length);
  this->strides = reverse_list(this->strides, this->strides_length);
}

// Dot product
ndarray *ndarray::dot(ndarray *arr) {
  // TODO
  string idx_fmt1 = "";
  string idx_fmt2 = "";
  char idx = 'i';
  char tmp;
  for (int i = 0; i < this->dim_length; i++) {
    idx_fmt1.push_back(idx);
    idx += 1;
  }
  tmp = idx - 1;
  for (int i = 0; i < arr->dim_length; i++) {
    idx_fmt2.push_back(idx);
    idx += 1;
  }
  idx_fmt2[arr->dim_length - 2] = tmp;

  return ndarray::einsum(this, idx_fmt1, arr, idx_fmt2);
}

// Einstein Sum
ndarray *ndarray::einsum(ndarray *arr1, string idx_fmt1, ndarray *arr2,
                         string idx_fmt2) {
  // TODO? Almost done
  if (arr1->strides_length != idx_fmt1.length() ||
      arr2->strides_length != idx_fmt2.length()) {
    // ERROR
    exit(-1);
  }

  if (!check_format_indexes(arr1->dim, idx_fmt1, arr2->dim, idx_fmt2)) {
    // ERROR
    exit(-1);
  }

  int sl1 = arr1->strides_length;
  int sl2 = arr2->strides_length;
  int *idxs1 = create_list(sl1);
  int *idxs2 = create_list(sl2);
  string result_idxs, sum_idxs;
  einsum_format_indexes(idx_fmt1, idx_fmt2, &result_idxs, &sum_idxs);

  int ril = result_idxs.length();
  int sil = sum_idxs.length();
  int *result_idx_iterator = create_list(ril);
  int *sum_idx_iterator = create_list(sil);
  int *list_indexes = create_list(AVAIL_NUM_INDEXES);

  fill_zeros_list(list_indexes, AVAIL_NUM_INDEXES);
  update_list_indexes(arr1->dim, idx_fmt1, list_indexes);
  update_list_indexes(arr2->dim, idx_fmt2, list_indexes);
  fill_zeros_list(result_idx_iterator, ril);
  fill_zeros_list(sum_idx_iterator, sil);

  int *new_shape = create_list_from_idx_fmt(result_idxs, list_indexes);
  int *sum_limits = create_list_from_idx_fmt(sum_idxs, list_indexes);

  int size = prod_all_elements(new_shape, ril);
  double *data = (double *)malloc(sizeof(double) * size);
  ndarray *result_ndarray = new ndarray(data, size, new_shape, ril);
  double acc;

  do {
    fill_zeros_list(list_indexes, AVAIL_NUM_INDEXES);
    update_list_indexes(result_idx_iterator, result_idxs, list_indexes);
    acc = 0;
    do {
      update_list_indexes(sum_idx_iterator, sum_idxs, list_indexes);
      update_list_from_idx_fmt(idx_fmt1, list_indexes, idxs1);
      update_list_from_idx_fmt(idx_fmt2, list_indexes, idxs2);
      acc += arr1->at(idxs1, arr1->strides_length) *
             arr2->at(idxs2, arr2->strides_length);
    } while (!increase_list_by_one(sum_idx_iterator, sum_limits, sil));
    result_ndarray->set(acc, result_idx_iterator, ril);

  } while (!increase_list_by_one(result_idx_iterator, new_shape, ril));
  return result_ndarray;
}
