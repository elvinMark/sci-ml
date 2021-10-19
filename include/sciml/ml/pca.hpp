#ifndef PCA
#define PCA

#include <iostream>
#include <sciml/data/ndarray.hpp>

class PCA {
public:
  int n_components;
  ndarray *eig_vectors;
  ndarray *eigvals;

public:
  PCA(int n_components);
  void fit(ndarray *arr1);
  ndarray *transform(ndarray *arr1);
  ndarray *fit_transform(ndarray *arr1);
}

#endif
