#include <stdexcept>
#include <string>

#pragma once
#ifndef OPENUDT___BASIC___STRING_STR_R_HPP
#define OPENUDT___BASIC___STRING_STR_R_HPP

namespace udt
{
    class str_r
    {
    private:
        bool fixed;
        char *data;
        size_t size;

    public:
        /// @brief Default constructor initializes an empty str.
        str_r() noexcept
        {
            data = new char[1];
            data[0] = '\0';
            size = 0;
            fixed = false;
        }

        /// @brief Constructor that initializes a fixed-size str.
        /// @param s The fixed size of the str.
        str_r(size_t s) noexcept
        {
            size = s;
            data = new char[size + 1];
            for (size_t i = 0; i < size; i++)
                data[i] = '\0';
            data[size] = '\0';
            fixed = true;
        }

        /// @brief Copy constructor for str_r objects.
        /// @param other The str_r object to be copied.
        str_r(const str_r &other) noexcept
        {
            size = other.size;
            data = new char[size + 1];
            for (size_t i = 0; i < size; i++)
                data[i] = other.data[i];
            data[size] = '\0';
            fixed = false;
        }

        /// @brief Constructor that initializes a str_r object from a C-style str.
        /// @param str The C-style str to initialize from.
        str_r(const char *str) noexcept
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

        /// @brief Constructor that initializes a str_r object from a standard str.
        /// @param str The std::string to initialize from.
        str_r(const std::string &str) noexcept
        {
            size = str.length();
            data = new char[size + 1];
            for (size_t i = 0; i < size; i++)
                data[i] = str[i];
            data[size] = '\0';
            fixed = false;
        }

        /// @brief Capitalizes all lowercase letters in the str.
        /// @details Converts all lowercase letters to uppercase by adjusting ASCII values.
        /// @note Only affects characters 'a' to 'z'.
        /// @throws No exceptions are thrown.
        void captalize() noexcept
        {
            for (size_t i = 0; i < size; i++)
            {
                if (data[i] >= 'a' && data[i] <= 'z')
                    data[i] = data[i] - ('a' - 'A');
            }
        }

        /// @brief Converting all lowercase letters in the str to uppercase.
        /// @note This modifies the str in place.
        /// @throws No exceptions are thrown.
        void lower_cast() noexcept
        {
            for (size_t i = 0; i < size; i++)
            {
                if (data[i] >= 'A' && data[i] <= 'Z')
                    data[i] = data[i] + ('a' - 'A');
            }
        }

        /// @brief Converting all uppercase letters in the str to lowercase.
        /// @note This modifies the str in place.
        /// @throws No exceptions are thrown.
        void upper_cast() noexcept
        {
            for (size_t i = 0; i < size; i++)
            {
                if (data[i] >= 'a' && data[i] <= 'z')
                    data[i] = data[i] - ('a' - 'A');
            }
        }

        /// @brief Checks if the str is empty.
        /// @return True if the str is empty, false otherwise.
        bool empty() const noexcept { return size == 0; }

        /**
         * @brief Checks if the character at the specified index is uppercase.
         * @param index The index of the character to check.
         * @return True if the character is uppercase, false otherwise.
         * @note Returns false if the index is out of bounds.
         * @throw No exceptions are thrown.
         */
        bool upper_cast(size_t index) const noexcept
        {
            if (index < size)
                return data[index] >= 'A' && data[index] <= 'Z';
            return false;
        }

        /**
         * @brief Checks if the character at the specified index is lowercase.
         * @param index The index of the character to check.
         * @return True if the character is lowercase, false otherwise.
         * @note Returns false if the index is out of bounds.
         * @throw No exceptions are thrown.
         */
        bool lower_cast(size_t index) const noexcept
        {
            if (index < size)
                return data[index] >= 'a' && data[index] <= 'z';
            return false;
        }

        /**
         * @brief Returns the length of the str.
         * @return The length of the str.
         * @note The length does not include the null terminator.
         * @throw No exceptions are thrown.
         */
        size_t length() const noexcept { return size; }

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
            delete[] data;
            size = s;
            data = new char[size + 1];
            for (size_t i = 0; i < size; i++)
                data[i] = '\0';
            data[size] = '\0';
        }

