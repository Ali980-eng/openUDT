/** @file dynamic.h
 *  @brief cdynamic struct and related functions for dynamic typing.
 * @details This module defines the cdynamic struct, which can hold a value of various types
 * along with a type tag.  It provides initialization functions for different types, as well as
 * casting and conversion utilities.  Users must call cdynamic_init() before using a cdynamic
 * instance to ensure it is in a valid state.
 * @author Ali Lafi
 * @date 2024-06
 */

#include "clite/micros.h"
#include <stdexcpt.h>
#include <stdbool.h>
#include <limits.h>

#ifndef OPENUDT___CUDT_DYNAMIC_H
#define OPENUDT___CUDT_DYNAMIC_H

cenum{
    _NULL_,
    BOOL,
    CHAR,
    SHORT,
    INT,
    FLOAT,
    LONG,
    DOUBLE} dynamic_index;

cobject(cdynamic, dynamic_index id; double value;);

static inline cdynamic cdynamic_new()
{
    cdynamic obj;
    obj.id = _NULL_;
    obj.value = 0.0;
    return obj;
}

/**
 * @brief Initialize a dynamic object to null state.
 * Sets the type tag to `_NULL_` and zeroes the value.  This function must
 * be called before using the object.
 * @param self Pointer to cdynamic instance.
 */
static inline void cdynamic_self(cdynamic *self)
{
    self->id = _NULL_;
    self->value = 0.0;
}

/**
 * @brief Initialize cdynamic from a boolean.
 * Stores the value as 1.0 or 0.0 and sets the type tag accordingly.
 * @param value Boolean value to assign.
 */
static inline cdynamic cdynamic_bool(bool value)
{
    cdynamic obj;
    obj.id = BOOL;
    obj.value = (value ? 1.0 : 0.0);
    return obj;
}

/**
 * @brief Initialize cdynamic from a char value.
 * The character is converted to double and the type tag is set to CHAR.
 * @param value Character to store.
 */
static inline cdynamic cdynamic_char(char value)
{
    cdynamic obj;
    obj.id = CHAR;
    obj.value = (double)value;
    return obj;
}

/**
 * @brief Initialize cdynamic from a short integer.
 * Converts to double internally.
 * @param value Short integer to store.
 */
static inline cdynamic cdynamic_short(short value)
{
    cdynamic obj;
    obj.id = SHORT;
    obj.value = (double)value;
    return obj;
}

/**
 * @brief Initialize cdynamic from an int.
 * Stored as double.
 * @param value Integer value.
 */
static inline cdynamic cdynamic_int(int value)
{
    cdynamic obj;
    obj.id = INT;
    obj.value = (double)value;
    return obj;
}

/**
 * @brief Initialize cdynamic from a float.
 * The float is promoted to double.
 * @param value Float value to store.
 */
static inline cdynamic cdynamic_float(float value)
{
    cdynamic obj;
    obj.id = FLOAT;
    obj.value = (double)value;
    return obj;
}

/**
 * @brief Initialize cdynamic from a double.
 * @param value Double value to store.
 */
static inline cdynamic cdynamic_double(double value)
{
    cdynamic obj;
    obj.id = DOUBLE;
    obj.value = value;
    return obj;
}

/**
 * @brief Copy initialize from another cdynamic.
 * Performs a shallow copy of the tag and value.
 * @param other Source cdynamic to copy.
 */
static inline cdynamic cdynamic_copy(cdynamic other)
{
    cdynamic obj;
    obj.id = other.id;
    obj.value = other.value;
    return obj;
}

/**
 * @brief Retrieve the textual name of the stored type.
 *
 * @param self Pointer to cdynamic instance.
 * @return String literal representing the current type tag.
 */
static inline const cstrptr type_name(cdynamic self)
{
    switch (self.id)
    {
    case _NULL_:
        return "NULL";
    case BOOL:
        return "BOOL";
    case CHAR:
        return "CHAR";
    case SHORT:
        return "SHORT";
    case INT:
        return "INT";
    case FLOAT:
        return "FLOAT";
    case LONG:
        return "LONG";
    case DOUBLE:
        return "DOUBLE";
    default:
        return "UNKNOWN";
    }
}

static inline bool get_bool(cdynamic self)
{
    switch (self.id)
    {
    case BOOL:
    case CHAR:
    case SHORT:
    case INT:
    case FLOAT:
    case LONG:
    case DOUBLE:
        return self.value != 0.0;
    default:
        printf("run time error: Invalid dynamic type for cast_bool");
    }
    return false;
}

static inline char get_char(cdynamic self)
{
    switch (self.id)
    {
    case BOOL:
        return (char)(self.value != 0.0 ? 1 : 0);
    case CHAR:
        return self.value;
    case SHORT:
    case INT:
    case FLOAT:
    case LONG:
    case DOUBLE:
        if (self.value > (double)'~' || self.value < (double)'\0')
        {
            printf("out of range error: the value is out of the range of ascii table.\n");
            return '~';
        }
        return (char)self.value;
    default:
        printf("run time error: Invalid dynamic type for cast_char\n");
    }
    return '\0';
}

