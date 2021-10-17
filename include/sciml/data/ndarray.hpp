#ifndef NDARRAY
#define NDARRAY
#include <iostream>
#include <stdarg.h>
#include <stdlib.h>

using namespace std;

class ndarray {
private:
  double *data;
  int *strides;
  int strides_length;
  int *dim;
  int dim_length;
  int size;
  int transpose_status;

public:
  ndarray(double *data, int size);
  ndarray(double *data, int size, int *dim, int l);
  double flat(int idx);
  int flat_index(int idx);
  ndarray *clone();
  double at(int idx, ...);
  double at(int *idxs, int l);
  void set(double val, int idx, ...);
  void set(double val, int *idxs, int l);
  ndarray *get_subndarray(int idx, ...);
  void set_subndarray(ndarray *arr, int idx, ...);
  int *shape();
  void set_strides(int s, ...);
  void set_strides(int *s, int l);
  void reshape(int s, ...);
  void reshape(int *s, int l);
  void transpose();
  ndarray *dot(ndarray *arr);

  static ndarray *einsum(ndarray *arr1, string idx_fmt1, ndarray *arr2,
                         string idx_fmt2);
};
#endif
