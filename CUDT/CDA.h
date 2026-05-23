// C Dynamic Array (CDA) implementation
#ifndef OPENUDT___CUDT_CDA_H
#define OPENUDT___CUDT_CDA_H

/** @file CDA.h
 *  @brief C Dynamic Array (CDA) implementation for CDynamic structs.
 * @details This module provides a dynamic array structure (DArray) for storing CDynamic
 * elements, along with functions for initialization, modification, querying, and cleanup.
 * The DArray supports dynamic resizing, element insertion, searching, and other common array
 * operations.  Users must call DArray_free() to release resources when finished with the array.
 * @author Ali Lafi
 * @date 2024-06
 */

#include <stdlib.h>
#include "CDynamic.h"

// CDA: C Dynamic Array (of CDynamic structs)

typedef struct
{
    size_t size;
    size_t capacity;
    CDynamic *data;
} DArray;

/**
 * @brief Initialize a dynamic array.
 *
 * Sets initial size to zero, capacity to 4 and allocates storage for
 * elements.  The user should call DynamicArray_free() when the array is
 * no longer needed.
 *
 * @param arr Pointer to the DDA to initialize.
 */
void DArray_init(DArray *arr)
{
    arr->size = 0;
    arr->capacity = 4;
    arr->data = (CDynamic *)malloc(arr->capacity * sizeof(CDynamic));
}

/**
 * @brief Copy contents from one array into another.
 *
 * Allocates new storage in @p arr and performs a element-wise copy of
 * @p other.  Any previous contents of @p arr are lost (caller must free
 * first if necessary).
 *
 * @param arr   Destination array to populate.
 * @param other Source array to copy from.
 */
void set(DArray *arr, DArray *other)
{
    arr->size = other->size;
    arr->capacity = other->capacity;
    arr->data = (CDynamic *)malloc(arr->capacity * sizeof(CDynamic));
    for (size_t i = 0; i < arr->size; i++)
        arr->data[i] = other->data[i];
}

/**
 * @brief Append an element to the end of the array.
 *
 * Grows the underlying storage (doubling capacity) if necessary.
 *
 * @param arr   Array to modify.
 * @param value Element to append.
 */
void append(DArray *arr, CDynamic value)
{
    if (arr->size >= arr->capacity)
    {
        arr->capacity *= 2;
        arr->data = (CDynamic *)realloc(arr->data, arr->capacity * sizeof(CDynamic));
    }
    arr->data[arr->size++] = value;
}

/**
 * @brief Insert an element at a specific index.
 *
 * If @p index is greater than the current size, the value is appended.
 * Existing elements are shifted right.  Capacity is grown if required.
 *
 * @param arr   Array to modify.
 * @param index Position at which to insert.
 * @param value Element to insert.
 */
void insert(DArray *arr, size_t index, CDynamic value)
{
    if (index > arr->size)
        index = arr->size;

    if (arr->size >= arr->capacity)
    {
        arr->capacity *= 2;
        arr->data = (CDynamic *)realloc(arr->data, arr->capacity * sizeof(CDynamic));
    }

    for (size_t i = arr->size; i > index; i--)
        arr->data[i] = arr->data[i - 1];

    arr->data[index] = value;
    arr->size++;
}

/**
 * @brief Locate the first occurrence of a value in the array.
 *
 * Comparison is done by member-wise equality on the CDynamic struct.
 *
 * @param arr   Array to search.
 * @param value Value to locate.
 * @return Index of the first match, or (size_t)-1 if not found.
 */
size_t find(DArray *arr, CDynamic value)
{
    for (size_t i = 0; i < arr->size; i++)
    {
        if (arr->data[i].id == value.id && arr->data[i].value == value.value)
            return i;
    }
    return -1; // Not found
}

/**
 * @brief Check if the array contains a given value.
 *
 * @param arr   Array to query.
 * @param value Value to look for.
 * @return true if found, false otherwise.
 */
bool contains(DArray *arr, CDynamic value)
{
    return find(arr, value) != -1;
}

/**
 * @brief Return the current number of elements in the array.
 *
 * @param arr Array to query.
 * @return Number of stored elements.
 */
size_t size(DArray *arr)
{
    return arr->size;
}

/**
 * @brief Return the current capacity of the internal buffer.
 *
 * @param arr Array to query.
 * @return Allocated capacity (number of elements) before reallocation.
 */
size_t capacity(DArray *arr)
{
    return arr->capacity;
}

/**
 * @brief Remove element at a given index.
 *
 * Shifts subsequent elements left.  If index is out of range, the call
 * is ignored.
 *
 * @param arr   Array to modify.
 * @param index Position of element to remove.
 */
void remove_at(DArray *arr, size_t index)
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
 * @param arr Array to clear.
 */
void clear(DArray *arr)
{
    arr->size = 0;
}

/**
 * @brief Access element by index (value copy).
 *
 * Throws std::out_of_range if the index is invalid.
 *
 * @param arr   Array to query.
 * @param index Position of the element.
 * @return Copy of the element at @p index.
 */
CDynamic at(DArray *arr, size_t index)
{
    if (index >= arr->size)
        throw std::out_of_range("Index out of bounds");
    return arr->data[index];
}

/**
 * @brief Get a pointer to the value field of an element.
 *
 * Useful for direct modification of the numeric portion of a
 * CDynamic entry.  Bounds-checked similarly to at().
 *
 * @param arr   Array to query.
 * @param index Position of the element.
 * @return Pointer to the value member.
 */
double *get(DArray *arr, size_t index)
{
    if (index >= arr->size)
        throw std::out_of_range("Index out of bounds");
    return &arr->data[index].value;
}

/**
 * @brief Return pointer to first element (for range-based iteration).
 *
 * @param arr Array to query.
 * @return Pointer to the first CDynamic element.
 */
auto begin(DArray *arr) { return arr->data; }

/**
 * @brief Return pointer one past the last element.
 *
 * Used together with begin() for iteration.
 *
 * @param arr Array to query.
 * @return Pointer past the last CDynamic element.
 */
auto end(DArray *arr) { return arr->data + arr->size; }

/**
 * @brief Count occurrences of a value in the array.
 *
 * @param arr   Array to search.
 * @param value Value to tally.
 * @return Number of matching elements.
 */
size_t count(DArray *arr, CDynamic value)
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
 * Throws std::out_of_range if the array is empty.
 *
 * @param arr Array to query.
 * @return Index of the last element (size - 1).
 */
size_t last_index(DArray *arr)
{
    if (arr->size == 0)
        throw std::out_of_range("Array is empty");
    return arr->size - 1;
}

/**
 * @brief Return a copy of the last element in the array.
 *
 * Throws std::out_of_range if the array is empty.
 *
 * @param arr Array to query.
 * @return Copy of the final CDynamic element.
 */
CDynamic last_element(DArray *arr)
{
    if (arr->size == 0)
        throw std::out_of_range("Array is empty");
    return arr->data[arr->size - 1];
}

/**
 * @brief Free all resources held by the array.
 *
 * Releases the dynamically allocated buffer and resets fields to
 * a clean state.  After calling this, the array must be re‑initialized
 * before use.
 *
 * @param arr Array to free.
 */
void DArray_free(DArray *arr)
{
    free(arr->data);
    arr->data = NULL;
    arr->size = 0;
    arr->capacity = 0;
}

#endif // OPENUDT___CUDT_CDA_H