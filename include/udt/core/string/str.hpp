#include <memory>
#include <vector>
#include <stdexcept>
#include <string>

#pragma once
#ifndef OPENUDT___BASIC___STRING_STR_HPP
#define OPENUDT___BASIC___STRING_STR_HPP

namespace udt
{
    /// @brief A custom str class that manages its own memory using unique_ptr.
    class str
    {
    private:
        bool fixed;
        std::unique_ptr<char> data; // 8 + 8 + 8 + 1 = 24
        size_t size;

    public:
        /// @brief Default constructor initializes an empty str.
        str() noexcept
        {
            data = std::make_unique<char>(1);
            data.get()[0] = '\0';
            size = 0;
            fixed = false;
        }

        /**
         * @brief Constructor that initializes a str with a fixed size.
         * @param s The fixed size of the str.
         * @note The allocated buffer is (s + 1) to accommodate the null terminator.
         */
        str(size_t s) noexcept
        {
            size = s;
            data = std::make_unique<char>(size + 1);
            for (size_t i = 0; i < size; i++)
                data.get()[i] = '\0';
            data.get()[size] = '\0';
            fixed = true;
        }

        /**
         * @brief Copy constructor that creates a new str as a copy of another.
         * @param other The str to copy from.
         * @note The allocated buffer is (other.size + 1) to accommodate the null terminator.
         */
        str(const str &other) noexcept
        {
            size = other.size;
            data = std::make_unique<char>(size + 1);
            for (size_t i = 0; i < size; i++)
                data.get()[i] = other.data.get()[i];
            data.get()[size] = '\0';
            fixed = false;
        }

        /**
         * @brief Constructor that initializes a str from a C-style str.
         * @param str The C-style str to initialize from.
         * @note The allocated buffer is (size + 1) to accommodate the null terminator.
         */
        str(const char *str) noexcept
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

        /// @brief Constructs a str object from a std::string.
        /// @param str The std::string to copy from.
        /// @note Allocates dynamic memory for the str data.
        /// @note The str is not fixed-size after construction.
        str(const std::string &str) noexcept
        {
            size = str.length();
            data = std::make_unique<char>(size + 1);
            for (size_t i = 0; i < size; i++)
                data.get()[i] = str[i];
            data.get()[size] = '\0';
            fixed = false;
        }

        /**
         * @brief Sets the str to a specified size, initializing with null characters.
         * @param s The new size of the str.
         * @throws std::invalid_argument if the str size is fixed.
         * @note The allocated buffer is (s + 1) to accommodate the null terminator.
         */
        void set(size_t s)
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

        /**
         * @brief Sets the str to the value of a C-style str.
         * @param str The C-style str to set.
         * @throws std::invalid_argument if the str size is fixed and does not match the input str length.
         * @note The allocated buffer is (size + 1) to accommodate the null terminator.
         */
        void set(const char *str)
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

        /**
         * @brief Sets the str to the value of another str object.
         * @param other The str object to copy from.
         * @throws std::invalid_argument if either str is fixed and their sizes do not match.
         * @note The allocated buffer is (other.size + 1) to accommodate the null
         */
        void set(const str &other)
        {
            if (fixed || other.fixed)
            {
                if (size != other.size)
                    throw std::invalid_argument(
                        "The object str length is not equal to fixed size of the object");
            }
            size = other.size;
            data = std::make_unique<char>(size + 1);
            for (size_t i = 0; i < size; i++)
                data.get()[i] = other.data.get()[i];
            data.get()[size] = '\0';
        }

        /**
         * @brief Sets the str to the value of a std::string.
         * @param str The std::string to set.
         * @throws std::invalid_argument if the str size is fixed and does not match the input str length.
         * @note The allocated buffer is (size + 1) to accommodate the null terminator.
         */
        void set(const std::string &str)
        {
            if (fixed)
            {
                if (str.length() != length())
                    throw std::invalid_argument(
                        "The object str length is not equal to fixed size of the object");
            }
            size = str.length();
            data = std::make_unique<char>(size + 1);
            for (size_t i = 0; i < size; i++)
                data.get()[i] = str[i];
            data.get()[size] = '\0';
        }

        /// @brief Checks if the str is empty.
        /// @return true if the str length is zero, false otherwise.
        constexpr void fix() noexcept { fixed = true; }

        /// @brief Unfixes the str, allowing its size to be changed.
        constexpr void unfix() noexcept { fixed = false; }

