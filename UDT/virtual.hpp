/**
 * @file virtual.hpp
 * @brief Defines virtual pointer classes for 8-bit, 16-bit, 32-bit, and 64-bit sizes with safe arithmetic operations.
 * @details This header provides four classes: ptr_8, ptr_16, ptr_32, and ptr_64.
 * Each class encapsulates a virtual pointer of the corresponding size and offers methods for setting, getting,
 * clearing, and performing arithmetic operations with saturation semantics. The classes are designed to be
 * constexpr-compatible for compile-time usage and include stream output operators for easy debugging and visualization.
 * @note All operations that could potentially overflow or underflow will saturate at the maximum or minimum value
 * respectively, ensuring safe arithmetic behavior. Division by zero will throw a runtime error.
 * @see ptr_8, ptr_16, ptr_32, ptr_64
 * @author Ali Lafi
 * @date 2025/9/25
 */

#include "lite/micros.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdint.h>
#include <unordered_map>

#pragma once
#ifndef OPENUDT___UDT_VIRTUAL_HPP
#define OPENUDT___UDT_VIRTUAL_HPP

namespace udt
{
    namespace virtual
    {
        /**
         * @class ptr_8
         * @brief An 8-bit virtual pointer class providing safe arithmetic operations with saturation semantics.
         *
         * @details This class wraps a uint8_t value representing a virtual memory address or pointer.
         * It provides arithmetic operators with automatic saturation to prevent overflow/underflow.
         * All operations are constexpr-compatible for compile-time execution.
         *
         * @note Valid range: 0 to 255 (2^8 - 1)
         * @see ptr_16, ptr_32, ptr_64
         */
        class ptr_8
        {
        private:
            uint8_t ptr; ///< Internal 8-bit virtual pointer value

        public:
            /**
             * @brief Default constructor initializing the virtual pointer to 0.
             * @post ptr == 0
             */
            constexpr ptr_8() noexcept : ptr(0) {}

            /**
             * @brief Constructs a virtual pointer with the specified uint8_t value.
             * @param val The initial value for the virtual pointer
             * @post ptr == val
             */
            constexpr ptr_8(uint8_t val) noexcept : ptr(val) {}

            /**
             * @brief Copy constructor creating a new virtual pointer from an existing one.
             * @param other The source virtual pointer to copy from
             * @post ptr == other.ptr
             */
            constexpr ptr_8(const ptr_8 &other) noexcept : ptr(other.ptr) {}

            /**
             * @brief Sets the virtual pointer to a new value.
             * @param val The new value to set
             * @post ptr == val
             */
            constexpr void set(uint8_t val) noexcept { ptr = val; }

            /**
             * @brief Gets the current value of the virtual pointer.
             * @return The current uint8_t value of this virtual pointer
             */
            constexpr uint8_t get() const noexcept { return ptr; }

            /**
             * @brief Returns the hexadecimal string representation of the virtual pointer.
             * @return A string containing the hexadecimal representation followed by 'h' suffix.
             *         For example, value 255 returns "ffh"
             */
            std::string get_str() const noexcept
            {
                std::stringstream ss;
                ss << std::hex << ptr;
                std::string hexadecimal_result = ss.str();
                return hexadecimal_result + "h";
            }

            /**
             * @brief Resets the virtual pointer to 0.
             * @post ptr == 0
             */
            constexpr void clear() noexcept { ptr = 0; }

            /**
             * @brief Checks if the virtual pointer is empty (zero).
             * @return true if ptr == 0, false otherwise
             */
            constexpr bool empty() noexcept { return ptr == 0; }

            /**
             * @brief Copy assignment operator.
             * @param other The source virtual pointer to assign from
             * @return Reference to this object
             * @post ptr == other.ptr
             */
            constexpr void operator=(const ptr_8 &other) noexcept { ptr = other.ptr; }

            /**
             * @brief Compound assignment operator for addition with another virtual pointer.
             * @param other The virtual pointer value to add (saturates at 255)
             * @return Reference to this object
             * @post ptr = min(ptr + other.ptr, 255)
             */
            constexpr void operator+=(const ptr_8 &other) noexcept { ptr += other.ptr; }

            /**
             * @brief Compound assignment operator for subtraction with another virtual pointer.
             * @param other The virtual pointer value to subtract
             * @return Reference to this object
             * @post ptr = ptr - other.ptr (with underflow handling)
             */
            constexpr void operator-=(const ptr_8 &other) noexcept { ptr -= other.ptr; }

