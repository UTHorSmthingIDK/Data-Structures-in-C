#include "Generic_Dynamic_array.h"

typedef struct gen_queue{
    gen_dyn_arr* gda;
    size_t front;
    size_t rear;
    size_t element_size;    // <- we may have to remove this one
} gen_queue;

gen_queue* create_gen_queue(size_t max_size, size_t element_size);
void delete_gen_queue(gen_queue* gq);

void Enqueue(gen_queue* gq, void* element, size_t element_size);
void Dequeue(gen_queue* gq, void* out, size_t element_size);
void fill_queue(gen_queue* gq, size_t end, void* element, size_t element_size);

int is_empty(gen_queue* gq);
size_t get_size(gen_queue* gq);

int search(gen_queue* gq, void* element, size_t element_size);

void get_peek(gen_queue* gq, void* out, size_t element_size);


int main(){
    gen_queue* gq = create_gen_queue(5, sizeof(int));
    int a = 3;
    Enqueue(gq, &a, sizeof(a));
    a = 2;
    Enqueue(gq, &a, sizeof(a));
    a = -1;
    Enqueue(gq, &a, sizeof(a));
    a = 5;
    printf("rear : %d\n", gq->rear);
    printf("size : %d\n\n", get_size(gq));

    Enqueue(gq, &a, sizeof(a));
    printf("rear : %d\n", gq->rear);
    printf("size : %d\n\n", get_size(gq));

    a = -3;

    Enqueue(gq, &a, sizeof(a));
    printf("rear : %d\n", gq->rear);
    printf("size : %d\n\n", get_size(gq));

    Enqueue(gq, &a, sizeof(a));
    printf("rear : %d\n", gq->rear);
    printf("size : %d\n\n", get_size(gq));

    int data = -3;
    printf("Size of queue : %d\n", get_size(gq));
    int flag = search(gq, &data, sizeof(int));
    printf("The element is in position %d\n", flag);
    printf("Size of queue : %d\n", get_size(gq));
    get_peek(gq, &flag, sizeof(int));
    printf("peek is : %d\n", flag);
    flag = search(gq, &data, sizeof(int));
    printf("The element is in position %d\n\n", flag);
    printf("front : %d, rear : %d\n", gq->front, gq->rear);
    delete_gen_queue(gq);
    return 0;
}


gen_queue* create_gen_queue(size_t max_size, size_t element_size){
    gen_queue* gq = malloc(sizeof(gen_queue));
    gq->front = 0;
    gq->rear = 0;
    gq->element_size = element_size;
    gq->gda = malloc(sizeof(gen_dyn_arr));
    gq->gda->element_size = element_size;
    gq->gda->max_size = max_size;
    gq->gda->data = malloc(max_size * element_size);
    return gq;
}

void delete_gen_queue(gen_queue* gq){
    free(gq->gda->data);
    free(gq->gda);
    free(gq);
}

void Enqueue(gen_queue* gq, void* element, size_t element_size){    // not sure if this is logically accurate with a queue
    if (gq->element_size != element_size){
        printf("Types of [element], [gq->gda->data] are incompatible\n");
        return;
    }
    if (gq->rear >= gq->gda->max_size){
        printf("This action cannot be taken.We have overflow\n");
        return;
    } else if (gq->rear + 1 > gq->gda->max_size){
        memcpy((char*)gq->gda->data + gq->rear * element_size, element, element_size);
        gq->rear++;
        return;
    }
    memcpy((char*)gq->gda->data + gq->rear * element_size, element, element_size);
    gq->rear++;
    return;
}

void Dequeue(gen_queue* gq, void* out, size_t element_size){
    if (gq->element_size != element_size){
        printf("Types of [element], [gq->gda->data] are incompatible\n");
        return;
    }
    gq->front++;
    if (gq->front == gq->rear) {
        memcpy(out, (char*)gq->gda->data + (gq->front - 1) * element_size, element_size);
        gq->front = 0;
        gq->rear = 0;
        return;
    }
    memcpy(out, (char*)gq->gda->data + (gq->front - 1) * element_size, element_size);

}

void fill_queue(gen_queue* gq, size_t end, void* element, size_t element_size){
    if (gq->rear + end > gq->gda->max_size){
        printf("This action cannot be done. Overflow");
        return;
    }
    for (int i = 0; i < end; i++){
        Enqueue(gq, element, element_size);
    }
    return;
}

int is_empty(gen_queue* gq){
    return gq->front == gq->rear;
}

size_t get_size(gen_queue* gq){
    return gq->rear - gq->front;
}

int search(gen_queue* gq, void* element, size_t element_size){
    if (gq->element_size != element_size){
        printf("Types of [gq->gda->data], [element] are incompatible\n");
        return -1;
    }
    int pos = -1;
    int size = get_size(gq);
    void* data = malloc(element_size);
    gen_dyn_arr* gda = create_gen_dyn_arr(gq->gda->max_size, element_size);
    for (int i = 0; i < size; i++){
        Dequeue(gq, data, element_size);
        if (!memcmp(data, element, element_size)){
            pos = i + 1;
        }
        add_element(gda, i, data, element_size);
    }
    for (int i = 0; i < size; i++){
        get_element(gda, data, i, element_size);    //getting the elements back from gda
        Enqueue(gq, data, element_size);    //placing the elements back in the queue
    }
    free(data);
    delete_gen_dyn_arr(gda);
    return pos;
}

void get_peek(gen_queue* gq, void* out, size_t element_size){ //get the element that front points to
    if (gq->element_size != element_size){
        printf("Types of [gq->gda->data], [out] are incompatible\n");
        return;
    }
    memcpy(out, (char*)gq->gda->data + gq->front * element_size, element_size);
    return;
}