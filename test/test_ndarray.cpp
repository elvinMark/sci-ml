#include <sciml/data/ndarray.hpp>
#include <sciml/data/random.hpp>
#include <sciml/utils/useful_functions.hpp>

using namespace std;
int main() {
  double data1[6] = {1, 2, 3, 4, 5, 6};
  int dim1[2] = {2, 3};
  double data2[6] = {1, 2, 3, 4, 5, 6};
  int dim2[2] = {3, 2};

  ndarray *d1 = new ndarray(data1, 6, dim1, 2);
  ndarray *d2 = new ndarray(data2, 6, dim2, 2);
  ndarray *d3;

  // d3 = ndarray::einsum(d1, "ik", d2, "kj");
  d3 = d1->dot(d2);
  // d->transpose();
  // d->set(2.3, 0, 1, 0, -2);
  cout << d3->at(0, 1, -2) << endl;
  return 0;
}
