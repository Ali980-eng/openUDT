#include "bfs_8.hpp"

#pragma once
#ifndef OPENUDT___CORE___BFS_BFS16_HPP
#define OPENUDT___CORE___BFS_BFS16_HPP

namespace udt
{
    /**
     * @brief A class to manage a 16-bit binary flag container using two bfs_8 objects.
     * The bfs_16 class encapsulates two bfs_8 objects to represent a 16-bit flag container, allowing for manipulation of individual flags as well as bulk operations on the entire container.
     * @note The lower_byte member represents the lower 8 bits of the 16-bit container, while the upper_byte member represents the upper 8 bits. This design allows for efficient management of flags while maintaining a clear separation between the two halves of the container.
     * @warning When using the bfs_16 class, ensure that flag positions are within the valid range (1-16) to avoid out-of-range errors when setting or resetting flags.
     * @see bfs_8 for managing 8-bit flag containers and BFS_32 for managing 32-bit flag containers.
     */
    class bfs_16
    {
    private:
        bfs_8 lower_byte;
        bfs_8 upper_byte;

    public:
        /// @brief Default constructor initializes all flags to 0.
        bfs_16() noexcept : lower_byte(0), upper_byte(0) {}

        /// @brief Constructor that initializes the bfs_16 object with a uint16_t value.
        /// @param value The uint16_t value to initialize the bfs_16 object with.
        bfs_16(const uint16_t &value) noexcept : lower_byte(static_cast<uint8_t>(value & 0x00FF)),
                                                 upper_byte(static_cast<uint8_t>((value >> 8) & 0x00FF)) {}

        /// @brief Constructor that initializes the bfs_16 object with two uint8_t values.
        /// @param upper_v The upper 8 bits value to initialize the bfs_16 object with.
        /// @param lower_v The lower 8 bits value to initialize the bfs_16 object with.
        bfs_16(const uint8_t &upper_v,
               const uint8_t &lower_v) noexcept : upper_byte(upper_v), lower_byte(lower_v) {}

        /// @brief Constructor that initializes the bfs_16 object with two int values.
        /// @param upper_val The upper 8 bits value to initialize the bfs_16 object with.
        /// @param lower_val The lower 8 bits value to initialize the bfs_16 object with.
        bfs_16(const int &upper_val,
               const int &lower_val) noexcept : upper_byte(static_cast<uint8_t>(upper_val)),
                                                lower_byte(static_cast<uint8_t>(lower_val)) {}

        /// @brief Constructor that initializes the bfs_16 object with two bfs_8 objects.
        /// @param upper_v The upper 8 bits value to initialize the bfs_16 object with.
        /// @param lower_v The lower 8 bits value to initialize the bfs_16 object with.
        bfs_16(const bfs_8 &upper_v,
               const bfs_8 &lower_v) noexcept : upper_byte(upper_v), lower_byte(lower_v) {}

        /// @brief Constructor that initializes the bfs_16 object with a bfs_8 object and a position.
        /// @param other The bfs_8 object to initialize the bfs_16 object with.
        /// @param position The position (true for upper byte, false for lower byte).
        bfs_16(const bfs_8 &other, bool position) noexcept
        {
            if (position)
                upper_byte = other;
            else
                lower_byte = other;
        }

        /// @brief Constructor that initializes the bfs_16 object with a position.
        /// @param position The position (1-16) to set the flag.
        bfs_16(size_t position)
        {
            if (position > 16)
                throw std::out_of_range("Position out of range");
            if (position >= 1 && position <= 8)
                lower_byte.set(position);
            else
                upper_byte.set(position - 8);
        }

        /// @brief Copy constructor for bfs_16.
        /// @param other The bfs_16 object to copy from.
        bfs_16(const bfs_16 &other) noexcept : lower_byte(other.lower_byte),
                                               upper_byte(other.upper_byte) {}

        /// @brief Sets all flags to 1.
        constexpr procedure(set_all) noexcept
        {
            lower_byte.set_all();
            upper_byte.set_all();
        }

        /// @brief Sets all flags to 1.
        constexpr procedure(set) noexcept
        {
            lower_byte.set_all();
            upper_byte.set_all();
        }

        /// @brief Sets the value of the bfs_16 object.
        /// @param value The uint16_t value to set the bfs_16 object with.
        void set(uint16_t value) noexcept
        {
            lower_byte = static_cast<uint8_t>(value & 0x00FF);
            upper_byte = static_cast<uint8_t>((value >> 8) & 0x00FF);
        }

