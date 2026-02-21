#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*typedef struct root{
    void* data;
    int data_size;
    struct gen_bin_tree* right;
    struct gen_bin_tree* left;
} root;*/

typedef struct gen_bin_tree
{
    void *cur_node;             // current node
    int node_size;              // the size of data
    struct gen_bin_tree *right; // right node
    struct gen_bin_tree *left;  // left node
} gen_bin_tree;                 // this tree can be used as a simple binary treee or a binary seacrh tree (that depends on the user and what functions he uses)



gen_bin_tree *create_root(int node_size);
void change_element_of_cur_node(gen_bin_tree *gbt, void *element, int element_size);

gen_bin_tree *create_node(void *node_data, int node_size);
void add_node(gen_bin_tree *gbt, void *element, int element_size, int rl_mode);
void fill_branch(gen_bin_tree* gbt, void* element, int element_size, int** rl_mode, int rl_mode_len);

int get_cur_node_element(gen_bin_tree *gbt, void *element, int element_size);

gen_bin_tree *search(gen_bin_tree *root, void *element, int element_size, int (*cmp)(const void *, const void *));
int cmp_int(const void *a, const void *b);



int main()
{
    gen_bin_tree *gbt = create_root(sizeof(int));
    int a = 3;
    int b = 0;
    int flag = get_cur_node_element(gbt, &b, sizeof(int));
    printf("Flag : %d Root Element: %d\n", flag, b);
    b = 1;
    change_element_of_cur_node(gbt, &b, sizeof(int));
    flag = get_cur_node_element(gbt, &b, sizeof(int));
    printf("Flag : %d Root Element: %d\n", flag, b);
    add_node(gbt, &a, sizeof(int), 0);
    a = -2;
    add_node(gbt->right, &a, sizeof(int), 0);
    printf("\n");
    for (gen_bin_tree *gbt1 = gbt; gbt1 != NULL; gbt1 = gbt1->right)
    {
        flag = get_cur_node_element(gbt1, &b, sizeof(int));
        printf("Flag : %d Root Element: %d\n", flag, b);
        b = -1;
    }
    return 0;
}


void delete_binary_tree(){

}


gen_bin_tree *create_root(int node_size)
{
    gen_bin_tree *gbt = malloc(sizeof(gen_bin_tree));
    gbt->node_size = node_size;
    gbt->cur_node = calloc(1, node_size);
    gbt->left = NULL;
    gbt->right = NULL;
    return gbt;
}

void change_element_of_cur_node(gen_bin_tree *gbt, void *element, int element_size)
{
    if (element_size != gbt->node_size)
    {
        printf("Types of [element] and [gbt->cur_node] are incompatible\n");
        return;
    }
    memcpy(gbt->cur_node, element, element_size);
}

// void delete_tree(gen_bin_tree* gbt){

//}

gen_bin_tree *create_node(void *node_data, int node_size)
{
    gen_bin_tree *gbt = malloc(sizeof(gen_bin_tree));
    gbt->node_size = node_size;
    gbt->cur_node = malloc(node_size);
    memcpy(gbt->cur_node, node_data, node_size);
    gbt->left = NULL;
    gbt->right = NULL;
    return gbt;
}

void add_node(gen_bin_tree *gbt, void *element, int element_size, int rl_mode)
{
    if (!rl_mode)
    { // right_left_mode
        gbt->right = create_node(element, element_size);
    }
    else
    {
        gbt->left = create_node(element, element_size);
    }
}

void fill_branch(gen_bin_tree* gbt, void* element, int element_size, int** rl_mode, int rl_mode_len){   //filling a branch of a specific pattern made by array rl_mode
    for (int i = 0; i < rl_mode_len; i++){
        add_node(gbt, element, element_size, rl_mode[i]);
    }
}

void add_node_in_order(gen_bin_tree *gbt, void *element, int element_size)
{
    if (element_size != gbt->node_size)
    {
        printf("Types of [element] and [gbt->cur_node] are incompatible\n");
        return;
    }
    if (memcmp(gbt->cur_node, element, element_size) > 0)
    {
        add_node(gbt, element, element_size, 1);
    }
    else
    {
        add_node(gbt, element, element_size, 0);
    }
    return;
}

int get_cur_node_element(gen_bin_tree *gbt, void *element, int element_size)
{
    if (element_size != gbt->node_size)
    {
        printf("Types of [element] and [gbt->cur_node] are incompatible\n");
        return 0;
    }
    memcpy(element, gbt->cur_node, gbt->node_size);
    return 1;
}

gen_bin_tree *search(gen_bin_tree *root, void *element, int element_size, int (*cmp)(const void *, const void *))
{
    while (root != NULL)
    {
        int result = cmp(element, root->cur_node);
        if (result < 0)
        {
            if (root->left != NULL && memcmp(root->cur_node, root->left->cur_node, root->node_size) > 0)
            {
                printf("The binary tree is not a binary seacrh tree\n");
                return NULL;
            }
            root = root->left;
        }
        else if (result > 0)
        {
            if (root->right != NULL && memcmp(root->cur_node, root->right->cur_node, root->node_size) < 0)
            {
                printf("The binary tree is not a binary seacrh tree\n");
                return NULL;
            }
            root = root->right;
        }
        else
            return root;
    }
    return NULL;
}

int cmp_int(const void *a, const void *b)
{
    int x = *(int *)a;
    int y = *(int *)b;

    if (x < y)
        return -1;
    if (x > y)
        return 1;
    return 0;
}

/*
we will make both a simple binary tree and
a simple binary seacrh tree
*/