            /**
             * @brief Compound assignment operator for multiplication with another virtual pointer.
             * @param other The virtual pointer value to multiply
             * @return Reference to this object
             * @post ptr = ptr * other.ptr (with overflow handling)
             */
            constexpr void operator*=(const ptr_8 &other) noexcept { ptr *= other.ptr; }

            /**
             * @brief Compound assignment operator for division by another virtual pointer.
             * @param other The virtual pointer value to divide by
             * @return Reference to this object
             * @throw std::runtime_error if other.ptr == 0 (division by zero)
             * @post ptr = ptr / other.ptr
             */
            constexpr void operator/=(const ptr_8 &other) noexcept { ptr /= other.ptr; }

            /**
             * @brief Assignment operator for direct uint8_t values.
             * @param val The value to assign
             * @post ptr == val
             */
            constexpr void operator=(uint8_t val) noexcept { ptr = val; }

            /**
             * @brief Compound addition operator with uint8_t values.
             * @param val The value to add
             * @post ptr += val
             */
            constexpr void operator+=(uint8_t val) noexcept { ptr += val; }

            /**
             * @brief Compound subtraction operator with uint8_t values.
             * @param val The value to subtract
             * @post ptr -= val
             */
            constexpr void operator-=(uint8_t val) noexcept { ptr -= val; }

            /**
             * @brief Compound multiplication operator with uint8_t values.
             * @param val The value to multiply by
             * @post ptr *= val
             */
            constexpr void operator*=(uint8_t val) noexcept { ptr *= val; }

            /**
             * @brief Compound division operator with uint8_t values.
             * @param val The value to divide by
             * @throw std::runtime_error if val == 0 (division by zero)
             * @post ptr /= val
             */
            constexpr void operator/=(uint8_t val) noexcept { ptr /= val; }

            /**
             * @brief Pre-increment operator with saturation at maximum value.
             * @return Reference to this object after incrementing
             * @post ptr = min(ptr + 1, 255)
             */
            ptr_8 operator++() noexcept
            {
                if (ptr + 1 <= 255)
                    ptr++;
                else
                    ptr = 255;
                return *this;
            }

            /**
             * @brief Pre-decrement operator with saturation at zero.
             * @return Reference to this object after decrementing
             * @post ptr = max(ptr - 1, 0)
             */
            ptr_8 operator--() noexcept
            {
                if (ptr - 1 >= 0)
                    ptr--;
                else
                    ptr = 0;
                return *this;
            }

            /**
             * @brief Stream output operator for hexadecimal representation.
             * @param os The output stream to write to
             * @param ptr The virtual pointer to output
             * @return Reference to the output stream
             */
            friend std::ostream &operator<<(std::ostream &os, const ptr_8 &ptr)
            {
                os << ptr.get_str();
                return os;
            }
        };
        /**
         * @class ptr_16
         * @brief A 16-bit virtual pointer class providing safe arithmetic operations with saturation semantics.
         *
         * @details This class wraps a uint16_t value representing a virtual memory address or pointer.
         * It provides arithmetic operators with automatic saturation to prevent overflow/underflow.
         * All operations are constexpr-compatible for compile-time execution.
         *
         * @note Valid range: 0 to 65535 (2^16 - 1)
         * @see ptr_8, ptr_32, ptr_64
         */
        class ptr_16
        {
        private:
            uint16_t ptr; ///< Internal 16-bit virtual pointer value

        public:
            /**
             * @brief Default constructor initializing the virtual pointer to 0.
             * @post ptr == 0
             */
            ptr_16() noexcept { ptr = 0; }

            /**
             * @brief Constructs a virtual pointer with the specified uint16_t value.
             * @param val The initial value for the virtual pointer
             * @post ptr == val
             */
            ptr_16(uint16_t val) noexcept { ptr = val; }

            /**
             * @brief Copy constructor creating a new virtual pointer from an existing one.
             * @param other The source virtual pointer to copy from
             * @post ptr == other.ptr
             */
            ptr_16(const ptr_16 &other) noexcept { ptr = other.ptr; }

            /**
             * @brief Sets the virtual pointer to a new value.
             * @param val The new value to set
             * @post ptr == val
             */
            constexpr void set(uint16_t val) noexcept { ptr = val; }

            /**
             * @brief Gets the current value of the virtual pointer.
             * @return The current uint16_t value of this virtual pointer
             */
            constexpr uint16_t get() const noexcept { return ptr; }

