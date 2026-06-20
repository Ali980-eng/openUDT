#include "core/bfs.hpp"
#include <cmath>

#pragma once
#ifndef OPENUDT___CORE___DYNAMIC__DYANMIC_T__HPP
#define OPENUDT___CORE___DYNAMIC__DYANMIC_T__HPP

namespace udt
{
    /**
     * @class dynamic_t
     * @brief Dynamic type holder that stores all primitive types simultaneously (bool, char, int, float, double).
     *
     * @details Unlike the `dynamic` class which uses type flags to track which type is active,
     * `dynamic_t` maintains all values at all times. This approach trades memory usage for
     * simplicity - all primitive types are always available without type tracking overhead.
     *
     * Memory Layout:
     * - bool d_bool: boolean value (1 byte)
     * - char d_char: character value (1 byte)
     * - int d_int: integer value (4 bytes)
     * - float d_float: single-precision floating point (4 bytes)
     * - double d_double: double-precision floating point (8 bytes)
     * Total: ~18 bytes per instance
     *
     * Usage Pattern:
     * This class is useful when you need to store multiple interpretations of the same data
     * or when type flexibility is needed without runtime type checking overhead.
     *
     * @warning This class stores all types simultaneously, resulting in higher memory usage
     * compared to type-discriminated alternatives like `dynamic` or `dynamic_u`.
     *
     * @note All operations are constexpr-compatible where possible, enabling compile-time usage.
     * @note Not thread-safe. External synchronization is required for concurrent access.
     */
    class dynamic_t
    {
    private:
        /// @brief Stores boolean value, initialized to false
        bool d_bool = false;
        /// @brief Stores character value, initialized to null character
        char d_char = '\0';
        /// @brief Stores integer value, initialized to zero
        int d_int = 0;
        /// @brief Stores single-precision floating-point value, initialized to 0.0f
        float d_float = 0.0f;
        /// @brief Stores double-precision floating-point value, initialized to 0.0
        double d_double = 0.0;

