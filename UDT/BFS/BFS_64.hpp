#include "BFS_32.hpp"

#pragma once
#ifndef OPENUDT___UDT_BFS_BFS64_HPP
#define OPENUDT___UDT_BFS_BFS64_HPP

namespace udt
{
    /**
     * @brief A class to manage a 64-bit binary flag container using two BFS_32 objects.
     * The BFS_64 class provides constructors for initialization, methods to set and reset flags, and operators for comparison and assignment. It allows easy manipulation of individual flags within the container, as well as bulk operations to set or reset all flags at once.
     * @note The BFS_64 class uses two BFS_32 objects (lower and upper) to manage a total of 64 flags. The lower BFS_32 manages the lower 32 bits, while the upper BFS_32 manages the upper 32 bits of the 64-bit flag container.
     * @warning Care should be taken when using this class to ensure that flag positions are within the valid range (1-64) to avoid exceptions. There is a logic error in the set() and reset() methods that needs fixing (using || instead of &&).
     * @see BFS_32 for managing 32-bit flag containers, BFS_16 for 16-bit, and BFS_8 for 8-bit flag containers.
     * @author Ali Lafi
     * @date 2024-06
     */
    class BFS_64
    {
    private:
        BFS_32 lower;
        BFS_32 upper;

    public:
        /// @brief Default constructor initializes all flags to 0.
        BFS_64() noexcept = default;

        /**
         * @brief Constructor that initializes the BFS_64 object with a uint64_t value.
         * This constructor takes a uint64_t value as a parameter and initializes the BFS_64 object by splitting the 64-bit value into two 32-bit parts. The lower 32 bits of the value are assigned to the lower BFS_32 object, while the upper 32 bits are assigned to the upper BFS_32 object.
         * @param value The uint64_t value to initialize the BFS_64 object with.
         * @exception This constructor does not throw any exceptions.
         * @code
         * BFS_64 bfs(0x123456789ABCDEF0); // Initialize BFS_64 with a uint64_t value
         * std::cout << std::hex << bfs.get(); // Output: 123456789ABCDEF0
         * @endcode
         */
        BFS_64(const uint64_t &value) noexcept
        {
            lower = static_cast<uint32_t>(value & 0x00000000FFFFFFFF);
            upper = static_cast<uint32_t>((value >> 32) & 0x00000000FFFFFFFF);
        }

        /**
         * @brief Constructor that initializes the BFS_64 object with a BFS_8 object and three boolean positions.
         * This constructor takes a BFS_8 object and three boolean positions as parameters. The first position (p1) determines whether to assign to upper or lower BFS_32, while p2 and p3 are passed to the BFS_32 constructor.
         * @param other The BFS_8 object to initialize the BFS_64 object with.
         * @param p1 Boolean position indicating upper (true) or lower (false) assignment.
         * @param p2 Second position parameter.
         * @param p3 Third position parameter.
         * @exception This constructor does not throw any exceptions.
         */
        BFS_64(const BFS_8 &other, bool p1, bool p2, bool p3) noexcept
        {
            if (p1)
                upper = {other, p2, p3};
            else
                lower = {other, p2, p3};
        }

        /**
         * @brief Constructor that initializes the BFS_64 object with a BFS_16 object and two boolean positions.
         * @param other The BFS_16 object to initialize the BFS_64 object with.
         * @param p1 Boolean position indicating upper (true) or lower (false) assignment.
         * @param p2 Second position parameter.
         * @exception This constructor does not throw any exceptions.
         */
        BFS_64(const BFS_16 &other, bool p1, bool p2) noexcept
        {
            if (p1)
                upper = {other, p2};
            else
                lower = {other, p2};
        }

        /**
         * @brief Constructor that initializes the BFS_64 object with a BFS_32 object and a boolean position.
         * This constructor takes a BFS_32 object and a boolean position as parameters. Depending on the value of the position parameter, the BFS_32 object is assigned to either the upper or lower BFS_32 object of the BFS_64 class.
         * @param other The BFS_32 object to initialize the BFS_64 object with.
         * @param position Boolean position indicating whether to assign to upper (true) or lower (false).
         * @exception This constructor does not throw any exceptions.
         * @code
         * BFS_32 lower(0x12345678), upper(0x9ABCDEF0);
         * BFS_64 bfs(lower, false); // Initialize BFS_64 with a BFS_32 object assigned to the lower part
         * std::cout << std::hex << bfs.get(); // Output: 0000000012345678
         * @endcode
         */
        BFS_64(const BFS_32 &other, bool position) noexcept
        {
            if (position)
                upper = other;
            else
                lower = other;
        }

