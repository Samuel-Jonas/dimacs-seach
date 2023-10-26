#include "Stack.h"

struct Stack create_stack() {
    struct Stack stack = {
        .size = 0,
        .stack = NULL
    };

    return stack;
}

void free_stack(struct Stack* stack) {
    struct StackNode** node = &stack->stack;

    while (*node != NULL) {
        struct StackNode* aux = *node;
        *node = (*node)->next;
        free(aux);
        stack->size--;
    }
}

struct StackNode* create_stack_node(uint32_t id) {
    struct StackNode* node = malloc(sizeof(struct StackNode));

    node->id = id;
    node->next = NULL;

    return node;
}

void push_stack(struct Stack* stack, uint32_t id) {
    struct StackNode* node = create_stack_node(id);

    node->next = stack->stack;
    stack->stack = node;
    stack->size++;
}

uint32_t pop_stack(struct Stack* stack) {
    uint32_t id = stack->stack->id;
    struct StackNode* aux = stack->stack;

    stack->stack = stack->stack->next;
    stack->size--;

    free(aux);

    return id;
}