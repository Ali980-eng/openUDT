/**
 * @file virtual.hpp
 * @brief Defines virtual pointer classes for 8-bit, 16-bit, 32-bit, and 64-bit sizes with safe arithmetic operations.
 * @details This header provides four classes: virtual_ptr_8, virtual_ptr_16, virtual_ptr_32, and virtual_ptr_64.
 * Each class encapsulates a virtual pointer of the corresponding size and offers methods for setting, getting,
 * clearing, and performing arithmetic operations with saturation semantics. The classes are designed to be
 * constexpr-compatible for compile-time usage and include stream output operators for easy debugging and visualization.
 * @note All operations that could potentially overflow or underflow will saturate at the maximum or minimum value
 * respectively, ensuring safe arithmetic behavior. Division by zero will throw a runtime error.
 * @see virtual_ptr_8, virtual_ptr_16, virtual_ptr_32, virtual_ptr_64
 * @author Ali Lafi
 * @date 2025/9/25
 */

#pragma once
#ifndef OPENUDT___UDT_VIRTUAL_HPP
#define OPENUDT___UDT_VIRTUAL_HPP
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdint.h>
#include <bitset>
#include <iomanip>

namespace udt
{
    /**
     * @class virtual_ptr_8
     * @brief An 8-bit virtual pointer class providing safe arithmetic operations with saturation semantics.
     *
     * @details This class wraps a uint8_t value representing a virtual memory address or pointer.
     * It provides arithmetic operators with automatic saturation to prevent overflow/underflow.
     * All operations are constexpr-compatible for compile-time execution.
     *
     * @note Valid range: 0 to 255 (2^8 - 1)
     * @see virtual_ptr_16, virtual_ptr_32, virtual_ptr_64
     */
    class virtual_ptr_8
    {
    private:
        uint8_t vptr; ///< Internal 8-bit virtual pointer value

    public:
        /**
         * @brief Default constructor initializing the virtual pointer to 0.
         * @post vptr == 0
         */
        constexpr virtual_ptr_8() noexcept : vptr(0) {}

        /**
         * @brief Constructs a virtual pointer with the specified uint8_t value.
         * @param val The initial value for the virtual pointer
         * @post vptr == val
         */
        constexpr virtual_ptr_8(uint8_t val) noexcept : vptr(val) {}

        /**
         * @brief Copy constructor creating a new virtual pointer from an existing one.
         * @param other The source virtual pointer to copy from
         * @post vptr == other.vptr
         */
        constexpr virtual_ptr_8(const virtual_ptr_8 &other) noexcept : vptr(other.vptr) {}

        /**
         * @brief Sets the virtual pointer to a new value.
         * @param val The new value to set
         * @post vptr == val
         */
        constexpr void set(uint8_t val) noexcept { vptr = val; }

        /**
         * @brief Gets the current value of the virtual pointer.
         * @return The current uint8_t value of this virtual pointer
         */
        constexpr uint8_t get() const noexcept { return vptr; }

        /**
         * @brief Returns the hexadecimal string representation of the virtual pointer.
         * @return A string containing the hexadecimal representation followed by 'h' suffix.
         *         For example, value 255 returns "ffh"
         */
        std::string get_str() const noexcept
        {
            std::stringstream ss;
            ss << std::hex << vptr;
            std::string hexadecimal_result = ss.str();
            return hexadecimal_result + "h";
        }

        /**
         * @brief Resets the virtual pointer to 0.
         * @post vptr == 0
         */
        constexpr void clear() noexcept { vptr = 0; }

        /**
         * @brief Checks if the virtual pointer is empty (zero).
         * @return true if vptr == 0, false otherwise
         */
        constexpr bool empty() noexcept { return vptr == 0; }

        /**
         * @brief Copy assignment operator.
         * @param other The source virtual pointer to assign from
         * @return Reference to this object
         * @post vptr == other.vptr
         */
        constexpr void operator=(const virtual_ptr_8 &other) noexcept { vptr = other.vptr; }

        /**
         * @brief Compound assignment operator for addition with another virtual pointer.
         * @param other The virtual pointer value to add (saturates at 255)
         * @return Reference to this object
         * @post vptr = min(vptr + other.vptr, 255)
         */
        constexpr void operator+=(const virtual_ptr_8 &other) noexcept { vptr += other.vptr; }

