#include <sciml/data/ndarray.hpp>

using namespace std;
int main() {
  double data_[3] = {1.2, 3.4, 5.6};
  ndarray *d = new ndarray(data_, 3);
  cout << d->strides[0] << endl;
  return 0;
}
