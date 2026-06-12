#include "bfs_16.hpp"

#pragma once
#ifndef OPENUDT___UDT_BFS_BFS32_HPP
#define OPENUDT___UDT_BFS_BFS32_HPP

namespace udt
{
    /**
     * @brief A class to manage a 32-bit binary flag container using two bfs_16 objects.
     * The bfs_32 class provides constructors for initialization, methods to set and reset flags, and operators for comparison and assignment. It allows easy manipulation of individual flags within the container, as well as bulk operations to set or reset all flags at once.
     * @note The bfs_32 class uses two bfs_16 objects (lower and upper) to manage a total of 32 flags. The lower bfs_16 manages the lower 16 bits, while the upper bfs_16 manages the upper 16 bits of the 32-bit flag container.
     * @warning Care should be taken when using this class to ensure that flag positions are within the valid range (1-32) to avoid exceptions.
     * @see bfs_16 for managing 16-bit flag containers and bfs_8 for managing 8-bit flag containers.
     */
    class bfs_32
    {
    private:
        bfs_16 lower;
        bfs_16 upper;

    public:
        /// @brief Default constructor initializes all flags to 0.
        bfs_32() noexcept = default;

        /**
         * @brief Constructor that initializes the bfs_32 object with a uint32_t value.
         * This constructor takes a uint32_t value as a parameter and initializes the bfs_32 object by splitting the 32-bit value into two 16-bit parts. The lower 16 bits of the value are assigned to the lower bfs_16 object, while the upper 16 bits are assigned to the upper bfs_16 object.
         * @param value The uint32_t value to initialize the bfs_32 object with.
         * @exception This constructor does not throw any exceptions.
         * @see bfs_32::set(uint32_t value) for setting the value of an existing bfs_32 object with a uint32_t value.
         * @note This constructor allows for easy initialization of the bfs_32 object with a single 32-bit value, making it convenient to work with larger flag containers without needing to manually split the value into parts.
         * @code
         * bfs_32 bfs(0x12345678); // Initialize bfs_32 with a uint32_t value
         * std::cout << std::hex << bfs.get(); // Output: 12345678
         * @endcode
         * @warning Ensure that the uint32_t value being used for initialization is within the valid
         */
        bfs_32(const uint32_t &value) noexcept
        {
            lower = static_cast<uint16_t>(value & 0x0000FFFF);
            upper = static_cast<uint16_t>((value >> 16) & 0x0000FFFF);
        }

        /**
         * @brief Constructor that initializes the bfs_32 object with two uint16_t values.
         * This constructor takes two uint16_t values as parameters, representing the upper and lower parts of the 32-bit flag container. The first parameter (upper_v) is assigned to the upper bfs_16 object, while the second parameter (lower_v) is assigned to the lower bfs_16 object.
         * @param upper_v The uint16_t value to initialize the upper part of the bfs_32 object.
         * @param lower_v The uint16_t value to initialize the lower part of the bfs_32 object.
         * @exception This constructor does not throw any exceptions.
         * @see bfs_32::set(uint16_t upper_v, uint16_t lower_v) for setting the values of an existing bfs_32 object with two uint16_t values.
         * @note This constructor allows for flexible initialization of the bfs_32 object using two separate 16-bit values, which can be useful when working with data that is naturally split into upper and lower parts.
         * @code
         * bfs_32 bfs(0x1234, 0x5678); //
         * Initialize bfs_32 with two uint16_t values
         * std::cout << std::hex << bfs.get(); // Output: 12345678
         * @endcode
         * @warning Ensure that the uint16_t values being used for initialization are within the valid range (0-65535) to avoid unexpected behavior.
         */
        bfs_32(const uint16_t &upper_v, const uint16_t &lower_v) noexcept
        {
            upper = upper_v;
            lower = lower_v;
        }

        /**
         * @brief Constructor that initializes the bfs_32 object with four uint8_t values.
         * This constructor takes four uint8_t values as parameters, representing the upper and lower parts
         * of the 32-bit flag container. The first two parameters (uuv and ulv) are assigned to the upper bfs_16 object, while the last two parameters (luv and llv) are assigned to the lower bfs_16 object.
         * @param uuv The uint8_t value to initialize the upper part of the upper bfs_16 object.
         * @param ulv The uint8_t value to initialize the lower part of the upper bfs_16 object.
         * @param luv The uint8_t value to initialize the upper part of the lower bfs_16 object.
         * @param llv The uint8_t value to initialize the lower part of the lower bfs_16 object.
         * @exception This constructor does not throw any exceptions.
         * @see bfs_32::set(uint8_t uuv, uint8_t ulv, uint8_t luv, uint8_t llv) for setting the values of an existing bfs_32 object with four uint8_t values.
         * @note This constructor allows for detailed initialization of the bfs_32 object using four separate 8-bit values, providing fine-grained control over the individual bytes of the flag container.
         * @code
         * bfs_32 bfs(0x12, 0x34, 0x56, 0x78); // Initialize bfs_32 with four uint8_t values
         * std::cout << std::hex << bfs.get(); // Output: 12345678
         * @endcode
         * @warning Ensure that the uint8_t values being used for initialization are within the valid range (0-255) to avoid unexpected behavior.
         */
        bfs_32(const uint8_t &uuv, const uint8_t &ulv,
               const uint8_t &luv, const uint8_t &llv) noexcept
        {
            upper = {uuv, ulv};
            lower = {luv, llv};
        }

