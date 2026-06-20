#include "uint128_t.hpp"
#include <cmath>

#pragma once
#ifndef OPENUDT___CORE___INT_INT128_HPP
#define OPENUDT___CORE___INT_INT128_HPP

namespace udt
{
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

#endif // OPENUDT___CORE___INT_INT128_HPP