            /**
             * @brief Returns the hexadecimal string representation of the virtual pointer.
             * @return A string containing the hexadecimal representation followed by 'h' suffix.
             *         For example, value 65535 returns "ffffh"
             */
            std::string get_str() const noexcept
            {
                std::stringstream ss;
                ss << std::hex << ptr;
                std::string hexadecimal_result = ss.str();
                return hexadecimal_result + "h";
            }

            /**
             * @brief Resets the virtual pointer to 0.
             * @post ptr == 0
             */
            constexpr void clear() noexcept { ptr = 0; }

            /**
             * @brief Checks if the virtual pointer is empty (zero).
             * @return true if ptr == 0, false otherwise
             */
            constexpr bool empty() noexcept { return ptr == 0; }

            /**
             * @brief Copy assignment operator.
             * @param other The source virtual pointer to assign from
             * @return Reference to this object
             * @post ptr == other.ptr
             */
            constexpr void operator=(const ptr_16 &other) noexcept { ptr = other.ptr; }

            /**
             * @brief Compound assignment operator for addition with another virtual pointer.
             * @param other The virtual pointer value to add
             * @return Reference to this object
             * @post ptr += other.ptr
             */
            constexpr void operator+=(const ptr_16 &other) noexcept { ptr += other.ptr; }

            /**
             * @brief Compound assignment operator for subtraction with another virtual pointer.
             * @param other The virtual pointer value to subtract
             * @return Reference to this object
             * @post ptr -= other.ptr
             */
            constexpr void operator-=(const ptr_16 &other) noexcept { ptr -= other.ptr; }

            /**
             * @brief Compound assignment operator for multiplication with another virtual pointer.
             * @param other The virtual pointer value to multiply
             * @return Reference to this object
             * @post ptr *= other.ptr
             */
            constexpr void operator*=(const ptr_16 &other) noexcept { ptr *= other.ptr; }

            /**
             * @brief Compound assignment operator for division by another virtual pointer.
             * @param other The virtual pointer value to divide by
             * @return Reference to this object
             * @throw std::runtime_error if other.ptr == 0 (division by zero)
             * @post ptr /= other.ptr
             */
            constexpr void operator/=(const ptr_16 &other) noexcept { ptr /= other.ptr; }

            /**
             * @brief Assignment operator for direct uint16_t values.
             * @param val The value to assign
             * @post ptr == val
             */
            constexpr void operator=(uint16_t val) noexcept { ptr = val; }

            /**
             * @brief Compound addition operator with uint16_t values.
             * @param val The value to add
             * @post ptr += val
             */
            constexpr void operator+=(uint16_t val) noexcept { ptr += val; }

            /**
             * @brief Compound subtraction operator with uint16_t values.
             * @param val The value to subtract
             * @post ptr -= val
             */
            constexpr void operator-=(uint16_t val) noexcept { ptr -= val; }

            /**
             * @brief Compound multiplication operator with uint16_t values.
             * @param val The value to multiply by
             * @post ptr *= val
             */
            constexpr void operator*=(uint16_t val) noexcept { ptr *= val; }

            /**
             * @brief Compound division operator with uint16_t values.
             * @param val The value to divide by
             * @throw std::runtime_error if val == 0 (division by zero)
             * @post ptr /= val
             */
            constexpr void operator/=(uint16_t val) noexcept { ptr /= val; }

            /**
             * @brief Pre-increment operator with saturation at maximum value.
             * @return Reference to this object after incrementing
             * @post ptr = min(ptr + 1, 65535)
             */
            ptr_16 operator++() noexcept
            {
                if (ptr + 1 <= 65535)
                    ptr++;
                else
                    ptr = 65535;
                return *this;
            }

            /**
             * @brief Pre-decrement operator with saturation at zero.
             * @return Reference to this object after decrementing
             * @post ptr = max(ptr - 1, 0)
             */
            ptr_16 operator--() noexcept
            {
                if (ptr - 1 >= 0)
                    ptr--;
                else
                    ptr = 0;
                return *this;
            }

