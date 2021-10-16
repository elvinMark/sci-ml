CC=g++
INCLUDE_DIR=./include/

test_ndarray:
	$(CC) -I$(INCLUDE_DIR) -c src/data/ndarray.cpp -o third_party/ndarray.o
	$(CC) -I$(INCLUDE_DIR) -c test/test_ndarray.cpp -o third_party/test_ndarray.o
	$(CC) third_party/*.o -o third_party/a.out
