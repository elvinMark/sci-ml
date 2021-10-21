#include <sciml/data/ndarray.hpp>
#include <sciml/linalg/linalg.hpp>
#include <sciml/utils/useful_functions.hpp>

using namespace std;
int main() {

  ndarray *d1 = ndarray::random(2, 3, 3, 3, END);
  ndarray *d2 = ndarray::random(3, 3, END);
  ndarray *d3 = ndarray::random(3, 3, END);
  ndarray *d4, *d5;

  d4 = d2->get_subndarray(0, ALL, END);
  d5 = d3->get_subndarray(ALL, 0, END);

  d4->reshape(1, 3, END);
  d5->reshape(3, 1, END);

  print_list(d4->strides, d4->strides_length);
  print_list(d5->strides, d5->strides_length);

  cout << d2->__str__() << endl;
  cout << d4->__str__() << endl;
  cout << d3->__str__() << endl;
  cout << d5->__str__() << endl;
  cout << d3->dot(d2)->__str__() << endl;
  cout << d4->dot(d5)->__str__() << endl;
  // cout << d1->__str__() << endl;
  // d2 = inv(d1);
  // cout << "det: " << endl;
  // cout << d2->__str__() << endl;

  return 0;
}