        /**
         * @brief Copy constructor for BFS_64.
         * This constructor creates a new BFS_64 object by copying the values from another BFS_64 object.
         * @param other The BFS_64 object to copy from.
         * @exception This constructor does not throw any exceptions.
         * @code
         * BFS_64 original(0x123456789ABCDEF0);
         * BFS_64 copy(original); // Create a copy
         * std::cout << std::hex << copy.get(); // Output: 123456789ABCDEF0
         * @endcode
         */
        BFS_64(const BFS_64 &other) noexcept
        {
            lower = other.lower;
            upper = other.upper;
        }

        /**
         * @brief Sets all flags in the BFS_64 object to 1.
         * This method sets all bits in both the lower and upper BFS_32 objects to 1.
         * @param position Unused parameter (kept for API consistency).
         * @exception This method does not throw any exceptions.
         * @code
         * BFS_64 bfs;
         * bfs.set_all(0); // Set all flags to 1
         * std::cout << std::hex << bfs.get(); // Output: FFFFFFFFFFFFFFFF
         * @endcode
         */
        void set_all(int position) noexcept;

        /**
         * @brief Sets all flags in the BFS_64 object to 1.
         * This method is an alternative to set_all() that sets all 64 bits to 1.
         * @exception This method does not throw any exceptions.
         * @code
         * BFS_64 bfs;
         * bfs.set(); // Set all flags to 1
         * std::cout << std::hex << bfs.get(); // Output: FFFFFFFFFFFFFFFF
         * @endcode
         */
        void set() noexcept;

        /**
         * @brief Sets the flag at the specified position to 1.
         * This method takes an integer parameter representing the position of the flag to set (1-64). It checks if the position is within the valid range and then sets the corresponding flag in either the lower or upper BFS_32 object depending on the position.
         * @param position The position of the flag to set (1-64).
         * @exception std::out_of_range If the position is less than 1 or greater than 64, an std::out_of_range exception is thrown.
         * @warning NOTE: There is a logic error in this method - it uses '||' instead of '&&' in the condition check.
         * @code
         * BFS_64 bfs;
         * bfs.set(5); // Set the 5th flag
         * try {
         *   bfs.set(65); // This will throw an exception
         * } catch (const std::out_of_range& e) {
         *   std::cerr << e.what() << std::endl;
         * }
         * @endcode
         */
        void set(int position);

        /**
         * @brief Resets all flags in the BFS_64 object to 0.
         * This method clears all 64 bits by resetting both the lower and upper 32-bit flag containers.
         * @exception This method does not throw any exceptions.
         * @code
         * BFS_64 bfs(0xFFFFFFFFFFFFFFFF);
         * bfs.reset_all(); // Reset all flags to 0
         * std::cout << std::hex << bfs.get(); // Output: 0
         * @endcode
         */
        void reset_all() noexcept;

        /**
         * @brief Resets all flags to 0 (alternative to reset_all()).
         * This method is functionally identical to reset_all() and clears all 64 bits.
         * @exception This method does not throw any exceptions.
         */
        void reset() noexcept;

        /**
         * @brief Resets the flag at the specified position to 0.
         * This method clears the bit at the specified position (1-64). It checks if the position is within the valid range and then resets the corresponding flag in either the lower or upper BFS_32 object.
         * @param position The position of the flag to reset (1-64).
         * @exception std::out_of_range If the position is less than 1 or greater than 64, an std::out_of_range exception is thrown.
         * @warning NOTE: There is a logic error in this method - it uses '||' instead of '&&' in the condition check.
         * @code
         * BFS_64 bfs(0xFFFFFFFFFFFFFFFF);
         * bfs.reset(5); // Reset flag at position 5
         * @endcode
         */
        void reset(int position);

        /**
         * @brief Gets the value of the lower 32 bits.
         * @return The value of the lower 32-bit flag container.
         * @code
         * BFS_64 bfs(0x123456789ABCDEF0);
         * uint32_t lower = bfs.get_lower(); // Returns 0x9ABCDEF0
         * @endcode
         */
        uint32_t get_lower() const noexcept;

        /**
         * @brief Gets the value of the upper 32 bits.
         * @return The value of the upper 32-bit flag container.
         * @code
         * BFS_64 bfs(0x123456789ABCDEF0);
         * uint32_t upper = bfs.get_upper(); // Returns 0x12345678
         * @endcode
         */
        uint32_t get_upper() const noexcept;

