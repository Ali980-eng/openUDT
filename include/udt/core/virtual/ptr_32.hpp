
#include <cstdint>
#include <stdexcept>
#include <sstream>
#include "cfrost/structure.h"

#pragma once
#ifndef OPENUDT___CORE___VIRTUAL_PTR_32_HPP
#define OPENUDT___CORE___VIRTUAL_PTR_32_HPP

namespace udt
{
    namespace Virtual
    {
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
            str get_str() const noexcept
            {
                std::stringstream ss;
                ss << std::hex << ptr;
                str hexadecimal_result = ss.str();
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
    }
}

#endif // OPENUDT___CORE___VIRTUAL_PTR_32_HPP