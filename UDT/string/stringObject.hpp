/**
 * @file stringObject.hpp
 * @brief This header defines the udt::string and udt::string_r classes, which are custom string implementations.
 * The udt::string class manages its own memory using std::unique_ptr, while the udt::string_r class uses raw pointers for memory management.
 * Both classes provide various constructors, assignment operators, and member functions for string manipulation, including setting values, checking properties, and performing operations like capitalization and splitting.
 * The classes also include error handling for fixed-size strings and provide comparison operators for equality and inequality checks.
 * @note The udt::string class is designed
 * to be more modern and safer with automatic memory management, while the udt::string_r class offers a more traditional approach with manual memory management.
 * @warning The udt::string_r class requires careful handling to avoid memory leaks and dangling pointers, while the udt::string class is safer due to its use of smart pointers.
 * @see std::string for a standard string implementation in C++.
 * @author Ali Lafi
 * @date 2025/9/25
 */

#include <memory>
#include <vector>
#include <stdexcept>
#include <string>

#pragma once
#ifndef OPENUDT___UDT_STRING_STRINGOBJECT_HPP
#define OPENUDT___UDT_STRING_STRINGOBJECT_HPP

namespace udt
{
    /// @brief A custom string class that manages its own memory using unique_ptr.
    class string
    {
    private:
        bool fixed;
        std::unique_ptr<char> data; // 8 + 8 + 8 + 1 = 24
        size_t size;

    public:
        /// @brief Default constructor initializes an empty string.
        string() noexcept
        {
            data = std::make_unique<char>(1);
            data.get()[0] = '\0';
            size = 0;
            fixed = false;
        }
        /**
         * @brief Constructor that initializes a string with a fixed size.
         * @param s The fixed size of the string.
         * @note The allocated buffer is (s + 1) to accommodate the null terminator.
         */
        string(int s) noexcept
        {
            size = s;
            data = std::make_unique<char>(size + 1);
            for (size_t i = 0; i < size; i++)
                data.get()[i] = '\0';
            data.get()[size] = '\0';
            fixed = true;
        }
        /**
         * @brief Copy constructor that creates a new string as a copy of another.
         * @param other The string to copy from.
         * @note The allocated buffer is (other.size + 1) to accommodate the null terminator.
         */
        string(const string &other) noexcept
        {
            size = other.size;
            data = std::make_unique<char>(size + 1);
            for (size_t i = 0; i < size; i++)
                data.get()[i] = other.data.get()[i];
            data.get()[size] = '\0';
            fixed = false;
        }
        /**
         * @brief Constructor that initializes a string from a C-style string.
         * @param str The C-style string to initialize from.
         * @note The allocated buffer is (size + 1) to accommodate the null terminator.
         */
        string(const char *str) noexcept
        {
            size = 0;
            while (str[size] != '\0')
                size++;
            data = std::make_unique<char>(size + 1);
            for (size_t i = 0; i < size; i++)
                data.get()[i] = str[i];
            data.get()[size] = '\0';
            fixed = false;
        }
        /// @brief Constructs a string object from a std::string.
        /// @param str The std::string to copy from.
        /// @note Allocates dynamic memory for the string data.
        /// @note The string is not fixed-size after construction.
        string(const std::string &str) noexcept
        {
            size = str.length();
            data = std::make_unique<char>(size + 1);
            for (size_t i = 0; i < size; i++)
                data.get()[i] = str[i];
            data.get()[size] = '\0';
            fixed = false;
        }
        /**
         * @brief Sets the string to a specified size, initializing with null characters.
         * @param s The new size of the string.
         * @throws std::invalid_argument if the string size is fixed.
         * @note The allocated buffer is (s + 1) to accommodate the null terminator.
         */
        void set(int s);

        /**
         * @brief Sets the string to the value of a C-style string.
         * @param str The C-style string to set.
         * @throws std::invalid_argument if the string size is fixed and does not match the input string length.
         * @note The allocated buffer is (size + 1) to accommodate the null terminator.
         */
        void set(const char *str);

        /**
         * @brief Sets the string to the value of another string object.
         * @param other The string object to copy from.
         * @throws std::invalid_argument if either string is fixed and their sizes do not match.
         * @note The allocated buffer is (other.size + 1) to accommodate the null
         */
        void set(const string &other);

        /**
         * @brief Sets the string to the value of a std::string.
         * @param str The std::string to set.
         * @throws std::invalid_argument if the string size is fixed and does not match the input string length.
         * @note The allocated buffer is (size + 1) to accommodate the null terminator.
         */
        void set(const std::string &str);

        /// @brief Checks if the string is empty.
        /// @return true if the string length is zero, false otherwise.
        constexpr void fix() noexcept;

