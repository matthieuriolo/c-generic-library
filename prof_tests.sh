#!/bin/bash
echo "Starting vec_test"
time ./tests/vec_test
./profiler.sh vec_test
echo "Starting basevector_test"
time ./tests/basevector_test
./profiler.sh basevector_test
echo "Starting queuevector_test"
time ./tests/queuevector_test
./profiler.sh queuevector_test
echo "Starting dequevector_test"
time ./tests/dequevector_test
./profiler.sh dequevector_test
echo "Starting stackvector_test"
time ./tests/stackvector_test
./profiler.sh stackvector_test
echo "Starting list_test"
time ./tests/list_test
./profiler.sh list_test
echo "Starting dequelist_test"
time ./tests/dequelist_test
./profiler.sh dequelist_test
echo "Starting queuelist_test"
time ./tests/queuelist_test
./profiler.sh queuelist_test
echo "Starting stacklist_test"
time ./tests/stacklist_test
./profiler.sh stacklist_test
echo "Starting binarytree_test"
time ./tests/binarytree_test
./profiler.sh binarytree_test
