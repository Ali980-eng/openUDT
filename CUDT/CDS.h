// C Dynamic Stack (CDS) header file

#ifndef OPENUDT___CUDT_CDS_H
#define OPENUDT___CUDT_CDS_H

/**
 * @file CDS.h
 * @brief Dynamic Stack (CDS) implementation for CDynamic structs.
 * @details This module provides a dynamic stack structure (DStack) for storing CDynamic
 * elements, along with functions for initialization, modification, querying, and cleanup.
 * The DStack supports dynamic resizing, element pushing and popping, and other common stack
 *  operations.  Users must call DStack_free() to release resources when finished with the stack.
 * @author Ali Lafi
 * @date 2024-06
 */

#include <stdlib.h>
#include "CDynamic.h"

// CDS: C Dynamic Stack (of CDynamic structs)

typedef struct
{
    size_t size;
    size_t capacity;
    CDynamic *data;
} DStack;

void DStack_init(DStack *stack)
{
    stack->size = 0;
    stack->capacity = 4;
    stack->data = (CDynamic *)malloc(stack->capacity * sizeof(CDynamic));
}

void DStack_free(DStack *stack)
{
    free(stack->data);
    stack->data = NULL;
    stack->size = 0;
    stack->capacity = 0;
}

void push(DStack *stack, CDynamic value)
{
    if (stack->size >= stack->capacity)
    {
        stack->capacity *= 2;
        stack->data = (CDynamic *)realloc(stack->data, stack->capacity * sizeof(CDynamic));
    }
    stack->data[stack->size++] = value;
}

CDynamic pop(DStack *stack)
{
    if (stack->size == 0)
        return (CDynamic){}; // Stack is empty, return default value

    return stack->data[--stack->size];
}

CDynamic peek(DStack *stack)
{
    if (stack->size == 0)
        return (CDynamic){}; // Stack is empty, return default value

    return stack->data[stack->size - 1];
}

size_t size(DStack *stack)
{
    return stack->size;
}

size_t capacity(DStack *stack)
{
    return stack->capacity;
}

#endif // OPENUDT___CUDT_CDS_H