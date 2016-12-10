/**********************************
This is for Purdue CS250 2015 fall
please do not modify this file
**********************************/
#include<stdio.h>
#include<sys/time.h>
#include<string.h>
#include<stdlib.h>
int cnt = 1;
double get_time();
void get_array(int *a, int n);
void get_rand_array(int *a, int n);
void cbub(int *a, int n);
int cpartition(int *a, int n);
void cqs(int *a, int n);
void check(int *a, int n);
int main(int argc, char** argv)
{
	int n, in[1000005], i;
	double start, stop;
	srand(42);
	if(argc == 2 && !strcmp(argv[1], "bubble"))
	{
		printf("Enter length of array:\n");
		scanf("%d",&n);
		printf("Enter numbers:\n");
		for(i=0;i<n;i++)
			scanf("%d",in+i);
		bubble(in, n);
		//cbub(in, n);
		printf("After sort:\n");
		for(i=0;i<n;i++)
			printf("%d ",in[i]);
		printf("\n");
	}
	else if(argc == 2 && !strcmp(argv[1], "quicksort"))
	{
		printf("Enter length of array:\n");
		scanf("%d",&n);
		printf("Enter numbers:\n");
		for(i=0;i<n;i++)
			scanf("%d",in+i);
		quicksort(in, n);
		//cqs(in, n);
		printf("After sort:\n");
		for(i=0;i<n;i++)
			printf("%d ",in[i]);
		printf("\n");
	}
	else if(argc == 2 && !strcmp(argv[1], "compare"))
	{
		for(n = 1; n<=100000; n*=10){
			printf("Size: %d\n", n);
			get_array(in, n);
			start = get_time();
			bubble(in, n);
			stop = get_time();
			printf("Bubble sort used %.12f secs\n", stop - start);
			get_array(in ,n);
			start = get_time();
			quicksort(in, n);
			stop = get_time();
			printf("Quick sort used %.12f secs\n", stop - start);
		}
	}
	else if(argc == 2 && !strcmp(argv[1], "test"))
	{
		in[0] = 2147483640;
		check(in, 1);
		for(i=0;i<9;i++){
			n = rand()%9999 + 1;
			get_rand_array(in, n);
			check(in, n);
		}
	}
	else
	{
		printf("*******************Usage****************\n");
		printf("Test your bubble by './main_sort bubble'\n");
		printf("Test your qsort by './main_sort quicksort'\n");
		printf("Compare performance by './main_sort compare'\n");
	}
}
double get_time(){
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec + tv.tv_usec/1000000.0;
}
void get_array(int *a, int n){
	int i;
	for(i=0;i<n;i++)
		a[i] = i*7%n;
}
void get_rand_array(int *a, int n){
	int i;
	for(i=0;i<n;i++)
		a[i] = rand();
}
void cbub(int *a, int n){
	int i, j, temp;
	for(i=1;i<n;i++)
		for(j=0;j<n-i;j++){
			if(a[j + 1] < a[j]){
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
}
int cpartition(int *a, int n){
	int pivot = a[n - 1];
	int i = 0, j, temp;
	for(j = i;j < n - 1; j++){
		if(a[j] < pivot){
			//swap a[i] and a[j]
			temp = a[i];
			a[i] = a[j];
			a[j] = temp;
			i++;
		}	
	}
	temp = a[n-1];
	a[n-1] = a[i];
	a[i] = temp;
	return i;
}
void cqs(int *a, int n){
	if(n > 1){
		int p = cpartition(a, n);
		cqs(&a[0], p);
		cqs(&a[p+1], n - p - 1);
	}
}
void check(int *a, int n){
	int i, *b, *c;
	b = (int*)malloc(sizeof(int)*n);
	c = (int*)malloc(sizeof(int)*n);
	memcpy(b, a, sizeof(int)*n);
	memcpy(c, a, sizeof(int)*n);
	cqs(a, n);
	bubble(b, n);
	quicksort(c, n);
	printf("Case %d:\n",cnt++);
	for(i=0;i<n;i++){
		int bf = 0;
		if(a[i]!=b[i]){
			printf("bubble failed at index %d: yours is %d, should be %d\n", i, b[i], a[i]);
			bf = 1;
		}
		if(a[i]!=c[i]){
			printf("quick sort failed at index %d: yours is %d, should be %d\n", i, c[i], a[i]);
			bf = 1;
		}
		if(bf){
			free(b);
			free(c);
			return;
		}
	}
	free(b);
	free(c);
	printf("Passed!\n");
}