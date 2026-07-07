#include <iomanip>
#include <cstdint>
#include <climits>
#include <stdexcept>
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

        /// @brief Constructs an int128_t value from a short integer.
        ///
        /// @param num The source value to represent.
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

        /// @brief Constructs an int128_t value from an int.
        ///
        /// @param num The source value to represent.
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

        /// @brief Constructs an int128_t value from a long integer.
        ///
        /// @param num The source value to represent.
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

        /// @brief Constructs an int128_t value from a long long integer.
        ///
        /// @param num The source value to represent.
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

        /// @brief Constructs an int128_t value from a floating-point number.
        ///
        /// @param num The source value to represent.
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

        /// @brief Constructs an int128_t value from a double-precision floating-point number.
        ///
        /// @param num The source value to represent.
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

        /// @brief Copies another int128_t instance.
        ///
        /// @param other The instance to copy from.
        int128_t(const int128_t &other) noexcept
        {
            positive = other.positive;
            negative = other.negative;
        }
#ifdef OPENUDT___CORE___INT_HPP

        /// @brief Constructs from a uint128_t value when the companion type is available.
        ///
        /// @param other The source unsigned value.
        int128_t(uint128_t &other) noexcept
        {
            positive = other.get_lower_part();
            negative = 0;
        }

        constexpr void operator=(uint128_t &other) noexcept
        {
            positive = other.get_lower_part();
            negative = 0;
        }