        /**
         * @brief Constructor that initializes the bfs_32 object with four bfs_8 objects.
         * This constructor takes four bfs_8 objects as parameters, representing the upper and lower parts of the 32-bit flag container. The first two parameters (uuv and ulv) are assigned to the upper bfs_16 object, while the last two parameters (luv and llv) are assigned to the lower bfs_16 object.
         * @param uuv The bfs_8 object to initialize the upper part of the upper bfs_16 object.
         * @param ulv The bfs_8 object to initialize the lower part of the upper bfs_16 object.
         * @param luv The bfs_8 object to initialize the upper part of the lower bfs_16 object.
         * @param llv The bfs_8 object to initialize the lower part of the lower bfs_16 object.
         * @exception This constructor does not throw any exceptions.
         * @see bfs_32::set(const bfs_8 &uuv, const bfs_8 &ulv, const bfs_8 &luv, const bfs_8 &llv) for setting the values of an existing bfs_32 object with four bfs_8 objects.
         * @note This constructor allows for detailed initialization of the bfs_32 object using four separate bfs_8 objects, providing fine-grained control over the individual bytes of the flag container while utilizing the functionality of the bfs_8 class for managing 8-bit flags.
         * @code
         * bfs_8 byte1(0x12), byte2(0x34), byte3(0x56), byte4(0x78);
         * bfs_32 bfs(byte1, byte2, byte3, byte4); // Initialize bfs_32 with four bfs_8 objects
         * std::cout << std::hex << bfs.get(); // Output: 12345678
         * @endcode
         * @warning Ensure that the bfs_8 objects being used for initialization contain valid 8-bit values (0-255) to avoid unexpected behavior.
         */
        bfs_32(const bfs_8 &uuv, const bfs_8 &ulv,
               const bfs_8 &luv, const bfs_8 &llv) noexcept
        {
            upper = {uuv, ulv};
            lower = {luv, llv};
        }

        /**
         * @brief Constructor that initializes the bfs_32 object with two bfs_16 objects.
         * This constructor takes two bfs_16 objects as parameters, representing the upper and lower parts
         * of the 32-bit flag container. The first parameter (upper_v) is assigned to the upper bfs_16 object, while the second parameter (lower_v) is assigned to the lower bfs_16 object.
         * @param upper_v The bfs_16 object to initialize the upper part of the bfs_32 object.
         * @param lower_v The bfs_16 object to initialize the lower part of the bfs_32 object.
         * @exception This constructor does not throw any exceptions.
         * @see bfs_32::set(const bfs_16 &upper_v, const bfs_16 &lower_v) for setting the values of an existing bfs_32 object with two bfs_16 objects.
         * @note This constructor allows for straightforward initialization of the bfs_32 object using two bfs_16 objects, which can be useful when working with data that is naturally split into upper and lower parts while utilizing the functionality of the bfs_16 class for managing 16-bit flags.
         * @code
         * bfs_16 upper(0x1234), lower(0x5678);
         * bfs_32 bfs(upper, lower); // Initialize bfs_32 with two bfs_16 objects
         * std::cout << std::hex << bfs.get(); // Output: 12345678
         * @endcode
         * @warning Ensure that the bfs_16 objects being used for initialization contain valid 16-bit values (0-65535) to avoid unexpected behavior.
         */
        bfs_32(const bfs_16 &upper_v, const bfs_16 &lower_v) noexcept
        {
            upper = upper_v;
            lower = lower_v;
        }

        /**
         * @brief Constructor that initializes the bfs_32 object with a bfs_8 object and a position.
         * This constructor takes a bfs_8 object and a boolean position as parameters. Depending on
         * the value of the position parameter, the bfs_8 object is assigned to either the upper or lower bfs_16 object. If the position is true, the bfs_8 object is assigned to the upper bfs_16; if false, it is assigned to the lower bfs_16.
         * @param other The bfs_8 object to initialize the bfs_32 object with.
         * @param position The boolean position indicating whether to assign the bfs_8 object to the upper (true) or lower (false) bfs_16 object.
         * @exception This constructor does not throw any exceptions.
         * @see bfs_32::set(const bfs_8 &other, bool position) for setting the value of an existing bfs_32 object with a bfs_8 object and a position.
         * @note This constructor allows for flexible initialization of the bfs_32 object using a single bfs_8 object and a position, providing an easy way to set either the upper or lower part of the flag container based on the position parameter.
         * @code
         * bfs_8 byte(0x12);
         * bfs_32 bfs(byte, true); // Initialize bfs_32 with a bfs_8 object assigned to the upper part
         * std::cout << std::hex << bfs.get(); // Output: 12000000
         * bfs_32 bfs2(byte, false); // Initialize bfs_32 with a bfs_8 object assigned to the lower part
         * std::cout << std::hex << bfs2.get(); // Output: 00000012
         * @endcode
         * @warning Ensure that the bfs_8 object being used for initialization contains a valid
         */
        bfs_32(int position)
        {
            if (position < 1 || position > 32)
                throw std::out_of_range("Position out of range");
            if (position >= 1 && position <= 16)
                lower.set(position);
            else
                upper.set(position - 16);
        }

