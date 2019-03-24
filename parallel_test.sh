#!/bin/bash 

for i in 10 100 1000 10000 100000 1000000 10000000 100000000
do
	echo "Data size: $i " >> parallel.result
	./bubble_parallel $i 2 >> parallel.result
done
