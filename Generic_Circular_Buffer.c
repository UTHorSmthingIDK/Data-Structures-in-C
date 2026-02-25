#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Generic_Circular_Buffer{
    size_t max_size;
    size_t element_size;
    size_t front;
    size_t rear;
    void* data;
} gen_cir_buf;

gen_cir_buf* create_gen_cir_buf(size_t max_size, size_t element_size);
void delete_gen_cir_buf(gen_cir_buf* gcb);

void Enqueue(gen_cir_buf* gcb, void* element, size_t element_size);
int Dequeue(gen_cir_buf* gcb, void* out, size_t element_size);
//void fill_queue(gen_queue* gq, size_t end, void* element, size_t element_size);

int isEmpty(gen_cir_buf* gcb);
int isFull(gen_cir_buf* gcb);
//size_t get_size(gen_queue* gq);

////int search(gen_queue* gq, void* element, size_t element_size);

void get_peek(gen_cir_buf* gcb, void* out, size_t element_size);


int main(void){
    gen_cir_buf* gcb = create_gen_cir_buf(10, sizeof(int));

    int val = 256;
    printf("%d, %d\n", gcb->rear, gcb->front);
    printf("\n\n");
    for (int i = 0; i < gcb->max_size; i++){
        Enqueue(gcb, &i, sizeof(i));
        printf("%d, %d\n", gcb->rear, gcb->front);
    }
    printf("\n\n");
    printf("%d, %d\n", gcb->rear, gcb->front);


    Enqueue(gcb, &val, sizeof(val));
    printf("%d, %d\n", gcb->rear, gcb->front);


    delete_gen_cir_buf(gcb);
    return 0;
}


gen_cir_buf* create_gen_cir_buf(size_t max_size, size_t element_size){
    gen_cir_buf* gcb = malloc(sizeof(gen_cir_buf));
    gcb->max_size = max_size;
    gcb->element_size = element_size;
    gcb->data = malloc(element_size * max_size);
    gcb->front = 0;
    gcb->rear = 0;
    return gcb;
}

void delete_gen_cir_buf(gen_cir_buf* gcb){
    free(gcb->data);
    free(gcb);
    return;
}

void Enqueue(gen_cir_buf* gcb, void* element, size_t element_size){
    if (gcb->element_size != element_size){
        printf("Types of [gcb->data], [element] are incpompatible\n");
        return;
    }
    memcpy((char*)gcb->data + gcb->rear * element_size, element, element_size);
    if (isFull(gcb)){
        printf("Queue is full\n");
        gcb->rear = (gcb->rear + 1) % gcb->max_size;
        gcb->front = (gcb->front + 1) % gcb->max_size;
        return;
    }
    gcb->rear = (gcb->rear + 1) % gcb->max_size;
    return;
}

int Dequeue(gen_cir_buf* gcb, void* out, size_t element_size){
    if (gcb->element_size != element_size){
        printf("Types of [gcb->data], [out] are incpompatible\n");
        return -1;
    }
    if (isEmpty(gcb)){
        printf("The buffer was empty\n");
        return 0;
    }
    memcpy(out, (char*)gcb->data + gcb->front * element_size, element_size);
    gcb->front = (gcb->front + 1) % gcb->max_size;
    return 1;
}

int isEmpty(gen_cir_buf* gcb){
    return gcb->front == gcb->rear;
}

int isFull(gen_cir_buf* gcb){
    return ((gcb->rear + 1) % gcb->max_size) == gcb->front;
}

void get_peek(gen_cir_buf* gcb, void* out, size_t element_size){
    if (gcb->element_size != element_size){
        printf("Types of [gcb->data], [out] are incpompatible\n");
        return;
    }
    if (isEmpty(gcb)){
        printf("The buffer is empty. Cannot get peek\n");
        return;
    }
    memcpy(out, (char*)gcb->data + gcb->front * element_size, element_size);
    return;
}