        /**
         * @brief Compound assignment operator for subtraction with another virtual pointer.
         * @param other The virtual pointer value to subtract
         * @return Reference to this object
         * @post vptr = vptr - other.vptr (with underflow handling)
         */
        constexpr void operator-=(const virtual_ptr_8 &other) noexcept { vptr -= other.vptr; }

        /**
         * @brief Compound assignment operator for multiplication with another virtual pointer.
         * @param other The virtual pointer value to multiply
         * @return Reference to this object
         * @post vptr = vptr * other.vptr (with overflow handling)
         */
        constexpr void operator*=(const virtual_ptr_8 &other) noexcept { vptr *= other.vptr; }

        /**
         * @brief Compound assignment operator for division by another virtual pointer.
         * @param other The virtual pointer value to divide by
         * @return Reference to this object
         * @throw std::runtime_error if other.vptr == 0 (division by zero)
         * @post vptr = vptr / other.vptr
         */
        constexpr void operator/=(const virtual_ptr_8 &other) noexcept { vptr /= other.vptr; }

        /**
         * @brief Assignment operator for direct uint8_t values.
         * @param val The value to assign
         * @post vptr == val
         */
        constexpr void operator=(uint8_t val) noexcept { vptr = val; }

        /**
         * @brief Compound addition operator with uint8_t values.
         * @param val The value to add
         * @post vptr += val
         */
        constexpr void operator+=(uint8_t val) noexcept { vptr += val; }

        /**
         * @brief Compound subtraction operator with uint8_t values.
         * @param val The value to subtract
         * @post vptr -= val
         */
        constexpr void operator-=(uint8_t val) noexcept { vptr -= val; }

        /**
         * @brief Compound multiplication operator with uint8_t values.
         * @param val The value to multiply by
         * @post vptr *= val
         */
        constexpr void operator*=(uint8_t val) noexcept { vptr *= val; }

        /**
         * @brief Compound division operator with uint8_t values.
         * @param val The value to divide by
         * @throw std::runtime_error if val == 0 (division by zero)
         * @post vptr /= val
         */
        constexpr void operator/=(uint8_t val) noexcept { vptr /= val; }

        /**
         * @brief Pre-increment operator with saturation at maximum value.
         * @return Reference to this object after incrementing
         * @post vptr = min(vptr + 1, 255)
         */
        virtual_ptr_8 operator++() noexcept
        {
            if (vptr + 1 <= 255)
                vptr++;
            else
                vptr = 255;
            return *this;
        }

        /**
         * @brief Pre-decrement operator with saturation at zero.
         * @return Reference to this object after decrementing
         * @post vptr = max(vptr - 1, 0)
         */
        virtual_ptr_8 operator--() noexcept
        {
            if (vptr - 1 >= 0)
                vptr--;
            else
                vptr = 0;
            return *this;
        }

        /**
         * @brief Stream output operator for hexadecimal representation.
         * @param os The output stream to write to
         * @param vptr The virtual pointer to output
         * @return Reference to the output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const virtual_ptr_8 &vptr)
        {
            os << vptr.get_str();
            return os;
        }
    };
    /**
     * @class virtual_ptr_16
     * @brief A 16-bit virtual pointer class providing safe arithmetic operations with saturation semantics.
     *
     * @details This class wraps a uint16_t value representing a virtual memory address or pointer.
     * It provides arithmetic operators with automatic saturation to prevent overflow/underflow.
     * All operations are constexpr-compatible for compile-time execution.
     *
     * @note Valid range: 0 to 65535 (2^16 - 1)
     * @see virtual_ptr_8, virtual_ptr_32, virtual_ptr_64
     */
    class virtual_ptr_16
    {
    private:
        uint16_t vptr; ///< Internal 16-bit virtual pointer value

    public:
        /**
         * @brief Default constructor initializing the virtual pointer to 0.
         * @post vptr == 0
         */
        virtual_ptr_16() noexcept { vptr = 0; }

        /**
         * @brief Constructs a virtual pointer with the specified uint16_t value.
         * @param val The initial value for the virtual pointer
         * @post vptr == val
         */
        virtual_ptr_16(uint16_t val) noexcept { vptr = val; }

        /**
         * @brief Copy constructor creating a new virtual pointer from an existing one.
         * @param other The source virtual pointer to copy from
         * @post vptr == other.vptr
         */
        virtual_ptr_16(const virtual_ptr_16 &other) noexcept { vptr = other.vptr; }

