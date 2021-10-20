#include <sciml/data/ndarray.hpp>
#include <sciml/utils/constants.hpp>
#include <sciml/utils/useful_functions.hpp>

ndarray::ndarray(int *dim, int l) {
  this->dim = dim;
  this->dim_length = l;
  this->strides = get_strides_from_shape(this->dim, l);
  this->strides_length = l;
  this->size = prod_all_elements(dim, l);
  this->data = (double *)malloc(sizeof(double) * this->size);
  this->offset = 0;
}

// Constructor of the n-dimensional array
ndarray::ndarray(double *data, int size) {
  this->data = data;
  this->size = size;
  this->dim = create_list(1);
  this->dim_length = 1;
  this->dim[0] = size;
  this->strides = get_strides_from_shape(this->dim, 1);
  this->strides_length = 1;
  this->offset = 0;
}

// Constructor of th n-dimensional array with an specific shape
ndarray::ndarray(double *data, int size, int *dim, int l) {
  this->data = data;
  this->size = size;
  this->dim = dim;
  this->dim_length = l;
  this->offset = 0;
  if (l > MAX_NUM_DIM) {
    // ERROR
    assert_error(EXCEED_MAX_NUM_DIM);
  }

  this->strides = get_strides_from_shape(dim, l);
  this->strides_length = l;

  if (prod_all_elements(dim, l) != size) {
    // ERROR
    assert_error(DIM_SIZE_MISMATCH);
  }
}

// General Constructor
ndarray::ndarray(double *data, int size, int *dim, int l, int offset) {
  this->data = data;
  this->size = size;
  this->dim = dim;
  this->dim_length = l;

  if (l > MAX_NUM_DIM) {
    // ERROR
    assert_error(EXCEED_MAX_NUM_DIM);
  }

  this->strides = get_strides_from_shape(dim, l);
  this->strides_length = l;

  if (prod_all_elements(dim, l) != size) {
    // ERROR
    assert_error(DIM_SIZE_MISMATCH);
  }
  this->offset = offset;
}

string ndarray::__str__() {
  string o = "";
  int *iter = create_list(this->dim_length);
  if (this->dim_length == 0) {
    o.append(to_string(this->at(END_OF_LIST)) + "\n");
    return o;
  } else if (this->dim_length == 1) {
    o.append("[ ");
    for (int i = 0; i < this->dim[0]; i++) {
      iter[0] = i;
      o.append(to_string(this->__at__(iter, 1)));
      if (i != this->dim[0] - 1)
        o.append("\t");
      else
        o.append(" ");
    }
    o.append("]");
    return o;
  } else {
    o.append("[");
    fill_elem_list(iter, this->dim_length, ALL);
    for (int i = 0; i < this->dim[0]; i++) {
      iter[0] = i;
      o.append(this->__get_subndarray__(iter, this->dim_length)->__str__());
      if (i != this->dim[0] - 1)
        o.append("\n");
    }
    o.append("]\n");
    return o;
  }
}

ndarray *ndarray::__add__(double x) { return ndarray::add(this, x); }
ndarray *ndarray::__add__(ndarray *arr) { return ndarray::add(this, arr); }
ndarray *ndarray::__sub__(ndarray *arr2) { return ndarray::sub(this, arr2); }
ndarray *ndarray::__mul__(double x) { return ndarray::mul(this, x); }
ndarray *ndarray::__mul__(ndarray *arr) { return ndarray::mul(this, arr); }
ndarray *ndarray::__div__(ndarray *arr) { return ndarray::div(this, arr); }
ndarray *ndarray::__power__(double num) { return ndarray::power(this, num); }
ndarray *ndarray::__apply__(double fun_f(double)) {
  return ndarray::apply(this, fun_f);
}