#endif // OPENUDT___CORE___INT_HPP

        /// @brief Converts the stored value to a short integer.
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

        /// @brief Converts the stored value to an int.
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

        /// @brief Converts the stored value to a long integer.
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

        /// @brief Converts the stored value to a long long integer.
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

        /// @brief Streams the value to an output stream.
        ///
        /// @param os The output stream.
        /// @param obj The value to serialize.
        /// @return Reference to the output stream.
        friend std::ostream &operator<<(std::ostream &os, const int128_t &obj)
        {
            if (obj.negative != 0)
                os << "-" << obj.negative;
            else
                os << obj.positive;
            return os;
        }

        /// @brief Assigns the value of another int128_t instance.
        ///
        /// @param other The source object.
        constexpr void operator=(int128_t &other) noexcept
        {
            positive = other.positive;
            negative = other.negative;
        }

        /// @brief Assigns a short integer value to this object.
        ///
        /// @param num The source value.
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

        /// @brief Assigns an int value to this object.
        ///
        /// @param num The source value.
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

        /// @brief Assigns a long integer value to this object.
        ///
        /// @param num The source value.
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

        /// @brief Assigns a long long integer value to this object.
        ///
        /// @param num The source value.
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

        /// @brief Assigns a floating-point value to this object.
        ///
        /// @param num The source value.
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

        /// @brief Assigns a double-precision floating-point value to this object.
        ///
        /// @param num The source value.
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

        /// @brief Adds a short integer to the current value.
        ///
        /// @param num The value to add.
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

        /// @brief Adds an int to the current value.
        ///
        /// @param num The value to add.
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

        /// @brief Adds a long integer to the current value.
        ///
        /// @param num The value to add.
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

        /// @brief Adds a long long integer to the current value.
        ///
        /// @param num The value to add.
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

        /// @brief Adds a floating-point value to the current value.
        ///
        /// @param num The value to add.
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

        /// @brief Adds a double-precision value to the current value.
        ///
        /// @param num The value to add.
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

        /// @brief Adds a character value to the current value.
        ///
        /// @param c The value to add.
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

        /// @brief Subtracts a short integer from the current value.
        ///
        /// @param num The value to subtract.
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

        /// @brief Subtracts an int from the current value.
        ///
        /// @param num The value to subtract.
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

        /// @brief Subtracts a long integer from the current value.
        ///
        /// @param num The value to subtract.
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

        /// @brief Subtracts a long long integer from the current value.
        ///
        /// @param num The value to subtract.
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

        /// @brief Subtracts a floating-point value from the current value.
        ///
        /// @param num The value to subtract.
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

        /// @brief Subtracts a double-precision value from the current value.
        ///
        /// @param num The value to subtract.
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

        /// @brief Subtracts a character value from the current value.
        ///
        /// @param c The value to subtract.
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

        /// @brief Multiplies the current value by a short integer.
        ///
        /// @param num The multiplier.
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

        /// @brief Multiplies the current value by an int.
        ///
        /// @param num The multiplier.
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

        /// @brief Multiplies the current value by a long integer.
        ///
        /// @param num The multiplier.
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

        /// @brief Multiplies the current value by a long long integer.
        ///
        /// @param num The multiplier.
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

        /// @brief Multiplies the current value by a floating-point value.
        ///
        /// @param num The multiplier.
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

        /// @brief Multiplies the current value by a double-precision value.
        ///
        /// @param num The multiplier.
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

        /// @brief Multiplies the current value by a character value.
        ///
        /// @param c The multiplier.
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

        /// @brief Divides the current value by a short integer.
        ///
        /// @param num The divisor.
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

        /// @brief Divides the current value by an int.
        ///
        /// @param num The divisor.
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

        /// @brief Divides the current value by a long integer.
        ///
        /// @param num The divisor.
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

        /// @brief Divides the current value by a long long integer.
        ///
        /// @param num The divisor.
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

        /// @brief Divides the current value by a floating-point value.
        ///
        /// @param num The divisor.
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

        /// @brief Divides the current value by a double-precision value.
        ///
        /// @param num The divisor.
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

        /// @brief Divides the current value by a character value.
        ///
        /// @param c The divisor.
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

        /// @brief Increments the current value by one.
        constexpr void operator++() noexcept
        {
            if (negative == 0)
                positive++;
            else
                negative--;
        }

        /// @brief Decrements the current value by one.
        constexpr void operator--() noexcept
        {
            if (negative == 0)
                positive--;
            else
                negative++;
        }

        /// @brief Raises the current value to a short integer exponent.
        ///
        /// @param num The exponent.
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

        /// @brief Raises the current value to an int exponent.
        ///
        /// @param num The exponent.
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

        /// @brief Compares the value with a short integer for equality.
        ///
        /// @warning This operator does not handle sign properly.
        /// @note It compares magnitude rather than the full signed value.
        /// @param num The value to compare with.
        /// @return true if the magnitudes match, false otherwise.
        constexpr bool operator==(short num) const noexcept
        {
            if (positive == 0)
                return negative == num;
            else
                return positive == num;
        }

        /// @brief Compares the value with an int for equality.
        ///
        /// @warning This operator does not handle sign properly.
        /// @note It compares magnitude rather than the full signed value.
        /// @param num The value to compare with.
        /// @return true if the magnitudes match, false otherwise.
        constexpr bool operator==(int num) const noexcept
        {
            if (positive == 0)
                return negative == num;
            else
                return positive == num;
        }

        /// @brief Compares the value with a float for equality.
        ///
        /// @warning This operator does not handle sign properly.
        /// @note It compares magnitude rather than the full signed value.
        /// @param num The value to compare with.
        /// @return true if the magnitudes match, false otherwise.
        constexpr bool operator==(float num) const noexcept
        {
            if (positive == 0)
                return negative == num;
            else
                return positive == num;
        }

        /// @brief Compares the value with a double for equality.
        ///
        /// @warning This operator does not handle sign properly.
        /// @note It compares magnitude rather than the full signed value.
        /// @param num The value to compare with.
        /// @return true if the magnitudes match, false otherwise.
        constexpr bool operator==(double num) const noexcept
        {
            if (positive == 0)
                return negative == num;
            else
                return positive == num;
        }

        /// @brief Compares the value with a character for equality.
        ///
        /// @param num The value to compare with.
        /// @return true if the magnitudes match, false otherwise.
        constexpr bool operator==(char num) const noexcept
        {
            if (positive == 0)
                return negative == num;
            else
                return positive == num;
        }

        /// @brief Compares the value with a short integer for inequality.
        ///
        /// @param num The value to compare with.
        /// @return true if the magnitudes differ, false otherwise.
        constexpr bool operator!=(short num) const noexcept
        {
            if (positive == 0)
                return negative != num;
            else
                return positive != num;
        }

        /// @brief Compares the value with an int for inequality.
        ///
        /// @param num The value to compare with.
        /// @return true if the magnitudes differ, false otherwise.
        constexpr bool operator!=(int num) const noexcept
        {
            if (positive == 0)
                return negative != num;
            else
                return positive != num;
        }

        /// @brief Compares the value with a float for inequality.
        ///
        /// @param num The value to compare with.
        /// @return true if the magnitudes differ, false otherwise.
        constexpr bool operator!=(float num) const noexcept
        {
            if (positive == 0)
                return negative != num;
            else
                return positive != num;
        }

        /// @brief Compares the value with a double for inequality.
        ///
        /// @param num The value to compare with.
        /// @return true if the magnitudes differ, false otherwise.
        constexpr bool operator!=(double num) const noexcept
        {
            if (positive == 0)
                return negative != num;
            else
                return positive != num;
        }

        /// @brief Compares the value with a character for inequality.
        ///
        /// @param num The value to compare with.
        /// @return true if the magnitudes differ, false otherwise.
        constexpr bool operator!=(char num) const noexcept
        {
            if (positive == 0)
                return negative != num;
            else
                return positive != num;
        }

        /// @brief Compares the value to a short integer.
        ///
        /// @param num The value to compare with.
        /// @return true if the value is greater than num, false otherwise.
        constexpr bool operator>(short num) const noexcept
        {
            if (positive == 0)
                return negative > num;
            else
                return positive > num;
        }

        /// @brief Compares the value to an int.
        ///
        /// @param num The value to compare with.
        /// @return true if the value is greater than num, false otherwise.
        constexpr bool operator>(int num) const noexcept
        {
            if (positive == 0)
                return negative > num;
            else
                return positive > num;
        }

        /// @brief Compares the value to a float.
        ///
        /// @param num The value to compare with.
        /// @return true if the value is greater than num, false otherwise.
        constexpr bool operator>(float num) const noexcept
        {
            if (positive == 0)
                return negative > num;
            else
                return positive > num;
        }

        /// @brief Compares the value to a double.
        ///
        /// @param num The value to compare with.
        /// @return true if the value is greater than num, false otherwise.
        constexpr bool operator>(double num) const noexcept
        {
            if (positive == 0)
                return negative > num;
            else
                return positive > num;
        }

        /// @brief Compares the value to a character.
        ///
        /// @param c The value to compare with.
        /// @return true if the value is greater than c, false otherwise.
        constexpr bool operator>(char c) const noexcept
        {
            if (positive == 0)
                return negative > c;
            else
                return positive > c;
        }

        /// @brief Compares the value to a short integer.
        ///
        /// @param num The value to compare with.
        /// @return true if the value is less than num, false otherwise.
        constexpr bool operator<(short num) const noexcept
        {
            if (positive == 0)
                return negative < num;
            else
                return positive < num;
        }

        /// @brief Compares the value to an int.
        ///
        /// @param num The value to compare with.
        /// @return true if the value is less than num, false otherwise.
        constexpr bool operator<(int num) const noexcept
        {
            if (positive == 0)
                return negative < num;
            else
                return positive < num;
        }

        /// @brief Compares the value to a float.
        ///
        /// @param num The value to compare with.
        /// @return true if the value is less than num, false otherwise.
        constexpr bool operator<(float num) const noexcept
        {
            if (positive == 0)
                return negative < num;
            else
                return positive < num;
        }

        /// @brief Compares the value to a double.
        ///
        /// @param num The value to compare with.
        /// @return true if the value is less than num, false otherwise.
        constexpr bool operator<(double num) const noexcept
        {
            if (positive == 0)
                return negative < num;
            else
                return positive < num;
        }

        /// @brief Compares the value to a character.
        ///
        /// @param c The value to compare with.
        /// @return true if the value is less than c, false otherwise.
        constexpr bool operator<(char c) const noexcept
        {
            if (positive == 0)
                return negative < c;
            else
                return positive < c;
        }

        /// @brief Compares the value to a short integer for greater-or-equal.
        ///
        /// @param num The value to compare with.
        /// @return true if the value is greater than or equal to num, false otherwise.
        constexpr bool operator>=(short num) const noexcept
        {
            if (positive == 0)
                return negative >= num;
            else
                return positive >= num;
        }

        /// @brief Compares the value to an int for greater-or-equal.
        ///
        /// @param num The value to compare with.
        /// @return true if the value is greater than or equal to num, false otherwise.
        constexpr bool operator>=(int num) const noexcept
        {
            if (positive == 0)
                return negative >= num;
            else
                return positive >= num;
        }

        /// @brief Compares the value to a float for greater-or-equal.
        ///
        /// @param num The value to compare with.
        /// @return true if the value is greater than or equal to num, false otherwise.
        constexpr bool operator>=(float num) const noexcept
        {
            if (positive == 0)
                return negative >= num;
            else
                return positive >= num;
        }

        /// @brief Compares the value to a double for greater-or-equal.
        ///
        /// @param num The value to compare with.
        /// @return true if the value is greater than or equal to num, false otherwise.
        constexpr bool operator>=(double num) const noexcept
        {
            if (positive == 0)
                return negative >= num;
            else
                return positive >= num;
        }

        /// @brief Compares the value to a character for greater-or-equal.
        ///
        /// @param c The value to compare with.
        /// @return true if the value is greater than or equal to c, false otherwise.
        constexpr bool operator>=(char c) const noexcept
        {
            if (positive == 0)
                return negative >= c;
            else
                return positive >= c;
        }

        /// @brief Compares the value to a short integer for less-or-equal.
        ///
        /// @param num The value to compare with.
        /// @return true if the value is less than or equal to num, false otherwise.
        constexpr bool operator<=(short num) const noexcept
        {
            if (positive == 0)
                return negative <= num;
            else
                return positive <= num;
        }

        /// @brief Compares the value to an int for less-or-equal.
        ///
        /// @param num The value to compare with.
        /// @return true if the value is less than or equal to num, false otherwise.
        constexpr bool operator<=(int num) const noexcept
        {
            if (positive == 0)
                return negative <= num;
            else
                return positive <= num;
        }

        /// @brief Compares the value to a float for less-or-equal.
        ///
        /// @param num The value to compare with.
        /// @return true if the value is less than or equal to num, false otherwise.
        constexpr bool operator<=(float num) const noexcept
        {
            if (positive == 0)
                return negative <= num;
            else
                return positive <= num;
        }

        /// @brief Compares the value to a double for less-or-equal.
        ///
        /// @param num The value to compare with.
        /// @return true if the value is less than or equal to num, false otherwise.
        constexpr bool operator<=(double num) const noexcept
        {
            if (positive == 0)
                return negative <= num;
            else
                return positive <= num;
        }

        /// @brief Compares the value to a character for less-or-equal.
        ///
        /// @param c The value to compare with.
        /// @return true if the value is less than or equal to c, false otherwise.
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