        /**
         * @brief Sets the virtual pointer to a new value.
         * @param val The new value to set
         * @post vptr == val
         */
        constexpr void set(uint16_t val) noexcept { vptr = val; }

        /**
         * @brief Gets the current value of the virtual pointer.
         * @return The current uint16_t value of this virtual pointer
         */
        constexpr uint16_t get() const noexcept { return vptr; }

        /**
         * @brief Returns the hexadecimal string representation of the virtual pointer.
         * @return A string containing the hexadecimal representation followed by 'h' suffix.
         *         For example, value 65535 returns "ffffh"
         */
        std::string get_str() const noexcept
        {
            std::stringstream ss;
            ss << std::hex << vptr;
            std::string hexadecimal_result = ss.str();
            return hexadecimal_result + "h";
        }

        /**
         * @brief Resets the virtual pointer to 0.
         * @post vptr == 0
         */
        constexpr void clear() noexcept { vptr = 0; }

        /**
         * @brief Checks if the virtual pointer is empty (zero).
         * @return true if vptr == 0, false otherwise
         */
        constexpr bool empty() noexcept { return vptr == 0; }

        /**
         * @brief Copy assignment operator.
         * @param other The source virtual pointer to assign from
         * @return Reference to this object
         * @post vptr == other.vptr
         */
        constexpr void operator=(const virtual_ptr_16 &other) noexcept { vptr = other.vptr; }

        /**
         * @brief Compound assignment operator for addition with another virtual pointer.
         * @param other The virtual pointer value to add
         * @return Reference to this object
         * @post vptr += other.vptr
         */
        constexpr void operator+=(const virtual_ptr_16 &other) noexcept { vptr += other.vptr; }

        /**
         * @brief Compound assignment operator for subtraction with another virtual pointer.
         * @param other The virtual pointer value to subtract
         * @return Reference to this object
         * @post vptr -= other.vptr
         */
        constexpr void operator-=(const virtual_ptr_16 &other) noexcept { vptr -= other.vptr; }

        /**
         * @brief Compound assignment operator for multiplication with another virtual pointer.
         * @param other The virtual pointer value to multiply
         * @return Reference to this object
         * @post vptr *= other.vptr
         */
        constexpr void operator*=(const virtual_ptr_16 &other) noexcept { vptr *= other.vptr; }

        /**
         * @brief Compound assignment operator for division by another virtual pointer.
         * @param other The virtual pointer value to divide by
         * @return Reference to this object
         * @throw std::runtime_error if other.vptr == 0 (division by zero)
         * @post vptr /= other.vptr
         */
        constexpr void operator/=(const virtual_ptr_16 &other) noexcept { vptr /= other.vptr; }

        /**
         * @brief Assignment operator for direct uint16_t values.
         * @param val The value to assign
         * @post vptr == val
         */
        constexpr void operator=(uint16_t val) noexcept { vptr = val; }

        /**
         * @brief Compound addition operator with uint16_t values.
         * @param val The value to add
         * @post vptr += val
         */
        constexpr void operator+=(uint16_t val) noexcept { vptr += val; }

        /**
         * @brief Compound subtraction operator with uint16_t values.
         * @param val The value to subtract
         * @post vptr -= val
         */
        constexpr void operator-=(uint16_t val) noexcept { vptr -= val; }

        /**
         * @brief Compound multiplication operator with uint16_t values.
         * @param val The value to multiply by
         * @post vptr *= val
         */
        constexpr void operator*=(uint16_t val) noexcept { vptr *= val; }

        /**
         * @brief Compound division operator with uint16_t values.
         * @param val The value to divide by
         * @throw std::runtime_error if val == 0 (division by zero)
         * @post vptr /= val
         */
        constexpr void operator/=(uint16_t val) noexcept { vptr /= val; }

        /**
         * @brief Pre-increment operator with saturation at maximum value.
         * @return Reference to this object after incrementing
         * @post vptr = min(vptr + 1, 65535)
         */
        virtual_ptr_16 operator++() noexcept
        {
            if (vptr + 1 <= 65535)
                vptr++;
            else
                vptr = 65535;
            return *this;
        }

