#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	int val;
	struct node *next;
} node;

void makering(node **head){
	if (*head == NULL){
		printf("impossible\n");
		return;
	}
	node *t = *head;
	while (t->next != NULL){
		t = t->next;
	}
	t->next = *head;
	printf("made ring\n");
	return;
}

void checkring(node **head){
	if (*head == NULL){
		printf("impossible\n");
		return;
	}
	node *t1, *t2;
	t1 = *head;
	t2 = (*head)->next;
	while (t2->next != NULL && t2->next->next != NULL && t1 != t2){
		t2 = t2->next->next;
		t1 = t1->next;
	}
	if (t1 == t2){
		printf("ring");
		return;
	}
	printf("no ring\n");
	return;
}

void add(node **head, int cur){
	node *t = (node*)malloc(sizeof(node));
	if (t == 0){
		printf("run out of memory\nbye");
		return 0;
	}
	t->val = cur;
	if (*head == NULL){
		t->next = *head;
		*head = t;
		return;
	}
	else{
		node *last;
		last = (*head);
		if (last->next == NULL){
			last->next = t;
			t->next = NULL;
		}
		else{
			while ((last->next)->next != NULL){
				last = (last->next);
			}
			(last->next)->next = t;
			t->next = NULL;
		}
	}
	return;
}

void rem(node **head, int num){
	node *t = (*head);
	if	(*head == NULL){
		printf("Empty\n");
		return;
	}
	if (t->val == num){
		*head = t->next;
		free(t);
		return;		
	}
	while (t->next->val != num && t->next->next != NULL){
		t = t->next;
	}
	if (t->next->val == num){
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

void print(node **head) {

	if (*head == NULL){
		printf("Empty\n");
		return;
	}

	node *cur;
	cur = (*head);
	//printf ("%d\n", cur->next);
	if (cur->next == NULL){
		printf("%d\n", cur->val);
		return;
	}
	while (cur->next != NULL){
		printf("%d\n", cur->val);
		cur = cur->next;	
	}
	printf("%d\n", cur->val);
	return;
}

void clear(node **head){
	node *t = *head;
	while(*head != NULL){
		*head = (*head)->next;
		free(t);
		t = *head;
	}
	return;
}

int main(){
	node * head;
	head = NULL;
	int b = 0, val;
	char cur;
	while (b == 0){
		scanf("%c", &cur);
		switch(cur){
			case 'a':
				scanf("%d", &val);
				add(&head, val);
			break;
			case 'r':
				scanf("%d", &val);
				rem(&head, val);
			break;
			case 'p':
				print(&head);
			break;
			case 'q':
				clear(&head);
				b = 1;
			break;
			case 'm':
				makering(&head);
			break;
			case 'c':
				checkring(&head);
			break;
		}
	}
	return 0;
}

