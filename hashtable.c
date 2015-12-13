#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define MAXN 100000



	
typedef struct node {
	int val;
	struct node *next;
} node;

void set(node **a, int hash, int data){

	node *t = (node*)malloc(sizeof(node));
	
	t->val = data;
	
	node *head = a[hash];
	
	if (t == 0){
		printf("run out of memory\n");
		return;
	}
	
	if (a[hash] == NULL){
		t->next = NULL;
		a[hash] = t;
		return; 	
	}
	
	else{
		node *last;
		last = a[hash];
		if (last->next == NULL){
			last->next = t;
			t->next = NULL;
			return;
		}
		else{
			while (last->next->next != NULL){
				last = last->next;
			}
			last->next->next = t;
			t->next = NULL;
		}
	}
	return;
}


void get(FILE* w, node **a, int hash){	
	if (a[hash] == NULL){
		fprintf(w, "Empty\n");
		return;
	}
	node *cur;
	cur = a[hash];
	
	while (cur->next != NULL){
		fprintf(w, "%d\t", cur->val);
		cur = cur->next;
	}
	fprintf(w, "%d\n", cur->val);
	return;
}


void rem (node **head, int hash, int size){
	node *t = head[hash];
	if	(head[hash] == NULL){
		printf("Empty\n");
		return;
	}
	if (t->val == size){
		head[hash] = t->next;
		free(t);
		return;		
	}
	while (t->next->val != size && t->next->next != NULL){
		t = t->next;
	}
	if (t->next->val == size){
		node *cur = t->next;
		t->next = t->next->next;
		free(cur);
		return;
	}
	if (t->next->next == NULL){
		printf("not found\n");
		return;
	}
	return;
}

void clear (node **head){
	int i;
	for (i = 0; i < MAXN; ++i){
		node *t = head[i];
		while(head[i] != NULL){
			head[i] = (head[i])->next;
			free(t);
			t = head[i];
		}
	}
	return;
}


void print(FILE *w, node **a){
	int i;
	for (i = 0; i < MAXN; ++i){
		get(w, a, i);
	}
}


int len(node **head, int hash){
	int res = 1;
	node *t = head[hash];
	if (t == NULL){
		return 0;
	}
	while (t->next != NULL){
		t = t->next;
		res++;
	}
	return res;
}

void printans(FILE *w, node **a){
	int i, t;
	for (i = 0; i < MAXN; ++i){
		t = len(a, i);
		if (t == 0){
			//fprintf(w, "Empty\n");
		}
		else{
			fprintf(w, "%d\n", t);
		}
	}
	return;
}

void statistics (FILE *w, node **head){
	int i;
	int num, nonempt = 0, min = MAXN, max = 0, t;
	for (i = 0; i < MAXN; ++i){
		t = len(head, i);
		num += t;
		if (t != 0){
			nonempt++;
		}
		if (min > t && t > 0){
			min = t;
		}
		if (max < t){	
			max = t;
		}
	}
	fprintf(w, "non empty = %d\n", nonempt);
	fprintf(w, "num = %d\n", num);
	fprintf(w, "mid = %f\n", ((float)num/(float)MAXN));
	fprintf(w, "mid without empty = %f\n", (float)num/(float)nonempt);
	fprintf(w, "min = %d\n", min);
	fprintf(w, "max = %d\n", max);
	return;
}	

////////////////////////////////////////////////////////////////////////////////////

int hash1 (char *s, int size){
	return 1;
}

int hash2 (char *s, int size){
	int res = 0;
	int i;
	for (i = 0; i < size; ++i){
		res += s[i];
	}
	return res;
}

int hash3 (char *s, int size){
	int div = 1 << 22, q = 1 << 8;
	int res = 0;
	int i;
	for (i = 0; i < size; ++i){
		res *= q;
		res += s[i];
	}
	return res;
}




////////////////////////////////////////////




int main() {
	
	FILE *r = fopen("input.txt", "r");
	FILE *w = fopen("output1.txt", "w");
	
	if (r == NULL){
		printf("u looser\n");
		return 0;
	}
	node *a[MAXN];
	int i;
	for (i = 0; i < MAXN; ++i){
		a[i] = NULL;
	}
	
	int start_time, end_time;
	start_time = clock();
	char s[256];
	int hash;
	int c;
	int j  = 0, size;
	while (c != EOF && (c = fgetc(r))){
		if (isalpha(c)){
			s[j] = c;
			j++;
		}
		else{
			s[j] = '\0'; 
			size = j;
			j = 0;
		}
		if (j == 0 && size != 0){
			hash = hash1(s, strlen(s));
			hash %= MAXN;
			set(a, hash, size);
		}
	}
	
	end_time = clock();
	
	//statistics (w, a);
	//clear (a);
	
	printans(w, a);

	
	fprintf(w, "%d", end_time - start_time);
	return 0;
}



///////////////////
/*
hash1
non empty = 1
num = 32771
mid = 0.327710
mid without empty = 32771.000000
min = 32770
max = 32770
time = 2281


hash2
non empty = 888
num = 32771
mid = 0.327710
mid without empty = 36.904278
min = 1
max = 999
time = 79

hash3
non empty = 2656
num = 32771
mid = 0.327710
mid without empty = 12.338479
min = 1
max = 992
time = 60
*/
