#include <functional>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <string>
#include "metaCore/adva/function.hpp"

#pragma once
#ifndef OPENUDT___CORE_VECTOR_MULTIDIMENSIONAL_VECTOR_HPP
#define OPENUDT___CORE_VECTOR_MULTIDIMENSIONAL_VECTOR_HPP

namespace udt
{

    /**
     * A simple wrapper over std::vector to provide list-like operations,
     * such as push_front, pop_front, insert before/after, and reverse view.
     *
     * @tparam T The type of elements stored in the list.
     */
    template <typename T>
    class vector
    {
    private:
        size_t max_size = 0; // Default size to -1 to indicate uninitialized
        bool fixed_size = false;
        std::vector<T> list;

    public:
        /**
         * Default constructor for list
         */
        vector() { list = {}; }

        /**
         * Constructor that initializes the list with an initializer list
         * @param init Initializer list to initialize the list
         */
        vector(std::initializer_list<T> init) : list(init)
        {
            if (fixed_size)
            {
                size_t num = init.size();
                max_size = list.size();
                if (max_size != -1)
                {
                    if (max_size != num)
                    {
                        throw std::runtime_error(
                            "Dimension Error: Initializer list dimensions do not match fixed "
                            "size");
                    }
                }
            }
        }

        /**
         * Constructor that initializes the list with a specified size and an
         * initializer list
         * @param num Size of the list
         * @param init Initializer list to initialize the list
         * @throws runtime_error if num is negative
         */
        vector(int num, std::initializer_list<T> init) : list(init)
        {
            if (num < 0)
                throw std::runtime_error("size can not be negative");
            max_size = static_cast<size_t>(num);
            fixed_size = true;
        }

        /**
         * @brief Constructs the object from a 2D vector.
         *
         * Initializes the internal list with the provided 2D vector.
         * Optionally checks against a fixed size if one is defined.
         *
         * @param vec2d Input 2D vector used to initialize the object.
         * @param i Optional parameter (currently unused, defaults to 0).
         * @throws std::length_error if vec2d.size() exceeds max_size when max_size != -1.
         */
        vector(const std::vector<std::vector<T>> &vec2d, unsigned int i = 0)
        {
            if (vec2d.size() > max_size && max_size != -1)
                throw std::length_error("unmatched to the fixed size of the vector");
            list = vec2d;
        }

        /**
         * Constructor that initializes the list with a specified size
         * @param s Size of the list
         * @throws runtime_error if s is negative
         */
        vector(size_t s)
        {
            if (static_cast<int>(s) < 0)
                throw std::invalid_argument("size can not be negative");
            max_size = s;
            fixed_size = true;
        }

        /**
         * Constructor that initializes the list with a specified size
         * @param s Size of the list
         * @throws runtime_error if s is negative
         * @note This constructor is provided for compatibility with the original code, but it is recommended to use the size_t version for better type safety.
         * @deprecated Use vector(size_t s) instead for better type safety.
         * @warning This constructor is deprecated and may be removed in future versions. Use vector(size_t s) instead.
         * @note The use of int for size is not recommended due to potential issues with negative values and type safety. Consider using size_t for size parameters to avoid these issues.
         * @see vector(size_t s) for a safer alternative to this constructor.
         * @note The use of int for size parameters can lead to unexpected behavior if negative values are passed. Always ensure that the size parameter is non-negative when using this constructor.
         * @note The fixed_size flag is set to true when using this constructor, indicating that the size of the vector is fixed and cannot be changed after construction. This may affect the behavior of other member functions that modify the size of the vector.
         * @note If a negative value is passed to this constructor, a std::invalid_argument exception is thrown, indicating that the size cannot be negative. This ensures that the vector is always initialized with a valid size.
         * @note The max_size member variable is set to the value of s, which represents the size of the vector. This value is used in other member functions to enforce the fixed size of the vector and to perform bounds checking when accessing elements.
         * @note The use of int for size parameters is not recommended in modern C++ code due to potential issues with negative values and type safety. It is generally better to use size_t for size parameters to ensure that they are non-negative and to avoid potential overflow issues. Consider updating the code to use size_t for size parameters for improved safety and clarity.
         */
        vector(int s)
        {
            if (s < 0)
                throw std::invalid_argument("size can not be negative");
            max_size = static_cast<size_t>(s);
            fixed_size = true;
        }

