#!/bin/bash 
for i in {1000000..100000000..1000000} 
do
	echo "Data size: $i " >> serial_time.txt
	./serial $i 2 >> serial_time.txt 
	echo "Data size: $i " >> parallel_time.txt
	./parallel $i >> parallel_time.txt 
done
