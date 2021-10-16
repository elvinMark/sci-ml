#include <sciml/data/ndarray.hpp>

using namespace std;
int main() {
  double data_[4] = {1.2, 3.4, 5.6, 6.7};
  ndarray *d = new ndarray(data_, 4);
  d->reshape(2, 2, END_OF_LIST);
  cout << d->at(0, 1, -2) << endl;
  return 0;
}