        /**
         * Copy constructor for vector
         * @param other Another vector to copy from
         */
        vector(const vector<T> &other) { list = other.list; }

        /**
         * Constructor that initializes the list with a vector
         * @param NewList Vector to initialize the list
         */
        vector(const std::vector<T> &NewList) { list = NewList; }

        /**
         * Constructor that initializes the list with a vector and a specified size
         * @param NewList Vector to initialize the list
         * @param s Size of the list
         * @throws runtime_error if s is negative
         */
        void set(const std::vector<T> &NewList) noexcept { ist = NewList; }

        /**
         * Sets the list with a vector and a specified size
         * @param NewList Vector to initialize the list
         * @param s Size of the list
         * @throws runtime_error if s is negative
         */
        void set_size(size_t s)
        {
            if (static_cast<int>(s) < 0)
                throw std::runtime_error("size can not be negative");
            if (max_size != -1 && list.size() > s)
                throw std::runtime_error("New size is smaller than current list size");
            max_size = s;
            fixed_size = true;
        }

        /**
         * Resizes the list to a specified size
         * @param s New size of the list
         * @throws runtime_error if s is negative
         * @note If the new size is smaller than the current size, the list is truncated.
         */
        void resize(size_t s)
        {
            if (static_cast<int>(s) < 0)
                throw std::runtime_error("size can not be negative");
            if (max_size != -1 && list.size() > s)
            {
                std::vector<T> temp = list;
                list.clear();
                for (size_t i = 0; i < s; i++)
                    list.push_back(temp[i]);
                max_size = static_cast<int>(s);
                return;
            }
            max_size = static_cast<int>(s);
            list.resize(s);
            fixed_size = true;
        }

        /**
         * Gets the current size of the vector
         * @return The size of the vector
         */
        const std::vector<T> &get() const noexcept { return list; }

        /**
         * Gets a copy of the current vector
         * @return A copy of the vector
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        std::vector<T> get_copy() const noexcept { return list; }

        /**
         * Gets the size of the vector
         * @return The size of the vector
         */
        T at(int index) const noexcept
        {
            if (index < 0)
            {
                std::cerr << "Index is negative, returning first element." << std::endl;
                return list[0];
            }
            if (index >= static_cast<int>(list.size()))
            {
                std::cerr << "Index is out of range, returning last element." << std::endl;
                return list[list.size() - 1];
            }
            return list[index];
        }

        /**
         * Clears the list
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        void clear() noexcept { list.clear(); }

        /**
         * @brief Calculates the sum of all elements in the list, optionally starting from a given initial value.
         *
         * This function iterates over all elements in the list and accumulates their values,
         * starting from the provided initial value `num`. The operation is only supported for numeric types.
         * If the list is empty, a std::runtime_error is thrown.
         *
         * @param num Optional initial value to start the summation (default is 0.0).
         * @return The total sum as a long double.
         * @throws std::runtime_error If the list is empty.
         */
        long double sum(double num = 0.0) const
        {
            static_assert(is_numeric_type<T>::value,
                          "This operation is not supported for non-numeric types");
            if (list.empty())
                throw std::runtime_error("empty list can not do this operation");
            long double result = num;
            for (const double &LNum : list)
                result += LNum;
            return result;
        }

        /**
         * Returns a reversed copy of the list as a vector
         * @return A vector containing the elements of the list in reverse order
         * @throws runtime_error if the list is empty
         */
        std::vector<T> reverse() const
        {
            if (list.empty())
                throw std::runtime_error("empty list can not do this operation");
            std::vector<T> reversed;
            for (auto it = list.rbegin(); it != list.rend(); ++it)
                reversed.push_back(*it);
            return reversed;
        }