        /**
         * @brief Constructor that initializes the bfs_32 object with a bfs_8 object and two boolean positions.
         * This constructor takes a bfs_8 object and two boolean positions as parameters. Depending on
         * the values of the position parameters, the bfs_8 object is assigned to either the upper or lower bfs_16 object. If the first position (p1) is true, the bfs_8 object is assigned to the upper bfs_16; if false, it is assigned to the lower bfs_16. The second position (p2) is used to determine which part of the bfs_16 object to assign the bfs_8 object to, but it is not explicitly used in this constructor as it relies on the first position (p1) for assignment.
         * @param other The bfs_8 object to initialize the bfs_32 object with.
         * @param p1 The boolean position indicating whether to assign the bfs_8 object to the upper (true) or lower (false) bfs_16 object.
         * @param p2 The second boolean position, which is not explicitly used in this constructor but can be used for additional logic if needed.
         * @exception This constructor does not throw any exceptions.
         * @see bfs_32::set(const bfs_8 &other, bool p1, bool p2) for setting the value of an existing bfs_32 object with a bfs_8 object and two boolean positions.
         * @note This constructor allows for flexible initialization of the bfs_32 object using a single bfs_8 object and two boolean positions, providing an easy way to set either the upper or lower part of the flag container based on the first position parameter while allowing for additional logic with the second position parameter if needed.
         * @code
         * bfs_8 byte(0x12);
         * bfs_32 bfs(byte, true, false); // Initialize bfs_32 with a bfs_8 object assigned to the upper part
         * std::cout << std::hex << bfs.get(); // Output: 12000000
         * bfs_32 bfs2(byte, false, true); // Initialize bfs_32 with a bfs_8 object assigned to the lower part
         * std::cout << std::hex << bfs2.get(); // Output: 00000012
         * @endcode
         * @warning Ensure that the bfs_8 object being used for initialization contains a valid 8-bit value (0-255) to avoid unexpected behavior.
         */
        bfs_32(const bfs_8 &other, bool p1, bool p2) noexcept
        {
            if (p1)
                upper = {other, p2};
            else
                lower = {other, p1};
        }

        /**
         * @brief Constructor that initializes the bfs_32 object with a bfs_16 object and a boolean position.
         * This constructor takes a bfs_16 object and a boolean position as parameters. Depending on the value of the position parameter, the bfs_16 object is assigned to either the upper or lower bfs_16 object of the bfs_32 class. If the position is true, the bfs_16 object is assigned to the upper bfs_16; if false, it is assigned to the lower bfs_16.
         * @param other The bfs_16 object to initialize the bfs_32 object with.
         * @param position The boolean position indicating whether to assign the bfs_16 object to the upper (true) or lower (false) bfs_16 object of the bfs_32 class.
         * @exception This constructor does not throw any exceptions.
         * @see bfs_32::set(const bfs_16 &other, bool position) for setting the value of an existing bfs_32 object with a bfs_16 object and a boolean position.
         * @note This constructor allows for flexible initialization of the bfs_32 object using a single bfs_16 object and a boolean position, providing an easy way to set either the upper or lower part of the flag container based on the position parameter.
         * @code
         * bfs_16 upper(0x1234), lower(0x5678);
         * bfs_32 bfs(upper, true); // Initialize bfs_32 with a bfs_16 object assigned to the upper part
         * std::cout << std::hex << bfs.get(); // Output: 12340000
         * bfs_32 bfs2(lower, false); // Initialize bfs_32 with a bfs_16 object assigned to the lower part
         * std::cout << std::hex << bfs2.get(); // Output: 00005678
         * @endcode
         * @warning Ensure that the bfs_16 object being used for initialization contains a valid 16-bit value (0-65535) to avoid unexpected behavior.
         */
        bfs_32(const bfs_16 &other, bool position) noexcept
        {
            if (position)
                upper = other;
            else
                lower = other;
        }

