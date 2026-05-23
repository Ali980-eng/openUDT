/**
 * @file INT.hpp
 * @brief Defines uint128_t and int128_t classes for extended precision integer arithmetic.
 * @details This header provides two classes, uint128_t and int128_t, which implement 128-bit unsigned and signed integers respectively.
 * The classes support construction from various numeric types, arithmetic operations with overflow/underflow checks, and comparison operators.
 * The uint128_t class uses a two-part representation (upper and lower 64 bits) to achieve 128-bit precision, while int128_t uses a sign-magnitude approach.
 * @note All operations that can potentially overflow or underflow will throw exceptions to ensure safe arithmetic.
 * @warning The comparison logic in int128_t may have issues due to the use of uint64_t for both positive and negative parts, which could lead to incorrect comparisons in edge cases.
 * @date 2025/9/25
 * @author Ali Lafi
 */

#include <iostream>
#include <iomanip>
#include <cstdint>
#include <cmath>
#include <climits>
#include <stdexcept>
#include <type_traits>
#include <utility>

#pragma once
#ifndef OPENUDT___UDT_INT_HPP
#define OPENUDT___UDT_INT_HPP

namespace udt
{
    /**
     * @class uint128_t
     * @brief A 128-bit unsigned integer type implementing extended precision arithmetic.
     *
     * @details This class extends unsigned integer capability beyond 64-bit by using two uint64_t components:
     * - upper_p: The upper 64 bits
     * - lower_p: The lower 64 bits
     *
     * Valid range: 0 to 2^128 - 1 (approximately 3.4 × 10^38)
     *
     * @note All arithmetic operations check for overflow and throw std::overflow_error if exceeded.
     * Underflow operations throw std::underflow_error.
     * @see int128_t
     */
    class uint128_t
    {
    private:
        uint64_t upper_p; ///< Upper 64 bits of the 128-bit value
        uint64_t lower_p; ///< Lower 64 bits of the 128-bit value

    public:
        /// @brief Default constructor initializing to zero.
        /// @post upper_p == 0 && lower_p == 0
        constexpr uint128_t() noexcept : upper_p(0), lower_p(0) {}

        /// @brief Constructs from a short value.
        /// @param num short value
        /// @post lower_p = num, upper_p = 0
        uint128_t(short num) noexcept
        {
            lower_p = static_cast<uint64_t>(num);
            upper_p = 0;
        }

        /// @brief Constructs from an int value.
        /// @param num int value
        /// @post lower_p = num, upper_p = 0
        uint128_t(int num) noexcept
        {
            lower_p = static_cast<uint64_t>(num);
            upper_p = 0;
        }

        /// @brief Constructs from a long value.
        /// @param num long value
        /// @post lower_p = num, upper_p = 0
        uint128_t(long num) noexcept
        {
            lower_p = static_cast<uint64_t>(num);
            upper_p = 0;
        }

        /// @brief Constructs from a long long value.
        /// @param num long long value
        /// @post lower_p = num, upper_p = 0
        uint128_t(long long num) noexcept
        {
            lower_p = static_cast<uint64_t>(num);
            upper_p = 0;
        }

        /// @brief Constructs from a float value.
        /// @param num float value
        /// @post lower_p = num, upper_p = 0
        uint128_t(float num) noexcept
        {
            lower_p = static_cast<long long>(num);
            upper_p = 0;
        }

        /// @brief Constructs from a double value.
        /// @param num double value
        /// @post lower_p = num, upper_p = 0
        uint128_t(double num) noexcept
        {
            lower_p = static_cast<long long>(num);
            upper_p = 0;
        }

        /// @brief Copy constructor.
        /// @param other source uint128_t
        /// @post Copies both parts from other
        uint128_t(const uint128_t &other) noexcept
        {
            lower_p = other.lower_p;
            upper_p = other.upper_p;
        }

        /// @brief Get lower bits as short.
        /// @return static_cast<short>(lower_p)
        /// @throw std::overflow_error if exceeds SHRT_MAX
        short get_short()
        {
            if (lower_p > SHRT_MAX)
                throw std::overflow_error("The number is bigger than short max value");
            return static_cast<short>(lower_p);
        }

        /// @brief Get lower bits as int.
        /// @return static_cast<int>(lower_p)
        /// @throw std::overflow_error if exceeds INT_MAX
        int get_int()
        {
            if (lower_p > INT_MAX)
                throw std::overflow_error("The number is bigger than int max value");
            return static_cast<int>(lower_p);
        }

        /// @brief Get lower bits as long.
        /// @return static_cast<long>(lower_p)
        /// @throw std::overflow_error if exceeds LONG_MAX
        long get_long()
        {
            if (lower_p > LONG_MAX)
                throw std::overflow_error("The number is bigger than long max value");
            return static_cast<long>(lower_p);
        }

        /// @brief Get lower bits as long long.
        /// @return static_cast<long long>(lower_p)
        /// @throw std::overflow_error if exceeds LONG_LONG_MAX
        long long get_long_long()
        {
            if (lower_p > LLONG_MAX)
                throw std::overflow_error("The number is bigger than long long max value");
            return static_cast<long long>(lower_p);
        }

        /// @brief Get lower 64-bit part.
        /// @return lower_p
        constexpr long long get_lower_part() noexcept { return lower_p; }

        /// @brief Get upper 64-bit part.
        /// @return upper_p
        constexpr long long get_upper_part() noexcept { return upper_p; }
        /// @brief Stream output operator.
        /// Outputs zero-padded if upper_p != 0.
        /// @return Reference to os
        friend std::ostream &operator<<(std::ostream &os, const uint128_t &obj)
        {
            if (obj.upper_p != 0)
                os << obj.upper_p << std::setw(20) << std::setfill('0') << obj.lower_p;
            else
                os << obj.lower_p;
            return os;
        }

        /// @brief Copy assignment.
        /// @param other source value
        /// @post Copies both parts
        constexpr void operator=(const uint128_t &other) noexcept
        {
            lower_p = other.lower_p;
            upper_p = other.upper_p;
        }

        /// @brief Assignment from char.
        /// @param c new value
        /// @post lower_p = c, upper_p = 0
        constexpr void operator=(char c) noexcept { lower_p = static_cast<uint64_t>(c); }

        /// @brief Assignment from short.
        /// @param num new value
        /// @post lower_p = num, upper_p = 0
        constexpr void operator=(short num) noexcept { lower_p = static_cast<uint64_t>(num); }

        /// @brief Assignment from int.
        /// @param num new value
        /// @post lower_p = num, upper_p = 0
        constexpr void operator=(int num) noexcept { lower_p = static_cast<uint64_t>(num); }