        /**
         * Returns a reversed copy of a portion of the list as a vector
         * @param begin The starting index of the portion to reverse
         * @return A vector containing the elements of the specified portion of the list in reverse order
         * @throws runtime_error if the list is empty or if the begin index is out of range
         */
        std::vector<T> reverse(int begin) const
        {
            if (list.empty())
                throw std::runtime_error("empty list can not do this operation");
            if (begin < 0 || begin >= list.size())
                throw std::runtime_error("begin index out of range");
            if (begin == list.size() - 1)
                return {};
            if (begin == 0)
                return reverse();
            std::vector<T> reversed;
            for (auto it = list.rbegin() + (list.size() - begin - 1); it != list.rend(); ++it)
                reversed.push_back(*it);
            return reversed;
        }

        /**
         * Returns a reversed copy of a portion of the list as a vector
         * @param begin The starting index of the portion to reverse
         * @param end The ending index of the portion to reverse
         * @return A vector containing the elements of the specified portion of the list in reverse order
         * @throws runtime_error if the list is empty or if the begin or end index is out of range
         */
        std::vector<T> reverse(int begin, int end) const
        {
            if (list.empty())
                throw std::runtime_error("empty list can not do this operation");
            if (begin < 0 || begin >= list.size() || end < 0 || end >= list.size() || begin > end)
                throw std::runtime_error("begin or end index out of range");
            if (begin == 0 && end == list.size() - 1)
                return reverse();
            if (begin == end)
                return {};
            std::vector<T> reversed;
            for (auto it = list.rbegin() + (list.size() - end); it != list.rbegin() + (list.size() - begin + 1); ++it)
                reversed.push_back(*it);
            return reversed;
        }

        /**
         * Multiplies all elements in the list by a given number
         * @param num The number to multiply by
         * @return The result of the multiplication
         */
        long double multiply(double num = 1) const
        {
            if (list.empty())
                throw std::runtime_error("empty list can not do this operation");
            if (!num)
                return 0;
            long double result = num;
            for (const double &LNum : list)
                result *= LNum;
            return result;
        }

        /**
         * Divides all elements in the list by a given number
         * @param num The number to divide by
         * @return The result of the division
         */
        long double divide(double num = 1) const
        {
            if (list.empty())
                throw std::runtime_error("empty list can not do this operation");
            if (!num)
                return 0;
            return num / sum();
        }

        /**
         * @brief Calculates the average value of the elements in the vector.
         *
         * This function computes the arithmetic mean of the stored elements.
         * The calculation depends on the internal implementation of the container
         * and the helper functions (e.g., divide).
         *
         * @return long double The average of all elements in the vector.
         *
         * @throws std::invalid_argument if the vector is empty, since averaging
         *         an empty container is undefined.
         */
        long double average() const
        {
            if (list.empty())
                throw std::invalid_argument("no average to an empty vector");
            return 1 / divide(list.size());
        }

        /**
         * Returns the size of the list
         * @return The size of the list
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        size_t size() const noexcept
        {
            if (max_size != -1)
                return max_size;
            return list.size();
        }

        /**
         * Pushes an element to the front of the list
         * @param value The element to push to the front
         */
        void push_front(T value)
        {
            if (max_size != -1 && static_cast<int>(list.size()) >= max_size)
                throw std::runtime_error("List size limit reached, cannot push front");
            std::vector<T> temp;
            temp.push_back(value);
            for (size_t i = 0; i < list.size(); i++)
                temp.push_back(list[i]);
            list.clear();
            list = temp;
            temp.clear();
        }

        /**
         * Pushes an element to the front of the list if it satisfies a given condition
         * @param fx A function that takes an element of type T and returns a boolean
         * @param value The element to push to the front
         * @throw runtime_error if the list size limit is reached
         * @note The function fx is applied to each element in the list, and the first
         */
        void push_front(std::function<bool(T)> fx, T value)
        {
            if (max_size != -1 && static_cast<int>(list.size()) >= max_size)
                throw std::runtime_error("List size limit reached, cannot push front");
            const auto temp = list;
            list.clear();
            for (size_t i = 0; i < temp.size(); i++)
            {
                if (fx(temp[i]))
                    list.push_back(value);
                list.push_back(temp[i]);
            }
        }

        /**
         * Returns the element at the front of the list
         * @return The element at the front of the list
         * @throws runtime_error if the list is empty
         */
        T top_front()
        {
            if (list.empty())
                throw std::runtime_error("List is empty");
            return list[0];
        }