        /**
         * @brief Copy constructor for bfs_32.
         * This constructor creates a new bfs_32 object by copying the values from another bfs_32 object. It takes a constant reference to another bfs_32 object as a parameter and initializes the new object by copying the lower and upper bfs_16 objects from the provided bfs_32 object.
         * @param other The bfs_32 object to copy from.
         * @exception This constructor does not throw any exceptions.
         * @see bfs_32::operator=(const bfs_32 &other) for assigning the values of one bfs_32 object to another after initialization.
         * @note This copy constructor allows for the creation of a new bfs_32 object that
         * is an exact copy of an existing bfs_32 object, making it easy to duplicate flag containers when needed.
         * @code
         * bfs_32 original(0x12345678); // Initialize original bfs_32 object
         * bfs_32 copy(original); // Create a copy of the original bfs_32 object using the copy constructor
         * std::cout << std::hex << copy.get(); // Output: 12345678
         * @endcode
         * @warning Ensure that the bfs_32 object being copied from is properly initialized to avoid copying uninitialized data.
         */
        bfs_32(const bfs_32 &other) noexcept
        {
            lower = other.lower;
            upper = other.upper;
        }

        /**
         * @brief Sets all flags in the bfs_32 object to 1.
         * This method sets all bits in both the lower and upper bfs_16 objects to 1, effectively setting all flags in the bfs_32 object. It does not take any parameters and does not return any value. This method is a convenient way to quickly set all flags in the bfs_32 object without needing to set each flag individually.
         * @exception This method does not throw any exceptions.
         * @see bfs_32::reset() for resetting all flags to 0.
         * @note This method is a constexpr function, meaning it can be evaluated at compile time if used in a constant expression context, allowing for efficient initialization of bfs_32 objects with all flags set to 1.
         * @code
         * bfs_32 bfs;
         * bfs.set_all(); // Set all flags in the bfs_32 object to 1
         * std::cout << std::hex << bfs.get(); // Output: FFFFFFFF
         * @endcode
         * @warning Using this method will set all flags in the bfs_32 object to
         */
        void set_all() noexcept;

        /**
         * @brief Sets all flags in the bfs_32 object to 1.
         * This method is functionally identical to the set_all() method and serves the same purpose of setting all bits in both the lower and upper bfs_16 objects to 1, effectively setting all flags in the bfs_32 object. It does not take any parameters and does not return any value. This method is provided as an alternative to set_all() for convenience and readability when setting all flags in the bfs_32 object.
         * @exception This method does not throw any exceptions.
         * @see bfs_32::reset() for resetting all flags to 0.
         * @note This method is a constexpr function, meaning it can be evaluated at compile time if used in a constant expression context, allowing for efficient initialization of bfs_32 objects with all flags set to 1.
         * @code
         * bfs_32 bfs;
         * bfs.set(); // Set all flags in the bfs_32 object to 1
         * std::cout << std::hex << bfs.get(); // Output: FFFFFFFF
         * @endcode
         * @warning Using this method will set all flags in the bfs_32 object to 1, which may not be desirable in all situations, so use with caution.
         */
        void set() noexcept;

        /**
         * @brief Sets the flag at the specified position to 1.
         * This method takes an integer parameter representing the position of the flag to set (1-
         * 32). It checks if the position is within the valid range and then sets the corresponding flag in either the lower or upper bfs_16 object depending on the position. If the position is between 1 and 16, it sets the flag in the lower bfs_16; if the position is between 17 and 32, it sets the flag in the upper bfs_16 (adjusting the position by subtracting 16).
         * @param position The position of the flag to set (1-32).
         * @exception std::out_of_range If the position is less than 1 or greater than 32, an std::out_of_range exception is thrown with a message indicating that the position is out of range.
         * @see bfs_32::reset(int position) for resetting a specific flag based on position.
         * @note This method does not return any value.
         * @warning Ensure that the position parameter is within the valid range to avoid exceptions.
         * @code
         * bfs_32 bfs;
         * bfs.set(5); // Set the 5th flag
         * try {
         *  bfs.set(33); // This will throw an exception
         * } catch (const std::out_of_range& e) {
         * std::cerr << e.what() << std::endl; // Output: Position out of range
         * }
         * @endcode
         */
        void set(int position);

        /**
         * @brief Resets all flags to 0.
         * This method clears all 32 bits by resetting both the lower and upper 16-bit flag containers.
         * @exception This method does not throw any exceptions.
         * @code
         * bfs_32 bfs(0xFFFFFFFF);
         * bfs.reset_all(); // Reset all flags to 0
         * std::cout << std::hex << bfs.get(); // Output: 0
         * @endcode
         */
        void reset_all();

        /**
         * @brief Resets all flags to 0 (constexpr version).
         * This method is a constexpr variant of reset_all() that can be evaluated at compile time.
         * @exception This method does not throw any exceptions.
         * @note This is a constexpr function.
         */
        constexpr void reset() noexcept;