            /**
             * @brief Stream output operator for hexadecimal representation.
             * @param os The output stream to write to
             * @param ptr The virtual pointer to output
             * @return Reference to the output stream
             */
            friend std::ostream &operator<<(std::ostream &os, const ptr_16 &ptr)
            {
                os << ptr.get_str();
                return os;
            }
        };
        /**
         * @class ptr_32
         * @brief A 32-bit virtual pointer class providing safe arithmetic operations with saturation semantics.
         *
         * @details This class wraps a uint32_t value representing a virtual memory address or pointer.
         * It provides arithmetic operators with automatic saturation to prevent overflow/underflow.
         * All operations are constexpr-compatible for compile-time execution.
         *
         * @note Valid range: 0 to 4294967295 (2^32 - 1)
         * @see ptr_8, ptr_16, ptr_64
         */
        class ptr_32
        {
        private:
            uint32_t ptr; ///< Internal 32-bit virtual pointer value

        public:
            /**
             * @brief Default constructor initializing the virtual pointer to 0.
             * @post ptr == 0
             */
            constexpr ptr_32() noexcept : ptr(0) {}

            /**
             * @brief Constructs a virtual pointer with the specified uint32_t value.
             * @param val The initial value for the virtual pointer
             * @post ptr == val
             */
            constexpr ptr_32(uint32_t val) noexcept : ptr(val) {}

            /**
             * @brief Copy constructor creating a new virtual pointer from an existing one.
             * @param other The source virtual pointer to copy from
             * @post ptr == other.ptr
             */
            constexpr ptr_32(const ptr_32 &other) noexcept : ptr(other.ptr) {}

            /**
             * @brief Sets the virtual pointer to a new value.
             * @param val The new value to set
             * @post ptr == val
             */
            constexpr void set(uint32_t val) noexcept { ptr = val; }

            /**
             * @brief Gets the current value of the virtual pointer.
             * @return The current uint32_t value of this virtual pointer
             */
            constexpr uint32_t get() const noexcept { return ptr; }

            /**
             * @brief Returns the hexadecimal string representation of the virtual pointer.
             * @return A string containing the hexadecimal representation followed by 'h' suffix.
             *         For example, value 4294967295 returns "ffffffffh"
             */
            std::string get_str() const noexcept
            {
                std::stringstream ss;
                ss << std::hex << ptr;
                std::string hexadecimal_result = ss.str();
                return hexadecimal_result + "h";
            }

            /**
             * @brief Resets the virtual pointer to 0.
             * @post ptr == 0
             */
            constexpr void clear() noexcept { ptr = 0; }

            /**
             * @brief Checks if the virtual pointer is empty (zero).
             * @return true if ptr == 0, false otherwise
             */
            constexpr bool empty() noexcept { return ptr == 0; }

            /**
             * @brief Copy assignment operator.
             * @param other The source virtual pointer to assign from
             * @return Reference to this object
             * @post ptr == other.ptr
             */
            constexpr void operator=(const ptr_32 &other) noexcept { ptr = other.ptr; }

            /**
             * @brief Compound assignment operator for addition with another virtual pointer.
             * @param other The virtual pointer value to add
             * @return Reference to this object
             * @post ptr += other.ptr
             */
            constexpr void operator+=(const ptr_32 &other) noexcept { ptr += other.ptr; }

            /**
             * @brief Compound assignment operator for subtraction with another virtual pointer.
             * @param other The virtual pointer value to subtract
             * @return Reference to this object
             * @post ptr -= other.ptr
             */
            constexpr void operator-=(const ptr_32 &other) noexcept { ptr -= other.ptr; }

            /**
             * @brief Compound assignment operator for multiplication with another virtual pointer.
             * @param other The virtual pointer value to multiply
             * @return Reference to this object
             * @post ptr *= other.ptr
             */
            constexpr void operator*=(const ptr_32 &other) noexcept { ptr *= other.ptr; }

            /**
             * @brief Compound assignment operator for division by another virtual pointer.
             * @param other The virtual pointer value to divide by
             * @return Reference to this object
             * @throw std::runtime_error if other.ptr == 0 (division by zero)
             * @post ptr /= other.ptr
             */
            constexpr void operator/=(const ptr_32 &other) noexcept { ptr /= other.ptr; }

            /**
             * @brief Assignment operator for direct uint32_t values.
             * @param val The value to assign
             * @post ptr == val
             */
            constexpr void operator=(uint32_t val) noexcept { ptr = val; }

            /**
             * @brief Compound addition operator with uint32_t values.
             * @param val The value to add
             * @post ptr += val
             */
            constexpr void operator+=(uint32_t val) noexcept { ptr += val; }

