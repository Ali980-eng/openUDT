/**
 * @file dynamic.hpp
 * @brief Defines the dynamic class for holding and manipulating various standard data types.
 * @details The dynamic class can store values of types bool, char, int, float, and double, along with type-tracking flags. It provides methods for setting and retrieving values, as well as type information. The class is designed
 * to be used in C++23 and is not thread-safe. It uses a bit flag system to track the active type of the stored value, allowing for efficient type management and operations.
 * @note This class is intended for educational and illustrative purposes to demonstrate a dynamic type holder in C++. It is not optimized for performance or memory usage and should be used with caution in production code.
 * @warning The dynamic class does not perform type safety checks when retrieving values. It is the responsibility of the user to ensure that the correct type is accessed based on the active type flags. Accessing a value with an incorrect type may lead to undefined behavior.
 * @author Ali Lafi
 * @date 2025/9/25
 */

#include <functional>
#include <algorithm>
#include <memory>
#include <vector>
#include <ostream>
#include <cmath>
#include "BFS.hpp"

#include "dynamic/dynamic_f.hpp"
#include "dynamic/dynamic_r.hpp"
#include "dynamic/dynamic_t.hpp"
#include "dynamic/dynamic_u.hpp"
#include "dynamic/dynamic_v.hpp"
#include "dynamic/dynamic_v2d.hpp"
#include "dynamic/dynamic_v3d.hpp"

#pragma once
#ifndef OPENUDT___UDT_DYNAMIC_HPP
#define OPENUDT___UDT_DYNAMIC_HPP

namespace udt
{
    /**
     * @brief A dynamic data type class that can hold and manipulate different standard data types (bool, char, int, float, double).
     * @details This class provides methods to set, get, and perform operations on the stored value, while keeping track of its type.
     * @note This class is designed to work with C++23 standard.
     * @warning This class is not thread-safe.
     */
    class dynamic
    {
    private:
        /* table of the bit flag system:
         * double values will take the flag: 0
         * bool values will take the flag: 1
         * char values will take the flag: 2
         * short values will take the flag: 3
         * int values will take the flag: 4
         * long and long long values will take the flag: 5
         * float values will take the flag: 6
         * long double values will take the flag: 7
         */
        BFS_8 flag;
        double d_double;

    public:
        /**
         * Default constructor for the dynamic type holder.
         *
         * Initializes the object into a well-defined state representing a double value
         * with the following initial values:
         * - d_double: value-initialized (equivalent to 0.0)
         * - dtype: true (indicates the active type is double)
         * - btype, ctype, itype, ftype: false (no other type is active)
         * - bvalue: false (boolean value flag cleared)
         *
         * Use this constructor to obtain a dynamic object that starts as a double with
         * a zero-initialized value and no other active type flags.
         */
        dynamic()
        {
            d_double = double();
            flag.set(0);
        };

        /**
         * Move Constructor
         * @brief Constructs a dynamic object by moving resources from another dynamic object.
         * @param other The dynamic object to move from.
         */
        dynamic(dynamic &&) = default;

        /**
         * @brief Constructs a dynamic object with a boolean value
         *
         * Initializes the dynamic object with a boolean value and sets the internal type flags.
         * The double value is initialized to default, and boolean type flag is set to true
         * while all other type flags are set to false.
         *
         * @param value The boolean value to store
         * @noexcept This constructor does not throw exceptions
         */
        dynamic(bool value) noexcept
        {
            d_double = static_cast<double>(value);
            flag.set(1);
        }

        /**
         * Construct a dynamic object from a character.
         *
         * The character is converted to a double and stored in d_double.
         * The instance is marked as a character type (ctype = true) while all
         * other type flags (btype, itype, ftype, dtype) are cleared. The
         * boolean value flag (bvalue) is also set to false.
         *
         * This constructor does not throw (noexcept).
         *
         * @param value  Character value to initialize the dynamic instance from.
         */
        dynamic(char value) noexcept
        {
            d_double = static_cast<double>(value);
            flag.set(2);
        }

        /**
         * Construct a dynamic object from a short integer.
         * The short value is converted to double and stored in d_double. The instance is marked as an integer type (itype = true) while all other type flags (btype, ctype, ftype, dtype) are cleared. The boolean value flag (bvalue) is also set to false.
         * This constructor is noexcept and does not throw exceptions.
         * @param value The short integer value to initialize the dynamic instance with.
         * @post d_double == static_cast<double>(value)
         * @post itype == true
         * @post btype == false, ctype == false, ftype == false, dtype == false, bvalue == false
         * @note This constructor allows for implicit conversion from short to dynamic, enabling seamless assignment of short values to dynamic objects.
         */
        dynamic(short value) noexcept
        {
            d_double = static_cast<double>(value);
            flag.set(3);
        }

        /**
         * Constructs a dynamic object representing the given integer value.
         *
         * The integer is stored in the internal floating-point storage (d_double)
         * after conversion to double. Type-discriminator flags are updated so that
         * itype becomes true and all other type flags (btype, ctype, ftype, dtype)
         * as well as bvalue are set to false.
         *
         * This constructor is noexcept.
         *
         * @param value The integer value to initialize the dynamic object with.
         */
        dynamic(int value) noexcept
        {
            d_double = static_cast<double>(value);
            flag.set(4);
        }

        /**
         * Constructs a dynamic object from a long integer value.
         * The long value is converted to double and stored in d_double. The instance is marked as an integer type (itype = true) while all other type flags (btype, ctype, ftype, dtype) are cleared. The boolean value flag (bvalue) is also set to false.
         * This constructor is noexcept and does not throw exceptions.
         * @param value The long integer value to initialize the dynamic instance with.
         * @post d_double == static_cast<double>(value)
         * @post itype == true
         * @post btype == false, ctype == false, ftype == false, dtype == false, bvalue == false
         * @note This constructor allows for implicit conversion from long to dynamic, enabling seamless assignment of long values to dynamic objects.
         */
        dynamic(long value) noexcept
        {
            d_double = static_cast<double>(value);
            flag.set(5);
        }

        /**
         * Constructs a dynamic object from a long long integer value.
         * The long long value is converted to double and stored in d_double. The instance is marked as an integer type (itype = true) while all other type flags (btype, ctype, ftype, dtype) are cleared. The boolean value flag (bvalue) is also set to false.
         * This constructor is noexcept and does not throw exceptions.
         * @param value The long long integer value to initialize the dynamic instance with.
         * @post d_double == static_cast<double>(value)
         * @post itype == true
         * @post btype == false, ctype == false, ftype == false, dtype == false, bvalue == false
         * @note This constructor allows for implicit conversion from long long to dynamic, enabling seamless assignment of long long values to dynamic objects.
         */
        dynamic(long long value) noexcept
        {
            d_double = static_cast<double>(value);
            flag.set(5);
        }

