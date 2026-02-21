#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct gen_dyn_arr{
    size_t max_size;
    size_t element_size;
    void* data;
} gen_dyn_arr;

gen_dyn_arr* create_gen_dyn_arr(size_t max_size, size_t element_size);
void delete_gen_dyn_arr(gen_dyn_arr* gda);

void add_element(gen_dyn_arr* gda, size_t pos, void* element, size_t element_size);
gen_dyn_arr* remove_element(gen_dyn_arr* gda, size_t pos);

void fill_arr(gen_dyn_arr* gda, size_t start, size_t end, void* element, size_t element_size);

void get_element(gen_dyn_arr* gda, void* val, size_t pos, size_t element_size);

void bubble_sort_gen_dyn_arr(gen_dyn_arr* gda, int mode, int (*cmp)(const void*, const void*));
int cmp_int(const void* a, const void* b);
int cmp_float(const void* a, const void* b);

size_t linear_search_gen_dyn_arr(gen_dyn_arr* gda, void* element, size_t element_size);
size_t binary_search_gen_dyn_arr(gen_dyn_arr* gda, void* element, size_t element_size);