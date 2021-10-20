CC=g++
INCLUDE_DIR=./include/
LIBFLAGS =-lm
test_ndarray:
	$(CC) -I$(INCLUDE_DIR) -c src/utils/useful_functions.cpp -o third_party/useful_functions.o
	$(CC) -I$(INCLUDE_DIR) -c src/linalg/linalg.cpp -o third_party/linalg.o
	$(CC) -I$(INCLUDE_DIR) -c src/data/ndarray.cpp -o third_party/ndarray.o
	$(CC) -I$(INCLUDE_DIR) -c test/test_ndarray.cpp -o third_party/test_ndarray.o
	$(CC) third_party/*.o $(LIBFLAGS) -o third_party/a.out
