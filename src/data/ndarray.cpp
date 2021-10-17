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
  this->strides = shift_left(dim, l, 1);
  this->strides_length = l;

  if (prod_all_elements(dim, l) != size) {
    // ERROR
    assert_error(DIM_SIZE_MISMATCH);
  }
}

// Accessing to the flat version of this ndarray
double ndarray::flat(int idx) {
  // TODO
  return this->data[idx];
}

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
  int real_idx;
  va_list vl;

  va_start(vl, idx);
  idxs = args_to_list(vl, idx, &l);

  if (l != this->strides_length) {
    // ERROR
    assert_error(NOT_ENOUGH_INDEXES);
  }

  va_end(vl);

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

// Get the sub ndarray at the specific indexes
ndarray *ndarray::get(int idx, ...) {
  // TODO
  return NULL;
}

// Set values at the specific subsection of the array at the specific
// indexes
void ndarray::set(ndarray *arr, int idx, ...) {
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

  this->dim = s;
  this->dim_length = l;
  this->strides = shift_left(s, l, 1);
  this->strides_length = l;
}

void ndarray::transpose() {
  this->dim = reverse_list(this->dim, this->dim_length);
  this->strides = reverse_list(this->strides, this->strides_length);
}

ndarray *dot(ndarray *arr) {
  // TODO
  return NULL;
}