        /// @brief Unfixes the string, allowing its size to be changed.
        constexpr void unfix() noexcept;

        /// @brief Returns the length of the string.
        /// @return The length of the string.
        constexpr size_t length() const noexcept;

        /// @brief Returns a pointer to the internal C-style string.
        /// @return A pointer to the internal C-style string.
        const char *get() const noexcept;

        /// @brief Returns a std::string representation of the internal C-style string.
        /// @return A std::string representation of the internal C-style string.
        std::string gss() const noexcept;

        /// @brief Clears the string, resetting it to an empty state.
        void clear();

        /**
         * @brief Swaps the contents of this string with another string object.
         * @param other The string object to swap with.
         * @throws std::invalid_argument if either string is fixed and their sizes do not match.
         * @note This operation is efficient as it only swaps pointers and sizes.
         */
        void swap(string &other);

        /**
         * @brief Swaps the contents of this string with a std::string.
         * @param other The std::string to swap with.
         * @throws std::invalid_argument if this string is fixed and its size does not match the input string length.
         * @note This operation involves copying data from the std::string to this string.
         */
        void swap(std::string &other);

        /**
         * @brief Capitalizes all lowercase letters in the string.
         * @note This modifies the string in place.
         * @throws No exceptions are thrown.
         * @note Only ASCII lowercase letters ('a' to 'z') are affected.
         */
        void capitalize() noexcept;

        /**
         * @brief Splits the string into a vector of substrings based on a delimiter.
         * @param delimiter The character used to split the string. Default is space (' ').
         * @return A vector of substrings.
         * @note The original string remains unchanged.
         */
        std::vector<string> split(char delimiter = ' ') const noexcept;

        /**
         * @brief Converts all uppercase letters in the string to lowercase.
         * @note This modifies the string in place.
         * @throws No exceptions are thrown.
         * @note Only ASCII uppercase letters ('A' to 'Z') are affected.
         */
        void lower_cast() noexcept;

        /**
         * @brief Converts all lowercase letters in the string to uppercase.
         * @note This modifies the string in place.
         * @throws No exceptions are thrown.
         * @note Only ASCII lowercase letters ('a' to 'z') are affected.
         */
        void upper_cast() noexcept;

        /**
         * @brief Assignment operator to set the string to a specified size.
         * @param s The new size of the string.
         * @note This calls the set(int s) method.
         * @throws No exceptions are thrown.
         */
        void operator=(int s) noexcept;

        /// @brief Assignment operator to set the string to a specified C-style string.
        /// @param str The C-style string to assign.
        void operator=(const char *str) noexcept;

        /// @brief Assignment operator to set the string to a specified std::string.
        /// @param other The std::string to assign.
        void operator=(const string &other) noexcept;

        /// @brief Assignment operator to set the string to a specified std::string.
        /// @param str The std::string to assign.
        void operator=(const std::string &str) noexcept;

        /**
         * @brief Equality operator to compare with another string object.
         * @param other The string object to compare with.
         * @return true if the strings are equal, false otherwise.
         * @note Comparison is done character by character.
         */
        bool operator==(const string &other) noexcept;

        /// @brief Inequality operator to compare with another string object.
        /// @param other The string object to compare with.
        /// @return true if the strings are not equal, false otherwise.
        bool operator!=(const string &other) noexcept;

        /// @brief Equality operator to compare with a C-style string.
        /// @param str The C-style string to compare with.
        /// @return true if the strings are equal, false otherwise.
        bool operator==(const char *str) noexcept;

        /// @brief Inequality operator to compare with a C-style string.
        /// @param str The C-style string to compare with.
        /// @return true if the strings are not equal, false otherwise.
        bool operator!=(const char *str) noexcept;

        /**
         * @brief Equality operator to compare with a std::string.
         * @param str The std::string to compare with.
         * @return true if the strings are equal, false otherwise.
         * @note Comparison is done character by character.
         */
        bool operator==(const std::string &str) noexcept;

        /// @brief Inequality operator to compare with a std::string.
        /// @param str The std::string to compare with.
        /// @return true if the strings are not equal, false otherwise.
        bool operator!=(const std::string &str) noexcept;

        /**
         * @brief Concatenates a C-style string to the current string object.
         *
         * Appends the provided null-terminated C-style string to the end of the current
         * string. The operation allocates new memory to accommodate both strings and updates
         * the internal size accordingly.
         *
         * @param str A pointer to a null-terminated C-style string to append.
         *
         * @throws std::invalid_argument If the object is marked as fixed, preventing modifications.
         *
         * @note This operation requires dynamic memory allocation and copying of existing data.
         *       The current string's content is preserved, and the new string is appended.
         *
         * @complexity Time: O(n + m) where n is the current string size and m is the size of the appended string.
         *             Space: O(n + m) for the new allocated memory.
         */
        void operator+=(const char *str);