        /**
         * @brief Constructs a dynamic object from a float value.
         *
         * Converts the provided float to double and stores it in the internal
         * double representation (d_double). Updates internal type flags to mark
         * this instance as holding a floating-point value and clears other type/value flags.
         *
         * @param value The float value to store (converted to double).
         * @note This constructor is noexcept and does not throw exceptions.
         *
         * @post d_double == static_cast<double>(value)
         * @post ftype == true
         * @post btype == false, ctype == false, itype == false, dtype == false, bvalue == false
         */
        dynamic(float value) noexcept
        {
            d_double = static_cast<double>(value);
            flag.set(6);
        }

        /**
         * @brief Constructs a dynamic object holding a double value.
         *
         * Stores the provided value as a double and updates internal type flags so
         * that the object is treated as a double. All other type flags are cleared.
         *
         * @param value The double value to store.
         * @note This constructor is noexcept and does not throw exceptions.
         */
        dynamic(double value) noexcept
        {
            d_double = static_cast<double>(value);
            flag.set(0);
        }

        /**
         * @brief Copy constructor for dynamic.
         *
         * Constructs a new dynamic object by copying the internal state from another
         * dynamic instance. Scalar/internal type-tag members (d_double, btype,
         * ctype, itype, ftype, dtype) are copied directly. The member bvalue is
         * copied from the source only when both this->dtype and other.dtype are
         * truthy (i.e., both objects indicate a valid/active dtype); otherwise
         * bvalue is left unchanged.
         *
         * This constructor is noexcept and intended to perform a lightweight,
         * non-throwing copy of the object's primitive/stateful fields. It does not
         * perform any additional allocation beyond copying the above members.
         *
         * @param other The dynamic object to copy from.
         */
        dynamic(const dynamic &other) noexcept
        {
            d_double = other.d_double;
            flag = other.flag;
        }

        /**
         * Set the object to represent a boolean value.
         *
         * Stores the provided boolean and updates the internal type indicators so
         * the instance is marked as holding a bool. Specifically, the boolean storage
         * is assigned the given value, the boolean-type flag is set, and all other
         * type flags (character, integer, float, double) are cleared.
         *
         * This function is noexcept and does not throw exceptions.
         *
         * Parameters:
         *   value - the boolean value to store
         */
        void set(bool value) noexcept
        {
            d_double = static_cast<double>(value);
            flag.reset_all();
            flag.set(1);
        }

        /**
         * Set the stored value from a char.
         *
         * Converts the provided character to a double (via static_cast<double>) and stores the result
         * in the internal d_double member. Adjusts internal type flags so the object reflects that
         * a character value is the current active representation.
         *
         * This function is constexpr and noexcept.
         *
         * @param value The character whose numeric code will be stored as a double.
         *
         * Postconditions:
         * - d_double == static_cast<double>(value)
         * - ctype == true
         * - btype == false
         * - itype == false
         * - ftype == false
         * - dtype == false
         * - bvalue == false
         */
        void set(char value) noexcept
        {
            d_double = static_cast<double>(value);
            flag.reset_all();
            flag.set(2);
        }

        /// @brief Sets the value of this Dynamic object to the specified short integer.
        /// @param value The short integer value to set.
        /// @note This operation resets all flags and sets flag bit 3, indicating the value is of short type.
        /// @remarks The short value is internally stored as a double for uniform representation.
        void set(short value) noexcept
        {
            d_double = static_cast<double>(value);
            flag.reset_all();
            flag.set(3);
        }

        /**
         * Set the stored value to the provided integer.
         *
         * Converts the integer to the internal double representation and updates the
         * internal type flags so the object represents an integer:
         *  - itype is set to true
         *  - btype, ctype, ftype, dtype and bvalue are set to false
         *
         * @param value The integer value to store (converted to double internally).
         *
         * Notes:
         * - This function is constexpr and noexcept; it can be evaluated at compile
         *   time when used in a constant expression and will not throw.
         * - Complexity: O(1).
         */
        void set(int value) noexcept
        {
            d_double = static_cast<double>(value);
            flag.reset_all();
            flag.set(4);
        }

        /// Sets the internal double value from a long integer.
        ///
        /// Converts the provided long integer value to a double and stores it.
        /// Resets all flags and then sets flag at position 5.
        ///
        /// @param value The long integer value to convert and store as a double
        /// @note This operation is noexcept and does not throw exceptions
        void set(long value) noexcept
        {
            d_double = static_cast<double>(value);
            flag.reset_all();
            flag.set(5);
        }

        /// Sets the value from a signed 64-bit integer.
        ///
        /// Converts the provided long long value to a double and stores it.
        /// Resets all flags and then sets flag bit 5 to indicate the value type.
        ///
        /// @param value The signed 64-bit integer value to set
        /// @note This operation is noexcept and does not throw exceptions
        void set(long long value) noexcept
        {
            d_double = static_cast<double>(value);
            flag.reset_all();
            flag.set(5);
        }

        /**
         * Set the stored value from a float.
         *
         * Converts the given float to double and stores it in the internal double
         * storage. Updates the internal type-tracking flags so that the float-type
         * flag is true and all other type flags are false.
         *
         * This operation is guaranteed not to throw (noexcept).
         *
         * @param value The float value to store (converted to double internally).
         */
        void set(float value) noexcept
        {
            d_double = static_cast<double>(value);
            flag.reset_all();
            flag.set(6);
        }

        /**
         * @brief Store a double value and mark this object as holding a double.
         *
         * constexpr noexcept function that assigns the provided value to the internal
         * double storage and updates the internal type flags so the object represents
         * a double value. All other type indicators are cleared.
         *
         * @param value The value to store (converted via static_cast<double>).
         *
         * Effects:
         *  - The internal double storage is set to the provided value.
         *  - dtype is set to true.
         *  - btype, ctype, itype, ftype and bvalue are set to false.
         *
         * @note This function does not throw and is evaluated at compile time when
         *       used in a constexpr context. Concurrent access is not synchronized and
         *       must be managed by the caller.
         */
        void set(double value) noexcept
        {
            d_double = value;
            flag.reset_all();
            flag.set(0);
        }

        /// @brief Sets the value as a long double and resets all flags except flag 7.
        /// @param value The long double value to set.
        /// @note This operation resets all flags and then sets flag 7, indicating the value is a double type.
        /// @noexcept This function does not throw exceptions.
        void set(long double value) noexcept
        {
            d_double = value;
            flag.reset_all();
            flag.set(7);
        }

