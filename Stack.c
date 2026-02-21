#include "Generic_Dynamic_array.h"


typedef struct stack{
    size_t max_size;
    size_t element_size;
    int top;
    void* data;
} Stack;

Stack* create_stack(size_t max_size, size_t element_size);
void delete_stack(Stack* s);

void push(Stack* s,void* data);
void pop(Stack* s, void* discarded_data);

int get_top(Stack* s, void* out);

void bubble_sort_stack(Stack* s, int mode, int (*cmp)(const void*, const void*));
size_t linear_search_stack(Stack* s, void* element, size_t element_size);


int main(void){
    Stack* s = create_stack(5, 4); // stack of integers, with 5 integers

    //void* p = malloc(4);
    //pop(s, p);  //underflow
    //free(p);

    int i = 5, b = 3, c = 4, a = 8;

    push(s, &i);
    push(s, &b);
    push(s, &c);
    c = -3;
    push(s, &c);
    push(s, &a);

    int val;
    if (get_top(s, &val)){
        printf("top index is %d and contains %d\n", s->top, val);
    }
    bubble_sort_stack(s, 0, cmp_int);

    if (get_top(s, &val)){
        printf("top index is %d and contains %d\n", s->top, val);
    }

    return 0;
}

Stack* create_stack(size_t max_size, size_t element_size){
    Stack* s = malloc(sizeof(Stack));
    s->data = malloc(max_size * element_size);
    s->top = -1;
    s->max_size = max_size;
    s->element_size = element_size;
    return s;
}

void delete_stack(Stack* s){    //not sure about this one
    free(s->data);
    free(s);
}

void push(Stack* s,void* data){
    if (s->top > (int)s->max_size -1){
        printf("This action cannot be performed, otherwise it is a stack overflow\n");
        return;
    }
    s->top++;
    memcpy((char*)s->data + s->top * s->element_size, data, s->element_size);
    /*
    * the casting [(char*)s->data] is done to notify the compiler that the pointer points to one sized bytes.
    * In the address of s_data, go to (s->top * s->element_size) and insert the data in that position.
    * Specifically the data that is inserted will be saved in (s->element_size) bytes
    */
}

void pop(Stack* s, void* discarded_data){
    if (s->top < 0){
        printf("This action cannot be performed, otherwise it is a stack underflow\n");
        return;
    }
    memcpy(discarded_data, (char*)s->data + s->top * s->element_size, s->element_size);
    s->top--;
    /*
    * the casting [(char*)s->data] is done to notify the compiler that the pointer points to one sized bytes.
    * To the address of discarded_data, you will save specifically (s->element_size) bytes and you will take those bytes
    * from  [(char*)s->data + s->top * s->element_size].
    */
}

int get_top(Stack* s, void* out){
    if (s->top < 0){
        printf("The stack is empty\n");
        return 0;
    }
    memcpy(out, (char*)s->data + s->top * s->element_size, s->element_size);
    return 1;
}

void bubble_sort_stack(Stack* s, int mode, int (*cmp)(const void*, const void*)){  //generic dynamic array needed
    gen_dyn_arr* gda = create_gen_dyn_arr(s->max_size, s->element_size);    //making a Generic Dynamic Array with the same size of stack and element_size
    for (size_t i = 0; i < s->max_size; i++){   //placing the stack elements is the Array
        void* out = malloc(s->element_size);
        pop(s, out);
        add_element(gda, i, out, s->element_size);
        free(out);
    }

    bubble_sort_gen_dyn_arr(gda, mode, cmp);    //sorting the array

    for (size_t i = 0; i < s->max_size; i++){   //sending the elements back to the stack
        void* out = malloc(gda->element_size);
        get_element(gda, out, i, s->element_size);
        push(s, out);
        free(out);
    }
    delete_gen_dyn_arr(gda);
}

size_t linear_search_stack(Stack* s, void* element, size_t element_size){   // ******* not sure if it is completely correct *******
    if (s->element_size != element_size){
        printf("Types of [element] and [s->data] are incompatible\n");
        return -1;
    }
    size_t original_pos = s->top;
    size_t pos = -1;
    gen_dyn_arr* gda = create_gen_dyn_arr(s->max_size, s->element_size);    //making a Generic Dynamic Array with the same size of stack and element_size
    for (size_t i = 0; i < s->max_size; i++){   //placing the stack elements is the Array
        void* out = malloc(s->element_size);
        pop(s, out);
        if (!memcmp(out, (char*)s->data + s->top * s->element_size, element_size)){
            pos = s->top;
            free(out);
            break;
        }
        add_element(gda, i, out, s->element_size);
        free(out);
    }
    size_t j = 0;
    for(size_t i = original_pos; i > pos; i--){ // If we want the elements of our stack to return we need to return them in opposite order to be correct
        void* out1 = malloc(s->element_size);
        get_element(gda, out1, j, element_size);
        j++;
        push(s,out1);
        free(out1);
    }
    if (pos == -1){
        printf("The element was not found\n");
        return pos;
    }
    delete_gen_dyn_arr(gda);
    return pos;
}

size_t binary_seacrh_stack(){   //in the works

}