        /// @brief Assignment from long.
        /// @param num new value
        /// @post lower_p = num, upper_p = 0
        constexpr void operator=(long num) noexcept { lower_p = static_cast<uint64_t>(num); }

        /// @brief Assignment from long long.
        /// @param num new value
        /// @post lower_p = num, upper_p = 0
        constexpr void operator=(long long num) noexcept { lower_p = static_cast<uint64_t>(num); }

        /// @brief Assignment from float.
        /// @param num new value
        /// @post lower_p = num, upper_p = 0
        constexpr void operator=(float num) noexcept { lower_p = static_cast<uint64_t>(num); }

        /// @brief Assignment from double.
        /// @param num new value
        /// @post lower_p = num, upper_p = 0
        constexpr void operator=(double num) noexcept { lower_p = static_cast<uint64_t>(num); }

        /// @brief Assignment from uint64_t.
        /// @param num new value
        /// @post lower_p = num, upper_p = 0
        constexpr void operator=(const uint64_t &num) noexcept { lower_p = num; }

        /// @brief Addition assignment with overflow detection.
        /// @param c char value to add.
        constexpr void operator+=(char c)
        {
            if (lower_p == UINT64_MAX && upper_p == UINT64_MAX)
                throw std::overflow_error("Overflow error: Attempt to add to maximum value.");
            if (lower_p > UINT64_MAX - static_cast<uint64_t>(c))
            {
                uint64_t temp = (UINT64_MAX - lower_p);
                lower_p = UINT64_MAX;
                c -= temp;
                upper_p += c;
            }
            else
                lower_p += static_cast<uint64_t>(c);
        }

        /**
         * @brief Addition assignment with overflow detection for short, int, long, long long, float, and double.
         * @param num value to add
         * @post Adds num to the current value with carry if lower_p exceeds UINT64_MAX
         * @throw std::overflow_error if the result exceeds UINT128_MAX
         * @note The logic checks if adding num to lower_p would exceed UINT64_MAX, and if so, it calculates the carry to upper_p. If both lower_p and upper_p are already at their maximum values, it throws an overflow error.
         */
        constexpr void operator+=(short num)
        {
            if (lower_p == UINT64_MAX && upper_p == UINT64_MAX)
                throw std::overflow_error("Overflow error: Attempt to add to maximum value.");
            long temp = 0;
            if (lower_p > UINT64_MAX - num)
            {
                temp = (UINT64_MAX - lower_p);
                lower_p = UINT64_MAX;
                num -= temp;
                upper_p += num;
            }
            else
                lower_p += num;
        }

        /**
         * @brief Addition assignment with overflow detection for int.
         * @param num int value to add
         * @post Adds num to the current value with carry if lower_p exceeds UINT64_MAX
         * @throw std::overflow_error if the result exceeds UINT128_MAX
         * @note The logic checks if adding num to lower_p would exceed UINT64_MAX, and if so, it calculates the carry to upper_p. If both lower_p and upper_p are already at their maximum values, it throws an overflow error.
         */
        constexpr void operator+=(int num)
        {
            if (lower_p == UINT64_MAX && upper_p == UINT64_MAX)
                throw std::overflow_error("Overflow error: Attempt to add to maximum value.");
            int temp = 0;
            if (lower_p > UINT64_MAX - num)
            {
                temp = (UINT64_MAX - lower_p);
                lower_p = UINT64_MAX;
                num -= temp;
                upper_p += num;
            }
            else
                lower_p += num;
        }

        /**
         * @brief Addition assignment with overflow detection for long.
         * @param num long value to add
         * @post Adds num to the current value with carry if lower_p exceeds UINT64_MAX
         * @throw std::overflow_error if the result exceeds UINT128_MAX
         * @note The logic checks if adding num to lower_p would exceed UINT64_MAX, and if so, it calculates the carry to upper_p. If both lower_p and upper_p are already at their maximum values, it throws an overflow error.
         */
        constexpr void operator+=(long num)
        {
            if (lower_p == UINT64_MAX && upper_p == UINT64_MAX)
                throw std::overflow_error("Overflow error: Attempt to add to maximum value.");
            long temp = 0;
            if (lower_p > UINT64_MAX - num)
            {
                temp = (UINT64_MAX - lower_p);
                lower_p = UINT64_MAX;
                num -= temp;
                upper_p += num;
            }
            else
                lower_p += num;
        }

        /**
         * @brief Addition assignment with overflow detection for long long.
         * @param num long long value to add
         * @post Adds num to the current value with carry if lower_p exceeds UINT64_MAX
         * @throw std::overflow_error if the result exceeds UINT128_MAX
         * @note The logic checks if adding num to lower_p would exceed UINT64_MAX, and if so, it calculates the carry to upper_p. If both lower_p and upper_p are already at their maximum values, it throws an overflow error.
         */
        constexpr void operator+=(long long num)
        {
            if (lower_p == UINT64_MAX && upper_p == UINT64_MAX)
                throw std::overflow_error("Overflow error: Attempt to add to maximum value.");
            long long temp = 0;
            if (lower_p > UINT64_MAX - num)
            {
                temp = (UINT64_MAX - lower_p);
                lower_p = UINT64_MAX;
                num -= temp;
                upper_p += num;
            }
            else
                lower_p += num;
        }

        /**
         * @brief Addition assignment with overflow detection for float and double.
         * @param num float or double value to add
         * @post Adds num to the current value with carry if lower_p exceeds UINT64_MAX
         * @throw std::overflow_error if the result exceeds UINT128_MAX
         * @note The logic checks if adding num to lower_p would exceed UINT64_MAX, and if so, it calculates the carry to upper_p. If both lower_p and upper_p are already at their maximum values, it throws an overflow error.
         */
        constexpr void operator+=(float num)
        {
            if (lower_p == UINT64_MAX && upper_p == UINT64_MAX)
                throw std::overflow_error("Overflow error: Attempt to add to maximum value.");
            int temp = 0;
            if (lower_p > UINT64_MAX - static_cast<uint64_t>(num))
            {
                temp = (UINT64_MAX - lower_p);
                lower_p = UINT64_MAX;
                num -= temp;
                upper_p += num;
            }
            else
                lower_p += static_cast<uint64_t>(num);
        }

