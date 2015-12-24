#include<stdio.h>
#include<stdlib.h>


typedef struct node {
	int val;
	struct node *left;
	struct node *right;
} node;

void add (node **head, int num){
	node *t = (node*)malloc(sizeof(node));	
	if (t == NULL){
		printf("run out of memory\n");
		return;
	}
	t->val = num;
	t->left = NULL;
	t->right = NULL;

	if (*head == NULL){
		//printf("do");
		(*head) = t;
		return;
	}
	node *cur = *head;
	while (cur->right != NULL || cur->left != NULL){
		if (cur->val <= num){
			if (cur->right != NULL){
				cur = cur->right;
			}
			else{
				cur->right = t;
				return;
			}
		}
		else{
			if (cur->left != NULL){
				cur = cur->left;
			}
			else{
				cur->left = t;
				return;
			}
		}
	}
	if (cur->val <= num){
		cur->right = t;
		return;
	}
		
	else{
			
		cur->left = t;
		return;
	}
}

node *check(node **head, int val){
	if (*head == NULL){
		printf("wrong\n");
		return NULL;
	}
	node *t = *head;
	if (t->val == val){
		return t;
	}
	if (val > t->val){
		if (t->right == NULL){
			return NULL;
		}
		return check(&(*head)->right, val);
	}
	else{
		if (t->left == NULL){
			return NULL;
		}
		return check(&(*head)->left, val);
	}
}

void printinc (node **head){
	if (*head == NULL){
		return;
	}
	printinc (&(*head)->left);
	printf("%d\t", (*head)->val);
	printinc (&(*head)->right);
	return;
}


void printdec (node **head){
	if (*head == NULL){
		return;
	}
	printdec (&(*head)->right);
	printf("%d\t", (*head)->val);
	printdec (&(*head)->left);
	return;
}

void print (node **head){
	if ((*head) == NULL){
		printf(" null ");
		return;
	}
	printf("(%d ", (*head)->val);
	print(&(*head)->left);
	print(&(*head)->right);
	printf(" )");
}

node *erase (node **head, int val){
	node *t = *head;
	if (t == NULL){
		printf("not found\n");
		return t;
	}
	if (val > t->val){
		t->right = erase(&(t->right), val);
		return t;
	}
	if (val < t->val){
		t->left = erase(&(t->left), val);
		return t;
	}
	if (val == t->val){
		if (t->left == NULL && t->right == NULL){
			
			free(*head);
			return NULL;
		}
		if (t->left == NULL){
			free(*head);
			return t->right;
		}
		if (t->right == NULL){
			free(*head);
			return t->left;
		}
		t = t->left;
		while (t->right != NULL){
			t = t->right;
		}
		(*head)->val = t->val;
		(*head)->left = erase(&(*head)->left, (*head)->val);
		return *head;
			
	}
}

void clear(node **head){
	if ((head) == NULL){
		return;
	}
	node *t = *head;
	clear(&(t->left));
	clear(&t->right);
	free(head);
	return;
}

int main(){
	node *head;
	head = NULL;
	int j = 0;
	while(j == 0)
    {
        char c;
        int cur;
        scanf("%c", &c);
        switch (c)
        {
            case 'a':
                scanf("%d", &cur);
                add(&head, cur);
            break;
            case 'r':
                scanf("%d", &cur);
                head = erase(&head, cur);
            break;
            case 'i':
                scanf("%d", &cur);
                check(&head, cur);
            break;
            case 'p':
                print(&head);
                printf("\n");
            break;
             case 'u':
                printinc(&head);
                printf("\n");
            break;
             case 'd':
                printdec(&head);
                printf("\n");
            break;
            case 'c':
                clear(&head);
                j = 1;
            break;
        }
    }
}
