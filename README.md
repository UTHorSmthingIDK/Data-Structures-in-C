# Data Structures in C

This project contains implementations of basic data structures in C.
It is currently a work in progress.


## Progress

I have worked on linked lists, doubly linked lists and a litle bit on the queue 

## Implemented Structures

- **Linked List** (in progress)
- **Doubly Linked List** (in progress)
- **Stack**
- **Queue** (in progress)
- **Generic Circular Buffer**
- **Generic Dynamic Array**
- **Binary Tree**

## General Project Structure

The project is not fully structured yet.

Compilation depends on what you want to test.  
Currently, each data structure has its own `main()` function for testing purposes.  

for example:
- **Stack** uses the Generic Dynamic Array, so both files must be compiled together.  
- **Queue** will eventually have a version using a list, but currently may also depend on the Generic Dynamic Array.  
- For the **Generic Dynamic Array**, remove the commented-out `main()` function if you want to compile it separately. This avoids conflicts when compiling structures like Stack that also include it.

## Specifics about each Data Structure

The **Generic_Dynamic_array** has functions:

- create_gen_dyn_arr -> allocates memory for the generic dynamic array and returns a pointer to it
- delete_gen_dyn_arr -> frees the memory allocated for the generic dynamic array
- add_element -> adds an element to the array in a certain position specified in the arguments
- resize -> creates a new array with a different max size and sends all the data of the old array to it (there is probably a more optimized way of doing this)
- remove_element_in_place -> finds the element of a certain position you want to remove and removes it, it also shifts the array depending on what you remove
- fill_arr -> fills the array with a certain element from the position of 'start' to the position of 'end'
- get_element -> returns an element through the argument list by void* pointer of a specific position specified in the arguments
- bubble_sort_gen_dyn_arr -> does bubble sort for the generic elements using a pointer to a function called cmp -> 'compare' -> (cmp_int for integers)
- cmp_int -> compares integer numbers
- cmp_float -> compares floating point numbers
- linear_search_gen_dyn_arr -> does a linear search using again a pointer to a function called cmp (for example cmp_int) and returns the position of the element we want
- binary_search_gen_dyn_arr -> does a binary search using again a pointer to a function called cmp (for example cmp_int) and returns the position of the element we want

how to build:

make sure to remove the comments on the main function (if they are there)

```bash
gcc Generic_Dynamic_array.c -o Generic_Dynamic_Array
```

how to run:

```bash
./Generic_Dynamic_Array
```

The **Stack** has functions:

this stack is implemented using generic dynamic arrays

- create_stack -> makes the Stack and returns a pointer to it 
- delete_stack -> frees the allocated memory for the stack
- push -> pushes elements to the top of the Stack
- pop -> pops elements from the top of the Stack
- bubble_sort_stack -> uses generic Dynamic array to perform the bubblesort (very expensive in memory and time)
- linear_search_stack -> does linear seacrh by poping elements, checking them, adding them to a generic dynamic array
and once the element is found or when the stack is empty places back to the stack the elements from the array in order (veryexpensive in memory and time)

how to build:

```bash
gcc Generic_Dynamic_array.c Stack.c -o Stack
```

how to run:

```bash
./Stack
```

The **Linked_List** has functions:

we have 2 linked lists one, in this section I will explain one of them,
the other linked list is the same single linked list but without the max_size (it is implemented in a queue, so the queue has the max_size).

- create_gen_lin_list -> allocates memory for just one node
- delete_node_gen_lin_list -> deletes one node in the list by freeing the memory
- create_head -> allocates memory for the head, and apoints a the pointer first to a node (the node is expected to be allocated)
- delete_List -> deallocates all of the memory allocated for the entire list (for all of the nodes and the head)
- change_cur_element -> changes the data of the current node that the user is accessing
- add_node -> adds a node one after another
- make_node_and_add_node -> creates a new node and then adds it after another nodes
- make_node_set_element_add_node -> creates a new node gives it data and then adds it after another node
- int get_indexof -> search for a specific data and once found you return position which is given depending on the node given for search
what I mean is the index doesn't have to be searched from the start of the list (head), you can give it the second node for example and if it returns 2
that means that it is 2 (because you gave it the second node) + 2 (the index given) = 4 (the forth position from the start of the list)
this may not seem very linked list like but I like it so yeah.
- get_element -> you get the element of the current node
- get_peek -> you get the data of the first node (the node head points to)
- get_element_index -> you give an index and it returns you the data stored there (the indexing works like get_indexof)
- get_last_element -> simply gives you the data of the last element, the parsing works just like get_indexof.

in most of these when I say return I usually mean return through the arguments (not using the return command)

how to build:

```bash
gcc Generic_Linked_List.c -o Linked_List
```

how to run:

```bash
./Linked_List
```

I will be adding information for the others as well, yes I know that I sound lazy.

### Future Plans

Eventually, all data structures will be compiled into a single library with a unified `main()` program.
But before that I want to do a HashMap, Stack with Linked List implementation, queue with doubly linked list implementation or just sigle linked list implementation,
Circular queue and if I think of something else I will probably add it