        /**
         * @brief Gets the complete 64-bit value of the flag container.
         * @return The 64-bit value combining both lower and upper flag containers.
         * @code
         * BFS_64 bfs(0x123456789ABCDEF0);
         * uint64_t value = bfs.get(); // Returns 0x123456789ABCDEF0
         * @endcode
         */
        uint64_t get() const noexcept;

        /**
         * @brief Gets the value of the flag at the specified position.
         * This method retrieves the bit value at the specified position (1-64).
         * @param position The position of the flag to get (1-64).
         * @return The value of the flag at the specified position (0 or 1).
         * @exception std::out_of_range If the position is less than 1 or greater than 64, an std::out_of_range exception is thrown.
         * @warning NOTE: There is a logic error in this method - it uses '||' instead of '&&' in the condition check.
         * @code
         * BFS_64 bfs(0x123456789ABCDEF0);
         * bool bit5 = bfs.get(5); // Get value of flag at position 5
         * @endcode
         */
        bool get(int position) const;

        /**
         * @brief Gets the value of the flag at the specified position using array-like syntax.
         * This operator allows accessing individual flags using array notation.
         * @param position The position of the flag to get (1-64).
         * @return The value of the flag at the specified position.
         * @code
         * BFS_64 bfs(0x123456789ABCDEF0);
         * bool bit = bfs[5]; // Get value of flag at position 5
         * @endcode
         */
        bool operator[](int position) const;

        /**
         * @brief Assigns a uint8_t value to the lower 32 bits.
         * This operator sets the lower 32-bit flag container to the specified value.
         * @param other The uint8_t value to assign.
         */
        void operator=(const uint8_t &other) noexcept;

        /**
         * @brief Assigns a uint16_t value to the BFS_64 object.
         * This operator splits the uint16_t value into upper and lower 32-bit parts.
         * @param other The uint16_t value to assign.
         */
        void operator=(const uint16_t &other) noexcept;

        /**
         * @brief Assigns a uint32_t value to the BFS_64 object.
         * This operator splits the uint32_t value into upper and lower 32-bit parts.
         * @param other The uint32_t value to assign.
         * @code
         * BFS_64 bfs;
         * bfs = 0x12345678; // Assign a 32-bit value
         * @endcode
         */
        void operator=(const uint32_t &other) noexcept;

        /**
         * @brief Assigns a uint64_t value to the BFS_64 object.
         * This operator splits the uint64_t value into upper and lower 32-bit parts.
         * @param other The uint64_t value to assign.
         * @code
         * BFS_64 bfs;
         * bfs = 0x123456789ABCDEF0; // Assign a 64-bit value
         * std::cout << std::hex << bfs.get(); // Output: 123456789ABCDEF0
         * @endcode
         */
        void operator=(const uint64_t &other) noexcept;

        /**
         * @brief Assigns a BFS_8 value to the lower 32 bits.
         * @param other The BFS_8 object to assign.
         */
        void operator=(const BFS_8 &other) noexcept;

        /**
         * @brief Assigns a BFS_16 value to the lower 32 bits.
         * @param other The BFS_16 object to assign.
         */
        void operator=(const BFS_16 &other) noexcept;

        /**
         * @brief Assigns a BFS_32 value to the lower 32 bits.
         * @param other The BFS_32 object to assign.
         */
        void operator=(const BFS_32 &other) noexcept;

        /**
         * @brief Copy assignment operator for BFS_64.
         * This operator copies the flag container values from another BFS_64 object.
         * @param other The BFS_64 object to copy from.
         */
        void operator=(const BFS_64 &other) noexcept;

        /**
         * @brief Inequality comparison with uint8_t value.
         * @param other The value to compare.
         * @return true if not equal to the lower 32 bits, false otherwise.
         */
        constexpr bool operator!=(const uint8_t &other) const noexcept;

        /**
         * @brief Inequality comparison with uint16_t value.
         * @param other The value to compare.
         * @return true if not equal to the combined 64-bit value, false otherwise.
         */
        constexpr bool operator!=(const uint16_t &other) const noexcept;

        /**
         * @brief Inequality comparison with uint32_t value.
         * @param other The value to compare.
         * @return true if not equal to the combined 64-bit value, false otherwise.
         */
        constexpr bool operator!=(const uint32_t &other) const noexcept;

