#include "Generic_Dynamic_array.h"

/*int main(void){

    gen_dyn_arr* gda = create_gen_dyn_arr(6, 4);

    int b = -4;

    add_element(gda, 0, &b, 4);
    b = -1;
    add_element(gda, 1, &b, 4);
    b = 4;
    add_element(gda, 2, &b, 4);
    b = 3;
    add_element(gda, 3, &b, 4);
    b = 6;
    add_element(gda, 4, &b, 4);
    b = 5;
    add_element(gda, 5, &b, 4);
    
    int a;
    for (int i = 0; i < gda->max_size; i++){
        get_element(gda, &a, i, sizeof(int));
        printf("index : %d, element : %d\n", i, a);
    }

    printf("\n");

    bubble_sort_gen_dyn_arr(gda, 1, cmp_int);   // int mode (in this case 1) changes the sorting method

    for (int i = 0; i < gda->max_size; i++){
        get_element(gda, &a, i, sizeof(int));
        printf("index : %d, element : %d\n", i, a);
    }

    return 0;
}*/


gen_dyn_arr* create_gen_dyn_arr(size_t max_size, size_t element_size){
    gen_dyn_arr* gda = malloc(sizeof(gen_dyn_arr));
    gda->element_size = element_size;
    gda->max_size = max_size;
    gda->data = malloc(gda->max_size);
}

void delete_gen_dyn_arr(gen_dyn_arr* gda){
    free(gda->data);
    free(gda);
}


void add_element(gen_dyn_arr* gda, size_t pos, void* element, size_t element_size){
    if (pos > gda->max_size || pos < 0){
        printf("This action is not posible.(pos is out of bounds)\n");
        return;
    }
    if (gda->element_size != element_size){
        printf("Warning: Type of [da->data] is not compatible with Type of [element]\n");
    }
    memcpy((char*)gda->data + pos * gda->element_size, element, gda->element_size);
}

gen_dyn_arr* remove_element(gen_dyn_arr* gda, size_t pos){
    if (pos < 0 || pos >= gda->max_size){
        printf("This action is not posible.(pos is out of bounds)");
        return NULL;
    }
    gen_dyn_arr* gda1 = create_gen_dyn_arr(gda->max_size - 1, gda->element_size);
    for (size_t i = 0; i < gda->max_size - 1; i++){
        if (i == pos){
            memcpy((char*)gda1->data + i * gda1->element_size, (char*)gda->data + (i + 1) * gda->element_size, gda1->element_size);//add to da1 the next element in the data
        } else {
            memcpy((char*)gda1->data + i * gda1->element_size, (char*)gda->data + i * gda->element_size, gda1->element_size);//copy the element of da into da1
        }
    }
    delete_gen_dyn_arr(gda);
}

void fill_arr(gen_dyn_arr* gda, size_t start, size_t end, void* element, size_t element_size){
    if (start > end || start < 0 || start >= gda->max_size || end < 0 || end >= gda->max_size){
        printf("This action is not posible.(start or end is out of bounds)\n");
    }
    for (size_t i = start; i < end; i++){
        add_element(gda, i, element, element_size);
    }    

}

void get_element(gen_dyn_arr* gda, void* val, size_t pos, size_t element_size){
    if (pos < 0 || pos >= gda->max_size){
        printf("This action is not posible.(trying to access out of bounds)\n");
        return;
    }
    if (gda->element_size != element_size){
        printf("Warning: Type of [da->data] is not compatible with Type of [val]");
    }
    memcpy(val, (char*)gda->data + pos * gda->element_size, element_size);
}

void bubble_sort_gen_dyn_arr(gen_dyn_arr* gda, int mode, int (*cmp)(const void*, const void*)) {  //we pass a function pointer as an argument to the Buble sort
    char* base = (char*)gda->data;
    size_t size = gda->element_size;
    void* tmp = malloc(size);
    for (size_t i = 0; i < gda->max_size - 1; i++) {
        int swapped = 0;
        for (size_t j = 0; j < gda->max_size - i - 1; j++) {
            void* a = base + j * size;
            void* b = base + (j + 1) * size;
            if (!mode){ //auxousa 
                if (cmp(b, a) > 0) {    //we use the pointer to the function
                    memcpy(tmp, a, size);
                    memcpy(a, b, size);
                    memcpy(b, tmp, size);
                    swapped = 1;
                }
            } else {    //fthinousa
                if (cmp(a, b) > 0) {    //we use the pointer to the function
                    memcpy(tmp, a, size);
                    memcpy(a, b, size);
                    memcpy(b, tmp, size);
                    swapped = 1;
                }
            }
        }
        if (!swapped) break;
    }
    free(tmp);
}

int cmp_int(const void* a, const void* b){
    int x = *(const int*)a;
    int y = *(const int*)b;
    return x - y;
}

int cmp_float(const void* a, const void* b){
    float x = *(const float*)a;
    float y = *(const float*)b;
    return x - y;
}


size_t linear_search_gen_dyn_arr(gen_dyn_arr* gda, void* element, size_t element_size){
    if (element_size != gda->element_size){
        printf("Types of [element] and [gda->data] are incompatible\n");
        return -1;
    }
    for(size_t i = 0; i < gda->max_size; i++){
        if (!memcmp(element, (char*)gda->data + i * gda->element_size, element_size)){
            return i;
        }
    }
    return -1;
}

size_t binary_search_gen_dyn_arr(gen_dyn_arr* gda, void* element, size_t element_size){
    if (element_size != gda->element_size){
        printf("Types of [element] and [gda->data] are incompatible\n");
        return -1;
    }
    size_t bot = 0;
    size_t top = gda->max_size;
    size_t mid = (top - bot)/2;
    int flag, flag1;
    while((flag = memcmp(element, (char*)gda->data + mid * gda->element_size, element_size)) && (flag1 = top > bot)){
        if (flag < 0){  //element < gda->data
            top = mid - 1;
            mid = (top + bot)/2;
        } else {    //element > gda->data
            bot = mid + 1;
            mid = (top + bot)/2;
        }
    }
    if (!flag1){
        return mid;
    }
    return -1;
}