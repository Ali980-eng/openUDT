#include <iostream>
#include <cmath>
#include <stdexcept>

#pragma once
#ifndef OPENUDT___CORE___TRIPLE_TRIPLE_3T_HPP
#define OPENUDT___CORE___TRIPLE_TRIPLE_3T_HPP

namespace udt
{
    /**
     * @brief A class representing a triple of values of potentially different types.
     * This class template allows for storing three values of types T1, T2, and T3, which may be different from each other. It provides member functions for accessing and modifying the elements, as well as various operations such as searching, swapping, and arithmetic operations. The member functions are designed to be constexpr and noexcept where appropriate, allowing for compile-time evaluation and guaranteeing no exceptions will be thrown.
     * @tparam T1 The type of the first element in the triple.
     * @tparam T2 The type of the second element in the triple.
     * @tparam T3 The type of the third element in the triple.
     * @note The implementation of some member functions (e.g., change_element) contains a bug where '==' is used instead of '=' for assignment, which should be addressed for correct functionality.
     * @see std::tuple for a more general-purpose alternative that can store an arbitrary number of elements of varying types.
     */
    template <typename T1, typename T2, typename T3>
    class triple_t3
    {
    private:
        T1 first;
        T2 second;
        T3 third;

    public:
        /// @brief Default constructor that initializes all elements to their default values.
        constexpr triple_t3() noexcept : first(T1()), second(T2()), third(T3()) {}

        /// @brief Constructor that initializes the triple with the given values.
        /// @param first The first element.
        /// @param second The second element.
        /// @param third The third element.
        constexpr triple_t3(const T1 &first, const T2 &second, const T3 &third) noexcept : first(first), second(second), third(third) {}

        /// @brief Copy constructor that initializes the triple with another triple.
        /// @param other The other triple to copy from.
        constexpr triple_t3(const triple_t3<T1, T2, T3> &other) noexcept : first(other.first), second(other.second), third(other.third) {}

        /// @brief Gets the first element of the triple.
        /// @return The first element.
        constexpr T1 get_first() const noexcept { return first; }

        /// @brief Gets the second element of the triple.
        /// @return The second element.
        constexpr T2 get_second() const noexcept { return second; }

        /// @brief Gets the third element of the triple.
        /// @return The third element.
        constexpr T3 get_third() const noexcept { return third; }

        /// @brief Sets the first element of the triple.
        /// @param value The new value for the first element.
        constexpr void set_first(const T1 &value) noexcept { first = value; }

        /// @brief Sets the second element of the triple.
        /// @param value The new value for the second element.
        constexpr void set_second(const T2 &value) noexcept { second = value; }

        /// @brief Sets the third element of the triple.
        /// @param value The new value for the third element.
        constexpr void set_third(const T3 &value) noexcept { third = value; }

        /**
         * Sets the object's elements from the provided values.
         *
         * Copies each argument into the corresponding data member:
         *   - this->first  = first
         *   - this->second = second
         *   - this->third  = third
         *
         * The function is constexpr and noexcept: it can be used in constant expressions
         * when the copy assignments are constexpr-capable, and it guarantees not to throw.
         *
         * @param first  Value to assign to the member 'first' (copied from const reference).
         * @param second Value to assign to the member 'second' (copied from const reference).
         * @param third  Value to assign to the member 'third' (copied from const reference).
         *
         * Complexity: O(1).
         */
        constexpr void set(const T1 &first, const T2 &second, const T3 &third) noexcept
        {
            this->first = first;
            this->second = second;
            this->third = third;
        }

        /// @brief Searches for an element in the triple.
        /// @param element the element to search for.
        /// @return a boolean indicating if the element was found.
        constexpr bool sarch(const T1 &element) const noexcept { return first == element; }

        /// @brief Searches for an element in the triple.
        /// @param element the element to search for.
        /// @return a boolean indicating if the element was found.
        constexpr bool sarch(const T2 &element) const noexcept { return second == element; }

        /// @brief Searches for an element in the triple.
        /// @param element the element to search for.
        /// @return a boolean indicating if the element was found.
        constexpr bool sarch(const T3 &element) const noexcept { return third == element; }

