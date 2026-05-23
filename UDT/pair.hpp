/**
 * @file pair.hpp
 * @brief This file contains the implementation of the pair_t and pair__t classes, which represent pairs of values.
 * The pair_t class represents a pair of values of the same type, while the pair__t class represents a pair of values of different types.
 * Both classes provide various constructors, assignment operators, comparison operators, and arithmetic operators to manipulate the pairs of values.
 * The classes are designed to be used in the openUDT library and can be included in other parts of the library or in user code that requires pair-like functionality.
 * The classes are implemented in a header file to allow for inline functions and templates, which can improve performance and flexibility when using the classes.
 * The classes are defined within the udt namespace to avoid naming conflicts with other libraries or user code.
 * The classes are designed to be simple and efficient, providing basic functionality for working with pairs of values without unnecessary overhead.
 * The classes are implemented using C++23 features, such as constexpr and noexcept, to ensure that they can be used in a wide range of contexts and with various types of values.
 * Overall, the pair.hpp file provides a useful utility for working with pairs of values in the openUDT library and can be easily integrated into other parts of the library or user code as needed.
 * @date 2025/9/25
 * @author Ali Lafi
 */

#pragma once
#ifndef OPENUDT___UDT_PAIR_HPP
#define OPENUDT___UDT_PAIR_HPP

namespace udt
{
    /// @brief A class representing a pair of values of type T.
    /// @tparam T The type of the elements in the pair.
    template <typename T>
    class pair_t
    {
    private:
        T first;
        T second;

    public:
        /// @brief Default constructor that initializes both elements to their default values.
        constexpr pair_t() noexcept
        {
            first = T();
            second = T();
        }

        /// @brief Constructor that initializes the pair with the given values.
        constexpr pair_t(const T &value1, const T &value2) noexcept
        {
            first = value1;
            second = value2;
        }

        /// @brief Copy constructor that initializes the pair with another pair.
        constexpr pair_t(const pair_t &other) noexcept
        {
            first = other.first;
            second = other.second;
        }

        /// @brief Set both elements of the pair to their default values.
        constexpr void set() noexcept
        {
            first = T();
            second = T();
        }

        /// @brief Set both elements of the pair to the given values.
        /// @param value1 The value to set the first element.
        /// @param value2 The value to set the second element.
        constexpr void set(const T &value1, const T &value2) noexcept
        {
            first = value1;
            second = value2;
        }

        /// @brief Set both elements of the pair to the values from another pair.
        /// @param other The other pair to copy values from.
        constexpr void set(const pair_t &other) noexcept
        {
            first = other.first;
            second = other.second;
        }

        /// @brief Get the pair.
        /// @return The pair itself.
        constexpr pair_t get() const noexcept { return *this; }

        /// @brief Get one of the elements of the pair based on position.
        /// @param position If true, get the first element; if false, get the second
        constexpr T get(bool position) const noexcept
        {
            if (position)
                return first;
            else
                return second;
        }

        /// @brief Swap the two elements of the pair.
        constexpr void swap() noexcept
        {
            T swap_v = first;
            first = second;
            second = swap_v;
        }

        /// @brief Assign a value to both elements of the pair.
        /// @param value The value to assign.
        constexpr void operator=(const T &value) noexcept { first = value; }

        /// @brief Assign values from another pair to this pair.
        /// @param other The other pair to copy values from.
        constexpr void operator=(const pair_t &other) noexcept
        {
            first = other.first;
            second = other.second;
        }

        /// @brief Check if either element of the pair is equal to the given value.
        /// @param value The value to compare with.
        /// @return True if either element is equal to the value, false otherwise.
        constexpr bool operator==(const T &value) noexcept { return first == value || second == value; }

        /// @brief Check if both elements of the pair are equal to the corresponding elements of another pair.
        /// @param other The other pair to compare with.
        /// @return True if both elements are equal, false otherwise.
        constexpr bool operator==(const pair_t &other) noexcept
        {
            return first == other.first && second == other.second;
        }

