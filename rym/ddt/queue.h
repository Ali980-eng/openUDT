/**
 * @file queue.h
 * @brief Dynamic Data Queue (cqueue) implementation for cdynamic structs.
 * @details This module provides a dynamic queue structure (cqueue) for storing cdynamic
 * elements, along with functions for initialization, modification, querying, and cleanup.
 * The cqueue supports dynamic resizing, element enqueueing and dequeueing, and other common
 * queue operations.  Users must call cqueue_free() to release resources when finished with the
 * queue.
 * @author Ali Lafi
 * @date 2024-06
 */

#include <stdlib.h>
#include "dynamic.h"

#ifndef OPENUDT___RYM_DDT_QUEUE_H
#define OPENUDT___RYM_DDT_QUEUE_H

cobject
{
    size_t size;
    size_t capacity;
    cdynamic *data;
}
cqueue;

static inline void cqueue_init(cqueue *queue)
{
    queue->size = 0;
    queue->capacity = 4;
    queue->data = (cdynamic *)malloc(queue->capacity * sizeof(cdynamic));
}

static inline void cqueue_free(cqueue *queue)
{
    free(queue->data);
    queue->data = NULL;
    queue->size = 0;
    queue->capacity = 0;
}

static inline void set(cqueue *queue, cqueue *other)
{
    queue->size = other->size;
    queue->capacity = other->capacity;
    queue->data = (cdynamic *)malloc(queue->capacity * sizeof(cdynamic));
    for (size_t i = 0; i < queue->size; i++)
        queue->data[i] = other->data[i];
}

#ifdef OPENUDT___CUDT_ARRAY_H
static inline void set(cqueue *queue, DArray *other)
{
    queue->size = other->size;
    queue->capacity = other->capacity;
    queue->data = (cdynamic *)malloc(queue->capacity * sizeof(cdynamic));
    for (size_t i = 0; i < queue->size; i++)
        queue->data[i] = other->data[i];
}
#endif // OPENUDT___CUDT_ARRAY_H

static inline void enqueue(cqueue *queue, cdynamic value)
{
    if (queue->size >= queue->capacity)
    {
        queue->capacity *= 2;
        queue->data = (cdynamic *)realloc(queue->data, queue->capacity * sizeof(cdynamic));
    }
    queue->data[queue->size++] = value;
}

static inline void dequeue(cqueue *queue)
{
    if (queue->size == 0)
        return; // Queue is empty, nothing to dequeue

    for (size_t i = 0; i < queue->size - 1; i++)
        queue->data[i] = queue->data[i + 1];

    queue->size--;
}

static inline size_t size(cqueue *queue)
{
    return queue->size;
}

static inline size_t capacity(cqueue *queue)
{
    return queue->capacity;
}

#endif // OPENUDT___RYM_DDT_QUEUE_H