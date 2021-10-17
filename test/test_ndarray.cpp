#include <sciml/data/ndarray.hpp>
#include <sciml/data/random.hpp>
#include <sciml/utils/useful_functions.hpp>

using namespace std;
int main() {
  ndarray *d = random(2, 3, -2);
  // d->transpose();
  cout << d->at(0, 2, -2) << endl;
  return 0;
}