        /// @brief Returns the length of the str.
        /// @return The length of the str.
        constexpr size_t length() const noexcept { return size; }

        /// @brief Returns a pointer to the internal C-style str.
        /// @return A pointer to the internal C-style str.
        const char *get() const noexcept { return data.get(); }

        /// @brief Returns a std::string representation of the internal C-style str.
        /// @return A std::string representation of the internal C-style str.
        std::string gss() const noexcept { return std::string(data.get()); }

        /// @brief Clears the str, resetting it to an empty state.
        void clear()
        {
            data = std::make_unique<char>(1);
            data.get()[0] = '\0';
            size = 0;
        }

        /**
         * @brief Swaps the contents of this str with another str object.
         * @param other The str object to swap with.
         * @throws std::invalid_argument if either str is fixed and their sizes do not match.
         * @note This operation is efficient as it only swaps pointers and sizes.
         */
        void swap(str &other)
        {
            if (fixed || other.fixed)
            {
                if (other.size != size)
                    throw std::invalid_argument(
                        "the length of input str is not equal to the fixed size of the object. ");
            }
            std::unique_ptr<char> tempData = std::move(data);
            size_t tempSize = size;
            data = std::move(other.data);
            size = other.size;
            other.data = std::move(tempData);
            other.size = tempSize;
        }

        /**
         * @brief Swaps the contents of this str with a std::string.
         * @param other The std::string to swap with.
         * @throws std::invalid_argument if this str is fixed and its size does not match the input str length.
         * @note This operation involves copying data from the std::string to this str.
         */
        void swap(std::string &other)
        {
            if (fixed)
            {
                if (other.length() != length())
                    throw std::invalid_argument(
                        "the length of input str is not equal to the fixed size of the object. ");
            }
            size_t otherSize = other.length();
            std::unique_ptr<char> newData = std::make_unique<char>(otherSize + 1);
            for (size_t i = 0; i < otherSize; i++)
                newData.get()[i] = other[i];
            newData.get()[otherSize] = '\0';
            data = std::move(newData);
            size = otherSize;
        }

        /**
         * @brief Capitalizes all lowercase letters in the str.
         * @note This modifies the str in place.
         * @throws No exceptions are thrown.
         * @note Only ASCII lowercase letters ('a' to 'z') are affected.
         */
        void capitalize() noexcept
        {
            for (size_t i = 0; i < size; i++)
            {
                if (data.get()[i] >= 'a' && data.get()[i] <= 'z')
                    data.get()[i] = data.get()[i] - ('a' - 'A');
            }
        }

