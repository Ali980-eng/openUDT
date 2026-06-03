/** @file carray.h
 *  @brief C Dynamic carray (CDA) implementation for cdynamic structs.
 * @details This module provides a dynamic carray structure (carray) for storing cdynamic
 * elements, along with functions for initialization, modification, querying, and cleanup.
 * The carray supports dynamic resizing, element insertion, searching, and other common carray
 * operations.  Users must call carray_free() to release resources when finished with the carray.
 * @author Ali Lafi
 * @date 2024-06
 */

#include <stdlib.h>
#include "dynamic.h"

#ifndef OPENUDT___CUDT_ARRAY_H
#define OPENUDT___CUDT_ARRAY_H

cobject(carray,
        size_t size;
        size_t capacity;
        cdynamic * data;);

/**
 * @brief Initialize a dynamic carray.
 *
 * Sets initial size to zero, capacity to 4 and allocates storage for
 * elements.  The user should call Dynamiccarray_free() when the carray is
 * no longer needed.
 *
 * @param arr Pointer to the DDA to initialize.
 */
void carray_init(carray *arr)
{
    arr->size = 0;
    arr->capacity = 4;
    arr->data = (cdynamic *)malloc(arr->capacity * sizeof(cdynamic));
}

/**
 * @brief Copy contents from one carray into another.
 *
 * Allocates new storage in @p arr and performs a element-wise copy of
 * @p other.  Any previous contents of @p arr are lost (caller must free
 * first if necessary).
 *
 * @param arr   Destination carray to populate.
 * @param other Source carray to copy from.
 */
void set(carray *arr, carray *other)
{
    arr->size = other->size;
    arr->capacity = other->capacity;
    arr->data = (cdynamic *)malloc(arr->capacity * sizeof(cdynamic));
    for (size_t i = 0; i < arr->size; i++)
        arr->data[i] = other->data[i];
}

/**
 * @brief Append an element to the end of the carray.
 *
 * Grows the underlying storage (doubling capacity) if necessary.
 *
 * @param arr   carray to modify.
 * @param value Element to append.
 */
void append(carray *arr, cdynamic value)
{
    if (arr->size >= arr->capacity)
    {
        arr->capacity *= 2;
        arr->data = (cdynamic *)realloc(arr->data, arr->capacity * sizeof(cdynamic));
    }
    arr->data[arr->size++] = value;
}

/**
 * @brief Insert an element at a specific index.
 *
 * If @p index is greater than the current size, the value is appended.
 * Existing elements are shifted right.  Capacity is grown if required.
 *
 * @param arr   carray to modify.
 * @param index Position at which to insert.
 * @param value Element to insert.
 */
void insert(carray *arr, size_t index, cdynamic value)
{
    if (index > arr->size)
        index = arr->size;

    if (arr->size >= arr->capacity)
    {
        arr->capacity *= 2;
        arr->data = (cdynamic *)realloc(arr->data, arr->capacity * sizeof(cdynamic));
    }

    for (size_t i = arr->size; i > index; i--)
        arr->data[i] = arr->data[i - 1];

    arr->data[index] = value;
    arr->size++;
}

/**
 * @brief Locate the first occurrence of a value in the carray.
 *
 * Comparison is done by member-wise equality on the cdynamic struct.
 *
 * @param arr   carray to search.
 * @param value Value to locate.
 * @return Index of the first match, or (size_t)-1 if not found.
 */
size_t find(carray *arr, cdynamic value)
{
    for (size_t i = 0; i < arr->size; i++)
    {
        if (arr->data[i].id == value.id && arr->data[i].value == value.value)
            return i;
    }
    return -1; // Not found
}

/**
 * @brief Check if the carray contains a given value.
 *
 * @param arr   carray to query.
 * @param value Value to look for.
 * @return true if found, false otherwise.
 */
bool contains(carray *arr, cdynamic value)
{
    return find(arr, value) != -1;
}

/**
 * @brief Return the current number of elements in the carray.
 *
 * @param arr carray to query.
 * @return Number of stored elements.
 */