        /**
         * @brief Sets the values of the current object using values from another dynamic object.
         *
         * This member function copies all member values from the provided dynamic object
         * to the current object.
         *
         * @param other The source dynamic object whose values will be copied.
         * @noexcept This function does not throw exceptions.
         */
        constexpr void set(const dynamic &other) noexcept
        {
            d_double = other.d_double;
            flag = other.flag;
        }

        /**
         * @brief Retrieves the stored boolean value.
         * @return The stored boolean value.
         * @note This function assumes that the current type is boolean; behavior is undefined otherwise.
         */
        constexpr bool get_bool() noexcept { return static_cast<bool>(d_double); }

        /**
         * @brief Retrieves the stored character value.
         * @return The stored character value.
         * @note This function assumes that the current type is character; behavior is undefined otherwise.
         */
        constexpr char get_char() noexcept { return static_cast<char>(d_double); }

        /**
         * @brief Retrieves the stored integer value.
         * @return The stored integer value.
         * @note This function assumes that the current type is integer; behavior is undefined otherwise.
         */
        constexpr int get_int() noexcept { return static_cast<int>(d_double); }

        /**
         * @brief Retrieves the stored float value.
         * @return The stored float value.
         * @note This function assumes that the current type is float; behavior is undefined otherwise.
         */
        constexpr float get_float() noexcept { return static_cast<float>(d_double); }

        /**
         * @brief Retrieves the stored double value.
         * @return The stored double value.
         * @note This function assumes that the current type is double; behavior is undefined otherwise.
         */
        constexpr double get_double() noexcept { return static_cast<double>(d_double); }

        /**
         * @brief Returns a reference to the current dynamic object.
         * @return A reference to the current dynamic object.
         * @note This function does not throw exceptions.
         */
        dynamic &get() noexcept { return *this; }

        /**
         * @brief Resets the dynamic object to its default state.
         *
         * This function clears all stored values and type flags, setting the object
         * back to its initial state as if it were newly constructed.
         *
         * @noexcept This function does not throw exceptions.
         */
        void reset() noexcept
        {
            d_double = double();
            flag.reset_all();
        }

        /**
         * @brief Checks if the stored value is of boolean type.
         */
        bool is_bool() noexcept { return flag[1]; }

        /**
         * @brief Checks if the stored value is of character type.
         */
        bool is_char() noexcept { return flag[2]; }

        /**
         * @brief Checks if the stored value is of short integer type.
         */
        bool is_short() noexcept { return flag[3]; }

        /**
         * @brief Checks if the stored value is of integer type.
         */
        bool is_int() noexcept { return flag[4]; }

        /**
         * @brief Checks if the stored value is of long integer type.
         */
        bool is_long() noexcept { return flag[5]; }

        /**
         * @brief Checks if the stored value is of float type.
         */
        bool is_float() noexcept { return flag[6]; }

        /**
         * @brief Checks if the stored value is of double type.
         */
        bool is_double() noexcept { return flag[0]; }

        /**
         * @brief Return a textual representation of the currently selected type.
         *
         * Inspects the internal boolean flags in the following priority order:
         *   1. btype  -> "bool"
         *   2. ctype  -> "char"
         *   3. itype  -> "int"
         *   4. ftype  -> "float"
         *   5. dtype  -> "double"
         *
         * If none of the flags are set, the function returns the sentinel string "***".
         *
         * Notes:
         * - The function is noexcept and will not throw exceptions.
         * - It does not modify object state (observational only).
         * - If multiple flags are true, the highest-priority flag listed above determines the result.
         *
         * @return std::string A string naming the active type ("bool", "char", "int", "float", "double")
         *         or "***" when no type flag is set.
         */
        std::string type() noexcept
        {
            if (flag[1])
                return "bool";
            else if (flag[2])
                return "char";
            else if (flag[3])
                return "short";
            else if (flag[4])
                return "int";
            else if (flag[5])
                return "long";
            else if (flag[6])
                return "float";
            else if (flag[0])
                return "double";
            else if (flag[7])
                return "long double";
            else
                return "***";
        }

        /**
         * @brief Assignment operator for dynamic.
         * @param value The boolean value to assign.
         * @note noexcept This operator does not throw exceptions.
         */
        void operator=(bool value) noexcept { set(value); }

        /**
         * @brief Assignment operator for dynamic.
         * @param value The character value to assign.
         * @note noexcept This operator does not throw exceptions.
         */
        void operator=(char value) noexcept { set(value); }

        /**
         * @brief Assignment operator for dynamic.
         * @param value The short integer value to assign.
         * @note noexcept This operator does not throw exceptions.
         */
        void operator=(short value) noexcept { set(value); }

        /**
         * @brief Assignment operator for dynamic.
         * @param value The integer value to assign.
         * @note noexcept This operator does not throw exceptions.
         */
        void operator=(int value) noexcept { set(value); }

        /**
         * @brief Assignment operator for dynamic.
         * @param value The long integer value to assign.
         * @note noexcept This operator does not throw exceptions.
         */
        void operator=(long value) noexcept { set(value); }

        /**
         * @brief Assignment operator for dynamic.
         * @param value The long long integer value to assign.
         * @note noexcept This operator does not throw exceptions.
         */
        void operator=(long long value) noexcept { set(value); }

        /**
         * @brief Assignment operator for dynamic.
         * @param value The float value to assign.
         * @note noexcept This operator does not throw exceptions.
         */
        void operator=(float value) noexcept { set(value); }

        /**
         * @brief Assignment operator for dynamic.
         * @param value The double value to assign.
         * @note noexcept This operator does not throw exceptions.
         */
        void operator=(double value) noexcept { set(value); }

        /**
         * @brief Assignment operator for dynamic.
         * @param value The long double value to assign.
         * @note noexcept This operator does not throw exceptions.
         */
        void operator=(long double value) noexcept { set(value); }

        /**
         * @brief Assignment operator for dynamic.
         * @param other The dynamic object to assign from.
         * @note noexcept This operator does not throw exceptions.
         */
        dynamic &operator=(dynamic &&) = default;

