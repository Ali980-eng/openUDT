#pragma once
#ifndef OPENUDT___UDT_PAIR_PAIR__T_HPP
#define OPENUDT___UDT_PAIR_PAIR__T_HPP

namespace udt
{

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

#endif // OPENUDT___UDT_PAIR_PAIR__T_HPP