#include "Queue.h"

struct PriorityQueue create_priority_queue() {
    struct PriorityQueue queue = {
        .size = 0,
        .queue = NULL
    };

    return queue;
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

struct QueueNode* pop_queue(struct PriorityQueue* queue) {
    struct QueueNode* node = queue->queue;
    queue->queue = queue->queue->next;
    queue->size--;

    return node;
}