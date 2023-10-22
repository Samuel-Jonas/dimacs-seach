#include "Queue.h"

struct PriorityQueue create_priority_queue() {
    struct PriorityQueue queue = {
        .size = 0,
        .queue = NULL
    };

    return queue;
}

void free_queue(struct PriorityQueue* queue) {
    struct QueueNode** node = &queue->queue;

    while (*node != NULL) {
        struct QueueNode* aux = *node;
        *node = (*node)->next;
        free(aux);
        queue->size--;
    }
}

struct QueueNode* create_queue_node(uint32_t id, uint32_t priority) {
    struct QueueNode* node = malloc(sizeof(struct QueueNode));

    node->id = id;
    node->priority = priority;
    node->next = NULL;

    return node;
}

void insert_into_queue(struct PriorityQueue* queue, uint32_t id, uint32_t priority) {
    struct QueueNode* node = create_queue_node(id, priority);
    struct QueueNode** aux = &queue->queue;

    while (*aux != NULL && node->priority >= (*aux)->priority)
        aux = &(*aux)->next;

    node->next = *aux;
    *aux = node;
    queue->size++;
}

uint32_t pop_queue(struct PriorityQueue* queue) {
    uint32_t id = queue->queue->id;
    struct QueueNode* aux = queue->queue;

    queue->queue = queue->queue->next;
    queue->size--;

    free(aux);

    return id;
}