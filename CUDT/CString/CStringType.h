#ifndef OPENUDT___CUDT___CSTRING_CSTRINGTYPE_H
#define OPENUDT___CUDT___CSTRING_CSTRINGTYPE_H

/**
 * @file CString.h
 * @brief cstring struct and related functions for C-style string manipulation.
 * @details This module defines the cstring struct, which encapsulates a dynamically allocated
 * character buffer along with its length and capacity.  It provides functions for initialization,
 * appending, copying, resizing, case conversion, searching, splitting, and other common string
 * operations.  Users must call cstring_init() to set up a cstring before use and cstring_free()
 * to release resources when finished.  All functions that modify a cstring take a pointer to
 * ensure changes are reflected in the caller's object.
 * @author Ali Lafi
 * @date 2024-06
 */

#include <string.h>
#include <stdlib.h>
#include <cctype>

typedef struct
{
    char *data;
    size_t length;
    size_t capacity;
} cstring;

/**
 * @brief Initialize a cstring object.
 *
 * Allocates an initial buffer of 16 bytes, sets the length to zero and
 * ensures the string is null-terminated.  The caller must eventually
 * call cstring_free() to release the allocated memory.
 *
 * @param str Pointer to the cstring structure to initialize.
 */
void cstring_init(cstring *str)
{
    str->capacity = 16;
    str->length = 0;
    str->data = (char *)malloc(str->capacity);
    str->data[0] = '\0';
}

/**
 * @brief Append a C‑style string to a cstring.
 *
 * Ensures there is enough capacity (doubling when necessary), then
 * copies the contents of @p src to the end of @p dest and updates the
 * length field.  The destination must have been initialized.
 *
 * @param dest Pointer to the target cstring.
 * @param src  Null‑terminated source string to append.
 */
void cstring_append(cstring *dest, const char *src)
{
    size_t src_len = strlen(src);

    if (dest->length + src_len + 1 > dest->capacity)
    {
        dest->capacity = (dest->length + src_len + 1) * 2;
        dest->data = (char *)realloc(dest->data, dest->capacity);
    }

    strcpy(dest->data + dest->length, src);
    dest->length += src_len;
}

/**
 * @brief Release memory held by a cstring.
 *
 * Frees the heap buffer associated with the string.  After this call the
 * cstring is no longer valid unless re‑initialized by cstring_init().
 *
 * @param str Pointer to the cstring to free.
 */
void cstring_free(cstring *str)
{
    free(str->data);
}

/**
 * @brief Assign a raw C string to a cstring (by value).
 *
 * This function operates on a *copy* of the destination structure, so it
 * has no effect on the caller's object.  It simply illustrates intended
 * semantics; consider using a pointer or returning the updated struct
 * instead.
 *
 * @param destination Copy of the destination cstring structure.
 * @param source      Null‑terminated C string to assign.
 */
inline void set(cstring destination, char *source)
{
    destination.data = source;
    destination.length = strlen(destination.data);
}

/**
 * @brief Assign one cstring to another (by value).
 *
 * Like the other overload, this modifies only the local copy of
 * @p destination.  It does not copy the character data.
 *
 * @param destination Copy of the destination cstring.
 * @param source      Source cstring to copy from.
 */
inline void set(cstring destination, cstring source)
{
    destination.data = source.data;
    destination.length = source.length;
}

/**
 * @brief Change the length of a cstring (on a copy).
 *
 * Adjusts the capacity if necessary and updates the length field.  The
 * passed structure is modified by value, so the caller's string is
 * unaffected.  After increasing the length the contents beyond the old
 * length are undefined except for the terminating null.
 *
 * @param str     cstring structure to resize (copied).
 * @param NLength New desired length (not including terminating null).
 */
void resize(cstring str, size_t NLength)
{
    if (NLength + 1 > str.capacity)
    {
        str.capacity = (NLength + 1) * 2;
        str.data = (char *)realloc(str.data, str.capacity);
    }
    str.length = NLength;
    str.data[NLength] = '\0';
}

/**
 * @brief Copy cstring contents into a C buffer.
 *
 * The destination buffer must be large enough to hold the string plus
 * terminating null.
 *
 * @param destination Buffer where data will be stored.
 * @param source      Source cstring to copy from.
 */