        /**
         * @brief Resets the flag at the specified position to 0.
         * This method clears the bit at the specified position (1-32). It checks if the position is within the valid range and then resets the corresponding flag in either the lower or upper bfs_16 object depending on the position.
         * @param position The position of the flag to reset (1-32).
         * @exception std::out_of_range If the position is less than 1 or greater than 32, an std::out_of_range exception is thrown.
         * @note This method does not return any value.
         * @code
         * bfs_32 bfs(0xFFFFFFFF);
         * bfs.reset(5); // Reset flag at position 5
         * try {
         *   bfs.reset(33); // This will throw an exception
         * } catch (const std::out_of_range& e) {
         *   std::cerr << e.what() << std::endl;
         * }
         * @endcode
         */
        void reset(int position);

        /**
         * @brief Gets the value of the lower 16 bits.
         * @return The value of the lower 16-bit flag container.
         * @code
         * bfs_32 bfs(0x12345678);
         * uint16_t lower = bfs.get_lower(); // Returns 0x5678
         * @endcode
         */
        uint16_t get_lower() const noexcept;

        /**
         * @brief Gets the value of the upper 16 bits.
         * @return The value of the upper 16-bit flag container.
         * @code
         * bfs_32 bfs(0x12345678);
         * uint16_t upper = bfs.get_upper(); // Returns 0x1234
         * @endcode
         */
        uint16_t get_upper() const noexcept;

        /**
         * @brief Gets the complete 32-bit value of the flag container.
         * @return The 32-bit value combining both lower and upper flag containers.
         * @code
         * bfs_32 bfs(0x12345678);
         * uint32_t value = bfs.get(); // Returns 0x12345678
         * @endcode
         */
        uint32_t get() const noexcept;

        /**
         * @brief Gets the value of the flag at the specified position.
         * This method retrieves the bit value at the specified position (1-32). It checks if the position is within the valid range and then returns the corresponding flag value from either the lower or upper bfs_16 object.
         * @param position The position of the flag to get (1-32).
         * @return The value of the flag at the specified position (0 or 1).
         * @exception std::out_of_range If the position is less than 1 or greater than 32, an std::out_of_range exception is thrown.
         * @code
         * bfs_32 bfs(0x12345678);
         * bool bit5 = bfs.get(5); // Get value of flag at position 5
         * try {
         *   bool bit = bfs.get(33); // This will throw an exception
         * } catch (const std::out_of_range& e) {
         *   std::cerr << e.what() << std::endl;
         * }
         * @endcode
         */
        bool get(int position) const;

        /**
         * @brief Gets the value of the flag at the specified position using array-like syntax.
         * This operator allows accessing individual flags using array notation.
         * @param position The position of the flag to get (1-32).
         * @return The value of the flag at the specified position.
         * @code
         * bfs_32 bfs(0x12345678);
         * bool bit = bfs[5]; // Get value of flag at position 5
         * @endcode
         */
        bool operator[](int position) const;

        /**
         * @brief Assigns a uint8_t value to the lower 16 bits.
         * This operator sets the lower 16-bit flag container to the specified value.
         * @param other The uint8_t value to assign.
         * @code
         * bfs_32 bfs;
         * bfs = 0x42; // Set lower bits to 0x42
         * @endcode
         */
        void operator=(const uint8_t &other) noexcept;

        /**
         * @brief Assigns a uint16_t value to the bfs_32 object.
         * This operator splits the uint16_t value into upper and lower 16-bit parts.
         * @param other The uint16_t value to assign.
         * @code
         * bfs_32 bfs;
         * bfs = 0x1234; // Assign a 16-bit value
         * @endcode
         */
        void operator=(const uint16_t &other) noexcept;

        /**
         * @brief Assigns a uint32_t value to the bfs_32 object.
         * This operator splits the uint32_t value into upper and lower 16-bit parts.
         * @param other The uint32_t value to assign.
         * @code
         * bfs_32 bfs;
         * bfs = 0x12345678; // Assign a 32-bit value
         * std::cout << std::hex << bfs.get(); // Output: 12345678
         * @endcode
         */
        void operator=(const uint32_t &other) noexcept;

        /**
         * @brief Assigns a bfs_8 value to the lower 16 bits.
         * @param other The bfs_8 object to assign.
         */
        void operator=(const bfs_8 &other) noexcept;

        /**
         * @brief Assigns a bfs_16 value to the lower 16 bits.
         * @param other The bfs_16 object to assign.
         */
        void operator=(const bfs_16 &other) noexcept;

        /**
         * @brief Copy assignment operator for bfs_32.
         * This operator copies the flag container values from another bfs_32 object.
         * @param other The bfs_32 object to copy from.
         */
        void operator=(const bfs_32 &other) noexcept;

        /**
         * @brief Inequality comparison with uint8_t value.
         * @param other The value to compare.
         * @return true if not equal to the lower 16 bits, false otherwise.
         */
        constexpr bool operator!=(const uint8_t &other) const noexcept;

        /**
         * @brief Inequality comparison with uint16_t value.
         * @param other The value to compare.
         * @return true if not equal to the combined 32-bit value, false otherwise.
         */
        constexpr bool operator!=(const uint16_t &other) const noexcept;