        /// @brief Sets the flag at the specified position.
        /// @param position The position (1-16) to set the flag.
        void set(size_t position)
        {
            if (position > 16)
                throw std::out_of_range("Position out of range");
            if (position >= 1 && position <= 8)
                lower_byte.set(position);
            else
                upper_byte.set(position - 8);
        }

        /// @brief Resets all flags to 0.
        constexpr procedure(reset_all) noexcept
        {
            lower_byte.reset_all();
            upper_byte.reset_all();
        }

        /**
         * @brief Resets all flags to 0.
         * This method sets all bits in both the lower_byte and upper_byte to 0, effectively clearing all flags in the bfs_16 object.
         * @note This method does not take any parameters and does not return any value. It is a constexpr function, meaning it can be evaluated at compile time if used in a constant expression context.
         * @exception This method does not throw any exceptions.
         * @see bfs_16::reset(int position) for resetting a specific flag based on position.
         */
        constexpr procedure(reset) noexcept
        {
            lower_byte.reset_all();
            upper_byte.reset_all();
        }

        /**
         * @brief Resets the flag at the specified position to 0.
         * This method takes an integer parameter representing the position of the flag to reset (1-16). It checks if the position is within the valid range and then resets the corresponding flag in either the lower_byte or upper_byte depending on the position.
         * @param position The position of the flag to reset (1-16).
         * @exception std::out_of_range If the position is less than 1 or greater than 16, an std::out_of_range exception is thrown with a message indicating that the position is out of BFS bit range.
         * @see bfs_16::reset() for resetting all flags to 0.
         * @note This method does not return any value.
         * @warning Ensure that the position parameter is within the valid range to avoid exceptions.
         * @code
         * bfs_16 bfs;
         * bfs.set(5); // Set the 5th flag
         * bfs.reset(5); // Reset the 5th flag
         * try {
         *   bfs.reset(17); // This will throw an exception
         * } catch (const std::out_of_range& e) {
         *  std::cerr << e.what() << std::endl; // Output: Position is out of BFS bit range
         * }
         * @endcode
         */
        void reset(size_t position)
        {
            if (position > 16)
                throw std::out_of_range("Position is out of BFS bit range");
            if (position <= 8 && position >= 1)
                lower_byte.reset_all();
            else
                upper_byte.reset_all();
        }

        /// @brief Gets the value of the lower byte.
        /// @return The value of the lower byte.
        uint8_t get_lower() const noexcept { return lower_byte.get(); }

        /// @brief Gets the value of the upper byte.
        /// @return The value of the upper byte.
        uint8_t get_upper() const noexcept { return upper_byte.get(); }

        /// @brief Gets the value of the 16-bit BFS object.
        /// @return The value of the 16-bit BFS object.
        uint16_t get() const noexcept { return (static_cast<uint16_t>(upper_byte.get()) << 8) | lower_byte.get(); }

        /**
         * @brief Gets the value of the flag at the specified position.
         * This method takes an integer parameter representing the position of the flag to get (1-16). It checks if the position is within the valid range and then returns the corresponding flag value from either the lower_byte or upper_byte depending on the position.
         * @param position The position of the flag to get (1-16).
         * @return The value of the flag at the specified position.
         * @exception std::out_of_range If the position is less than 1 or greater than 16, an std::out_of_range exception is thrown with a message indicating that the position is out of BFS bit range.
         * @see bfs_16::set(int position) for setting a specific flag based on position.
         * @note This method does not modify any flags in the bfs_16 object.
         * @warning Ensure that the position parameter is within the valid range to avoid exceptions.
         * @code
         * bfs_16 bfs;
         * bfs.set(5); // Set the 5th flag
         * bool value = bfs.get(5); // Get the value of the 5th flag
         * try {
         *   bool value = bfs.get(17); // This will throw an exception
         * } catch (const std::out_of_range& e) {
         *  std::cerr << e.what() << std::endl; // Output: Position out of range
         * }
         * @endcode
         */
        bool get(size_t position) const
        {
            if (position > 16)
                throw std::out_of_range("Position out of range");
            if (position >= 1 && position <= 8)
                return lower_byte.get(position);
            else
                return upper_byte.get(position - 8);
        }

        /// @brief Gets the value of the flag at the specified position using array-like syntax.
        /// @param position The position of the flag to get (1-16).
        /// @return The value of the flag at the specified position.
        bool operator[](int position) { return get(position); }

