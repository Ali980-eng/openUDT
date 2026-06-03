/**
 * @file CStringFunctions.h
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

#ifndef OPENUDT___CUDT_STRING_STRINGFUNCTIONS_H
#define OPENUDT___CUDT_STRING_STRINGFUNCTIONS_H

static inline size_t length(const char *str)
{
    size_t len = 0;
    while (str[len] != '\0')
    {
        len++;
    }
    return len;
}

static inline size_t find(const char *str, char ch)
{
    size_t index = 0;
    while (str[index] != '\0')
    {
        if (str[index] == ch)
        {
            return index;
        }
        index++;
    }
    return -1; // Not found
}

static inline bool compare(const char *str1, const char *str2)
{
    size_t index = 0;
    while (str1[index] != '\0' && str2[index] != '\0')
    {
        if (str1[index] != str2[index])
        {
            return false;
        }
        index++;
    }
    return str1[index] == '\0' && str2[index] == '\0'; // Both should end at the same time
}

static inline void copy(char *destination, const char *source)
{
    size_t index = 0;
    while (source[index] != '\0')
    {
        destination[index] = source[index];
        index++;
    }
    destination[index] = '\0'; // Null-terminate the destination string
}

static inline size_t count_char(const char *str, char ch)
{
    size_t count = 0;
    size_t index = 0;
    while (str[index] != '\0')
    {
        if (str[index] == ch)
        {
            count++;
        }
        index++;
    }
    return count;
}

static size_t count_substr(const char *str, const char *substr)
{
    size_t count = 0;
    size_t index = 0;
    size_t substr_len = length(substr);
    while (str[index] != '\0')
    {
        if (compare(str + index, substr))
        {
            count++;
            index += substr_len; // Move past the found substring
        }
        else
        {
            index++;
        }
    }
    return count;
}

static int *locations(const char *str, char ch, size_t out_count)
{
    size_t char_count = count_char(str, ch);
    int *indices = (int *)malloc(char_count * sizeof(int));
    size_t index = 0;
    size_t found_index = 0;
    while (str[index] != '\0')
    {
        if (str[index] == ch)
        {
            indices[found_index++] = index;
        }
        index++;
    }
    out_count = char_count;
    return indices;
}

#endif // OPENUDT___CUDT_STRING_STRINGFUNCTIONS_H