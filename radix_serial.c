#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#define TRUE 1
#define FALSE 0 

void usage(){
	printf("Usage: \n");
	printf("Bubble sort serial implementation.\n");
	printf("Generates random vector and sorts it using bubble sort.\n");
	printf("$:gcc bubble_serial.c -o bubble_serial\n");
	printf("Running\n"); 
	printf("$:./bubble_serial <size> <debug|time>"); 
}

void printList(unsigned long int *list, unsigned long int size)
{
	int i; 
	for(i = 0; i < size; i++)
		printf("%lu%c", list[i], (i==size-1) ? '\n': ' '); 
}

int getMax(unsigned long int *list, int n){
	int mx = list[0]; 
	int i; 
	for(i = 1; i < n; i++)
		if(list[i] > mx)
			mx = list[i];
	return mx; 
}
void countSort(unsigned long int *list, int n, int exp)
{
	unsigned long int *output = malloc(n*sizeof(unsigned long int)); 
	int i, count[10] = {0}; 

	for(i = 0; i < n; i++)
		count[ (list[i]/exp)%10 ]++; 

	for(i = 1; i < 10; i++)
		count[i] += count[i - 1]; 

	for(i = n - 1; i >= 0; i--)
	{
		output[count[ (list[i]/exp)%10 ] - 1] = list[i]; 
		count[ (list[i]/exp)%10 ]--; 
	}
	
	for(i = 0; i < n; i++)
		list[i] = output[i];
}

void radixsort(unsigned long int *list, int n)
{
	int exp; 
	int m = getMax(list,n); 
	for(exp = 1; m / exp > 0; exp *= 10)
		countSort(list,n,exp); 
}

int main(int argc, char *argv[]){
	if(argc != 3){
		usage(); 
		exit(EXIT_FAILURE); 
	}
	unsigned long int n = atoi(argv[1]); 
	int debug = atoi(argv[2]); 
	int i;
	unsigned long int len = n; 
	unsigned long int *list = malloc(n*sizeof(unsigned long int)); 
	clock_t start; 
	for(i = 0; i < n; i++){
		list[i] = rand()%100000; 
	}

	if(debug == TRUE){
		printf("*** Unsorted List ***\n"); 
		printList(list, len);
	}
	else if (debug == 2){
		start = clock(); 
	}
	radixsort(list, n); 
	if(debug == TRUE) {
		printf("*** Sorted List ***\n"); 
		printList(list, len);
	}
	else if(debug == 2) {
		printf("%10.10f\n", (double)(clock() - start) / CLOCKS_PER_SEC); 
	}
	free(list);
	return 0;
}
