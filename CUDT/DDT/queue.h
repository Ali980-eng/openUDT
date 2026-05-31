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

#ifndef OPENUDT___CUDT_CDQ_H
#define OPENUDT___CUDT_CDQ_H

cobject(cqueue,
        size_t size;
        size_t capacity;
        cdynamic * data;);

void cqueue_init(cqueue *queue)
{
    queue->size = 0;
    queue->capacity = 4;
    queue->data = (cdynamic *)malloc(queue->capacity * sizeof(cdynamic));
}

void cqueue_free(cqueue *queue)
{
    free(queue->data);
    queue->data = NULL;
    queue->size = 0;
    queue->capacity = 0;
}

void set(cqueue *queue, cqueue *other)
{
    queue->size = other->size;
    queue->capacity = other->capacity;
    queue->data = (cdynamic *)malloc(queue->capacity * sizeof(cdynamic));
    for (size_t i = 0; i < queue->size; i++)
        queue->data[i] = other->data[i];
}

#ifdef OPENUDT___CUDT_CDA_H
void set(cqueue *queue, DArray *other)
{
    queue->size = other->size;
    queue->capacity = other->capacity;
    queue->data = (cdynamic *)malloc(queue->capacity * sizeof(cdynamic));
    for (size_t i = 0; i < queue->size; i++)
        queue->data[i] = other->data[i];
}
#endif // OPENUDT___CUDT_CDA_H

void enqueue(cqueue *queue, cdynamic value)
{
    if (queue->size >= queue->capacity)
    {
        queue->capacity *= 2;
        queue->data = (cdynamic *)realloc(queue->data, queue->capacity * sizeof(cdynamic));
    }
    queue->data[queue->size++] = value;
}

void dequeue(cqueue *queue)
{
    if (queue->size == 0)
        return; // Queue is empty, nothing to dequeue

    for (size_t i = 0; i < queue->size - 1; i++)
        queue->data[i] = queue->data[i + 1];

    queue->size--;
}

size_t size(cqueue *queue)
{
    return queue->size;
}

size_t capacity(cqueue *queue)
{
    return queue->capacity;
}

#endif // OPENUDT___CUDT_CDQ_H