inline void copy(char *destination, cstring source) { strcpy(destination, source.data); }

/**
 * @brief Return the length of a cstring.
 *
 * @param source cstring whose length is queried.
 * @return Number of characters in the string (excluding null).
 */
size_t length(cstring source) { return source.length; }

/**
 * @brief Create a lowercase copy of a cstring.
 *
 * Allocates a new buffer and returns a cstring whose characters are the
 * lowercase equivalents of those in @p source.  The caller must free the
 * returned string's data when finished.
 *
 * @param source Input string to convert.
 * @return New cstring containing lowercase text.
 */
cstring lower(cstring source)
{
    cstring result;
    result.data = (char *)malloc(source.length + 1);
    strcpy(result.data, source.data);
    for (size_t i = 0; i < result.length; i++)
        result.data[i] = tolower(result.data[i]);
    return result;
}

/**
 * @brief Create an uppercase copy of a cstring.
 *
 * Similar to lower(), but converts characters to uppercase.
 *
 * @param source Input string to convert.
 * @return New cstring containing uppercase text.
 */
cstring upper(cstring source)
{
    cstring result;
    result.data = (char *)malloc(source.length + 1);
    strcpy(result.data, source.data);
    for (size_t i = 0; i < result.length; i++)
        result.data[i] = toupper(result.data[i]);
    return result;
}

/**
 * @brief Concatenate two cstrings and return a new one.
 *
 * Allocates a fresh cstring containing the contents of @p destination
 * followed by @p source.  The original arguments are not modified.
 *
 * @param destination First operand.
 * @param source      Second operand to append.
 * @return Newly allocated cstring with combined text.
 */
cstring append(cstring destination, cstring source)
{
    cstring result;
    result.data = (char *)malloc(destination.length + source.length + 1);
    strcpy(result.data, destination.data);
    strcat(result.data, source.data);
    result.length = strlen(result.data);
    return result;
}

/**
 * @brief Append a C string to a cstring, returning a new object.
 *
 * Similar to the previous overload but takes a raw C string as second
 * argument.
 *
 * @param destination Base string.
 * @param source      Null‑terminated C string to append.
 * @return New cstring containing the concatenation.
 */
cstring append(cstring destination, char *source)
{
    cstring result;
    result.data = (char *)malloc(destination.length + strlen(source) + 1);
    strcpy(result.data, destination.data);
    strcat(result.data, source);
    result.length = strlen(result.data);
    return result;
}

/**
 * @brief Append a single character to a cstring, returning a new one.
 *
 * Allocates space for the extra character and null terminator.  The
 * original string is left unchanged.
 *
 * @param destination Original string.
 * @param source      Character to append.
 * @return New cstring containing the result.
 */
cstring add(cstring destination, char source)
{
    cstring result;
    result.data = (char *)malloc(destination.length + 2);
    strcpy(result.data, destination.data);
    result.data[destination.length] = source;
    result.data[destination.length + 1] = '\0';
    result.length = strlen(result.data);
    return result;
}

/**
 * @brief Determine if a character exists in the string.
 *
 * @param source The string to search.
 * @param target Character to look for.
 * @return true if @p target appears anywhere, false otherwise.
 */
bool search(cstring source, char target)
{
    for (size_t i = 0; i < source.length; i++)
    {
        if (source.data[i] == target)
            return true;
    }
    return false;
}

/**
 * @brief Search for a C string inside the cstring.
 *
 * @param source The string to scan.
 * @param target Null‑terminated substring to find.
 * @return true if @p target is found, false otherwise.
 */
bool search(cstring source, char *target)
{
    return strstr(source.data, target) != NULL;
}

/**
 * @brief Search for another cstring within this one.
 *
 * @param source Source string to examine.
 * @param target cstring to search for.
 * @return true if @p target is a substring of @p source.
 */
bool search(cstring source, cstring target)
{
    return strstr(source.data, target.data) != NULL;
}

/**
 * @brief Split a cstring into tokens on a delimiter.
 *
 * The function uses strtok() on a writable copy of the data and returns
 * an array of freshly initialized cstrings.  The caller is responsible for
 * freeing each element and the array itself.
 *
 * @param source    The string to split; its contents are modified.
 * @param delimiter Character used as separator (default is space).
 * @param count     If non‑NULL, receives the number of tokens produced.
 * @return Pointer to dynamically allocated array of cstring tokens.
 */