        /**
         * @brief Sets the value of the bfs_16 object using a uint16_t value.
         * This operator overload allows you to assign a uint16_t value directly to a bfs_16 object. It takes the uint16_t value, extracts the lower 8 bits and assigns it to the lower_byte, and extracts the upper 8 bits and assigns it to the upper_byte.
         * @param other The uint16_t value to assign to the bfs_16 object.
         * @exception This operator does not throw any exceptions.
         * @see bfs_16::operator=(const bfs_8 &other) for assigning a bfs_8 object to the bfs_16 object.
         * @note This operator does not return any value.
         * @code
         *  bfs_16 bfs;
         * bfs = 0xABCD; // Assign a uint16_t value to the bfs_16 object
         * std::cout << std::hex << bfs.get(); // Output: ABCD
         * @endcode
         * @warning Ensure that the uint16_t value being assigned is within the valid range (0-65535) to avoid unexpected behavior.
         */
        void operator=(const uint16_t &other) noexcept
        {
            lower_byte = static_cast<uint8_t>(other & 0x00FF);
            upper_byte = static_cast<uint8_t>((other >> 8) & 0x00FF);
        }

        /// @brief Sets the value of the bfs_16 object using a uint8_t value.
        /// @param other The uint8_t value to assign to the bfs_16 object.
        void operator=(const uint8_t &other) noexcept { lower_byte = other; }

        /// @brief Sets the value of the bfs_16 object using a bfs_8 object.
        /// @param other The bfs_8 object to assign to the bfs_16 object.
        void operator=(const bfs_8 &other) noexcept { lower_byte = other; }

        /// @brief Sets the value of the bfs_16 object using a bfs_16 object.
        /// @param other The bfs_16 object to assign to the bfs_16 object.
        void operator=(const bfs_16 &other) noexcept
        {
            lower_byte = other.lower_byte;
            upper_byte = other.upper_byte;
        }

        /// @brief Checks if the bfs_16 object is not equal to a uint16_t value.
        /// @param other The uint16_t value to compare with.
        /// @return true if the objects are not equal, false otherwise.
        constexpr bool operator!=(const uint16_t &other) const noexcept
        {
            return lower_byte != static_cast<uint8_t>(other & 0x00FF) ||
                   upper_byte != static_cast<uint8_t>((other >> 8) & 0x00FF);
        }

        /// @brief Checks if the bfs_16 object is not equal to a uint8_t value.
        /// @param other The uint8_t value to compare with.
        /// @return true if the objects are not equal, false otherwise.
        constexpr bool operator!=(const uint8_t &other) const noexcept
        {
            return lower_byte != other;
        }

        /// @brief Checks if the bfs_16 object is not equal to a bfs_8 object.
        /// @param other The bfs_8 object to compare with.
        /// @return true if the objects are not equal, false otherwise.
        constexpr bool operator!=(const bfs_8 &other) const noexcept
        {
            return lower_byte != other;
        }

        /// @brief Checks if the bfs_16 object is not equal to a bfs_16 object.
        /// @param other The bfs_16 object to compare with.
        /// @return true if the objects are not equal, false otherwise.
        constexpr bool operator!=(const bfs_16 &other) const noexcept
        {
            return lower_byte != other.lower_byte || upper_byte != other.upper_byte;
        }

        /// @brief Checks if the bfs_16 object is equal to a uint8_t value.
        /// @param other The uint8_t value to compare with.
        /// @return true if the objects are equal, false otherwise.
        constexpr bool operator==(const uint8_t &other) const noexcept
        {
            return lower_byte == other;
        }

        /// @brief Checks if the bfs_16 object is equal to a bfs_8 object.
        /// @param other The bfs_8 object to compare with.
        /// @return true if the objects are equal, false otherwise.
        constexpr bool operator==(const bfs_8 &other) const noexcept
        {
            return lower_byte == other;
        }

        /// @brief Checks if the bfs_16 object is equal to a bfs_16 object.
        /// @param other The bfs_16 object to compare with.
        /// @return true if the objects are equal, false otherwise.
        constexpr bool operator==(const bfs_16 &other) const noexcept
        {
            return lower_byte == other.lower_byte && upper_byte == other.upper_byte;
        }

        /// @brief Checks if the bfs_16 object is equal to a uint16_t value.
        /// @param other The uint16_t value to compare with.
        /// @return true if the objects are equal, false otherwise.
        constexpr bool operator==(const uint16_t &other) const noexcept
        {
            return lower_byte == static_cast<uint8_t>(other & 0x00FF) &&
                   upper_byte == static_cast<uint8_t>((other >> 8) & 0x00FF);
        }

        /**
         * @brief Destructor for bfs_16.
         * This is a trivial destructor as bfs_16 contains only two bfs_8 objects which manage resources automatically.
         * No explicit cleanup is required.
         */
        ~bfs_16() = default;
    };
} // namespace udt

#endif // OPENUDT___CORE___BFS_BFS16_HPP