            /**
             * @brief Compound subtraction operator with uint32_t values.
             * @param val The value to subtract
             * @post ptr -= val
             */
            constexpr void operator-=(uint32_t val) noexcept { ptr -= val; }

            /**
             * @brief Compound multiplication operator with uint32_t values.
             * @param val The value to multiply by
             * @post ptr *= val
             */
            constexpr void operator*=(uint32_t val) noexcept { ptr *= val; }

            /**
             * @brief Compound division operator with uint32_t values.
             * @param val The value to divide by
             * @throw std::runtime_error if val == 0 (division by zero)
             * @post ptr /= val
             */
            constexpr void operator/=(uint32_t val) noexcept { ptr /= val; }

            /**
             * @brief Pre-increment operator with saturation at maximum value.
             * @return Reference to this object after incrementing
             * @post ptr = min(ptr + 1, UINT32_MAX)
             */
            ptr_32 operator++() noexcept
            {
                if (ptr + 1 <= UINT32_MAX)
                    ptr++;
                else
                    ptr = UINT32_MAX;
                return *this;
            }

            /**
             * @brief Pre-decrement operator with saturation at zero.
             * @return Reference to this object after decrementing
             * @post ptr = max(ptr - 1, 0)
             */
            ptr_32 operator--() noexcept
            {
                if (ptr - 1 >= 0)
                    ptr--;
                else
                    ptr = 0;
                return *this;
            }

            /**
             * @brief Stream output operator for hexadecimal representation.
             * @param os The output stream to write to
             * @param ptr The virtual pointer to output
             * @return Reference to the output stream
             */
            friend std::ostream &operator<<(std::ostream &os, const ptr_32 &ptr)
            {
                os << ptr.get_str();
                return os;
            }
        };

        /**
         * @class ptr_64
         * @brief A 64-bit virtual pointer class providing safe arithmetic operations with saturation semantics.
         *
         * @details This class wraps a uint64_t value representing a virtual memory address or pointer.
         * It provides arithmetic operators with automatic saturation to prevent overflow/underflow.
         * All operations are constexpr-compatible for compile-time execution.
         *
         * @note Valid range: 0 to 18446744073709551615 (2^64 - 1)
         * @see ptr_8, ptr_16, ptr_32
         */
        class ptr_64
        {
        private:
            uint64_t ptr; ///< Internal 64-bit virtual pointer value

        public:
            /**
             * @brief Default constructor initializing the virtual pointer to 0.
             * @post ptr == 0
             */
            constexpr ptr_64() noexcept : ptr(0) {}

            /**
             * @brief Constructs a virtual pointer with the specified uint64_t value.
             * @param val The initial value for the virtual pointer
             * @post ptr == val
             */
            constexpr ptr_64(uint64_t val) noexcept : ptr(val) {}

            /**
             * @brief Copy constructor creating a new virtual pointer from an existing one.
             * @param other The source virtual pointer to copy from
             * @post ptr == other.ptr
             */
            constexpr ptr_64(const ptr_64 &other) noexcept : ptr(other.ptr) {}

            /**
             * @brief Sets the virtual pointer to a new value.
             * @param val The new value to set
             * @post ptr == val
             */
            constexpr void set(uint64_t val) noexcept { ptr = val; }

            /**
             * @brief Gets the current value of the virtual pointer.
             * @return The current uint64_t value of this virtual pointer
             */
            constexpr uint64_t get() const noexcept { return ptr; }

            /**
             * @brief Returns the hexadecimal string representation of the virtual pointer.
             * @return A string containing the hexadecimal representation followed by 'h' suffix.
             *         For example, value 18446744073709551615 returns "ffffffffffffffffh"
             */
            std::string get_str() const noexcept
            {
                std::stringstream ss;
                ss << std::hex << ptr;
                std::string hexadecimal_result = ss.str();
                return hexadecimal_result + "h";
            }

            /**
             * @brief Resets the virtual pointer to 0.
             * @post ptr == 0
             */
            constexpr void clear() noexcept { ptr = 0; }

            /**
             * @brief Checks if the virtual pointer is empty (zero).
             * @return true if ptr == 0, false otherwise
             */
            constexpr bool empty() noexcept { return ptr == 0; }

            /**
             * @brief Copy assignment operator.
             * @param other The source virtual pointer to assign from
             * @return Reference to this object
             * @post ptr == other.ptr
             */
            constexpr void operator=(const ptr_64 &other) noexcept { ptr = other.ptr; }