ndarray *ndarray::__get_subndarray__(int *idxs, int l) {
  if (l != this->dim_length) {
    // ERROR
    assert_error(IDX_DIM_MISMATCH);
  }

  if (!list_less_than_list(idxs, this->dim, l)) {
    // ERROR
    assert_error(IDX_DIM_MISMATCH);
  }
  ndarray *o = this->clone();
  o->dim = reduce_list(this->dim, idxs, l);
  o->dim_length = count_elem_list(idxs, l, ALL);
  o->size = prod_all_elements(o->dim, o->dim_length);
  o->strides_length = o->dim_length;
  o->strides = reduce_list(this->strides, idxs, l);
  o->offset = this->offset + list_dot_list(replace_elem_list(idxs, l, ALL, 0),
                                           this->strides, l);

  return o;
}

void ndarray::__set_subndarray__(ndarray *arr, int *idxs, int l) {
  ndarray *o = this->__get_subndarray__(idxs, l);
  int *limit = o->dim;
  int sl = o->dim_length;
  int *iter = create_list(sl);
  fill_zeros_list(iter, sl);
  do {
    o->__set__(arr->__at__(iter, sl), iter, sl);
  } while (!increase_list_by_one(iter, o->dim, sl));
}

// Convert strided index into flat index
int ndarray::flat_index(int idx) {
  // TODO? Now it is just returning the same index;
  // Fix offset?
  return idx;
}

// Accessing to the flat version of this ndarray
double ndarray::flat(int idx) {
  // TODO? Fix offset?
  return this->data[this->offset + this->flat_index(idx)];
}

// Clonning an array
ndarray *ndarray::clone() {
  return new ndarray(this->data, this->size, this->dim, this->dim_length,
                     this->offset);
}

// Getting the element at an specific indexes
double ndarray::at(int idx, ...) {
  // TODO? Fix offset?
  int l;
  int *idxs;
  va_list vl;

  va_start(vl, idx);
  idxs = args_to_list(vl, idx, &l);
  va_end(vl);

  return this->__at__(idxs, l);
}

double ndarray::__at__(int *idxs, int l) {
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

  this->__set__(val, idxs, l);
}

void ndarray::__set__(double val, int *idxs, int l) {
  // TODO? fix offset?
  int strided_idx = list_dot_list(idxs, this->strides, l);
  this->data[this->offset + this->flat_index(strided_idx)] = val;
}

// Get the sub ndarray at the specific indexes
ndarray *ndarray::get_subndarray(int idx, ...) {
  va_list vl;
  int l;
  int *idxs;

  va_start(vl, idx);
  idxs = args_to_list(vl, idx, &l);
  va_end(vl);

  return this->__get_subndarray__(idxs, l);
}

// Set values at the specific subsection of the array at the specific
// indexes
void ndarray::set_subndarray(ndarray *arr, int idx, ...) {
  va_list vl;
  int l;
  int *idxs;

  va_start(vl, idx);
  idxs = args_to_list(vl, idx, &l);
  va_end(vl);

  this->__set_subndarray__(arr, idxs, l);
}

// Get the shape of the ndarray
int *ndarray::shape() {
  // TODO
  return this->dim;
}

// Set strides of the ndarray
void ndarray::__as_strided__(int *new_strides, int *new_shape, int l) {
  /*******************************************/
  /* WARNING: Be careful using this function */
  /*******************************************/
  this->strides = new_strides;
  this->strides_length = l;
  this->dim = new_shape;
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
  this->__reshape__(shapes, l);
}

// Set shape (or dim) of the ndarray
void ndarray::__reshape__(int *s, int l) {
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
  this->strides = get_strides_from_shape(s, l);
  this->strides_length = l;
}

void ndarray::transpose() {
  this->dim = reverse_list(this->dim, this->dim_length);
  this->strides = reverse_list(this->strides, this->strides_length);
}

// Dot product
ndarray *ndarray::dot(ndarray *arr) { return ndarray::dot(this, arr); }

ndarray *ndarray::sum(int axis, ...) {
  va_list vl;
  int *axs;
  int l;

  va_start(vl, axis);
  axs = args_to_list(vl, axis, &l);
  va_end(vl);

  return ndarray::sum(this, axs, l);
}