    public:
        /**
         * @brief Default constructor - initializes all values to zero/false.
         *
         * Creates a dynamic_t with all primitive type values initialized to their
         * default/zero values. This is a constexpr constructor.
         *
         * @post d_bool = false, d_char = '\0', d_int = 0, d_float = 0.0f, d_double = 0.0
         * @note Usable in compile-time constant expressions
         */
        constexpr dynamic_t() = default;
        /**
         * @brief Constructor to initialize dynamic_t with a specific type value.
         * @param value The value to initialize the dynamic_t with.
         */
        constexpr dynamic_t(bool value) noexcept : d_bool(value) {}
        /**
         * @brief Constructor to initialize dynamic_t with a specific type value.
         * @param value The value to initialize the dynamic_t with.
         */
        constexpr dynamic_t(char value) noexcept : d_char(value) {}
        /**
         * @brief Constructor to initialize dynamic_t with a specific type value.
         * @param value The value to initialize the dynamic_t with.
         */
        constexpr dynamic_t(int value) noexcept : d_int(value) {}
        /**
         * @brief Constructor to initialize dynamic_t with a specific type value.
         * @param value The value to initialize the dynamic_t with.
         */
        constexpr dynamic_t(float value) noexcept : d_float(value) {}
        /**
         * @brief Constructor to initialize dynamic_t with a specific type value.
         * @param value The value to initialize the dynamic_t with.
         */
        constexpr dynamic_t(double value) noexcept : d_double(value) {}
        /**
         * @brief Constructor to initialize dynamic_t with all type values.
         * @param bvalue The boolean value to initialize.
         * @param cvalue The character value to initialize.
         * @param value The integer value to initialize.
         * @param fvalue The float value to initialize.
         * @param dvalue The double value to initialize.
         */
        constexpr dynamic_t(bool bvalue, char cvalue, int value, float fvalue, double dvalue) noexcept
        {
            d_bool = bvalue;
            d_char = cvalue;
            d_int = value;
            d_float = fvalue;
            d_double = dvalue;
        }
        /**
         * @brief Copy constructor for dynamic_t.
         * @param other The dynamic_t object to copy from.
         */
        constexpr dynamic_t(const dynamic_t &other) noexcept
        {
            d_bool = other.d_bool;
            d_char = other.d_char;
            d_int = other.d_int;
            d_float = other.d_float;
            d_double = other.d_double;
        }
        /**
         * @brief Set the stored value from a boolean.
         * Sets the internal boolean storage to the provided value.
         * Updates the internal state to reflect that the stored type is boolean.
         * @param value The boolean value to store.
         * @note This function is constexpr and noexcept; it can be evaluated at compile
         * time when used in a constant expression and will not throw.
         * Effects:
         * - The internal boolean storage is set to the provided value.
         * - The internal type state is updated to indicate that the stored type is boolean.
         */
        constexpr void set(bool value) noexcept { d_bool = value; }
        /**
         * @brief Sets the internal character value
         * @param value The character value to be stored
         * @noexcept This function does not throw exceptions
         */
        constexpr void set(char value) noexcept { d_char = value; }
        /**
         * @brief Sets the internal integer value
         *
         * @param val The integer value to set
         * @throws std::invalid_argument if the change is not allowed and complextype is false
         *
         * This method updates the internal integer value if either:
         * - The change is allowed based on change_allowed() check
         * - The complextype flag is true
         * Otherwise, it throws an exception.
         */
        constexpr void set(int value) noexcept { d_int = value; }
        /**
         * @brief Sets the floating-point value
         * @param value The floating-point value to set
         * @note This function is constexpr and noexcept; it can be evaluated at compile
         * time when used in a constant expression and will not throw.
         */
        constexpr void set(float value) noexcept { d_float = value; }
        /**
         * @brief Sets the double-precision floating-point value
         * @param value The double value to set
         * @note This function is constexpr and noexcept; it can be evaluated at compile
         * time when used in a constant expression and will not throw.
         */
        constexpr void set(double value) noexcept { d_double = value; }
        /**
         * @brief Atomically assigns all stored value fields.
         *
         * Sets the object's boolean, character, integer, float and double members
         * to the supplied values in a single call.
         *
         * @param bvalue  New value for the boolean member (d_bool).
         * @param cvalue  New value for the character member (d_char).
         * @param value   New value for the integer member (d_int).
         * @param fvalue  New value for the float member (d_float).
         * @param dvalue  New value for the double member (d_double).
         *
         * @note This function is constexpr and noexcept; it can be used in constant
         *       expressions and is guaranteed not to throw exceptions.
         *
         * @warning Invoking this will overwrite all five stored values unconditionally.
         *
         * @complexity Constant time O(1).
         */
        constexpr void set(bool bvalue, char cvalue, int value, float fvalue, double dvalue) noexcept
        {
            d_bool = bvalue;
            d_char = cvalue;
            d_int = value;
            d_float = fvalue;
            d_double = dvalue;
        }
        /**
         * @brief Sets the values of this object from another dynamic_t object
         *
         * @param other The dynamic_t object to copy values from
         *
         * @details Copies all primitive type values (boolean, character, integer,
         *          float, and double) from the provided dynamic_t object to this object.
         *          This is a constexpr function that performs the operation at compile-time
         *          when possible.
         */
        constexpr void set(dynamic_t &other) noexcept
        {
            d_bool = other.d_bool;
            d_char = other.d_char;
            d_int = other.d_int;
            d_float = other.d_float;
            d_double = other.d_double;
        }
        /// @brief Retrieves the stored boolean value.
        /// @return The stored boolean value.
        constexpr bool get_bool() const noexcept { return d_bool; }
        /// @brief Retrieves the stored character value.
        /// @return The stored character value.
        constexpr char get_char() const noexcept { return d_char; }
        /// @brief Retrieves the stored integer value.
        /// @return The stored integer value.
        constexpr int get_int() const noexcept { return d_int; }
        /// @brief Retrieves the stored float value.
        /// @return The stored float value.
        constexpr float get_float() const noexcept { return d_float; }
        /// @brief Retrieves the stored double value.
        /// @return The stored double value.
        constexpr double get_double() const noexcept { return d_double; }
        /**
         * @brief Reset all stored scalar members to their value-initialized defaults.
         *
         * This constexpr, noexcept function assigns each member its type's
         * value-initialized state: the boolean becomes false, the character
         * becomes '\0', the integer becomes 0, and the floating-point members
         * become 0.0. It is safe to use in constant expressions and provides
         * the no-throw guarantee.
         *
         * Complexity: O(1).
         */
        constexpr void clear() noexcept
        {
            d_bool = bool();
            d_char = char();
            d_int = int();
            d_float = float();
            d_double = double();
        }
        /// @brief Logical OR operator.
        /// @param value The boolean value to OR with the stored boolean.
        /// @return The result of the logical OR operation.
        constexpr bool operator||(bool value) noexcept { return d_bool || value; }
        /// @brief Logical AND operator.
        /// @param value The boolean value to AND with the stored boolean.
        /// @return The result of the logical AND operation.
        constexpr bool operator&&(bool value) noexcept { return d_bool && value; }
        /// @brief Logical XOR operator.
        /// @param value The boolean value to XOR with the stored boolean.
        /// @return The result of the logical XOR operation.
        constexpr bool operator^(bool value) noexcept { return d_bool ^ value; }
        /// @brief Logical AND assignment operator.
        /// @param value The boolean value to AND with the stored boolean.
        constexpr void operator&=(bool value) noexcept { d_bool &= value; }
        /// @brief Logical OR assignment operator.
        /// @param value The boolean value to OR with the stored boolean.
        constexpr void operator|=(bool value) noexcept { d_bool |= value; }
        /// @brief Logical XOR assignment operator.
        /// @param value The boolean value to XOR with the stored boolean.
        constexpr void operator^=(bool value) noexcept { d_bool ^= value; }
        /// @brief Logical NOT operator.
        /// @return The result of the logical NOT operation.
        constexpr bool operator!() noexcept { return !d_bool; }
        /// @brief Assignment operator for boolean values.
        /// @param value The boolean value to assign to the stored boolean.
        constexpr void operator=(bool value) noexcept { set(value); }
        /// @brief Assignment operator for character values.
        /// @param value The character value to assign to the stored character.
        constexpr void operator=(char value) noexcept { set(value); }
        /// @brief Assignment operator for integer values.
        /// @param value The integer value to assign to the stored integer.
        constexpr void operator=(int value) noexcept { set(value); }
        /// @brief Assignment operator for float values.
        /// @param value The float value to assign to the stored float.
        constexpr void operator=(float value) noexcept { set(value); }
        /// @brief Assignment operator for double values.
        /// @param value The double value to assign to the stored double.
        constexpr void operator=(double value) noexcept { set(value); }
        /**
         * @brief Assigns the stored values from another dynamic_t instance.
         *
         * Performs a member-wise copy of the internal value fields from @p other
         * into this object (copies d_bool, d_char, d_int, d_float and d_double).
         * The operation is constexpr and guaranteed not to throw.
         *
         * @param other Reference to the source dynamic_t whose members will be copied.
         *              Note: the parameter is a non-const reference.
         * @return void
         * @note This is a direct, shallow copy of the listed primitive members;
         *       no heap allocation or deep-cloning is performed and no explicit
         *       self-assignment check is done.
         */
        constexpr void operator=(dynamic_t &other) noexcept
        {
            d_bool = other.d_bool;
            d_char = other.d_char;
            d_int = other.d_int;
            d_float = other.d_float;
            d_double = other.d_double;
        }
        /// @brief Greater-than comparison operator for character values.
        /// @param value The character value to compare with the stored character.
        /// @return True if the stored character is greater than the given value, false otherwise.
        constexpr bool operator>(char value) noexcept { return d_char > value; }
        /// @brief Greater-than comparison operator for integer values.
        /// @param value The integer value to compare with the stored integer.
        /// @return True if the stored integer is greater than the given value, false otherwise.
        constexpr bool operator>(int value) noexcept { return d_int > value; }
        /// @brief Greater-than comparison operator for float values.
        /// @param value The float value to compare with the stored float.
        /// @return True if the stored float is greater than the given value, false otherwise.
        constexpr bool operator>(float value) noexcept { return d_float > value; }
        /// @brief Greater-than comparison operator for double values.
        /// @param value The double value to compare with the stored double.
        /// @return True if the stored double is greater than the given value, false otherwise.
        constexpr bool operator>(double value) noexcept { return d_double > value; }
        /// @brief Greater-than-or-equal-to comparison operator for character values.
        /// @param value The character value to compare with the stored character.
        /// @return True if the stored character is greater than or equal to the given value, false otherwise.
        constexpr bool operator>=(char value) noexcept { return d_char >= value; }
        /// @brief Greater-than-or-equal-to comparison operator for integer values.
        /// @param value The integer value to compare with the stored integer.
        /// @return True if the stored integer is greater than or equal to the given value, false otherwise.
        constexpr bool operator>=(int value) noexcept { return d_int >= value; }
        /// @brief Greater-than-or-equal-to comparison operator for float values.
        /// @param value The float value to compare with the stored float.
        /// @return True if the stored float is greater than or equal to the given value, false otherwise.
        constexpr bool operator>=(float value) noexcept { return d_float >= value; }
        /// @brief Greater-than-or-equal-to comparison operator for double values.
        /// @param value The double value to compare with the stored double.
        /// @return True if the stored double is greater than or equal to the given value, false otherwise.
        constexpr bool operator>=(double value) noexcept { return d_double >= value; }
        /// @brief Less-than comparison operator for character values.
        /// @param value The character value to compare with the stored character.
        /// @return True if the stored character is less than the given value, false otherwise.
        constexpr bool operator<(char value) noexcept { return d_char < value; }
        /// @brief Less-than comparison operator for integer values.
        /// @param value The integer value to compare with the stored integer.
        /// @return True if the stored integer is less than the given value, false otherwise.
        constexpr bool operator<(int value) noexcept { return d_int < value; }
        /// @brief Less-than comparison operator for float values.
        /// @param value The float value to compare with the stored float.
        /// @return True if the stored float is less than the given value, false otherwise.
        constexpr bool operator<(float value) noexcept { return d_float < value; }
        /// @brief Less-than comparison operator for double values.
        /// @param value The double value to compare with the stored double.
        /// @return True if the stored double is less than the given value, false otherwise.
        constexpr bool operator<(double value) noexcept { return d_double < value; }
        /// @brief Less-than-or-equal-to comparison operator for character values.
        /// @param value The character value to compare with the stored character.
        /// @return True if the stored character is less than or equal to the given value, false otherwise.
        constexpr bool operator<=(char value) noexcept { return d_char <= value; }
        /// @brief Less-than-or-equal-to comparison operator for integer values.
        /// @param value The integer value to compare with the stored integer.
        /// @return True if the stored integer is less than or equal to the given value, false otherwise.
        constexpr bool operator<=(int value) noexcept { return d_int <= value; }
        /// @brief Less-than-or-equal-to comparison operator for float values.
        /// @param value The float value to compare with the stored float.
        /// @return True if the stored float is less than or equal to the given value, false otherwise.
        constexpr bool operator<=(float value) noexcept { return d_float <= value; }
        /// @brief Less-than-or-equal-to comparison operator for double values.
        /// @param value The double value to compare with the stored double.
        /// @return True if the stored double is less than or equal to the given value, false otherwise.
        constexpr bool operator<=(double value) noexcept { return d_double <= value; }
        /// @brief Equality comparison operator.
        /// @param value The boolean value to compare with the stored boolean.
        /// @return True if the stored boolean is equal to the given value, false otherwise.
        constexpr bool operator==(bool value) noexcept { return d_bool == value; }
        /// @brief Equality comparison operator for character values.
        /// @param value The character value to compare with the stored character.
        /// @return True if the stored character is equal to the given value, false otherwise.
        constexpr bool operator==(char value) noexcept { return d_char == value; }
        /// @brief Equality comparison operator for integer values.
        /// @param value The integer value to compare with the stored integer.
        /// @return True if the stored integer is equal to the given value, false otherwise.
        constexpr bool operator==(int value) noexcept { return d_int == value; }
        /// @brief Equality comparison operator for float values.
        /// @param value The float value to compare with the stored float.
        /// @return True if the stored float is equal to the given value, false otherwise.
        constexpr bool operator==(float value) noexcept { return d_float == value; }
        /// @brief Equality comparison operator for double values.
        /// @param value The double value to compare with the stored double.
        /// @return True if the stored double is equal to the given value, false otherwise.
        constexpr bool operator==(double value) noexcept { return d_double == value; }
        /**
         * @brief Equality comparison operator for dynamic_t.
         *
         * Performs a member-wise comparison of the contained values (d_bool, d_char,
         * d_int, d_float, and d_double) and returns true only if all corresponding
         * members are equal.
         *
         * @param other Reference to the dynamic_t instance to compare with.
         *              Note: the parameter is a non-const reference; if the function
         *              does not modify the argument, consider changing it to
         *              const dynamic_t& to better express intent.
         *
         * @return true if all compared members are equal, false otherwise.
         *
         * @exception noexcept This function is marked noexcept and guarantees not to throw.
         *
         * @complexity Constant time — compares a fixed number of scalar members.
         */
        constexpr bool operator==(dynamic_t &other) noexcept
        {
            return d_bool == other.d_bool &&
                   d_char == other.d_char &&
                   d_int == other.d_int &&
                   d_float == other.d_float &&
                   d_double == other.d_double;
        }
        /// @brief Inequality comparison operator for boolean values.
        /// @param value The boolean value to compare with the stored boolean.
        /// @return True if the stored boolean is not equal to the given value, false otherwise.
        constexpr bool operator!=(bool value) noexcept { return d_bool != value; }
        /// @brief Inequality comparison operator for character values.
        /// @param value The character value to compare with the stored character.
        /// @return True if the stored character is not equal to the given value, false otherwise.
        constexpr bool operator!=(char value) noexcept { return d_char != value; }
        /// @brief Inequality comparison operator for integer values.
        /// @param value The integer value to compare with the stored integer.
        /// @return True if the stored integer is not equal to the given value, false otherwise.
        constexpr bool operator!=(int value) noexcept { return d_int != value; }
        /// @brief Inequality comparison operator for float values.
        /// @param value The float value to compare with the stored float.
        /// @return True if the stored float is not equal to the given value, false otherwise.
        constexpr bool operator!=(float value) noexcept { return d_float != value; }
        /// @brief
        /// @param value
        /// @return
        constexpr bool operator!=(double value) noexcept { return d_double != value; }
        /// @brief Inequality comparison operator for dynamic_t.
        /// @param other The dynamic_t object to compare with.
        /// @return True if the two dynamic_t objects are not equal, false otherwise.
        constexpr bool operator!=(dynamic_t &other) noexcept
        {
            return d_bool != other.d_bool &&
                   d_char != other.d_char &&
                   d_int != other.d_int &&
                   d_float != other.d_float &&
                   d_double != other.d_double;
        }
        /// @brief Addition assignment operator for character values.
        /// @param value The character value to add to the stored character.
        constexpr void operator+=(char value) noexcept { d_char += value; }
        /// @brief Addition assignment operator for integer values.
        /// @param value The integer value to add to the stored integer.
        constexpr void operator+=(int value) noexcept { d_int += value; }
        /// @brief Addition assignment operator for float values.
        /// @param value The float value to add to the stored float.
        constexpr void operator+=(float value) noexcept { d_float += value; }
        /// @brief Addition assignment operator for double values.
        /// @param value The double value to add to the stored double.
        constexpr void operator+=(double value) noexcept { d_double += value; }
        /**
         * @brief Adds the components of another dynamic_t object to this object
         * @param value The dynamic_t object to add
         * @noexcept This function does not throw exceptions
         *
         * Performs component-wise addition of the corresponding members:
         * - Adds d_char values
         * - Adds d_int values
         * - Adds d_float values
         * - Adds d_double values
         */
        constexpr void operator+=(dynamic_t value) noexcept
        {
            d_char += value.d_char;
            d_int += value.d_int;
            d_float += value.d_float;
            d_double += value.d_double;
        }
        /// @brief Subtraction assignment operator for character values.
        /// @param value The character value to subtract from the stored character.
        constexpr void operator-=(char value) noexcept { d_char -= value; }
        /// @brief Subtraction assignment operator for integer values.
        /// @param value The integer value to subtract from the stored integer.
        constexpr void operator-=(int value) noexcept { d_int -= value; }
        /// @brief Subtraction assignment operator for float values.
        /// @param value The float value to subtract from the stored float.
        constexpr void operator-=(float value) noexcept { d_float -= value; }
        /// @brief Subtraction assignment operator for double values.
        /// @param value The double value to subtract from the stored double.
        constexpr void operator-=(double value) noexcept { d_double -= value; }
        /**
         * @brief Subtracts another dynamic_t object from this one.
         *
         * Performs element-wise subtraction of the components of the given dynamic_t value
         * from the corresponding components of this object.
         *
         * @param value The dynamic_t object to subtract from this one
         * @noexcept This operation does not throw exceptions
         */
        constexpr void operator-=(dynamic_t value) noexcept
        {
            d_char -= value.get_char();
            d_int -= value.get_int();
            d_float -= value.d_float;
            d_double -= value.d_double;
        }
        /// @brief Multiplication assignment operator for integer values.
        /// @param value The integer value to multiply with the stored integer.
        constexpr void operator*=(int value) noexcept { d_int *= value; }
        /// @brief Multiplication assignment operator for float values.
        /// @param value The float value to multiply with the stored float.
        constexpr void operator*=(float value) noexcept { d_float *= value; }
        /// @brief Multiplication assignment operator for double values.
        /// @param value The double value to multiply with the stored double.
        constexpr void operator*=(double value) noexcept { d_double *= value; }
        /**
         * @brief Multiplies the dynamic type with another dynamic type
         *
         * Performs element-wise multiplication of the current dynamic_t object with another dynamic_t object.
         * All corresponding numeric members are multiplied together.
         *
         * @param value The dynamic_t object to multiply with
         * @noexcept This operation does not throw exceptions
         */
        constexpr void operator*=(dynamic_t value) noexcept
        {
            d_char *= value.d_char;
            d_int *= value.d_int;
            d_float *= value.d_float;
            d_double *= value.d_double;
        }
        /// @brief Division assignment operator for integer values.
        /// @param value The integer value to divide the stored integer by.
        constexpr void operator/=(int value) noexcept { d_int /= value; }
        /// @brief Division assignment operator for float values.
        /// @param value The float value to divide the stored float by.
        constexpr void operator/=(float value) noexcept { d_float /= value; }
        /// @brief Division assignment operator for double values.
        /// @param value The double value to divide the stored double by.
        constexpr void operator/=(double value) noexcept { d_double /= value; }
        /**
         * @brief Performs compound division assignment with another dynamic_t object
         * @param value The dynamic_t object to divide by
         * @details Divides each member of the current object by the corresponding member of the parameter
         * @note Operation is performed in-place
         * @note This operation is constexpr and noexcept
         */
        constexpr void operator/=(dynamic_t value) noexcept
        {
            d_int /= value.d_int;
            d_float /= value.d_float;
            d_double /= value.d_double;
        }
        /// @brief Exponentiation assignment operator for integer values.
        /// @param value The integer exponent value.
        constexpr void operator^=(int value) noexcept { d_int = std::pow(d_int, value); }
        /// @brief Exponentiation assignment operator for float values.
        /// @param value The float exponent value.
        constexpr void operator^=(float value) noexcept { d_float = std::pow(d_float, value); }
        /// @brief Exponentiation assignment operator for double values.
        /// @param value The double exponent value.
        constexpr void operator^=(double value) noexcept { d_double = std::pow(d_double, value); }
        /**
         * @brief Raises each numeric member to the power of the corresponding member in another dynamic_t object
         *
         * @param value The dynamic_t object containing the exponent values
         * @note noexcept This operation does not throw exceptions
         */
        constexpr char operator+(char value) noexcept { return (d_char + value); }
        /// @brief Addition operator for integer values.
        /// @param value The integer value to add.
        /// @return The sum of the stored integer and the given integer.
        constexpr int operator+(int value) noexcept { return (d_int + value); }
        /// @brief Addition operator for float values.
        /// @param value The float value to add.
        /// @return The sum of the stored float and the given float.
        constexpr float operator+(float value) noexcept { return (d_float + value); }
        /// @brief Addition operator for double values.
        /// @param value The double value to add.
        /// @return The sum of the stored double and the given double.
        constexpr double operator+(double value) noexcept { return (d_double + value); }
        /// @brief Subtraction operator for character values.
        /// @param value The character value to subtract.
        /// @return The difference between the stored character and the given character.
        constexpr char operator-(char value) noexcept { return (d_char - value); }
        /// @brief Subtraction operator for integer values.
        /// @param value The integer value to subtract.
        /// @return The difference between the stored integer and the given integer.
        constexpr int operator-(int value) noexcept { return (d_int - value); }
        /// @brief Subtraction operator for float values.
        /// @param value The float value to subtract.
        /// @return The difference between the stored float and the given float.
        constexpr float operator-(float value) noexcept { return (d_float - value); }
        /// @brief Subtraction operator for double values.
        /// @param value The double value to subtract.
        /// @return The difference between the stored double and the given double.
        constexpr double operator-(double value) noexcept { return (d_double - value); }
        /// @brief Multiplication operator for integer values.
        /// @param value The integer value to multiply.
        /// @return The product of the stored integer and the given integer.
        constexpr int operator*(int value) noexcept { return (d_int * value); }
        /// @brief Multiplication operator for float values.
        /// @param value The float value to multiply.
        /// @return The product of the stored float and the given float.
        constexpr float operator*(float value) noexcept { return (d_float * value); }
        /// @brief Multiplication operator for double values.
        /// @param value The double value to multiply.
        /// @return The product of the stored double and the given double.
        constexpr double operator*(double value) noexcept { return (d_double * value); }
        /// @brief Division operator for integer values.
        /// @param value The integer value to divide by.
        /// @return The quotient of the stored integer and the given integer.
        constexpr int operator/(int value) noexcept { return (d_int / value); }
        /// @brief Division operator for float values.
        /// @param value The float value to divide by.
        /// @return The quotient of the stored float and the given float.
        constexpr float operator/(float value) noexcept { return (d_float / value); }
        /// @brief Division operator for double values.
        /// @param value The double value to divide by.
        /// @return The quotient of the stored double and the given double.
        constexpr double operator/(double value) noexcept { return (d_double / value); }
        /// @brief Exponentiation operator for integer values.
        /// @param value The integer exponent value.
        /// @return The result of raising the stored integer to the given exponent.
        constexpr int operator^(int value) noexcept { return std::pow(d_int, value); }
        /// @brief Exponentiation operator for float values.
        /// @param value The float exponent value.
        /// @return The result of raising the stored float to the given exponent.
        constexpr float operator^(float value) noexcept { return std::pow(d_float, value); }
        /// @brief Exponentiation operator for double values.
        /// @param value The double exponent value.
        /// @return The result of raising the stored double to the given exponent.
        constexpr double operator^(double value) noexcept { return std::pow(d_double, value); }
        /// @brief Modulus operator for integer values.
        /// @param value The integer value to perform modulus with.
        /// @return The result of performing modulus between the stored integer and the given integer.
        constexpr int operator%(int value) noexcept { return (d_int % value); }
        /// @brief Modulus assignment operator for integer values.
        /// @param value The integer value to perform modulus with.
        /// @return The result of performing modulus assignment between the stored integer and the given integer.
        constexpr void operator%=(int value) noexcept { d_int %= value; }
    };

