#pragma once
#ifndef OPENUDT___CORE_PAIR_PAIR_T_HPP
#define OPENUDT___CORE_PAIR_PAIR_T_HPP

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

}

#endif // OPENUDT___CORE_PAIR_PAIRs_T_HPP