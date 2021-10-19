#ifndef LINALG
#define LINALG

ndarray *__det__(ndarray *arr);
ndarray *__inv__(ndarray *arr);
ndarray **__qr__(ndarray *arr);
ndarray **__eig__(ndarray *arr);

ndarray *det(ndarray *arr);
ndarray *inv(ndarray *arr);
ndarray **qr(ndarray *arr);
ndarray **eig(ndarray *arr);

#endif LINALG