ndarray *ndarray::mean(int axis, ...) {
  va_list vl;
  int *axs;
  int l;

  va_start(vl, axis);
  axs = args_to_list(vl, axis, &l);
  va_end(vl);

  return ndarray::mean(this, axs, l);
}

ndarray *ndarray::std(int axis, ...) {
  va_list vl;
  int *axs;
  int l;

  va_start(vl, axis);
  axs = args_to_list(vl, axis, &l);
  va_end(vl);

  return ndarray::std(this, axs, l);
}

// Einstein Sum
ndarray *ndarray::einsum(ndarray *arr1, string idx_fmt1, ndarray *arr2,
                         string idx_fmt2) {
  // TODO? Almost done
  if (arr1->strides_length != idx_fmt1.length() ||
      arr2->strides_length != idx_fmt2.length()) {
    // ERROR
    assert_error(IDX_FMT_DIM_MISMATCH);
  }

  if (!check_format_indexes(arr1->dim, idx_fmt1, arr2->dim, idx_fmt2)) {
    // ERROR
    assert_error(COMMON_IDX_SIZE_MISMATCH);
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
      acc += arr1->__at__(idxs1, arr1->strides_length) *
             arr2->__at__(idxs2, arr2->strides_length);
    } while (!increase_list_by_one(sum_idx_iterator, sum_limits, sil));
    result_ndarray->__set__(acc, result_idx_iterator, ril);

  } while (!increase_list_by_one(result_idx_iterator, new_shape, ril));
  return result_ndarray;
}

/*
Einsum:
arr_{idx_fmt1} 1_{idx_fmt2}
For example:
arr_{ijk} 1_{jk} -> a_{i} (sum over index j and k)
*/
ndarray *ndarray::einsum(ndarray *arr1, string idx_fmt1, string idx_fmt2) {
  // TODO?/ FIX?
  if (arr1->strides_length != idx_fmt1.length()) {
    // ERROR
    assert_error(IDX_FMT_DIM_MISMATCH);
  }

  int sl1 = arr1->strides_length;
  int *idxs1 = create_list(sl1);
  string result_idxs, sum_idxs;
  einsum_format_indexes(idx_fmt1, idx_fmt2, &result_idxs, &sum_idxs);

  int ril = result_idxs.length();
  int sil = sum_idxs.length();
  int *result_idx_iterator = create_list(ril);
  int *sum_idx_iterator = create_list(sil);
  int *list_indexes = create_list(AVAIL_NUM_INDEXES);

  fill_zeros_list(list_indexes, AVAIL_NUM_INDEXES);
  update_list_indexes(arr1->dim, idx_fmt1, list_indexes);
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
      acc += arr1->__at__(idxs1, arr1->strides_length);
    } while (!increase_list_by_one(sum_idx_iterator, sum_limits, sil));
    result_ndarray->__set__(acc, result_idx_iterator, ril);

  } while (!increase_list_by_one(result_idx_iterator, new_shape, ril));
  return result_ndarray;
}

// Dot product between 2 ndarrays
ndarray *ndarray::dot(ndarray *arr1, ndarray *arr2) {
  // TODO? Almost done?
  string idx_fmt1 = "";
  string idx_fmt2 = "";
  char idx = 'i';
  char tmp;
  for (int i = 0; i < arr1->dim_length; i++) {
    idx_fmt1.push_back(idx);
    idx += 1;
  }
  tmp = idx - 1;
  for (int i = 0; i < arr2->dim_length; i++) {
    idx_fmt2.push_back(idx);
    idx += 1;
  }
  idx_fmt2[arr2->dim_length - 2] = tmp;

  return ndarray::einsum(arr1, idx_fmt1, arr2, idx_fmt2);
}

ndarray *ndarray::sum(ndarray *arr1, int *axis, int l) {
  // TODO
  string idx_fmt1 = "";
  string idx_fmt2 = "";
  for (int i = 0; i < arr1->dim_length; i++)
    idx_fmt1.push_back('i' + i);
  for (int i = 0; i < l; i++) {
    if (axis[i] > arr1->dim_length) {
      // ERROR
      assert_error(IDX_DIM_MISMATCH);
    }
    idx_fmt2.push_back('i' + axis[i]);
  }
  return ndarray::einsum(arr1, idx_fmt1, idx_fmt2);
}