        /**
         * @brief Pre-decrement operator with saturation at zero.
         * @return Reference to this object after decrementing
         * @post vptr = max(vptr - 1, 0)
         */
        virtual_ptr_16 operator--() noexcept
        {
            if (vptr - 1 >= 0)
                vptr--;
            else
                vptr = 0;
            return *this;
        }

        /**
         * @brief Stream output operator for hexadecimal representation.
         * @param os The output stream to write to
         * @param vptr The virtual pointer to output
         * @return Reference to the output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const virtual_ptr_16 &vptr)
        {
            os << vptr.get_str();
            return os;
        }
    };
    /**
     * @class virtual_ptr_32
     * @brief A 32-bit virtual pointer class providing safe arithmetic operations with saturation semantics.
     *
     * @details This class wraps a uint32_t value representing a virtual memory address or pointer.
     * It provides arithmetic operators with automatic saturation to prevent overflow/underflow.
     * All operations are constexpr-compatible for compile-time execution.
     *
     * @note Valid range: 0 to 4294967295 (2^32 - 1)
     * @see virtual_ptr_8, virtual_ptr_16, virtual_ptr_64
     */
    class virtual_ptr_32
    {
    private:
        uint32_t vptr; ///< Internal 32-bit virtual pointer value

    public:
        /**
         * @brief Default constructor initializing the virtual pointer to 0.
         * @post vptr == 0
         */
        constexpr virtual_ptr_32() noexcept : vptr(0) {}

        /**
         * @brief Constructs a virtual pointer with the specified uint32_t value.
         * @param val The initial value for the virtual pointer
         * @post vptr == val
         */
        constexpr virtual_ptr_32(uint32_t val) noexcept : vptr(val) {}

        /**
         * @brief Copy constructor creating a new virtual pointer from an existing one.
         * @param other The source virtual pointer to copy from
         * @post vptr == other.vptr
         */
        constexpr virtual_ptr_32(const virtual_ptr_32 &other) noexcept : vptr(other.vptr) {}

        /**
         * @brief Sets the virtual pointer to a new value.
         * @param val The new value to set
         * @post vptr == val
         */
        constexpr void set(uint32_t val) noexcept { vptr = val; }

        /**
         * @brief Gets the current value of the virtual pointer.
         * @return The current uint32_t value of this virtual pointer
         */
        constexpr uint32_t get() const noexcept { return vptr; }

        /**
         * @brief Returns the hexadecimal string representation of the virtual pointer.
         * @return A string containing the hexadecimal representation followed by 'h' suffix.
         *         For example, value 4294967295 returns "ffffffffh"
         */
        std::string get_str() const noexcept
        {
            std::stringstream ss;
            ss << std::hex << vptr;
            std::string hexadecimal_result = ss.str();
            return hexadecimal_result + "h";
        }

        /**
         * @brief Resets the virtual pointer to 0.
         * @post vptr == 0
         */
        constexpr void clear() noexcept { vptr = 0; }

        /**
         * @brief Checks if the virtual pointer is empty (zero).
         * @return true if vptr == 0, false otherwise
         */
        constexpr bool empty() noexcept { return vptr == 0; }

        /**
         * @brief Copy assignment operator.
         * @param other The source virtual pointer to assign from
         * @return Reference to this object
         * @post vptr == other.vptr
         */
        constexpr void operator=(const virtual_ptr_32 &other) noexcept { vptr = other.vptr; }

        /**
         * @brief Compound assignment operator for addition with another virtual pointer.
         * @param other The virtual pointer value to add
         * @return Reference to this object
         * @post vptr += other.vptr
         */
        constexpr void operator+=(const virtual_ptr_32 &other) noexcept { vptr += other.vptr; }

        /**
         * @brief Compound assignment operator for subtraction with another virtual pointer.
         * @param other The virtual pointer value to subtract
         * @return Reference to this object
         * @post vptr -= other.vptr
         */
        constexpr void operator-=(const virtual_ptr_32 &other) noexcept { vptr -= other.vptr; }

        /**
         * @brief Compound assignment operator for multiplication with another virtual pointer.
         * @param other The virtual pointer value to multiply
         * @return Reference to this object
         * @post vptr *= other.vptr
         */
        constexpr void operator*=(const virtual_ptr_32 &other) noexcept { vptr *= other.vptr; }