cstring *split(cstring source, char delimiter = ' ', size_t *count = NULL)
{
    size_t capacity = 4;
    size_t length = 0;
    cstring *result = (cstring *)malloc(capacity * sizeof(cstring));

    char *token = strtok(source.data, &delimiter);
    while (token != NULL)
    {
        if (length >= capacity)
        {
            capacity *= 2;
            result = (cstring *)realloc(result, capacity * sizeof(cstring));
        }
        cstring_init(&result[length]);
        cstring_append(&result[length], token);
        length++;
        token = strtok(NULL, &delimiter);
    }
    *count = length;
    return result;
}

/**
 * @brief Extract a substring from a cstring.
 *
 * Allocates a new cstring containing @p length characters starting at
 * position @p start from @p source.  No bounds checking is performed.
 *
 * @param source The original string.
 * @param start  Zero‑based start index.
 * @param length Number of characters to include.
 * @return New cstring with the requested slice.
 */
cstring substring(cstring source, size_t start, size_t length)
{
    cstring result;
    result.data = (char *)malloc(length + 1);
    strncpy(result.data, source.data + start, length);
    result.data[length] = '\0';
    result.length = length;
    return result;
}

/**
 * @brief Return a new cstring containing the reverse of the input.
 *
 * The returned string is freshly allocated; the original is unchanged.
 *
 * @param source String to reverse.
 * @return Reversed copy of @p source.
 */
cstring reverse(cstring source)
{
    cstring result;
    result.data = (char *)malloc(source.length + 1);
    for (size_t i = 0; i < source.length; i++)
        result.data[i] = source.data[source.length - 1 - i];
    result.data[source.length] = '\0';
    result.length = source.length;
    return result;
}

// Insert Begning and End

/**
 * @brief Insert a substring at an arbitrary position.
 *
 * The function shifts the tail of @p source to make room for
 * @p substring.  If @p position is larger than the current length it is
 * treated as an append.  Capacity is grown if necessary.
 *
 * @param source    Pointer to the string to modify.
 * @param substring Null‑terminated substring to insert.
 * @param position  Insertion index (0 = beginning).
 */
void insertBE(cstring *source, char *substring, size_t position)
{
    if (position > source->length)
        position = source->length;

    size_t substring_len = strlen(substring);
    size_t new_length = source->length + substring_len;

    if (new_length + 1 > source->capacity)
    {
        source->capacity = (new_length + 1) * 2;
        source->data = (char *)realloc(source->data, source->capacity);
    }

    memmove(source->data + position + substring_len, source->data + position, source->length - position + 1);
    memcpy(source->data + position, substring, substring_len);
    source->length = new_length;
}

/**
 * @brief Insert a substring at the beginning of a cstring.
 *
 * Convenience wrapper around insertBE() with position set to 0.
 *
 * @param source    Pointer to the string to modify.
 * @param substring Null‑terminated substring to insert.
 */
void insertB(cstring *source, char *substring)
{
    insertBE(source, substring, 0);
}

// Insert End

/**
 * @brief Append a substring to the end of a cstring.
 *
 * Convenience wrapper around insertBE() with position equal to the
 * current string length, effectively performing an append.
 *
 * @param source    Pointer to the string to modify.
 * @param substring Null‑terminated substring to insert.
 */
void insertE(cstring *source, char *substring)
{
    insertBE(source, substring, source->length);
}

size_t where(cstring str, char ch)
{
    for (size_t index = 0; index < str.length; index++)
    {
        if (str.data[index] == ch)
        {
            return index;
        }
    }
    return -1; // Not found
}

bool exist(cstring str, char ch)
{
    for (size_t index = 0; index < str.length; index++)
    {
        if (str.data[index] == ch)
        {
            return true;
        }
    }
    return false; // Not found
}

bool exist(cstring str, char *substr)
{
    return strstr(str.data, substr) != NULL;
}

bool exist(cstring str, cstring substr)
{
    return strstr(str.data, substr.data) != NULL;
}

#endif // OPENUDT___CUDT___CSTRING_CSTRINGTYPE_H