        /**
         * @brief Concatenates another string to this string using the += operator.
         *
         * Appends the contents of the provided string to the current string object.
         * If the string is marked as fixed, an exception is thrown to prevent modifications.
         *
         * @param other A const reference to the string object to be concatenated.
         *
         * @throws std::invalid_argument If the string object is fixed (immutable).
         *
         * @note This operation reallocates internal memory to accommodate the combined string.
         * @note The resulting string is null-terminated.
         *
         * @return void
         */
        void operator+=(const string &other);

        /**
         * @brief Concatenates a standard string to the current string object.
         *
         * Appends the contents of the provided std::string to this string object.
         * A new character buffer is allocated to accommodate the combined size, and
         * the original data is copied followed by the new string data.
         *
         * @param str The std::string to append to this string object.
         *
         * @throws std::invalid_argument If this string object is marked as fixed.
         *         Fixed objects cannot be modified after creation.
         *
         * @note This operation allocates new memory and invalidates any direct
         *       pointers to the previous data buffer.
         */
        void operator+=(const std::string &str);

        /// @brief Appends a single character to the string.
        /// @param ch The character to append.
        /// @throws std::invalid_argument if the string object is fixed.
        /// @details Allocates a new buffer with size + 2 bytes, copies existing data,
        ///          appends the new character, and null-terminates the string.
        ///          Updates the size member. The operation is not allowed on fixed strings.
        void operator+=(char ch);

        /// @brief Destructor for the string class.
        /// @note Uses default destructor since unique_ptr handles cleanup automatically.
        ~string() = default;
    };
    class string_r
    {
    private:
        bool fixed;
        char *data;
        size_t size;

    public:
        /// @brief Default constructor initializes an empty string.
        string_r() noexcept
        {
            data = new char[1];
            data[0] = '\0';
            size = 0;
            fixed = false;
        }

        /// @brief Constructor that initializes a fixed-size string.
        /// @param s The fixed size of the string.
        string_r(int s) noexcept
        {
            size = s;
            data = new char[size + 1];
            for (size_t i = 0; i < size; i++)
                data[i] = '\0';
            data[size] = '\0';
            fixed = true;
        }

        /// @brief Copy constructor for string_r objects.
        /// @param other The string_r object to be copied.
        string_r(const string_r &other) noexcept
        {
            size = other.size;
            data = new char[size + 1];
            for (size_t i = 0; i < size; i++)
                data[i] = other.data[i];
            data[size] = '\0';
            fixed = false;
        }

        /// @brief Constructor that initializes a string_r object from a C-style string.
        /// @param str The C-style string to initialize from.
        string_r(const char *str) noexcept
        {
            size = 0;
            while (str[size] != '\0')
                size++;
            data = new char[size + 1];
            for (size_t i = 0; i < size; i++)
                data[i] = str[i];
            data[size] = '\0';
            fixed = false;
        }

        /// @brief Constructor that initializes a string_r object from a standard string.
        /// @param str The std::string to initialize from.
        string_r(const std::string &str) noexcept
        {
            size = str.length();
            data = new char[size + 1];
            for (size_t i = 0; i < size; i++)
                data[i] = str[i];
            data[size] = '\0';
            fixed = false;
        }

        /// @brief Capitalizes all lowercase letters in the string.
        /// @details Converts all lowercase letters to uppercase by adjusting ASCII values.
        /// @note Only affects characters 'a' to 'z'.
        /// @throws No exceptions are thrown.
        void captalize() noexcept;

        /// @brief Converting all lowercase letters in the string to uppercase.
        /// @note This modifies the string in place.
        /// @throws No exceptions are thrown.
        void lower_cast() noexcept;

        /// @brief Converting all uppercase letters in the string to lowercase.
        /// @note This modifies the string in place.
        /// @throws No exceptions are thrown.
        void upper_cast() noexcept;

        /// @brief Checks if the string is empty.
        /// @return True if the string is empty, false otherwise.
        bool empty() const noexcept;

        /**
         * @brief Checks if the character at the specified index is uppercase.
         * @param index The index of the character to check.
         * @return True if the character is uppercase, false otherwise.
         * @note Returns false if the index is out of bounds.
         * @throw No exceptions are thrown.
         */
        bool upper_cast(size_t index) const noexcept;

        /**
         * @brief Checks if the character at the specified index is lowercase.
         * @param index The index of the character to check.
         * @return True if the character is lowercase, false otherwise.
         * @note Returns false if the index is out of bounds.
         * @throw No exceptions are thrown.
         */
        bool lower_cast(size_t index) const noexcept;

