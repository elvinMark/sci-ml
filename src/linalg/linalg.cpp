#include <sciml/linalg/linalg.hpp>

ndarray **__lu__(ndarray *arr) {
  if (arr->dim_length != 2) {
    // ERROR
    assert_error(DIM_TOO_HIGH);
  }

  if (arr->dim[0] != arr->dim[1]) {
    // ERROR
    assert_error(DIM_NOT_EXPECTED);
  }

  ndarray **o = (ndarray **)malloc(sizeof(ndarray *) * 2);
  ndarray *_l, *_u;
  int d = arr->dim[0];
  int *iter_1 = create_list(2);
  int *iter_2 = create_list(2);
  double s;
  double uii;

  _l = ndarray::eye(d);
  _u = new ndarray(arr->dim, arr->dim_length);

  for (int i = 0; i < d; i++) {
    iter_1[0] = i;
    for (int j = i; j < d; j++) {
      s = 0;
      iter_2[1] = j;
      for (int k = 0; k < i; k++) {
        iter_1[1] = k;
        iter_2[0] = k;
        s += _l->__at__(iter_1, 2) * _u->__at__(iter_2, 2);
      }
      iter_2[0] = i;
      _u->__set__(arr->__at__(iter_2, 2) - s, iter_2, 2);
    }
    iter_2[1] = i;
    iter_2[0] = i;
    uii = _u->__at__(iter_2, 2);

    for (int j = i + 1; j < d; j++) {
      s = 0;
      iter_1[0] = j;
      for (int k = 0; k < i; k++) {
        iter_1[1] = k;
        iter_2[0] = k;
        s += _l->__at__(iter_1, 2) * _u->__at__(iter_2, 2);
      }
      iter_1[1] = i;
      _l->__set__((arr->__at__(iter_1, 2) - s) / uii, iter_1, 2);
    }
  }

  o[0] = _l;
  o[1] = _u;

  return o;
}

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
  for (int i = 0; i < n; i++) {
    iter[0] = i;
    iter[1] = i;
    ans *= _lu[0]->__at__(iter, 2) * _lu[1]->__at__(iter, 2);
  }
  return ans;
}

ndarray *__solve__(ndarray *arr, ndarray *b) {
  if (arr->dim_length != 2 || b->dim_length != 2) {
    // ERROR
    assert_error(DIM_TOO_HIGH);
  }

  if (arr->dim[0] != arr->dim[1] || arr->dim[0] != b->dim[0]) {
    // ERROR
    assert_error(DIM_NOT_EXPECTED);
  }

  int d = arr->dim[0];
  int *iter_arr = create_list(2);
  int *iter_z = create_list(2);
  ndarray **_lu = __lu__(arr);
  ndarray *_l, *_u;
  ndarray *_sol = new ndarray(b->dim, b->dim_length);
  ndarray *_z = new ndarray(b->dim, b->dim_length);
  double s;

  _l = _lu[0];
  _u = _lu[1];

  // Solving L * z = b
  // for each row
  for (int i = 0; i < b->dim[1]; i++) {
    for (int j = 0; j < b->dim[0]; j++) {
      s = 0;
      iter_arr[0] = j;
      iter_z[1] = i;
      for (int k = 0; k < j; k++) {
        iter_arr[1] = k;
        iter_z[0] = k;
        s += _l->__at__(iter_arr, 2) * _z->__at__(iter_z, 2);
      }
      iter_z[0] = j;
      _z->__set__(b->__at__(iter_z, 2) - s, iter_z, 2);
    }
  }

  // Solving U * sol = z
  for (int i = 0; i < _z->dim[1]; i++) {
    for (int j = _z->dim[0] - 1; j >= 0; j--) {
      s = 0;
      iter_arr[0] = j;
      iter_z[1] = i;
      for (int k = j + 1; k < _z->dim[0]; k++) {
        iter_arr[1] = k;
        iter_z[0] = k;
        s += _u->__at__(iter_arr, 2) * _sol->__at__(iter_z, 2);
      }
      iter_z[0] = j;
      iter_arr[1] = j;
      _sol->__set__((_z->__at__(iter_z, 2) - s) / _u->__at__(iter_arr, 2),
                    iter_z, 2);
    }
  }

  return _sol;
}

ndarray *__inv__(ndarray *arr) {
  // Inverse of a nxn matrix (2-dim ndarray)
  if (arr->dim_length != 2) {
    // ERROR
    assert_error(DIM_TOO_HIGH);
  }

  if (arr->dim[0] != arr->dim[1]) {
    // ERROR
    assert_error(DIM_NOT_EXPECTED);
  }

  int d = arr->dim[0];
  ndarray *I = ndarray::eye(d);

  return __solve__(arr, I);
}

ndarray **__qr__(ndarray *arr) {
  // TODO
  ndarray *_q;
  ndarray *_r;
  ndarray **o = (ndarray **)malloc(sizeof(ndarray *) * 2);

  _q = new ndarray(arr->dim, arr->dim_length);
  _r = new ndarray(arr->dim, arr->dim_length);

  o[0] = _q;
  o[1] = _r;

  return o;
}

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
  ndarray **out = (ndarray **)malloc(sizeof(ndarray *) * 2);

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
  int l = arr->dim_length - 2;
  int *new_dim = sublist(0, l, arr->dim, arr->dim_length);
  int new_size = prod_all_elements(new_dim, l);
  double *new_data = (double *)malloc(sizeof(double) * new_size);
  ndarray *o = new ndarray(new_data, new_size, new_dim, l);
  int *iter = create_list(arr->dim_length);
  int *new_iter = create_list(l);
  ndarray *tmp;

  fill_zeros_list(new_iter, l);
  fill_elem_list(iter, arr->dim_length, ALL);
  do {
    // Get nxn subndarray
    copy_list_to_list(new_iter, iter, l);
    tmp = arr->__get_subndarray__(iter, arr->dim_length);
    // Calculate the det of the subndarray and set the value in the major
    // ndarray
    o->__set__(__det__(tmp), new_iter, l);
  } while (!increase_list_by_one(new_iter, new_dim, l));

  return o;
}

ndarray *inv(ndarray *arr) {
  int l = arr->dim_length - 2;
  int *new_dim = sublist(0, l, arr->dim, arr->dim_length);
  int new_size = prod_all_elements(new_dim, l);
  ndarray *o = new ndarray(arr->dim, arr->dim_length);
  int *iter = create_list(arr->dim_length);
  int *new_iter = create_list(l);
  ndarray *tmp;

  fill_zeros_list(new_iter, l);
  fill_elem_list(iter, arr->dim_length, ALL);

  do {
    // Get nxn subndarray
    copy_list_to_list(new_iter, iter, l);
    tmp = arr->__get_subndarray__(iter, arr->dim_length);
    // Calculate the inv of the subndarray and set the value in the major
    // ndarray
    o->__set_subndarray__(__inv__(tmp), iter, arr->dim_length);
  } while (!increase_list_by_one(new_iter, new_dim, l));

  return o;
}

ndarray **qr(ndarray *arr) {
  // TODO
  return NULL;
}

ndarray **eig(ndarray *arr) {
  // TODO
  return NULL;
}