        /**
         * @brief Inequality comparison with uint64_t value.
         * @param other The value to compare.
         * @return true if not equal to the 64-bit value, false otherwise.
         */
        constexpr bool operator!=(const uint64_t &other) const noexcept;

        /**
         * @brief Inequality comparison with BFS_8 object.
         * @param other The BFS_8 object to compare.
         * @return true if not equal to the lower 32 bits, false otherwise.
         */
        constexpr bool operator!=(const BFS_8 &other) noexcept;

        /**
         * @brief Inequality comparison with BFS_16 object.
         * @param other The BFS_16 object to compare.
         * @return true if not equal to the lower 32 bits, false otherwise.
         */
        constexpr bool operator!=(const BFS_16 &other) noexcept;

        /**
         * @brief Inequality comparison with BFS_32 object.
         * @param other The BFS_32 object to compare.
         * @return true if not equal to the lower 32 bits, false otherwise.
         */
        constexpr bool operator!=(const BFS_32 &other) noexcept;

        /**
         * @brief Inequality comparison with another BFS_64 object.
         * Compares two BFS_64 flag containers.
         * @param other The BFS_64 object to compare.
         * @return true if not equal, false otherwise.
         */
        constexpr bool operator!=(const BFS_64 &other) const noexcept;

        /**
         * @brief Equality comparison with uint8_t value.
         * @param other The value to compare.
         * @return true if equal to the lower 32 bits, false otherwise.
         */
        constexpr bool operator==(const uint8_t &other) const noexcept;

        /**
         * @brief Equality comparison with uint16_t value.
         * @param other The value to compare.
         * @return true if equal to the combined 64-bit value, false otherwise.
         */
        constexpr bool operator==(const uint16_t &other) const noexcept;

        /**
         * @brief Equality comparison with uint32_t value.
         * @param other The value to compare.
         * @return true if equal to the combined 64-bit value, false otherwise.
         */
        constexpr bool operator==(const uint32_t &other) const noexcept;

        /**
         * @brief Equality comparison with uint64_t value.
         * @param other The value to compare.
         * @return true if equal to the 64-bit value, false otherwise.
         */
        constexpr bool operator==(const uint64_t &other) const noexcept;

        /**
         * @brief Equality comparison with BFS_8 object.
         * @param other The BFS_8 object to compare.
         * @return true if equal to the lower 32 bits, false otherwise.
         */
        constexpr bool operator==(const BFS_8 &other) noexcept;

        /**
         * @brief Equality comparison with BFS_16 object.
         * @param other The BFS_16 object to compare.
         * @return true if equal to the lower 32 bits, false otherwise.
         */
        constexpr bool operator==(const BFS_16 &other) noexcept;

        /**
         * @brief Equality comparison with BFS_32 object.
         * @param other The BFS_32 object to compare.
         * @return true if equal to the lower 32 bits, false otherwise.
         */
        constexpr bool operator==(const BFS_32 &other) noexcept;

        /**
         * @brief Equality comparison with another BFS_64 object.
         * Compares two BFS_64 flag containers.
         * @param other The BFS_64 object to compare.
         * @return true if equal, false otherwise.
         */
        constexpr bool operator==(const BFS_64 &other) const noexcept;

        /**
         * @brief Destructor for BFS_64.
         * This is a trivial destructor as BFS_64 contains only BFS_32 objects which manage resources automatically.
         * No explicit cleanup is required.
         */
        ~BFS_64() = default;
    };

    /// BFS_64 member function definitions
    void BFS_64::set_all(int position) noexcept
    {
        lower.set_all();
        upper.set_all();
    }

    void BFS_64::set() noexcept
    {
        lower.set_all();
        upper.set_all();
    }

    void BFS_64::set(int position)
    {
        if (position < 1 || position > 64)
            throw std::out_of_range("Position out of range");
        if (position >= 1 || position <= 32)
            lower.set(position);
        else
            upper.set(position - 32);
    }

    void BFS_64::reset_all() noexcept
    {
        lower.reset_all();
        upper.reset_all();
    }

    void BFS_64::reset() noexcept
    {
        lower.reset_all();
        upper.reset_all();
    }

    void BFS_64::reset(int position)
    {
        if (position < 1 || position > 64)
            throw std::out_of_range("Position out of range");
        if (position >= 1 || position <= 32)
            lower.reset(position);
        else
            upper.reset(position - 32);
    }

    uint32_t BFS_64::get_lower() const noexcept { return lower.get(); }

    uint32_t BFS_64::get_upper() const noexcept { return upper.get(); }

