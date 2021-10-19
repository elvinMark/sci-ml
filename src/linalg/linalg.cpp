#include <sciml/linalg/linalg.hpp>

ndarray *__det__(ndarray *arr) { return NULL; }

ndarray *__inv__(ndarray *arr) { return NULL; }

ndarray **__qr__(ndarray *arr) { return NULL; }

ndarray **__eig__(ndarray *arr) { return NULL; }

ndarray *det(ndarray *arr) {
  int l = arr->dim_length - 2;
  int *new_dim = sublist(0, l);
  int new_size = prod_all_elements(new_dim);
  double *new_data = (double *)malloc(sizeof(double) * size);
  ndarray *o = new ndarray(new_data, new_size, new_dim, l);
  int *iter = create_list(l);
  ndarray *tmp;

  fill_zeros_list(iter, l);

  do {
    tmp = arr->get_subndarray()
  } while (!increase_list_by_one(iter, new_dim, l));

  return o;
}

ndarray *inv(ndarray *arr) { return NULL; }

ndarray **qr(ndarray *arr) { return NULL; }

ndarray **eig(ndarray *arr) { return NULL; }