        /**
         * @brief Returns the length of the string.
         * @return The length of the string.
         * @note The length does not include the null terminator.
         * @throw No exceptions are thrown.
         */
        size_t length() const noexcept;

        /**
         * @brief Sets the string to a specified size, initializing with null characters.
         * @param s The new size of the string.
         * @throws std::invalid_argument if the string size is fixed.
         * @note The allocated buffer is (s + 1) to accommodate the null terminator.
         */
        void set(int s);

        /**
         * @brief Sets the string to the value of a C-style string.
         * @param str The C-style string to set.
         * @throws std::invalid_argument if the string size is fixed and does not match the input string length.
         * @note The allocated buffer is (size + 1) to accommodate the null termin
         */
        void set(const char *str);

        /**
         * @brief Sets the string to the value of another string_r object.
         * @param other The string_r object to copy from.
         * @throws std::invalid_argument if either string is fixed and their sizes do not match.
         * @note The allocated buffer is (other.size + 1) to accommodate the null terminator.
         */
        void set(const string_r &other);

        /**
         * @brief Sets the string to the value of a std::string.
         * @param str The std::string to set.
         * @throws std::invalid_argument if the string size is fixed and does not match the input string length.
         * @note The allocated buffer is (size + 1) to accommodate the null terminator.
         */
        void set(const std::string &str);

        /**
         * @brief Returns a pointer to the internal C-style string.
         * @return A pointer to the internal C-style string.
         * @note The returned pointer is valid as long as the string_r object exists and is not modified.
         * @throw No exceptions are thrown.
         */
        const char *get() const noexcept;

        /**
         * gss: standes for get stdanderd string.
         * @brief Returns a std::string representation of the internal C-style string.
         * @return A std::string representation of the internal C-style string.
         * @note The returned std::string is a copy of the internal data.
         * @throw No exceptions are thrown.
         */
        std::string gss() const noexcept;

        /**
         * @brief Marks the string as fixed-size, preventing further modifications.
         * @note Once fixed, the size of the string cannot be changed.
         * @throw No exceptions are thrown.
         */
        void fix() noexcept;

        /**
         * @brief Unmarks the string as fixed-size, allowing modifications.
         * @note Once unfixed, the size of the string can be changed.
         * @throw No exceptions are thrown.
         */
        void unfix() noexcept;

        /**
         * @brief Clears the string, resetting it to an empty state.
         * @throws std::invalid_argument if the string is fixed.
         * @note The allocated buffer is reset to size 1 to accommodate the null terminator.
         * @note The size is set to 0 after clearing.
         */
        void clear();

        /**
         * @brief Swaps the contents of this string_r with another string_r object.
         * @param other The string_r object to swap with.
         * @throws std::invalid_argument if either string is fixed and their sizes do not match.
         * @note This operation is efficient as it only swaps pointers and sizes.
         */
        void swap(string_r &other);

        /**
         * @brief Swaps the contents of this string_r with a std::string.
         * @param other The std::string to swap with.
         * @throws std::invalid_argument if this string_r is fixed and its size does not match the input string length.
         * @note This operation involves copying data from the std::string to this string_r.
         */
        void swap(std::string &other);

        /**
         * @brief Assignment operator to set the string_r to a specified size.
         * @param s The new size of the string_r.
         * @note This calls the set(int s) method.
         * @throws No exceptions are thrown.
         */
        void operator=(int s) noexcept;

        /**
         * @brief Assignment operator to set the string_r to a specified C-style string.
         * @param str The C-style string to assign.
         * @throws No exceptions are thrown.
         */
        void operator=(const char *str) noexcept;

        /**
         * @brief Assignment operator to set the string_r to a specified string_r object.
         * @param other The string_r object to assign.
         * @throws No exceptions are thrown.
         */
        void operator=(const string_r &other) noexcept;

        /**
         * @brief Assignment operator to set the string_r to a specified std::string.
         * @param str The std::string to assign.
         * @throws No exceptions are thrown.
         */
        void operator=(const std::string &str) noexcept;

        /**
         * @brief Equality operator to compare with a C-style string.
         * @param str The C-style string to compare with.
         * @return true if the strings are equal, false otherwise.
         * @note Comparison is done character by character.
         * @throw No exceptions are thrown.
         */
        bool operator==(const char *str) const noexcept;

        /**
         * @brief Inequality operator to compare with a C-style string.
         * @param str The C-style string to compare with.
         * @return true if the strings are not equal, false otherwise.
         * @note Comparison is done character by character.
         * @throw No exceptions are thrown.
         */
        bool operator!=(const char *str) const noexcept;

