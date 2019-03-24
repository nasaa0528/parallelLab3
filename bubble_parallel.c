#include <stdio.h>
#include <stdlib.h> 
#include <omp.h> 
#include <time.h> 
#define TRUE 1
#define FALSE 0 

void usage(){
	printf("Usage: \n");
	printf("Bubble sort parallel implementation.\n");
	printf("Generates random vector and sorts it using bubble sort.\n");
	printf("$:gcc bubble.c -o bubble\n");
	printf("Running\n"); 
	printf("$:./bubble <size> <debug>"); 
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
	double start; 
	unsigned long int len = n; 
	unsigned long int *list=malloc(n*sizeof(unsigned long int)); 
	start = omp_get_wtime(); 
	#pragma omp parallel for 
	for(i = 0; i < n; i++){
		list[i] = rand()%1000; 
	}
	int sorted = FALSE; 
	if(debug == TRUE){
		printf("*** Unsorted List ***\n"); 
		printList(list, len); 
	}
	while(!sorted){
		sorted = TRUE;
		#pragma omp parallel for
		for(i = 1; i < n - 1; i+=2){
			if(list[i] > list[i+1]){
				swap(list, i, i+1); 
				sorted = FALSE; 
			}
		}
		#pragma omp parallel for 
		for(i = 0; i < n - 1; i+=2){
			if(list[i] > list[i+1])
			{
				swap(list,i,i+1); 
				sorted=FALSE; 
			}
		}
	}
	if(debug == TRUE){
		printf("*** Sorted List ***\n"); 
		printList(list, len); 
	}
	else if(debug == 2){ 
		printf("%10.10f\n", omp_get_wtime() - start); 
	}
	return 0;
}
