#include "ds_common.h"
#include <string.h>
#include <stdlib.h>
int int_cmp(const void* a, const void* b){
    int va = *(const int*)a;
    int vb = *(const int*)b;
    return (va > vb) - (va < vb);
}

int str_cmp(const void* a, const void* b){
    return strcmp((const char*)a, (const char*)b);
}

void node_free(void* node){
    free(node);
    return;
}