        /**
         * @brief Exchanges the contents of this triple with another.
         *
         * Swaps the values of the three members (first, second, third) with the corresponding
         * members of @p other by calling std::swap on each member in that order.
         *
         * @param other Reference to the triple whose contents will be exchanged with this object.
         *
         * @note This member function is declared constexpr and noexcept. It can be evaluated in
         *       a constant expression if std::swap for the element types is constexpr.
         *       Because the function is unconditionally noexcept, if any std::swap invocation
         *       would throw, std::terminate will be invoked.
         *
         * @complexity Performs exactly three calls to std::swap; overall complexity is the sum
         *             of the complexities of those three calls.
         *
         * @requirements T1, T2 and T3 must be Swappable (std::swap must be valid for each).
         */
        constexpr void swap(triple_t3<T1, T2, T3> &other) noexcept
        {
            std::swap(first, other.first);
            std::swap(second, other.second);
            std::swap(third, other.third);
        }

        /**
         * @brief Copy-assignment operator for triple_t3.
         *
         * Performs a memberwise copy assignment of the three elements (first, second, third).
         * A self-assignment check is performed to avoid unnecessary work. The function is
         * declared noexcept and returns a reference to the assigned object.
         *
         * @param other The triple to copy from.
         * @return Reference to this object after assignment.
         *
         * @pre The element types T1, T2 and T3 must be copy-assignable.
         * @exception This function is noexcept; if any element's assignment throws, std::terminate may be called.
         * @complexity Constant time (subject to the complexity of each element's assignment).
         */
        constexpr triple_t3 &operator=(const triple_t3<T1, T2, T3> &other) noexcept
        {
            if (this != &other)
            {
                first = other.first;
                second = other.second;
                third = other.third;
            }
            return *this;
        }

        /// @brief Equality comparison operator for triple_t3.
        /// @param other the other triple to compare with.
        /// @return true if the triples are equal, false otherwise.
        constexpr bool operator==(const triple_t3<T1, T2, T3> &other) const noexcept { return first == other.first && second == other.second && third == other.third; }

        /// @brief Inequality comparison operator for triple_t3.
        /// @param other the other triple to compare with.
        /// @return true if the triples are not equal, false otherwise.
        constexpr bool operator!=(const triple_t3<T1, T2, T3> &other) const noexcept { return !(*this == other); }

        /// @brief Adds a value to the corresponding element.
        /// @param value sum value to add.
        constexpr void operator+=(const T1 &value) noexcept { first += value; }

        /// @brief Adds a value to the corresponding element.
        /// @param value sum value to add.
        constexpr void operator+=(const T2 &value) noexcept { second += value; }

        /// @brief Adds a value to the corresponding element.
        /// @param value sum value to add.
        constexpr void operator+=(const T3 &value) noexcept { third += value; }

        /**
         * Adds the elements of another triple to this triple, performing element-wise addition.
         *
         * This member function updates this->first by adding other.first, this->second by adding other.second,
         * and this->third by adding other.third using their respective operator+= implementations.
         *
         * Requirements:
         * - T1, T2, and T3 must support operator+=(const T&) (or a compatible overload) with the corresponding
         *   types stored in the provided other triple.
         * - For this function to be noexcept, each of the individual operator+= calls must be noexcept.
         *
         * Parameters:
         * @param other  The triple whose elements are added to this triple (passed by const reference).
         *
         * Effects:
         * - Modifies this object by performing element-wise addition with other.
         *
         * Return value:
         * - void
         *
         * Complexity:
         * - Constant time.
         *
         * Notes:
         * - constexpr-qualified: may be evaluated at compile time when operands are constexpr.
         * - Exception-safety: marked noexcept; actual noexcept-ness depends on the noexcept-specifications of the
         *   underlying operator+= implementations for T1, T2, and T3.
         */
        constexpr void operator+=(const triple_t3<T1, T2, T3> &other) noexcept
        {
            first += other.first;
            second += other.second;
            third += other.third;
        }