        /**
         * Pops the front element from the list
         */
        void pop_front()
        {
            if (list.empty())
                throw std::runtime_error("List is empty, cannot pop front");
            std::vector<T> temp;
            for (size_t i = 1; i < list.size(); i++)
                temp.push_back(list[i]);
            list.clear();
            list = temp;
            temp.clear();
        }

        /**
         * Pushes an element to the back of the list
         * @param value The element to push to the back
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        void push_back(T value)
        {
            if (max_size != -1 && static_cast<int>(list.size()) >= max_size)
                throw std::runtime_error("List size limit reached, cannot push back");
            list.push_back(value);
        }

        /**
         * Returns the element at the back of the list
         * @return The element at the back of the list
         * @throws runtime_error if the list is empty
         */
        T top_back()
        {
            if (list.empty())
                throw std::runtime_error("List is empty");
            return list[list.size() - 1];
        }

        /**
         * Pops the back element from the list
         */
        void pop_back()
        {
            if (list.empty())
                throw std::runtime_error("List is empty, cannot pop back");
            list.pop_back();
        }

        /**
         * Inserts an element before a specified node in the list
         * @param Node The node before which to insert the new element
         * @param value The element to insert
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        bool find(T value) const noexcept
        {
            for (size_t i = 0; i < list.size(); i++)
                if (value == list[i])
                    return true;
            return false;
        }

        /**
         * Finds an element in the list that satisfies a given condition
         * @param fx A function that takes an element of type T and returns a boolean
         * @return True if an element satisfying the condition is found, false otherwise
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        bool find(std::function<bool(T)> fx) const noexcept
        {
            for (size_t i = 0; i < list.size(); i++)
            {
                if (fx(list[i]))
                    return true;
            }
            return false;
        }

        /**
         * Finds the index of a specified element in the list
         * @param Key The element to find
         * @return The index of the element, or -1 if not found
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        int find_index(T Key) const noexcept
        {
            for (size_t i = 0; i < list.size(); i++)
                if (Key == list[i])
                    return static_cast<int>(i);
            return -1; // Not found
        }

        /**
         * Finds the index of an element in the list that satisfies a given condition
         * @param fx A function that takes an element of type T and returns a boolean
         * @return The index of the element satisfying the condition, or -1 if not found
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        int find_index(std::function<bool(T)> fx) const noexcept
        {
            for (size_t i = 0; i < list.size(); i++)
            {
                if (fx(list[i]))
                    return static_cast<int>(i);
            }
            return -1; // Not found
        }

        /**
         * Erases an element at a specified index in the list
         * @param index The index of the element to erase
         */
        void erase_index(int index)
        {
            if (index < 0 || index >= static_cast<int>(list.size()))
                throw std::runtime_error("Index out of range");
            std::vector<T> temp;
            for (size_t i = 0; i < list.size(); i++)
            {
                if (static_cast<int>(i) == index)
                    continue;
                else
                    temp.push_back(list[i]);
            }
            list.clear();
            list = temp;
            temp.clear();
        }

        /**
         * Erases a specified element from the list
         * @param Key The element to erase
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        void erase(T Key) noexcept
        {
            std::vector<T> temp;
            for (size_t i = 0; i < list.size(); i++)
            {
                if (Key == list[i])
                    continue;
                else
                    temp.push_back(list[i]);
            }
            list.clear();
            list = temp;
            temp.clear();
        }

        /**
         * Erases elements from the list that satisfy a given condition
         * @param fx A function that takes an element of type T and returns a boolean
         * @note This function is noexcept, meaning it does not throw exceptions.
         * The function fx is applied to each element in the list, and elements for which
         */
        void erase(std::function<bool(T)> fx) noexcept
        {
            std::vector<T> temp;
            for (size_t i = 0; i < list.size(); i++)
            {
                if (fx(list[i]))
                    continue;
                else
                    temp.push_back(list[i]);
            }
            list.clear();
            list = temp;
        }