        /**
         * @brief Compound assignment operator for division by another virtual pointer.
         * @param other The virtual pointer value to divide by
         * @return Reference to this object
         * @throw std::runtime_error if other.vptr == 0 (division by zero)
         * @post vptr /= other.vptr
         */
        constexpr void operator/=(const virtual_ptr_32 &other) noexcept { vptr /= other.vptr; }

        /**
         * @brief Assignment operator for direct uint32_t values.
         * @param val The value to assign
         * @post vptr == val
         */
        constexpr void operator=(uint32_t val) noexcept { vptr = val; }

        /**
         * @brief Compound addition operator with uint32_t values.
         * @param val The value to add
         * @post vptr += val
         */
        constexpr void operator+=(uint32_t val) noexcept { vptr += val; }

        /**
         * @brief Compound subtraction operator with uint32_t values.
         * @param val The value to subtract
         * @post vptr -= val
         */
        constexpr void operator-=(uint32_t val) noexcept { vptr -= val; }

        /**
         * @brief Compound multiplication operator with uint32_t values.
         * @param val The value to multiply by
         * @post vptr *= val
         */
        constexpr void operator*=(uint32_t val) noexcept { vptr *= val; }

        /**
         * @brief Compound division operator with uint32_t values.
         * @param val The value to divide by
         * @throw std::runtime_error if val == 0 (division by zero)
         * @post vptr /= val
         */
        constexpr void operator/=(uint32_t val) noexcept { vptr /= val; }

        /**
         * @brief Pre-increment operator with saturation at maximum value.
         * @return Reference to this object after incrementing
         * @post vptr = min(vptr + 1, UINT32_MAX)
         */
        virtual_ptr_32 operator++() noexcept
        {
            if (vptr + 1 <= UINT32_MAX)
                vptr++;
            else
                vptr = UINT32_MAX;
            return *this;
        }

        /**
         * @brief Pre-decrement operator with saturation at zero.
         * @return Reference to this object after decrementing
         * @post vptr = max(vptr - 1, 0)
         */
        virtual_ptr_32 operator--() noexcept
        {
            if (vptr - 1 >= 0)
                vptr--;
            else
                vptr = 0;
            return *this;
        }

        /**
         * @brief Stream output operator for hexadecimal representation.
         * @param os The output stream to write to
         * @param vptr The virtual pointer to output
         * @return Reference to the output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const virtual_ptr_32 &vptr)
        {
            os << vptr.get_str();
            return os;
        }
    };

    /**
     * @class virtual_ptr_64
     * @brief A 64-bit virtual pointer class providing safe arithmetic operations with saturation semantics.
     *
     * @details This class wraps a uint64_t value representing a virtual memory address or pointer.
     * It provides arithmetic operators with automatic saturation to prevent overflow/underflow.
     * All operations are constexpr-compatible for compile-time execution.
     *
     * @note Valid range: 0 to 18446744073709551615 (2^64 - 1)
     * @see virtual_ptr_8, virtual_ptr_16, virtual_ptr_32
     */
    class virtual_ptr_64
    {
    private:
        uint64_t vptr; ///< Internal 64-bit virtual pointer value

    public:
        /**
         * @brief Default constructor initializing the virtual pointer to 0.
         * @post vptr == 0
         */
        constexpr virtual_ptr_64() noexcept : vptr(0) {}

        /**
         * @brief Constructs a virtual pointer with the specified uint64_t value.
         * @param val The initial value for the virtual pointer
         * @post vptr == val
         */
        constexpr virtual_ptr_64(uint64_t val) noexcept : vptr(val) {}

        /**
         * @brief Copy constructor creating a new virtual pointer from an existing one.
         * @param other The source virtual pointer to copy from
         * @post vptr == other.vptr
         */
        constexpr virtual_ptr_64(const virtual_ptr_64 &other) noexcept : vptr(other.vptr) {}

        /**
         * @brief Sets the virtual pointer to a new value.
         * @param val The new value to set
         * @post vptr == val
         */
        constexpr void set(uint64_t val) noexcept { vptr = val; }

        /**
         * @brief Gets the current value of the virtual pointer.
         * @return The current uint64_t value of this virtual pointer
         */
        constexpr uint64_t get() const noexcept { return vptr; }