        /**
         * @brief Equality operator to compare with a std::string.
         * @param str The std::string to compare with.
         * @return true if the strings are equal, false otherwise.
         * @note Comparison is done character by character.
         * @throw No exceptions are thrown.
         */
        bool operator==(const std::string &str) const noexcept;

        /**
         * @brief Inequality operator to compare with a std::string.
         * @param str The std::string to compare with.
         * @return true if the strings are not equal, false otherwise.
         * @note Comparison is done character by character.
         * @throw No exceptions are thrown.
         */
        bool operator!=(const std::string &str) const noexcept;

        /**
         * @brief Equality operator to compare with another string_r object.
         * @param other The string_r object to compare with.
         * @return true if the strings are equal, false otherwise.
         * @note Comparison is done character by character.
         * @throw No exceptions are thrown.
         */
        bool operator==(const string_r &other) const noexcept;

        /**
         * @brief Inequality operator to compare with another string_r object.
         * @param other The string_r object to compare with.
         * @return true if the strings are not equal, false otherwise.
         * @note Comparison is done character by character.
         * @throw No exceptions are thrown.
         */
        bool operator!=(const string_r &other) const noexcept;

        /**
         * @brief Concatenates a single character to the string_r.
         * @param ch The character to append.
         * @throws std::invalid_argument if the string_r object is fixed.
         * @details Allocates a new buffer with size + 2 bytes, copies existing data,
         *         appends the new character, and null-terminates the string.
         *        Updates the size member. The operation is not allowed on fixed strings.
         */
        void operator+=(char ch)
        {
            if (fixed)
                throw std::invalid_argument("changes on the fixed objects isn't allowed. ");
            char *newData = new char[size + 2];
            for (size_t i = 0; i < size; i++)
                newData[i] = data[i];
            newData[size] = ch;
            newData[size + 1] = '\0';
            delete[] data;
            data = newData;
            size += 1;
        }

        /**
         * @brief Concatenates a C-style string to the string_r.
         * @param str The C-style string to append.
         * @throws std::invalid_argument if the string_r object is fixed.
         * @details Allocates a new buffer to accommodate the combined size,
         *        copies existing data, appends the new string, and null-terminates the result.
         *      Updates the size member. The operation is not allowed on fixed strings.
         */
        void operator+=(const char *str);

        /**
         * @brief Concatenates another string_r to this string_r using the += operator.
         * @param other The string_r object to be concatenated.
         * @throws std::invalid_argument If the string_r object is fixed (immutable).
         * @note This operation reallocates internal memory to accommodate the combined string.
         *      @note The resulting string is null-terminated.
         */
        void operator+=(const string_r &other);

        /**
         * @brief Concatenates a standard string to the current string_r object.
         * @param str The std::string to append to this string_r object.
         * @throws std::invalid_argument If this string_r object is marked as fixed.
         *       Fixed objects cannot be modified after creation.
         * @note This operation allocates new memory and invalidates any direct
         *      pointers to the previous data buffer.
         */
        void operator+=(const std::string &str);

        ~string_r() noexcept { delete[] data; }
    };

    // string implementations
    void string::set(int s)
    {
        if (fixed)
        {
            throw std::invalid_argument(
                "The size have been fixed: use the method unfix to reset the fixed value");
        }
        size = s;
        data = std::make_unique<char>(size + 1);
        for (size_t i = 0; i < size; i++)
            data.get()[i] = '\0';
        data.get()[size] = '\0';
    }

    void string::set(const char *str)
    {
        if (fixed)
        {
            int length = 0;
            while (str[length] != '\0')
                length++;
            if (length != size)
            {
                throw std::invalid_argument(
                    "The size is of the input is not equal to the fixed size of the object");
            }
        }
        size = 0;
        while (str[size] != '\0')
            size++;
        data = std::make_unique<char>(size + 1);
        for (size_t i = 0; i < size; i++)
            data.get()[i] = str[i];
        data.get()[size] = '\0';
    }

    void string::set(const string &other)
    {
        if (fixed || other.fixed)
        {
            if (size != other.size)
                throw std::invalid_argument(
                    "The object string length is not equal to fixed size of the object");
        }
        size = other.size;
        data = std::make_unique<char>(size + 1);
        for (size_t i = 0; i < size; i++)
            data.get()[i] = other.data.get()[i];
        data.get()[size] = '\0';
    }

    void string::set(const std::string &str)
    {
        if (fixed)
        {
            if (str.length() != length())
                throw std::invalid_argument(
                    "The object string length is not equal to fixed size of the object");
        }
        size = str.length();
        data = std::make_unique<char>(size + 1);
        for (size_t i = 0; i < size; i++)
            data.get()[i] = str[i];
        data.get()[size] = '\0';
    }

