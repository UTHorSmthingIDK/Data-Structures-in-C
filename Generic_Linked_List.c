#include "Generic_Linked_List.h"
#include "mallocW.h"


int main(void){
    gen_lin_list* gll = create_gen_lin_list(5, sizeof(int));
    head* h = create_head(gll);
    int a = -1;
    change_cur_element(gll, &a, sizeof(a));
    a = -4;
    make_node_set_element_add_node(gll, h, &a, sizeof(a));
    a = 8;
    make_node_set_element_add_node(gll->next, h, &a, sizeof(a));
    a = 5;
    make_node_set_element_add_node(gll->next->next, h, &a, sizeof(a));
    a = 3;
    make_node_set_element_add_node(gll->next->next->next, h, &a, sizeof(a));
    int count = 0;
    for (gen_lin_list* gll1 = h->first; gll1 != NULL; gll1 = gll1->next){
        int data;
        get_element(gll1, &data, sizeof(data));
        printf("element %d: %d\n", count++, data);
    }

    delete_List(h);

    return 0;
}


gen_lin_list* create_gen_lin_list(size_t max_size, size_t element_size){
    gen_lin_list* gll = mallocWrap(sizeof(gen_lin_list));
    if (!gll) return NULL;
    gll->max_size = max_size;
    gll->element_size = element_size;
    gll->data = mallocWrap(element_size);
    if (!gll) return NULL;
    gll->next = NULL;
    return gll;
}

head* create_head(gen_lin_list* gll){
    head* h = mallocWrap(sizeof(head));
    if (!h) return NULL;
    h->first = gll;
    h->count = (gll != NULL)? 1 : 0;
    return h;
}

void delete_List(head* h){
    gen_lin_list* gll = h->first;
    while(gll != NULL){
        free(gll->data);    //we first free the data section
        gen_lin_list* gll1 = gll;   //used as a temporary and then deleted
        gll = gll->next;    //the reason we used a temporary was because we wanted to go to the next node.
        free(gll1);
    }
    h->count = 0;
    free(h);
}

void delete_node_gen_lin_list(head* h, size_t pos) {
    if (h == NULL || h->first == NULL) return;
    gen_lin_list* temp = h->first;
    if (pos == 0) { // Special case: Deleting the head (position 0)
        h->first = temp->next;  // Move head to the second node
        free(temp->data);   // Free the generic data
        free(temp); // Free the node
        h->count--;
        return;
    }
    for (int i = 0; temp != NULL && i < pos - 1; i++) { // Traverse to find the node BEFORE the one we want to delete
        temp = temp->next;
    }
    if (temp == NULL || temp->next == NULL) return; // If position is out of bounds
    gen_lin_list* next_node = temp->next->next; // temp->next is the node to be deleted
    free(temp->next->data); // Free data of target node
    free(temp->next);   // Free target node
    temp->next = next_node; // Bridge the gap
    h->count--;
}

void change_cur_element(gen_lin_list* gll, void* element, size_t element_size){ //changing the current element of the node
    if (gll->element_size != element_size){
        printf("Types of [gll->data], [element] are incompatible\n");
        return;
    }
    memcpy((char*)gll->data, element, element_size);
    return;
}

void add_node(gen_lin_list* gll1, gen_lin_list* gll2, head* h) { //adding a new node to the list
    if (gll1 == NULL || gll2 == NULL) return;
    gll2->next = gll1->next;    // Point the new node to whatever was after gll1
    gll1->next = gll2;  // Point gll1 to the new node
    h->count++;
}

void make_node_and_add_node(gen_lin_list* gll, head* h){ //create a node, and add it to the list
    gen_lin_list* gll1 = create_gen_lin_list(gll->max_size, gll->element_size);
    add_node(gll, gll1, h);
}

void make_node_set_element_add_node(gen_lin_list* gll, head* h, void* element, size_t element_size){ //create a node, add an element, and add it to the list
    if (gll->element_size != element_size){
        printf("Types of [gll->data], [element] are incompatible\n");
        return;
    }
    gen_lin_list* gll1 = create_gen_lin_list(gll->max_size, gll->element_size);
    change_cur_element(gll1, element, element_size);
    add_node(gll, gll1, h);
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
            return count + 1;
        }
        count++;
    }
    return -1;
}

void get_peek(head* h, void* element, size_t element_size){
    if (h->first->element_size != element_size){
        printf("Types of [h->first->data], [element] are incompatible\n");
        return;
    }
    memcpy(element, (char*)h->first->data, element_size);
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

size_t get_size(head* h){
    return h->count;
}