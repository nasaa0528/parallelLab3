#!/bin/bash 

for i in 10 100 1000 10000 100000 1000000 10000000 100000000
do
	echo "Data size: $i " >> serial.result
	./bubble_serial $i 2 >> serial.result 
done