        /**
         * @brief Sets the str to the value of a C-style str.
         * @param str The C-style str to set.
         * @throws std::invalid_argument if the str size is fixed and does not match the input str length.
         * @note The allocated buffer is (size + 1) to accommodate the null termin
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
            delete[] data;
            size = 0;
            while (str[size] != '\0')
                size++;
            data = new char[size + 1];
            for (size_t i = 0; i < size; i++)
                data[i] = str[i];
            data[size] = '\0';
        }

        /**
         * @brief Sets the str to the value of another str_r object.
         * @param other The str_r object to copy from.
         * @throws std::invalid_argument if either str is fixed and their sizes do not match.
         * @note The allocated buffer is (other.size + 1) to accommodate the null terminator.
         */
        void set(const str_r &other)
        {
            if (fixed || other.fixed)
            {
                if (size != other.size)
                    throw std::invalid_argument(
                        "The object str length is not equal to fixed size of the object");
            }
            delete[] data;
            size = other.size;
            data = new char[size + 1];
            for (size_t i = 0; i < size; i++)
                data[i] = other.data[i];
            data[size] = '\0';
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
            delete[] data;
            size = str.length();
            data = new char[size + 1];
            for (size_t i = 0; i < size; i++)
                data[i] = str[i];
            data[size] = '\0';
        }

        /**
         * @brief Returns a pointer to the internal C-style str.
         * @return A pointer to the internal C-style str.
         * @note The returned pointer is valid as long as the str_r object exists and is not modified.
         * @throw No exceptions are thrown.
         */
        const char *get() const noexcept { return data; }

        /**
         * gss: standes for get stdanderd str.
         * @brief Returns a std::string representation of the internal C-style str.
         * @return A std::string representation of the internal C-style str.
         * @note The returned std::string is a copy of the internal data.
         * @throw No exceptions are thrown.
         */
        std::string gss() const noexcept { return std::string(data); }

        /**
         * @brief Marks the str as fixed-size, preventing further modifications.
         * @note Once fixed, the size of the str cannot be changed.
         * @throw No exceptions are thrown.
         */
        void fix() noexcept { fixed = true; }

        /**
         * @brief Unmarks the str as fixed-size, allowing modifications.
         * @note Once unfixed, the size of the str can be changed.
         * @throw No exceptions are thrown.
         */
        void unfix() noexcept { fixed = false; }

        /**
         * @brief Clears the str, resetting it to an empty state.
         * @throws std::invalid_argument if the str is fixed.
         * @note The allocated buffer is reset to size 1 to accommodate the null terminator.
         * @note The size is set to 0 after clearing.
         */
        void clear()
        {
            if (fixed)
                throw std::invalid_argument("can't clear a fixed object.");
            delete[] data;
            data = new char[1];
            data[0] = '\0';
            size = 0;
        }

        /**
         * @brief Swaps the contents of this str_r with another str_r object.
         * @param other The str_r object to swap with.
         * @throws std::invalid_argument if either str is fixed and their sizes do not match.
         * @note This operation is efficient as it only swaps pointers and sizes.
         */
        void swap(str_r &other)
        {
            if (fixed || other.fixed)
            {
                if (other.size != size)
                    throw std::invalid_argument(
                        "the length of input str is not equal to the fixed size of the object. ");
            }
            char *tempData = data;
            size_t tempSize = size;
            data = other.data;
            size = other.size;
            other.data = tempData;
            other.size = tempSize;
        }

        /**
         * @brief Swaps the contents of this str_r with a std::string.
         * @param other The std::string to swap with.
         * @throws std::invalid_argument if this str_r is fixed and its size does not match the input str length.
         * @note This operation involves copying data from the std::string to this str_r.
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
            char *newData = new char[otherSize + 1];
            for (size_t i = 0; i < otherSize; i++)
                newData[i] = other[i];
            newData[otherSize] = '\0';
            delete[] data;
            data = newData;
            size = otherSize;
        }

        /**
         * @brief Assignment operator to set the str_r to a specified size.
         * @param s The new size of the str_r.
         * @note This calls the set(int s) method.
         * @throws No exceptions are thrown.
         */
        void operator=(size_t s) { set(s); }

