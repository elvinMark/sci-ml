#ifndef RANDOM
#define RANDOM

#include <sciml/data/ndarray.hpp>
#include <sciml/utils/useful_functions.hpp>
#include <stdarg.h>
#include <time.h>

ndarray *random(int d, ...);
ndarray *random(int *d, int l);

#endif
