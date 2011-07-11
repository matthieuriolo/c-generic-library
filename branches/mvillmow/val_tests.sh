#!/bin/bash
echo "Starting vec_test"
time valgrind --tool=memcheck --show-reachable=yes --leak-check=yes ./tests/vec_test
echo "Starting vector_test"
time valgrind --tool=memcheck --show-reachable=yes --leak-check=yes ./tests/vector_test
echo "Starting basevector_test"
time valgrind --tool=memcheck --show-reachable=yes --leak-check=yes ./tests/basevector_test
echo "Starting queuevector_test"
time valgrind --tool=memcheck --show-reachable=yes --leak-check=yes ./tests/queuevector_test
echo "Starting dequevector_test"
time valgrind --tool=memcheck --show-reachable=yes --leak-check=yes ./tests/dequevector_test
echo "Starting stackvector_test"
time valgrind --tool=memcheck --show-reachable=yes --leak-check=yes ./tests/stackvector_test
echo "Starting list_test"
time valgrind --tool=memcheck --show-reachable=yes --leak-check=yes ./tests/list_test
echo "Starting dequelist_test"
time valgrind --tool=memcheck --show-reachable=yes --leak-check=yes ./tests/dequelist_test
echo "Starting queuelist_test"
time valgrind --tool=memcheck --show-reachable=yes --leak-check=yes ./tests/queuelist_test
echo "Starting stacklist_test"
time valgrind --tool=memcheck --show-reachable=yes --leak-check=yes ./tests/stacklist_test
echo "Starting binarytree_test"
time valgrind --tool=memcheck --show-reachable=yes --leak-check=yes ./tests/binarytree_test
echo "Starting openhash_test"
time valgrind --tool=memcheck --show-reachable=yes --leak-check=yes ./tests/openhash_test
echo "Starting closedhash_test"
time valgrind --tool=memcheck --show-reachable=yes --leak-check=yes ./tests/closedhash_test
echo "Starting heap_test"
time valgrind --tool=memcheck --show-reachable=yes --leak-check=yes ./tests/heap_test
echo "Starting prio_test"
time valgrind --tool=memcheck --show-reachable=yes --leak-check=yes ./tests/prio_test