        /**
         * Copy-assigns the value and internal state from another dynamic.
         *
         * This constexpr, noexcept assignment operator copies all internal representation
         * members from the source object into this object:
         *  - d_double: numeric double storage
         *  - btype, ctype, itype, ftype, dtype: internal type/tag fields
         *  - bvalue: boolean/union storage value
         *
         * The operation performs a direct member-wise copy of the stored state and
         * returns a reference to *this. It is safe for use in constexpr contexts and
         * promises not to throw exceptions.
         *
         * @param other The dynamic instance to copy from.
         * @return Reference to this dynamic after assignment.
         */
        constexpr dynamic &operator=(const dynamic &other) noexcept
        {
            d_double = other.d_double;
            flag = other.flag;
            return *this;
        }

        /**
         * @brief Equality operator for dynamic.
         * @param value The boolean value to compare.
         * @return True if equal, false otherwise.
         */
        bool operator==(bool value) const noexcept
        {
            if (flag[1])
                return static_cast<bool>(d_double) == value;
            else
                return false;
        }

        /**
         * @brief Equality operator for dynamic.
         * @param value The character value to compare.
         * @return True if equal, false otherwise.
         */
        bool operator==(char value) const noexcept
        {
            if (flag[2])
                return static_cast<char>(d_double) == value;
            else
                return false;
        }

        /**
         * @brief Equality operator for dynamic.
         * @param value The short integer value to compare.
         * @return True if equal, false otherwise.
         * @note This operator checks if the current dynamic object holds a short integer value (indicated by flag[3]) and compares it to the provided short value. If the flag is not set, it returns false, indicating that the types are not compatible for comparison.
         */
        bool operator==(short value) const noexcept
        {
            if (flag[3])
                return static_cast<short>(d_double) == value;
            else
                return false;
        }

        /**
         * @brief Equality operator for dynamic.
         * @param value The integer value to compare.
         * @return True if equal, false otherwise.
         */
        bool operator==(int value) const noexcept
        {
            if (flag[4])
                return static_cast<int>(d_double) == value;
            else
                return false;
        }

        /**
         * @brief Equality operator for dynamic.
         * @param value The long integer value to compare.
         * @return True if equal, false otherwise.
         * @note This operator checks if the current dynamic object holds a long integer value (indicated by flag[5]) and compares it to the provided long value. If the flag is not set, it returns false, indicating that the types are not compatible for comparison.
         */
        bool operator==(long value) const noexcept
        {
            if (flag[5])
                return static_cast<long>(d_double) == value;
            else
                return false;
        }

        /**
         * @brief Equality operator for dynamic.
         * @param value The long long integer value to compare.
         * @return True if equal, false otherwise.
         * @note This operator checks if the current dynamic object holds a long long integer value (indicated by flag[5]) and compares it to the provided long long value. If the flag is not set, it returns false, indicating that the types are not compatible for comparison.
         */
        bool operator==(long long value) const noexcept
        {
            if (flag[5])
                return static_cast<long>(d_double) == value;
            else
                return false;
        }

        /**
         * @brief Equality operator for dynamic.
         * @param value The float value to compare.
         * @return True if equal, false otherwise.
         */
        bool operator==(float value) const noexcept
        {
            if (flag[6])
                return static_cast<float>(d_double) == value;
            else
                return false;
        }

        /**
         * @brief Equality operator for dynamic.
         * @param value The double value to compare.
         * @return True if equal, false otherwise.
         */
        bool operator==(double value) const noexcept
        {
            if (flag[0])
                return d_double == value;
            else
                return false;
        }

        /**
         * @brief Equality operator for dynamic.
         * @param value The long double value to compare.
         * @return True if equal, false otherwise.
         * @note This operator checks if the current dynamic object holds a long double value (indicated by flag[7]) and compares it to the provided long double value. If the flag is not set, it returns false, indicating that the types are not compatible for comparison.
         */
        bool operator==(long double value) const noexcept
        {
            if (flag[7])
                return d_double == value;
            else
                return false;
        }

        /**
         * @brief Equality operator for dynamic.
         * @param other The dynamic instance to compare with.
         * @return True if equal, false otherwise.
         */
        constexpr bool operator==(const dynamic &other) const noexcept
        {
            return d_double == other.d_double && flag == other.flag;
        }

        /**
         * @brief Inequality operator for dynamic.
         * @param value The boolean value to compare.
         * @return True if not equal, false otherwise.
         */
        bool operator!=(bool value) const noexcept
        {
            if (flag[1])
                return static_cast<bool>(d_double) != value;
            else
                return false;
        }

        /**
         * @brief Inequality operator for dynamic.
         * @param value The character value to compare.
         * @return True if not equal, false otherwise.
         */
        bool operator!=(char value) const noexcept
        {
            if (flag[2])
                return static_cast<char>(d_double) != value;
            else
                return false;
        }

        /**
         * @brief Inequality operator for dynamic.
         * @param value The short integer value to compare.
         * @return True if not equal, false otherwise.
         * @note This operator checks if the current dynamic object holds a short integer value (indicated by flag[3]) and compares it to the provided short value. If the flag is not set, it returns false, indicating that the types are not compatible for comparison.
         */
        bool operator!=(short value) const noexcept
        {
            if (flag[3])
                return static_cast<short>(d_double) != value;
            else
                return false;
        }

        /**
         * @brief Inequality operator for dynamic.
         * @param value The integer value to compare.
         * @return True if not equal, false otherwise.
         */
        bool operator!=(int value) const noexcept
        {
            if (flag[4])
                return static_cast<int>(d_double) != value;
            else
                return false;
        }

        /**
         * @brief Inequality operator for dynamic.
         * @param value The long integer value to compare.
         * @return True if not equal, false otherwise.
         * @note This operator checks if the current dynamic object holds a long integer value (indicated by flag[5]) and compares it to the provided long value. If the flag is not set, it returns false, indicating that the types are not compatible for comparison.
         */
        bool operator!=(long value) const noexcept
        {
            if (flag[5])
                return static_cast<long>(d_double) != value;
            else
                return false;
        }

        /**
         * @brief Inequality operator for dynamic.
         * @param value The long long integer value to compare.
         * @return True if not equal, false otherwise.
         * @note This operator checks if the current dynamic object holds a long long integer value (indicated by flag[5]) and compares it to the provided long long value. If the flag is not set, it returns false, indicating that the types are not compatible for comparison.
         */
        bool operator!=(long long value) const noexcept
        {
            if (flag[5])
                return static_cast<long long>(d_double) != value;
            else
                return false;
        }

        /**
         * @brief Inequality operator for dynamic.
         * @param value The float value to compare.
         * @return True if not equal, false otherwise.
         */
        bool operator!=(float value) const noexcept
        {
            if (flag[6])
                return static_cast<float>(d_double) != value;
            else
                return false;
        }

