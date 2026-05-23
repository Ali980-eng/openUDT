// C Dynamic Queue (CDQ) implementation
#ifndef OPENUDT___CUDT_CDQ_H
#define OPENUDT___CUDT_CDQ_H

/**
 * @file CDQ.h
 * @brief Dynamic Data Queue (DQueue) implementation for CDynamic structs.
 * @details This module provides a dynamic queue structure (DQueue) for storing CDynamic
 * elements, along with functions for initialization, modification, querying, and cleanup.
 * The DQueue supports dynamic resizing, element enqueueing and dequeueing, and other common
 * queue operations.  Users must call DQueue_free() to release resources when finished with the
 * queue.
 * @author Ali Lafi
 * @date 2024-06
 */

#include <stdlib.h>
#include "CDynamic.h"

// CDQ: C Dynamic Queue (of CDynamic structs)

typedef struct
{
    size_t size;
    size_t capacity;
    CDynamic *data;
} DQueue;

void DQueue_init(DQueue *queue)
{
    queue->size = 0;
    queue->capacity = 4;
    queue->data = (CDynamic *)malloc(queue->capacity * sizeof(CDynamic));
}

void DQueue_free(DQueue *queue)
{
    free(queue->data);
    queue->data = NULL;
    queue->size = 0;
    queue->capacity = 0;
}

void set(DQueue *queue, DQueue *other)
{
    queue->size = other->size;
    queue->capacity = other->capacity;
    queue->data = (CDynamic *)malloc(queue->capacity * sizeof(CDynamic));
    for (size_t i = 0; i < queue->size; i++)
        queue->data[i] = other->data[i];
}

#ifdef ELC___CGENERAL_CUDT_CDDA_H
void set(DQueue *queue, DArray *other)
{
    queue->size = other->size;
    queue->capacity = other->capacity;
    queue->data = (CDynamic *)malloc(queue->capacity * sizeof(CDynamic));
    for (size_t i = 0; i < queue->size; i++)
        queue->data[i] = other->data[i];
}
#endif // ELC___CGENERAL_CUDT_CDDA_H

void enqueue(DQueue *queue, CDynamic value)
{
    if (queue->size >= queue->capacity)
    {
        queue->capacity *= 2;
        queue->data = (CDynamic *)realloc(queue->data, queue->capacity * sizeof(CDynamic));
    }
    queue->data[queue->size++] = value;
}

void dequeue(DQueue *queue)
{
    if (queue->size == 0)
        return; // Queue is empty, nothing to dequeue

    for (size_t i = 0; i < queue->size - 1; i++)
        queue->data[i] = queue->data[i + 1];

    queue->size--;
}

size_t size(DQueue *queue)
{
    return queue->size;
}

size_t capacity(DQueue *queue)
{
    return queue->capacity;
}

#endif // OPENUDT___CUDT_CDQ_H