    constexpr void dynamic_t::set(bool value) noexcept { d_bool = value; }

    constexpr void dynamic_t::set(char value) noexcept { d_char = value; }

    constexpr void dynamic_t::set(int value) noexcept { d_int = value; }

    constexpr void dynamic_t::set(float value) noexcept { d_float = value; }

    constexpr void dynamic_t::set(double value) noexcept { d_double = value; }

    constexpr void dynamic_t::set(bool bvalue, char cvalue, int value, float fvalue, double dvalue) noexcept
    {
        d_bool = bvalue;
        d_char = cvalue;
        d_int = value;
        d_float = fvalue;
        d_double = dvalue;
    }

    constexpr void dynamic_t::set(dynamic_t &other) noexcept
    {
        d_bool = other.d_bool;
        d_char = other.d_char;
        d_int = other.d_int;
        d_float = other.d_float;
        d_double = other.d_double;
    }

    constexpr bool dynamic_t::get_bool() const noexcept { return d_bool; }

    constexpr char dynamic_t::get_char() const noexcept { return d_char; }

    constexpr int dynamic_t::get_int() const noexcept { return d_int; }

    constexpr float dynamic_t::get_float() const noexcept { return d_float; }

    constexpr double dynamic_t::get_double() const noexcept { return d_double; }