        /**
         * @brief Inequality comparison with uint32_t value.
         * @param other The value to compare.
         * @return true if not equal to the combined 32-bit value, false otherwise.
         * @code
         * bfs_32 bfs(0x12345678);
         * bool isNotEqual = (bfs != 0x12345678); // This will return false since bfs is equal to 0x12345678
         * isNotEqual = (bfs != 0x87654321); // This will return true since bfs is not equal to 0x87654321
         * @endcode
         * represents the inequality comparison between a bfs_32 object and a uint32_t value by checking if either the lower or upper parts of the bfs_32 object are not equal to the corresponding parts of the uint32_t value. If either part is different, the operator returns true, indicating that the bfs_32 object is not equal to the uint32_t value; otherwise, it returns false.
         * @note This operator checks both the lower and upper parts of the bfs_32 object against the corresponding parts of the uint32_t value to determine inequality. If you only want to compare specific parts (e.g., just the lower or upper), you can use the corresponding operator!= for bfs_8 or bfs_16.
         * @warning Ensure that the bfs_32 object being compared is properly initialized to avoid comparing uninitialized data, which may lead to unexpected results.
         */
        constexpr bool operator!=(const uint32_t &other) const noexcept;

        /**
         * @brief Inequality comparison with another bfs_8 object.
         * @param other The bfs_8 object to compare with.
         * @return true if the lower parts are not equal, false otherwise.
         * @code
         * bfs_8 bfs1(0x12);
         * bfs_8 bfs2(0x12);
         * bool isNotEqual = (bfs1 != bfs2); // This will return false since bfs1 and bfs2 are equal
         * bfs_8 bfs3(0x34);
         * isNotEqual = (bfs1 != bfs3); // This will return true since bfs1 and bfs3 are not equal
         * @endcode
         * represents the inequality comparison between two bfs_8 objects by checking if the lower parts are not equal. If the lower parts are different, the operator returns true, indicating that the two bfs_8 objects are not equal; otherwise, it returns false.
         * @note This operator only checks the lower part of the bfs_32 object against the bfs_8 object for inequality. If you want to compare both the lower and upper parts, you should use the operator!= that takes a bfs_32 object or a uint32_t value.
         * @warning Ensure that the bfs_8 object being compared is properly initialized to avoid comparing uninitialized data, which may lead to unexpected results.
         */
        constexpr bool operator!=(const bfs_8 &other) const noexcept;

        /**
         * @brief Inequality comparison with another bfs_16 object.
         * @param other The bfs_16 object to compare with.
         * @return true if the lower parts are not equal, false otherwise.
         * @code
         * bfs_16 bfs1(0x1234);
         * bfs_16 bfs2(0x1234);
         * bool isNotEqual = (bfs1 != bfs2); // This will return false since bfs1 and bfs2 are equal
         * bfs_16 bfs3(0x5678);
         * isNotEqual = (bfs1 != bfs3); // This will return true since bfs1 and bfs3 are not equal
         * @endcode
         * represents the inequality comparison between two bfs_16 objects by checking if the lower parts are not equal. If the lower parts are different, the operator returns true, indicating that the two bfs_16 objects are not equal; otherwise, it returns false.
         * @note This operator only checks the lower part of the bfs_32 object against the bfs_16 object for inequality. If you want to compare both the lower and upper parts, you should use the operator!= that takes a bfs_32 object or a uint32_t value.
         * @warning Ensure that the bfs_16 object being compared is properly initialized to avoid comparing uninitialized data, which may lead to unexpected results.
         */
        constexpr bool operator!=(const bfs_16 &other) const noexcept;

        /**
         * @brief Inequality comparison with another bfs_32 object.
         * @param other The bfs_32 object to compare with.
         * @return true if the lower and upper parts are not equal, false otherwise.
         * @code
         * bfs_32 bfs1(0x12345678);
         * bfs_32 bfs2(0x12345678);
         * bool isNotEqual = (bfs1 != bfs2); // This will return false since bfs1 and bfs2 are equal
         * bfs_32 bfs3(0x87654321);
         * isNotEqual = (bfs1 != bfs3); // This will return true since bfs1 and bfs3 are not equal
         * @endcode
         * represents the inequality comparison between two bfs_32 objects by checking if either the lower or upper parts are not equal. If either part is different, the operator returns true, indicating that the two bfs_32 objects are not equal; otherwise, it returns false.
         * @note This operator checks both the lower and upper parts of the bfs_32 objects to determine inequality. If you only want to compare specific parts (e.g., just the lower or upper), you can use the corresponding operator!= for bfs_8 or bfs_16.
         * @warning Ensure that the bfs_32 objects being compared are properly initialized to avoid comparing uninitialized data, which may lead to unexpected results.
         */
        constexpr bool operator!=(const bfs_32 &other) const noexcept;

