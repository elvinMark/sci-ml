#include <sciml/data/ndarray.hpp>
#include <sciml/utils/useful_functions.hpp>
#include <stdlib.h>

ndarray::ndarray(double *data, int size) {
  this->data = data;
  this->size = size;
  this->dim = (int *)malloc(sizeof(int));
  this->dim_length = 1;
  this->dim[0] = size;
  this->strides = shift_left(this->dim, 1, 1);
  this->strides_length = 1;
}

ndarray *ndarray::clone() {
  ndarray *arr = new ndarray(this->data, this->size);
  arr->set_strides(this->strides, this->strides_length);
  return arr;
}

ndarray *ndarray::get(int idx, ...) { return NULL; }

void ndarray::set(ndarray *arr, int idx, ...) {}

int *ndarray::shape() { return this->dim; }

void ndarray::set_strides(int s, ...) {}

void ndarray::set_strides(int *s, int l) {
  int prod = prod_all_elements(s, l);

  if (this->size % prod)
    return NULL;

  this->strides = s;
  this->strides_length = l;
  this->dim = shift_right(s, l, this->size / prod);
  this->dim_length = l;
}

void ndarray::reshape(int *s, int l) {
  int prod = prod_all_elements(s, l);

  if (prod != this->size)
    return NULL;

  this->dim = s;
  this->dim_length = l;
  this->strides = shift_left(s, l, 1);
  this->strides_length = l;
}

void ndarray::reshape(int s, ...) {}

ndarray *dot(ndarray *arr) { return NULL; }