    constexpr void dynamic_t::clear() noexcept
    {
        d_bool = bool();
        d_char = char();
        d_int = int();
        d_float = float();
        d_double = double();
    }

    constexpr bool dynamic_t::operator||(bool value) noexcept { return d_bool || value; }

    constexpr bool dynamic_t::operator&&(bool value) noexcept { return d_bool && value; }

    constexpr bool dynamic_t::operator^(bool value) noexcept { return d_bool ^ value; }

    constexpr void dynamic_t::operator&=(bool value) noexcept { d_bool &= value; }

    constexpr void dynamic_t::operator|=(bool value) noexcept { d_bool |= value; }

    constexpr void dynamic_t::operator^=(bool value) noexcept { d_bool ^= value; }

    constexpr bool dynamic_t::operator!() noexcept { return !d_bool; }

    constexpr void dynamic_t::operator=(bool value) noexcept { set(value); }

    constexpr void dynamic_t::operator=(char value) noexcept { set(value); }

    constexpr void dynamic_t::operator=(int value) noexcept { set(value); }

    constexpr void dynamic_t::operator=(float value) noexcept { set(value); }

    constexpr void dynamic_t::operator=(double value) noexcept { set(value); }

    constexpr void dynamic_t::operator=(dynamic_t &other) noexcept
    {
        d_bool = other.d_bool;
        d_char = other.d_char;
        d_int = other.d_int;
        d_float = other.d_float;
        d_double = other.d_double;
    }

