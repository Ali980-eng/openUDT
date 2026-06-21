#include "core/bfs/bfs_8.hpp"
#include <cmath>

#pragma once
#ifndef OPENUDT___CORE___DYNAMIC__DYANMIC_F__HPP
#define OPENUDT___CORE___DYNAMIC__DYANMIC_F__HPP

namespace udt
{

    /**
     * @brief A dynamic data type class that can hold and manipulate different standard data types (bool, char, int, float, double).
     * @details This class provides methods to set, get, and perform operations on the stored value, while keeping track of its type.
     * @note This class is designed to work with C++23 standard.
     * @warning This class is not thread-safe.
     */
    class dynamic_f
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
        udt::bfs_8 flag;
        float d_float;

    public:
        /**
         * Default constructor for the dynamic_f type holder.
         *
         * Initializes the object into a well-defined state representing a double value
         * with the following initial values:
         * - d_double: value-initialized (equivalent to 0.0)
         * - dtype: true (indicates the active type is double)
         * - btype, ctype, itype, ftype: false (no other type is active)
         * - bvalue: false (boolean value flag cleared)
         *
         * Use this constructor to obtain a dynamic_f object that starts as a double with
         * a zero-initialized value and no other active type flags.
         */
        dynamic_f() noexcept : d_float(0.0f) { flag.set(0); }

        /**
         * Move Constructor
         * @brief Constructs a dynamic_f object by moving resources from another dynamic object.
         * @param other The dynamic_f object to move from.
         */
        dynamic_f(dynamic_f &&) = default;

        /**
         * @brief Constructs a dynamic_f object with a boolean value
         *
         * Initializes the dynamic_f object with a boolean value and sets the internal type flags.
         * The double value is initialized to default, and boolean type flag is set to true
         * while all other type flags are set to false.
         *
         * @param value The boolean value to store
         * @noexcept This constructor does not throw exceptions
         */
        dynamic_f(bool value) noexcept : d_float(static_cast<float>(value)) { flag.set(1); }

        /**
         * Construct a dynamic_f object from a character.
         *
         * The character is converted to a float and stored in d_float.
         * The instance is marked as a character type (ctype = true) while all
         * other type flags (btype, itype, ftype, dtype) are cleared. The
         * boolean value flag (bvalue) is also set to false.
         *
         * This constructor does not throw (noexcept).
         *
         * @param value  Character value to initialize the dynamic_f instance from.
         */
        dynamic_f(char value) noexcept : d_float(static_cast<float>(value)) { flag.set(2); }

        /**
         * Construct a dynamic_f object from a short integer.
         * The short integer is converted to a float and stored in d_float. The instance is marked as a short integer type (flag[3] = true) while all other type flags (btype, ctype, itype, ftype, dtype) are cleared. The boolean value flag (bvalue) is also set to false.
         * This constructor is noexcept and does not throw exceptions.
         * @param value The short integer value to initialize the dynamic_f instance with.
         */
        dynamic_f(short value) noexcept : d_float(static_cast<float>(value)) { flag.set(3); }

        /**
         * Constructs a dynamic_f object representing the given integer value.
         *
         * The integer is stored in the internal floating-point storage (d_float)
         * after conversion to float. Type-discriminator flags are updated so that
         * itype becomes true and all other type flags (btype, ctype, ftype, dtype)
         * as well as bvalue are set to false.
         *
         * This constructor is noexcept.
         *
         * @param value The integer value to initialize the dynamic_f object with.
         */
        dynamic_f(int value) noexcept : d_float(static_cast<float>(value)) { flag.set(4); }

        /**
         * @brief Constructs a dynamic_f object from a long integer value.
         * The long integer is converted to a float and stored in the internal d_float member. The type flags are updated to indicate that this instance holds a long integer value (flag[5] = true) while all other type flags (btype, ctype, itype, ftype, dtype) and the boolean value flag (bvalue) are set to false.
         * This constructor is noexcept and does not throw exceptions.
         * @param value The long integer value to initialize the dynamic_f instance with.
         * @note This constructor allows for implicit conversion from long to dynamic_f, enabling seamless assignment of long integer values to dynamic_f objects. The internal state is updated accordingly to reflect the new type and value.
         */
        dynamic_f(long value) noexcept : d_float(static_cast<float>(value)) { flag.set(5); }

