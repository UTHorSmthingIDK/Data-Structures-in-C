#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct gen_linked_list{
    size_t max_size;
    size_t element_size;
    void* data;
    struct gen_linked_list* next;
} gen_lin_list;

gen_lin_list* create_gen_lin_list(size_t max_size, size_t element_size);
void delete_node_gen_lin_list(gen_lin_list* gll, size_t pos);

void change_cur_element(gen_lin_list* gll, void* element, size_t element_size);

void add_node(gen_lin_list* gll1, gen_lin_list* gll2);
void make_node_and_add_node(gen_lin_list* gll);
void make_node_set_element_add_node(gen_lin_list* gll, void* element, size_t element_size);

int get_indexof(gen_lin_list* gll, void* element, size_t element_size);
void get_element(gen_lin_list* gll, void* element, size_t element_size);
void get_element_index(gen_lin_list* gll, size_t pos, void* element, size_t element_size);
void get_last_element(gen_lin_list* gll, void* element, size_t element_size);


int main(void){

    return 0;
}


gen_lin_list* create_gen_lin_list(size_t max_size, size_t element_size){
    gen_lin_list* gll = malloc(sizeof(gen_lin_list));
    gll->max_size = max_size;
    gll->element_size = element_size;
    gll->data = malloc(element_size);
    gll->next = NULL;
}

void delete_node_gen_lin_list(gen_lin_list* gll, size_t pos){ // in the works
    int count = 0;
    for (gen_lin_list* gll1 = gll; gll1 != NULL; gll1 = gll1->next){
        gen_lin_list* gll2;
        if (count + 1 == pos){
            gll2 = gll1;    // the node before the one to be removed (gll2)
        } else if (count == pos){   // the node we want to remove
            free(gll->data);
            free(gll->next);    // <- not sure about this one in case it is NULL
            free(gll);
        } else if (count -1 == pos){
            gll2->next = gll1;  // the node after the one removed (we need to make the node before the removed to point (gll2->next) to the one after the removed (gll1) )
        }
    }
    return;
}

void change_cur_element(gen_lin_list* gll, void* element, size_t element_size){ //changing the current element of the node
    if (gll->element_size != element_size){
        printf("Types of [gll->data], [element] are incompatible\n");
        return;
    }
    memcpy((char*)gll->data, element, element_size);
    return;
}

void add_node(gen_lin_list* gll1, gen_lin_list* gll2){  //adding a node to the list
    gll1->next = gll2;
    return;
}

void make_node_and_add_node(gen_lin_list* gll){ //create a node, and add it to the list
    gen_lin_list* gll1 = create_gen_lin_list(gll->max_size, gll->element_size);
    gll->next = gll1;
}

void make_node_set_element_add_node(gen_lin_list* gll, void* element, size_t element_size){ //create a node, add an element, and add it to the list
    if (gll->element_size != element_size){
        printf("Types of [gll->data], [element] are incompatible\n");
        return;
    }
    gen_lin_list* gll1 = create_gen_lin_list(gll->max_size, gll->element_size);
    change_cur_element(gll1, element, element_size);
    add_node(gll, gll1);
    return;
}

int get_indexof(gen_lin_list* gll, void* element, size_t element_size){
    if (gll->element_size != element_size){
        printf("Types of [gll->data], [element] are incompatible\n");
        return -1;
    }
    int count = 0;
    for (gen_lin_list* gll1 = gll; gll1 != NULL; gll1 = gll1->next){
        if (!memcmp(gll1->data, element, element_size)){
            return count;
        }
        count++;
    }
    return -1;
}

void get_element(gen_lin_list* gll, void* element, size_t element_size){
    if (gll->element_size != element_size){
        printf("Types of [gll->data], [element] are incompatible\n");
        return;
    }
    memcpy(element, (char*)gll->data, element_size);
    return;
}

void get_element_index(gen_lin_list* gll, size_t pos, void* element, size_t element_size){
    if (gll->element_size != element_size){
        printf("Types of [gll->data], [element] are incompatible\n");
        return;
    }
    size_t count = 0;
    for (gen_lin_list* gll1 = gll; gll1 != NULL; gll1 = gll1->next){
        if (count == pos){
            memcpy(element, (char*)gll1->data, element_size);
            return;
        }
        count++;
    }
    printf("element not found\n");
    return;
}

void get_last_element(gen_lin_list* gll, void* element, size_t element_size){
    if (gll->element_size != element_size){
        printf("Types of [gll->data], [element] are incompatible\n");
        return;
    }
    gen_lin_list* gll1 = gll;
    for (; gll1->next != NULL; gll1 = gll1->next){} //we use the for loop to find NULL. before NULL is our last node, which we use to copy the element (last element)
    memcpy(element, (char*)gll1->data, element_size);
    return;
}