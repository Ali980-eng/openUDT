#ifndef OPENUDT___CUDT_CDYNAMIC_H
#define OPENUDT___CUDT_CDYNAMIC_H

/** @file CDynamic.h
 *  @brief CDynamic struct and related functions for dynamic typing.
 * @details This module defines the CDynamic struct, which can hold a value of various types
 * along with a type tag.  It provides initialization functions for different types, as well as
 * casting and conversion utilities.  Users must call CDynamic_init() before using a CDynamic
 * instance to ensure it is in a valid state.
 * @author Ali Lafi
 * @date 2024-06
 */

#include <stdexcept>

enum class dynamic_index
{
    _NULL_,
    BOOL,
    CHAR,
    SHORT,
    INT,
    FLOAT,
    LONG,
    DOUBLE
};

typedef struct CDynamic
{
    dynamic_index id;
    double value;
};

/**
 * @brief Initialize a dynamic object to null state.
 *
 * Sets the type tag to `_NULL_` and zeroes the value.  This function must
 * be called before using the object.
 *
 * @param self Pointer to CDynamic instance.
 */
void CDynamic_init(CDynamic *self)
{
    self->id = dynamic_index::_NULL_;
    self->value = double();
}

/**
 * @brief Initialize CDynamic from a boolean.
 *
 * Stores the value as 1.0 or 0.0 and sets the type tag accordingly.
 *
 * @param self  Pointer to CDynamic instance.
 * @param value Boolean value to assign.
 */
void CDynamic_init(CDynamic *self, bool value)
{
    self->id = dynamic_index::BOOL;
    self->value = value ? 1.0 : 0.0;
}

/**
 * @brief Initialize CDynamic from a char value.
 *
 * The character is converted to double and the type tag is set to CHAR.
 *
 * @param self  Pointer to CDynamic instance.
 * @param value Character to store.
 */
void CDynamic_init(CDynamic *self, char value)
{
    self->id = dynamic_index::CHAR;
    self->value = static_cast<double>(value);
}

/**
 * @brief Initialize CDynamic from a short integer.
 *
 * Converts to double internally.
 *
 * @param self  Pointer to CDynamic instance.
 * @param value Short integer to store.
 */
void CDynamic_init(CDynamic *self, short value)
{
    self->id = dynamic_index::SHORT;
    self->value = static_cast<double>(value);
}

/**
 * @brief Initialize CDynamic from an int.
 *
 * Stored as double.
 *
 * @param self  Pointer to CDynamic instance.
 * @param value Integer value.
 */
void CDynamic_init(CDynamic *self, int value)
{
    self->id = dynamic_index::INT;
    self->value = static_cast<double>(value);
}

/**
 * @brief Initialize CDynamic from a float.
 *
 * The float is promoted to double.
 *
 * @param self  Pointer to CDynamic instance.
 * @param value Float value to store.
 */
void CDynamic_init(CDynamic *self, float value)
{
    self->id = dynamic_index::FLOAT;
    self->value = static_cast<double>(value);
}

/**
 * @brief Initialize CDynamic from a double.
 *
 * @param self  Pointer to CDynamic instance.
 * @param value Double value to store.
 */
void CDynamic_init(CDynamic *self, double value)
{
    self->id = dynamic_index::DOUBLE;
    self->value = value;
}

/**
 * @brief Copy initialize from another CDynamic.
 *
 * Performs a shallow copy of the tag and value.
 *
 * @param self  Pointer to CDynamic instance to initialize.
 * @param other Source CDynamic to copy.
 */
void CDynamic_init(CDynamic *self, CDynamic *other)
{
    self->id = other->id;
    self->value = other->value;
}

/**
 * @brief Retrieve the textual name of the stored type.
 *
 * @param self Pointer to CDynamic instance.
 * @return String literal representing the current type tag.
 */
char *type_name(CDynamic *self)
{
    switch (self->id)
    {
    case dynamic_index::_NULL_:
        return "NULL";
    case dynamic_index::BOOL:
        return "BOOL";
    case dynamic_index::CHAR:
        return "CHAR";
    case dynamic_index::SHORT:
        return "SHORT";
    case dynamic_index::INT:
        return "INT";
    case dynamic_index::FLOAT:
        return "FLOAT";
    case dynamic_index::LONG:
        return "LONG";
    case dynamic_index::DOUBLE:
        return "DOUBLE";
    default:
        return "UNKNOWN";
    }
}

/**
 * @brief Convert stored value to a bool.
 *
 * Handles numeric types by comparing against zero.  Throws
 * std::runtime_error if the current type is NULL or unrecognized.
 *
 * @param self Pointer to CDynamic instance.
 * @return Boolean representation of the value.
 */
bool cast_bool(CDynamic *self)
{
    switch (self->id)
    {
    case dynamic_index::BOOL:
        return self->value != 0.0;
    case dynamic_index::CHAR:
    case dynamic_index::SHORT:
    case dynamic_index::INT:
    case dynamic_index::FLOAT:
    case dynamic_index::LONG:
    case dynamic_index::DOUBLE:
        return self->value != 0.0;
    default:
        throw std::runtime_error("Invalid dynamic type for cast_bool");
    }
}

/**
 * @brief Convert stored value to a char.
 *
 * Boolean values become 0 or 1; numeric types are cast via C++ rules.
 * Throws on invalid type.
 *
 * @param self Pointer to CDynamic instance.
 * @return Character representation.
 */