        /**
         * @brief Inequality operator for dynamic.
         * @param value The double value to compare.
         * @return True if not equal, false otherwise.
         */
        bool operator!=(double value) const noexcept
        {
            if (flag[0])
                return static_cast<double>(d_double) != value;
            else
                return false;
        }

        /**
         * @brief Inequality operator for dynamic.
         * @param value The long double value to compare.
         * @return True if not equal, false otherwise.
         * @note This operator checks if the current dynamic object holds a long double value (indicated by flag[7]) and compares it to the provided long double value. If the flag is not set, it returns false, indicating that the types are not compatible for comparison.
         */
        bool operator!=(long double value) const noexcept
        {
            if (flag[7])
                return static_cast<long double>(d_double) != value;
            else
                return false;
        }

        /**
         * @brief Inequality operator for dynamic.
         * @param other The dynamic instance to compare with.
         * @return True if not equal, false otherwise.
         */
        constexpr bool operator!=(const dynamic &other) const noexcept
        {
            return d_double != other.d_double && flag != other.flag;
        }

        /**
         * @brief Greater-than operator for dynamic.
         * @param c The character value to compare.
         * @return True if greater, false otherwise.
         */
        bool operator>(char c) const noexcept
        {
            if (flag[2])
                return static_cast<char>(d_double) > c;
            else
                return false;
        }

        /// @brief Compares if the dynamic value is greater than a short integer.
        /// @param value The short integer value to compare against.
        /// @return true if the dynamic value (when valid) is greater than the provided short value; false otherwise.
        /// @note Returns false if the dynamic value flag is not set (flag[3] is false), indicating an invalid or uninitialized state.
        bool operator>(short value) const noexcept
        {
            if (flag[3])
                return static_cast<short>(d_double) > value;
            else
                return false;
        }

        /**
         * @brief Greater-than operator for dynamic.
         * @param value The integer value to compare.
         * @return True if greater, false otherwise.
         */
        bool operator>(int value) const noexcept
        {
            if (flag[4])
                return static_cast<int>(d_double) > value;
            else
                return false;
        }

        /**
         * @brief Greater-than operator for dynamic.
         * @param value The long integer value to compare.
         * @return True if greater, false otherwise.
         * @note This operator checks if the current dynamic object holds a long integer value (indicated by flag[5]) and compares it to the provided long value. If the flag is not set, it returns false, indicating that the types are not compatible for comparison.
         */
        bool operator>(long value) const noexcept
        {
            if (flag[5])
                return static_cast<long>(d_double) > value;
            else
                return false;
        }

        /**
         * @brief Greater-than operator for dynamic.
         * @param value The long long integer value to compare.
         * @return True if greater, false otherwise.
         * @note This operator checks if the current dynamic object holds a long long integer value (indicated by flag[5]) and compares it to the provided long long value. If the flag is not set, it returns false, indicating that the types are not compatible for comparison.
         */
        bool operator>(long long value) const noexcept
        {
            if (flag[5])
                return static_cast<long long>(d_double) > value;
            else
                return false;
        }

        /**
         * @brief Greater-than operator for dynamic.
         * @param value The float value to compare.
         * @return True if greater, false otherwise.
         */
        bool operator>(float value) const noexcept
        {
            if (flag[6])
                return static_cast<float>(d_double) > value;
            else
                return false;
        }

        /**
         * @brief Greater-than operator for dynamic.
         * @param value The double value to compare.
         * @return True if greater, false otherwise.
         */
        bool operator>(double value) const noexcept
        {
            if (flag[0])
                return static_cast<int>(d_double) > value;
            else
                return false;
        }

        /**
         * @brief Greater-than-or-equal operator for dynamic.
         * @param c The character value to compare.
         * @return True if greater or equal, false otherwise.
         */
        constexpr bool operator>=(char c) const noexcept { return static_cast<char>(d_double) >= c; }

        /**
         * @brief Greater-than-or-equal operator for dynamic.
         * @param value The integer value to compare.
         * @return True if greater or equal, false otherwise.
         */
        constexpr bool operator>=(int value) const noexcept { return static_cast<int>(d_double) >= value; }

        /**
         * @brief Greater-than-or-equal operator for dynamic.
         * @param value The float value to compare.
         * @return True if greater or equal, false otherwise.
         */
        constexpr bool operator>=(float value) const noexcept { return static_cast<float>(d_double) >= value; }

        /**
         * @brief Greater-than-or-equal operator for dynamic.
         * @param value The double value to compare.
         * @return True if greater or equal, false otherwise.
         */
        constexpr bool operator>=(double value) const noexcept { return d_double >= value; }

        /**
         * @brief Less-than operator for dynamic.
         * @param c The character value to compare.
         * @return True if less, false otherwise.
         */
        constexpr bool operator<(char c) const noexcept { return static_cast<char>(d_double) < c; }

        /**
         * @brief Less-than operator for dynamic.
         * @param value The integer value to compare.
         * @return True if less, false otherwise.
         */
        constexpr bool operator<(int value) const noexcept { return static_cast<int>(d_double) < value; }

        /**
         * @brief Less-than operator for dynamic.
         * @param value The float value to compare.
         * @return True if less, false otherwise.
         */
        constexpr bool operator<(float value) const noexcept { return static_cast<float>(d_double) < value; }

        /**
         * @brief Less-than operator for dynamic.
         * @param value The double value to compare.
         * @return True if less, false otherwise.
         */
        constexpr bool operator<(double value) const noexcept { return d_double < value; }

        /**
         * @brief Less-than-or-equal operator for dynamic.
         * @param c The character value to compare.
         * @return True if less or equal, false otherwise.
         */
        constexpr bool operator<=(char c) const noexcept { return static_cast<char>(d_double) <= c; }

        /**
         * @brief Less-than-or-equal operator for dynamic.
         * @param value The integer value to compare.
         * @return True if less or equal, false otherwise.
         */
        constexpr bool operator<=(int value) const noexcept { return static_cast<int>(d_double) <= value; }

        /**
         * @brief Less-than-or-equal operator for dynamic.
         * @param value The float value to compare.
         * @return True if less or equal, false otherwise.
         */
        constexpr bool operator<=(float value) const noexcept { return static_cast<float>(d_double) <= value; }

        /**
         * @brief Less-than-or-equal operator for dynamic.
         * @param value The double value to compare.
         * @return True if less or equal, false otherwise.
         */
        constexpr bool operator<=(double value) const noexcept { return d_double <= value; }

        /**
         * @brief Pre-increment operator for dynamic.
         * Increments the stored double value by 1.
         * @note noexcept This operator does not throw exceptions.
         */
        constexpr void operator++() noexcept { ++d_double; }