    constexpr bool dynamic_t::operator>(char value) noexcept { return d_char > value; }

    constexpr bool dynamic_t::operator>(int value) noexcept { return d_int > value; }

    constexpr bool dynamic_t::operator>(float value) noexcept { return d_float > value; }

    constexpr bool dynamic_t::operator>(double value) noexcept { return d_double > value; }

    constexpr bool dynamic_t::operator>=(char value) noexcept { return d_char >= value; }

    constexpr bool dynamic_t::operator>=(int value) noexcept { return d_int >= value; }

    constexpr bool dynamic_t::operator>=(float value) noexcept { return d_float >= value; }

    constexpr bool dynamic_t::operator>=(double value) noexcept { return d_double >= value; }

    constexpr bool dynamic_t::operator<(char value) noexcept { return d_char < value; }

    constexpr bool dynamic_t::operator<(int value) noexcept { return d_int < value; }

    constexpr bool dynamic_t::operator<(float value) noexcept { return d_float < value; }

    constexpr bool dynamic_t::operator<(double value) noexcept { return d_double < value; }

    constexpr bool dynamic_t::operator<=(char value) noexcept { return d_char <= value; }

    constexpr bool dynamic_t::operator<=(int value) noexcept { return d_int <= value; }

    constexpr bool dynamic_t::operator<=(float value) noexcept { return d_float <= value; }

