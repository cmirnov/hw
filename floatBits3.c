#include<stdio.h>
#include<math.h>

int main(){
	
	
	float f, f2;
	
	scanf ("%f%f", &f, &f2);
	
	
	if (f2 == -1){
		f = sqrt(f);
	}
	else{
		f = f/f2;
	}
	

	int* n = (int*)&f;
	

	int sign = ((*n) >> 31) & 1; 
	int exp = ((*n)>> 23) & 0xFF;
	int man = (*n  & 0X7FFFFF);
	
	if (exp == 0XFF){
		if (man == 0){
			printf(sign ? "-inf\n" : "+inf\n");
		}
		else{
			printf("NaN\n");
		}
		return 0;
	}
	
	printf("float = (-1)^%d * 1.%d * 2^(%d)", sign, man, (exp - 127));
	
	return 0;
}
