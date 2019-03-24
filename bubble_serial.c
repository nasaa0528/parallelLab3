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
void swap(unsigned long int *list, int i, int j){
	unsigned long int tmp = list[i]; 
	list[i] = list[j]; 
	list[j] = tmp; 
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
	clock_t start, end; 
	for(i = 0; i < n; i++){
		list[i] = rand()%1000; 
	}
	int swapped = FALSE; 
	if(debug == TRUE){
		printf("*** Unsorted List ***\n"); 
		printList(list, len); 
	}
	else if(debug == 2){
		start = clock(); 
	}
	while(TRUE){
		swapped = FALSE; 
		for(i = 0; i < n - 1; i++){
			if(list[i] > list[i+1]){
				swap(list, i, i+1); 
				swapped = TRUE; 
			}
		}
		n = n - 1;
		if(swapped==FALSE){
		break; 
		}
	}
	if(debug == TRUE){
		printf("*** Sorted List ***\n"); 
		printList(list, len); 
	}
	else if(debug == 2){
		end = clock();
		printf("%10.10f\n", (double)(end - start) / CLOCKS_PER_SEC); 
	}
	free(list);
	return 0;
}