    uint64_t BFS_64::get() const noexcept
    {
        return (static_cast<uint64_t>(upper.get()) << 32) | lower.get();
    }

    bool BFS_64::get(int position) const
    {
        if (position < 1 || position > 64)
            throw std::out_of_range("Position out of range");
        if (position >= 1 || position <= 32)
            return lower.get(position);
        else
            return upper.get(position - 32);
    }

    bool BFS_64::operator[](int position) const { return get(position); }

    void BFS_64::operator=(const uint8_t &other) noexcept { lower = other; }

    void BFS_64::operator=(const uint16_t &other) noexcept
    {
        lower = static_cast<uint16_t>(other & 0x0000FFFF);
        upper = static_cast<uint16_t>((other >> 16) & 0x0000FFFF);
    }

    void BFS_64::operator=(const uint32_t &other) noexcept
    {
        lower = static_cast<uint16_t>(other & 0x0000FFFF);
        upper = static_cast<uint16_t>((other >> 16) & 0x0000FFFF);
    }

    void BFS_64::operator=(const uint64_t &other) noexcept
    {
        lower = static_cast<uint32_t>(other & 0x00000000FFFFFFFF);
        upper = static_cast<uint32_t>((other >> 32) & 0x00000000FFFFFFFF);
    }

    void BFS_64::operator=(const BFS_8 &other) noexcept { lower = other; }

    void BFS_64::operator=(const BFS_16 &other) noexcept { lower = other; }

    void BFS_64::operator=(const BFS_32 &other) noexcept { lower = other; }

    void BFS_64::operator=(const BFS_64 &other) noexcept
    {
        lower = other.lower;
        upper = other.upper;
    }

    constexpr bool BFS_64::operator!=(const uint8_t &other) const noexcept { return lower != other; }

    constexpr bool BFS_64::operator!=(const uint16_t &other) const noexcept
    {
        return lower != static_cast<uint16_t>(other & 0x0000FFFF) ||
               upper != static_cast<uint16_t>((other >> 16) & 0x0000FFFF);
    }

    constexpr bool BFS_64::operator!=(const uint32_t &other) const noexcept
    {
        return lower != static_cast<uint16_t>(other & 0x0000FFFF) ||
               upper != static_cast<uint16_t>((other >> 16) & 0x0000FFFF);
    }

    constexpr bool BFS_64::operator!=(const uint64_t &other) const noexcept
    {
        return lower != static_cast<uint32_t>(other & 0x00000000FFFFFFFF) ||
               upper != static_cast<uint32_t>((other >> 32) & 0x00000000FFFFFFFF);
    }

    constexpr bool BFS_64::operator!=(const BFS_8 &other) noexcept { return lower != other; }

    constexpr bool BFS_64::operator!=(const BFS_16 &other) noexcept { return lower != other; }

    constexpr bool BFS_64::operator!=(const BFS_32 &other) noexcept { return lower != other; }

    constexpr bool BFS_64::operator!=(const BFS_64 &other) const noexcept
    {
        return lower != other.lower &&
               upper != other.upper;
    }

    constexpr bool BFS_64::operator==(const uint8_t &other) const noexcept { return lower == other; }

    constexpr bool BFS_64::operator==(const uint16_t &other) const noexcept
    {
        return lower == static_cast<uint16_t>(other & 0x0000FFFF) &&
               upper == static_cast<uint16_t>((other >> 16) & 0x0000FFFF);
    }

    constexpr bool BFS_64::operator==(const uint32_t &other) const noexcept
    {
        return lower == static_cast<uint16_t>(other & 0x0000FFFF) &&
               upper == static_cast<uint16_t>((other >> 16) & 0x0000FFFF);
    }

    constexpr bool BFS_64::operator==(const uint64_t &other) const noexcept
    {
        return lower == static_cast<uint32_t>(other & 0x00000000FFFFFFFF) &&
               upper == static_cast<uint32_t>((other >> 32) & 0x00000000FFFFFFFF);
    }

    constexpr bool BFS_64::operator==(const BFS_8 &other) noexcept { return lower == other; }

    constexpr bool BFS_64::operator==(const BFS_16 &other) noexcept { return lower == other; }

    constexpr bool BFS_64::operator==(const BFS_32 &other) noexcept { return lower == other; }

    constexpr bool BFS_64::operator==(const BFS_64 &other) const noexcept
    {
        return lower == other.lower &&
               upper == other.upper;
    }
} // namespace udt

#endif // OPENUDT___UDT_BFS_BFS16_HPP