    constexpr bool dynamic_t::operator<=(double value) noexcept { return d_double <= value; }

    constexpr bool dynamic_t::operator==(bool value) noexcept { return d_bool == value; }

    constexpr bool dynamic_t::operator==(char value) noexcept { return d_char == value; }

    constexpr bool dynamic_t::operator==(int value) noexcept { return d_int == value; }

    constexpr bool dynamic_t::operator==(float value) noexcept { return d_float == value; }

    constexpr bool dynamic_t::operator==(double value) noexcept { return d_double == value; }

    constexpr bool dynamic_t::operator==(dynamic_t &other) noexcept
    {
        return d_bool == other.d_bool &&
               d_char == other.d_char &&
               d_int == other.d_int &&
               d_float == other.d_float &&
               d_double == other.d_double;
    }

    constexpr bool dynamic_t::operator!=(bool value) noexcept { return d_bool != value; }

    constexpr bool dynamic_t::operator!=(char value) noexcept { return d_char != value; }

    constexpr bool dynamic_t::operator!=(int value) noexcept { return d_int != value; }

    constexpr bool dynamic_t::operator!=(float value) noexcept { return d_float != value; }

    constexpr bool dynamic_t::operator!=(double value) noexcept { return d_double != value; }

    constexpr bool dynamic_t::operator!=(dynamic_t &other) noexcept
    {
        return d_bool != other.d_bool &&
               d_char != other.d_char &&
               d_int != other.d_int &&
               d_float != other.d_float &&
               d_double != other.d_double;
    }

