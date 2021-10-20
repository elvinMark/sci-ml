#include <sciml/data/ndarray.hpp>
#include <sciml/linalg/linalg.hpp>
#include <sciml/utils/useful_functions.hpp>

using namespace std;
int main() {
  double data1[24] = {1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12,
                      13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};
  int dim1[4] = {1, 3, 2, 4};
  double data2[6] = {1, 2, 3, 4, 5, 6};
  int dim2[2] = {2, 3};
  int dim3[1] = {6};

  ndarray *d1 = new ndarray(data1, 24, dim1, 4);
  ndarray *d2 = new ndarray(data2, 6, dim2, 2);
  ndarray *d3 = new ndarray(data2, 6);
  ndarray **d4;
  // d3 = d1->dot(d2);
  // d3 = d1->sum(0, 1, -2);
  // d3 = d1->mean(1, -2);
  // d3 = d1->std(0, 1, -2);
  // d3 = d1->get_subndarray(1, ALL, 3, -2);
  // d3 = d1->get_subndarray(ALL, ALL, 1, -2)->dot(d2)->mean(0, -2);
  // cout << d3->at(0, -2) << endl;
  d1 = ndarray::random(3, 3, END_OF_LIST);
  cout << d1->__str__() << endl;
  d4 = __lu__(d1);
  cout << d4[0]->dot(d4[1])->__str__() << endl;
  // for (int i = 0; i < 3; i++) {
  //   for (int j = 0; j < 3; j++)
  //     cout << d3->at(i, j, -2) << " ";
  //   cout << endl;
  // }
  // cout << d3->at(1, -2) << endl;
  return 0;
}
