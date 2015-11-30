#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

const int MAXN = 1e8, MAXVAL = 1e5;

void heap (int a[], int n, int b){
	if (b) {
		int j = 0;
		while (j <= n/2-1){
			int cur = a[j];
			int child = 2 * j;
			if (child < n - 1 && a[child] > a[child + 1]){
				child++;
			}
			if (cur > a[child]) {
				a[j] = a[child];
				a[child] = cur;
				j = child;
			}
			else{
				break;
			}
		}
		return;
	}
	int i;
	for (i = (n - 1) / 2; i > 0; --i){
		int j = i;
		while (2 * j + 1 < n){
			int cur = a[j];
			int child = 2 * j + 1;
			if (child + 1 < n && a[child] > a[child + 1]){
				child++;
			}
			if (cur > a[child]) {
				a[j] = a[child];
				a[child] = cur;
				j = child;
			}
			else{
				break;
			}
		}
	}
	return;
}

void heapSort (int a[], int n){
	heap(a, n, 0);
	int i;
	int * res = malloc(sizeof(int) * n);
	for (i = n - 1; i >= 0; --i) {
		int t = a[i];
		a[i] = a[0];
		a[0] = t;
		heap(a, i, 1);
	}
	for (i = 0; i < n / 2; ++i){
		int t = a[i];
		a[i] = a[n - 1 - i];
		a[n - 1 - i] = t;
	}
	return;
}
		


void SlowlySort(int a[], int n){
	int t;
	int i, j;
	for (i = 0; i < n; ++i){
		for (j = i + 1; j < n; ++j) {
			if (a[i] > a[j]) {
				t = a[i];
				a[i] = a[j];
				a[j] = t;
			}
		}
	}
	return;
}

void line(int a[], int n){
	int * res = malloc(sizeof(int) * MAXVAL);
	int i;
	for (i = 0; i < MAXVAL; ++i){
		res[i] = 0;
	}
	for (i = 0; i < n; ++i){
		res[a[i]]++;
	}
	return;
}

int main(){
	
	FILE *in = fopen("test.out", "r");
	FILE *out = fopen("ans", "w"); 
	
	
	int n = MAXN;
	
	int num = 1, start_time, end_time;
	
	int * b = malloc(sizeof(int) * n);
	int * a = malloc(sizeof(int) * n); 
	int * c = malloc(sizeof(int) * n);
	int i;
	
	for (i = 0; i < n; ++i){
		b[i] = a[i] = c[i] = rand() % MAXVAL;
	}
	
	
	
	
	start_time = clock();
	
	for (i = 0; i < num; ++i) {
		SlowlySort(b, n);
	}
	
	end_time = clock();
	
	fprintf(out, "\nslowly = %f", (float)(end_time - start_time) / num);
	
	
	
	start_time = clock();
	
	for (i = 0; i < num; ++i) {
		line(c, n);
	}
	
	end_time = clock();
	
	fprintf(out, "\nline = %f", (float)(end_time - start_time) / num);
	
	
	
	start_time = clock();
	
	for (i = 0; i < num; ++i) {
		heapSort(a, n);
	}
	
	end_time = clock();
	
	fprintf(out, "\nheap = %f", (float)(end_time - start_time) / num);


	return 0;
}