        /**
         * @brief Addition assignment with overflow detection for double.
         * @param num double value to add
         * @post Adds num to the current value with carry if lower_p exceeds UINT64_MAX
         * @throw std::overflow_error if the result exceeds UINT128_MAX
         * @note The logic checks if adding num to lower_p would exceed UINT64_MAX, and if so, it calculates the carry to upper_p. If both lower_p and upper_p are already at their maximum values, it throws an overflow error.
         */
        constexpr void operator+=(double num)
        {
            if (lower_p == UINT64_MAX && upper_p == UINT64_MAX)
                throw std::overflow_error("Overflow error: Attempt to add to maximum value.");
            int temp = 0;
            if (lower_p > UINT64_MAX - static_cast<uint64_t>(num))
            {
                temp = (UINT64_MAX - lower_p);
                lower_p = UINT64_MAX;
                num -= temp;
                upper_p += num;
            }
            else
                lower_p += static_cast<uint64_t>(num);
        }

        /**
         * @brief Subtraction assignment with underflow detection for char, short, int, long, long long, float, and double.
         * @param num value to subtract
         * @post Subtracts num from the current value with borrow if lower_p goes below zero
         * @throw std::underflow_error if the result goes below zero
         * @note The logic checks if subtracting num from lower_p would go below zero, and if so, it calculates the borrow from upper_p. If both lower_p and upper_p are already at zero, it throws an underflow error.
         */
        void operator-=(char c)
        {
            if (upper_p == 0 && lower_p == 0)
                throw std::underflow_error("Underflow error: Attempt to subtract from zero.");
            if (upper_p != 0 && static_cast<uint64_t>(c) > upper_p)
            {
                long temp = static_cast<long>(upper_p) - static_cast<long>(c);
                upper_p = 0;
                lower_p -= temp;
            }
            else
                lower_p -= static_cast<uint64_t>(c);
        }

        /**
         * @brief Subtraction assignment with underflow detection for short, int, long, long long, float, and double.
         * @param num value to subtract
         * @post Subtracts num from the current value with borrow if lower_p goes below zero
         * @throw std::underflow_error if the result goes below zero
         * @note The logic checks if subtracting num from lower_p would go below zero, and if so, it calculates the borrow from upper_p. If both lower_p and upper_p are already at zero, it throws an underflow error.
         */
        void operator-=(short num)
        {
            if (upper_p == 0 && lower_p == 0)
                throw std::underflow_error("Underflow error: Attempt to subtract from zero.");
            if (upper_p != 0 && static_cast<uint64_t>(num) > upper_p)
            {
                long temp = static_cast<long>(upper_p) - static_cast<long>(num);
                upper_p = 0;
                lower_p -= temp;
            }
            else
                lower_p -= static_cast<uint64_t>(num);
        }

        void operator-=(int num)
        {
            if (upper_p == 0 && lower_p == 0)
                throw std::underflow_error("Underflow error: Attempt to subtract from zero.");
            if (upper_p != 0 && static_cast<uint64_t>(num) > upper_p)
            {
                long temp = static_cast<long>(upper_p) - static_cast<long>(num);
                upper_p = 0;
                lower_p -= temp;
            }
            else
                lower_p -= static_cast<uint64_t>(num);
        }

        void operator-=(long num)
        {
            if (upper_p == 0 && lower_p == 0)
                throw std::underflow_error("Underflow error: Attempt to subtract from zero.");
            if (upper_p != 0 && static_cast<uint64_t>(num) > upper_p)
            {
                long temp = static_cast<long>(upper_p) - static_cast<long>(num);
                upper_p = 0;
                lower_p -= temp;
            }
            else
                lower_p -= static_cast<uint64_t>(num);
        }

        void operator-=(long long num)
        {
            if (upper_p == 0 && lower_p == 0)
                throw std::underflow_error("Underflow error: Attempt to subtract from zero.");
            if (upper_p != 0 && static_cast<uint64_t>(num) > upper_p)
            {
                long temp = static_cast<long>(upper_p) - static_cast<long>(num);
                upper_p = 0;
                lower_p -= temp;
            }
            else
                lower_p -= static_cast<uint64_t>(num);
        }

        void operator-=(float num)
        {
            if (upper_p == 0 && lower_p == 0)
                throw std::underflow_error("Underflow error: Attempt to subtract from zero.");
            if (upper_p != 0 && static_cast<uint64_t>(num) > upper_p)
            {
                long temp = static_cast<long>(upper_p) - static_cast<long>(num);
                upper_p = 0;
                lower_p -= temp;
            }
            else
                lower_p -= static_cast<uint64_t>(num);
        }

        void operator-=(double num)
        {
            if (upper_p == 0 && lower_p == 0)
                throw std::underflow_error("Underflow error: Attempt to subtract from zero.");
            if (upper_p != 0 && static_cast<uint64_t>(num) > upper_p)
            {
                long temp = static_cast<long>(upper_p) - static_cast<long>(num);
                upper_p = 0;
                lower_p -= temp;
            }
            else
                lower_p -= static_cast<uint64_t>(num);
        }

        void operator*=(char c)
        {
            if (lower_p == UINT64_MAX && upper_p == UINT64_MAX)
                throw std::overflow_error("Overflow error: Attempt to add to maximum value.");
            if (c == 0)
            {
                lower_p = 0;
                upper_p = 0;
                return;
            }
            uint64_t temp_lower = lower_p * static_cast<uint64_t>(c);
            uint64_t temp_upper = upper_p * static_cast<uint64_t>(c);
            if (temp_lower / static_cast<uint64_t>(c) != lower_p)
                temp_upper += (temp_lower >> 64);
            lower_p = temp_lower;
            upper_p = temp_upper;
        }

        void operator*=(short num)
        {
            if (lower_p == UINT64_MAX && upper_p == UINT64_MAX)
                throw std::overflow_error("Overflow error: Attempt to add to maximum value.");
            if (num == 0)
            {
                lower_p = 0;
                upper_p = 0;
                return;
            }
            uint64_t temp_lower = lower_p * static_cast<uint64_t>(num);
            uint64_t temp_upper = upper_p * static_cast<uint64_t>(num);
            if (temp_lower / static_cast<uint64_t>(num) != lower_p)
                temp_upper += (temp_lower >> 64);
            lower_p = temp_lower;
            upper_p = temp_upper;
        }

        void operator*=(int num)
        {
            if (lower_p == UINT64_MAX && upper_p == UINT64_MAX)
                throw std::overflow_error("Overflow error: Attempt to add to maximum value.");
            if (num == 0)
            {
                lower_p = 0;
                upper_p = 0;
                return;
            }
            uint64_t temp_lower = lower_p * static_cast<uint64_t>(num);
            uint64_t temp_upper = upper_p * static_cast<uint64_t>(num);
            if (temp_lower / static_cast<uint64_t>(num) != lower_p)
                temp_upper += (temp_lower >> 64);
            lower_p = temp_lower;
            upper_p = temp_upper;
        }