    constexpr void string::fix() noexcept { fixed = true; }

    constexpr void string::unfix() noexcept { fixed = false; }

    constexpr size_t string::length() const noexcept { return size; }

    const char *string::get() const noexcept { return data.get(); }

    std::string string::gss() const noexcept { return std::string(data.get()); }

    void string::clear()
    {
        data = std::make_unique<char>(1);
        data.get()[0] = '\0';
        size = 0;
    }

    void string::swap(string &other)
    {
        if (fixed || other.fixed)
        {
            if (other.size != size)
                throw std::invalid_argument(
                    "the length of input string is not equal to the fixed size of the object. ");
        }
        std::unique_ptr<char> tempData = std::move(data);
        size_t tempSize = size;
        data = std::move(other.data);
        size = other.size;
        other.data = std::move(tempData);
        other.size = tempSize;
    }

    void string::swap(std::string &other)
    {
        if (fixed)
        {
            if (other.length() != length())
                throw std::invalid_argument(
                    "the length of input string is not equal to the fixed size of the object. ");
        }
        size_t otherSize = other.length();
        std::unique_ptr<char> newData = std::make_unique<char>(otherSize + 1);
        for (size_t i = 0; i < otherSize; i++)
            newData.get()[i] = other[i];
        newData.get()[otherSize] = '\0';
        data = std::move(newData);
        size = otherSize;
    }

    void string::capitalize() noexcept
    {
        for (size_t i = 0; i < size; i++)
        {
            if (data.get()[i] >= 'a' && data.get()[i] <= 'z')
                data.get()[i] = data.get()[i] - ('a' - 'A');
        }
    }

    std::vector<string> string::split(char delimiter = ' ') const noexcept
    {
        std::vector<string> result;
        size_t start = 0;
        for (size_t i = 0; i < size; i++)
        {
            if (data.get()[i] == delimiter)
            {
                size_t segmentSize = i - start;
                string segment;
                segment.set(segmentSize);
                for (size_t j = 0; j < segmentSize; j++)
                {
                    segment.data.get()[j] = data.get()[start + j];
                }
                result.push_back(segment);
                start = i + 1;
            }
        }
        // Add the last segment
        if (start <= size)
        {
            size_t segmentSize = size - start;
            string segment;
            segment.set(segmentSize);
            for (size_t j = 0; j < segmentSize; j++)
            {
                segment.data.get()[j] = data.get()[start + j];
            }
            result.push_back(segment);
        }
        return result;
    }

    void string::lower_cast() noexcept
    {
        for (size_t i = 0; i < size; i++)
        {
            if (data.get()[i] >= 'A' && data.get()[i] <= 'Z')
                data.get()[i] = data.get()[i] + ('a' - 'A');
        }
    }

    void string::upper_cast() noexcept
    {
        for (size_t i = 0; i < size; i++)
        {
            if (data.get()[i] >= 'a' && data.get()[i] <= 'z')
                data.get()[i] = data.get()[i] - ('a' - 'A');
        }
    }

    void string::operator=(int s) noexcept { set(s); }

    void string::operator=(const char *str) noexcept { set(str); }

    void string::operator=(const string &other) noexcept { set(other); }

    void string::operator=(const std::string &str) noexcept { set(str); }

    bool string::operator==(const string &other) noexcept
    {
        if (size != other.size)
            return false;
        for (size_t i = 0; i < size; i++)
        {
            if (data.get()[i] != other.data.get()[i])
                return false;
        }
        return true;
    }

    bool string::operator!=(const string &other) noexcept
    {
        return !(*this == other);
    }

    bool string::operator==(const char *str) noexcept
    {
        size_t strSize = 0;
        while (str[strSize] != '\0')
            strSize++;
        if (size != strSize)
            return false;
        for (size_t i = 0; i < size; i++)
        {
            if (data.get()[i] != str[i])
                return false;
        }
        return true;
    }

    bool string::operator!=(const char *str) noexcept
    {
        return !(*this == str);
    }

    bool string::operator==(const std::string &str) noexcept
    {
        if (size != str.length())
            return false;
        for (size_t i = 0; i < size; i++)
        {
            if (data.get()[i] != str[i])
                return false;
        }
        return true;
    }

    bool string::operator!=(const std::string &str) noexcept
    {
        return !(*this == str);
    }

