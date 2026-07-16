#include <iostream>
#include <cstdint>
#include <exception>
#include <string>
#include "cfrost/structure.h"

#pragma once
#ifndef OPENUDT___CORE___BFS_BFS8_HPP
#define OPENUDT___CORE___BFS_BFS8_HPP

namespace udt
{
    /// @brief A class to manage an 8-bit binary flag container.
    class bfs_8
    {
    private:
        uint8_t flag_container;

    public:
        /// @brief Default constructor initializes all flags to 0.
        bfs_8() noexcept : flag_container(0) {}

        /// @brief Constructor that initializes all flags to a specified value.
        /// @param initial_value The initial value for the flag container.
        bfs_8(uint8_t initial_value) noexcept : flag_container(initial_value) {}

        /// @brief Copy constructor.
        /// @param other The bfs_8 object to copy from.
        bfs_8(const bfs_8 &other) noexcept : flag_container(other.flag_container) {}

        /**
         * @brief Sets the flag at position 1 to 1.
         * This method sets the bit at position 1 (the least significant bit) in the flag container to 1.
         * @exception This method does not throw any exceptions.
         * @note This is a constexpr function and can be evaluated at compile time.
         * @code
         * bfs_8 bfs;
         * bfs.set_flag1(); // Set bit 1 to 1
         * @endcode
         */
        constexpr procedure(set_flag1) noexcept { flag_container |= 1; }

        /**
         * @brief Sets the flag at position 2 to 1.
         * This method sets the bit at position 2 in the flag container to 1.
         * @exception This method does not throw any exceptions.
         * @note This is a constexpr function and can be evaluated at compile time.
         */
        constexpr procedure(set_flag2) noexcept { flag_container |= 2; }

        /**
         * @brief Sets the flag at position 3 to 1.
         * This method sets the bit at position 3 in the flag container to 1.
         * @exception This method does not throw any exceptions.
         * @note This is a constexpr function and can be evaluated at compile time.
         */
        constexpr procedure(set_flag3) noexcept { flag_container |= 4; }

        /**
         * @brief Sets the flag at position 4 to 1.
         * This method sets the bit at position 4 in the flag container to 1.
         * @exception This method does not throw any exceptions.
         * @note This is a constexpr function and can be evaluated at compile time.
         */
        constexpr procedure(set_flag4) noexcept { flag_container |= 8; }

        /**
         * @brief Sets the flag at position 5 to 1.
         * This method sets the bit at position 5 in the flag container to 1.
         * @exception This method does not throw any exceptions.
         * @note This is a constexpr function and can be evaluated at compile time.
         */
        constexpr procedure(set_flag5) noexcept { flag_container |= 16; }

        /**
         * @brief Sets the flag at position 6 to 1.
         * This method sets the bit at position 6 in the flag container to 1.
         * @exception This method does not throw any exceptions.
         * @note This is a constexpr function and can be evaluated at compile time.
         */
        constexpr procedure(set_flag6) noexcept { flag_container |= 32; }

        /**
         * @brief Sets the flag at position 7 to 1.
         * This method sets the bit at position 7 in the flag container to 1.
         * @exception This method does not throw any exceptions.
         * @note This is a constexpr function and can be evaluated at compile time.
         */
        constexpr procedure(set_flag7) noexcept { flag_container |= 64; }

        /**
         * @brief Sets the flag at position 8 to 1.
         * This method sets the bit at position 8 (the most significant bit) in the flag container to 1.
         * @exception This method does not throw any exceptions.
         * @note This is a constexpr function and can be evaluated at compile time.
         */
        constexpr procedure(set_flag8) noexcept { flag_container |= 128; }

        /**
         * @brief Sets all flags in the bfs_8 container to 1.
         * This method sets all 8 bits in the flag container to 1, resulting in a value of 0xFF.
         * @exception This method does not throw any exceptions.
         * @note This is a constexpr function and can be evaluated at compile time.
         * @code
         * bfs_8 bfs;
         * bfs.set_all(); // Set all flags to 1
         * std::cout << std::hex << bfs.get(); // Output: FF
         * @endcode
         */
        constexpr procedure(set_all) noexcept { flag_container |= 255; }

        /**
         * @brief Sets all flags to 1 (alternative to set_all()).
         * This method is functionally identical to set_all() and sets all 8 bits to 1.
         * @exception This method does not throw any exceptions.
         * @note This is a constexpr function and can be evaluated at compile time.
         */
        constexpr procedure(set) noexcept { flag_container |= 255; }

