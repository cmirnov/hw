#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string.h>

struct list{
    int val;
    char hash[255];
    struct list *next;
}; typedef struct list list;


struct hash_array{
    list *head;
}; typedef struct hash_array array;

struct hash_table{
    int size;
    array *arr;
    int (*callback)(char*);
}; typedef struct hash_table table;
table tbl;

typedef int (*callback_param_func)(char *param);

int call_hash_func(callback_param_func func, char *param){
    return func(param);
}

void clean(list *cur){
	list *tmp;
    while (cur != NULL){
        tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    return;
}

list *find(char *c){
    long long Hsh = call_hash_func(tbl.callback, c);
    int pos = (Hsh % tbl.size + tbl.size) % tbl.size;
    list *cur = tbl.arr[pos].head;
    list *tmp;
    while (cur->next != NULL){
        tmp = cur->next;
		if (strcmp(tmp->hash, c) == 0){
            break;
        }
        cur = cur->next;
    }
    return cur;
}


int max(int a, int b){
   if (a > b){
        return a;
    } else {
        return b;
    }
}

int min(int a, int b){
    if (a < b){
        return a;
    } else {
        return b;
    }
}




void create(int(*func)(char*), int num){
    int i;
    tbl.size = num;
    tbl.arr = (array*)malloc(num * sizeof(array));
    if (tbl.arr == NULL){
        printf("run out of memory\n");
        return;
    }
    tbl.callback = func;
    for (i = 0; i < num; ++i){
        tbl.arr[i].head = malloc(sizeof(list));
        if(tbl.arr[i].head == NULL){
            printf("run out of memory\n");
            return;
        }
        (tbl.arr[i].head)->next = NULL;
        (tbl.arr[i].head)->val = 0;
    }
    return;
}

void del(){
    int i;
    int size = tbl.size;
    for (i = 0; i < size; ++i){
        clean(tbl.arr[i].head);
    }
    free(tbl.arr);
    return;
}

void add(char *c){
    list *cur = find(c);
    if (cur->next == NULL){
        list *nw = (list*)malloc(sizeof(list));
        if (nw == NULL){
            printf("run out of memory\n");
            return;
        }
        cur->next = nw;
        nw->next = NULL;
        nw->val = 1;
        strcpy(nw->hash, c);
    } else {
        cur = cur->next;
        cur->val++;
    }
    return;
}

void erase(char *c){
    list *cur = find(c);
    if (cur->next == NULL){
        printf("fail\n");
    } else {
        /*cur = cur->next;
        if (cur->val == 0){
            printf("fail\n");
        } else {
            cur->val--;
        }*/
        list *t = cur->next;
        cur->next = t->next;
        free(t);
    }
    return;
}

void val(char *c){
    list *cur = find(c);
    printf("number");
    if (cur->next == NULL){
        printf("0\n");
    } else {
        cur = cur->next;
        printf("%d\n", cur->val);
    }
    return;
}

void statistic(){
    int i = 0;
    int number_cells = 0;
    int number_elem = 0;
    int sum_len_chain = 0;
    int max_len_chain = 0;
    int min_len_chain = 1e9;
    int max_elem = 0;
    int mid_len_chain = 0;
    for (i = 0; i < tbl.size; ++i){
        list *cur = tbl.arr[i].head;
        int cur_len = 0;
        while (cur != NULL){
            cur_len++;
            number_elem += cur->val;
            max_elem = max(max_elem, cur->val);
            cur = cur->next;
        }
        cur_len--;
        if (cur_len > 0){
            number_cells++;
            min_len_chain = min(min_len_chain, cur_len);
        }
        sum_len_chain += cur_len;
        max_len_chain = max(max_len_chain, cur_len);
    }
    if (number_cells != 0){
        mid_len_chain = sum_len_chain / number_cells;
    }
    if (min_len_chain == 1e9){
        min_len_chain = -1;
    }
    printf("Number of using cells: %d\n", number_cells);
    printf("Number of elements: %d\n", number_elem);
    printf("Average length of chains: %d\n", mid_len_chain);
    printf("Minimal length of chains: %d\n", min_len_chain);
    printf("Maximal length of chains: %d\n", max_len_chain);
    printf("Maximal element: %d\n", max_elem);
    return;
}

/////////////////////////////////////////////////////////

int hash1(char *c){
    return 3;
}

int hash2(char *c){
    int sum = 0;
    while (*c){
        sum += *c;
        c++;
    }
    return sum;
}

int hash3(char *c){
    const int p = 300;
    long long hash = 0;
    int i;
    for (i = 0; i < strlen(c); ++i){
    	hash *= p;
    	hash += c[i];
	}
    return hash;
}

/////////////////////////////////////////////////////////

int main()
{
    double start = clock();
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    const int size = 42*42*42;
    create(hash3, size);
    char c[100];
    while (scanf("%s", c) != EOF){
        size_t len = strlen(c) - 1;
        while (len >= 0 && !isalpha(c[len])){
            c[len] = '\0';
            len--;
        }
        add(c);
    }
    statistic();
    del();
    printf("%f", (clock() - start) / CLOCKS_PER_SEC);
    return 0;
}