    void string::operator+=(const char *str)
    {
        if (fixed)
            throw std::invalid_argument("changes on the fixed objects isn't allowed. ");
        size_t strSize = 0;
        while (str[strSize] != '\0')
            strSize++;
        std::unique_ptr<char> newData = std::make_unique<char>(size + strSize + 1);
        for (size_t i = 0; i < size; i++)
            newData.get()[i] = data.get()[i];
        for (size_t i = 0; i < strSize; i++)
            newData.get()[size + i] = str[i];
        newData.get()[size + strSize] = '\0';
        data = std::move(newData);
        size += strSize;
    }

    void string::operator+=(const string &other)
    {
        if (fixed)
            throw std::invalid_argument("changes on the fixed objects isn't allowed. ");
        std::unique_ptr<char> newData = std::make_unique<char>(size + other.size + 1);
        for (size_t i = 0; i < size; i++)
            newData.get()[i] = data.get()[i];
        for (size_t i = 0; i < other.size; i++)
            newData.get()[size + i] = other.data.get()[i];
        newData.get()[size + other.size] = '\0';
        data = std::move(newData);
        size += other.size;
    }

    void string::operator+=(const std::string &str)
    {
        if (fixed)
            throw std::invalid_argument("changes on the fixed objects isn't allowed. ");
        size_t strSize = str.length();
        std::unique_ptr<char> newData = std::make_unique<char>(size + strSize + 1);
        for (size_t i = 0; i < size; i++)
            newData.get()[i] = data.get()[i];
        for (size_t i = 0; i < strSize; i++)
            newData.get()[size + i] = str[i];
        newData.get()[size + strSize] = '\0';
        data = std::move(newData);
        size += strSize;
    }

    void string::operator+=(char ch)
    {
        if (fixed)
            throw std::invalid_argument("changes on the fixed objects isn't allowed. ");
        std::unique_ptr<char> newData = std::make_unique<char>(size + 2);
        for (size_t i = 0; i < size; i++)
            newData.get()[i] = data.get()[i];
        newData.get()[size] = ch;
        newData.get()[size + 1] = '\0';
        data = std::move(newData);
        size += 1;
    }

    // string_r implementations
    void string_r::captalize() noexcept
    {
        for (size_t i = 0; i < size; i++)
        {
            if (data[i] >= 'a' && data[i] <= 'z')
                data[i] = data[i] - ('a' - 'A');
        }
    }

    void string_r::lower_cast() noexcept
    {
        for (size_t i = 0; i < size; i++)
        {
            if (data[i] >= 'A' && data[i] <= 'Z')
                data[i] = data[i] + ('a' - 'A');
        }
    }

    void string_r::upper_cast() noexcept
    {
        for (size_t i = 0; i < size; i++)
        {
            if (data[i] >= 'a' && data[i] <= 'z')
                data[i] = data[i] - ('a' - 'A');
        }
    }

    bool string_r::empty() const noexcept { return size == 0; }

    bool string_r::upper_cast(size_t index) const noexcept
    {
        if (index < size)
            return data[index] >= 'A' && data[index] <= 'Z';
        return false;
    }

    bool string_r::lower_cast(size_t index) const noexcept
    {
        if (index < size)
            return data[index] >= 'a' && data[index] <= 'z';
        return false;
    }

    size_t string_r::length() const noexcept { return size; }

    void string_r::set(int s)
    {
        if (fixed)
        {
            throw std::invalid_argument(
                "The size have been fixed: use the method unfix to reset the fixed value");
        }
        delete[] data;
        size = s;
        data = new char[size + 1];
        for (size_t i = 0; i < size; i++)
            data[i] = '\0';
        data[size] = '\0';
    }

    void string_r::set(const char *str)
    {
        if (fixed)
        {
            int length = 0;
            while (str[length] != '\0')
                length++;
            if (length != size)
            {
                throw std::invalid_argument(
                    "The size is of the input is not equal to the fixed size of the object");
            }
        }
        delete[] data;
        size = 0;
        while (str[size] != '\0')
            size++;
        data = new char[size + 1];
        for (size_t i = 0; i < size; i++)
            data[i] = str[i];
        data[size] = '\0';
    }

    void string_r::set(const string_r &other)
    {
        if (fixed || other.fixed)
        {
            if (size != other.size)
                throw std::invalid_argument(
                    "The object string length is not equal to fixed size of the object");
        }
        delete[] data;
        size = other.size;
        data = new char[size + 1];
        for (size_t i = 0; i < size; i++)
            data[i] = other.data[i];
        data[size] = '\0';
    }
    void string_r::set(const std::string &str)
    {
        if (fixed)
        {
            if (str.length() != length())
                throw std::invalid_argument(
                    "The object string length is not equal to fixed size of the object");
        }
        delete[] data;
        size = str.length();
        data = new char[size + 1];
        for (size_t i = 0; i < size; i++)
            data[i] = str[i];
        data[size] = '\0';
    }