    constexpr void dynamic_t::operator+=(char value) noexcept { d_char += value; }

    constexpr void dynamic_t::operator+=(int value) noexcept { d_int += value; }

    constexpr void dynamic_t::operator+=(float value) noexcept { d_float += value; }

    constexpr void dynamic_t::operator+=(double value) noexcept { d_double += value; }

    constexpr void dynamic_t::operator+=(dynamic_t value) noexcept
    {
        d_char += value.d_char;
        d_int += value.d_int;
        d_float += value.d_float;
        d_double += value.d_double;
    }

    constexpr void dynamic_t::operator-=(char value) noexcept { d_char -= value; }

    constexpr void dynamic_t::operator-=(int value) noexcept { d_int -= value; }

    constexpr void dynamic_t::operator-=(float value) noexcept { d_float -= value; }

    constexpr void dynamic_t::operator-=(double value) noexcept { d_double -= value; }

    constexpr void dynamic_t::operator-=(dynamic_t value) noexcept
    {
        d_char -= value.get_char();
        d_int -= value.get_int();
        d_float -= value.d_float;
        d_double -= value.d_double;
    }

    constexpr void dynamic_t::operator*=(int value) noexcept { d_int *= value; }

    constexpr void dynamic_t::operator*=(float value) noexcept { d_float *= value; }