        /**
         * Checks if the list is empty
         * @return True if the list is empty, false otherwise
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        bool empty() const noexcept { return list.empty(); }

        /**
         * @brief Checks if the vector has a fixed size defined at construction.
         *
         * This function returns whether the container enforces a fixed size
         * (i.e., cannot grow or shrink dynamically). The information is taken
         * from the internal @c fixed_size flag.
         *
         * @return true  If the vector is fixed in size.
         * @return false If the vector is resizable.
         *
         * @note This function is @c constexpr and @c noexcept, meaning it can
         *       be evaluated at compile-time (if context allows) and guarantees
         *       not to throw exceptions.
         */
        constexpr bool is_fixed_size() const noexcept { return fixed_size; }

        /**
         * Reverses the list and updates the reversed list
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        void add_before(T Node, T Key) noexcept
        {
            std::vector<T> temp;
            for (size_t i = 0; i < list.size(); i++)
            {
                if (list[i] == Node)
                {
                    temp.push_back(Key);
                    temp.push_back(list[i]);
                }
                else
                    temp.push_back(list[i]);
            }
            list.clear();
            list = temp;
            temp.clear();
        }

        /**
         * Adds an element after a specified node in the list
         * @param Node The node after which to add the new element
         * @param Key The element to add
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        void add_after(T Node, T Key) noexcept
        {
            std::vector<T> temp;
            for (size_t i = 0; i < list.size(); i++)
            {
                if (list[i] == Node)
                {
                    temp.push_back(list[i]);
                    temp.push_back(Key);
                }
                else
                    temp.push_back(list[i]);
            }
            list.clear();
            list = temp;
            temp.clear();
        }

        /**
         * Returns an iterator to the beginning of the list.
         * This function provides an iterator that points to the first element of the list.
         * The returned iterator can be used in range-based for loops or with standard algorithms to traverse the list.
         * @return An iterator pointing to the beginning of the list.
         * @note This function is noexcept, meaning it guarantees not to throw exceptions.
         */
        auto begin() noexcept { return list.begin(); }

        /**
         * @brief Returns an iterator to the end of the list.
         * This function provides an iterator that points to the position just past the last element of the list.
         * The returned iterator can be used in range-based for loops or with standard algorithms to traverse the list.
         * @return An iterator pointing to the end of the list.
         * @note This function is noexcept, meaning it guarantees not to throw exceptions.
         */
        auto end() noexcept { return list.end(); }

        /**
         * @brief Overloads the stream insertion operator to print the contents of a vector.
         *
         * This friend function allows a vector of type T to be output to an std::ostream
         * in a formatted manner. It prints "vector: " followed by the elements of the vector,
         * enclosed in square brackets and separated by spaces.
         *
         * @tparam T The type of elements stored in the vector.
         * @param os The output stream to which the vector will be written.
         * @param list The vector to be printed.
         * @return Reference to the output stream after writing the vector.
         */
        friend std::ostream &operator<<(std::ostream &os, const vector<T> &list)
        {
            os << "vector: ";
            for (const auto &elem : list)
            {
                if (list.begin() == elem)
                    os << "[ ";
                else if (list.end() == elem)
                    os << "] ";
                else
                    os << elem << " ";
            }
            return os;
        }