        /// @brief Check if both elements of the pair are not equal to the given value.
        /// @param value The value to compare with.
        /// @return True if both elements are not equal to the value, false otherwise.
        constexpr bool operator!=(const T &value) noexcept { return first != value && second != value; }

        /// @brief Check if both elements of the pair are not equal to the corresponding elements of another pair.
        /// @param other The other pair to compare with.
        /// @return True if both elements are not equal, false otherwise.
        constexpr bool operator!=(const pair_t &other) noexcept { return first != other.first && second != other.second; }

        /// @brief Increment both elements of the pair.
        constexpr void operator++() noexcept
        {
            ++first;
            ++second;
        }

        /// @brief Decrement both elements of the pair.
        constexpr void operator--() noexcept
        {
            --first;
            --second;
        }

        /// @brief Add a value to both elements of the pair.
        /// @param value The value to add.
        constexpr void operator+=(const T &value) noexcept
        {
            first += value;
            second += value;
        }

        /// @brief Subtract a value from both elements of the pair.
        /// @param value The value to subtract.
        constexpr void operator-=(const T &value) noexcept
        {
            first -= value;
            second -= value;
        }

        /// @brief Multiply both elements of the pair by a value.
        /// @param value The value to multiply by.
        constexpr void operator*=(const T &value) noexcept
        {
            first *= value;
            second *= value;
        }

        /// @brief Divide both elements of the pair by a value.
        /// @param value The value to divide by.
        constexpr void operator/=(const T &value) noexcept
        {
            first /= value;
            second /= value;
        }

        ~pair_t() = default;
    };

    /// @brief A class representing a pair of values of different types.
    /// @tparam T1
    /// @tparam T2
    template <typename T1, typename T2>
    class pair__t
    {
    private:
        T1 first;
        T2 second;

    public:
        /// @brief Default constructor that initializes both elements to their default values.
        constexpr pair__t() noexcept
        {
            first = T1();
            second = T2();
        }

        /// @brief Copy constructor that initializes the pair with another pair.
        /// @param other The other pair to copy from.
        constexpr pair__t(const pair__t<T1, T2> &other) noexcept
        {
            first = other.first;
            second = other.second;
        }

        /// @brief Constructor that initializes the first element with a given value.
        /// @param value The value to initialize the first element with.
        constexpr pair__t(const T1 &value) noexcept { first = value; }

        /// @brief Constructor that initializes the second element with a given value.
        /// @param value The value to initialize the second element with.
        constexpr pair__t(const T2 &value) noexcept { second = value; }

        /// @brief Constructor that initializes both elements with given values.
        /// @param value1 The value to initialize the first element with.
        /// @param value2 The value to initialize the second element with.
        constexpr pair__t(const T1 &value1, const T2 &value2) noexcept
        {
            first = value1;
            second = value2;
        }

        /// @brief Copy constructor that initializes the pair with another pair.
        /// @param other The other pair to copy from.
        constexpr void set() noexcept
        {
            first = T1();
            second = T2();
        }

        /// @brief set both elements of the pair to the values from another pair.
        /// @param other the other pair to copy values from.
        constexpr void set(const pair__t<T1, T2> &other) noexcept
        {
            first = other.first;
            second = other.second;
        }

        /// @brief set the first element of the pair.
        /// @param value the value to set the first element to.
        constexpr void set(const T1 &value) noexcept { first = value; }

        /// @brief set the second element of the pair.
        /// @param value the value to set the second element to.
        constexpr void set(const T2 &value) noexcept { second = value; }

        /// @brief set both elements of the pair to the given values.
        /// @param value1 the value to set the first element to.
        /// @param value2 the value to set the second element to.
        constexpr void set(const T1 &value1, const T2 &value2) noexcept
        {
            first = value1;
            second = value2;
        }

        /// @brief get the pair.
        /// @return the pair itself.
        constexpr pair__t get() noexcept { return *this; }

        /// @brief get one of the elements of the pair based on position.
        /// @param position if true, get the first element; if false, get the second.
        /// @return the requested element.
        template <typename T>
        T &get(bool position) noexcept
        {
            if (position)
                return static_cast<T>(first);
            else
                return static_cast<T>(second);
        }