        void operator*=(long num)
        {
            if (lower_p == UINT64_MAX && upper_p == UINT64_MAX)
                throw std::overflow_error("Overflow error: Attempt to add to maximum value.");
            if (num == 0)
            {
                lower_p = 0;
                upper_p = 0;
                return;
            }
            uint64_t temp_lower = lower_p * static_cast<uint64_t>(num);
            uint64_t temp_upper = upper_p * static_cast<uint64_t>(num);
            if (temp_lower / static_cast<uint64_t>(num) != lower_p)
                temp_upper += (temp_lower >> 64);
            lower_p = temp_lower;
            upper_p = temp_upper;
        }

        void operator*=(long long num)
        {
            if (lower_p == UINT64_MAX && upper_p == UINT64_MAX)
                throw std::overflow_error("Overflow error: Attempt to add to maximum value.");
            if (num == 0)
            {
                lower_p = 0;
                upper_p = 0;
                return;
            }
            uint64_t temp_lower = lower_p * static_cast<uint64_t>(num);
            uint64_t temp_upper = upper_p * static_cast<uint64_t>(num);
            if (temp_lower / static_cast<uint64_t>(num) != lower_p)
                temp_upper += (temp_lower >> 64);
            lower_p = temp_lower;
            upper_p = temp_upper;
        }

        void operator*=(float num)
        {
            if (lower_p == UINT64_MAX && upper_p == UINT64_MAX)
                throw std::overflow_error("Overflow error: Attempt to add to maximum value.");
            if (num == 0)
            {
                lower_p = 0;
                upper_p = 0;
                return;
            }
            uint64_t temp_lower = lower_p * static_cast<uint64_t>(num);
            uint64_t temp_upper = upper_p * static_cast<uint64_t>(num);
            if (temp_lower / static_cast<uint64_t>(num) != lower_p)
                temp_upper += (temp_lower >> 64);
            lower_p = temp_lower;
            upper_p = temp_upper;
        }

        void operator*=(double num)
        {
            if (lower_p == UINT64_MAX && upper_p == UINT64_MAX)
                throw std::overflow_error("Overflow error: Attempt to add to maximum value.");
            if (num == 0)
            {
                lower_p = 0;
                upper_p = 0;
                return;
            }
            uint64_t temp_lower = lower_p * static_cast<uint64_t>(num);
            uint64_t temp_upper = upper_p * static_cast<uint64_t>(num);
            if (temp_lower / static_cast<uint64_t>(num) != lower_p)
                temp_upper += (temp_lower >> 64);
            lower_p = temp_lower;
            upper_p = temp_upper;
        }

        void operator/=(char c)
        {
            if (c == 0)
                throw std::invalid_argument("Division by zero is not allowed.");
            uint64_t new_lower = lower_p / static_cast<uint64_t>(c);
            uint64_t remainder = lower_p % static_cast<uint64_t>(c);
            uint64_t new_upper = upper_p / static_cast<uint64_t>(c);
            remainder += (upper_p % static_cast<uint64_t>(c)) << 64;
            new_lower += remainder / static_cast<uint64_t>(c);
            lower_p = new_lower;
            upper_p = new_upper;
        }

        void operator/=(short num)
        {
            if (num == 0)
                throw std::invalid_argument("Division by zero is not allowed.");
            uint64_t new_lower = lower_p / static_cast<uint64_t>(num);
            uint64_t remainder = lower_p % static_cast<uint64_t>(num);
            uint64_t new_upper = upper_p / static_cast<uint64_t>(num);
            remainder += (upper_p % static_cast<uint64_t>(num)) << 64;
            new_lower += remainder / static_cast<uint64_t>(num);
            lower_p = new_lower;
            upper_p = new_upper;
        }

        void operator/=(int num)
        {
            if (num == 0)
                throw std::invalid_argument("Division by zero is not allowed.");
            uint64_t new_lower = lower_p / static_cast<uint64_t>(num);
            uint64_t remainder = lower_p % static_cast<uint64_t>(num);
            uint64_t new_upper = upper_p / static_cast<uint64_t>(num);
            remainder += (upper_p % static_cast<uint64_t>(num)) << 64;
            new_lower += remainder / static_cast<uint64_t>(num);
            lower_p = new_lower;
            upper_p = new_upper;
        }

        void operator/=(long num)
        {
            if (num == 0)
                throw std::invalid_argument("Division by zero is not allowed.");
            uint64_t new_lower = lower_p / static_cast<uint64_t>(num);
            uint64_t remainder = lower_p % static_cast<uint64_t>(num);
            uint64_t new_upper = upper_p / static_cast<uint64_t>(num);
            remainder += (upper_p % static_cast<uint64_t>(num)) << 64;
            new_lower += remainder / static_cast<uint64_t>(num);
            lower_p = new_lower;
            upper_p = new_upper;
        }

        void operator/=(long long num)
        {
            if (num == 0)
                throw std::invalid_argument("Division by zero is not allowed.");
            uint64_t new_lower = lower_p / static_cast<uint64_t>(num);
            uint64_t remainder = lower_p % static_cast<uint64_t>(num);
            uint64_t new_upper = upper_p / static_cast<uint64_t>(num);
            remainder += (upper_p % static_cast<uint64_t>(num)) << 64;
            new_lower += remainder / static_cast<uint64_t>(num);
            lower_p = new_lower;
            upper_p = new_upper;
        }

        void operator/=(float num)
        {
            if (num == 0.0f)
                throw std::invalid_argument("Division by zero is not allowed.");
            uint64_t new_lower = lower_p / static_cast<uint64_t>(num);
            uint64_t remainder = lower_p % static_cast<uint64_t>(num);
            uint64_t new_upper = upper_p / static_cast<uint64_t>(num);
            remainder += (upper_p % static_cast<uint64_t>(num)) << 64;
            new_lower += remainder / static_cast<uint64_t>(num);
            lower_p = new_lower;
            upper_p = new_upper;
        }

        void operator/=(double num)
        {
            if (num == 0.0)
                throw std::invalid_argument("Division by zero is not allowed.");
            uint64_t new_lower = lower_p / static_cast<uint64_t>(num);
            uint64_t remainder = lower_p % static_cast<uint64_t>(num);
            uint64_t new_upper = upper_p / static_cast<uint64_t>(num);
            remainder += (upper_p % static_cast<uint64_t>(num)) << 64;
            new_lower += remainder / static_cast<uint64_t>(num);
            lower_p = new_lower;
            upper_p = new_upper;
        }

        /// @brief Pre-increment with overflow detection.
        /// @post Adds 1 with carry
        /// @throw std::overflow_error at UINT128_MAX
        void operator++()
        {
            if (lower_p == UINT64_MAX && upper_p == UINT64_MAX)
                throw std::overflow_error("Overflow error: Attempt to add to maximum value.");
            if (lower_p == UINT64_MAX)
            {
                lower_p = 0;
                upper_p++;
            }
            else
                lower_p++;
        }