ndarray *ndarray::add(ndarray *arr1, ndarray *arr2) {
  if (arr1->dim_length != arr2->dim_length) {
    // ERROR
    assert_error(DIM_SIZE_MISMATCH);
  }

  if (!list_equal_list(arr1->dim, arr2->dim, arr1->dim_length)) {
    // ERROR
    assert_error(DIM_SIZE_MISMATCH);
  }

  int size = arr1->size;
  double *data = (double *)malloc(sizeof(double) * arr1->size);
  for (int i = 0; i < arr1->size; i++)
    data[i] = arr1->data[arr1->flat_index(i)] + arr2->data[arr2->flat_index(i)];
  return new ndarray(data, size, arr1->dim, arr1->dim_length);
}

ndarray *ndarray::add(ndarray *arr1, double num) {
  int size = arr1->size;
  double *data = (double *)malloc(sizeof(double) * arr1->size);
  for (int i = 0; i < arr1->size; i++)
    data[i] = num * arr1->data[arr1->flat_index(i)];
  return new ndarray(data, size, arr1->dim, arr1->dim_length);
}

ndarray *ndarray::sub(ndarray *arr1, ndarray *arr2) {
  if (arr1->dim_length != arr2->dim_length) {
    // ERROR
    assert_error(DIM_SIZE_MISMATCH);
  }

  if (!list_equal_list(arr1->dim, arr2->dim, arr1->dim_length)) {
    // ERROR
    assert_error(DIM_SIZE_MISMATCH);
  }

  int size = arr1->size;
  double *data = (double *)malloc(sizeof(double) * arr1->size);
  for (int i = 0; i < arr1->size; i++)
    data[i] = arr1->data[arr1->flat_index(i)] - arr2->data[arr2->flat_index(i)];
  return new ndarray(data, size, arr1->dim, arr1->dim_length);
}

ndarray *ndarray::mul(ndarray *arr1, ndarray *arr2) {
  if (arr1->dim_length != arr2->dim_length) {
    // ERROR
    assert_error(DIM_SIZE_MISMATCH);
  }

  if (!list_equal_list(arr1->dim, arr2->dim, arr1->dim_length)) {
    // ERROR
    assert_error(DIM_SIZE_MISMATCH);
  }

  int size = arr1->size;
  double *data = (double *)malloc(sizeof(double) * arr1->size);
  for (int i = 0; i < arr1->size; i++)
    data[i] = arr1->data[arr1->flat_index(i)] * arr2->data[arr2->flat_index(i)];
  return new ndarray(data, size, arr1->dim, arr1->dim_length);
}

ndarray *ndarray::mul(ndarray *arr1, double num) {
  int size = arr1->size;
  double *data = (double *)malloc(sizeof(double) * arr1->size);
  for (int i = 0; i < arr1->size; i++)
    data[i] = num * arr1->data[arr1->flat_index(i)];
  return new ndarray(data, size, arr1->dim, arr1->dim_length);
}

ndarray *ndarray::div(ndarray *arr1, ndarray *arr2) {
  if (arr1->dim_length != arr2->dim_length) {
    // ERROR
    assert_error(DIM_SIZE_MISMATCH);
  }

  if (!list_equal_list(arr1->dim, arr2->dim, arr1->dim_length)) {
    // ERROR
    assert_error(DIM_SIZE_MISMATCH);
  }

  int size = arr1->size;
  double *data = (double *)malloc(sizeof(double) * arr1->size);
  for (int i = 0; i < arr1->size; i++)
    data[i] = arr1->data[arr1->flat_index(i)] / arr2->data[arr2->flat_index(i)];
  return new ndarray(data, size, arr1->dim, arr1->dim_length);
}