        /// @brief swap the two elements of the pair.
        constexpr void swap() noexcept
        {
            T2 swap_v = static_cast<T2>(first);
            first = static_cast<T1>(second);
            second = swap_v;
        }

        /// @brief swap the contents of this pair with another.
        /// @param other the pair to swap contents with.
        constexpr void swap(pair__t<T1, T2> &other) noexcept
        {
            std::swap(first, other.first);
            std::swap(second, other.second);
        }

        /// @brief Increment both elements of the pair.
        constexpr void operator++() noexcept
        {
            ++first;
            ++second;
        }

        /// @brief Decrement both elements of the pair.
        constexpr void operator--() noexcept
        {
            --first;
            --second;
        }

        /// @brief Assign the values from another pair to this pair.
        /// @param other The other pair to assign values from.
        constexpr void operator=(const pair__t<T1, T2> &other) noexcept
        {
            first = other.first;
            second = other.second;
        }

        /// @brief Assign the value to the first element of the pair.
        /// @param value The value to assign to the first element.
        constexpr void operator=(const T1 &value) noexcept { first = value; }

        /// @brief Assign the value to the second element of the pair.
        /// @param value The value to assign to the second element.
        constexpr void operator=(const T2 &value) noexcept { second = value; }

        /// @brief Check if both elements of the pair are equal to the corresponding elements of another pair.
        /// @param other The other pair to compare with.
        constexpr bool operator==(const pair__t<T1, T2> &other) noexcept
        {
            return first == other.first && second == other.second;
        }

        /// @brief Check if the first element of the pair is equal to the given value.
        /// @param value The value to compare with.
        constexpr bool operator==(const T1 &value) noexcept { return first == value; }

        /// @brief Check if the second element of the pair is equal to the given value.
        /// @param value The value to compare with.
        constexpr bool operator==(const T2 &value) noexcept { return second == value; }

        /// @brief Check if the first element of the pair is not equal to the given value.
        /// @param value the value to compare with.
        /// @return true if the first element is not equal to the given value, false otherwise.
        constexpr bool operator!=(const T1 &value) noexcept { return first != value; }

        /// @brief Check if the second element of the pair is not equal to the given value.
        /// @param value the value to compare with.
        /// @return true if the second element is not equal to the given value, false otherwise.
        constexpr bool operator!=(const T2 &value) noexcept { return second != value; }

        /// @brief Check if both elements of the pair are not equal to the corresponding elements of another pair.
        /// @param other The other pair to compare with.
        /// @return true if both elements are not equal to the corresponding elements of the other pair, false otherwise.
        constexpr bool operator!=(const pair__t<T1, T2> &other) noexcept
        {
            return first != other.first && second != other.second;
        }

        /// @brief Add the given value to the first element of the pair.
        /// @param value The value to add.
        /// @return The result of adding the value to the first element.
        constexpr T1 operator+(const T1 &value) noexcept { return first + value; }

        /// @brief Add the given value to the second element of the pair.
        /// @param value The value to add.
        /// @return The result of adding the value to the second element.
        constexpr T2 operator+(const T2 &value) noexcept { return second + value; }

        /// @brief Add another pair to this pair.
        /// @param other The other pair to add.
        /// @return The result of adding the other pair to this pair.
        constexpr pair__t<T1, T2> operator+(const pair__t<T1, T2> &other) noexcept
        {
            return pair__t<T1, T2>(first + other.first, second + other.second);
        }

        /// @brief Add the given value to both elements of the pair.
        /// @param value The value to add.
        constexpr void operator+=(const T1 &value) noexcept { first += value; }

        /// @brief Add the given value to the second element of the pair.
        /// @param value The value to add.
        constexpr void operator+=(const T2 &value) noexcept { second += value; }

        /// @brief Add another pair to this pair.
        /// @param other The other pair to add.
        constexpr void operator+=(const pair__t<T1, T2> &other) noexcept
        {
            first += other.first;
            second += other.second;
        }