        /**
         * @brief Pre-decrement operator for dynamic.
         * Decrements the stored double value by 1.
         * @note noexcept This operator does not throw exceptions.
         */
        constexpr void operator--() noexcept { --d_double; }

        /**
         * @brief Logical AND operator for dynamic.
         * @param value The boolean value to AND with.
         * @return The result of the logical AND operation.
         * @throws std::invalid_argument if the current type is not boolean.
         */
        bool operator&&(bool value)
        {
            if (flag[1])
                return static_cast<bool>(d_double) && value;
            else
                throw std::invalid_argument("no boolean value has been set");
        }

        /**
         * @brief Logical OR operator for dynamic.
         * @param value The boolean value to OR with.
         * @return The result of the logical OR operation.
         * @throws std::invalid_argument if the current type is not boolean.
         */
        bool operator||(bool value)
        {
            if (flag[1])
                return static_cast<bool>(d_double) || value;
            else
                throw std::invalid_argument("no boolean value has been set");
        }

        /**
         * @brief Logical XOR operator for dynamic.
         * @param value The boolean value to XOR with.
         * @return The result of the logical XOR operation.
         * @throws std::invalid_argument if the current type is not boolean.
         */
        bool operator^(bool value)
        {
            if (flag[1])
                return static_cast<bool>(d_double) ^ value;
            else
                throw std::invalid_argument("no boolean value has been set");
        }

        /**
         * @brief Logical NOT operator for dynamic.
         * @return The result of the logical NOT operation.
         * @throws std::invalid_argument if the current type is not boolean.
         */
        bool operator!()
        {
            if (flag[1])
                return !static_cast<bool>(d_double);
            else
                throw std::invalid_argument("no boolean value has been set");
        }

        /**
         * @brief Logical AND assignment operator for dynamic.
         * @param value The boolean value to AND with.
         * @throws std::invalid_argument if the current type is not boolean.
         */
        void operator&=(bool value)
        {
            bool temp = static_cast<bool>(d_double);
            if (flag[1])
            {
                temp &= value;
                set(temp);
            }
            else
                throw std::invalid_argument("no boolean value has been set");
        }

        /**
         * @brief Logical OR assignment operator for dynamic.
         * @param value The boolean value to OR with.
         * @throws std::invalid_argument if the current type is not boolean.
         */
        void operator|=(bool value)
        {
            bool temp = static_cast<bool>(d_double);
            if (flag[1])
            {
                temp |= value;
                set(temp);
            }
            else
                throw std::invalid_argument("no boolean value has been set");
        }

        /**
         * @brief Logical XOR assignment operator for dynamic.
         * @param value The boolean value to XOR with.
         * @throws std::invalid_argument if the current type is not boolean.
         */
        constexpr void operator+=(char value) noexcept { d_double += value; }

        /**
         * @brief Addition assignment operator for dynamic.
         * @param value The integer value to add.
         */
        constexpr void operator+=(int value) noexcept { d_double += value; }

        /**
         * @brief Addition assignment operator for dynamic.
         * @param value The float value to add.
         */
        constexpr void operator+=(float value) noexcept { d_double += value; }

        /**
         * @brief Addition assignment operator for dynamic.
         * @param value The double value to add.
         */
        constexpr void operator+=(double value) noexcept { d_double += value; }

        /**
         * @brief Addition assignment operator for dynamic.
         * @param other The dynamic object to add.
         */
        constexpr void operator+=(const dynamic &other) noexcept { d_double += other.d_double; }

        /**
         * @brief Subtraction assignment operator for dynamic.
         * @param value The character value to subtract.
         */
        constexpr void operator-=(char value) noexcept { d_double -= value; }

        /**
         * @brief Subtraction assignment operator for dynamic.
         * @param value The integer value to subtract.
         */
        constexpr void operator-=(int value) noexcept { d_double -= value; }

        /**
         * @brief Subtraction assignment operator for dynamic.
         * @param value The float value to subtract.
         */
        constexpr void operator-=(float value) noexcept { d_double -= value; }

        /**
         * @brief Subtraction assignment operator for dynamic.
         * @param value The double value to subtract.
         */
        constexpr void operator-=(double value) noexcept { d_double -= value; }

        /**
         * @brief Subtraction assignment operator for dynamic.
         * @param other The dynamic object to subtract.
         */
        constexpr void operator-=(const dynamic &other) noexcept { d_double -= other.d_double; }

        /**
         * @brief Multiplication assignment operator for dynamic.
         * @param value The character value to multiply.
         */
        constexpr void operator*=(char value) noexcept { d_double *= value; }

        /**
         * @brief Multiplication assignment operator for dynamic.
         * @param value The integer value to multiply.
         */
        constexpr void operator*=(int value) noexcept { d_double *= value; }

        /**
         * @brief Multiplication assignment operator for dynamic.
         * @param value The float value to multiply.
         */
        constexpr void operator*=(float value) noexcept { d_double *= value; }

        /**
         * @brief Multiplication assignment operator for dynamic.
         * @param value The double value to multiply.
         */
        constexpr void operator*=(double value) noexcept { d_double *= value; }

        /**
         * @brief Multiplication assignment operator for dynamic.
         * @param other The dynamic object to multiply.
         */
        constexpr void operator*=(const dynamic &other) noexcept { d_double *= other.d_double; }

        /**
         * @brief Division assignment operator for dynamic.
         * @param value The character value to divide.
         */
        constexpr void operator/=(char value) noexcept { d_double /= value; }

        /**
         * @brief Division assignment operator for dynamic.
         * @param value The integer value to divide.
         */
        constexpr void operator/=(int value) noexcept { d_double /= value; }

        /**
         * @brief Division assignment operator for dynamic.
         * @param value The float value to divide.
         */
        constexpr void operator/=(float value) noexcept { d_double /= value; }

        /**
         * @brief Division assignment operator for dynamic.
         * @param value The double value to divide.
         */
        constexpr void operator/=(double value) noexcept { d_double /= value; }

        /**
         * @brief Division assignment operator for dynamic.
         * @param other The dynamic object to divide.
         */
        constexpr void operator/=(const dynamic &other) noexcept { d_double /= other.d_double; }

        /**
         * @brief Exponentiation assignment operator for dynamic.
         * @param value The character exponent value.
         */
        constexpr void operator^=(char value) noexcept { d_double = std::pow(d_double, value); }

        /**
         * @brief Exponentiation assignment operator for dynamic.
         * @param value The integer exponent value.
         */
        constexpr void operator^=(int value) noexcept { d_double = std::pow(d_double, value); }