ndarray *ndarray::power(ndarray *arr1, double num) {
  int size = arr1->size;
  double *data = (double *)malloc(sizeof(double) * arr1->size);
  for (int i = 0; i < arr1->size; i++)
    data[i] = pow(arr1->data[arr1->flat_index(i)], num);
  return new ndarray(data, size, arr1->dim, arr1->dim_length);
}

ndarray *ndarray::apply(ndarray *arr1, double fun_f(double)) {
  int size = arr1->size;
  double *data = (double *)malloc(sizeof(double) * arr1->size);
  for (int i = 0; i < arr1->size; i++)
    data[i] = fun_f(arr1->data[arr1->flat_index(i)]);
  return new ndarray(data, size, arr1->dim, arr1->dim_length);
}

ndarray *ndarray::mean(ndarray *arr1, int *axis, int l) {
  int N = 1;
  for (int i = 0; i < l; i++) {
    if (axis[i] > arr1->dim_length) {
      // ERROR
      assert_error(IDX_DIM_MISMATCH);
    }
    N *= arr1->dim[axis[i]];
  }

  return ndarray::mul(ndarray::sum(arr1, axis, l), 1.0 / N);
}

ndarray *ndarray::std(ndarray *arr1, int *axis, int l) {
  ndarray *arr_2_mean = ndarray::mean(ndarray::power(arr1, 2), axis, l);
  ndarray *arr_mean_2 = ndarray::power(ndarray::mean(arr1, axis, l), 2);
  return ndarray::power(ndarray::sub(arr_2_mean, arr_mean_2), 0.5);
}

ndarray *ndarray::random(int d, ...) {
  va_list vl;
  int l;
  int *dim;

  va_start(vl, d);
  dim = args_to_list(vl, d, &l);
  va_end(vl);

  return ndarray::__random__(dim, l);
}

ndarray *ndarray::__random__(int *d, int l) {
  int size = prod_all_elements(d, l);
  double *data = (double *)malloc(sizeof(double) * size);
  int i;

  srand(time(NULL));

  for (i = 0; i < size; i++)
    data[i] = rand() % 10000 / 10000.0;

  return new ndarray(data, size, d, l);
}

ndarray *ndarray::zeros(int d, ...) {
  va_list vl;
  int l;
  int *dim;

  va_start(vl, d);
  dim = args_to_list(vl, d, &l);
  va_end(vl);

  return ndarray::__zeros__(dim, l);
}

ndarray *ndarray::__zeros__(int *d, int l) {
  int size = prod_all_elements(d, l);
  double *data = (double *)malloc(sizeof(double) * size);
  int i;

  for (i = 0; i < size; i++)
    data[i] = 0;

  return new ndarray(data, size, d, l);
}

ndarray *ndarray::ones(int d, ...) {
  va_list vl;
  int l;
  int *dim;

  va_start(vl, d);
  dim = args_to_list(vl, d, &l);
  va_end(vl);

  return ndarray::__ones__(dim, l);
}

ndarray *ndarray::__ones__(int *d, int l) {
  int size = prod_all_elements(d, l);
  double *data = (double *)malloc(sizeof(double) * size);
  int i;

  for (i = 0; i < size; i++)
    data[i] = 1;

  return new ndarray(data, size, d, l);
}

ndarray *ndarray::eye(int d) {
  int *dim = create_list(2);
  int size = d * d;
  double *data = (double *)malloc(sizeof(double) * size);

  dim[0] = d;
  dim[1] = d;

  for (int i = 0; i < d; i++)
    for (int j = 0; j < d; j++)
      data[i * d + j] = i == j ? 1 : 0;

  return new ndarray(data, size, dim, 2);
}

ndarray *ndarray::eye(int r, int c) {
  int *dim = create_list(2);
  int size = r * c;
  double *data = (double *)malloc(sizeof(double) * size);

  dim[0] = r;
  dim[1] = c;

  for (int i = 0; i < r; i++)
    for (int j = 0; j < c; j++)
      data[i * r + j] = i == j ? 1 : 0;

  return new ndarray(data, size, dim, 2);
}