        /// @brief Subtract the given value from the first element of the pair.
        /// @param value The value to subtract.
        /// @return The result of subtracting the value from the first element.
        constexpr T1 operator-(const T1 &value) noexcept { return first - value; }

        /// @brief Subtract the given value from the second element of the pair.
        /// @param value The value to subtract.
        /// @return The result of subtracting the value from the second element.
        constexpr T2 operator-(const T2 &value) noexcept { return second - value; }

        /// @brief Subtract another pair from this pair.
        /// @param other The other pair to subtract.
        /// @return The result of subtracting the other pair from this pair.
        constexpr pair__t<T1, T2> operator-(const pair__t<T1, T2> &other) noexcept
        {
            return pair__t<T1, T2>(first - other.first, second - other.second);
        }

        /// @brief Subtract the given value from the first element of the pair.
        /// @param value The value to subtract.
        constexpr void operator-=(const T1 &value) noexcept { first -= value; }

        /// @brief Subtract the given value from the second element of the pair.
        /// @param value The value to subtract.
        constexpr void operator-=(const T2 &value) noexcept { second -= value; }

        /// @brief Subtract another pair from this pair.
        /// @param other The other pair to subtract.
        constexpr void operator-=(const pair__t<T1, T2> &other) noexcept
        {
            first -= other.first;
            second -= other.second;
        }

        /// @brief Multiply the first element of the pair by the given value.
        /// @param value The value to multiply by.
        /// @return The result of multiplying the first element by the value.
        constexpr T1 operator*(const T1 &value) noexcept { return first * value; }

        /// @brief Multiply the second element of the pair by the given value.
        /// @param value The value to multiply by.
        /// @return The result of multiplying the second element by the value.
        constexpr T2 operator*(const T2 &value) noexcept { return second * value; }

        /// @brief Multiply this pair by another pair.
        /// @param other The other pair to multiply by.
        /// @return The result of multiplying this pair by the other pair.
        constexpr pair__t<T1, T2> operator*(const pair__t<T1, T2> &other) noexcept
        {
            return pair__t<T1, T2>(first * other.first, second * other.second);
        }

        /// @brief Multiply the first element of the pair by the given value.
        /// @param value The value to multiply by.
        constexpr void operator*=(const T1 &value) noexcept { first *= value; }

        /// @brief Multiply the second element of the pair by the given value.
        /// @param value The value to multiply by.
        constexpr void operator*=(const T2 &value) noexcept { second *= value; }

        /// @brief Multiply this pair by another pair.
        /// @param other The other pair to multiply by.
        constexpr void operator*=(const pair__t<T1, T2> &other) noexcept
        {
            first *= other.first;
            second *= other.second;
        }

        /// @brief Divide the first element of the pair by the given value.
        /// @param value The value to divide by.
        /// @return The result of dividing the first element by the value.
        constexpr T1 operator/(const T1 &value) noexcept { return first / value; }

        /// @brief Divide the second element of the pair by the given value.
        /// @param value The value to divide by.
        /// @return The result of dividing the second element by the value.
        constexpr T2 operator/(const T2 &value) noexcept { return second / value; }

        /// @brief Divide this pair by another pair.
        /// @param other The other pair to divide by.
        /// @return The result of dividing this pair by the other pair.
        constexpr pair__t<T1, T2> operator/(const pair__t<T1, T2> &other) noexcept
        {
            return pair__t<T1, T2>(first / other.first, second / other.second);
        }

        /// @brief Divide the first element of the pair by the given value.
        /// @param value The value to divide by.
        constexpr void operator/=(const T1 &value) noexcept { first /= value; }

        /// @brief Divide the second element of the pair by the given value.
        /// @param value The value to divide by.
        constexpr void operator/=(const T2 &value) noexcept { second /= value; }

        /// @brief Divide this pair by another pair.
        /// @param other The other pair to divide by.
        constexpr void operator/=(const pair__t<T1, T2> &other) noexcept
        {
            first /= other.first;
            second /= other.second;
        }

        /// @brief Destructor for the pair__t class.
        ~pair__t() = default;
    };
}
#endif // OPENUDT___UDT_PAIR_HPP