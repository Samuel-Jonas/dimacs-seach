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

#endif
