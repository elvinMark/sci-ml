#include <sciml/ml/pca.hpp>

PCA::PCA(int n_components) { this->ncomponents = n_components; }

void PCA::fit(ndarray *arr) {
  if (arr->dim_length > 2) {
    // ERROR
    assert_error(DIM_TOO_HIGH);
  }
}

ndarray *PCA::transform(ndarray *arr) {}

ndarray *PCA::fit_transform(ndarray *arr) {
  this->fit(arr);
  return this->transform(arr);
}
