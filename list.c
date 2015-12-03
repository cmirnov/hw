#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	int val;
	struct node *next;
} node;

void add(node **head, int cur){
	node *t = (node*)malloc(sizeof(node));
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


void quit(node **head){
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
				quit(&head);
				b = 1;
			break;
		}
	}
	return 0;
}