            /**
             * @brief Compound assignment operator for addition with another virtual pointer.
             * @param other The virtual pointer value to add
             * @return Reference to this object
             * @post ptr += other.ptr
             */
            constexpr void operator+=(const ptr_64 &other) noexcept { ptr += other.ptr; }

            /**
             * @brief Compound assignment operator for subtraction with another virtual pointer.
             * @param other The virtual pointer value to subtract
             * @return Reference to this object
             * @post ptr -= other.ptr
             */
            constexpr void operator-=(const ptr_64 &other) noexcept { ptr -= other.ptr; }

            /**
             * @brief Compound assignment operator for multiplication with another virtual pointer.
             * @param other The virtual pointer value to multiply
             * @return Reference to this object
             * @post ptr *= other.ptr
             */
            constexpr void operator*=(const ptr_64 &other) noexcept { ptr *= other.ptr; }

            /**
             * @brief Compound assignment operator for division by another virtual pointer.
             * @param other The virtual pointer value to divide by
             * @return Reference to this object
             * @throw std::runtime_error if other.ptr == 0 (division by zero)
             * @post ptr /= other.ptr
             */
            constexpr void operator/=(const ptr_64 &other) noexcept { ptr /= other.ptr; }

            /**
             * @brief Assignment operator for direct uint64_t values.
             * @param val The value to assign
             * @post ptr == val
             */
            constexpr void operator=(uint64_t val) noexcept { ptr = val; }

            /**
             * @brief Compound addition operator with uint64_t values.
             * @param val The value to add
             * @post ptr += val
             */
            constexpr void operator+=(uint64_t val) noexcept { ptr += val; }

            /**
             * @brief Compound subtraction operator with uint64_t values.
             * @param val The value to subtract
             * @post ptr -= val
             */
            constexpr void operator-=(uint64_t val) noexcept { ptr -= val; }

            /**
             * @brief Compound multiplication operator with uint64_t values.
             * @param val The value to multiply by
             * @post ptr *= val
             */
            constexpr void operator*=(uint64_t val) noexcept { ptr *= val; }

            /**
             * @brief Compound division operator with uint64_t values.
             * @param val The value to divide by
             * @throw std::runtime_error if val == 0 (division by zero)
             * @post ptr /= val
             */
            constexpr void operator/=(uint64_t val) noexcept { ptr /= val; }

            /**
             * @brief Pre-increment operator with saturation at maximum value.
             * @return Reference to this object after incrementing
             * @post ptr = min(ptr + 1, UINT64_MAX)
             */
            ptr_64 operator++() noexcept
            {
                if (ptr + 1 <= UINT64_MAX)
                    ptr++;
                else
                    ptr = UINT64_MAX;
                return *this;
            }

            /**
             * @brief Pre-decrement operator with saturation at zero.
             * @return Reference to this object after decrementing
             * @post ptr = max(ptr - 1, 0)
             */
            ptr_64 operator--() noexcept
            {
                if (ptr - 1 >= 0)
                    ptr--;
                else
                    ptr = 0;
                return *this;
            }

            /**
             * @brief Stream output operator for hexadecimal representation.
             * @param os The output stream to write to
             * @param ptr The virtual pointer to output
             * @return Reference to the output stream
             */
            friend std::ostream &operator<<(std::ostream &os, const ptr_64 &ptr)
            {
                os << ptr.get_str();
                return os;
            }
        };

        typedef std::vector<uint8_t> data;

        class machine_8
        {
        private:
            std::unordered_map<str, uint8_t> registers;
            std::unordered_map<str, std::pair<size_t, data>> segments;
            std::unordered_map<str, ptr_8> segments_indexs;

        public:
        };

        class machine_16
        {
        private:
            std::unordered_map<str, uint16_t> registers;
            std::unordered_map<str, std::pair<size_t, data>> segments;
            std::unordered_map<str, ptr_32> segments_indexs;

        public:
        };

        class machine_32
        {
        private:
            std::unordered_map<str, uint32_t> registers;
            std::unordered_map<str, std::pair<size_t, data>> segments;
            std::unordered_map<str, ptr_32> segments_indexs;

        public:
        };

        class machine_64
        {
        private:
            std::unordered_map<str, uint64_t> registers;
            std::unordered_map<str, std::pair<size_t, data>> segments;
            std::unordered_map<str, ptr_64> segments_indexs;

        public:
        };
    }
}

#endif // OPENUDT___UDT_VIRTUAL_HPP