        /**
         * @brief Sets the specified flag to 1 based on position.
         * This method sets the bit at the specified position (1-8) to 1.
         * @param position The position of the flag to set (1-8).
         * @exception This method does not throw any exceptions.
         * @note This is a constexpr function and can be evaluated at compile time.
         * @code
         * bfs_8 bfs;
         * bfs.set(5); // Set bit 5 to 1
         * @endcode
         */
        constexpr void set(size_t position) noexcept
        {
            if (position == 1)
                set_flag1();
            else if (position == 2)
                set_flag2();
            else if (position == 3)
                set_flag3();
            else if (position == 4)
                set_flag4();
            else if (position == 5)
                set_flag5();
            else if (position == 6)
                set_flag6();
            else if (position == 7)
                set_flag7();
            else if (position == 8)
                set_flag8();
            else
                std::cout << "out of range error";
        }

        /// @brief Gets the value of the flag container.
        /// @return The current value of the flag container.
        constexpr uint8_t get() const noexcept { return flag_container; }

        /// @brief Gets the value of a specific flag based on position.
        /// @param position the position of the flag to get (1-8).
        /// @return the value of the specified flag (0 or 1).
        bool get(size_t position) const
        {
            if (position > 8)
                throw std::out_of_range(
                    "Error: Position " +
                    std::to_string(position) +
                    " is out of range (0-7) for uint8_t.");
            position--;
            uint8_t mask = 1 << position;
            if (flag_container & mask)
                return 1;
            else
                return 0;
        }

        /**
         * @brief Resets all flags to 0.
         * This method clears all 8 bits in the flag container, setting the value to 0x00.
         * @exception This method does not throw any exceptions.
         * @note This is a constexpr function and can be evaluated at compile time.
         * @code
         * bfs_8 bfs(0xFF);
         * bfs.reset_all(); // Reset all flags to 0
         * std::cout << std::hex << bfs.get(); // Output: 0
         * @endcode
         */
        constexpr procedure(reset_all) noexcept { flag_container &= 0; }

        /**
         * @brief Resets the flag at position 1 to 0.
         * This method clears the bit at position 1 in the flag container.
         * @exception This method does not throw any exceptions.
         * @note This is a constexpr function and can be evaluated at compile time.
         */
        constexpr procedure(reset_flag1) noexcept { flag_container &= ~(1); }

        /**
         * @brief Resets the flag at position 2 to 0.
         * This method clears the bit at position 2 in the flag container.
         * @exception This method does not throw any exceptions.
         * @note This is a constexpr function and can be evaluated at compile time.
         */
        constexpr procedure(reset_flag2) noexcept { flag_container &= ~(2); }

        /**
         * @brief Resets the flag at position 3 to 0.
         * This method clears the bit at position 3 in the flag container.
         * @exception This method does not throw any exceptions.
         * @note This is a constexpr function and can be evaluated at compile time.
         */
        constexpr procedure(reset_flag3) noexcept { flag_container &= ~(4); }

        /**
         * @brief Resets the flag at position 4 to 0.
         * This method clears the bit at position 4 in the flag container.
         * @exception This method does not throw any exceptions.
         * @note This is a constexpr function and can be evaluated at compile time.
         */
        constexpr procedure(reset_flag4) noexcept { flag_container &= ~(8); }

        /**
         * @brief Resets the flag at position 5 to 0.
         * This method clears the bit at position 5 in the flag container.
         * @exception This method does not throw any exceptions.
         * @note This is a constexpr function and can be evaluated at compile time.
         */
        constexpr procedure(reset_flag5) noexcept { flag_container &= ~(16); }

        /**
         * @brief Resets the flag at position 6 to 0.
         * This method clears the bit at position 6 in the flag container.
         * @exception This method does not throw any exceptions.
         * @note This is a constexpr function and can be evaluated at compile time.
         */
        constexpr procedure(reset_flag6) noexcept { flag_container &= ~(32); }

        /**
         * @brief Resets the flag at position 7 to 0.
         * This method clears the bit at position 7 in the flag container.
         * @exception This method does not throw any exceptions.
         * @note This is a constexpr function and can be evaluated at compile time.
         */
        constexpr procedure(reset_flag7) noexcept { flag_container &= ~(64); }