        /**
         * @brief Prefix increment operator that increments all three members.
         *
         * Invokes the prefix ++ operator on the members `first`, `second`, and `third`
         * in that order. The operation is performed in place and does not return a value.
         *
         * Requirements:
         * - The types of `first`, `second`, and `third` must support prefix ++.
         * - If evaluated in a constant expression, the member types' ++ must also be constexpr.
         *
         * Attributes:
         * - constexpr: Can be used in compile-time contexts when the member increments are constexpr.
         * - noexcept: Guaranteed not to throw.
         *
         * Complexity: Constant time.
         *
         * Example:
         * @code
         * // Given an object obj with integer-like members:
         * // obj.first == 1, obj.second == 2, obj.third == 3
         * ++obj; // obj.first == 2, obj.second == 3, obj.third == 4
         * @endcode
         */
        constexpr void operator++() noexcept
        {
            first++;
            second++;
            third++;
        }

        /// @brief Subtracts a value from the corresponding element.
        /// @param value the value to subtract.
        constexpr void operator-=(const T1 &value) noexcept { first -= value; }

        /// @brief Subtracts a value from the corresponding element.
        /// @param value the value to subtract.
        constexpr void operator-=(const T2 &value) noexcept { second -= value; }

        /// @brief Subtracts a value from the corresponding element.
        /// @param value the value to subtract.
        constexpr void operator-=(const T3 &value) noexcept { third -= value; }

        /// @brief Subtracts the elements of another triple from this triple.
        /// @param other the triple whose elements are to be subtracted.
        constexpr void operator-=(const triple_t3<T1, T2, T3> &other) noexcept
        {
            first -= other.first;
            second -= other.second;
            third -= other.third;
        }

        /**
         * @brief Pre-decrement operator that decrements all three elements.
         *
         * Performs a pre-decrement on each member in order: first, second, then third,
         * by invoking their respective pre-decrement operator (--).
         *
         * This function is constexpr and declared noexcept.
         *
         * Requirements:
         * - The types of first, second, and third must support pre-decrement.
         *
         * Complexity: Constant time.
         */
        constexpr void operator--() noexcept
        {
            first--;
            second--;
            third--;
        }

        /// @brief Multiplies the corresponding element by a value.
        /// @param value The value to multiply by.
        constexpr void operator*=(const T1 &value) noexcept { first *= value; }

        /// @brief Multiplies the corresponding element by a value.
        /// @param value The value to multiply by.
        constexpr void operator*=(const T2 &value) noexcept { second *= value; }

        /// @brief Multiplies the corresponding element by a value.
        /// @param value The value to multiply by.
        constexpr void operator*=(const T3 &value) noexcept { third *= value; }

        /// @brief Multiplies the corresponding element by the elements of another triple.
        /// @param other The triple whose elements are to be multiplied.
        constexpr void operator*=(const triple_t3<T1, T2, T3> &other) noexcept
        {
            first *= other.first;
            second *= other.second;
            third *= other.third;
        }

        /// @brief Divides the corresponding element by a value.
        /// @param value The value to divide by.
        constexpr void operator/=(const T1 &value) noexcept { first /= value; }

        /// @brief Divides the corresponding element by a value.
        /// @param value The value to divide by.
        constexpr void operator/=(const T2 &value) noexcept { second /= value; }

        /// @brief Divides the corresponding element by a value.
        /// @param value The value to divide by.
        constexpr void operator/=(const T3 &value) noexcept { third /= value; }

        /// @brief Divides the corresponding element by the elements of another triple.
        /// @param other The triple whose elements are to be divided.
        constexpr void operator/=(const triple_t3<T1, T2, T3> &other) noexcept
        {
            first /= other.first;
            second /= other.second;
            third /= other.third;
        }

        /// @brief Raises the corresponding element to the power of a value.
        /// @param value The exponent value.
        constexpr void operator^=(const T1 &value) noexcept { first = std::pow(first, value); }

        /// @brief Raises the corresponding element to the power of a value.
        /// @param value The exponent value.
        constexpr void operator^=(const T2 &value) noexcept { second = std::pow(second, value); }

        /// @brief Raises the corresponding element to the power of a value.
        /// @param value The exponent value.
        constexpr void operator^=(const T3 &value) noexcept { third = std::pow(third, value); }

        /// @brief Raises the elements to the powers of the elements of another triple.
        /// @param other The triple whose elements are the exponents.
        constexpr void operator^=(const triple_t3<T1, T2, T3> &other) noexcept
        {
            first = std::pow(first, other.first);
            second = std::pow(second, other.second);
            third = std::pow(third, other.third);
        }
    };
}

#endif // OPENUDT___CORE___TRIPLE_TRIPLE_3T_HPP