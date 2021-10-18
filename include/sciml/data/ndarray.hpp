#ifndef NDARRAY
#define NDARRAY
#include <iostream>
#include <stdarg.h>
#include <stdlib.h>

using namespace std;

class ndarray {
public:
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
  ndarray *__add__(double x);
  ndarray *__add__(ndarray *arr);
  ndarray *__mul__(double x);
  ndarray *__mul__(ndarray *arr);
  ndarray *__div__(ndarray *arr);
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
  ndarray *sum(int *axis);
  ndarray *sum(int axis, ...);

  static ndarray *einsum(ndarray *arr1, string idx_fmt1, ndarray *arr2,
                         string idx_fmt2);
  static ndarray *einsum(ndarray *arr1, string idx_fmt1, string idx_fmt2);
  static ndarray *dot(ndarray *arr1, ndarray *arr2);
  static ndarray *sum(ndarray *arr1, int *axis);
  static ndarray *sum(ndarray *arr1, int axis, ...);
};
#endif