        /**
         * @brief Constructs a dynamic_f object from a long long integer value.
         * The long long integer is converted to a float and stored in the internal d_float member. The type flags are updated to indicate that this instance holds a long integer value (flag[5] = true) while all other type flags (btype, ctype, itype, ftype, dtype) and the boolean value flag (bvalue) are set to false.
         * This constructor is noexcept and does not throw exceptions.
         * @param value The long long integer value to initialize the dynamic_f instance with.
         * @note This constructor allows for implicit conversion from long long to dynamic_f, enabling seamless assignment of long long integer values to dynamic_f objects. The internal state is updated accordingly to reflect the new type and value.
         */
        dynamic_f(long long value) noexcept : d_float(static_cast<float>(value)) { flag.set(5); }

        /**
         * @brief Constructs a dynamic_f object from a float value.
         *
         * Converts the provided float to double and stores it in the internal
         * double representation (d_float). Updates internal type flags to mark
         * this instance as holding a floating-point value and clears other type/value flags.
         *
         * @param value The float value to store (converted to float).
         * @note This constructor is noexcept and does not throw exceptions.
         *
         * @post d_float == static_cast<float>(value)
         * @post ftype == true
         * @post btype == false, ctype == false, itype == false, dtype == false, bvalue == false
         */
        dynamic_f(float value) noexcept : d_float(static_cast<float>(value)) { flag.set(6); }

