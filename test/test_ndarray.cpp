#include <sciml/data/ndarray.hpp>
#include <sciml/linalg/linalg.hpp>
#include <sciml/utils/useful_functions.hpp>

using namespace std;
int main() {

  ndarray *d1 = ndarray::random(2, 3, 3, 3, END);
  ndarray *d2;

  cout << d1->__str__() << endl;
  d2 = inv(d1);
  cout << "det: " << endl;
  cout << d2->__str__() << endl;

  return 0;
}