size_t size(carray *arr)
{
    return arr->size;
}

/**
 * @brief Return the current capacity of the internal buffer.
 *
 * @param arr carray to query.
 * @return Allocated capacity (number of elements) before reallocation.
 */
size_t capacity(carray *arr)
{
    return arr->capacity;
}

/**
 * @brief Remove element at a given index.
 *
 * Shifts subsequent elements left.  If index is out of range, the call
 * is ignored.
 *
 * @param arr   carray to modify.
 * @param index Position of element to remove.
 */
void remove_at(carray *arr, size_t index)
{
    if (index >= arr->size)
        return;

    for (size_t i = index; i < arr->size - 1; i++)
        arr->data[i] = arr->data[i + 1];

    arr->size--;
}

/**
 * @brief Remove all elements without deallocating storage.
 *
 * The size is reset to zero but the capacity remains unchanged.
 *
 * @param arr carray to clear.
 */
void clear(carray *arr)
{
    arr->size = 0;
}

/**
 * @brief Access element by index (value copy).
 *
 * Throws std::out_of_range if the index is invalid.
 *
 * @param arr   carray to query.
 * @param index Position of the element.
 * @return Copy of the element at @p index.
 */
cdynamic at(carray *arr, size_t index)
{
    if (index >= arr->size)
    {
        printf("out of range error: Index out of bounds");
        return cdynamic_new();
    }
    return arr->data[index];
}

/**
 * @brief Get a pointer to the value field of an element.
 *
 * Useful for direct modification of the numeric portion of a
 * cdynamic entry.  Bounds-checked similarly to at().
 *
 * @param arr   carray to query.
 * @param index Position of the element.
 * @return Pointer to the value member.
 */
double get(carray *arr, size_t index)
{
    if (index >= arr->size)
    {
        printf("out of range error: Index out of bounds");
        return (double)0;
    }
    return arr->data[index].value;
}

/**
 * @brief Return pointer to first element (for range-based iteration).
 *
 * @param arr carray to query.
 * @return Pointer to the first cdynamic element.
 */
auto begin(carray *arr) { return arr->data; }

/**
 * @brief Return pointer one past the last element.
 *
 * Used together with begin() for iteration.
 *
 * @param arr carray to query.
 * @return Pointer past the last cdynamic element.
 */
auto end(carray *arr) { return arr->data + arr->size; }

/**
 * @brief Count occurrences of a value in the carray.
 *
 * @param arr   carray to search.
 * @param value Value to tally.
 * @return Number of matching elements.
 */
size_t count(carray *arr, cdynamic value)
{
    size_t count = 0;
    for (size_t i = 0; i < arr->size; i++)
    {
        if (arr->data[i].id == value.id && arr->data[i].value == value.value)
            count++;
    }
    return count;
}

/**
 * @brief Return the index of the last element.
 *
 * Throws std::out_of_range if the carray is empty.
 *
 * @param arr carray to query.
 * @return Index of the last element (size - 1).
 */
size_t last_index(carray *arr)
{
    if (arr->size == 0)
    {
        printf("out of range error: carray is empty");
        return (size_t)0;
    }
    return arr->size - 1;
}

/**
 * @brief Return a copy of the last element in the carray.
 *
 * Throws std::out_of_range if the carray is empty.
 *
 * @param arr carray to query.
 * @return Copy of the final cdynamic element.
 */
cdynamic last_element(carray *arr)
{
    if (arr->size == 0)
    {
        printf("out of range error: carray is empty");
        return cdynamic_new();
    }
    return arr->data[arr->size - 1];
}

/**
 * @brief Free all resources held by the carray.
 *
 * Releases the dynamically allocated buffer and resets fields to
 * a clean state.  After calling this, the carray must be re‑initialized
 * before use.
 *
 * @param arr carray to free.
 */
void carray_free(carray *arr)
{
    free(arr->data);
    arr->data = NULL;
    arr->size = 0;
    arr->capacity = 0;
}

#endif // OPENUDT___CUDT_ARRAY_H