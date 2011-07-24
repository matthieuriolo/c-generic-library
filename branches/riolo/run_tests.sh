#!/bin/bash
echo "Starting vec_test"
time ./tests/vec_test
echo "Starting basevector_test"
time ./tests/basevector_test
echo "Starting queuevector_test"
time ./tests/queuevector_test
echo "Starting dequevector_test"
time ./tests/dequevector_test
echo "Starting stackvector_test"
time ./tests/stackvector_test
echo "Starting dequelist_test"
time ./tests/dequelist_test
echo "Starting queuelist_test"
time ./tests/queuelist_test
echo "Starting stacklist_test"
time ./tests/stacklist_test
echo "Starting binarytree_test"
time ./tests/binarytree_test
echo "Starting openhash_test"
time ./tests/openhash_test
echo "Starting closedhash_test"
time ./tests/closedhash_test
echo "Starting heap_test"
time ./tests/heap_test
echo "Starting prio_test"
time ./tests/prio_test