        /**
         * @brief Equality comparison with a uint8_t value.
         * Compares the lower 16 bits of the bfs_32 object with a uint8_t value.
         * @param other The uint8_t value to compare.
         * @return true if the lower 16 bits of the bfs_32 object are equal to the uint8_t value, false otherwise.
         * @code
         * bfs_32 bfs(0x12345678);
         * uint8_t value = 0x78;
         * bool isEqual = (bfs == value); // This will return true since the lower 16 bits of bfs are equal to the uint8_t variable
         * @endcode
         * represents the same 8-bit value as the lower part of the bfs_32 object
         * @note This comparison only checks the lower 16 bits of the bfs_32 object against the uint8_t value, and does not consider the upper 16 bits. If you need to compare the entire 32-bit value, use the operator== that takes a uint32_t or another bfs_32 object.
         * @warning Ensure that the uint8_t value being compared is within the valid range (0-255) to avoid unexpected behavior, as values outside this range may not be properly compared against the bfs_32 object.
         */
        constexpr bool operator==(const uint8_t &other) const noexcept;

        /**
         * @brief Equality comparison with a uint16_t value.
         * Compares the bfs_32 object with a uint16_t value by splitting the uint16_t into upper and lower 16-bit parts and comparing them with the corresponding parts of the bfs_32 object.
         * @param other The uint16_t value to compare.
         * @return true if the bfs_32 object is equal to the uint16_t value, false otherwise.
         * @code
         * bfs_32 bfs(0x12345678);
         * uint16_t value = 0x5678;
         * bool isEqual = (bfs == value); // This will return true since the lower 16 bits of bfs are equal to the uint16_t variable
         * @endcode
         * represents the same 16-bit value as the lower part of the bfs_32 object
         * @note This comparison checks both the lower and upper 16 bits of the bfs_32 object against the corresponding parts of the uint16_t value to determine equality. The upper 16 bits of the bfs_32 object are compared against the upper 16 bits of the uint16_t value (which will be 0 for any valid uint16_t), while the lower 16 bits are compared directly.
         * @warning Ensure that the uint16_t value being compared is within the valid range (0-65535) to avoid unexpected behavior, as values outside this range may not be properly compared against the bfs_32 object.
         */
        constexpr bool operator==(const uint16_t &other) const noexcept;

        /**
         * @brief Equality comparison with a uint32_t value.
         * Compares the bfs_32 object with a uint32_t value by splitting the uint32_t into upper and lower 16-bit parts and comparing them with the corresponding parts of the bfs_32 object.
         * @param other The uint32_t value to compare.
         * @return true if the bfs_32 object is equal to the uint32_t value, false otherwise.
         * @code
         * bfs_32 bfs(0x12345678);
         * uint32_t value = 0x12345678;
         * bool isEqual = (bfs == value); // This will return true since bfs
         * @endcode
         * represents the same 32-bit value as the uint32_t variable
         * @note This comparison checks both the lower and upper 16 bits of the bfs_32 object against the corresponding parts of the uint32_t value to determine equality.
         * @warning Ensure that the uint32_t value being compared is within the valid range (0-4294967295) to avoid unexpected behavior.
         */
        constexpr bool operator==(const uint32_t &other) const noexcept;

        /**
         * @brief Equality comparison with a bfs_8 object.
         * Compares the lower 16 bits of the bfs_32 object with the bfs_8 object.
         * @param other The bfs_8 object to compare.
         * @return true if the lower 16 bits of the bfs_32 object are equal to the bfs_8 object, false otherwise.
         * @note This comparison only checks the lower 16 bits of the bfs_32 object against the bfs_8 object, and does not consider the upper 16 bits. If you need to compare the entire 32-bit value, use the operator== that takes a uint32_t or another bfs_32 object.
         * @code
         * bfs_32 bfs(0x12345678);
         * bfs_8 lower(0x78);
         * bool isEqual = (bfs == lower); // This will return true since the lower 16 bits of bfs are equal to lower
         * @endcode
         * @warning Ensure that the bfs_8 object being compared contains a valid 8-bit value (0-255) to avoid unexpected behavior.
         */
        constexpr bool operator==(const bfs_8 &other) const noexcept;

        /**
         * @brief Equality comparison with a bfs_16 object.
         * Compares the lower 16 bits of the bfs_32 object with the bfs_16 object.
         * @param other The bfs_16 object to compare.
         * @return true if the lower 16 bits of the bfs_32 object are equal to the bfs_16 object, false otherwise.
         * @note This comparison only checks the lower 16 bits of the bfs_32 object against the bfs_16 object, and does not consider the upper 16 bits. If you need to compare the entire 32-bit value, use the operator== that takes a uint32_t or another bfs_32 object.
         * @code
         * bfs_32 bfs(0x12345678);
         * bfs_16 lower(0x5678);
         * bool isEqual = (bfs == lower); // This will return true since the lower 16 bits of bfs are equal to lower
         * @endcode
         * @warning Ensure that the bfs_16 object being compared contains a valid 16-bit value (0-65535) to avoid unexpected behavior.
         */
        constexpr bool operator==(const bfs_16 &other) const noexcept;

