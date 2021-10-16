#include <sciml/data/ndarray.hpp>
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
  }

  va_end(vl);
  real_idx = list_dot_list(idxs, this->strides, l);

  if (real_idx >= this->size) {
    // ERROR
  }

  return this->data[real_idx];
}

// Get the sub ndarray at the specific indexes
ndarray *ndarray::get(int idx, ...) { return NULL; }

// Set values at the specific subsection of the array at the specific
// indexes
void ndarray::set(ndarray *arr, int idx, ...) {}

// Get the shape of the ndarray
int *ndarray::shape() { return this->dim; }

// Set strides of the ndarray
void ndarray::set_strides(int s, ...) {
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
  }

  this->strides = s;
  this->strides_length = l;
  this->dim = shift_right(s, l, this->size / prod);
  this->dim_length = l;
}

// Set shape (or dim) of the ndarray
void ndarray::reshape(int s, ...) {
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
  int prod = prod_all_elements(s, l);

  if (prod != this->size) {
    // ERROR
  }

  this->dim = s;
  this->dim_length = l;
  this->strides = shift_left(s, l, 1);
  this->strides_length = l;
}

ndarray *dot(ndarray *arr) { return NULL; }