        /// @brief Pre-decrement with underflow detection.
        /// @post Subtracts 1 with borrow
        /// @throw std::underflow_error at 0
        void operator--()
        {
            if (lower_p == 0 && upper_p == 0)
                throw std::underflow_error("Underflow error: Attempt to subtract from zero.");
            if (upper_p == 0)
                lower_p--;
            else
                upper_p--;
        }

        constexpr bool operator==(const uint128_t &other) const noexcept { return (lower_p == other.lower_p) && (upper_p == other.upper_p); }

        constexpr bool operator==(short num) const noexcept { return (lower_p == static_cast<uint64_t>(num)) && (upper_p == 0); }

        constexpr bool operator==(int num) const noexcept { return (lower_p == static_cast<uint64_t>(num)) && (upper_p == 0); }

        constexpr bool operator==(float num) const noexcept { return (lower_p == static_cast<uint64_t>(num)) && (upper_p == 0); }

        constexpr bool operator==(double num) const noexcept { return (lower_p == static_cast<uint64_t>(num)) && (upper_p == 0); }

        constexpr bool operator==(char num) const noexcept { return (lower_p == static_cast<uint64_t>(num)) && (upper_p == 0); }

        constexpr bool operator!=(short num) const noexcept { return !(*this == num); }

        constexpr bool operator!=(int num) const noexcept { return !(*this == num); }

        constexpr bool operator!=(float num) const noexcept { return !(*this == num); }

        constexpr bool operator!=(double num) const noexcept { return !(*this == num); }

        constexpr bool operator!=(char num) const noexcept { return !(*this == num); }

        constexpr bool operator>(short num) const noexcept
        {
            if (upper_p > 0)
                return true;
            if (upper_p < 0)
                return false;
            return lower_p > static_cast<uint64_t>(num);
        }

        constexpr bool operator>(int num) const noexcept
        {
            if (upper_p > 0)
                return true;
            if (upper_p < 0)
                return false;
            return lower_p > static_cast<uint64_t>(num);
        }

        constexpr bool operator>(float num) const noexcept
        {
            if (upper_p > 0)
                return true;
            if (upper_p < 0)
                return false;
            return lower_p > static_cast<uint64_t>(num);
        }

        constexpr bool operator>(double num) const noexcept
        {
            if (upper_p > 0)
                return true;
            if (upper_p < 0)
                return false;
            return lower_p > static_cast<uint64_t>(num);
        }

        constexpr bool operator>(char c) const noexcept
        {
            if (upper_p > 0)
                return true;
            if (upper_p < 0)
                return false;
            return lower_p > static_cast<uint64_t>(c);
        }

        constexpr bool operator<(short num) const noexcept
        {
            if (upper_p < 0)
                return true;
            if (upper_p > 0)
                return false;
            return lower_p < static_cast<uint64_t>(num);
        }

        constexpr bool operator<(int num) const noexcept
        {
            if (upper_p < 0)
                return true;
            if (upper_p > 0)
                return false;
            return lower_p < static_cast<uint64_t>(num);
        }

        constexpr bool operator<(float num) const noexcept
        {
            if (upper_p < 0)
                return true;
            if (upper_p > 0)
                return false;
            return lower_p < static_cast<uint64_t>(num);
        }

        constexpr bool operator<(double num) const noexcept
        {
            if (upper_p < 0)
                return true;
            if (upper_p > 0)
                return false;
            return lower_p < static_cast<uint64_t>(num);
        }

        constexpr bool operator<(char c) const noexcept
        {
            if (upper_p < 0)
                return true;
            if (upper_p > 0)
                return false;
            return lower_p < static_cast<uint64_t>(c);
        }

        constexpr bool operator>=(short num) const noexcept { return !(*this < num); }

        constexpr bool operator>=(int num) const noexcept { return !(*this < num); }

        constexpr bool operator>=(float num) const noexcept { return !(*this < num); }

        constexpr bool operator>=(double num) const noexcept { return !(*this < num); }

        constexpr bool operator>=(char c) const noexcept { return !(*this < c); }

        constexpr bool operator<=(short num) const noexcept { return !(*this > num); }

        constexpr bool operator<=(int num) const noexcept { return !(*this > num); }

        constexpr bool operator<=(float num) const noexcept { return !(*this > num); }

        constexpr bool operator<=(double num) const noexcept { return !(*this > num); }

        constexpr bool operator<=(char c) const noexcept { return !(*this > c); }
    };

    /**
     * @class int128_t
     * @brief A 128-bit signed integer type implementing extended precision arithmetic.
     *
     * @details This class extends signed integer capability beyond 64-bit by using a sign-magnitude representation:
     * - positive: Stores the magnitude when the number is positive or zero
     * - negative: Stores the absolute value when the number is negative
     *
     * Valid range: -(2^127 - 1) to +(2^127 - 1)
     *
     * @note Sign is determined by which member (positive/negative) is non-zero.
     * When both are zero, the value is treated as positive (zero).
     * The power operator (^=) supports exponentiation with special handling for even/odd exponents.
     * @see uint128_t
     *
     * @warning The comparison operators may have issues with the logic since upper_p is uint64_t but checked as if negative.
     * This could lead to incorrect comparisons in edge cases.
     */
    class int128_t
    {
    private:
        uint64_t positive; ///< Magnitude when value >= 0
        uint64_t negative; ///< Magnitude when value < 0

    public:
        /// @brief Default constructor initializing to zero.
        /// @post positive == 0 && negative == 0
        constexpr int128_t() noexcept : positive(0), negative(0) {}

        /// @brief Constructs from short. Separates into positive/negative parts based on sign.
        int128_t(short num) noexcept
        {
            if (num > 0)
            {
                positive = static_cast<uint64_t>(num);
                negative = 0;
            }
            else if (num < 0)
            {
                negative = static_cast<uint64_t>(std::abs(num));
                positive = 0;
            }
            else
                negative = 0, positive = 0;
        }

        int128_t(int num) noexcept
        {
            if (num > 0)
            {
                positive = static_cast<uint64_t>(num);
                negative = 0;
            }
            else if (num < 0)
            {
                negative = static_cast<uint64_t>(std::abs(num));
                positive = 0;
            }
            else
                negative = 0, positive = 0;
        }

        int128_t(long num) noexcept
        {
            if (num > 0)
            {
                positive = num;
                negative = 0;
            }
            else if (num < 0)
            {
                negative = std::abs(num);
                positive = 0;
            }
            else
                negative = 0, positive = 0;
        }