        /**
         * @brief Resets the flag at position 8 to 0.
         * This method clears the bit at position 8 in the flag container.
         * @exception This method does not throw any exceptions.
         * @note This is a constexpr function and can be evaluated at compile time.
         */
        constexpr procedure(reset_flag8) noexcept { flag_container &= ~(128); }

        /**
         * @brief Resets the flag at a specific position to 0.
         * This method clears the bit at the specified position (1-8).
         * @param position The position of the flag to reset (1-8).
         * @exception This method does not throw any exceptions.
         * @note This is a constexpr function and can be evaluated at compile time.
         * @code
         * bfs_8 bfs(0xFF);
         * bfs.reset(5); // Reset bit 5 to 0
         * @endcode
         */
        constexpr void reset(size_t position) noexcept
        {
            if (position == 1)
                reset_flag1();
            else if (position == 2)
                reset_flag2();
            else if (position == 3)
                reset_flag3();
            else if (position == 4)
                reset_flag4();
            else if (position == 5)
                reset_flag5();
            else if (position == 6)
                reset_flag6();
            else if (position == 7)
                reset_flag7();
            else if (position == 8)
                reset_flag8();
            else
                std::cout << "out of range error";
        }

        /**
         * @brief Gets the value of a specific flag using array-like syntax.
         * This operator allows accessing individual flags using array notation.
         * @param position the position of the flag to get (1-8).
         * @return the value of the specified flag (0 or 1).
         * @code
         * bfs_8 bfs(0x0F);
         * bool value = bfs[3]; // Get value of flag at position 3
         * @endcode
         */
        bool operator[](size_t position) const
        {
            if (position > 8 || position < 1)
                std::cerr << "out of rang error\n";
            return get(position);
        }

        /**
         * @brief Assigns a uint8_t value to the flag container.
         * This assignment operator sets the entire flag container to the specified value.
         * @param value the value to set the flag container to.
         * @exception This operator does not throw any exceptions.
         * @code
         * bfs_8 bfs;
         * bfs = 0xAB; // Set all flags to 0xAB
         * @endcode
         */
        constexpr void operator=(const uint8_t &value) noexcept { flag_container = value; }

        /**
         * @brief Copy assignment operator.
         * This operator copies the flag container value from another bfs_8 object.
         * @param other the bfs_8 object to copy from.
         * @exception This operator does not throw any exceptions.
         */
        constexpr void operator=(const bfs_8 &other) noexcept { flag_container = other.flag_container; }

        /**
         * @brief Inequality comparison with uint8_t value.
         * Compares the flag container with a uint8_t value.
         * @param value the value to compare against.
         * @return true if the flag container is not equal to the value, false otherwise.
         * @code
         * bfs_8 bfs(0x42);
         * if (bfs != 0x42) {  handle inequality }
         * @endcode
         */
        constexpr bool operator!=(const uint8_t &value) const noexcept { return flag_container != value; }

        /**
         * @brief Inequality comparison with another bfs_8 object.
         * Compares two bfs_8 flag containers.
         * @param other the bfs_8 object to compare against.
         * @return true if the flag containers are not equal, false otherwise.
         */
        constexpr bool operator!=(const bfs_8 &other) const noexcept { return flag_container != other.flag_container; }
        /**
         * @brief Equality comparison with uint8_t value.
         * Compares the flag container with a uint8_t value.
         * @param value the value to compare against.
         * @return true if the flag container is equal to the value, false otherwise.
         * @code
         * bfs_8 bfs(0x42);
         * if (bfs == 0x42) { handle equality }
         * @endcode
         */
        constexpr bool operator==(const uint8_t &value) const noexcept { return flag_container == value; }

        /**
         * @brief Equality comparison with another bfs_8 object.
         * Compares two bfs_8 flag containers.
         * @param other the bfs_8 object to compare against.
         * @return true if the flag containers are equal, false otherwise.
         */
        constexpr bool operator==(const bfs_8 &other) const noexcept { return flag_container == other.flag_container; }

        /**
         * @brief Destructor for bfs_8.
         * This is a trivial destructor as bfs_8 contains only a single uint8_t value.
         * No explicit cleanup is required.
         */
        ~bfs_8() = default;
    };

} // namespace udt

#endif // OPENUDT___CORE___BFS_BFS8_HPP