        /**
         * @brief Constructs a dynamic_f object holding a float value.
         *
         * Stores the provided value as a double and updates internal type flags so
         * that the object is treated as a float. All other type flags are cleared.
         *
         * @param value The double value to store.
         * @note This constructor is noexcept and does not throw exceptions.
         */
        dynamic_f(double value) noexcept : d_float(static_cast<float>(value)) { flag.set(0); }

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
        dynamic_f(const dynamic_f &other) noexcept : d_float(other.d_float),
                                                     flag(other.flag) {}

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
            d_float = static_cast<float>(value);
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
            d_float = static_cast<float>(value);
            flag.reset_all();
            flag.set(2);
        }
        /**
         * Set the stored value from a short integer.
         * Converts the provided short integer to a double (via static_cast<double>) and stores it in the internal d_double member. Updates internal type flags to indicate that the current value is a short integer, while clearing all other type flags (boolean, character, integer, float, double) and the boolean value flag.
         * This function is noexcept and does not throw exceptions.
         * @param value The short integer value to store (converted to double internally).
         * Postconditions:
         * - d_double == static_cast<double>(value)
         * - itype == true
         * - btype == false
         * - ctype == false
         * - ftype == false
         * - dtype == false
         * - bvalue == false
         */
        void set(short value) noexcept
        {
            d_float = static_cast<float>(value);
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
            d_float = static_cast<float>(value);
            flag.reset_all();
            flag.set(4);
        }
        /**
         * Set the stored value from a long integer.
         * Converts the provided long integer to a double (via static_cast<double>) and stores it in the internal d_double member. Updates internal type flags to indicate that the current value is a long integer, while clearing all other type flags (boolean, character, short integer, float, double) and the boolean value flag.
         * This function is noexcept and does not throw exceptions.
         * @param value The long integer value to store (converted to double internally).
         * Postconditions:
         * - d_double == static_cast<double>(value)
         * - itype == false
         * - btype == false
         * - ctype == false
         * - ftype == false
         * - dtype == false
         * - bvalue == false
         */
        void set(long value) noexcept
        {
            d_float = static_cast<float>(value);
            flag.reset_all();
            flag.set(5);
        }
        /**
         * Set the stored value from a long long integer.
         * Converts the provided long long integer to a double (via static_cast<double>) and stores it in the internal d_double member. Updates internal type flags to indicate that the current value is a long integer, while clearing all other type flags (boolean, character, short integer, float, double) and the boolean value flag.
         * This function is noexcept and does not throw exceptions.
         * @param value The long long integer value to store (converted to double internally).
         * Postconditions:
         * - d_double == static_cast<double>(value)
         * - itype == false
         * - btype == false
         * - ctype == false
         * - ftype == false
         * - dtype == false
         * - bvalue == false
         */
        void set(long long value) noexcept
        {
            d_float = static_cast<float>(value);
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
            d_float = static_cast<float>(value);
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
            d_float = value;
            flag.reset_all();
            flag.set(0);
        }
        /**
         * @brief Store a long double value and mark this object as holding a long double.
         * This function assigns the provided long double value to the internal double storage (d_double) and updates the internal type flags to indicate that the current value is a long double. Specifically, it sets the flag corresponding to long double (flag[7]) to true while resetting all other type flags (boolean, character, short integer, integer, float, double) and the boolean value flag to false.
         * This function is noexcept and does not throw exceptions.
         * @param value The long double value to store (converted to double internally).
         * Postconditions:
         * - d_double == static_cast<double>(value)
         * - itype == false
         * - btype == false
         * - ctype == false
         * - ftype == false
         * - dtype == false
         */
        void set(long double value) noexcept
        {
            d_float = value;
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
        constexpr void set(const dynamic_f &other) noexcept
        {
            d_float = other.d_float;
            flag = other.flag;
        }
        /**
         * @brief Retrieves the stored boolean value.
         * @return The stored boolean value.
         * @note This function assumes that the current type is boolean; behavior is undefined otherwise.
         */
        constexpr bool get_bool() noexcept { return static_cast<bool>(d_float); }
        /**
         * @brief Retrieves the stored character value.
         * @return The stored character value.
         * @note This function assumes that the current type is character; behavior is undefined otherwise.
         */
        constexpr char get_char() noexcept { return static_cast<char>(d_float); }
        /**
         * @brief Retrieves the stored integer value.
         * @return The stored integer value.
         * @note This function assumes that the current type is integer; behavior is undefined otherwise.
         */
        constexpr int get_int() noexcept { return static_cast<int>(d_float); }
        /**
         * @brief Retrieves the stored float value.
         * @return The stored float value.
         * @note This function assumes that the current type is float; behavior is undefined otherwise.
         */
        constexpr float get_float() noexcept { return static_cast<float>(d_float); }
        /**
         * @brief Retrieves the stored double value.
         * @return The stored double value.
         * @note This function assumes that the current type is double; behavior is undefined otherwise.
         */
        constexpr double get_double() noexcept { return static_cast<double>(d_float); }
        /**
         * @brief Returns a reference to the current dynamic object.
         * @return A reference to the current dynamic object.
         * @note This function does not throw exceptions.
         */
        dynamic_f &get() noexcept { return *this; }
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
            d_float = float();
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
        dynamic_f &operator=(dynamic_f &&) = default;
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
        constexpr dynamic_f &operator=(const dynamic_f &other) noexcept
        {
            d_float = other.d_float;
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
                return static_cast<bool>(d_float) == value;
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
                return static_cast<char>(d_float) == value;
            else
                return false;
        }
        /**
         * @brief Equality operator for dynamic.
         * @param value The short integer value to compare.
         * @return True if equal, false otherwise.
         */
        bool operator==(short value) const noexcept
        {
            if (flag[3])
                return static_cast<short>(d_float) == value;
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
                return static_cast<int>(d_float) == value;
            else
                return false;
        }
        /**
         * @brief Equality operator for dynamic.
         * @param value The long integer value to compare.
         * @return True if equal, false otherwise.
         */
        bool operator==(long value) const noexcept
        {
            if (flag[5])
                return static_cast<long>(d_float) == value;
            else
                return false;
        }
        /**
         * @brief Equality operator for dynamic.
         * @param value The long long integer value to compare.
         * @return True if equal, false otherwise.
         */
        bool operator==(long long value) const noexcept
        {
            if (flag[5])
                return static_cast<long long>(d_float) == value;
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
                return static_cast<float>(d_float) == value;
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
                return d_float == value;
            else
                return false;
        }
        /**
         * @brief Equality operator for dynamic.
         * @param value The long double value to compare.
         * @return True if equal, false otherwise.
         */
        bool operator==(long double value) const noexcept
        {
            if (flag[7])
                return d_float == value;
            else
                return false;
        }
        /**
         * @brief Equality operator for dynamic.
         * @param other The dynamic instance to compare with.
         * @return True if equal, false otherwise.
         */
        constexpr bool operator==(const dynamic_f &other) const noexcept
        {
            return d_float == other.d_float && flag == other.flag;
        }
        /**
         * @brief Inequality operator for dynamic.
         * @param value The boolean value to compare.
         * @return True if not equal, false otherwise.
         */
        bool operator!=(bool value) const noexcept
        {
            if (flag[1])
                return static_cast<bool>(d_float) != value;
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
                return static_cast<char>(d_float) != value;
            else
                return false;
        }
        /**
         * @brief Inequality operator for dynamic.
         * @param value The short integer value to compare.
         * @return True if not equal, false otherwise.
         */
        bool operator!=(short value) const noexcept
        {
            if (flag[3])
                return static_cast<short>(d_float) != value;
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
                return static_cast<int>(d_float) != value;
            else
                return false;
        }
        /**
         * @brief Inequality operator for dynamic.
         * @param value The long integer value to compare.
         * @return True if not equal, false otherwise.
         */
        bool operator!=(long value) const noexcept
        {
            if (flag[5])
                return static_cast<long>(d_float) != value;
            else
                return false;
        }
        /**
         * @brief Inequality operator for dynamic.
         * @param value The long long integer value to compare.
         * @return True if not equal, false otherwise.
         */
        bool operator!=(long long value) const noexcept
        {
            if (flag[5])
                return static_cast<long long>(d_float) != value;
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
                return static_cast<float>(d_float) != value;
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
                return static_cast<double>(d_float) != value;
            else
                return false;
        }
        /**
         * @brief Inequality operator for dynamic.
         * @param value The long double value to compare.
         * @return True if not equal, false otherwise.
         */
        bool operator!=(long double value) const noexcept
        {
            if (flag[7])
                return static_cast<long double>(d_float) != value;
            else
                return false;
        }
        /**
         * @brief Inequality operator for dynamic.
         * @param other The dynamic instance to compare with.
         * @return True if not equal, false otherwise.
         */
        constexpr bool operator!=(const dynamic_f &other) const noexcept
        {
            return d_float != other.d_float && flag != other.flag;
        }
        /**
         * @brief Greater-than operator for dynamic.
         * @param c The character value to compare.
         * @return True if greater, false otherwise.
         */
        bool operator>(char c) const noexcept
        {
            if (flag[2])
                return static_cast<char>(d_float) > c;
            else
                return false;
        }
        /**
         * @brief Greater-than operator for dynamic.
         * @param value The short integer value to compare.
         * @return True if greater, false otherwise.
         */
        bool operator>(short value) const noexcept
        {
            if (flag[3])
                return static_cast<short>(d_float) > value;
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
                return static_cast<int>(d_float) > value;
            else
                return false;
        }
        /**
         * @brief Greater-than operator for dynamic.
         * @param value The long integer value to compare.
         * @return True if greater, false otherwise.
         */
        bool operator>(long value) const noexcept
        {
            if (flag[5])
                return static_cast<long>(d_float) > value;
            else
                return false;
        }
        /**
         * @brief Greater-than operator for dynamic.
         * @param value The long long integer value to compare.
         * @return True if greater, false otherwise.
         */
        bool operator>(long long value) const noexcept
        {
            if (flag[5])
                return static_cast<long long>(d_float) > value;
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
                return static_cast<float>(d_float) > value;
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
                return static_cast<int>(d_float) > value;
            else
                return false;
        }
        /**
         * @brief Greater-than-or-equal operator for dynamic.
         * @param c The character value to compare.
         * @return True if greater or equal, false otherwise.
         */
        constexpr bool operator>=(char c) const noexcept { return static_cast<char>(d_float) >= c; }
        /**
         * @brief Greater-than-or-equal operator for dynamic.
         * @param value The integer value to compare.
         * @return True if greater or equal, false otherwise.
         */
        constexpr bool operator>=(int value) const noexcept { return static_cast<int>(d_float) >= value; }
        /**
         * @brief Greater-than-or-equal operator for dynamic.
         * @param value The float value to compare.
         * @return True if greater or equal, false otherwise.
         */
        constexpr bool operator>=(float value) const noexcept { return static_cast<float>(d_float) >= value; }
        /**
         * @brief Greater-than-or-equal operator for dynamic.
         * @param value The double value to compare.
         * @return True if greater or equal, false otherwise.
         */
        constexpr bool operator>=(double value) const noexcept { return d_float >= value; }
        /**
         * @brief Less-than operator for dynamic.
         * @param c The character value to compare.
         * @return True if less, false otherwise.
         */
        constexpr bool operator<(char c) const noexcept { return static_cast<char>(d_float) < c; }
        /**
         * @brief Less-than operator for dynamic.
         * @param value The integer value to compare.
         * @return True if less, false otherwise.
         */
        constexpr bool operator<(int value) const noexcept { return static_cast<int>(d_float) < value; }
        /**
         * @brief Less-than operator for dynamic.
         * @param value The float value to compare.
         * @return True if less, false otherwise.
         */
        constexpr bool operator<(float value) const noexcept { return static_cast<float>(d_float) < value; }
        /**
         * @brief Less-than operator for dynamic.
         * @param value The double value to compare.
         * @return True if less, false otherwise.
         */
        constexpr bool operator<(double value) const noexcept { return d_float < value; }
        /**
         * @brief Less-than-or-equal operator for dynamic.
         * @param c The character value to compare.
         * @return True if less or equal, false otherwise.
         */
        constexpr bool operator<=(char c) const noexcept { return static_cast<char>(d_float) <= c; }
        /**
         * @brief Less-than-or-equal operator for dynamic.
         * @param value The integer value to compare.
         * @return True if less or equal, false otherwise.
         */
        constexpr bool operator<=(int value) const noexcept { return static_cast<int>(d_float) <= value; }
        /**
         * @brief Less-than-or-equal operator for dynamic.
         * @param value The float value to compare.
         * @return True if less or equal, false otherwise.
         */
        constexpr bool operator<=(float value) const noexcept { return static_cast<float>(d_float) <= value; }
        /**
         * @brief Less-than-or-equal operator for dynamic.
         * @param value The double value to compare.
         * @return True if less or equal, false otherwise.
         */
        constexpr bool operator<=(double value) const noexcept { return d_float <= value; }
        /**
         * @brief Pre-increment operator for dynamic.
         * Increments the stored double value by 1.
         * @note noexcept This operator does not throw exceptions.
         */
        constexpr void operator++() noexcept { ++d_float; }
        /**
         * @brief Pre-decrement operator for dynamic.
         * Decrements the stored double value by 1.
         * @note noexcept This operator does not throw exceptions.
         */
        constexpr void operator--() noexcept { --d_float; }
        /**
         * @brief Logical AND operator for dynamic.
         * @param value The boolean value to AND with.
         * @return The result of the logical AND operation.
         * @throws std::invalid_argument if the current type is not boolean.
         */
        bool operator&&(bool value)
        {
            if (flag[1])
                return static_cast<bool>(d_float) && value;
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
                return static_cast<bool>(d_float) || value;
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
                return static_cast<bool>(d_float) ^ value;
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
                return !static_cast<bool>(d_float);
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
            bool temp = static_cast<bool>(d_float);
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
            bool temp = static_cast<bool>(d_float);
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
        constexpr void operator+=(char value) noexcept { d_float += value; }
        /**
         * @brief Addition assignment operator for dynamic.
         * @param value The integer value to add.
         */
        constexpr void operator+=(int value) noexcept { d_float += value; }
        /**
         * @brief Addition assignment operator for dynamic.
         * @param value The float value to add.
         */
        constexpr void operator+=(float value) noexcept { d_float += value; }
        /**
         * @brief Addition assignment operator for dynamic.
         * @param value The double value to add.
         */
        constexpr void operator+=(double value) noexcept { d_float += value; }
        /**
         * @brief Addition assignment operator for dynamic.
         * @param other The dynamic object to add.
         */
        constexpr void operator+=(const dynamic_f &other) noexcept { d_float += other.d_float; }
        /**
         * @brief Subtraction assignment operator for dynamic.
         * @param value The character value to subtract.
         */
        constexpr void operator-=(char value) noexcept { d_float -= value; }
        /**
         * @brief Subtraction assignment operator for dynamic.
         * @param value The integer value to subtract.
         */
        constexpr void operator-=(int value) noexcept { d_float -= value; }
        /**
         * @brief Subtraction assignment operator for dynamic.
         * @param value The float value to subtract.
         */
        constexpr void operator-=(float value) noexcept { d_float -= value; }
        /**
         * @brief Subtraction assignment operator for dynamic.
         * @param value The double value to subtract.
         */
        constexpr void operator-=(double value) noexcept { d_float -= value; }
        /**
         * @brief Subtraction assignment operator for dynamic.
         * @param other The dynamic object to subtract.
         */
        constexpr void operator-=(const dynamic_f &other) noexcept { d_float -= other.d_float; }
        /**
         * @brief Multiplication assignment operator for dynamic.
         * @param value The character value to multiply.
         */
        constexpr void operator*=(char value) noexcept { d_float *= value; }
        /**
         * @brief Multiplication assignment operator for dynamic.
         * @param value The integer value to multiply.
         */
        constexpr void operator*=(int value) noexcept { d_float *= value; }
        /**
         * @brief Multiplication assignment operator for dynamic.
         * @param value The float value to multiply.
         */
        constexpr void operator*=(float value) noexcept { d_float *= value; }
        /**
         * @brief Multiplication assignment operator for dynamic.
         * @param value The double value to multiply.
         */
        constexpr void operator*=(double value) noexcept { d_float *= value; }
        /**
         * @brief Multiplication assignment operator for dynamic.
         * @param other The dynamic object to multiply.
         */
        constexpr void operator*=(const dynamic_f &other) noexcept { d_float *= other.d_float; }
        /**
         * @brief Division assignment operator for dynamic.
         * @param value The character value to divide.
         */
        constexpr void operator/=(char value) noexcept { d_float /= value; }
        /**
         * @brief Division assignment operator for dynamic.
         * @param value The integer value to divide.
         */
        constexpr void operator/=(int value) noexcept { d_float /= value; }
        /**
         * @brief Division assignment operator for dynamic.
         * @param value The float value to divide.
         */
        constexpr void operator/=(float value) noexcept { d_float /= value; }
        /**
         * @brief Division assignment operator for dynamic.
         * @param value The double value to divide.
         */
        constexpr void operator/=(double value) noexcept { d_float /= value; }
        /**
         * @brief Division assignment operator for dynamic.
         * @param other The dynamic object to divide.
         */
        constexpr void operator/=(const dynamic_f &other) noexcept { d_float /= other.d_float; }
        /**
         * @brief Exponentiation assignment operator for dynamic.
         * @param value The character exponent value.
         */
        constexpr void operator^=(char value) noexcept { d_float = std::pow(d_float, value); }
        /**
         * @brief Exponentiation assignment operator for dynamic.
         * @param value The integer exponent value.
         */
        constexpr void operator^=(int value) noexcept { d_float = std::pow(d_float, value); }
        /**
         * @brief Exponentiation assignment operator for dynamic.
         * @param value The float exponent value.
         */
        constexpr void operator^=(float value) noexcept { d_float = std::pow(d_float, value); }
        /**
         * @brief Exponentiation assignment operator for dynamic.
         * @param value The double exponent value.
         */
        constexpr void operator^=(double value) noexcept { d_float = std::pow(d_float, value); }
    };

    // implementation of dynamic_f class member functions
    void dynamic_f::set(bool value) noexcept
    {
        d_float = static_cast<float>(value);
        flag.reset_all();
        flag.set(1);
    }

    void dynamic_f::set(char value) noexcept
    {
        d_float = static_cast<float>(value);
        flag.reset_all();
        flag.set(2);
    }

    void dynamic_f::set(short value) noexcept
    {
        d_float = static_cast<float>(value);
        flag.reset_all();
        flag.set(3);
    }

    void dynamic_f::set(int value) noexcept
    {
        d_float = static_cast<float>(value);
        flag.reset_all();
        flag.set(4);
    }

    void dynamic_f::set(long value) noexcept
    {
        d_float = static_cast<float>(value);
        flag.reset_all();
        flag.set(5);
    }

    void dynamic_f::set(long long value) noexcept
    {
        d_float = static_cast<float>(value);
        flag.reset_all();
        flag.set(5);
    }

    void dynamic_f::set(float value) noexcept
    {
        d_float = static_cast<float>(value);
        flag.reset_all();
        flag.set(6);
    }

    void dynamic_f::set(double value) noexcept
    {
        d_float = value;
        flag.reset_all();
        flag.set(0);
    }

    void dynamic_f::set(long double value) noexcept
    {
        d_float = value;
        flag.reset_all();
        flag.set(7);
    }

    constexpr void dynamic_f::set(const dynamic_f &other) noexcept
    {
        d_float = other.d_float;
        flag = other.flag;
    }

    constexpr bool dynamic_f::get_bool() noexcept { return static_cast<bool>(d_float); }

    constexpr char dynamic_f::get_char() noexcept { return static_cast<char>(d_float); }

    constexpr int dynamic_f::get_int() noexcept { return static_cast<int>(d_float); }

    constexpr float dynamic_f::get_float() noexcept { return static_cast<float>(d_float); }

    constexpr double dynamic_f::get_double() noexcept { return static_cast<double>(d_float); }

    dynamic_f &dynamic_f::get() noexcept { return *this; }

    void dynamic_f::reset() noexcept
    {
        d_float = float();
        flag.reset_all();
    }

    bool dynamic_f::is_bool() noexcept { return flag[1]; }

    bool dynamic_f::is_char() noexcept { return flag[2]; }

    bool dynamic_f::is_short() noexcept { return flag[3]; }

    bool dynamic_f::is_int() noexcept { return flag[4]; }

    bool dynamic_f::is_long() noexcept { return flag[5]; }

    bool dynamic_f::is_float() noexcept { return flag[6]; }

    bool dynamic_f::is_double() noexcept { return flag[0]; }

    std::string dynamic_f::type() noexcept
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

    void dynamic_f::operator=(bool value) noexcept { set(value); }

    void dynamic_f::operator=(char value) noexcept { set(value); }

    void dynamic_f::operator=(short value) noexcept { set(value); }

    void dynamic_f::operator=(int value) noexcept { set(value); }

    void dynamic_f::operator=(long value) noexcept { set(value); }

    void dynamic_f::operator=(long long value) noexcept { set(value); }

    void dynamic_f::operator=(float value) noexcept { set(value); }

    void dynamic_f::operator=(double value) noexcept { set(value); }

    void dynamic_f::operator=(long double value) noexcept { set(value); }

    dynamic_f &dynamic_f::operator=(dynamic_f &&) = default;

    constexpr dynamic_f &dynamic_f::operator=(const dynamic_f &other) noexcept
    {
        d_float = other.d_float;
        flag = other.flag;
        return *this;
    }

    bool dynamic_f::operator==(bool value) const noexcept
    {
        if (flag[1])
            return static_cast<bool>(d_float) == value;
        else
            return false;
    }

    bool dynamic_f::operator==(char value) const noexcept
    {
        if (flag[2])
            return static_cast<char>(d_float) == value;
        else
            return false;
    }

    bool dynamic_f::operator==(short value) const noexcept
    {
        if (flag[3])
            return static_cast<short>(d_float) == value;
        else
            return false;
    }

    bool dynamic_f::operator==(int value) const noexcept
    {
        if (flag[4])
            return static_cast<int>(d_float) == value;
        else
            return false;
    }

    bool dynamic_f::operator==(long value) const noexcept
    {
        if (flag[5])
            return static_cast<long>(d_float) == value;
        else
            return false;
    }

    bool dynamic_f::operator==(long long value) const noexcept
    {
        if (flag[5])
            return static_cast<long long>(d_float) == value;
        else
            return false;
    }

    bool dynamic_f::operator==(float value) const noexcept
    {
        if (flag[6])
            return static_cast<float>(d_float) == value;
        else
            return false;
    }

    bool dynamic_f::operator==(double value) const noexcept
    {
        if (flag[0])
            return d_float == value;
        else
            return false;
    }

    bool dynamic_f::operator==(long double value) const noexcept
    {
        if (flag[7])
            return d_float == value;
        else
            return false;
    }

    constexpr bool dynamic_f::operator==(const dynamic_f &other) const noexcept
    {
        return d_float == other.d_float && flag == other.flag;
    }

    bool dynamic_f::operator!=(bool value) const noexcept
    {
        if (flag[1])
            return static_cast<bool>(d_float) != value;
        else
            return false;
    }

    bool dynamic_f::operator!=(char value) const noexcept
    {
        if (flag[2])
            return static_cast<char>(d_float) != value;
        else
            return false;
    }

    bool dynamic_f::operator!=(short value) const noexcept
    {
        if (flag[3])
            return static_cast<short>(d_float) != value;
        else
            return false;
    }

    bool dynamic_f::operator!=(int value) const noexcept
    {
        if (flag[4])
            return static_cast<int>(d_float) != value;
        else
            return false;
    }

    bool dynamic_f::operator!=(long value) const noexcept
    {
        if (flag[5])
            return static_cast<long>(d_float) != value;
        else
            return false;
    }

    bool dynamic_f::operator!=(long long value) const noexcept
    {
        if (flag[5])
            return static_cast<long long>(d_float) != value;
        else
            return false;
    }

    bool dynamic_f::operator!=(float value) const noexcept
    {
        if (flag[6])
            return static_cast<float>(d_float) != value;
        else
            return false;
    }

    bool dynamic_f::operator!=(double value) const noexcept
    {
        if (flag[0])
            return static_cast<double>(d_float) != value;
        else
            return false;
    }

    bool dynamic_f::operator!=(long double value) const noexcept
    {
        if (flag[7])
            return static_cast<long double>(d_float) != value;
        else
            return false;
    }

    constexpr bool dynamic_f::operator!=(const dynamic_f &other) const noexcept
    {
        return d_float != other.d_float && flag != other.flag;
    }

    bool dynamic_f::operator>(char c) const noexcept
    {
        if (flag[2])
            return static_cast<char>(d_float) > c;
        else
            return false;
    }

    bool dynamic_f::operator>(short value) const noexcept
    {
        if (flag[3])
            return static_cast<short>(d_float) > value;
        else
            return false;
    }

    bool dynamic_f::operator>(int value) const noexcept
    {
        if (flag[4])
            return static_cast<int>(d_float) > value;
        else
            return false;
    }

    bool dynamic_f::operator>(long value) const noexcept
    {
        if (flag[5])
            return static_cast<long>(d_float) > value;
        else
            return false;
    }

    bool dynamic_f::operator>(long long value) const noexcept
    {
        if (flag[5])
            return static_cast<long long>(d_float) > value;
        else
            return false;
    }

    bool dynamic_f::operator>(float value) const noexcept
    {
        if (flag[6])
            return static_cast<float>(d_float) > value;
        else
            return false;
    }

    bool dynamic_f::operator>(double value) const noexcept
    {
        if (flag[0])
            return static_cast<double>(d_float) > value;
        else
            return false;
    }

    constexpr bool dynamic_f::operator>=(char c) const noexcept { return static_cast<char>(d_float) >= c; }

    constexpr bool dynamic_f::operator>=(int value) const noexcept { return static_cast<int>(d_float) >= value; }

    constexpr bool dynamic_f::operator>=(float value) const noexcept { return static_cast<float>(d_float) >= value; }

    constexpr bool dynamic_f::operator>=(double value) const noexcept { return static_cast<double>(d_float) >= value; }

    constexpr bool dynamic_f::operator<(char c) const noexcept { return static_cast<char>(d_float) < c; }

    constexpr bool dynamic_f::operator<(int value) const noexcept { return static_cast<int>(d_float) < value; }

    constexpr bool dynamic_f::operator<(float value) const noexcept { return static_cast<float>(d_float) < value; }

    constexpr bool dynamic_f::operator<(double value) const noexcept { return static_cast<double>(d_float) < value; }

    constexpr bool dynamic_f::operator<=(char c) const noexcept { return static_cast<char>(d_float) <= c; }

    constexpr bool dynamic_f::operator<=(int value) const noexcept { return static_cast<int>(d_float) <= value; }

    constexpr bool dynamic_f::operator<=(float value) const noexcept { return static_cast<float>(d_float) <= value; }

    constexpr bool dynamic_f::operator<=(double value) const noexcept { return static_cast<double>(d_float) <= value; }

    constexpr void dynamic_f::operator++() noexcept { ++d_float; }

    constexpr void dynamic_f::operator--() noexcept { --d_float; }

    bool dynamic_f::operator&&(bool value)
    {
        if (flag[1])
            return static_cast<bool>(d_float) && value;
        else
            throw std::invalid_argument("no boolean value has been set");
    }

    bool dynamic_f::operator||(bool value)
    {
        if (flag[1])
            return static_cast<bool>(d_float) || value;
        else
            throw std::invalid_argument("no boolean value has been set");
    }

    bool dynamic_f::operator^(bool value)
    {
        if (flag[1])
            return static_cast<bool>(d_float) ^ value;
        else
            throw std::invalid_argument("no boolean value has been set");
    }

    bool dynamic_f::operator!()
    {
        if (flag[1])
            return !static_cast<bool>(d_float);
        else
            throw std::invalid_argument("no boolean value has been set");
    }

    void dynamic_f::operator&=(bool value)
    {
        bool temp = static_cast<bool>(d_float);
        if (flag[1])
        {
            temp &= value;
            set(temp);
        }
        else
            throw std::invalid_argument("no boolean value has been set");
    }

    void dynamic_f::operator|=(bool value)
    {
        bool temp = static_cast<bool>(d_float);
        if (flag[1])
        {
            temp |= value;
            set(temp);
        }
        else
            throw std::invalid_argument("no boolean value has been set");
    }

    constexpr void dynamic_f::operator+=(char value) noexcept { d_float += value; }

    constexpr void dynamic_f::operator+=(int value) noexcept { d_float += value; }

    constexpr void dynamic_f::operator+=(float value) noexcept { d_float += value; }

    constexpr void dynamic_f::operator+=(double value) noexcept { d_float += value; }

    constexpr void dynamic_f::operator+=(const dynamic_f &other) noexcept { d_float += other.d_float; }

    constexpr void dynamic_f::operator-=(char value) noexcept { d_float -= value; }

    constexpr void dynamic_f::operator-=(int value) noexcept { d_float -= value; }

    constexpr void dynamic_f::operator-=(float value) noexcept { d_float -= value; }

    constexpr void dynamic_f::operator-=(double value) noexcept { d_float -= value; }

    constexpr void dynamic_f::operator-=(const dynamic_f &other) noexcept { d_float -= other.d_float; }

    constexpr void dynamic_f::operator*=(char value) noexcept { d_float *= value; }

    constexpr void dynamic_f::operator*=(int value) noexcept { d_float *= value; }

    constexpr void dynamic_f::operator*=(float value) noexcept { d_float *= value; }

    constexpr void dynamic_f::operator*=(double value) noexcept { d_float *= value; }

    constexpr void dynamic_f::operator*=(const dynamic_f &other) noexcept { d_float *= other.d_float; }

    constexpr void dynamic_f::operator/=(char value) noexcept { d_float /= value; }

    constexpr void dynamic_f::operator/=(int value) noexcept { d_float /= value; }

    constexpr void dynamic_f::operator/=(float value) noexcept { d_float /= value; }

    constexpr void dynamic_f::operator/=(double value) noexcept { d_float /= value; }

    constexpr void dynamic_f::operator/=(const dynamic_f &other) noexcept { d_float /= other.d_float; }

    constexpr void dynamic_f::operator^=(char value) noexcept { d_float = std::pow(d_float, value); }

    constexpr void dynamic_f::operator^=(int value) noexcept { d_float = std::pow(d_float, value); }

    constexpr void dynamic_f::operator^=(float value) noexcept { d_float = std::pow(d_float, value); }

    constexpr void dynamic_f::operator^=(double value) noexcept { d_float = std::pow(d_float, value); }
}

#endif // OPENUDT___CORE___DYNAMIC__DYANMIC_F__HPP