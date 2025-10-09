#include "ds_common.h"
#include "list.h"
#include <stdio.h>
int main(void){


List* l = list_create();
int a = 10, b = 20, c = 30;
flist_insert(l, &a);
flist_insert(l, &b);
flist_insert(l, &c);

int target = 20;
Node* found = list_find(l, &target, int_cmp);
printf("Found: %d\n", *(int*)found->data);

list_remove(l, &b, int_cmp,node_free);
list_destroy(l,node_free);
return 0;

}