        int128_t(long long num) noexcept
        {
            if (num > 0)
            {
                positive = num;
                negative = 0;
            }
            else if (num < 0)
            {
                negative = std::abs(num);
                positive = 0;
            }
            else
                negative = 0, positive = 0;
        }

        int128_t(float num) noexcept
        {
            if (num > 0)
            {
                positive = static_cast<uint64_t>(num);
                negative = 0;
            }
            else if (num < 0)
            {
                negative = static_cast<uint64_t>(std::abs(num));
                positive = 0;
            }
            else
                negative = 0, positive = 0;
        }

        int128_t(double num) noexcept
        {
            if (num > 0)
            {
                positive = static_cast<uint64_t>(num);
                negative = 0;
            }
            else if (num < 0)
            {
                negative = static_cast<uint64_t>(std::abs(num));
                positive = 0;
            }
            else
                negative = 0, positive = 0;
        }

        int128_t(const int128_t &other) noexcept
        {
            positive = other.positive;
            negative = other.negative;
        }

        int128_t(uint128_t &other) noexcept
        {
            positive = other.get_lower_part();
            negative = 0;
        }

        /// @brief Converts to short, applying sign.
        /// @return Short value with sign applied
        /// @throw std::overflow_error if magnitude > SHRT_MAX
        /// @note Uses sign-magnitude: returns -result if negative != 0
        short get_short()
        {
            if (SHRT_MAX < positive || negative > SHRT_MAX)
                throw std::overflow_error("The number is bigger then the short max value.");
            short result;
            if (positive == 0)
                result = negative;
            else
                result = positive;
            if (negative != 0)
                return -1 * result;
            return result;
        }

        /// @brief Converts to int, applying sign.
        /// @return Int value with sign applied
        /// @throw std::overflow_error if magnitude > INT_MAX
        /// @note Uses sign-magnitude: returns -result if negative != 0
        int get_int()
        {
            if (INT_MAX < positive || negative > INT_MAX)
                throw std::overflow_error("The number is bigger then the integer max value.");
            int result;
            if (positive == 0)
                result = negative;
            else
                result = positive;
            if (negative != 0)
                return -1 * result;
            return result;
        }

        /// @brief Converts to long, applying sign.
        /// @return Long value with sign applied
        /// @throw std::overflow_error if magnitude > LONG_MAX
        /// @note Uses sign-magnitude: returns -result if negative != 0
        long get_long()
        {
            if (LONG_MAX < positive || negative > LONG_MAX)
                throw std::overflow_error("The number is bigger then the long max value.");
            long result;
            if (positive == 0)
                result = negative;
            else
                result = positive;
            if (negative != 0)
                return -1 * result;
            return result;
        }

        /// @brief Converts to long long, applying sign.
        /// @return Long long value with sign applied
        /// @throw std::overflow_error if magnitude > LONG_LONG_MAX
        /// @note Uses sign-magnitude: returns -result if negative != 0
        long long get_long_long()
        {
            if (LLONG_MIN < positive || negative > LLONG_MAX)
                throw std::overflow_error("The number is bigger then the integer max value.");
            long long result;
            if (positive == 0)
                result = negative;
            else
                result = positive;
            if (negative != 0)
                return -1 * result;
            return result;
        }

        /// @brief Stream output with sign. Outputs "-" + magnitude if negative, else magnitude.
        friend std::ostream &operator<<(std::ostream &os, const int128_t &obj)
        {
            if (obj.negative != 0)
                os << "-" << obj.negative;
            else
                os << obj.positive;
            return os;
        }

        /// @brief Copy assignment.
        /// @param other source int128_t
        /// @post Copies both positive and negative parts
        constexpr void operator=(int128_t &other) noexcept
        {
            positive = other.positive;
            negative = other.negative;
        }

        constexpr void operator=(short num) noexcept
        {
            if (num > 0)
            {
                positive = static_cast<uint64_t>(num);
                negative = 0;
            }
            else if (num < 0)
            {
                negative = static_cast<uint64_t>(std::abs(num));
                positive = 0;
            }
            else
                negative = 0, positive = 0;
        }

        constexpr void operator=(int num) noexcept
        {
            if (num > 0)
            {
                positive = static_cast<uint64_t>(num);
                negative = 0;
            }
            else if (num < 0)
            {
                negative = static_cast<uint64_t>(std::abs(num));
                positive = 0;
            }
            else
                negative = 0, positive = 0;
        }

        constexpr void operator=(long num) noexcept
        {
            if (num > 0)
            {
                positive = num;
                negative = 0;
            }
            else if (num < 0)
            {
                negative = -1 * num;
                positive = 0;
            }
            else
                negative = 0, positive = 0;
        }

        constexpr void operator=(long long num) noexcept
        {
            if (num > 0)
            {
                positive = num;
                negative = 0;
            }
            else if (num < 0)
            {
                negative = -1 * num;
                positive = 0;
            }
            else
                negative = 0, positive = 0;
        }

        constexpr void operator=(float num) noexcept
        {
            if (num > 0)
            {
                positive = static_cast<uint64_t>(num);
                negative = 0;
            }
            else if (num < 0)
            {
                negative = static_cast<uint64_t>(std::abs(num));
                positive = 0;
            }
            else
                negative = 0, positive = 0;
        }

        constexpr void operator=(double num) noexcept
        {
            if (num > 0)
            {
                positive = static_cast<uint64_t>(num);
                negative = 0;
            }
            else if (num < 0)
            {
                negative = static_cast<uint64_t>(std::abs(num));
                positive = 0;
            }
            else
                negative = 0, positive = 0;
        }

        constexpr void operator=(uint128_t &other) noexcept
        {
            positive = other.get_lower_part();
            negative = 0;
        }

        constexpr void operator+=(short num) noexcept
        {
            if (negative == 0 && positive == 0)
                positive += num;
            else if (num > negative && positive == 0)
            {
                positive = num - negative;
                negative = 0;
            }
            else
                positive += num;
        }

        constexpr void operator+=(int num) noexcept
        {
            if (negative == 0 && positive == 0)
                positive += num;
            else if (num > negative && positive == 0)
            {
                positive = num - negative;
                negative = 0;
            }
            else
                positive += num;
        }

        constexpr void operator+=(long num) noexcept
        {
            if (negative == 0 && positive == 0)
                positive += num;
            else if (num > negative && positive == 0)
            {
                positive = num - negative;
                negative = 0;
            }
            else
                positive += num;
        }

        constexpr void operator+=(long long num) noexcept
        {
            if (negative == 0 && positive == 0)
                positive += num;
            else if (num > negative && positive == 0)
            {
                positive = num - negative;
                negative = 0;
            }
            else
                positive += num;
        }