        /**
         * Assignment operator for vector
         * @param vec Vector to assign to the vector
         * @post Replaces the current vector with the input vector
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        void operator=(const std::vector<T> &vec)
        {
            if (vec.size() > max_size && max_size != -1)
                throw std::runtime_error("List size limit reached, cannot assign vector");
            if (vec.empty())
                list = {};
            list = vec;
        }

        /**
         * Equality operator for VecList
         * @param vec Vector to compare with the list
         * @return True if the list is equal to the vector, false otherwise
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        bool operator==(const std::vector<T> &vec) const noexcept
        {
            if (vec.empty() && list.empty())
                return true;
            else if (vec.empty())
                return false;
            else if (list.empty())
                return false;
            else if (list.size() != vec.size())
                return false;
            for (size_t i = 0; i < vec.size(); i++)
                if (vec[i] != list[i])
                    return false;
            return true;
        }

        /**
         * Adds an element to the list
         * @param element Element to add
         * @post Adds the element to the list
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        void operator+(T element)
        {
            if (list.empty())
                return;
            auto temp = list;
            list.clear();
            for (size_t i = 0; i < temp.size(); i++)
                list.push_back(temp[i] + element);
        }

        /**
         * Adds a vector to the list
         * @param vec Vector to add
         * @post Adds the vector to the list
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        void operator+(const std::vector<T> &vec)
        {
            if (vec.empty() || list.empty())
                return;
            auto temp = list;
            list.clear();
            if (vec.size() == temp.size())
            {
                for (size_t i = 0; i < temp.size(); i++)
                    list.push_back(temp[i] + vec[i]);
            }
            else if (temp.size() > vec.size())
            {
                if (static_cast<int>(temp.size()) > max_size && max_size != -1)
                    throw std::runtime_error("List size limit reached, cannot add vector");
                for (size_t i = 0; i < vec.size(); i++)
                    list.push_back(temp[i] + vec[i]);
                for (size_t j = vec.size(); j < temp.size(); j++)
                    list.push_back(temp[j]);
            }
            else
            {
                if (static_cast<int>(vec.size()) > max_size && max_size != -1)
                    throw std::runtime_error("List size limit reached, cannot add vector");
                for (size_t i = 0; i < temp.size(); i++)
                    list.push_back(temp[i] + vec[i]);
                for (size_t j = temp.size(); j < vec.size(); j++)
                    list.push_back(vec[j]);
            }
        }

        /**
         * Subtracts an element from the list
         * @param element Element to subtract
         * @post Subtracts the element from the list
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        void operator-(T element)
        {
            if (list.empty())
                return;
            auto temp = list;
            list.clear();
            for (size_t i = 0; i < temp.size(); i++)
                list.push_back(temp[i] - element);
        }

        /**
         * Subtracts a vector from the list
         * @param vec Vector to subtract
         * @post Subtracts the vector from the list
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        void operator-(const std::vector<T> &vec)
        {
            if (vec.empty() || list.empty())
                return;
            auto temp = list;
            list.clear();
            if (vec.size() == temp.size())
            {
                for (size_t i = 0; i < temp.size(); i++)
                    list.push_back(temp[i] - vec[i]);
            }
            else if (temp.size() > vec.size())
            {
                if (static_cast<int>(temp.size()) > max_size && max_size != -1)
                    throw std::runtime_error("List size limit reached, cannot subtract vector");
                for (size_t i = 0; i < vec.size(); i++)
                    list.push_back(temp[i] - vec[i]);
                for (size_t j = vec.size(); j < temp.size(); j++)
                    list.push_back(temp[j]);
            }
            else
            {
                if (static_cast<int>(vec.size()) > max_size && max_size != -1)
                    throw std::runtime_error("List size limit reached, cannot subtract vector");
                for (size_t i = 0; i < temp.size(); i++)
                    list.push_back(temp[i] - vec[i]);
                for (size_t j = temp.size(); j < vec.size(); j++)
                    list.push_back(vec[j]);
            }
        }

        /**
         * Multiplies the list by a scalar
         * @param element Scalar to multiply by
         * @post Multiplies each element in the list by the scalar
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        void operator*(T element)
        {
            if (list.empty())
                return;
            auto temp = list;
            list.clear();
            for (size_t i = 0; i < temp.size(); i++)
                list.push_back(temp[i] * element);
        }

        /**
         * Divides the list by a scalar
         * @param element Scalar to divide by
         * @post Divides each element in the list by the scalar
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        void operator/(T element)
        {
            if (list.empty())
                return;
            auto temp = list;
            list.clear();
            for (size_t i = 0; i < temp.size(); i++)
                list.push_back(temp[i] / element);
        }

        /**
         * Index operator for VecList
         * @param i Index to access
         * @return Reference to the element at the specified index
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        T operator[](size_t i) const
        {
            if (list.empty())
                throw("empty list don't return value");
            if (i >= list.size())
                throw("out limites index");
            return list[i];
        }

        /**
         * Destructor for VecList
         */
        ~vector() = default;
    };

}

#endif // OPENUDT___CORE_VECTOR_MULTIDIMENSIONAL_VECTOR_HPP