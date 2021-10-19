#ifndef NDARRAY
#define NDARRAY
#include <iostream>
#include <math.h>
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
  int offset;

public:
  ndarray(double *data, int size);
  ndarray(double *data, int size, int *dim, int l);
  ndarray *__add__(double x);
  ndarray *__add__(ndarray *arr);
  ndarray *__sub__(ndarray *arr);
  ndarray *__mul__(double x);
  ndarray *__mul__(ndarray *arr);
  ndarray *__div__(ndarray *arr);
  ndarray *__power__(double num);
  ndarray *__apply__(double fun_f(double));
  double __at__(int *idxs, int l);
  void __set__(double val, int *idxs, int l);
  ndarray *__get_subndarray__(int *idxs, int l);
  void __set_subndarray__(ndarray *arr, int *idxs, int l);
  void __set_strides__(int *s, int l);
  void __reshape__(int *s, int l);
  double flat(int idx);
  int flat_index(int idx);
  ndarray *clone();
  double at(int idx, ...);
  void set(double val, int idx, ...);
  ndarray *get_subndarray(int idx, ...);
  void set_subndarray(ndarray *arr, int idx, ...);
  int *shape();
  void set_strides(int s, ...);
  void reshape(int s, ...);
  void transpose();
  ndarray *dot(ndarray *arr);
  ndarray *sum(int axis, ...);
  ndarray *mean(int axis, ...);
  ndarray *std(int axis, ...);

  static ndarray *add(ndarray *arr1, ndarray *arr2);
  static ndarray *add(ndarray *arr1, double num);
  static ndarray *sub(ndarray *arr1, ndarray *arr2);
  static ndarray *mul(ndarray *arr1, ndarray *arr2);
  static ndarray *mul(ndarray *arr1, double num);
  static ndarray *div(ndarray *arr1, ndarray *arr2);
  static ndarray *power(ndarray *arr1, double num);
  static ndarray *apply(ndarray *arr1, double fun_f(double));

  static ndarray *einsum(ndarray *arr1, string idx_fmt1, ndarray *arr2,
                         string idx_fmt2);
  static ndarray *einsum(ndarray *arr1, string idx_fmt1, string idx_fmt2);
  static ndarray *dot(ndarray *arr1, ndarray *arr2);
  static ndarray *sum(ndarray *arr1, int *axis, int l);
  static ndarray *mean(ndarray *arr1, int *axis, int l);
  static ndarray *std(ndarray *arr1, int *axis, int l);
};
#endif
