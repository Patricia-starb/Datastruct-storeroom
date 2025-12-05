#ifndef DS_COMMON_H

#define DS_COMMON_H

typedef int(*cmp_func)(const void*, const void*);
typedef void(*free_func)(void*);

int int_cmp(const void* a, const void* b);
int str_cmp(const void* a, const void* b);
void node_free(void* node);


#endif