        /**
         * @brief Returns the hexadecimal string representation of the virtual pointer.
         * @return A string containing the hexadecimal representation followed by 'h' suffix.
         *         For example, value 18446744073709551615 returns "ffffffffffffffffh"
         */
        std::string get_str() const noexcept
        {
            std::stringstream ss;
            ss << std::hex << vptr;
            std::string hexadecimal_result = ss.str();
            return hexadecimal_result + "h";
        }

        /**
         * @brief Resets the virtual pointer to 0.
         * @post vptr == 0
         */
        constexpr void clear() noexcept { vptr = 0; }

        /**
         * @brief Checks if the virtual pointer is empty (zero).
         * @return true if vptr == 0, false otherwise
         */
        constexpr bool empty() noexcept { return vptr == 0; }

        /**
         * @brief Copy assignment operator.
         * @param other The source virtual pointer to assign from
         * @return Reference to this object
         * @post vptr == other.vptr
         */
        constexpr void operator=(const virtual_ptr_64 &other) noexcept { vptr = other.vptr; }

        /**
         * @brief Compound assignment operator for addition with another virtual pointer.
         * @param other The virtual pointer value to add
         * @return Reference to this object
         * @post vptr += other.vptr
         */
        constexpr void operator+=(const virtual_ptr_64 &other) noexcept { vptr += other.vptr; }

        /**
         * @brief Compound assignment operator for subtraction with another virtual pointer.
         * @param other The virtual pointer value to subtract
         * @return Reference to this object
         * @post vptr -= other.vptr
         */
        constexpr void operator-=(const virtual_ptr_64 &other) noexcept { vptr -= other.vptr; }

        /**
         * @brief Compound assignment operator for multiplication with another virtual pointer.
         * @param other The virtual pointer value to multiply
         * @return Reference to this object
         * @post vptr *= other.vptr
         */
        constexpr void operator*=(const virtual_ptr_64 &other) noexcept { vptr *= other.vptr; }

        /**
         * @brief Compound assignment operator for division by another virtual pointer.
         * @param other The virtual pointer value to divide by
         * @return Reference to this object
         * @throw std::runtime_error if other.vptr == 0 (division by zero)
         * @post vptr /= other.vptr
         */
        constexpr void operator/=(const virtual_ptr_64 &other) noexcept { vptr /= other.vptr; }

        /**
         * @brief Assignment operator for direct uint64_t values.
         * @param val The value to assign
         * @post vptr == val
         */
        constexpr void operator=(uint64_t val) noexcept { vptr = val; }

        /**
         * @brief Compound addition operator with uint64_t values.
         * @param val The value to add
         * @post vptr += val
         */
        constexpr void operator+=(uint64_t val) noexcept { vptr += val; }

        /**
         * @brief Compound subtraction operator with uint64_t values.
         * @param val The value to subtract
         * @post vptr -= val
         */
        constexpr void operator-=(uint64_t val) noexcept { vptr -= val; }

        /**
         * @brief Compound multiplication operator with uint64_t values.
         * @param val The value to multiply by
         * @post vptr *= val
         */
        constexpr void operator*=(uint64_t val) noexcept { vptr *= val; }

        /**
         * @brief Compound division operator with uint64_t values.
         * @param val The value to divide by
         * @throw std::runtime_error if val == 0 (division by zero)
         * @post vptr /= val
         */
        constexpr void operator/=(uint64_t val) noexcept { vptr /= val; }

        /**
         * @brief Pre-increment operator with saturation at maximum value.
         * @return Reference to this object after incrementing
         * @post vptr = min(vptr + 1, UINT64_MAX)
         */
        virtual_ptr_64 operator++() noexcept
        {
            if (vptr + 1 <= UINT64_MAX)
                vptr++;
            else
                vptr = UINT64_MAX;
            return *this;
        }

        /**
         * @brief Pre-decrement operator with saturation at zero.
         * @return Reference to this object after decrementing
         * @post vptr = max(vptr - 1, 0)
         */
        virtual_ptr_64 operator--() noexcept
        {
            if (vptr - 1 >= 0)
                vptr--;
            else
                vptr = 0;
            return *this;
        }

        /**
         * @brief Stream output operator for hexadecimal representation.
         * @param os The output stream to write to
         * @param vptr The virtual pointer to output
         * @return Reference to the output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const virtual_ptr_64 &vptr)
        {
            os << vptr.get_str();
            return os;
        }
    };
}
#endif // OPENUDT___UDT_VIRTUAL_HPP