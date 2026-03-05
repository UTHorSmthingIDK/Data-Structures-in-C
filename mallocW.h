#include <stdlib.h>

void* mallocWrap(size_t size){
    void* data = malloc(size);
    if (!data){
        return NULL;
    }
    return data;
}