    const char *string_r::get() const noexcept { return data; }

    // gss: standes for get stdanderd string.
    std::string string_r::gss() const noexcept { return std::string(data); }

    void string_r::fix() noexcept { fixed = true; }

    void string_r::unfix() noexcept { fixed = false; }

    void string_r::clear()
    {
        if (fixed)
            throw std::invalid_argument("can't clear a fixed object.");
        delete[] data;
        data = new char[1];
        data[0] = '\0';
        size = 0;
    }

    void string_r::swap(string_r &other)
    {
        if (fixed || other.fixed)
        {
            if (other.size != size)
                throw std::invalid_argument(
                    "the length of input string is not equal to the fixed size of the object. ");
        }
        char *tempData = data;
        size_t tempSize = size;
        data = other.data;
        size = other.size;
        other.data = tempData;
        other.size = tempSize;
    }

    void string_r::swap(std::string &other)
    {
        if (fixed)
        {
            if (other.length() != length())
                throw std::invalid_argument(
                    "the length of input string is not equal to the fixed size of the object. ");
        }
        size_t otherSize = other.length();
        char *newData = new char[otherSize + 1];
        for (size_t i = 0; i < otherSize; i++)
            newData[i] = other[i];
        newData[otherSize] = '\0';
        delete[] data;
        data = newData;
        size = otherSize;
    }

    void string_r::operator=(int s) noexcept { set(s); }

    void string_r::operator=(const char *str) noexcept { set(str); }

    void string_r::operator=(const string_r &other) noexcept { set(other); }

    void string_r::operator=(const std::string &str) noexcept { set(str); }

    bool string_r::operator==(const char *str) const noexcept
    {
        size_t strSize = 0;
        while (str[strSize] != '\0')
            strSize++;
        if (size != strSize)
            return false;
        for (size_t i = 0; i < size; i++)
        {
            if (data[i] != str[i])
                return false;
        }
        return true;
    }

    bool string_r::operator!=(const char *str) const noexcept { return !(*this == str); }

    bool string_r::operator==(const std::string &str) const noexcept
    {
        if (size != str.length())
            return false;
        for (size_t i = 0; i < size; i++)
        {
            if (data[i] != str[i])
                return false;
        }
        return true;
    }

    bool string_r::operator!=(const std::string &str) const noexcept { return !(*this == str); }

    bool string_r::operator==(const string_r &other) const noexcept
    {
        if (size != other.size)
            return false;
        for (size_t i = 0; i < size; i++)
        {
            if (data[i] != other.data[i])
                return false;
        }
        return true;
    }

    bool string_r::operator!=(const string_r &other) const noexcept { return !(*this == other); }

    void string_r::operator+=(char ch)
    {
        if (fixed)
            throw std::invalid_argument("changes on the fixed objects isn't allowed. ");
        char *newData = new char[size + 2];
        for (size_t i = 0; i < size; i++)
            newData[i] = data[i];
        newData[size] = ch;
        newData[size + 1] = '\0';
        delete[] data;
        data = newData;
        size += 1;
    }

    void string_r::operator+=(const char *str)
    {
        if (fixed)
            throw std::invalid_argument("changes on the fixed objects isn't allowed. ");
        size_t strSize = 0;
        while (str[strSize] != '\0')
            strSize++;
        char *newData = new char[size + strSize + 1];
        for (size_t i = 0; i < size; i++)
            newData[i] = data[i];
        for (size_t i = 0; i < strSize; i++)
            newData[size + i] = str[i];
        newData[size + strSize] = '\0';
        delete[] data;
        data = newData;
        size += strSize;
    }

    void string_r::operator+=(const string_r &other)
    {
        if (fixed)
            throw std::invalid_argument("changes on the fixed objects isn't allowed. ");
        char *newData = new char[size + other.size + 1];
        for (size_t i = 0; i < size; i++)
            newData[i] = data[i];
        for (size_t i = 0; i < other.size; i++)
            newData[size + i] = other.data[i];
        newData[size + other.size] = '\0';
        delete[] data;
        data = newData;
        size += other.size;
    }

    void string_r::operator+=(const std::string &str)
    {
        if (fixed)
            throw std::invalid_argument("changes on the fixed objects isn't allowed. ");
        size_t strSize = str.length();
        char *newData = new char[size + strSize + 1];
        for (size_t i = 0; i < size; i++)
            newData[i] = data[i];
        for (size_t i = 0; i < strSize; i++)
            newData[size + i] = str[i];
        newData[size + strSize] = '\0';
        delete[] data;
        data = newData;
        size += strSize;
    }
}
#endif // OPENUDT___UDT_STRING_STRINGOBJECT_HPP