    constexpr void dynamic_t::operator*=(double value) noexcept { d_double *= value; }

    constexpr void dynamic_t::operator*=(dynamic_t value) noexcept
    {
        d_char *= value.d_char;
        d_int *= value.d_int;
        d_float *= value.d_float;
        d_double *= value.d_double;
    }

    constexpr void dynamic_t::operator/=(int value) noexcept { d_int /= value; }

    constexpr void dynamic_t::operator/=(float value) noexcept { d_float /= value; }

    constexpr void dynamic_t::operator/=(double value) noexcept { d_double /= value; }

    constexpr void dynamic_t::operator/=(dynamic_t value) noexcept
    {
        d_int /= value.d_int;
        d_float /= value.d_float;
        d_double /= value.d_double;
    }

    constexpr void dynamic_t::operator^=(int value) noexcept { d_int = std::pow(d_int, value); }

    constexpr void dynamic_t::operator^=(float value) noexcept { d_float = std::pow(d_float, value); }

    constexpr void dynamic_t::operator^=(double value) noexcept { d_double = std::pow(d_double, value); }

    constexpr char dynamic_t::operator+(char value) noexcept { return (d_char + value); }

    constexpr int dynamic_t::operator+(int value) noexcept { return (d_int + value); }

    constexpr float dynamic_t::operator+(float value) noexcept { return (d_float + value); }

    constexpr double dynamic_t::operator+(double value) noexcept { return (d_double + value); }

    constexpr char dynamic_t::operator-(char value) noexcept { return (d_char - value); }

    constexpr int dynamic_t::operator-(int value) noexcept { return (d_int - value); }

    constexpr float dynamic_t::operator-(float value) noexcept { return (d_float - value); }

    constexpr double dynamic_t::operator-(double value) noexcept { return (d_double - value); }

    constexpr int dynamic_t::operator*(int value) noexcept { return (d_int * value); }

    constexpr float dynamic_t::operator*(float value) noexcept { return (d_float * value); }

    constexpr double dynamic_t::operator*(double value) noexcept { return (d_double * value); }

    constexpr int dynamic_t::operator/(int value) noexcept { return (d_int / value); }

    constexpr float dynamic_t::operator/(float value) noexcept { return (d_float / value); }

    constexpr double dynamic_t::operator/(double value) noexcept { return (d_double / value); }

    constexpr int dynamic_t::operator^(int value) noexcept { return std::pow(d_int, value); }

    constexpr float dynamic_t::operator^(float value) noexcept { return std::pow(d_float, value); }

    constexpr double dynamic_t::operator^(double value) noexcept { return std::pow(d_double, value); }

    constexpr int dynamic_t::operator%(int value) noexcept { return (d_int % value); }

    constexpr void dynamic_t::operator%=(int value) noexcept { d_int %= value; }
}

#endif // OPENUDT___CORE___DYNAMIC__DYANMIC_T__HPP