        /**
         * @brief Equality comparison with another bfs_32 object.
         * Compares two bfs_32 flag containers.
         * @param other The bfs_32 object to compare.
         * @return true if both flag containers are equal, false otherwise.
         */
        constexpr bool operator==(const bfs_32 &other) const noexcept;

        /**
         * @brief Destructor for bfs_32.
         * This is a trivial destructor as bfs_32 contains only bfs_16 objects which manage resources automatically.
         * No explicit cleanup is required.
         */
        ~bfs_32() = default;
    };

    // bfs_32 member function definitions
    void bfs_32::set_all() noexcept
    {
        lower.set_all();
        upper.set_all();
    }

    void bfs_32::set() noexcept
    {
        lower.set_all();
        upper.set_all();
    }

    void bfs_32::set(int position)
    {
        if (position < 1 || position > 32)
            throw std::out_of_range("Position out of range");
        if (position >= 1 && position <= 16)
            lower.set(position);
        else
            upper.set(position - 16);
    }

    void bfs_32::reset_all()
    {
        lower.reset_all();
        upper.reset_all();
    }

    constexpr void bfs_32::reset() noexcept
    {
        lower.reset_all();
        upper.reset_all();
    }

    void bfs_32::reset(int position)
    {
        if (position < 1 || position > 32)
            throw std::out_of_range("Position out of range");
        if (position >= 1 && position <= 16)
            lower.reset(position);
        else
            upper.reset(position - 16);
    }

    uint16_t bfs_32::get_lower() const noexcept { return lower.get(); }

    uint16_t bfs_32::get_upper() const noexcept { return upper.get(); }

    uint32_t bfs_32::get() const noexcept { return (static_cast<uint32_t>(upper.get()) << 16) | lower.get(); }

    bool bfs_32::get(int position) const
    {
        if (position < 1 || position > 32)
            throw std::out_of_range("Position out of range");
        if (position >= 1 && position <= 16)
            return lower.get(position);
        else
            return upper.get(position - 16);
    }

    bool bfs_32::operator[](int position) const { return get(position); }

    void bfs_32::operator=(const uint8_t &other) noexcept { lower = other; }

    void bfs_32::operator=(const uint16_t &other) noexcept
    {
        lower = static_cast<uint16_t>(other & 0x0000FFFF);
        upper = static_cast<uint16_t>((other >> 16) & 0x0000FFFF);
    }

    void bfs_32::operator=(const uint32_t &other) noexcept
    {
        lower = static_cast<uint16_t>(other & 0x0000FFFF);
        upper = static_cast<uint16_t>((other >> 16) & 0x0000FFFF);
    }

    void bfs_32::operator=(const bfs_8 &other) noexcept { lower = other; }

    void bfs_32::operator=(const bfs_16 &other) noexcept { lower = other; }

    void bfs_32::operator=(const bfs_32 &other) noexcept
    {
        lower = other.lower;
        upper = other.upper;
    }

    constexpr bool bfs_32::operator!=(const uint8_t &other) const noexcept { return lower != other; }

    constexpr bool bfs_32::operator!=(const uint16_t &other) const noexcept
    {
        return lower != static_cast<uint16_t>(other & 0x0000FFFF) ||
               upper != static_cast<uint16_t>((other >> 16) & 0x0000FFFF);
    }

    constexpr bool bfs_32::operator!=(const uint32_t &other) const noexcept
    {
        return lower != static_cast<uint16_t>(other & 0x0000FFFF) ||
               upper != static_cast<uint16_t>((other >> 16) & 0x0000FFFF);
    }

    constexpr bool bfs_32::operator!=(const bfs_8 &other) const noexcept { return lower != other; }

    constexpr bool bfs_32::operator!=(const bfs_16 &other) const noexcept { return lower != other; }

    constexpr bool bfs_32::operator!=(const bfs_32 &other) const noexcept
    {
        return lower != other.lower &&
               upper != other.upper;
    }

    constexpr bool bfs_32::operator==(const uint8_t &other) const noexcept { return lower == other; }

    constexpr bool bfs_32::operator==(const uint16_t &other) const noexcept
    {
        return lower == static_cast<uint16_t>(other & 0x0000FFFF) &&
               upper == static_cast<uint16_t>((other >> 16) & 0x0000FFFF);
    }

    constexpr bool bfs_32::operator==(const uint32_t &other) const noexcept
    {
        return lower == static_cast<uint16_t>(other & 0x0000FFFF) &&
               upper == static_cast<uint16_t>((other >> 16) & 0x0000FFFF);
    }

    constexpr bool bfs_32::operator==(const bfs_8 &other) const noexcept { return lower == other; }

    constexpr bool bfs_32::operator==(const bfs_16 &other) const noexcept { return lower == other; }

    constexpr bool bfs_32::operator==(const bfs_32 &other) const noexcept
    {
        return lower == other.lower &&
               upper == other.upper;
    }
} // namespace udt

#endif // OPENUDT___UDT_BFS_BFS16_HPP