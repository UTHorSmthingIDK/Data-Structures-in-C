#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct gen_double_linked_list{
    size_t max_size;
    size_t element_size;
    void* data;
    struct gen_double_linked_list* next;
    struct gen_double_linked_list* previous;
} gen_doub_lin_list;

typedef struct head_and_tail {   //this has not been implemented yet
    gen_doub_lin_list* head;
    gen_doub_lin_list* tail;
} head_and_tail;

head_and_tail* create_head_and_tail();

void delete_head(head_and_tail* hat);
void delete_tail(head_and_tail* hat);
void delete_head_tail(head_and_tail* hat);

void link_head(head_and_tail* hat, gen_doub_lin_list* gdll);
void link_tail(head_and_tail* hat, gen_doub_lin_list* gdll);
void link_head_and_tail(head_and_tail* hat, gen_doub_lin_list* gdll1, gen_doub_lin_list* gdll2);


gen_doub_lin_list* create_gen_doub_lin_list(size_t max_size, size_t element_size);
void delete_node_gen_doub_lin_list(gen_doub_lin_list* gdll, size_t pos);

void change_cur_element_gdll(gen_doub_lin_list* gdll, void* element, size_t element_size);
void add_gdll_node(gen_doub_lin_list* gdll1, gen_doub_lin_list* gdll2);
void make_gdll_node_and_add_node(gen_doub_lin_list* gdll);
void make_gdll_node_set_element_add_node(gen_doub_lin_list* gdll, void* element, size_t element_size);

void get_element_gdll(gen_doub_lin_list* gdll, void* element, size_t element_size);
int get_indexof_gdll(head_and_tail* hat, int mode, void* element, size_t element_size);
void get_element_gdll(gen_doub_lin_list* gdll, void* element, size_t element_size);
void get_element_index_gdll(gen_doub_lin_list* gdll, size_t pos, void* element, size_t element_size);
void get_last_element_gdll(gen_doub_lin_list* gdll, void* element, size_t element_size);


int main(void){

    return 0;
}


head_and_tail* create_head_and_tail(){
    head_and_tail* hat = malloc(sizeof(head_and_tail));
    hat->head = malloc(sizeof(gen_doub_lin_list));
    hat->tail = malloc(sizeof(gen_doub_lin_list));
    return;
}

void delete_head(head_and_tail* hat){
    free(hat->head);
    return;
}

void delete_tail(head_and_tail* hat){
    free(hat->tail);
    return;
}

void delete_head_tail(head_and_tail* hat){
    delete_head(hat);
    delete_tail(hat);
    return;
}

void link_head(head_and_tail* hat, gen_doub_lin_list* gdll){
    hat->head = gdll;
    return;
}

void link_tail(head_and_tail* hat, gen_doub_lin_list* gdll){
    hat->tail = gdll;
    return;
}

void link_head_and_tail(head_and_tail* hat, gen_doub_lin_list* gdll1, gen_doub_lin_list* gdll2){
    link_head(hat, gdll1);
    link_tail(hat, gdll2);
    return;
}


gen_doub_lin_list* create_gen_doub_lin_list(size_t max_size, size_t element_size){
    gen_doub_lin_list* gdll = malloc(sizeof(gen_doub_lin_list));
    gdll->max_size = max_size;
    gdll->element_size = element_size;
    gdll->data = malloc(element_size);
    gdll->next = NULL;
    gdll->previous = NULL;
}

void delete_node_gen_doub_lin_list(gen_doub_lin_list* gdll, size_t pos){ // in the works
    int count = 0;
    for (gen_doub_lin_list* gdll1 = gdll; gdll1 != NULL; gdll1 = gdll1->next){
        gen_doub_lin_list* gdll2;
        if (count + 1 == pos){
            gdll2 = gdll1;    // the node before the one to be removed (gll2)
        } else if (count == pos){   // the node we want to remove
            free(gdll->data);
            free(gdll->next);    // <- not sure about this one
            free(gdll);
        } else if (count -1 == pos){
            gdll2->next = gdll1;  // the node after the one removed (we need to make the node before the removed to point (gll2->next) to the one after the removed (gll1) )
            gdll1->previous = gdll2;
        }
    }
    return;
}

void change_cur_element_gdll(gen_doub_lin_list* gdll, void* element, size_t element_size){ //changing the current element of the node
    if (gdll->element_size != element_size){
        printf("Types of [gll->data], [element] are incompatible\n");
        return;
    }
    memcpy((char*)gdll->data, element, element_size);
    return;
}

void add_gdll_node(gen_doub_lin_list* gdll1, gen_doub_lin_list* gdll2){  //adding a node to the list
    gdll1->next = gdll2;
    gdll2->previous = gdll1;
    return;
}

void make_gdll_node_and_add_node(gen_doub_lin_list* gdll){ //create a node, and add it to the list
    gen_doub_lin_list* gdll1 = create_gen_doub_lin_list(gdll->max_size, gdll->element_size);
    gdll->next = gdll1;
    gdll1->previous = gdll;
}

void make_gdll_node_set_element_add_node(gen_doub_lin_list* gdll, void* element, size_t element_size){ //create a node, add an element, and add it to the list
    if (gdll->element_size != element_size){
        printf("Types of [gll->data], [element] are incompatible\n");
        return;
    }
    gen_doub_lin_list* gdll1 = create_gen_doub_lin_list(gdll->max_size, gdll->element_size);
    change_cur_element(gdll1, element, element_size);
    add_node(gdll, gdll1);
    return;
}

int get_indexof_gdll(head_and_tail* hat, int mode, void* element, size_t element_size){
    if (hat->head->element_size != element_size){
        printf("Types of [gll->data], [element] are incompatible\n");
        return -1;
    }
    int count = 0;
    if (!mode){
        for (gen_doub_lin_list* gdll1 = hat->head; gdll1 != NULL; gdll1 = gdll1->next){
            if (!memcmp(gdll1->data, element, element_size)){
                return count;
            }
            count++;
        }
    } else {
        for (gen_doub_lin_list* gdll1 = hat->tail; gdll1 != NULL; gdll1 = gdll1->previous){
            if (!memcmp(gdll1->data, element, element_size)){
                return count;
            }
            count++;
        }
    }
    return -1;
}

void get_element_gdll(gen_doub_lin_list* gdll, void* element, size_t element_size){
    if (gdll->element_size != element_size){
        printf("Types of [gll->data], [element] are incompatible\n");
        return;
    }
    memcpy(element, (char*)gdll->data, element_size);
    return;
}

void get_element_index_gdll(gen_doub_lin_list* gdll, size_t pos, void* element, size_t element_size){
    if (gdll->element_size != element_size){
        printf("Types of [gll->data], [element] are incompatible\n");
        return;
    }
    size_t count = 0;
    for (gen_doub_lin_list* gdll1 = gdll; gdll1 != NULL; gdll1 = gdll1->next){
        if (count == pos){
            memcpy(element, (char*)gdll1->data, element_size);
            return;
        }
        count++;
    }
    printf("element not found\n");
    return;
}

void get_last_element_gdll(gen_doub_lin_list* gdll, void* element, size_t element_size){    //we need to evaluate this one
    if (gdll->element_size != element_size){
        printf("Types of [gll->data], [element] are incompatible\n");
        return;
    }
    gen_doub_lin_list* gdll1 = gdll;
    for (; gdll1->next != NULL; gdll1 = gdll1->next){} //we use the for loop to find NULL. before NULL is our last node, which we use to copy the element (last element)
    memcpy(element, (char*)gdll1->data, element_size);
    return;
}