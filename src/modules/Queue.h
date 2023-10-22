#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct QueueNode {
    uint32_t id;
    uint32_t priority;
    struct QueueNode* next;
};

struct PriorityQueue {
    uint32_t size;
    struct QueueNode* queue;
};

struct PriorityQueue create_priority_queue();
void insert_into_queue(struct PriorityQueue* queue, uint32_t id, uint32_t priority);
struct QueueNode* pop_queue(struct PriorityQueue* queue);

#endif