        /**
         * @brief Assignment operator to set the str_r to a specified C-style str.
         * @param str The C-style str to assign.
         * @throws No exceptions are thrown.
         */
        void operator=(const char *str) { set(str); }

        /**
         * @brief Assignment operator to set the str_r to a specified str_r object.
         * @param other The str_r object to assign.
         * @throws No exceptions are thrown.
         */
        void operator=(const str_r &other) { set(other); }

        /**
         * @brief Assignment operator to set the str_r to a specified std::string.
         * @param str The std::string to assign.
         * @throws No exceptions are thrown.
         */
        void operator=(const std::string &str) { set(str); }

        /**
         * @brief Equality operator to compare with a C-style str.
         * @param str The C-style str to compare with.
         * @return true if the strs are equal, false otherwise.
         * @note Comparison is done character by character.
         * @throw No exceptions are thrown.
         */
        bool operator==(const char *str) const noexcept
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

        /**
         * @brief Inequality operator to compare with a C-style str.
         * @param str The C-style str to compare with.
         * @return true if the strs are not equal, false otherwise.
         * @note Comparison is done character by character.
         * @throw No exceptions are thrown.
         */
        bool operator!=(const char *str) const noexcept { return !(*this == str); }

        /**
         * @brief Equality operator to compare with a std::string.
         * @param str The std::string to compare with.
         * @return true if the strs are equal, false otherwise.
         * @note Comparison is done character by character.
         * @throw No exceptions are thrown.
         */
        bool operator==(const std::string &str) const noexcept
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

        /**
         * @brief Inequality operator to compare with a std::string.
         * @param str The std::string to compare with.
         * @return true if the strs are not equal, false otherwise.
         * @note Comparison is done character by character.
         * @throw No exceptions are thrown.
         */
        bool operator!=(const std::string &str) const noexcept { return !(*this == str); }

        /**
         * @brief Equality operator to compare with another str_r object.
         * @param other The str_r object to compare with.
         * @return true if the strs are equal, false otherwise.
         * @note Comparison is done character by character.
         * @throw No exceptions are thrown.
         */
        bool operator==(const str_r &other) const noexcept
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

        /**
         * @brief Inequality operator to compare with another str_r object.
         * @param other The str_r object to compare with.
         * @return true if the strs are not equal, false otherwise.
         * @note Comparison is done character by character.
         * @throw No exceptions are thrown.
         */
        bool operator!=(const str_r &other) const noexcept { return !(*this == other); }

        /**
         * @brief Concatenates a single character to the str_r.
         * @param ch The character to append.
         * @throws std::invalid_argument if the str_r object is fixed.
         * @details Allocates a new buffer with size + 2 bytes, copies existing data,
         *         appends the new character, and null-terminates the str.
         *        Updates the size member. The operation is not allowed on fixed strs.
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
         * @brief Concatenates a C-style str to the str_r.
         * @param str The C-style str to append.
         * @throws std::invalid_argument if the str_r object is fixed.
         * @details Allocates a new buffer to accommodate the combined size,
         *        copies existing data, appends the new str, and null-terminates the result.
         *      Updates the size member. The operation is not allowed on fixed strs.
         */
        void operator+=(const char *str)
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

        /**
         * @brief Concatenates another str_r to this str_r using the += operator.
         * @param other The str_r object to be concatenated.
         * @throws std::invalid_argument If the str_r object is fixed (immutable).
         * @note This operation reallocates internal memory to accommodate the combined str.
         *      @note The resulting str is null-terminated.
         */
        void operator+=(const str_r &other)
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

        /**
         * @brief Concatenates a standard str to the current str_r object.
         * @param str The std::string to append to this str_r object.
         * @throws std::invalid_argument If this str_r object is marked as fixed.
         *       Fixed objects cannot be modified after creation.
         * @note This operation allocates new memory and invalidates any direct
         *      pointers to the previous data buffer.
         */
        void operator+=(const std::string &str)
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

        ~str_r() noexcept { delete[] data; }
    };
}
#endif // OPENUDT___BASIC___STRING_STR_R_HPP