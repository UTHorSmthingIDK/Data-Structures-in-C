#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct gen_linked_list{
    size_t max_size;
    size_t element_size;
    void* data;
    struct gen_linked_list* next;
} gen_lin_list;

typedef struct head{
    gen_lin_list* first;
    size_t count;
} head;

gen_lin_list* create_gen_lin_list(size_t max_size, size_t element_size);
void delete_node_gen_lin_list(head* h, size_t pos);

head* create_head(gen_lin_list* gll);
void delete_List(head* h);

void change_cur_element(gen_lin_list* gll, void* element, size_t element_size);

void add_node(gen_lin_list* gll1, gen_lin_list* gll2, head* h);
void make_node_and_add_node(gen_lin_list* gll, head* h);
void make_node_set_element_add_node(gen_lin_list* gll, head* h, void* element, size_t element_size);

int get_indexof(gen_lin_list* gll, void* element, size_t element_size);
void get_element(gen_lin_list* gll, void* element, size_t element_size);
void get_peek(head* h, void* element, size_t element_size);
void get_element_index(gen_lin_list* gll, size_t pos, void* element, size_t element_size);
void get_last_element(gen_lin_list* gll, void* element, size_t element_size);

size_t get_size(head* h);