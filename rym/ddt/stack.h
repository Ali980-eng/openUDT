/**
 * @file stack.h
 * @brief Dynamic Stack (CDS) implementation for cdynamic structs.
 * @details This module provides a dynamic stack structure (cstack) for storing cdynamic
 * elements, along with functions for initialization, modification, querying, and cleanup.
 * The cstack supports dynamic resizing, element pushing and popping, and other common stack
 *  operations.  Users must call cstack_free() to release resources when finished with the stack.
 * @author Ali Lafi
 * @date 2024-06
 */

#include <stdlib.h>
#include "dynamic.h"

#ifndef OPENUDT___RYM_DDT_STACK_H
#define OPENUDT___RYM_DDT_STACK_H

cobject
{
    size_t size;
    size_t capacity;
    cdynamic *data;
}
cstack;

static inline void cstack_init(cstack *stack)
{
    stack->size = 0;
    stack->capacity = 4;
    stack->data = (cdynamic *)malloc(stack->capacity * sizeof(cdynamic));
}

static inline void cstack_free(cstack *stack)
{
    free(stack->data);
    stack->data = NULL;
    stack->size = 0;
    stack->capacity = 0;
}

static inline void push(cstack *stack, cdynamic value)
{
    if (stack->size >= stack->capacity)
    {
        stack->capacity *= 2;
        stack->data = (cdynamic *)realloc(stack->data, stack->capacity * sizeof(cdynamic));
    }
    stack->data[stack->size++] = value;
}

static inline cdynamic pop(cstack *stack)
{
    if (stack->size == 0)
        return (cdynamic){}; // Stack is empty, return default value

    return stack->data[--stack->size];
}

static inline cdynamic peek(cstack *stack)
{
    if (stack->size == 0)
        return (cdynamic){}; // Stack is empty, return default value

    return stack->data[stack->size - 1];
}

static inline size_t size(cstack *stack)
{
    return stack->size;
}

static inline size_t capacity(cstack *stack)
{
    return stack->capacity;
}

#endif // OPENUDT___RYM_DDT_STACK_H