char cast_char(CDynamic *self)
{
    switch (self->id)
    {
    case dynamic_index::BOOL:
        return self->value != 0.0 ? 1 : 0;
    case dynamic_index::CHAR:
    case dynamic_index::SHORT:
    case dynamic_index::INT:
    case dynamic_index::FLOAT:
    case dynamic_index::LONG:
    case dynamic_index::DOUBLE:
        return static_cast<char>(self->value);
    default:
        throw std::runtime_error("Invalid dynamic type for cast_char");
    }
}

/**
 * @brief Convert stored value to a short integer.
 *
 * Boolean values map to 0/1; other numeric types are cast with C++
 * semantics.  Throws on unsupported tag.
 *
 * @param self Pointer to CDynamic instance.
 * @return Short integer conversion.
 */
short cast_short(CDynamic *self)
{
    switch (self->id)
    {
    case dynamic_index::BOOL:
        return self->value != 0.0 ? 1 : 0;
    case dynamic_index::CHAR:
    case dynamic_index::SHORT:
    case dynamic_index::INT:
    case dynamic_index::FLOAT:
    case dynamic_index::LONG:
    case dynamic_index::DOUBLE:
        return static_cast<short>(self->value);
    default:
        throw std::runtime_error("Invalid dynamic type for cast_short");
    }
}

/**
 * @brief Convert stored value to an int.
 *
 * Handles bool and numeric types.  Throws std::runtime_error if the
 * object is uninitialized.
 *
 * @param self Pointer to CDynamic instance.
 * @return Integer conversion.
 */
int cast_int(CDynamic *self)
{
    switch (self->id)
    {
    case dynamic_index::BOOL:
        return self->value != 0.0 ? 1 : 0;
    case dynamic_index::CHAR:
    case dynamic_index::SHORT:
    case dynamic_index::INT:
    case dynamic_index::FLOAT:
    case dynamic_index::LONG:
    case dynamic_index::DOUBLE:
        return static_cast<int>(self->value);
    default:
        throw std::runtime_error("Invalid dynamic type for cast_int");
    }
}

/**
 * @brief Convert stored value to a float.
 *
 * All numeric kinds are converted; bools yield 1.0 or 0.0.  Throws if the
 * dynamic type is not convertible.
 *
 * @param self Pointer to CDynamic instance.
 * @return Float representation.
 */
float cast_float(CDynamic *self)
{
    switch (self->id)
    {
    case dynamic_index::BOOL:
        return self->value != 0.0 ? 1.0f : 0.0f;
    case dynamic_index::CHAR:
    case dynamic_index::SHORT:
    case dynamic_index::INT:
    case dynamic_index::FLOAT:
    case dynamic_index::LONG:
    case dynamic_index::DOUBLE:
        return static_cast<float>(self->value);
    default:
        throw std::runtime_error("Invalid dynamic type for cast_float");
    }
}

/**
 * @brief Convert stored value to a double.
 *
 * This is essentially a no-op for numeric types but also handles bool
 * by mapping to 0.0/1.0.  Throws for invalid types.
 *
 * @param self Pointer to CDynamic instance.
 * @return Double value.
 */
double cast_double(CDynamic *self)
{
    switch (self->id)
    {
    case dynamic_index::BOOL:
        return self->value != 0.0 ? 1.0 : 0.0;
    case dynamic_index::CHAR:
    case dynamic_index::SHORT:
    case dynamic_index::INT:
    case dynamic_index::FLOAT:
    case dynamic_index::LONG:
    case dynamic_index::DOUBLE:
        return self->value;
    default:
        throw std::runtime_error("Invalid dynamic type for cast_double");
    }
}

/**
 * @brief Convert the object to a specified target type.
 *
 * Performs the appropriate cast based on @p target_type and returns a new
 * CDynamic with that type and value.  Throws if the target type is
 * unsupported.
 *
 * @param self        Source object to convert.
 * @param target_type Desired dynamic_index value.
 * @return New CDynamic holding the converted value.
 */
CDynamic convert_to(CDynamic *self, dynamic_index target_type)
{
    CDynamic result;
    switch (target_type)
    {
    case dynamic_index::_NULL_:
        CDynamic_init(&result);
        break;
    case dynamic_index::BOOL:
        CDynamic_init(&result, cast_bool(self));
        break;
    case dynamic_index::CHAR:
        CDynamic_init(&result, cast_char(self));
        break;
    case dynamic_index::SHORT:
        CDynamic_init(&result, cast_short(self));
        break;
    case dynamic_index::INT:
        CDynamic_init(&result, cast_int(self));
        break;
    case dynamic_index::FLOAT:
        CDynamic_init(&result, cast_float(self));
        break;
    case dynamic_index::DOUBLE:
        CDynamic_init(&result, cast_double(self));
        break;
    default:
        throw std::runtime_error("Invalid target type for convert_to");
    }
    return result;
}

/**
 * @brief Retrieve the stored numeric value.
 *
 * @param self Pointer to CDynamic instance.
 * @return Underlying double value.
 */
double get_value(CDynamic *self) { return self->value; }

/**
 * @brief Get the type tag of the dynamic object.
 *
 * @param self Pointer to CDynamic instance.
 * @return The current dynamic_index id.
 */
dynamic_index get_id(CDynamic *self) { return self->id; }

#endif // OPENUDT___CUDT_CDYNAMIC_H