static inline short get_short(cdynamic self)
{
    switch (self.id)
    {
    case BOOL:
        return (short)(self.value != 0.0 ? 1 : 0);
    case CHAR:
    case SHORT:
    case INT:
    case FLOAT:
    case LONG:
    case DOUBLE:
        if (self.value > SHRT_MAX || self.value < SHRT_MIN)
        {
            printf("out of range error: the value is out of range of the type short.\n");
            return (short)0;
        }
        return (short)self.value;
    default:
        printf("run time error: Invalid dynamic type for cast_short");
    }
    return (short)0;
}

static inline int get_int(cdynamic self)
{
    switch (self.id)
    {
    case BOOL:
        return (int)(self.value != 0.0 ? 1 : 0);
    case CHAR:
    case SHORT:
    case INT:
    case FLOAT:
    case LONG:
    case DOUBLE:
        if (self.value > INT_MAX || self.value < INT_MIN)
        {
            printf("out of range error: the value is out of range of the type int.\n");
            return (int)0;
        }
        return (int)self.value;
    default:
        printf("run time error: Invalid dynamic type for cast_int");
    }
}

static inline float get_float(cdynamic self)
{
    switch (self.id)
    {
    case BOOL:
        return (self.value != 0.0 ? 1.0f : 0.0f);
    case CHAR:
    case SHORT:
    case INT:
    case FLOAT:
    case LONG:
    case DOUBLE:
        return (float)(self.value);
    default:
        printf("run time error: Invalid dynamic type for cast_float\n");
    }
    return 0.0f;
}

static inline double get_double(cdynamic self)
{
    switch (self.id)
    {
    case BOOL:
        return self.value != 0.0 ? 1.0 : 0.0;
    case CHAR:
    case SHORT:
    case INT:
    case FLOAT:
    case LONG:
    case DOUBLE:
        return self.value;
    default:
        printf("run time error: Invalid dynamic type for cast_double");
    }
}

static inline cdynamic cast2bool(cdynamic self)
{
    if (self.id == BOOL)
    {
        return self;
    }
    return cdynamic_bool(self.value != 0.0);
}

static inline cdynamic cast2char(cdynamic self)
{
    if (self.id == CHAR)
    {
        return self;
    }
    if (self.value > '~' || self.value < '\0')
    {
        printf("out of range error: the value is out of range of the type char.\n");
        return cdynamic_new();
    }
    return cdynamic_char(self.value);
}

static inline cdynamic cast2short(cdynamic self)
{
    if (self.id == SHORT)
    {
        return self;
    }
    if (self.value > SHRT_MAX || self.value < SHRT_MIN)
    {
        printf("out of range error: the value is out of range of the type short.\n");
        return cdynamic_new();
    }
    return cdynamic_short(self.value);
}

static inline cdynamic cast2int(cdynamic self)
{
    if (self.id == INT)
    {
        return self;
    }
    if (self.value > INT_MAX || self.value < INT_MIN)
    {
        printf("out of range error: the value is out of range of the type int.\n");
        return cdynamic_new();
    }
    return cdynamic_int(self.value);
}

static inline cdynamic cast2float(cdynamic self)
{
    if (self.id == FLOAT)
    {
        return self;
    }
    return cdynamic_float(self.value);
}

static inline cdynamic cast2double(cdynamic self)
{
    if (self.id == DOUBLE)
    {
        return self;
    }
    return cdynamic_double(self.value);
}

/**
 * @brief Convert the object to a specified target type.
 *
 * Performs the appropriate cast based on @p target_type and returns a new
 * cdynamic with that type and value.  Throws if the target type is
 * unsupported.
 *
 * @param self        Source object to convert.
 * @param target_type Desired dynamic_index value.
 * @return New cdynamic holding the converted value.
 */
static inline cdynamic convert_to(cdynamic self, dynamic_index target_type)
{
    switch (target_type)
    {
    case _NULL_:
        return cdynamic_new();
    case BOOL:
        return cast2bool(self);
    case CHAR:
        return cast2char(self);
    case SHORT:
        return cast2short(self);
    case INT:
        return cast2int(self);
    case FLOAT:
        return cast2float(self);
    case DOUBLE:
        return cast2double(self);
    default:
        printf("run time error: Invalid target type for convert_to");
        return cdynamic_new();
    }
}

/**
 * @brief Retrieve the stored numeric value.
 *
 * @param self Pointer to cdynamic instance.
 * @return Underlying double value.
 */
static inline double get_value(cdynamic self) { return self.value; }

/**
 * @brief Get the type tag of the dynamic object.
 *
 * @param self Pointer to cdynamic instance.
 * @return The current dynamic_index id.
 */
static inline dynamic_index get_id(cdynamic self) { return self.id; }

static inline bool is_null(cdynamic self) { return self.id == _NULL_; }

static inline bool is_bool(cdynamic self) { return self.id == BOOL; }

static inline bool is_char(cdynamic self) { return self.id == CHAR; }

static inline bool is_short(cdynamic self) { return self.id == SHORT; }

static inline bool is_int(cdynamic self) { return self.id == INT; }

static inline bool is_long(cdynamic self) { return self.id == LONG; }

static inline bool is_float(cdynamic self) { return self.id == FLOAT; }

static inline bool is_double(cdynamic self) { return self.id == DOUBLE; }

#endif // OPENUDT___CUDT_DYNAMIC_H