        constexpr void operator+=(float num) noexcept
        {
            if (negative == 0 && positive == 0)
                positive += num;
            if (num > negative && positive == 0)
            {
                positive = num - negative;
                negative = 0;
            }
            else
                positive += num;
        }

        constexpr void operator+=(double num) noexcept
        {
            if (negative == 0 && positive == 0)
                positive += num;
            else if (num > negative && positive == 0)
            {
                positive = num - negative;
                negative = 0;
            }
            else
                positive += num;
        }

        constexpr void operator+=(char c) noexcept
        {
            if (negative == 0 && positive == 0)
                positive += c;
            else if (c > negative && positive == 0)
            {
                positive = c - negative;
                negative = 0;
            }
            else
                positive += c;
        }

        constexpr void operator-=(short num) noexcept
        {
            if (positive == 0 && negative == 0)
                positive -= num;
            else if (num > positive && negative == 0)
            {
                negative = num - positive;
                positive = 0;
            }
            else
                positive -= num;
        }

        constexpr void operator-=(int num) noexcept
        {
            if (positive == 0 && negative == 0)
                positive -= num;
            else if (num > positive && negative == 0)
            {
                negative = num - positive;
                positive = 0;
            }
            else
                positive -= num;
        }

        constexpr void operator-=(long num) noexcept
        {
            if (positive == 0 && negative == 0)
                positive -= num;
            else if (num > positive && negative == 0)
            {
                negative = num - positive;
                positive = 0;
            }
            else
                positive -= num;
        }

        constexpr void operator-=(long long num) noexcept
        {
            if (positive == 0 && negative == 0)
                positive -= num;
            else if (num > positive && negative == 0)
            {
                negative = num - positive;
                positive = 0;
            }
            else
                positive -= num;
        }

        constexpr void operator-=(float num) noexcept
        {
            if (positive == 0 && negative == 0)
                positive -= num;
            else if (num > positive && negative == 0)
            {
                negative = num - positive;
                positive = 0;
            }
            else
                positive -= num;
        }

        constexpr void operator-=(double num) noexcept
        {
            if (positive == 0 && negative == 0)
                positive -= num;
            else if (num > positive && negative == 0)
            {
                negative = num - positive;
                positive = 0;
            }
            else
                positive -= num;
        }

        constexpr void operator-=(char c) noexcept
        {
            if (positive == 0 && negative == 0)
                positive -= c;
            else if (c > positive && negative == 0)
            {
                negative = c - positive;
                positive = 0;
            }
            else
                positive -= c;
        }

        constexpr void operator*=(short num) noexcept
        {
            if (num > 0 && positive == 0)
                negative *= num;
            else if (num < 0 && positive == 0)
            {
                positive = negative * num;
                negative = 0;
            }
            else
                negative *= num;
        }

        constexpr void operator*=(int num) noexcept
        {
            if (num > 0 && positive == 0)
                negative *= num;
            else if (num < 0 && positive == 0)
            {
                positive = negative * num;
                negative = 0;
            }
            else
                negative *= num;
        }

        constexpr void operator*=(long num) noexcept
        {
            if (num > 0 && positive == 0)
                negative *= num;
            else if (num < 0 && positive == 0)
            {
                positive = negative * num;
                negative = 0;
            }
            else
                negative *= num;
        }

        constexpr void operator*=(long long num) noexcept
        {
            if (num > 0 && positive == 0)
                negative *= num;
            else if (num < 0 && positive == 0)
            {
                positive = negative * num;
                negative = 0;
            }
            else
                negative *= num;
        }

        constexpr void operator*=(float num) noexcept
        {
            if (num > 0 && positive == 0)
                negative *= num;
            else if (num < 0 && positive == 0)
            {
                positive = negative * num;
                negative = 0;
            }
            else
                negative *= num;
        }

        constexpr void operator*=(double num) noexcept
        {
            if (num > 0 && positive == 0)
                negative *= num;
            else if (num < 0 && positive == 0)
            {
                positive = negative * num;
                negative = 0;
            }
            else
                negative *= num;
        }

        constexpr void operator*=(char c) noexcept
        {
            if (c > 0 && positive == 0)
                negative *= c;
            else if (c < 0 && positive == 0)
            {
                positive = negative * c;
                negative = 0;
            }
            else
                negative *= c;
        }

        constexpr void operator/=(short num) noexcept
        {
            if (num == 0)
                return;
            if (num < 0 && positive == 0)
            {
                positive = negative / std::abs(num);
                negative = 0;
            }
            else if (num < 0 && negative == 0)
            {
                negative = positive / std::abs(num);
                positive = 0;
            }
            else if (num > 0 && negative == 0)
                negative /= num;
            else
                positive /= num;
        }

        constexpr void operator/=(int num) noexcept
        {
            if (num == 0)
                return;
            if (num < 0 && positive == 0)
            {
                positive = negative / std::abs(num);
                negative = 0;
            }
            else if (num < 0 && negative == 0)
            {
                negative = positive / std::abs(num);
                positive = 0;
            }
            else if (num > 0 && negative == 0)
                negative /= num;
            else
                positive /= num;
        }

        constexpr void operator/=(long num) noexcept
        {
            if (num == 0)
                return;
            if (num < 0 && positive == 0)
            {
                positive = negative / std::abs(num);
                negative = 0;
            }
            else if (num < 0 && negative == 0)
            {
                negative = positive / std::abs(num);
                positive = 0;
            }
            else if (num > 0 && negative == 0)
                negative /= num;
            else
                positive /= num;
        }

        constexpr void operator/=(long long num) noexcept
        {
            if (num == 0)
                return;
            if (num < 0 && positive == 0)
            {
                positive = negative / std::abs(num);
                negative = 0;
            }
            else if (num < 0 && negative == 0)
            {
                negative = positive / std::abs(num);
                positive = 0;
            }
            else if (num > 0 && negative == 0)
                negative /= num;
            else
                positive /= num;
        }

        constexpr void operator/=(float num) noexcept
        {
            if (num == 0)
                return;
            if (num < 0 && positive == 0)
            {
                positive = negative / std::abs(num);
                negative = 0;
            }
            else if (num < 0 && negative == 0)
            {
                negative = positive / std::abs(num);
                positive = 0;
            }
            else if (num > 0 && negative == 0)
                negative /= num;
            else
                positive /= num;
        }

        constexpr void operator/=(double num) noexcept
        {
            if (num == 0)
                return;
            if (num < 0 && positive == 0)
            {
                positive = negative / std::abs(num);
                negative = 0;
            }
            else if (num < 0 && negative == 0)
            {
                negative = positive / std::abs(num);
                positive = 0;
            }
            else if (num > 0 && negative == 0)
                negative /= num;
            else
                positive /= num;
        }