        /**
         * @brief Exponentiation assignment operator for dynamic.
         * @param value The float exponent value.
         */
        constexpr void operator^=(float value) noexcept { d_double = std::pow(d_double, value); }

        /**
         * @brief Exponentiation assignment operator for dynamic.
         * @param value The double exponent value.
         */
        constexpr void operator^=(double value) noexcept { d_double = std::pow(d_double, value); }
    };

    // Implementation of dynamic class member functions
    void dynamic::set(bool value) noexcept
    {
        d_double = static_cast<double>(value);
        flag.reset_all();
        flag.set(1);
    }
    void dynamic::set(char value) noexcept
    {
        d_double = static_cast<double>(value);
        flag.reset_all();
        flag.set(2);
    }

    void dynamic::set(short value) noexcept
    {
        d_double = static_cast<double>(value);
        flag.reset_all();
        flag.set(3);
    }

    void dynamic::set(int value) noexcept
    {
        d_double = static_cast<double>(value);
        flag.reset_all();
        flag.set(4);
    }

    void dynamic::set(long value) noexcept
    {
        d_double = static_cast<double>(value);
        flag.reset_all();
        flag.set(5);
    }

    void dynamic::set(long long value) noexcept
    {
        d_double = static_cast<double>(value);
        flag.reset_all();
        flag.set(5);
    }

    void dynamic::set(float value) noexcept
    {
        d_double = static_cast<double>(value);
        flag.reset_all();
        flag.set(6);
    }

    void dynamic::set(double value) noexcept
    {
        d_double = value;
        flag.reset_all();
        flag.set(0);
    }

    void dynamic::set(long double value) noexcept
    {
        d_double = value;
        flag.reset_all();
        flag.set(7);
    }

    constexpr void dynamic::set(const dynamic &other) noexcept
    {
        d_double = other.d_double;
        flag = other.flag;
    }

    constexpr bool dynamic::get_bool() noexcept { return static_cast<bool>(d_double); }

    constexpr char dynamic::get_char() noexcept { return static_cast<char>(d_double); }

    constexpr int dynamic::get_int() noexcept { return static_cast<int>(d_double); }

    constexpr float dynamic::get_float() noexcept { return static_cast<float>(d_double); }

    constexpr double dynamic::get_double() noexcept { return static_cast<double>(d_double); }

    dynamic &dynamic::get() noexcept { return *this; }

    void dynamic::reset() noexcept
    {
        d_double = double();
        flag.reset_all();
    }

    bool dynamic::is_bool() noexcept { return flag[1]; }

    bool dynamic::is_char() noexcept { return flag[2]; }

    bool dynamic::is_short() noexcept { return flag[3]; }

    bool dynamic::is_int() noexcept { return flag[4]; }

    bool dynamic::is_long() noexcept { return flag[5]; }

    bool dynamic::is_float() noexcept { return flag[6]; }

    bool dynamic::is_double() noexcept { return flag[0]; }

    std::string dynamic::type() noexcept
    {
        if (flag[1])
            return "bool";
        else if (flag[2])
            return "char";
        else if (flag[3])
            return "short";
        else if (flag[4])
            return "int";
        else if (flag[5])
            return "long";
        else if (flag[6])
            return "float";
        else if (flag[0])
            return "double";
        else if (flag[7])
            return "long double";
        else
            return "***";
    }

    void dynamic::operator=(bool value) noexcept { set(value); }

    void dynamic::operator=(char value) noexcept { set(value); }

    void dynamic::operator=(short value) noexcept { set(value); }

    void dynamic::operator=(int value) noexcept { set(value); }

    void dynamic::operator=(long value) noexcept { set(value); }

    void dynamic::operator=(long long value) noexcept { set(value); }

    void dynamic::operator=(float value) noexcept { set(value); }

    void dynamic::operator=(double value) noexcept { set(value); }

    void dynamic::operator=(long double value) noexcept { set(value); }

    dynamic &dynamic::operator=(dynamic &&) = default;

    constexpr dynamic &dynamic::operator=(const dynamic &other) noexcept
    {
        d_double = other.d_double;
        flag = other.flag;
        return *this;
    }

    bool dynamic::operator==(bool value) const noexcept
    {
        if (flag[1])
            return static_cast<bool>(d_double) == value;
        else
            return false;
    }

    bool dynamic::operator==(char value) const noexcept
    {
        if (flag[2])
            return static_cast<char>(d_double) == value;
        else
            return false;
    }

    bool dynamic::operator==(short value) const noexcept
    {
        if (flag[3])
            return static_cast<short>(d_double) == value;
        else
            return false;
    }

    bool dynamic::operator==(int value) const noexcept
    {
        if (flag[4])
            return static_cast<int>(d_double) == value;
        else
            return false;
    }

    bool dynamic::operator==(long value) const noexcept
    {
        if (flag[5])
            return static_cast<long>(d_double) == value;
        else
            return false;
    }

    bool dynamic::operator==(long long value) const noexcept
    {
        if (flag[5])
            return static_cast<long long>(d_double) == value;
        else
            return false;
    }

    bool dynamic::operator==(float value) const noexcept
    {
        if (flag[6])
            return static_cast<float>(d_double) == value;
        else
            return false;
    }

    bool dynamic::operator==(double value) const noexcept
    {
        if (flag[0])
            return d_double == value;
        else
            return false;
    }

    bool dynamic::operator==(long double value) const noexcept
    {
        if (flag[7])
            return d_double == value;
        else
            return false;
    }

    constexpr bool dynamic::operator==(const dynamic &other) const noexcept
    {
        return d_double == other.d_double && flag == other.flag;
    }

    bool dynamic::operator!=(bool value) const noexcept
    {
        if (flag[1])
            return static_cast<bool>(d_double) != value;
        else
            return false;
    }

    bool dynamic::operator!=(char value) const noexcept
    {
        if (flag[2])
            return static_cast<char>(d_double) != value;
        else
            return false;
    }

    bool dynamic::operator!=(short value) const noexcept
    {
        if (flag[3])
            return static_cast<short>(d_double) != value;
        else
            return false;
    }

    bool dynamic::operator!=(int value) const noexcept
    {
        if (flag[4])
            return static_cast<int>(d_double) != value;
        else
            return false;
    }

    bool dynamic::operator!=(long value) const noexcept
    {
        if (flag[5])
            return static_cast<long>(d_double) != value;
        else
            return false;
    }

    bool dynamic::operator!=(long long value) const noexcept
    {
        if (flag[5])
            return static_cast<long long>(d_double) != value;
        else
            return false;
    }

