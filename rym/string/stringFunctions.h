/**
 * @file stringFunctions.h
 * @brief Common string manipulation functions for C-style strings.
 * @details This module provides a set of functions for working with null-terminated C strings,
 * including length calculation, character searching, string comparison, copying, counting occurrences,
 * and finding locations of characters.  These functions operate on raw char pointers and do not
 * perform any dynamic memory management, so users must ensure that destination buffers are
 * sufficiently large when copying strings.  All functions assume that input strings are properly
 * null-terminated.
 * @author Ali Lafi
 * @date 2024-06
 */

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include "cgen/micros/string.h"

#ifndef OPENUDT___RYM_STRING_STRINGFUNCTIONS_H
#define OPENUDT___RYM_STRING_STRINGFUNCTIONS_H

static inline size_t length(const cstrptr _str_)
{
    size_t len = 0;
    while (_str_[len] != '\0')
    {
        len++;
    }
    return len;
}

static inline size_t find(const cstrptr _str_, char ch)
{
    size_t index = 0;
    while (_str_[index] != '\0')
    {
        if (_str_[index] == ch)
        {
            return index;
        }
        index++;
    }
    return -1; // Not found
}

static inline bool compare(const cstrptr _str_1, const cstrptr _str_2)
{
    size_t index = 0;
    while (_str_1[index] != '\0' && _str_2[index] != '\0')
    {
        if (_str_1[index] != _str_2[index])
        {
            return false;
        }
        index++;
    }
    return _str_1[index] == '\0' && _str_2[index] == '\0'; // Both should end at the same time
}

static inline void copy(cstrptr destination, const cstrptr source)
{
    size_t index = 0;
    while (source[index] != '\0')
    {
        destination[index] = source[index];
        index++;
    }
    destination[index] = '\0'; // Null-terminate the destination _str_ing
}

static inline size_t count_char(const cstrptr _str_, char ch)
{
    size_t count = 0;
    size_t index = 0;
    while (_str_[index] != '\0')
    {
        if (_str_[index] == ch)
        {
            count++;
        }
        index++;
    }
    return count;
}

static size_t count_sub_str_(const cstrptr _str_, const cstrptr sub_str_)
{
    size_t count = 0;
    size_t index = 0;
    size_t sub_str__len = length(sub_str_);
    while (_str_[index] != '\0')
    {
        if (compare(_str_ + index, sub_str_))
        {
            count++;
            index += sub_str__len; // Move past the found sub_str_ing
        }
        else
        {
            index++;
        }
    }
    return count;
}

static int *locations(const cstrptr _str_, char ch, size_t out_count)
{
    size_t char_count = count_char(_str_, ch);
    int *indices = (int *)malloc(char_count * sizeof(int));
    size_t index = 0;
    size_t found_index = 0;
    while (_str_[index] != '\0')
    {
        if (_str_[index] == ch)
        {
            indices[found_index++] = index;
        }
        index++;
    }
    out_count = char_count;
    return indices;
}

#endif // OPENUDT___RYM_STRING_STRINGFUNCTIONS_H