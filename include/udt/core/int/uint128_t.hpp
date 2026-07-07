#include <iomanip>
#include <cstdint>
#include <climits>
#include <stdexcept>

#pragma once
#ifndef OPENUDT___CORE___INT_UINT128_HPP
#define OPENUDT___CORE___INT_UINT128_HPP

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

        /// @brief Subtracts an int value from the current value.
        ///
        /// @param num The value to subtract.
        /// @throw std::underflow_error if the result would be below zero.
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

        /// @brief Subtracts a long value from the current value.
        ///
        /// @param num The value to subtract.
        /// @throw std::underflow_error if the result would be below zero.
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

        /// @brief Subtracts a long long value from the current value.
        ///
        /// @param num The value to subtract.
        /// @throw std::underflow_error if the result would be below zero.
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

        /// @brief Subtracts a floating-point value from the current value.
        ///
        /// @param num The value to subtract.
        /// @throw std::underflow_error if the result would be below zero.
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

        /// @brief Subtracts a double-precision value from the current value.
        ///
        /// @param num The value to subtract.
        /// @throw std::underflow_error if the result would be below zero.
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

        /// @brief Multiplies the current value by a character.
        ///
        /// @param c The multiplier.
        /// @throw std::overflow_error if the result exceeds the representable range.
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

        /// @brief Multiplies the current value by a short integer.
        ///
        /// @param num The multiplier.
        /// @throw std::overflow_error if the result exceeds the representable range.
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

        /// @brief Multiplies the current value by an int.
        ///
        /// @param num The multiplier.
        /// @throw std::overflow_error if the result exceeds the representable range.
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

        /// @brief Multiplies the current value by a long integer.
        ///
        /// @param num The multiplier.
        /// @throw std::overflow_error if the result exceeds the representable range.
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

        /// @brief Multiplies the current value by a long long integer.
        ///
        /// @param num The multiplier.
        /// @throw std::overflow_error if the result exceeds the representable range.
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

        /// @brief Multiplies the current value by a floating-point value.
        ///
        /// @param num The multiplier.
        /// @throw std::overflow_error if the result exceeds the representable range.
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

        /// @brief Multiplies the current value by a double-precision value.
        ///
        /// @param num The multiplier.
        /// @throw std::overflow_error if the result exceeds the representable range.
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

        /// @brief Divides the current value by a character.
        ///
        /// @param c The divisor.
        /// @throw std::invalid_argument if the divisor is zero.
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

        /// @brief Divides the current value by a short integer.
        ///
        /// @param num The divisor.
        /// @throw std::invalid_argument if the divisor is zero.
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

        /// @brief Divides the current value by an int.
        ///
        /// @param num The divisor.
        /// @throw std::invalid_argument if the divisor is zero.
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

        /// @brief Divides the current value by a long integer.
        ///
        /// @param num The divisor.
        /// @throw std::invalid_argument if the divisor is zero.
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

        /// @brief Divides the current value by a long long integer.
        ///
        /// @param num The divisor.
        /// @throw std::invalid_argument if the divisor is zero.
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

        /// @brief Divides the current value by a floating-point value.
        ///
        /// @param num The divisor.
        /// @throw std::invalid_argument if the divisor is zero.
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

        /// @brief Divides the current value by a double-precision value.
        ///
        /// @param num The divisor.
        /// @throw std::invalid_argument if the divisor is zero.
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

        /// @brief Increments the current value by one.
        ///
        /// @throw std::overflow_error if the value is already at the maximum representable value.
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

        /// @brief Decrements the current value by one.
        ///
        /// @throw std::underflow_error if the value is already zero.
        void operator--()
        {
            if (lower_p == 0 && upper_p == 0)
                throw std::underflow_error("Underflow error: Attempt to subtract from zero.");
            if (upper_p == 0)
                lower_p--;
            else
                upper_p--;
        }

        /// @brief Compares this value to another uint128_t instance.
        ///
        /// @param other The value to compare with.
        /// @return true if both parts are equal, false otherwise.
        constexpr bool operator==(const uint128_t &other) const noexcept { return (lower_p == other.lower_p) && (upper_p == other.upper_p); }

        /// @brief Compares this value to a short integer.
        ///
        /// @param num The value to compare with.
        /// @return true if the value is equal to num, false otherwise.
        constexpr bool operator==(short num) const noexcept { return (lower_p == static_cast<uint64_t>(num)) && (upper_p == 0); }

        /// @brief Compares this value to an int.
        ///
        /// @param num The value to compare with.
        /// @return true if the value is equal to num, false otherwise.
        constexpr bool operator==(int num) const noexcept { return (lower_p == static_cast<uint64_t>(num)) && (upper_p == 0); }

        /// @brief Compares this value to a float.
        ///
        /// @param num The value to compare with.
        /// @return true if the value is equal to num, false otherwise.
        constexpr bool operator==(float num) const noexcept { return (lower_p == static_cast<uint64_t>(num)) && (upper_p == 0); }

        /// @brief Compares this value to a double.
        ///
        /// @param num The value to compare with.
        /// @return true if the value is equal to num, false otherwise.
        constexpr bool operator==(double num) const noexcept { return (lower_p == static_cast<uint64_t>(num)) && (upper_p == 0); }

        /// @brief Compares this value to a character.
        ///
        /// @param num The value to compare with.
        /// @return true if the value is equal to num, false otherwise.
        constexpr bool operator==(char num) const noexcept { return (lower_p == static_cast<uint64_t>(num)) && (upper_p == 0); }

        /// @brief Compares this value to a short integer for inequality.
        ///
        /// @param num The value to compare with.
        /// @return true if the value is not equal to num, false otherwise.
        constexpr bool operator!=(short num) const noexcept { return !(*this == num); }

        /// @brief Compares this value to an int for inequality.
        ///
        /// @param num The value to compare with.
        /// @return true if the value is not equal to num, false otherwise.
        constexpr bool operator!=(int num) const noexcept { return !(*this == num); }

        /// @brief Compares this value to a float for inequality.
        ///
        /// @param num The value to compare with.
        /// @return true if the value is not equal to num, false otherwise.
        constexpr bool operator!=(float num) const noexcept { return !(*this == num); }

        /// @brief Compares this value to a double for inequality.
        ///
        /// @param num The value to compare with.
        /// @return true if the value is not equal to num, false otherwise.
        constexpr bool operator!=(double num) const noexcept { return !(*this == num); }

        /// @brief Compares this value to a character for inequality.
        ///
        /// @param num The value to compare with.
        /// @return true if the value is not equal to num, false otherwise.
        constexpr bool operator!=(char num) const noexcept { return !(*this == num); }

        /// @brief Compares this value to a short integer for greater-than.
        ///
        /// @param num The value to compare with.
        /// @return true if this value is greater than num, false otherwise.
        constexpr bool operator>(short num) const noexcept
        {
            if (upper_p > 0)
                return true;
            if (upper_p < 0)
                return false;
            return lower_p > static_cast<uint64_t>(num);
        }

        /// @brief Compares this value to an int for greater-than.
        ///
        /// @param num The value to compare with.
        /// @return true if this value is greater than num, false otherwise.
        constexpr bool operator>(int num) const noexcept
        {
            if (upper_p > 0)
                return true;
            if (upper_p < 0)
                return false;
            return lower_p > static_cast<uint64_t>(num);
        }

        /// @brief Compares this value to a float for greater-than.
        ///
        /// @param num The value to compare with.
        /// @return true if this value is greater than num, false otherwise.
        constexpr bool operator>(float num) const noexcept
        {
            if (upper_p > 0)
                return true;
            if (upper_p < 0)
                return false;
            return lower_p > static_cast<uint64_t>(num);
        }

        /// @brief Compares this value to a double for greater-than.
        ///
        /// @param num The value to compare with.
        /// @return true if this value is greater than num, false otherwise.
        constexpr bool operator>(double num) const noexcept
        {
            if (upper_p > 0)
                return true;
            if (upper_p < 0)
                return false;
            return lower_p > static_cast<uint64_t>(num);
        }

        /// @brief Compares this value to a character for greater-than.
        ///
        /// @param c The value to compare with.
        /// @return true if this value is greater than c, false otherwise.
        constexpr bool operator>(char c) const noexcept
        {
            if (upper_p > 0)
                return true;
            if (upper_p < 0)
                return false;
            return lower_p > static_cast<uint64_t>(c);
        }

        /// @brief Compares this value to a short integer for less-than.
        ///
        /// @param num The value to compare with.
        /// @return true if this value is less than num, false otherwise.
        constexpr bool operator<(short num) const noexcept
        {
            if (upper_p < 0)
                return true;
            if (upper_p > 0)
                return false;
            return lower_p < static_cast<uint64_t>(num);
        }

        /// @brief Compares this value to an int for less-than.
        ///
        /// @param num The value to compare with.
        /// @return true if this value is less than num, false otherwise.
        constexpr bool operator<(int num) const noexcept
        {
            if (upper_p < 0)
                return true;
            if (upper_p > 0)
                return false;
            return lower_p < static_cast<uint64_t>(num);
        }

        /// @brief Compares this value to a float for less-than.
        ///
        /// @param num The value to compare with.
        /// @return true if this value is less than num, false otherwise.
        constexpr bool operator<(float num) const noexcept
        {
            if (upper_p < 0)
                return true;
            if (upper_p > 0)
                return false;
            return lower_p < static_cast<uint64_t>(num);
        }

        /// @brief Compares this value to a double for less-than.
        ///
        /// @param num The value to compare with.
        /// @return true if this value is less than num, false otherwise.
        constexpr bool operator<(double num) const noexcept
        {
            if (upper_p < 0)
                return true;
            if (upper_p > 0)
                return false;
            return lower_p < static_cast<uint64_t>(num);
        }

        /// @brief Compares this value to a character for less-than.
        ///
        /// @param c The value to compare with.
        /// @return true if this value is less than c, false otherwise.
        constexpr bool operator<(char c) const noexcept
        {
            if (upper_p < 0)
                return true;
            if (upper_p > 0)
                return false;
            return lower_p < static_cast<uint64_t>(c);
        }

        /// @brief Compares this value to a short integer for greater-or-equal.
        ///
        /// @param num The value to compare with.
        /// @return true if this value is greater than or equal to num, false otherwise.
        constexpr bool operator>=(short num) const noexcept { return !(*this < num); }

        /// @brief Compares this value to an int for greater-or-equal.
        ///
        /// @param num The value to compare with.
        /// @return true if this value is greater than or equal to num, false otherwise.
        constexpr bool operator>=(int num) const noexcept { return !(*this < num); }

        /// @brief Compares this value to a float for greater-or-equal.
        ///
        /// @param num The value to compare with.
        /// @return true if this value is greater than or equal to num, false otherwise.
        constexpr bool operator>=(float num) const noexcept { return !(*this < num); }

        /// @brief Compares this value to a double for greater-or-equal.
        ///
        /// @param num The value to compare with.
        /// @return true if this value is greater than or equal to num, false otherwise.
        constexpr bool operator>=(double num) const noexcept { return !(*this < num); }

        /// @brief Compares this value to a character for greater-or-equal.
        ///
        /// @param c The value to compare with.
        /// @return true if this value is greater than or equal to c, false otherwise.
        constexpr bool operator>=(char c) const noexcept { return !(*this < c); }

        /// @brief Compares this value to a short integer for less-or-equal.
        ///
        /// @param num The value to compare with.
        /// @return true if this value is less than or equal to num, false otherwise.
        constexpr bool operator<=(short num) const noexcept { return !(*this > num); }

        /// @brief Compares this value to an int for less-or-equal.
        ///
        /// @param num The value to compare with.
        /// @return true if this value is less than or equal to num, false otherwise.
        constexpr bool operator<=(int num) const noexcept { return !(*this > num); }

        /// @brief Compares this value to a float for less-or-equal.
        ///
        /// @param num The value to compare with.
        /// @return true if this value is less than or equal to num, false otherwise.
        constexpr bool operator<=(float num) const noexcept { return !(*this > num); }

        /// @brief Compares this value to a double for less-or-equal.
        ///
        /// @param num The value to compare with.
        /// @return true if this value is less than or equal to num, false otherwise.
        constexpr bool operator<=(double num) const noexcept { return !(*this > num); }

        /// @brief Compares this value to a character for less-or-equal.
        ///
        /// @param c The value to compare with.
        /// @return true if this value is less than or equal to c, false otherwise.
        constexpr bool operator<=(char c) const noexcept { return !(*this > c); }
    };
}

#endif // OPENUDT___CORE___INT_UINT128_HPP