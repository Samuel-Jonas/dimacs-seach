#ifndef STACK_H
#define STACK_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct StackNode {
    uint32_t id;
    struct StackNode* next;
};

struct Stack {
    uint32_t size;
    struct StackNode* stack;
};

struct Stack create_stack();
void free_stack(struct Stack* stack);
void push_stack(struct Stack* stack, uint32_t id);
uint32_t pop_stack(struct Stack* stack);

#endif
