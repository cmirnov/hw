#include<stdio.h>

union bits {
	float f;
	long long n;
};

int main(){
	
	bits b;
	
	float f;
	
	scanf ("%f", &f);

	int* n = (int*)(&f);

	int sign = (*n & (1 << 31)) >> 31; 
	int exp = (*n >> 23) & 0xFF;
	int man = (*n  & (((1 << 31) >> 31) ^ ((1 << 31) >> 8)));
	
	printf("float = (-1)^%d * 1.%d * 2^(%d)", sign, man, (exp - 127));
	
	return 0;
}
