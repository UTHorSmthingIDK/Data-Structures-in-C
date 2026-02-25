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

## Project Structure

The project is not fully structured yet.

Compilation depends on what you want to test.  
Currently, each data structure has its own `main()` function for testing purposes.  

for example:
- **Stack** uses the Generic Dynamic Array, so both files must be compiled together.  
- **Queue** will eventually have a version using a list, but currently may also depend on the Generic Dynamic Array.  
- For the **Generic Dynamic Array**, remove the commented-out `main()` function if you want to compile it separately. This avoids conflicts when compiling structures like Stack that also include it.  

### Future Plans

Eventually, all data structures will be compiled into a single library with a unified `main()` program.
But before that I want to do a HashMap, Stack with Linked List implementation, queue with doubly linked list implementation or just sigle linked list implementation,
Circular queue and if I think of something else I will probably add it
