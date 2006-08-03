#!/bin/bash
echo "Starting vec_test"
time ./vec_test.x
./profiler.sh vec_test.x
echo "Starting basevector_test"
time ./basevector_test.x
./profiler.sh basevector_test.x
echo "Starting queuevector_test"
time ./queuevector_test.x
./profiler.sh queuevector_test.x
echo "Starting dequevector_test"
time ./dequevector_test.x
./profiler.sh dequevector_test.x
echo "Starting stackvector_test"
time ./stackvector_test.x
./profiler.sh stackvector_test.x
echo "Starting list_test"
time ./list_test.x
./profiler.sh list_test.x
echo "Starting dequelist_test"
time ./dequelist_test.x
./profiler.sh dequelist_test.x
echo "Starting queuelist_test"
time ./queuelist_test.x
./profiler.sh queuelist_test.x
echo "Starting stacklist_test"
time ./stacklist_test.x
./profiler.sh stacklist_test.x
echo "Starting binarytree_test"
time ./binarytree_test.x
./profiler.sh binarytree_test.x
