#!/bin/sh 
opcontrol --reset; opcontrol --no-vmlinux --callgraph=3 --separate=library --start; ./tests/$1;  opcontrol --shutdown; opreport -dgarl | grep $1