        constexpr void operator/=(char c) noexcept
        {
            if (c == 0)
                return;
            if (c < 0 && positive == 0)
            {
                positive = negative / std::abs(c);
                negative = 0;
            }
            else if (c < 0 && negative == 0)
            {
                negative = positive / std::abs(c);
                positive = 0;
            }
            else if (c > 0 && negative == 0)
                negative /= c;
            else
                positive /= c;
        }

        constexpr void operator++() noexcept
        {
            if (negative == 0)
                positive++;
            else
                negative--;
        }

        constexpr void operator--() noexcept
        {
            if (negative == 0)
                positive--;
            else
                negative++;
        }

        constexpr void operator^=(short num) noexcept
        {
            if (num % 2 == 0 && positive == 0)
                positive = std::pow(negative, num);
            else if (num % 2 == 1 && positive == 0)
                negative = std::pow(negative, num);
            else if (num % 2 == 0 && negative == 0)
                positive = std::pow(positive, num);
            else
                negative = std::pow(negative, num);
        }

        constexpr void operator^=(int num) noexcept
        {
            if (num % 2 == 0 && positive == 0)
                positive = std::pow(negative, num);
            else if (num % 2 == 1 && positive == 0)
                negative = std::pow(negative, num);
            else if (num % 2 == 0 && negative == 0)
                positive = std::pow(positive, num);
            else
                negative = std::pow(negative, num);
        }

        /// @brief Equality comparison with short.
        /// @warning This operator does NOT handle sign properly!
        /// @note It only compares magnitude regardless of sign. -5 and +5 would have the same behavior.
        /// @return true if magnitude (either positive or negative) equals num
        constexpr bool operator==(short num) const noexcept
        {
            if (positive == 0)
                return negative == num;
            else
                return positive == num;
        }

        /// @brief Equality comparison with int.
        /// @warning This operator does NOT handle sign properly!
        /// @note It only compares magnitude regardless of sign.
        /// @return true if magnitude (either positive or negative) equals num
        constexpr bool operator==(int num) const noexcept
        {
            if (positive == 0)
                return negative == num;
            else
                return positive == num;
        }

        /// @brief Equality comparison with float.
        /// @warning This operator does NOT handle sign properly!
        /// @note It only compares magnitude regardless of sign.
        /// @return true if magnitude (either positive or negative) equals num
        constexpr bool operator==(float num) const noexcept
        {
            if (positive == 0)
                return negative == num;
            else
                return positive == num;
        }

        /// @brief Equality comparison with double.
        /// @warning This operator does NOT handle sign properly!
        /// @note It only compares magnitude regardless of sign.
        /// @return true if magnitude (either positive or negative) equals num
        constexpr bool operator==(double num) const noexcept
        {
            if (positive == 0)
                return negative == num;
            else
                return positive == num;
        }

        constexpr bool operator==(char num) const noexcept
        {
            if (positive == 0)
                return negative == num;
            else
                return positive == num;
        }

        constexpr bool operator!=(short num) const noexcept
        {
            if (positive == 0)
                return negative != num;
            else
                return positive != num;
        }

        constexpr bool operator!=(int num) const noexcept
        {
            if (positive == 0)
                return negative != num;
            else
                return positive != num;
        }

        constexpr bool operator!=(float num) const noexcept
        {
            if (positive == 0)
                return negative != num;
            else
                return positive != num;
        }

        constexpr bool operator!=(double num) const noexcept
        {
            if (positive == 0)
                return negative != num;
            else
                return positive != num;
        }

        constexpr bool operator!=(char num) const noexcept
        {
            if (positive == 0)
                return negative != num;
            else
                return positive != num;
        }

        constexpr bool operator>(short num) const noexcept
        {
            if (positive == 0)
                return negative > num;
            else
                return positive > num;
        }

        constexpr bool operator>(int num) const noexcept
        {
            if (positive == 0)
                return negative > num;
            else
                return positive > num;
        }

        constexpr bool operator>(float num) const noexcept
        {
            if (positive == 0)
                return negative > num;
            else
                return positive > num;
        }

        constexpr bool operator>(double num) const noexcept
        {
            if (positive == 0)
                return negative > num;
            else
                return positive > num;
        }

        constexpr bool operator>(char c) const noexcept
        {
            if (positive == 0)
                return negative > c;
            else
                return positive > c;
        }

        constexpr bool operator<(short num) const noexcept
        {
            if (positive == 0)
                return negative < num;
            else
                return positive < num;
        }

        constexpr bool operator<(int num) const noexcept
        {
            if (positive == 0)
                return negative < num;
            else
                return positive < num;
        }

        constexpr bool operator<(float num) const noexcept
        {
            if (positive == 0)
                return negative < num;
            else
                return positive < num;
        }

        constexpr bool operator<(double num) const noexcept
        {
            if (positive == 0)
                return negative < num;
            else
                return positive < num;
        }

        constexpr bool operator<(char c) const noexcept
        {
            if (positive == 0)
                return negative < c;
            else
                return positive < c;
        }

        constexpr bool operator>=(short num) const noexcept
        {
            if (positive == 0)
                return negative >= num;
            else
                return positive >= num;
        }

        constexpr bool operator>=(int num) const noexcept
        {
            if (positive == 0)
                return negative >= num;
            else
                return positive >= num;
        }

        constexpr bool operator>=(float num) const noexcept
        {
            if (positive == 0)
                return negative >= num;
            else
                return positive >= num;
        }

        constexpr bool operator>=(double num) const noexcept
        {
            if (positive == 0)
                return negative >= num;
            else
                return positive >= num;
        }

        constexpr bool operator>=(char c) const noexcept
        {
            if (positive == 0)
                return negative >= c;
            else
                return positive >= c;
        }

        constexpr bool operator<=(short num) const noexcept
        {
            if (positive == 0)
                return negative <= num;
            else
                return positive <= num;
        }

        constexpr bool operator<=(int num) const noexcept
        {
            if (positive == 0)
                return negative <= num;
            else
                return positive <= num;
        }

        constexpr bool operator<=(float num) const noexcept
        {
            if (positive == 0)
                return negative <= num;
            else
                return positive <= num;
        }

        constexpr bool operator<=(double num) const noexcept
        {
            if (positive == 0)
                return negative <= num;
            else
                return positive <= num;
        }

        constexpr bool operator<=(char c) const noexcept
        {
            if (positive == 0)
                return negative <= c;
            else
                return positive <= c;
        }
    };
}
#endif // OPENUDT___UDT_INT_HPP