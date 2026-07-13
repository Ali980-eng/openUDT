/**
 * @file ternary.hpp
 * @brief A header file defining the Ternary class for representing ternary logic values.
 * The Ternary class provides methods for setting, getting, and manipulating ternary logic values,
 * which can be true, false, or unknown. The class includes constructors, assignment operators,
 * logical operators, and comparison operators to facilitate the use of ternary logic in C++ programs.
 * The Ternary class is designed to be efficient and easy to use, making it a valuable tool for
 * developers working with ternary logic in their applications.
 * @date 2025/9/25
 * @author Ali Lafi
 */

#include "cfrost/structure.h"

#pragma once
#ifndef OPENUDT___BASIC___TERNARY_HPP
#define OPENUDT___BASIC___TERNARY_HPP

const int unknown = 2;
/// @brief A class to represent ternary logic values: true, false, and unknown.
/// The class provides methods for setting, getting, and manipulating ternary logic values.
namespace udt
{

    /**
     * @class ternary
     * @brief A class to represent ternary logic values: true, false, and unknown
     * The ternary class provides methods for setting, getting, and manipulating ternary logic values,
     * which can be true, false, or unknown. The class includes constructors, assignment operators,
     * logical operators, and comparison operators to facilitate the use of ternary logic in C++ programs.
     * The ternary class is designed to be efficient and easy to use, making it a valuable tool for
     * developers working with ternary logic in their applications.
     */
    class ternary
    {
    private:
        /// @brief The internal representation of the ternary logic value.
        enum Value
        {
            FALSE = 0,
            TRUE = 1,
            UNKNOWN = 2
        } value;

    public:
        /// @brief Default constructor initializes the value to UNKNOWN.
        ternary() noexcept : value(UNKNOWN) {}

        /// @brief Constructor initializes the value based on a boolean input.
        /// @param b Boolean value to initialize the ternary logic value.
        ternary(const bool &b) noexcept : value(b ? TRUE : FALSE) {}

        /// @brief Constructor initializes the value based on an integer input.
        /// @param v Integer value to initialize the ternary logic value (0 for FALSE,
        ternary(int v) noexcept
        {
            if (v == 0)
                value = FALSE;
            else if (v == 1)
                value = TRUE;
            else
                value = UNKNOWN;
        }

        /// @brief Copy constructor initializes the value based on another Ternary object.
        /// @param other Another Ternary object to initialize the value.
        ternary(const ternary &other) noexcept : value(other.value) {}

        /// @brief Resets the value to UNKNOWN.
        procedure(reset) noexcept { value = UNKNOWN; }

        /// @brief Sets the value based on a boolean input.
        /// @param b Boolean value to set the ternary logic value.
        void set(const bool &b) noexcept { value = b ? TRUE : FALSE; }

        /// @brief Sets the value based on another Ternary object.
        /// @param other Another ternary object to set the value.
        void set(ternary &other) noexcept { value = other.value; }

        /// @brief Sets the value based on an integer input.
        /// @param v Integer value to set the ternary logic value (0 for FALSE,
        procedure(set) noexcept { value = UNKNOWN; }

        /// @brief Sets the value based on an integer input.
        /// @param v Integer value to set the ternary logic value (0 for FALSE,
        void set(int v) noexcept
        {
            if (v == 0)
                value = FALSE;
            else if (v == 1)
                value = TRUE;
            else
                value = UNKNOWN;
        }

        /// @brief Gets the boolean representation of the ternary logic value.
        /// @return True if the value is TRUE, false otherwise.
        bool get() const noexcept
        {
            if (value == TRUE)
                return true;
            else
                return false;
        }

        /// @brief Assignment operator to set the value based on a boolean input.
        /// @param b Boolean value to assign to the ternary logic value.
        void operator=(const bool &b) noexcept { value = b ? TRUE : FALSE; }

        /// @brief Assignment operator to set the value based on another Ternary_Logic object.
        /// @param other Another ternary object to assign to the ternary logic value.
        /// @return Reference to the assigned Ternary object.
        ternary &operator=(const ternary &other) noexcept
        {
            value = other.value;
            return *this;
        }

        /// @brief Equality operator to compare with a boolean value.
        /// @param v Boolean value to compare with the ternary logic value.
        /// @return True if the values are equal, false otherwise.
        bool operator==(const bool &v) noexcept { return value == (v ? TRUE : FALSE); }

        /// @brief Equality operator to compare with another Ternary object.
        /// @param other Another ternary object to compare with the ternary logic value.
        /// @return True if the values are equal, false otherwise.
        bool operator==(const ternary &other) const noexcept { return value == other.value; }

        /// @brief Inequality operator to compare with a boolean value.
        /// @param v Boolean value to compare with the ternary logic value.
        /// @return True if the values are not equal, false otherwise.
        bool operator!=(const bool &v) noexcept { return value != (v ? TRUE : FALSE); }

        /// @brief Inequality operator to compare with another Ternary object.
        /// @param other Another ternary object to compare with the ternary logic value.
        /// @return True if the values are not equal, false otherwise.
        bool operator!=(const ternary &other) const noexcept { return value != other.value; }

        /// @brief Logical NOT operator.
        /// @return The negation of the current ternary logic value.
        ternary operator!() const noexcept
        {
            if (value == TRUE)
                return ternary(FALSE);
            else if (value == FALSE)
                return ternary(TRUE);
            else
                return ternary();
        }

        /// @brief Logical AND operator.
        /// @param other Another ternary object to perform the AND operation with.
        /// @return The result of the logical AND operation.
        ternary operator&&(const ternary &other) noexcept
        {
            if (value == FALSE || other.value == FALSE)
                return ternary(FALSE);
            else if (value == TRUE && other.value == TRUE)
                return ternary(TRUE);
            else
                return ternary(UNKNOWN);
        }

        /// @brief Logical OR operator.
        /// @param other Another ternary object to perform the OR operation with.
        /// @return The result of the logical OR operation.
        ternary operator||(const ternary &other) noexcept
        {
            if (value == TRUE || other.value == TRUE)
                return ternary(TRUE);
            else if (value == FALSE && other.value == FALSE)
                return ternary(FALSE);
            else
                return ternary(UNKNOWN);
        }

        /// @brief Logical XOR operator.
        /// @param other Another ternary object to perform the XOR operation with.
        /// @return The result of the logical XOR operation.
        ternary operator^(const ternary &other) noexcept
        {
            if (value == UNKNOWN || other.value == UNKNOWN)
                return ternary(UNKNOWN);
            else if (value == other.value)
                return ternary(FALSE);
            else
                return ternary(TRUE);
        }

        /// @brief Assignment operator for logical OR operation.
        /// @param other Another ternary object to assign with the logical OR operation.
        void operator|=(const ternary &other) noexcept { *this = *this || other; }

        /// @brief Assignment operator for logical AND operation.
        /// @param other Another ternary object to assign with the logical AND operation.
        void operator&=(const ternary &other) noexcept { *this = *this && other; }

        /// @brief Assignment operator for logical XOR operation.
        /// @param other Another ternary object to assign with the logical XOR operation.
        void operator^=(const ternary &other) noexcept { *this = *this ^ other; }

        ~ternary() = default;
    };
}

#endif // OPENUDT___BASIC___TERNARY_HPP