        /**
         * @brief Splits the str into a vector of substrs based on a delimiter.
         * @param delimiter The character used to split the str. Default is space (' ').
         * @return A vector of substrs.
         * @note The original str remains unchanged.
         */
        std::vector<str> split(char delimiter = ' ') const noexcept
        {
            std::vector<str> result;
            size_t start = 0;
            for (size_t i = 0; i < size; i++)
            {
                if (data.get()[i] == delimiter)
                {
                    size_t segmentSize = i - start;
                    str segment;
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
                str segment;
                segment.set(segmentSize);
                for (size_t j = 0; j < segmentSize; j++)
                {
                    segment.data.get()[j] = data.get()[start + j];
                }
                result.push_back(segment);
            }
            return result;
        }

        /**
         * @brief Converts all uppercase letters in the str to lowercase.
         * @note This modifies the str in place.
         * @throws No exceptions are thrown.
         * @note Only ASCII uppercase letters ('A' to 'Z') are affected.
         */
        void lower_cast() noexcept
        {
            for (size_t i = 0; i < size; i++)
            {
                if (data.get()[i] >= 'A' && data.get()[i] <= 'Z')
                    data.get()[i] = data.get()[i] + ('a' - 'A');
            }
        }

        /**
         * @brief Converts all lowercase letters in the str to uppercase.
         * @note This modifies the str in place.
         * @throws No exceptions are thrown.
         * @note Only ASCII lowercase letters ('a' to 'z') are affected.
         */
        void upper_cast() noexcept
        {
            for (size_t i = 0; i < size; i++)
            {
                if (data.get()[i] >= 'a' && data.get()[i] <= 'z')
                    data.get()[i] = data.get()[i] - ('a' - 'A');
            }
        }

        /**
         * @brief Assignment operator to set the str to a specified size.
         * @param s The new size of the str.
         * @note This calls the set(int s) method.
         * @throws No exceptions are thrown.
         */
        void operator=(size_t s) { set(s); }

        /// @brief Assignment operator to set the str to a specified C-style str.
        /// @param str The C-style str to assign.
        void operator=(const char *str) { set(str); }

        /// @brief Assignment operator to set the str to a specified std::string.
        /// @param other The std::string to assign.
        void operator=(const str &other) { set(other); }

        /// @brief Assignment operator to set the str to a specified std::string.
        /// @param str The std::string to assign.
        void operator=(const std::string &str) { set(str); }

        /**
         * @brief Equality operator to compare with another str object.
         * @param other The str object to compare with.
         * @return true if the strs are equal, false otherwise.
         * @note Comparison is done character by character.
         */
        bool operator==(const str &other) noexcept
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

        /// @brief Inequality operator to compare with another str object.
        /// @param other The str object to compare with.
        /// @return true if the strs are not equal, false otherwise.
        bool operator!=(const str &other) noexcept { return !(*this == other); }

        /// @brief Equality operator to compare with a C-style str.
        /// @param str The C-style str to compare with.
        /// @return true if the strs are equal, false otherwise.
        bool operator==(const char *str) noexcept
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

        /// @brief Inequality operator to compare with a C-style str.
        /// @param str The C-style str to compare with.
        /// @return true if the strs are not equal, false otherwise.
        bool operator!=(const char *str) noexcept { return !(*this == str); }

        /**
         * @brief Equality operator to compare with a std::string.
         * @param str The std::string to compare with.
         * @return true if the strs are equal, false otherwise.
         * @note Comparison is done character by character.
         */
        bool operator==(const std::string &str) noexcept
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

        /// @brief Inequality operator to compare with a std::string.
        /// @param str The std::string to compare with.
        /// @return true if the strs are not equal, false otherwise.
        bool operator!=(const std::string &str) noexcept { return !(*this == str); }

        /**
         * @brief Concatenates a C-style str to the current str object.
         *
         * Appends the provided null-terminated C-style str to the end of the current
         * str. The operation allocates new memory to accommodate both strs and updates
         * the internal size accordingly.
         *
         * @param str A pointer to a null-terminated C-style str to append.
         *
         * @throws std::invalid_argument If the object is marked as fixed, preventing modifications.
         *
         * @note This operation requires dynamic memory allocation and copying of existing data.
         *       The current str's content is preserved, and the new str is appended.
         *
         * @complexity Time: O(n + m) where n is the current str size and m is the size of the appended str.
         *             Space: O(n + m) for the new allocated memory.
         */
        void operator+=(const char *str)
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

        /**
         * @brief Concatenates another str to this str using the += operator.
         *
         * Appends the contents of the provided str to the current str object.
         * If the str is marked as fixed, an exception is thrown to prevent modifications.
         *
         * @param other A const reference to the str object to be concatenated.
         *
         * @throws std::invalid_argument If the str object is fixed (immutable).
         *
         * @note This operation reallocates internal memory to accommodate the combined str.
         * @note The resulting str is null-terminated.
         *
         * @return void
         */
        void operator+=(const str &other)
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

        /**
         * @brief Concatenates a standard str to the current str object.
         *
         * Appends the contents of the provided std::string to this str object.
         * A new character buffer is allocated to accommodate the combined size, and
         * the original data is copied followed by the new str data.
         *
         * @param str The std::string to append to this str object.
         *
         * @throws std::invalid_argument If this str object is marked as fixed.
         *         Fixed objects cannot be modified after creation.
         *
         * @note This operation allocates new memory and invalidates any direct
         *       pointers to the previous data buffer.
         */
        void operator+=(const std::string &str)
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

        /// @brief Appends a single character to the str.
        /// @param ch The character to append.
        /// @throws std::invalid_argument if the str object is fixed.
        /// @details Allocates a new buffer with size + 2 bytes, copies existing data,
        ///          appends the new character, and null-terminates the str.
        ///          Updates the size member. The operation is not allowed on fixed strs.
        void operator+=(char ch)
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

        /// @brief Destructor for the str class.
        /// @note Uses default destructor since unique_ptr handles cleanup automatically.
        ~str() = default;
    };
}

#endif // OPENUDT___BASIC___STRING_STR_HPP