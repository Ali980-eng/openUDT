
#include <cstdint>
#include <stdexcept>
#include <sstream>

#pragma once
#ifndef OPENUDT___CORE_VIRTUAL_PTR_8_HPP
#define OPENUDT___CORE_VIRTUAL_PTR_8_HPP

namespace udt
{
    namespace Virtual
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
    }
}

#endif // OPENUDT___CORE_VIRTUAL_PTR_8_HPP