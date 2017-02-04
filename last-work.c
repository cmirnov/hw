#include <stdio.h>
#include <string.h>
#include "hashtables.h"

int main(){
    hashtables dict = createHashtables();
    int i, n;
    char s[256];
    scanf("%d", &n);
    for(i = 0; i < n; i++)
    {
        gets(s);
        add(dict, s);
    }
    countS(dict);
}
