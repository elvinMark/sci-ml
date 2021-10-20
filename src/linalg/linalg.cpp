#include <sciml/linalg/linalg.hpp>

ndarray **__lu__(ndarray *arr) { return NULL; }

double __det__(ndarray *arr) {
  // Determinant of a nxn matrix (2-dim ndarray)
  if (arr->dim_length != 2) {
    // ERROR
    assert_error(DIM_TOO_HIGH);
  }

  if (arr->dim[0] != arr->dim[1]) {
    // ERROR
    assert_error(DIM_NOT_EXPECTED);
  }

  int n = arr->dim[0];
  int *iter = create_list(2);
  ndarray **_lu = __lu__(arr);
  double ans = 1;
  for (i = 0; i < n; i++) {
    iter[0] = i;
    iter[1] = i;
    ans *= _lu[0]->__at__(iter, 2) * _lu[1]->__at__(iter, 2);
  }
  return ans;
}

ndarray *__inv__(ndarray *arr) {
  // Inverse of a nxn matrix (2-dim ndarray)
  // TODO
  if (arr->dim_length != 2) {
    // ERROR
    assert_error(DIM_TOO_HIGH);
  }

  if (arr->dim[0] != arr->dim[1]) {
    // ERROR
    assert_error(DIM_NOT_EXPECTED);
  }

  int n = arr->dim[0];
  int *iter = create_list(2);
  ndarray **_lu = __lu__(arr);
  ndarray *_inv = new ndarray(arr->dim, arr->dim_length);

  return ans;
}

ndarray **__qr__(ndarray *arr) { return NULL; }

ndarray **__eig__(ndarray *arr, int maxIter) {
  // Calculate the eigenvalues of a nxn matrix (2-dim ndarray)
  if (arr->dim_length != 2) {
    // ERROR
    assert_error(DIM_TOO_HIGH);
  }

  if (arr->dim[0] != arr->dim[1]) {
    // ERROR
    assert_error(DIM_NOT_EXPECTED);
  }

  int n = arr->dim[0];
  int *iter = create_list(2);
  ndarray **_qr;
  ndarray *_q, *_r;
  ndarray *_eig_vecs;
  ndarray *out[2];

  _eig_vecs = ndarray::eye(arr->dim[0]);

  if (maxIter == DEFAULT)
    maxIter = EIG_MAX_ITER;

  for (int i = 0; i < maxIter; i++) {
    _qr = __qr__(arr);
    _q = _qr[0];
    _r = _qr[1];
    arr = _r->dot(_q);
    _eig_vecs = _eig_vecs->dot(_q);
  }

  out[0] = arr;
  out[1] = _eig_vecs;

  return out;
}

ndarray *det(ndarray *arr) {
  // TODO
  int l = arr->dim_length - 2;
  int *new_dim = sublist(0, l);
  int new_size = prod_all_elements(new_dim);
  double *new_data = (double *)malloc(sizeof(double) * size);
  ndarray *o = new ndarray(new_data, new_size, new_dim, l);
  int *iter = create_list(l);
  ndarray *tmp;

  fill_zeros_list(iter, l);

  do {
    tmp = arr->__get_subndarray__()
  } while (!increase_list_by_one(iter, new_dim, l));

  return o;
}

ndarray *inv(ndarray *arr) { return NULL; }

ndarray **qr(ndarray *arr) { return NULL; }

ndarray **eig(ndarray *arr) { return NULL; }
