#include <sciml/data/random.hpp>

ndarray *random(int d, ...) {
  va_list vl;
  int l;
  int *dim;

  va_start(vl, d);
  dim = args_to_list(vl, d, &l);
  va_end(vl);

  return random(dim, l);
}

ndarray *random(int *d, int l) {
  int size = prod_all_elements(d, l);
  double *data = (double *)malloc(sizeof(double) * size);
  int i;

  srand(time(NULL));

  for (i = 0; i < size; i++)
    data[i] = rand() % 10000 / 10000.0;

  return new ndarray(data, size, d, l);
}
