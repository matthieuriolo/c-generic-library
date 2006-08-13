#!/bin/bash
echo "Starting vec_test"
time valgrind --tool=memcheck --show-reachable=yes --leak-check=yes ./vec_test.x
echo "Starting vector_test"
time valgrind --tool=memcheck --show-reachable=yes --leak-check=yes ./vector_test.x
echo "Starting basevector_test"
time valgrind --tool=memcheck --show-reachable=yes --leak-check=yes ./basevector_test.x
echo "Starting queuevector_test"
time valgrind --tool=memcheck --show-reachable=yes --leak-check=yes ./queuevector_test.x
echo "Starting dequevector_test"
time valgrind --tool=memcheck --show-reachable=yes --leak-check=yes ./dequevector_test.x
echo "Starting stackvector_test"
time valgrind --tool=memcheck --show-reachable=yes --leak-check=yes ./stackvector_test.x
echo "Starting list_test"
time valgrind --tool=memcheck --show-reachable=yes --leak-check=yes ./list_test.x
echo "Starting dequelist_test"
time valgrind --tool=memcheck --show-reachable=yes --leak-check=yes ./dequelist_test.x
echo "Starting queuelist_test"
time valgrind --tool=memcheck --show-reachable=yes --leak-check=yes ./queuelist_test.x
echo "Starting stacklist_test"
time valgrind --tool=memcheck --show-reachable=yes --leak-check=yes ./stacklist_test.x
echo "Starting binarytree_test"
time valgrind --tool=memcheck --show-reachable=yes --leak-check=yes ./binarytree_test.x
echo "Starting openhash_test"
time valgrind --tool=memcheck --show-reachable=yes --leak-check=yes ./openhash_test.x
echo "Starting closedhash_test"
time valgrind --tool=memcheck --show-reachable=yes --leak-check=yes ./closedhash_test.x
echo "Starting heap_test"
time valgrind --tool=memcheck --show-reachable=yes --leak-check=yes ./heap_test.x
