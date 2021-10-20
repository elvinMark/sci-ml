#ifndef LINALG
#define LINALG

#include <sciml/data/ndarray.hpp>
#include <sciml/utils/useful_functions.hpp>

ndarray **__lu__(ndarray *arr);
double __det__(ndarray *arr);
ndarray *__solve__(ndarray *arr, ndarray *b);
ndarray *__inv__(ndarray *arr);
ndarray **__qr__(ndarray *arr);
ndarray **__eig__(ndarray *arr);

ndarray *det(ndarray *arr);
ndarray *inv(ndarray *arr);
ndarray **qr(ndarray *arr);
ndarray **eig(ndarray *arr);

#endif
