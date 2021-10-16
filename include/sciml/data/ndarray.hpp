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

public:
  ndarray(double *data, int size);
  ndarray *clone();
  double at(int idx, ...);
  ndarray *get(int idx, ...);
  void set(ndarray *arr, int idx, ...);
  int *shape();
  void set_strides(int s, ...);
  void set_strides(int *s, int l);
  void reshape(int s, ...);
  void reshape(int *s, int l);
  ndarray *dot(ndarray *arr);
};
#endif
