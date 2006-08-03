#!/bin/sh 
opcontrol --reset; opcontrol --no-vmlinux --callgraph=3 --separate=library --start; ./$1;  opcontrol --shutdown; opreport -dgarl | grep $1

