#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
	
	printf("input string\n");	
	char s[255];
	gets(s);
	
	printf("input char\n");
	char c;
	scanf("%c", &c);
	
	int i;
	for (i = 0; i < strlen(s); ++i){
		if (s[i] != c){
			printf("%c", s[i]);
		}
	}
	
	return 0;
}