    bool dynamic::operator!=(float value) const noexcept
    {
        if (flag[6])
            return static_cast<float>(d_double) != value;
        else
            return false;
    }

    bool dynamic::operator!=(double value) const noexcept
    {
        if (flag[0])
            return static_cast<double>(d_double) != value;
        else
            return false;
    }

    bool dynamic::operator!=(long double value) const noexcept
    {
        if (flag[7])
            return static_cast<long double>(d_double) != value;
        else
            return false;
    }

    constexpr bool dynamic::operator!=(const dynamic &other) const noexcept
    {
        return d_double != other.d_double && flag != other.flag;
    }

    bool dynamic::operator>(char c) const noexcept
    {
        if (flag[2])
            return static_cast<char>(d_double) > c;
        else
            return false;
    }

    bool dynamic::operator>(short value) const noexcept
    {
        if (flag[3])
            return static_cast<short>(d_double) > value;
        else
            return false;
    }

    bool dynamic::operator>(int value) const noexcept
    {
        if (flag[4])
            return static_cast<int>(d_double) > value;
        else
            return false;
    }

    bool dynamic::operator>(long value) const noexcept
    {
        if (flag[5])
            return static_cast<long>(d_double) > value;
        else
            return false;
    }

    bool dynamic::operator>(long long value) const noexcept
    {
        if (flag[5])
            return static_cast<long long>(d_double) > value;
        else
            return false;
    }

    bool dynamic::operator>(float value) const noexcept
    {
        if (flag[6])
            return static_cast<float>(d_double) > value;
        else
            return false;
    }

    bool dynamic::operator>(double value) const noexcept
    {
        if (flag[0])
            return static_cast<double>(d_double) > value;
        else
            return false;
    }

    constexpr bool dynamic::operator>=(char c) const noexcept { return static_cast<char>(d_double) >= c; }

    constexpr bool dynamic::operator>=(int value) const noexcept { return static_cast<int>(d_double) >= value; }

    constexpr bool dynamic::operator>=(float value) const noexcept { return static_cast<float>(d_double) >= value; }

    constexpr bool dynamic::operator>=(double value) const noexcept { return d_double >= value; }

    constexpr bool dynamic::operator<(char c) const noexcept { return static_cast<char>(d_double) < c; }

    constexpr bool dynamic::operator<(int value) const noexcept { return static_cast<int>(d_double) < value; }

    constexpr bool dynamic::operator<(float value) const noexcept { return static_cast<float>(d_double) < value; }

    constexpr bool dynamic::operator<(double value) const noexcept { return d_double < value; }

    constexpr bool dynamic::operator<=(char c) const noexcept { return static_cast<char>(d_double) <= c; }

    constexpr bool dynamic::operator<=(int value) const noexcept { return static_cast<int>(d_double) <= value; }

    constexpr bool dynamic::operator<=(float value) const noexcept { return static_cast<float>(d_double) <= value; }

    constexpr bool dynamic::operator<=(double value) const noexcept { return d_double <= value; }

    constexpr void dynamic::operator++() noexcept { ++d_double; }

    constexpr void dynamic::operator--() noexcept { --d_double; }

    bool dynamic::operator&&(bool value)
    {
        if (flag[1])
            return static_cast<bool>(d_double) && value;
        else
            throw std::invalid_argument("no boolean value has been set");
    }

    bool dynamic::operator||(bool value)
    {
        if (flag[1])
            return static_cast<bool>(d_double) || value;
        else
            throw std::invalid_argument("no boolean value has been set");
    }

    bool dynamic::operator^(bool value)
    {
        if (flag[1])
            return static_cast<bool>(d_double) ^ value;
        else
            throw std::invalid_argument("no boolean value has been set");
    }

    bool dynamic::operator!()
    {
        if (flag[1])
            return !static_cast<bool>(d_double);
        else
            throw std::invalid_argument("no boolean value has been set");
    }

    void dynamic::operator&=(bool value)
    {
        bool temp = static_cast<bool>(d_double);
        if (flag[1])
        {
            temp &= value;
            set(temp);
        }
        else
            throw std::invalid_argument("no boolean value has been set");
    }

    void dynamic::operator|=(bool value)
    {
        bool temp = static_cast<bool>(d_double);
        if (flag[1])
        {
            temp |= value;
            set(temp);
        }
        else
            throw std::invalid_argument("no boolean value has been set");
    }

    constexpr void dynamic::operator+=(char value) noexcept { d_double += value; }

    constexpr void dynamic::operator+=(int value) noexcept { d_double += value; }

    constexpr void dynamic::operator+=(float value) noexcept { d_double += value; }

    constexpr void dynamic::operator+=(double value) noexcept { d_double += value; }

    constexpr void dynamic::operator+=(const dynamic &other) noexcept { d_double += other.d_double; }

    constexpr void dynamic::operator-=(char value) noexcept { d_double -= value; }

    constexpr void dynamic::operator-=(int value) noexcept { d_double -= value; }

    constexpr void dynamic::operator-=(float value) noexcept { d_double -= value; }

    constexpr void dynamic::operator-=(double value) noexcept { d_double -= value; }

    constexpr void dynamic::operator-=(const dynamic &other) noexcept { d_double -= other.d_double; }

    constexpr void dynamic::operator*=(char value) noexcept { d_double *= value; }

    constexpr void dynamic::operator*=(int value) noexcept { d_double *= value; }

    constexpr void dynamic::operator*=(float value) noexcept { d_double *= value; }

    constexpr void dynamic::operator*=(double value) noexcept { d_double *= value; }

    constexpr void dynamic::operator*=(const dynamic &other) noexcept { d_double *= other.d_double; }

    constexpr void dynamic::operator/=(char value) noexcept { d_double /= value; }

    constexpr void dynamic::operator/=(int value) noexcept { d_double /= value; }

    constexpr void dynamic::operator/=(float value) noexcept { d_double /= value; }

    constexpr void dynamic::operator/=(double value) noexcept { d_double /= value; }

    constexpr void dynamic::operator/=(const dynamic &other) noexcept { d_double /= other.d_double; }

    constexpr void dynamic::operator^=(char value) noexcept { d_double = std::pow(d_double, value); }

    constexpr void dynamic::operator^=(int value) noexcept { d_double = std::pow(d_double, value); }

    constexpr void dynamic::operator^=(float value) noexcept { d_double = std::pow(d_double, value); }

    constexpr void dynamic::operator^=(double value) noexcept { d_double = std::pow(d_double, value); }
};

#endif // OPENUDT___UDT_DYNAMIC_HPP