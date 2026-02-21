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


int main(){

    return 0;
}


gen_queue* create_gen_queue(size_t max_size, size_t element_size){
    gen_queue* gq = malloc(sizeof(gq));
    gq->front = 0;
    gq->rear = 0;
    gq->element_size = element_size;
    gq->gda = malloc(sizeof(gen_dyn_arr));
    gq->gda->element_size = element_size;
    gq->gda->max_size = max_size;
    gq->gda->data = malloc(max_size * element_size);
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
    if (gq->rear + 1 > gq->gda->max_size){
        printf("This action cannot be taken.We have overflow\n");
        return;
    }
    if (gq->front == gq->rear && gq->rear != 0){
        memcpy((char*)gq->gda->data, (char*)gq->gda->data + gq->rear * element_size, element_size); //copying it to the first position
        gq->front = 0;
        gq->rear = 0;
    } else if (gq->front != 0) {
        for (int i = gq->front; i < gq->rear; i++){
            memcpy((char*)gq->gda->data + (i - gq->front) * element_size , (char*)gq->gda->data + i * element_size, element_size);  // a shift towards the start of the queue
        }
        gq->rear = gq->rear - gq->front;
        gq->front = 0;
    }
    memcpy((char*)gq->gda->data + gq->rear * element_size, element, element_size);
    gq->rear++;
}

void Dequeue(gen_queue* gq, void* out, size_t element_size){    // not sure if this is logically accurate with a queue
    if (gq->element_size != element_size){
        printf("Types of [element], [gq->gda->data] are incompatible\n");
        return;
    }
    if (gq->front + 1 > gq->gda->max_size) {
        printf("This action cannot be taken.We have overflow\n");
        return;
    }
    if (gq->front == gq->rear && gq->rear != 0){
        memcpy((char*)gq->gda->data, (char*)gq->gda->data + gq->rear * element_size, element_size); //copying it to the first position
        gq->front = 0;
        gq->rear = 0;
    } else if (gq->front != 0) {
        for (int i = gq->front; i < gq->rear; i++){
            memcpy((char*)gq->gda->data + (i - gq->front) * element_size , (char*)gq->gda->data + i * element_size, element_size);  // a shift towards the start of the queue
        }
        gq->rear = gq->rear - gq->front;
        gq->front = 0;
    }
    memcpy((char*)gq->gda->data + gq->front * element_size, out, element_size);
    gq->front++;
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