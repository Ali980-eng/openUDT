/**
 * @file multidimensionalVector.hpp
 * @brief A header file defining the multidimensionalVector class, which is a wrapper over std::vector
 * providing list-like operations and additional functionalities such as summation, multiplication, and reversal.
 * The class supports both fixed-size and dynamic-size vectors, and includes various constructors, member functions, and operator overloads to manipulate the vector data.
 * The class is designed to be flexible and efficient, allowing for a wide range of operations on the stored elements while ensuring type safety and error handling.
 * @note This class is part of the openUDT library and is intended for use in C++23 compliant codebases.
 * @see vectorFunction.hpp for helper functions related to vector operations.
 * @author Ali Lafi
 * @date 2025/9/25
 */

#include <functional>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <string>
#include "vectorFunction.hpp"

#pragma once
#ifndef OPENUDT___UDT_VECTOR_MULTIDIMENSIONALVECTOR_HPP
#define OPENUDT___UDT_VECTOR_MULTIDIMENSIONALVECTOR_HPP

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
        int list_size = -1; // Default size to -1 to indicate uninitialized
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
                size_t num;
                list_size = static_cast<size_t>(list.size());
                if (list_size != -1)
                {
                    if (list_size != num)
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
            list_size = static_cast<size_t>(num);
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
         * @throws std::length_error if vec2d.size() exceeds list_size when list_size != -1.
         */
        vector(const std::vector<std::vector<T>> &vec2d, unsigned int i = 0)
        {
            if (vec2d.size() > list_size && list_size != -1)
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
            list_size = s;
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
         * @note The list_size member variable is set to the value of s, which represents the size of the vector. This value is used in other member functions to enforce the fixed size of the vector and to perform bounds checking when accessing elements.
         * @note The use of int for size parameters is not recommended in modern C++ code due to potential issues with negative values and type safety. It is generally better to use size_t for size parameters to ensure that they are non-negative and to avoid potential overflow issues. Consider updating the code to use size_t for size parameters for improved safety and clarity.
         */
        vector(int s)
        {
            if (s < 0)
                throw std::invalid_argument("size can not be negative");
            list_size = static_cast<size_t>(s);
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
            if (list_size != -1 && list.size() > s)
                throw std::runtime_error("New size is smaller than current list size");
            list_size = s;
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
            if (list_size != -1 && list.size() > s)
            {
                std::vector<T> temp = list;
                list.clear();
                for (size_t i = 0; i < s; i++)
                    list.push_back(temp[i]);
                list_size = static_cast<int>(s);
                return;
            }
            list_size = static_cast<int>(s);
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
            if (list_size != -1)
                return list_size;
            return list.size();
        }

        /**
         * Pushes an element to the front of the list
         * @param value The element to push to the front
         */
        void push_front(T value)
        {
            if (list_size != -1 && static_cast<int>(list.size()) >= list_size)
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
            if (list_size != -1 && static_cast<int>(list.size()) >= list_size)
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
        void push_back(T value) noexcept
        {
            if (list_size != -1 && static_cast<int>(list.size()) >= list_size)
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
        void operator=(const std::vector<T> &vec) noexcept
        {
            if (vec.size() > list_size && list_size != -1)
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
                if (static_cast<int>(temp.size()) > list_size && list_size != -1)
                    throw std::runtime_error("List size limit reached, cannot add vector");
                for (size_t i = 0; i < vec.size(); i++)
                    list.push_back(temp[i] + vec[i]);
                for (size_t j = vec.size(); j < temp.size(); j++)
                    list.push_back(temp[j]);
            }
            else
            {
                if (static_cast<int>(vec.size()) > list_size && list_size != -1)
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
                if (static_cast<int>(temp.size()) > list_size && list_size != -1)
                    throw std::runtime_error("List size limit reached, cannot subtract vector");
                for (size_t i = 0; i < vec.size(); i++)
                    list.push_back(temp[i] - vec[i]);
                for (size_t j = vec.size(); j < temp.size(); j++)
                    list.push_back(temp[j]);
            }
            else
            {
                if (static_cast<int>(vec.size()) > list_size && list_size != -1)
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

    /**
     * @brief Performs Gauss-Jordan elimination on a given augmented matrix.
     *
     * This function transforms the input augmented matrix `mat` into its reduced
     * row echelon form (RREF). It is typically used to solve systems of linear
     * equations.
     *
     * @param mat The augmented matrix represented as a vector of vectors of
     * doubles. Each row should have n+1 elements for a system of n equations (n
     * variables + 1 constant).
     * @param status Reference to an integer that will be set to indicate the result
     * of the elimination:
     *        - 0: Successful elimination, unique solution found.
     *        - 1: Matrix is singular (no unique solution).
     *        - 2: Infinite solutions exist.
     *        - 3: No solution exists.
     *
     * @return The matrix in reduced row echelon form after elimination.
     *
     * @throws invalid_argument if the input matrix is empty.
     *
     * @note The input matrix is modified and returned in its transformed state.
     */
    std::vector<std::vector<double>> gauss_jordan(std::vector<std::vector<double>> mat, int &status)
    {
        if (mat.empty())
            throw std::invalid_argument("Empty matrix");
        int n = static_cast<int>(mat.size());
        status = 0;
        for (int i = 0; i < n; i++)
        {
            if (mat[i][i] == 0)
            {
                int c = 1;
                while ((i + c) < n && mat[i + c][i] == 0)
                    c++;
                if ((i + c) == n)
                {
                    status = 1;
                    break;
                }
                std::swap(mat[i], mat[i + c]);
            }
            for (int j = 0; j < n; j++)
            {
                if (i != j)
                {
                    double pro = mat[j][i] / mat[i][i];
                    for (int k = 0; k <= n; k++)
                        mat[j][k] -= mat[i][k] * pro;
                }
            }
        }
        if (status == 1)
        {
            status = 3;
            for (int i = 0; i < n; i++)
            {
                double sum = 0;
                for (int j = 0; j < n; j++)
                    sum += mat[i][j];
                if (sum == mat[i][n])
                    status = 2;
            }
        }
        return mat;
    }

    /**
     * A generic 2D vector wrapper that provides utilities for:
     * - shape checking (square or NxM),
     * - flattening,
     * - transposition,
     * - accessors for rows and internal states.
     *
     * @tparam T Type of elements stored (int, float, string, etc.)
     */
    template <typename T>
    class vector_2d
    {
    private:
        int n = -1, m = -1;
        std::vector<std::vector<T>> vec_2D;

    protected:
        /**
         * Determines if the target matrix is a fixed 2x2 square matrix
         *
         * The function checks either:
         *   - The internal 2D vector (member `vec_2D`) when no argument is provided,
         * or
         *   - The provided 2D vector `vec` when passed as an argument
         *
         * @param vec Optional external 2D vector to evaluate (uses internal vector if
         * empty)
         * @return `true` if the matrix has exactly 2 rows and each row contains
         * exactly 2 columns, `false` otherwise
         */
        bool square2X2(const std::vector<std::vector<T>> &vec = {})
        {
            const auto &target = vec.empty() ? vec_2D : vec;
            if (target.size() != 2)
                return false;
            return target[0].size() == 2 && target[1].size() == 2;
        }

        /**
         * Determines if the target matrix is a fixed 3x3 square matrix
         *
         * Evaluates either:
         *   - The internal 2D vector (member `vec_2D`) when no argument is provided,
         * or
         *   - The provided 2D vector `vec` when specified
         *
         * @param vec Optional external matrix to check (defaults to internal vector
         * if empty)
         * @return `true` if the matrix has exactly 3 rows and each row contains
         * exactly 3 columns, `false` otherwise
         */
        bool square3X3(const std::vector<std::vector<T>> &vec = {})
        {
            const auto &target = vec.empty() ? vec_2D : vec;
            if (target.size() != 3)
                return false;
            return target[0].size() == 3 && target[1].size() == 3 &&
                   target[2].size() == 3;
        }

        /**
         * Verifies if the target matrix is an N×N square matrix
         *
         * Checks either:
         *   - The internal 2D vector (member `vec_2D`) when no argument is provided,
         * or
         *   - The provided 2D vector `vec` when specified
         *
         * @param vec Optional external matrix to evaluate (uses internal vector if
         * empty)
         * @return `true` if the matrix is square (all rows have same length as total
         * rows), `false` otherwise
         */
        bool squareNXN(const std::vector<std::vector<T>> &vec = {})
        {
            const auto &target = vec.empty() ? vec_2D : vec;
            for (const auto &row : target)
            {
                if (row.size() != target.size())
                    return false;
            }
            return true;
        }

        /**
         * Determines if the internal matrix matches specified n×m dimensions
         *
         * Checks if the 2D vector has exactly `nnum` rows and each row contains
         * exactly `mnum` columns. This only evaluates the internal member `vec_2D`.
         *
         * @param nnum Expected number of rows (first dimension)
         * @param mnum Expected number of columns (second dimension)
         * @return `true` if matrix dimensions exactly match n×m, `false` otherwise
         */
        bool isNXM(int nnum, int mnum)
        {
            if (static_cast<int>(vec_2D.size()) == nnum)
            {
                for (size_t i = 0; i < vec_2D.size(); i++)
                {
                    if (static_cast<int>(vec_2D[i].size()) != mnum)
                        return false;
                }
                return true;
            }
            return false;
        }

        /**
         * Determines if the target matrix is a square matrix of any valid size
         *
         * Checks for square matrices of either:
         *   - Standard sizes (2×2, 3×3, or N×N) on internal `vec_2D` when no argument
         * is provided
         *   - Standard sizes (2×2, 3×3, or N×N) on provided matrix `mat` when
         * specified
         *
         * @param mat Optional external matrix to evaluate (uses internal vector if
         * empty)
         * @return `true` if the matrix is square (2×2, 3×3, or general N×N), `false`
         * otherwise
         */
        bool is_square_matrix(const std::vector<std::vector<T>> &mat = {})
        {
            if (mat.empty())
                return square2X2() || square3X3() || squareNXN();
            return square2X2(mat) || square3X3(mat) || squareNXN(mat);
        }

        /**
         * Determines if the target matrix is a diagonal matrix
         *
         * A diagonal matrix is a square matrix where all elements outside
         * the main diagonal are zero. The function checks either:
         *   - The internal member `vec_2D` when no argument is provided, or
         *   - The provided matrix `mat` when specified
         *
         * @param mat Optional external matrix to evaluate (uses internal matrix if
         * empty)
         * @return `true` if:
         *           - The matrix is square, AND
         *           - All non-diagonal elements are zero
         *         `false` otherwise
         */
        bool is_diagonal_matrix(const std::vector<std::vector<T>> &mat = {})
        {
            const auto &target = mat.empty() ? vec_2D : mat;
            if (!is_square_matrix(target))
                return false;
            size_t n = target.size();
            for (size_t i = 0; i < n; ++i)
            {
                for (size_t j = 0; j < n; ++j)
                {
                    if (i != j && target[i][j] != T(0))
                        return false;
                }
            }
            return true;
        }

        /**
         * Determines if the target matrix is an identity matrix
         *
         * An identity matrix is a square matrix where:
         *   - All main diagonal elements are 1, AND
         *   - All other elements are 0
         *
         * The function evaluates either:
         *   - The internal member `vec_2D` when no argument is provided, OR
         *   - The provided matrix `mat` when specified
         *
         * @param mat Optional external matrix to evaluate (defaults to internal
         * matrix if empty)
         * @return `true` if:
         *           - The matrix is square, AND
         *           - All diagonal elements equal 1, AND
         *           - All non-diagonal elements equal 0
         *         `false` otherwise
         */
        bool is_identity_matrix(const std::vector<std::vector<T>> &mat = {})
        {
            const auto &target = mat.empty() ? vec_2D : mat;
            if (!is_square_matrix(target))
                return false;
            size_t n = target.size();
            for (size_t i = 0; i < n; ++i)
            {
                for (size_t j = 0; j < n; ++j)
                {
                    if ((i == j && target[i][j] != T(1)) ||
                        (i != j && target[i][j] != T(0)))
                        return false;
                }
            }
            return true;
        }

        /**
         * Determines if the target matrix is an upper triangular matrix
         *
         * An upper triangular matrix is a square matrix where:
         *   - All elements below the main diagonal are zero
         *   - Elements on or above the diagonal may be any value
         *
         * The function evaluates either:
         *   - The internal member `vec_2D` when no argument is provided, or
         *   - The provided matrix `mat` when specified
         *
         * @param mat Optional external matrix to evaluate (defaults to internal
         * matrix if empty)
         * @return `true` if:
         *           - The matrix is square, AND
         *           - All elements below the main diagonal are zero
         *         `false` otherwise
         */
        bool is_upper_triangular(const std::vector<std::vector<T>> &mat = {})
        {
            const auto &target = mat.empty() ? vec_2D : mat;
            if (!is_square_matrix(target))
                return false;
            size_t n = target.size();
            for (size_t i = 1; i < n; ++i)
            {
                for (size_t j = 0; j < i; ++j)
                {
                    if (target[i][j] != T(0))
                        return false;
                }
            }
            return true;
        }

        /**
         * Determines if the target matrix is a lower triangular matrix
         *
         * A lower triangular matrix is a square matrix where:
         *   - All elements above the main diagonal are zero
         *   - Elements on or below the diagonal may be any value
         *
         * @param mat Optional external matrix to evaluate (uses internal matrix if
         * empty)
         * @return `true` if:
         *           - The matrix is square, AND
         *           - All elements above the main diagonal are zero
         *         `false` otherwise
         */
        bool is_lower_triangular(const std::vector<std::vector<T>> &mat = {})
        {
            const auto &target = mat.empty() ? vec_2D : mat;
            if (!is_square_matrix(target))
                return false;
            size_t n = target.size();
            for (size_t i = 0; i < n - 1; ++i)
            {
                for (size_t j = i + 1; j < n; ++j)
                {
                    if (target[i][j] != T(0))
                        return false;
                }
            }
            return true;
        }

        /**
         * Identifies the specific type of matrix
         *
         * Tests the matrix against known matrix types in this order:
         *   1. Identity Matrix
         *   2. Diagonal Matrix
         *   3. Upper Triangular Matrix
         *   4. Lower Triangular Matrix
         *   5. Square Matrix (generic)
         *
         * @param mat Optional external matrix to evaluate (uses internal matrix if
         * empty)
         * @return String name of the matrix type or "Unknown Form" if no match found
         */
        std::string matrix_type(const std::vector<std::vector<T>> &mat = {})
        {
            const auto &target = mat.empty() ? vec_2D : mat;
            if (is_identity_matrix(target))
                return "Identity Matrix";
            if (is_diagonal_matrix(target))
                return "Diagonal Matrix";
            if (is_upper_triangular(target))
                return "Upper Triangular Matrix";
            if (is_lower_triangular(target))
                return "Lower Triangular Matrix";
            return is_square_matrix(target) ? "Square Matrix" : "Unknown Form";
        }

        /**
         * Calculates the determinant of a 2×2 matrix
         *
         * @param vec Optional external matrix (uses internal matrix if empty)
         * @return The determinant value as long double
         * @throws When:
         *           - The matrix is empty, OR
         *           - The matrix is not 2×2
         */
        long double determinant2X2(const std::vector<std::vector<T>> &vec = {})
        {
            const auto &target = vec.empty() ? vec_2D : vec;
            if (target.empty())
                throw std::invalid_argument("Empty matrix");
            if (!square2X2(target))
                throw std::invalid_argument("Matrix is not 2x2");
            return (target[0][0] * target[1][1] - target[0][1] * target[1][0]);
        }

        /**
         * Calculates the determinant of a 3×3 matrix using Rule of Sarrus
         *
         * @param vec Optional external matrix (uses internal matrix if empty)
         * @return The determinant value as long double
         * @throws When:
         *           - The matrix is empty, OR
         *           - The matrix is not 3×3
         */
        long double determinant3X3(const std::vector<std::vector<T>> &vec = {})
        {
            const auto &target = vec.empty() ? vec_2D : vec;
            if (target.empty())
                throw std::invalid_argument("Empty matrix");
            if (!square3X3(target))
                throw std::invalid_argument("Matrix is not 3x3");
            return (target[0][0] *
                        (target[1][1] * target[2][2] - target[2][1] * target[1][2]) -
                    target[0][1] *
                        (target[1][0] * target[2][2] - target[2][0] * target[1][2]) +
                    target[0][2] *
                        (target[1][0] * target[2][1] - target[2][0] * target[1][1]));
        }

        /**
         * Calculates the determinant of an N×N matrix using Gaussian elimination with
         * partial pivoting
         * @param vec Optional external matrix (uses internal matrix if empty)
         * @return The determinant value as long double
         * @throws invalid_argument if:
         *          - The matrix is empty
         *          - The matrix is not square
         */
        long double determinantNXN(const std::vector<std::vector<T>> &vec = {})
        {
            const auto &target_ref = vec.empty() ? vec_2D : vec;
            if (target_ref.empty())
                throw std::invalid_argument("Empty matrix");
            if (!squareNXN(target_ref))
                throw std::invalid_argument("Matrix is not square");
            size_t n = target_ref.size();
            std::vector<std::vector<long double>> mat;
            mat.reserve(n);
            // Copy with casting to long double
            for (const auto &row : target_ref)
                mat.emplace_back(row.begin(), row.end());
            long double det = 1.0;
            int swap_count = 0;
            for (size_t i = 0; i < n; ++i)
            {
                // Partial pivoting
                size_t pivot_row = i;
                for (size_t j = i + 1; j < n; ++j)
                {
                    if (abs(mat[j][i]) > abs(mat[pivot_row][i]))
                        pivot_row = j;
                }
                // If pivot element is zero, determinant is zero
                if (mat[pivot_row][i] == 0.0)
                    return 0.0;
                // Swap rows if needed
                if (i != pivot_row)
                {
                    std::swap(mat[i], mat[pivot_row]);
                    ++swap_count;
                }
                // Eliminate below
                for (size_t j = i + 1; j < n; ++j)
                {
                    long double factor = mat[j][i] / mat[i][i];
                    for (size_t k = i; k < n; ++k)
                        mat[j][k] -= mat[i][k] * factor;
                }
            }
            // Multiply diagonal elements
            for (size_t i = 0; i < n; ++i)
                det *= mat[i][i];
            // Adjust sign based on number of swaps
            if (swap_count % 2 != 0)
                det = -det;
            return det;
        }

        /**
         * Flattens a 2D matrix into a 1D vector
         *
         * @param vec Optional external matrix to flatten (uses internal matrix if
         * empty)
         * @note Results are stored in member variable `flatten_vec`
         * @warning Will skip operation if input matrix is empty
         */
        std::vector<T> flatten(const std::vector<std::vector<T>> &vec = {}) const
        {
            const auto &target = vec.empty() ? vec_2D : vec;
            std::vector<T> flatten_vec;
            if (target.empty())
                throw std::invalid_argument("The 2D vector is empty");
            for (const auto &row : target)
            {
                for (const auto &elem : row)
                    flatten_vec.push_back(elem);
            }
            return flatten_vec;
        }

        /**
         * Computes the transpose of a matrix
         *
         * @param vec Optional external matrix to transpose (uses internal matrix if
         * empty)
         * @note Results are stored in member variable `transpose_2D`
         * @warning Will skip operation if input matrix is empty
         */
        std::vector<std::vector<T>> transpose(const std::vector<std::vector<T>> &vec = {}) const
        {
            const auto &target = vec.empty() ? vec_2D : vec;
            std::vector<std::vector<T>> transpose_2D;
            if (target.empty() || target[0].empty())
                throw std::invalid_argument("The 2D vector is empty");
            for (size_t i = 0; i < target[0].size(); i++)
                transpose_2D.push_back({});
            for (size_t i = 0; i < target.size(); i++)
            {
                for (size_t j = 0; j < target[0].size(); j++)
                    transpose_2D[j].push_back(target[i][j]);
            }
            return transpose_2D;
        }

        /**
         * @brief Computes the inverse of a 2x2 matrix.
         *
         * If no matrix is provided, it uses the internal vec_2D member.
         * Throws exceptions if the input is empty, not square, or singular.
         *
         * @param v Optional 2x2 matrix to invert.
         * @return A 2x2 matrix representing the inverse of the input matrix.
         * @throws std::invalid_argument if the input and internal vector are empty,
         *         if the matrix is not 2x2 square, or if the determinant is zero (non-invertible).
         */
        std::vector<std::vector<T>> inverse2X2(const std::vector<std::vector<T>> &v = {})
        {
            if (v.empty() && vec_2D.empty())
                throw std::invalid_argument("Empty Error: all input vector is empty");
            const auto &target = v.empty() ? vec_2D : v;
            auto d = determinant2X2(target);
            if (!square2X2(target))
                throw std::invalid_argument("the target vector is not a square matrix with size 2");
            if (d == 0)
                throw std::invalid_argument("the matrix is not invertible matrix");
            std::vector<std::vector<T>> result_v = {
                {target[1][1], -target[0][1]},
                {-target[1][0], target[0][0]}};
            for (std::vector<T> &v : result_v)
            {
                for (T &element : v)
                    element /= d;
            }
            return result_v;
        }

        /**
         * @brief Computes the inverse of a 3x3 matrix.
         *
         * If no matrix is provided, it uses the internal vec_2D member.
         * The inverse is calculated using the adjugate method:
         * 1. Compute the matrix of cofactors.
         * 2. Transpose the cofactor matrix (adjugate).
         * 3. Divide each element by the determinant.
         *
         * @param v Optional 3x3 matrix to invert.
         * @return A 3x3 matrix representing the inverse of the input matrix.
         * @throws std::invalid_argument if the input and internal vector are empty,
         *         if the matrix is not 3x3 square, or if the determinant is zero (non-invertible).
         */
        std::vector<std::vector<T>> inverse3X3(const std::vector<std::vector<T>> &v = {})
        {
            if (v.empty() && vec_2D.empty())
                throw std::invalid_argument("Empty Error: all input vector is empty");
            const auto &target = v.empty() ? vec_2D : v;
            if (!square3X3(target))
                throw std::invalid_argument("the target vector is not a square matrix with size 3");
            auto d = determinant3X3(target);
            if (d == 0)
                throw std::invalid_argument("the matrix is not invertible matrix");

            std::vector<std::vector<T>> cof(3, std::vector<T>(3));
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    T minor_det = determinant2X2(erase_row_column(target, i, j));
                    cof[i][j] = ((i + j) % 2 == 0 ? 1 : -1) * minor_det;
                }
            }
            // adjoint = transpose(cofactors)
            auto adj = transpose(cof);
            // inverse = adj / determinant
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    adj[i][j] /= d;
                }
            }
            return adj;
        }

    public:
        /**
         * Default constructor - initializes empty matrices
         *
         * Creates a vector_2d object with:
         *   - vec_2D: Empty 2D vector
         *   - tranvec_2D: Empty transpose vector
         *   - flatten: Empty flattened vector
         */
        vector_2d() { vec_2D = {}; }

        /**
         * Square matrix constructor
         *
         * @param num Size for both dimensions (n×n)
         * @throws Error if size ≤ 0
         */
        vector_2d(int num)
        {
            if (num <= 0)
                throw std::invalid_argument("Size Error: the size have to be greater than zero");
            else
            {
                n = num;
                m = num;
            }
        }

        /**
         * Rectangular matrix constructor
         *
         * @param Nnum Number of rows
         * @param Mnum Number of columns
         * @throws Error if either dimension ≤ 0
         */
        vector_2d(int Nnum, int Mnum)
        {
            if (Nnum <= 0 || Nnum <= 0)
                throw std::invalid_argument("Size Error: the size have to be greater than zero");
            else
            {
                n = Nnum;
                m = Mnum;
            }
        }

        /**
         * Initializer list constructor
         *
         * @param init Initializer list of vectors to create the matrix
         */
        vector_2d(std::initializer_list<std::vector<T>> init) : vec_2D(init)
        {
            size_t nnum, mnum;
            nnum = static_cast<size_t>(vec_2D.size());
            mnum = nnum > 0 ? static_cast<size_t>(vec_2D[0].size()) : -1;
            if (n != -1 && m != -1)
            {
                if (nnum != n || mnum != m)
                {
                    throw std::runtime_error(
                        "Dimension Error: Initializer list dimensions do not match fixed "
                        "size");
                }
            }
        }

        /**
         * Initializer list constructor with specified number of rows
         * @param init Initializer list of vectors to create the matrix
         * @param num Number of rows (must be > 0)
         */
        vector_2d(size_t num, std::initializer_list<std::vector<T>> init) : vec_2D(init)
        {
            if (num > 0)
            {
                n = static_cast<int>(num);
                m = static_cast<int>(vec_2D.size() > 0 ? vec_2D[0].size() : 0);
            }
            else
            {
                throw std::invalid_argument("Size Error: the size have to be greater than zero");
                n = -1;
                m = -1;
            }
        }

        /**
         * Initializer list constructor with specified dimensions
         * @param init Initializer list of vectors to create the matrix
         * @param Nnum Number of rows (must be > 0)
         * @param Mnum Number of columns (must be > 0)
         */
        vector_2d(int Nnum, int Mnum, std::initializer_list<std::vector<T>> init)
            : vec_2D(init)
        {
            if (Nnum <= 0 || Mnum <= 0)
            {
                throw std::invalid_argument("Size Error: the size have to be greater than zero");
                n = -1;
                m = -1;
            }
            else
            {
                n = Nnum;
                m = Mnum;
            }
        }

        /**
         * Copy constructor from existing 2D vector
         *
         * @param vec2d 2D vector to copy into the matrix
         */
        vector_2d(const std::vector<std::vector<T>> &vec2d) { vec_2D = vec2d; }

        /**
         * Copy constructor from another vector_2d object
         * @param other The vector_2d object to copy from
         * Initializes the new object with the same internal state as `other`:
         *   - vec_2D: Copy of the 2D vector
         *   - transpose_2D: Copy of the transpose vector
         *   - flatten_vec: Copy of the flattened vector
         */
        vector_2d(const vector_2d<T> &other)
        {
            vec_2D = other.vec_2D;
            n = other.n;
            m = other.m;
        }

        /**
         * @brief Constructs a 2D vector container from a 3D vector.
         *
         * This constructor initializes the internal 2D container (vec_2D)
         * using the provided 3D vector. If fixed dimensions (n, m) are defined,
         * it validates that the provided data matches those constraints.
         *
         * @param vec3d Input 3D vector used to initialize the 2D container.
         * @param i Optional parameter (currently unused, defaults to 0).
         *
         * @throws std::length_error if:
         *         - n != -1 and the outer size of vec3d does not match n.
         *         - m != -1 and any inner 1D vector does not have size equal to m.
         */
        vector_2d(const std::vector<std::vector<std::vector<T>>> &vec3d, int i = 0)
        {
            if (n != -1 && m != -1)
            {
                if (n != vec3d.size())
                    throw std::length_error("unmatched size");
                for (const std::vector<std::vector<T>> &vec2d : vec3d)
                {
                    for (const std::vector<T> &vec : vec2d)
                    {
                        if (vec.size() != m)
                            throw std::length_error("unmatched size");
                    }
                }
            }
            vec_2D = vec3d;
        }

        /**
         * Determines the general matrix type classification
         *
         * Classifies matrices into these categories:
         *   1. Empty Matrix
         *   2. Invalid Matrix (irregular dimensions)
         *   3. Row Matrix (1×n)
         *   4. Column Matrix (n×1)
         *   5. Square Matrix types (via matrix_type())
         *   6. Rectangular Matrix
         *
         * @param mat Optional external matrix to evaluate (uses internal matrix if
         * empty)
         * @return String name of the matrix classification
         */
        std::string general_matrix_type(const std::vector<std::vector<T>> &mat = {})
        {
            const auto &target = mat.empty() ? vec_2D : mat;
            if (target.empty())
                return "Empty Matrix";
            size_t n_size = target.size();
            size_t m_size = target[0].size();
            for (const auto &row : target)
            {
                if (row.size() != m_size)
                    return "Invalid Matrix";
            }
            if (n_size == 1 && m_size >= 2)
                return "Row Matrix";
            if (n_size >= 2 && m_size == 1)
                return "Column Matrix";
            if (n_size == m_size)
                return matrix_type(target);
            if (m_size != n_size)
                return "Rectangular Matrix";
            return "Unknown Matrix";
        }

        /**
         * Sets/updates the main 2D vector storage
         *
         * @param vec2d The new 2D vector to store as the main matrix
         * @note Overwrites any existing content in vec_2D
         */
        void set(const std::vector<std::vector<T>> &vec2d) noexcept { vec_2D = vec2d; }

        /**
         * Sets the fixed dimensions for the matrix
         *
         * @param num Size for both dimensions (n×n)
         * @throws Error if size ≤ 0
         * @note Does not automatically resize existing matrix data
         * @warning This will not resize the internal 2D vector, only updates the size
         * attributes Use set_2dvec() to resize the internal vector if needed
         */
        void set_size(int num) noexcept
        {
            if (num <= 0)
                throw std::invalid_argument("Size Error: the size have to be greater than zero");
            else
            {
                n = num;
                m = num;
            }
        }

        /**
         * Sets the fixed dimensions for the matrix
         *
         * @param Nnum Number of rows (must be > 0)
         * @param Mnum Number of columns (must be > 0)
         * @throws Error if either dimension ≤ 0
         * @note Does not automatically resize existing matrix data
         */
        void set_size(size_t Nnum, size_t Mnum) noexcept
        {
            if (Nnum <= 0 || Mnum <= 0)
                throw std::invalid_argument("Size Error: the size have to be greater than zero");
            else
            {
                n = static_cast<int>(Nnum);
                m = static_cast<int>(Mnum);
            }
        }

        /**
         * Returns a const reference to the internal 2D vector
         *
         * @return Const reference to vec_2D, or empty vector if matrix is empty
         * @warning Returned reference becomes invalid if matrix is modified
         */
        const std::vector<std::vector<T>> &get() const noexcept { return vec_2D; }

        /**
         * Returns a deep copy of the internal 2D vector
         *
         * @return Copy of vec_2D, or empty vector if matrix is empty
         */
        std::vector<std::vector<T>> get_copy_2dvec() const noexcept { return vec_2D; }

        /**
         * Returns a const reference to a specific row vector
         *
         * @param index Row index (0-based)
         * @return Const reference to the requested row vector
         * @throws out_of_range if index is invalid
         */
        const std::vector<T> &get(size_t index) const
        {
            if (index >= vec_2D.size())
                throw std::out_of_range("Index is out of range.");
            return vec_2D[index];
        }

        /**
         * Returns a deep copy of a specific row vector
         *
         * @param index Row index (0-based)
         * @return Copy of the requested row vector
         * @throws out_of_range if index is invalid
         */
        std::vector<T> get_copy(size_t index)
        {
            if (index >= vec_2D.size())
                throw std::out_of_range("Index is out of range.");
            return vec_2D[index];
        }

        /**
         * Accesses an element in the 2D matrix
         *
         * @param ind1 Row index (0-based)
         * @param ind2 Column index (0-based)
         * @return Copy of the element at [ind1][ind2]
         * @throws out_of_range if either index is invalid
         */
        T get(size_t ind1, size_t ind2)
        {
            if (ind1 >= vec_2D.size())
                throw std::out_of_range("Row index is out of range.");
            if (ind2 >= vec_2D[ind1].size())
                throw std::out_of_range("Column index is out of range.");
            return vec_2D[ind1][ind2];
        }

        /**
         * Returns a const reference to the transposed matrix
         *
         * @return Const reference to transpose_2D
         * @note Reference is invalid if matrix is modified
         */
        std::vector<std::vector<T>> get_transpose(const std::vector<std::vector<T>> &v2d = {}) const { return transpose(); }

        /**
         * Returns a const reference to a row in the transposed matrix
         *
         * @param index Row index (0-based) in transposed matrix
         * @return Const reference to the requested row
         * @throws out_of_range if index is invalid
         */
        const std::vector<T> &get_transpose(size_t index, const std::vector<std::vector<T>> &v2d = {}) const
        {
            if (index >= transpose(v2d).size())
                throw std::out_of_range("Index is out of range.");
            return transpose(v2d)[index];
        }

        /**
         * Returns a deep copy of a row in the transposed matrix
         *
         * @param index Row index (0-based) in transposed matrix
         * @return Copy of the requested row
         * @throws out_of_range if index is invalid
         */
        std::vector<T> get_copy_transpose(size_t index, const std::vector<std::vector<T>> &v2d = {}) const
        {
            if (index >= transpose().size())
                throw std::out_of_range("Index is out of range.");
            return transpose(v2d)[index];
        }

        /**
         * Accesses an element in the transposed matrix
         *
         * @param ind1 Row index (0-based) in transposed matrix
         * @param ind2 Column index (0-based) in transposed matrix
         * @return The element at [ind1][ind2] in transpose_2D
         * @throws out_of_range if either index is invalid
         */
        T get_transpose(size_t ind1, size_t ind2, const std::vector<std::vector<T>> &v2d = {})
        {
            if (ind1 >= transpose().size())
                throw std::out_of_range("Row index is out of range.");
            if (ind2 >= transpose()[ind1].size())
                throw std::out_of_range("Column index is out of range.");
            return transpose(v2d)[ind1][ind2];
        }

        /**
         * Returns a const reference to the flattened vector
         *
         * @return Const reference to flatten_vec
         * @note Reference is invalid if matrix is modified
         */
        std::vector<T> get_flatten(const std::vector<std::vector<T>> &v2d = {}) const { return flatten(v2d); }

        /**
         * Accesses an element in the flattened vector
         *
         * @param index Element position (0-based)
         * @return The element at specified position
         * @throws out_of_range if index is invalid
         */
        T get_flatten(size_t index, const std::vector<std::vector<T>> &v2d = {}) const
        {
            if (index >= flatten().size())
                throw std::out_of_range("Index is out of range.");
            return flatten(v2d)[index];
        }

        /**
         * @brief Accesses an entire row of the 2D vector.
         *
         * @param i The row index.
         * @return std::vector<T> A copy of the row at index @p i.
         *
         * @note This method returns the row by value (copy). For large datasets,
         *       consider using references to avoid extra copies.
         * @warning No bounds checking is performed. Using an out-of-range index
         *          leads to undefined behavior.
         */
        std::vector<T> at(size_t i) const
        {
            if (i >= vec_2D.size())
                throw std::out_of_range("i parameter is bigger than the vector size or less than zero");
            return vec_2D[i];
        }

        /**
         * @brief Accesses a single element of the 2D vector.
         *
         * @param i The row index.
         * @param j The column index within the row @p i.
         * @return T A copy of the element at position (i, j).
         *
         * @note This method returns the element by value (copy).
         * @warning No bounds checking is performed. Using out-of-range indices
         *          leads to undefined behavior.
         */
        T at(size_t i, size_t j) const
        {
            if (i >= vec_2D.size())
                throw std::out_of_range("i parameter is bigger than the vector size or less than zero");
            if (j >= vec_2D[i].size())
                throw std::out_of_range("j parameter is bigger than the vector size or less than zero");
            return vec_2D[i][j];
        }

        /**
         * Appends a vector to the end of the 2D matrix
         *
         * @param vec Vector to append
         * @throws Error if:
         *           - Matrix has fixed size and is full (n×m reached), OR
         *           - Input vector dimensions don't match matrix columns
         */
        void push(const std::vector<T> &vec)
        {
            if (n != -1 && vec_2D.size() == n)
                throw std::length_error("Capacity Error: Cannot exceed fixed row count");
            else if (m != -1 && vec.size() != m)
                throw std::length_error("Dimension Error: Vector size must match column count");
            else
                vec_2D.push_back(vec);
        }

        /**
         * @brief Pushes a new vector into the 2D container.
         *
         * This function inserts a new row (1D vector) into the internal
         * 2D vector (`vec_2D`). It validates dimensions if the container
         * is configured with fixed sizes.
         *
         * @param vec A custom vector<T> object to be added. The underlying
         *            std::vector<T> is extracted using vec.get().
         *
         * @throws std::length_error if:
         *         - n != -1 and the current row count already reached n
         *           (capacity overflow).
         *         - m != -1 and the size of vec does not equal m
         *           (dimension mismatch).
         */
        void push(const vector<T> &vec)
        {
            if (n != -1 && vec_2D.size() == n)
                throw std::length_error("Capacity Error: Cannot exceed fixed row count");
            else if (m != -1 && vec.size() != m)
                throw std::length_error("Dimension Error: Vector size must match column count");
            else
                vec_2D.push_back(vec.get());
        }

        /**
         * Appends a default-initialized element to a specific row
         *
         * @param index Row index to modify (0-based)
         * @throws Error if:
         *           - Index is out of bounds, OR
         *           - Row has reached maximum column count
         */
        void push(size_t index, T element)
        {
            if (index >= vec_2D.size())
                throw std::out_of_range("Index Error: Row index out of range");
            else if (m != -1 && vec_2D[index].size() == m)
                throw std::length_error("Capacity Error: Cannot exceed fixed column count");
            else
                vec_2D[index].push_back(element);
        }

        /**
         * Removes the last row from the 2D matrix
         *
         * @throws Error if matrix is empty
         */
        void pop()
        {
            if (vec_2D.empty())
                throw std::underflow_error("Empty Error: Matrix has no rows to remove");
            else
                vec_2D.pop_back();
        }

        /**
         * Removes the last element from a specific row
         *
         * @param index Row index to modify (0-based)
         * @throws Error if index is invalid or row is empty
         */
        void pop(size_t index)
        {
            if (index >= vec_2D.size())
                throw std::out_of_range("Index Error: Row index out of range");
            else if (vec_2D[index].empty())
                throw std::underflow_error("Empty Error: Row is already empty");
            else
                vec_2D[index].pop_back();
        }

        /**
         * Checks if the main 2D matrix is empty
         *
         * @return true if vec_2D has no rows, false otherwise
         */
        constexpr bool empty() const noexcept { return vec_2D.empty(); }

        /**
         * Checks if a specific row in the main matrix is empty
         *
         * @param index Row index to check (0-based)
         * @return true if the specified row is empty
         * @throws Error if index is out of bounds
         */
        constexpr bool empty(size_t index) const
        {
            if (index >= vec_2D.size())
                throw std::invalid_argument("Index out of range");
            return vec_2D[index].empty();
        }

        /**
         * Clears the main 2D matrix
         *
         * @post vec_2D is empty
         */
        void clear() noexcept { vec_2D.clear(); }

        /**
         * Clears a specific row in the main 2D matrix
         *
         * @param index Row index to clear (0-based)
         * @throws Error if index is out of bounds
         * @post Specified row vector is empty
         */
        void clear(size_t index)
        {
            if (index >= vec_2D.size())
                throw std::invalid_argument("Index out of range");
            vec_2D[index].clear();
        }

        /**
         * Gets the row count (first dimension) of the main 2D matrix
         *
         * @return Number of rows:
         *         - Fixed size (n) if set, otherwise
         *         - Current row count of vec_2D
         */
        constexpr size_t size() const
        {
            return (n != -1) ? static_cast<size_t>(n) : vec_2D.size();
        }

        /**
         * Gets the column count of a specific row in the main matrix
         *
         * @param index Row index to check (0-based)
         * @return Number of columns:
         *         - Fixed size (m) if set, otherwise
         *         - Current size of specified row
         * @throws Error if index is out of bounds
         */
        constexpr size_t size(size_t index) const
        {
            if (index >= vec_2D.size())
                throw std::out_of_range("Index out of range");
            return (m != -1) ? static_cast<size_t>(m) : vec_2D[index].size();
        }

        /**
         * Calculates the determinant of a square matrix (2x2 or 3x3)
         *
         * Supports both internal matrix (vec_2D) and external matrices.
         * Currently implements:
         *   - 2x2 matrices (using simple diagonal rule)
         *   - 3x3 matrices (using Rule of Sarrus)
         *   - NxN matrices (using Gaussian-Jordan elimination)
         *
         * @param vec Optional external matrix (uses internal matrix if empty)
         * @return The determinant value as long double
         * @throws When:
         *           - Input matrix is empty, OR
         *           - Matrix is not square, OR
         *           - Matrix size is not currently supported (only 2x2 and 3x3)
         *
         * @note For 2x2 matrices: det = ad - bc
         * @note For 3x3 matrices: det = a(ei−fh) − b(di−fg) + c(dh−eg)
         * @see determinant2X2()
         * @see determinant3X3()
         */
        long double determinant(const std::vector<std::vector<T>> &vec = {})
        {
            const auto &target = vec.empty() ? vec_2D : vec;
            if (target.empty())
                throw std::invalid_argument("Empty matrix");
            if (is_numeric_type<T>::value)
            {
                if (square2X2(target))
                    return determinant2X2(target);
                if (square3X3(target))
                    return determinant3X3(target);
                if (squareNXN(target))
                    return determinantNXN(target);
            }
            throw std::runtime_error("Unsupported matrix size or the type of the data not numeric");
        }

        /**
         * @brief Computes the inverse of a 2x2 or 3x3 matrix.
         *
         * If no matrix is provided, it uses the internal vec_2D member.
         * The function automatically selects the appropriate method based on the size:
         * - 2x2 matrices use inverse2X2
         * - 3x3 matrices use inverse3X3
         *
         * @param vec Optional matrix to invert. If empty, vec_2D is used.
         * @return A 2x2 or 3x3 matrix representing the inverse.
         * @throws std::invalid_argument if both vec and vec_2D are empty.
         * @throws std::runtime_error if the matrix is not 2x2 or 3x3 (unsupported size).
         */
        std::vector<std::vector<T>> inverse(const std::vector<std::vector<T>> &vec = {})
        {
            if (vec.empty() && vec_2D.empty())
                throw std::invalid_argument("Empty Error");
            const auto &target = vec.empty() ? vec_2D : vec;
            if (square2X2(target))
                return inverse2X2(target);
            if (square3X3(target))
                return inverse3X3(target);
            throw std::runtime_error("the matrix isn\'t compatible with the function");
        }

        /**
         * Determines if the matrix has fixed dimensions
         *
         * @return true if both row count (n) and column count (m) are fixed, false
         * otherwise
         * @note Fixed dimensions are set through:
         *       - vector_2d(int, int) constructor
         *       - set_size() function
         */
        constexpr bool is_fixed_size() const noexcept { return (n != -1) && (m != -1); }

        /**
         * @brief Returns an iterator to the beginning of the outer vector.
         *
         * Useful for iterating over the first-level elements (each element
         * is itself a std::vector<T>).
         *
         * @return Iterator to the first element of vec_2D.
         */
        auto begin() const noexcept { return vec_2D.begin(); }

        /**
         * @brief Returns an iterator to the end of the outer vector.
         *
         * Marks the past-the-end iterator for the first-level elements.
         * Commonly used with range-based for loops.
         *
         * @return Iterator to the element following the last in vec_2D.
         */
        auto end() const noexcept { return vec_2D.end(); }

        /**
         * @brief Returns an iterator to the beginning of the inner vector at index i.
         *
         * Useful for iterating over elements inside a specific inner vector.
         *
         * @param i Index of the inner vector.
         * @return Iterator to the first element of vec_2D[i].
         */
        auto begin(int i) const noexcept { return vec_2D[i].begin(); }

        /**
         * @brief Returns an iterator to the end of the inner vector at index i.
         *
         * Marks the past-the-end iterator for the specified inner vector.
         *
         * @param i Index of the inner vector.
         * @return Iterator to the element following the last in vec_2D[i].
         */
        auto end(int i) const noexcept { return vec_2D[i].end(); }

        /**
         * @brief Returns the last valid index of the outer vector.
         *
         * Equivalent to vec_2D.size() - 1.
         *
         * @return Index of the last element in vec_2D.
         */
        size_t last_index() const noexcept { return vec_2D.size() - 1; }

        /**
         * @brief Returns the last valid index of the inner vector at index i.
         *
         * Equivalent to vec_2D[i].size() - 1.
         *
         * @param i Index of the inner vector.
         * @return Index of the last element in vec_2D[i].
         */
        size_t last_index(int i) const noexcept { return vec_2D[i].size() - 1; }

        /**
         * @brief Returns the capacity of the outer vector.
         *
         * Capacity is the number of elements the outer vector can hold
         * without reallocation.
         *
         * @return Capacity of vec_2D.
         */
        size_t capacity() const noexcept { return vec_2D.capacity(); }

        /**
         * @brief Returns the capacity of the inner vector at index i.
         *
         * Capacity is the number of elements that the specified inner vector
         * can hold without reallocation.
         *
         * @param i Index of the inner vector.
         * @return Capacity of vec_2D[i].
         */
        size_t capacity(int i) const noexcept { return vec_2D[i].capacity(); }

        /**
         * Prints the main 2D matrix in a formatted way
         *
         * Output format:
         * | a11, a12, a13 |
         * | a21, a22, a23 |
         *
         * @note Uses borders and commas for clear matrix visualization
         */
        void print() const noexcept
        {
            for (size_t i = 0; i < vec_2D.size(); i++)
            {
                std::cout << "| ";
                for (size_t j = 0; j < vec_2D[i].size(); j++)
                {
                    std::cout << vec_2D[i][j];
                    if (j != vec_2D[i].size() - 1)
                        std::cout << ", ";
                }
                std::cout << " |" << std::endl;
            }
        }

        /**
         * Assignment operator for matrix replacement
         *
         * @param vec2d 2D vector to assign to the internal storage
         * @post Replaces current vec_2D with the input vector
         */
        void operator=(const std::vector<std::vector<T>> &vec2d) noexcept { vec_2D = vec2d; }

        /**
         * Assignment operator for vector_2d object
         * @param other The vector_2d object to copy from
         * Initializes the current object with the same internal state as `other`:
         *   - vec_2D: Copy of the 2D vector
         */
        void operator=(const vector_2d<T> &other) noexcept
        {
            vec_2D = other.vec_2D;
            n = other.n;
            m = other.m;
        }

        /**
         * Subscript operator for row access (mutable)
         *
         * @param i Row index (0-based)
         * @return Reference to the requested row vector
         * @warning No bounds checking - use with valid indices
         */
        std::vector<T> &operator[](size_t i) noexcept { return vec_2D[i]; }

        /**
         * Subscript operator for row access (const)
         *
         * @param i Row index (0-based)
         * @return Const reference to the requested row vector
         * @warning No bounds checking - use with valid indices
         */
        const std::vector<T> &operator[](size_t i) const noexcept { return vec_2D[i]; }

        /**
         * Equality operator for matrix comparison
         *
         * @param vec2d Matrix to compare against
         * @return true if:
         *           - Both matrices are empty, OR
         *           - All elements are equal
         *         false otherwise
         */
        bool operator==(const std::vector<std::vector<T>> &vec2d) const noexcept
        {
            if (vec2d.size() != vec_2D.size())
                return false;
            for (size_t i = 0; i < vec_2D.size(); i++)
            {
                if (vec2d[i].size() != vec_2D[i].size())
                    return false;
                for (size_t j = 0; j < vec_2D[i].size(); j++)
                {
                    if (vec_2D[i][j] != vec2d[i][j])
                        return false;
                }
            }
            return true;
        }

        /**
         * Equality operator for matrix comparison
         * @param v2d Matrix to compare against
         * @return true if:
         *           - Both matrices are empty, OR
         *           - All elements are equal
         *         false otherwise
         */
        bool operator==(const vector_2d<T> &v2d) const noexcept { return v2d == vec_2D; }

        /**
         * Scalar addition operator (modifies current matrix)
         *
         * @param element Value to add to all elements
         * @post Adds element to every element in the matrix
         */
        void operator+=(T element) noexcept
        {
            for (auto &row : vec_2D)
            {
                for (auto &elem : row)
                    elem += element;
            }
        }

        /**
         * Matrix addition operator (modifies current matrix)
         *
         * @param vec2d Matrix to add element-wise
         * @post Performs element-wise addition
         * @note Matrices must have identical dimensions
         */
        void operator+=(const std::vector<std::vector<T>> &vec2d)
        {
            if (vec2d.size() != vec_2D.size())
                throw std::invalid_argument("Incompatible matrix dimensions");
            for (size_t i = 0; i < vec_2D.size(); i++)
            {
                if (vec2d[i].size() != vec_2D[i].size())
                    throw std::invalid_argument("Incompatible matrix dimensions");
                for (size_t j = 0; j < vec_2D[i].size(); j++)
                    vec_2D[i][j] += vec2d[i][j];
            }
        }

        /**
         * Matrix addition operator (modifies current matrix)
         *
         * @param v2d Matrix to add element-wise
         * @post Performs element-wise addition
         * @note Matrices must have identical dimensions
         */
        void operator+=(const vector_2d<T> &v2d)
        {
            if (v2d.size() != vec_2D.size())
                throw std::invalid_argument("Incompatible matrix dimensions");
            for (size_t i = 0; i < vec_2D.size(); i++)
            {
                if (v2d.size(i) != vec_2D[i].size())
                    throw std::invalid_argument("Incompatible matrix dimensions");
                for (size_t j = 0; j < vec_2D[i].size(); j++)
                    vec_2D[i][j] += v2d.at(i, j);
            }
        }

        /**
         * Scalar subtraction operator (modifies current matrix)
         *
         * @param element Value to subtract from all elements
         * @post Subtracts element from every element in the matrix
         */
        void operator-=(T element)
        {
            if (!is_numeric_type<T>::value)
                throw std::invalid_argument("Element type is not numeric");
            if (vec_2D.empty())
                return; // No change for empty matrix
            if (element == 0)
                return; // No change for zero subtraction
            for (auto &row : vec_2D)
            {
                for (auto &elem : row)
                    elem -= element;
            }
        }

        /**
         * Matrix subtraction operator (modifies current matrix)
         *
         * @param vec2d Matrix to subtract element-wise
         * @post Performs element-wise subtraction
         * @note Matrices must have identical dimensions
         */
        void operator-=(const std::vector<std::vector<T>> &vec2d)
        {
            if (!is_numeric_type<T>::value)
                throw std::invalid_argument("Element type is not numeric");
            if (vec2d.size() != vec_2D.size())
                throw std::invalid_argument("Incompatible matrix dimensions");
            for (size_t i = 0; i < vec_2D.size(); i++)
            {
                if (vec2d[i].size() != vec_2D[i].size())
                    throw std::invalid_argument("Incompatible matrix dimensions");
                for (size_t j = 0; j < vec_2D[i].size(); j++)
                    vec_2D[i][j] -= vec2d[i][j];
            }
        }

        /**
         * Matrix subtraction operator (modifies current matrix)
         *
         * @param v2d Matrix to subtract element-wise
         * @post Performs element-wise subtraction
         * @note Matrices must have identical dimensions
         */
        void operator-=(const vector_2d<T> &v2d)
        {
            if (v2d.size() != vec_2D.size())
                throw std::invalid_argument("Incompatible matrix dimensions");
            for (size_t i = 0; i < vec_2D.size(); i++)
            {
                if (v2d.size(i) != vec_2D[i].size())
                    throw std::invalid_argument("Incompatible matrix dimensions");
                for (size_t j = 0; j < vec_2D[i].size(); j++)
                    vec_2D[i][j] -= v2d.at(i, j);
            }
        }

        /**
         * @brief Raises all elements of the 2D vector to the given power.
         *
         * This operator overload applies the power operation (std::pow) to
         * every element inside the internal 2D container @c vec_2D.
         *
         * @param element The exponent to which each element is raised.
         *
         * @throws std::invalid_argument If the 2D vector is empty.
         *
         * @note The operation is performed in-place, modifying the current
         *       object. No new vector is created.
         *
         * @example
         * vector_2d<int> mat = {{1, 2}, {3, 4}};
         * mat ^= 2; // Result: {{1, 4}, {9, 16}}
         */
        void operator^=(T element)
        {
            if (vec_2D.empty())
                throw std::invalid_argument("Empty Error");
            for (std::vector<T> &vec : vec_2D)
            {
                for (T &value : vec)
                    value = std::pow(value, element);
            }
        }

        /**
         * Element-wise power operator (modifies current matrix)
         *
         * @param vec2d Exponent matrix
         * @post Raises elements to corresponding powers
         * @note Matrices must have identical dimensions
         */
        void operator^=(const std::vector<std::vector<T>> &vec2d)
        {
            if (vec2d.size() != vec_2D.size())
                throw std::invalid_argument("Incompatible matrix dimensions");
            for (size_t i = 0; i < vec_2D.size(); i++)
            {
                if (vec2d[i].size() != vec_2D[i].size())
                    throw std::invalid_argument("Incompatible matrix dimensions");
                for (size_t j = 0; j < vec_2D[i].size(); j++)
                    vec_2D[i][j] = std::pow(vec_2D[i][j], vec2d[i][j]);
            }
        }

        /**
         * Element-wise power operator (modifies current matrix)
         *
         * @param v2d Exponent matrix
         * @post Raises elements to corresponding powers
         * @note Matrices must have identical dimensions
         */
        void operator^=(const vector_2d<T> &v2d)
        {
            if (v2d.size() != vec_2D.size())
                throw std::invalid_argument("Incompatible matrix dimensions");
            for (size_t i = 0; i < vec_2D.size(); i++)
            {
                if (v2d.size(i) != vec_2D[i].size())
                    throw std::invalid_argument("Incompatible matrix dimensions");
                for (size_t j = 0; j < vec_2D[i].size(); j++)
                    vec_2D[i][j] = std::pow(vec_2D[i][j], v2d.at(i, j));
            }
        }

        /**
         * Scalar multiplication operator (modifies current matrix)
         *
         * @param element Value to multiply all elements by
         * @post Multiplies every element by given scalar
         */
        void operator*=(T element)
        {
            if (vec_2D.empty())
                return; // No change for empty matrix
            for (auto &row : vec_2D)
            {
                for (auto &elem : row)
                    elem *= element;
            }
        }

        /**
         * Scalar division operator (modifies current matrix)
         *
         * @param element Value to divide all elements by
         * @post Divides every element by given scalar
         * @throws invalid_argument if element is zero
         */
        void operator/=(T element)
        {
            if (vec_2D.empty())
                return; // No change for empty matrix
            if (element == 0)
                throw std::invalid_argument("Division by zero");
            for (auto &row : vec_2D)
            {
                for (auto &elem : row)
                    elem /= element;
            }
        }

        /**
         * Default destructor
         *
         * @note Automatically clears all managed resources
         * @warning Does not manually clear members - relies on vector destructors
         */
        ~vector_2d() = default;
    };

    /**
     * @brief Overloads the stream insertion operator to output a 2D vector (vector_2d).
     *
     * This function prints the contents of a 2D vector in a formatted manner.
     * Each row is enclosed within vertical bars ('|'), and elements within a row
     * are separated by commas. Each row is printed on a new line.
     *
     * @tparam U The type of elements stored in the 2D vector.
     * @param os The output stream to which the vector will be written.
     * @param vec2d The 2D vector to output.
     * @return Reference to the output stream after writing the vector.
     */
    template <typename U>
    std::ostream &operator<<(std::ostream &os, const vector_2d<U> &vec2d)
    {
        for (size_t i = 0; i < vec2d.size(); i++)
        {
            os << "| ";
            for (size_t j = 0; j < vec2d[i].size(); j++)
            {
                os << vec2d[i][j];
                if (j != vec2d[i].size() - 1)
                    os << ", ";
            }
            os << " |" << std::endl;
        }
        return os;
    }

    /**
     * A generic 3D vector wrapper that provides access and modification utilities
     * for elements, 2D slices, and full 3D structure.
     *
     * @tparam T Type of the elements stored (int, float, string, etc.)
     */
    template <typename T>
    class vector_3d
    {
    private:
        size_t w = -1, n = -1, m = -1;
        std::vector<std::vector<std::vector<T>>> vec_3D;

    protected:
        /**
         * Flattens a 3D vector into a 2D vector
         *
         * Transformation:
         *   [depth][rows][cols] -> [depth * rows][cols]
         *
         * @param vec Optional external 3D vector (uses internal vec_3D if empty)
         * @post Result stored in member 'flatten' (2D vector)
         * @warning Will skip operation if input is empty
         */
        std::vector<std::vector<T>> flatten_2dvec(const std::vector<std::vector<std::vector<T>>> &vec = {}) const
        {
            const auto &target = vec.empty() ? vec_3D : vec;
            std::vector<std::vector<T>> flatten;
            if (target.empty())
                throw std::runtime_error("The 3D vector is empty");
            for (size_t i = 0; i < target.size(); i++)
            {
                for (size_t j = 0; j < target[i].size(); j++)
                    flatten.push_back(target[i][j]);
            }
            return flatten;
        }

        /**
         * Transposes the first two dimensions of a 3D vector
         *
         * Transformation:
         *   Original: [depth][rows][cols]
         *   Transposed: [rows][depth][cols]
         *
         * @param vec Optional external 3D vector (uses internal vec_3D if empty)
         * @post Result stored in member 'transpose_3D'
         * @warning Requires non-empty input and consistent dimensions
         */
        std::vector<std::vector<std::vector<T>>> transpose(const std::vector<std::vector<std::vector<T>>> &vec = {})
        {
            const auto &target = vec.empty() ? vec_3D : vec;
            std::vector<std::vector<std::vector<T>>> transpose_3D;
            if (target.empty() || target[0].empty())
                throw std::runtime_error("The 3D vector is empty");
            transpose_3D.resize(target[0].size());
            for (size_t i = 0; i < target[0].size(); i++)
            {
                for (size_t j = 0; j < target.size(); j++)
                    transpose_3D[i].push_back(target[j][i]);
            }
            return transpose_3D;
        }

        /**
         * Computes determinants for each 2D matrix in a 3D vector
         *
         * Processes each 2D slice (depth layer) independently
         *
         * @param vec Optional external 3D vector (uses internal vec_3D if empty)
         * @post Results stored in member 'determinant' (1D vector of determinants)
         * @note Uses vector_2d::determinant() for each 2D matrix
         * @warning Only works for 2x2 and 3x3 matrices
         */
        std::vector<long double> determinant_vec(const std::vector<std::vector<std::vector<T>>> &vec = {}) const
        {
            const auto &target = vec.empty() ? vec_3D : vec;
            if (target.empty())
                throw std::runtime_error(
                    "EmptyMatrixError: Cannot calculate determinant of empty 3D vector");
            std::vector<long double> determinant;
            vector_2d<T> vt;
            for (const std::vector<std::vector<T>> &loopvec : target)
                determinant.push_back(vt.determinant(loopvec));
            return determinant;
        }

    public:
        /**
         * @brief Checks if the 3D vector has fixed dimensions.
         *
         * This function returns true if the object has predefined dimensions (n, m, w),
         * and false if any of them is -1 (unknown or dynamic size).
         *
         * @return true if dimensions are fixed, false otherwise.
         */
        constexpr bool is_fixed_size() const noexcept
        {
            if (n == -1 || m == -1 || w == -1)
                return false;
            return true;
        }

        /**
         * @brief Checks if a 3D vector has the specified dimensions N x M x W.
         *
         * If no vector is provided, it checks the internal vec_3D member.
         * Throws std::invalid_argument if both the input vector and vec_3D are empty.
         *
         * @param N Expected size of the first dimension.
         * @param M Expected size of the second dimension.
         * @param W Expected size of the third dimension.
         * @param v Optional external 3D vector to check.
         * @return true if the vector matches the specified dimensions, false otherwise.
         * @throws std::invalid_argument if both v and vec_3D are empty.
         */
        bool is_sizeNXMXW(int N, int M, int W, const std::vector<std::vector<std::vector<T>>> &v = {}) const
        {
            if (v.empty() && vec_3D.empty())
                throw std::invalid_argument("the input vector is all empty");
            if (is_fixed_size())
            {
                if (N == n && M == m && W == w)
                    return true;
                return false;
            }
            auto target = v.empty() ? vec_3D : v;
            if (static_cast<int>(target.size()) == N)
            {
                for (int i = 0; i < N; i++)
                {
                    if (static_cast<int>(target[i].size()) == M)
                    {
                        for (int j = 0; j < M; j++)
                        {
                            if (static_cast<int>(target[i][j].size()) != W)
                                return false;
                        }
                    }
                    else
                        return false;
                }
            }
            else
                return false;
            return true;
        }

        /**
         * @brief Checks if a 3D vector forms a cube of size N x N x N.
         *
         * This is a convenience function that calls is_sizeNXMXW with N for all dimensions.
         *
         * @param N Expected size for all three dimensions.
         * @param v Optional external 3D vector to check.
         * @return true if the vector is a cube of size N x N x N, false otherwise.
         */
        bool is_cudeNXNXN(int N, const std::vector<std::vector<std::vector<T>>> &v = {})
        {
            return is_sizeNXMXW(N, N, N, v);
        }

        /**
         * @brief Checks if a 3D vector is a 3x3x3 cube.
         *
         * @param v Optional external 3D vector to check.
         * @return true if the vector is 3x3x3, false otherwise.
         */
        bool is_cude3X3X3(const std::vector<std::vector<std::vector<T>>> &v = {})
        {
            return is_cudeNXNXN(3, v);
        }

        /**
         * @brief Checks if a 3D vector is a 2x2x2 cube.
         *
         * @param v Optional external 3D vector to check.
         * @return true if the vector is 2x2x2, false otherwise.
         */
        bool is_cude2X2X2(const std::vector<std::vector<std::vector<T>>> &v = {})
        {
            return is_cudeNXNXN(2, v);
        }

        /**
         * @brief Checks if an external 3D vector has the same size as the internal vec_3D.
         *
         * Comparison is done for known cube sizes (2x2x2, 3x3x3) and general dimensions.
         * Throws std::invalid_argument if either vector is empty.
         *
         * @param v External 3D vector to compare against vec_3D.
         * @return true if the vectors have the same size, false otherwise.
         * @throws std::invalid_argument if either v or vec_3D is empty.
         */
        bool is_equal_size(const std::vector<std::vector<std::vector<T>>> &v)
        {
            if (v.empty() || vec_3D.empty())
                throw std::invalid_argument("Empty Error: all input vector is empty");
            if (is_cude2X2X2(v) && is_cude2X2X2())
                return true;
            if (is_cude3X3X3(v) && is_cude3X3X3())
                return true;
            if (is_cudeNXNXN(vec_3D.size(), v) && is_cudeNXNXN(vec_3D.size()))
                return true;
            if (is_sizeNXMXW(vec_3D.size(), vec_3D[0].size(), vec_3D[0][0].size(), v) && is_sizeNXMXW(vec_3D.size(), vec_3D[0].size(), vec_3D[0][0].size()))
                return true;
            return false;
        }

        /**
         * Default constructor - creates an empty 3D vector
         *
         * Initializes vec_3D as an empty 3-dimensional vector
         */
        vector_3d() { vec_3D = {}; } // default constructor

        /**
         * Cubic matrix constructor - creates a cube-shaped 3D vector
         *
         * @param num Size for all three dimensions (w×n×m cube)
         */
        vector_3d(size_t num)
        {
            w = num;
            n = num;
            m = num;
        }

        /**
         * Semi-cubic constructor - creates a 3D vector with equal last two dimensions
         *
         * @param num1 Size of first dimension (depth)
         * @param num2 Size for both second and third dimensions (rows and columns)
         */
        vector_3d(size_t num1, size_t num2)
        {
            w = num1;
            n = num2;
            m = num2;
        }

        /**
         * Rectangular 3D constructor - creates a 3D vector with custom dimensions
         *
         * @param num1 Size of first dimension (depth)
         * @param num2 Size of second dimension (rows)
         * @param num3 Size of third dimension (columns)
         */
        vector_3d(size_t num1, size_t num2, size_t num3)
        {
            w = num1;
            n = num2;
            m = num3;
        }

        /**
         * Initializer list constructor - creates from nested initializer lists
         *
         * @param init Initializer list of 2D vectors to form the 3D structure
         *
         * Example:
         *   vector_3d<int> v = {
         *     {{1,2}, {3,4}},
         *     {{5,6}, {7,8}}
         *   };
         */
        vector_3d(std::initializer_list<std::vector<std::vector<T>>> init) : vec_3D(init)
        {
            size_t wnum, nnum, mnum;
            wnum = static_cast<size_t>(vec_3D.size());
            nnum = wnum > 0 ? static_cast<size_t>(vec_3D[0].size()) : -1;
            mnum =
                (wnum > 0 && nnum > 0) ? static_cast<size_t>(vec_3D[0][0].size()) : -1;
            if (w != -1 && n != -1 && m != -1)
            {
                if (wnum != w || nnum != n || mnum != m)
                {
                    throw std::runtime_error(
                        "Dimension Error: Initializer list dimensions do not match fixed "
                        "size");
                }
            }
        }

        /**
         * Copy constructor from existing 3D vector
         *
         * @param vec3d 3D vector to copy into the new object
         */
        vector_3d(const std::vector<std::vector<std::vector<T>>> &vec3d)
        {
            vec_3D = vec3d;
        }

        /**
         * @brief Copy constructor for the vector_3d class.
         *
         * Creates a new vector_3d object by copying all member variables from another
         * vector_3d instance.
         *
         * @param other The vector_3d object to copy from.
         */
        vector_3d(const vector_3d<T> &other)
        {
            vec_3D = other.vec_3D;
            w = other.w;
            n = other.n;
            m = other.m;
        }

        /**
         * Sets/updates the main 3D vector storage
         *
         * @param vec3d The new 3D vector to store as the main data
         * @note Overwrites any existing 3D vector content
         */
        void set(const std::vector<std::vector<std::vector<T>>> &vec3d) noexcept
        {
            vec_3D = vec3d;
        }

        /**
         * Sets fixed cubic dimensions (w×n×m cube)
         *
         * @param num Size for all three dimensions
         */
        void set(size_t num) noexcept
        {
            w = num;
            n = num;
            m = num;
        }

        /**
         * Sets fixed dimensions with equal last two dimensions
         *
         * @param num1 Size of first dimension (depth)
         * @param num2 Size for both second and third dimensions (rows and columns)
         */
        void set(size_t num1, size_t num2) noexcept
        {
            w = num1;
            n = num2;
            m = num2;
        }

        /**
         * Sets custom fixed dimensions for all three axes
         *
         * @param num1 Size of first dimension (depth)
         * @param num2 Size of second dimension (rows)
         * @param num3 Size of third dimension (columns)
         */
        void set(size_t num1, size_t num2, size_t num3) noexcept
        {
            w = num1;
            n = num2;
            m = num3;
        }

        /**
         * Returns a const reference to the internal 3D vector
         *
         * @return Const reference to vec_3D
         * @warning Reference becomes invalid if matrix is modified
         */
        const std::vector<std::vector<std::vector<T>>> &get() const noexcept { return vec_3D; }

        /**
         * Returns a deep copy of the internal 3D vector
         *
         * @return Copy of vec_3D
         */
        std::vector<std::vector<std::vector<T>>> get_copy() const noexcept { return vec_3D; }

        /**
         * Returns a const reference to a 2D slice within the 3D vector
         *
         * @param index Depth index (0-based)
         * @return Const reference to the 2D matrix at specified depth
         * @throws out_of_range if index is invalid
         */
        const std::vector<std::vector<T>> &get(size_t index) const
        {
            if (index >= vec_3D.size())
                throw std::out_of_range("Depth index out of range");
            return vec_3D[index];
        }

        /**
         * Returns a deep copy of a 2D slice within the 3D vector
         *
         * @param index Depth index (0-based)
         * @return Copy of the 2D matrix at specified depth
         * @throws out_of_range if index is invalid
         */
        std::vector<std::vector<T>> get_copy(size_t index) const
        {
            if (index >= vec_3D.size())
                throw std::out_of_range("Depth index out of range");
            return vec_3D[index];
        }

        /**
         * Returns a const reference to a row vector within a 2D slice
         *
         * @param ind1 Depth index (0-based)
         * @param ind2 Row index (0-based)
         * @return Const reference to the row vector
         * @throws out_of_range if either index is invalid
         */
        const std::vector<T> &get(size_t ind1, size_t ind2) const
        {
            if (ind1 >= vec_3D.size())
                throw std::out_of_range("Depth index out of range");
            if (ind2 >= vec_3D[ind1].size())
                throw std::out_of_range("Row index out of range");
            return vec_3D[ind1][ind2];
        }

        /**
         * Returns a deep copy of a row vector within a 2D slice
         *
         * @param ind1 Depth index (0-based)
         * @param ind2 Row index (0-based)
         * @return Copy of the row vector
         * @throws out_of_range if either index is invalid
         */
        std::vector<T> get_copy(size_t ind1, size_t ind2) const
        {
            if (ind1 >= vec_3D.size())
                throw std::out_of_range("Depth index out of range");
            if (ind2 >= vec_3D[ind1].size())
                throw std::out_of_range("Row index out of range");
            return vec_3D[ind1][ind2];
        }

        /**
         * Accesses an element in the 3D vector
         *
         * @param ind1 Depth index (0-based)
         * @param ind2 Row index (0-based)
         * @param ind3 Column index (0-based)
         * @return The element at [ind1][ind2][ind3]
         * @throws out_of_range if any index is invalid
         */
        T get(size_t ind1, size_t ind2, size_t ind3) const
        {
            if (ind1 >= vec_3D.size())
                throw std::out_of_range("Depth index out of range");
            if (ind2 >= vec_3D[ind1].size())
                throw std::out_of_range("Row index out of range");
            if (ind3 >= vec_3D[ind1][ind2].size())
                throw std::out_of_range("Column index out of range");
            return vec_3D[ind1][ind2][ind3];
        }

        /**
         * @brief Sets the value at the specified indices in the 3D vector.
         *
         * This function assigns the given value to the element located at the position
         * specified by ind1 (depth), ind2 (row), and ind3 (column) in the 3D vector.
         *
         * @param ind1 The index for the first dimension (depth).
         * @param ind2 The index for the second dimension (row).
         * @param ind3 The index for the third dimension (column).
         * @param value The value to set at the specified position.
         *
         * @throws std::out_of_range If any of the indices are out of bounds.
         */
        void at(size_t ind1, size_t ind2, size_t ind3, T value)
        {
            if (ind1 >= vec_3D.size())
                throw std::out_of_range("Depth index out of range");
            if (ind2 >= vec_3D[ind1].size())
                throw std::out_of_range("Row index out of range");
            if (ind3 >= vec_3D[ind1][ind2].size())
                throw std::out_of_range("Column index out of range");
            vec_3D[ind1][ind2][ind3] = value;
        }

        /**
         * @brief Sets the value of a specific 2D slice in the 3D vector.
         *
         * Replaces the vector at the specified depth (ind1) and row (ind2) with the provided value.
         *
         * @param ind1 The index for the depth (first dimension) of the 3D vector.
         * @param ind2 The index for the row (second dimension) within the specified depth.
         * @param value The vector to assign at the specified position.
         *
         * @throws std::out_of_range If ind1 or ind2 is out of the valid range of indices.
         */
        void at(size_t ind1, size_t ind2, std::vector<T> &value)
        {
            if (ind1 >= vec_3D.size())
                throw std::out_of_range("Depth index out of range");
            if (ind2 >= vec_3D[ind1].size())
                throw std::out_of_range("Row index out of range");
            vec_3D[ind1][ind2] = value;
        }

        /**
         * @brief Replaces the 2D vector at the specified depth index in the 3D vector.
         *
         * @param ind1 The index at the first (depth) dimension to access.
         * @param value The 2D vector to assign at the specified depth index.
         * @throws std::out_of_range If the provided index is out of bounds.
         */
        void at(size_t ind1, std::vector<std::vector<T>> &value)
        {
            if (ind1 >= vec_3D.size())
                throw std::out_of_range("Depth index out of range");
            vec_3D[ind1] = value;
        }

        /**
         * @brief Retrieves the element at the specified 3D indices.
         *
         * This function returns the element located at the given depth (ind1), row (ind2),
         * and column (ind3) in the 3D vector. If any of the indices are out of range,
         * it throws a std::out_of_range exception with an appropriate message.
         *
         * @param ind1 The depth index (first dimension).
         * @param ind2 The row index (second dimension).
         * @param ind3 The column index (third dimension).
         * @return The element of type T at the specified indices.
         * @throws std::out_of_range if any index is out of bounds.
         */
        T at(size_t ind1, size_t ind2, size_t ind3) const
        {
            if (ind1 >= vec_3D.size())
                throw std::out_of_range("Depth index out of range");
            if (ind2 >= vec_3D[ind1].size())
                throw std::out_of_range("Row index out of range");
            if (ind3 >= vec_3D[ind1][ind2].size())
                throw std::out_of_range("Column index out of range");
            return vec_3D[ind1][ind2][ind3];
        }

        /**
         * @brief Retrieves a 1D vector from the 3D vector at the specified depth and row indices.
         *
         * @tparam T The type of elements stored in the vector.
         * @param ind1 The depth index (first dimension).
         * @param ind2 The row index (second dimension).
         * @return std::vector<T> The 1D vector at the specified indices.
         * @throws std::out_of_range If either ind1 or ind2 is out of bounds.
         */
        std::vector<T> at(size_t ind1, size_t ind2) const
        {
            if (ind1 >= vec_3D.size())
                throw std::out_of_range("Depth index out of range");
            if (ind2 >= vec_3D[ind1].size())
                throw std::out_of_range("Row index out of range");
            return vec_3D[ind1][ind2];
        }

        /**
         * @brief Returns a 2D vector at the specified depth index from the 3D vector.
         *
         * @param ind1 The depth index to access in the 3D vector.
         * @return std::vector<std::vector<T>> The 2D vector at the specified depth.
         * @throws std::out_of_range If the provided index is out of the 3D vector's range.
         */
        std::vector<std::vector<T>> at(size_t ind1) const
        {
            if (ind1 >= vec_3D.size())
                throw std::out_of_range("Depth index out of range");
            return vec_3D[ind1];
        }

        /**
         * @brief Returns the full transposed 3D vector.
         *
         * This function returns a new 3D vector representing the transpose
         * of the internal data.
         *
         * @return A std::vector<std::vector<std::vector<T>>> containing the transposed data.
         */
        std::vector<std::vector<std::vector<T>>> get_transpose() { return transpose(); }

        /**
         * @brief Returns a specific 2D slice of the transposed 3D vector.
         *
         * The slice corresponds to the layer at the given index in the transposed vector.
         * Throws std::out_of_range if the index is invalid.
         *
         * @param index Index of the depth layer in the transposed 3D vector.
         * @return A std::vector<std::vector<T>> representing the requested 2D slice.
         * @throws std::out_of_range if index < 0 or index >= number of layers.
         */
        std::vector<std::vector<T>> get_transpose(int index) const
        {
            if (index < 0 || index >= static_cast<int>(transpose().size()))
                throw std::out_of_range("Depth index out of range");
            return transpose()[index];
        }

        /**
         * @brief Returns a specific 1D row from the transposed 3D vector.
         *
         * Accesses the row at ind2 from the depth layer ind1.
         * Throws std::out_of_range if any index is invalid.
         *
         * @param ind1 Depth index (first dimension) in the transposed vector.
         * @param ind2 Row index (second dimension) within the specified depth layer.
         * @return A std::vector<T> representing the requested row.
         * @throws std::out_of_range if ind1 or ind2 is out of range.
         */
        std::vector<T> get_transpose(int ind1, int ind2) const
        {
            if (ind1 < 0 || ind1 >= static_cast<int>(transpose().size()))
                throw std::out_of_range("Depth index out of range");
            if (ind2 < 0 || ind2 >= static_cast<int>(transpose()[ind1].size()))
                throw std::out_of_range("Row index out of range");
            return transpose()[ind1][ind2];
        }

        /**
         * @brief Returns a single element from the transposed 3D vector.
         *
         * Accesses the element at position [ind1][ind2][ind3] in the transposed vector.
         * Throws std::out_of_range if any index is invalid.
         *
         * @param ind1 Depth index (first dimension) in the transposed vector.
         * @param ind2 Row index (second dimension) within the specified depth layer.
         * @param ind3 Column index (third dimension) within the specified row.
         * @return The element of type T at the specified position.
         * @throws std::out_of_range if any of ind1, ind2, or ind3 is out of range.
         */
        std::vector<T> get_transpose(int ind1, int ind2, int ind3) const
        {
            if (ind1 < 0 || ind1 >= static_cast<int>(transpose().size()))
                throw std::out_of_range("Depth index out of range");
            if (ind2 < 0 || ind2 >= static_cast<int>(transpose()[ind1].size()))
                throw std::out_of_range("Row index out of range");
            if (ind3 < 0 || ind3 >= static_cast<int>(transpose()[ind1][ind2].size()))
                throw std::out_of_range("Column index out of range");
            return transpose()[ind1][ind2];
        }

        /**
         * Returns a const reference to the flattened 2D representation
         *
         * @return Const reference to the flatten member
         */
        std::vector<std::vector<T>> &get_flatten(std::vector<std::vector<T>> &input)
        {
            input = flatten_2dvec();
            return input;
        }

        /**
         * Returns a deep copy of the flattened 2D representation
         *
         * @return Copy of the flatten member
         */
        std::vector<std::vector<T>> get_copy_flatten() const noexcept { return flatten_2dvec(); }

        /**
         * Returns a const reference to a row in the flattened 2D representation
         *
         * @param index Row index (0-based)
         * @return Const reference to the requested row
         * @throws out_of_range if index is invalid
         */
        const std::vector<T> &get_flatten(size_t index) const
        {
            if (index >= flatten_2dvec().size())
                throw std::out_of_range("Flatten row index out of range");
            return flatten_2dvec()[index];
        }

        /**
         * Returns a deep copy of a row in the flattened 2D representation
         *
         * @param index Row index (0-based)
         * @return Copy of the requested row
         * @throws out_of_range if index is invalid
         */
        std::vector<T> get_copy_flatten(size_t index) const
        {
            if (index >= flatten_2dvec().size())
                throw std::out_of_range("Flatten row index out of range");
            return flatten_2dvec()[index];
        }

        /**
         * Accesses an element in the flattened 2D representation
         *
         * @param ind1 Row index (0-based)
         * @param ind2 Column index (0-based)
         * @return The element at [ind1][ind2] in flatten
         * @throws out_of_range if either index is invalid
         */
        T get_flatten(size_t ind1, size_t ind2) const
        {
            if (ind1 >= flatten_2dvec().size())
                throw std::out_of_range("Flatten row index out of range");
            if (ind2 >= flatten_2dvec()[ind1].size())
                throw std::out_of_range("Flatten column index out of range");
            return flatten_2dvec()[ind1][ind2];
        }

        /**
         * Returns a copy of the determinant vector
         *
         * @return Vector of determinants for each 2D slice
         */
        std::vector<long double> get_determinant_vec(const std::vector<std::vector<std::vector<T>>> &vec = {}) const noexcept { return determinant_vec(vec); }

        /**
         * Accesses a specific determinant value
         *
         * @param index Slice index (0-based)
         * @return Determinant value for the specified 2D slice
         * @throws std::out_of_range if index is invalid
         */
        long double get_determinant(size_t index, const std::vector<std::vector<std::vector<T>>> &vec = {}) const
        {
            const std::vector<long double> &detvec = determinant_vec(vec);
            if (index >= detvec.size())
                throw std::out_of_range("Determinant index out of range");
            return detvec[index];
        }

        /**
         * Appends a 2D matrix to the end of the 3D vector
         *
         * @param vec2d 2D matrix to append
         * @throws Error if fixed depth (w) is reached
         */
        void push(const std::vector<std::vector<T>> &vec2d)
        {
            if (w != -1 && w == vec_3D.size())
                throw std::runtime_error("CapacityError: Cannot exceed fixed depth");
            vec_3D.push_back(vec2d);
        }

        /**
         * Appends a 2D matrix to the end of the 3D vector
         *
         * @param vec2d 2D matrix to append
         * @throws Error if fixed depth (w) is reached
         */
        void push(const vector_2d<T> &vec2d)
        {
            if (w != -1 && w == vec_3D.size())
                throw std::runtime_error("CapacityError: Cannot exceed fixed depth");
            vec_3D.push_back(vec2d.get_2dvec());
        }

        /**
         * Appends a row vector to a specific 2D matrix in the 3D vector
         *
         * @param index Depth index of target matrix (0-based)
         * @param vec Row vector to append
         * @throws Error if:
         *           - Index is invalid, OR
         *           - Fixed row count (n) is reached
         *          - Row exceeds fixed column count (m)
         */
        void push(size_t index, const std::vector<T> &vec)
        {
            if (index >= vec_3D.size())
                throw std::out_of_range("Depth index out of range");
            if (n != -1 && n == vec_3D[index].size())
                throw std::runtime_error("CapacityError: Cannot exceed fixed row count");
            if (vec.size() > m && m != -1)
                throw std::runtime_error("CapacityError: Row exceeds fixed column count");
            vec_3D[index].push_back(vec);
        }

        /**
         * Appends an element to a specific row in the 3D vector
         *
         * @param ind1 Depth index (0-based)
         * @param ind2 Row index (0-based)
         * @param ele Element to append
         * @throws Error if:
         *           - Either index is invalid, OR
         *           - Fixed column count (m) is reached
         */
        void push(size_t ind1, size_t ind2, T ele)
        {
            if (ind1 >= vec_3D.size())
                throw std::out_of_range("Depth index out of range");
            if (ind2 >= vec_3D[ind1].size())
                throw std::out_of_range("Row index out of range");
            if (m != -1 && m == vec_3D[ind1][ind2].size())
                throw std::runtime_error("Capacity Error: Cannot exceed fixed column count");
            vec_3D[ind1][ind2].push_back(ele);
        }

        /**
         * Removes the last 2D matrix from the 3D vector
         *
         * @throws Error if 3D vector is empty
         */
        void pop()
        {
            if (vec_3D.empty())
                throw std::out_of_range("3D vector is empty");
            vec_3D.pop_back();
        }

        /**
         * Removes the last row from a specific 2D matrix
         *
         * @param index Depth index (0-based)
         * @throws Error if:
         *           - Index is invalid, OR
         *           - Target matrix is empty
         */
        void pop(size_t index)
        {
            if (index >= vec_3D.size())
                throw std::out_of_range("Depth index out of range");
            if (vec_3D[index].empty())
                throw std::out_of_range("Matrix at index is empty");
            vec_3D[index].pop_back();
        }

        /**
         * Removes the last element from a specific row
         *
         * @param ind1 Depth index (0-based)
         * @param ind2 Row index (0-based)
         * @throws Error if:
         *           - Either index is invalid, OR
         *           - Target row is empty
         */
        void pop(size_t ind1, size_t ind2)
        {
            if (ind1 >= vec_3D.size())
                throw std::out_of_range("Depth index out of range");
            if (ind2 >= vec_3D[ind1].size())
                throw std::out_of_range("Row index out of range");
            if (vec_3D[ind1][ind2].empty())
                throw std::out_of_range("Row vector is empty");
            vec_3D[ind1][ind2].pop_back();
        }

        /**
         * Gets the depth dimension (first dimension) of the 3D vector
         *
         * @return Number of depth layers (w dimension)
         */
        size_t size() const noexcept { return vec_3D.size(); }

        /**
         * Gets the row count of a specific depth layer in the 3D vector
         *
         * @param index Depth index (0-based)
         * @return Number of rows (n dimension) at specified depth
         * @throws out_of_range if depth index is invalid
         */
        size_t size(size_t index) const
        {
            if (index >= vec_3D.size())
                throw std::out_of_range("Depth index out of range");
            return vec_3D[index].size();
        }

        /**
         * Gets the column count of a specific row in the 3D vector
         *
         * @param ind1 Depth index (0-based)
         * @param ind2 Row index (0-based)
         * @return Number of columns (m dimension) at specified position
         * @throws out_of_range if either index is invalid
         */
        size_t size(size_t ind1, size_t ind2) const
        {
            if (ind1 >= vec_3D.size())
                throw std::out_of_range("Depth index out of range");
            if (ind2 >= vec_3D[ind1].size())
                throw std::out_of_range("Row index out of range");
            return vec_3D[ind1][ind2].size();
        }

        /**
         * Clears the entire 3D vector while preserving other structures
         *
         * @post vec_3D is empty
         * @note Does not affect transpose_3D or flatten
         */
        void clear() noexcept { vec_3D.clear(); }

        /**
         * Clears a specific depth layer in the 3D vector
         *
         * @param index Depth index to clear (0-based)
         * @throws out_of_range if index is invalid
         * @post Specified depth layer is empty
         */
        void clear(size_t index)
        {
            if (index >= vec_3D.size())
                throw std::out_of_range("Depth index out of range");
            vec_3D[index].clear();
        }

        /**
         * Clears a specific row within a depth layer
         *
         * @param ind1 Depth index (0-based)
         * @param ind2 Row index (0-based)
         * @throws out_of_range if either index is invalid
         * @post Specified row vector is empty
         */
        void clear(size_t ind1, size_t ind2)
        {
            if (ind1 >= vec_3D.size())
                throw std::out_of_range("Depth index out of range");
            if (ind2 >= vec_3D[ind1].size())
                throw std::out_of_range("Row index out of range");
            vec_3D[ind1][ind2].clear();
        }

        /**
         * Checks if the entire 3D vector is empty
         *
         * @return true if vec_3D has no depth layers, false otherwise
         */
        bool empty() const noexcept { return vec_3D.empty(); }

        /**
         * Checks if a specific depth layer is empty
         *
         * @param index Depth index to check (0-based)
         * @return true if the specified depth layer has no rows
         * @throws out_of_range if index is invalid
         */
        bool empty(size_t index) const
        {
            if (index >= vec_3D.size())
                throw std::out_of_range("Depth index out of range");
            return vec_3D[index].empty();
        }

        /**
         * Checks if a specific row within a depth layer is empty
         *
         * @param ind1 Depth index (0-based)
         * @param ind2 Row index (0-based)
         * @return true if the specified row has no elements
         * @throws std::out_of_range if either index is invalid
         */
        bool empty(size_t ind1, size_t ind2) const
        {
            if (ind1 >= vec_3D.size())
                throw std::out_of_range("Depth index out of range");
            if (ind2 >= vec_3D[ind1].size())
                throw std::out_of_range("Row index out of range");
            return vec_3D[ind1][ind2].empty();
        }

        /**
         * @brief Returns an iterator to the beginning of the outer 3D vector.
         *
         * Useful for iterating over the first-level elements (each element is a 2D vector).
         *
         * @return Iterator to the first element of vec_3D.
         */
        auto begin() const noexcept { return vec_3D.begin(); }

        /**
         * @brief Returns an iterator to the beginning of the 2D vector at index i.
         *
         * Allows iterating over a specific 2D layer inside vec_3D.
         *
         * @param i Index of the 2D vector in the 3D vector.
         * @return Iterator to the first element of vec_3D[i].
         */
        auto begin(int i) const noexcept { return vec_3D[i].begin(); }

        /**
         * @brief Returns an iterator to the beginning of the 1D vector at position (i, j).
         *
         * Allows iterating over a specific row inside the 2D layer vec_3D[i].
         *
         * @param i Index of the 2D vector in vec_3D.
         * @param j Index of the row inside vec_3D[i].
         * @return Iterator to the first element of vec_3D[i][j].
         */
        auto begin(int i, int j) { return vec_3D[i][j].begin(); }

        /**
         * @brief Returns an iterator to the end of the outer 3D vector.
         *
         * Marks the past-the-end iterator for the first-level elements.
         *
         * @return Iterator past the last element of vec_3D.
         */
        auto end() const noexcept { return vec_3D.end(); }

        /**
         * @brief Returns an iterator to the end of the 2D vector at index i.
         *
         * Marks the past-the-end iterator for the specified 2D layer.
         *
         * @param i Index of the 2D vector in vec_3D.
         * @return Iterator past the last element of vec_3D[i].
         */
        auto end(int i) const noexcept { return vec_3D[i].end(); }

        /**
         * @brief Returns an iterator to the end of the 1D vector at position (i, j).
         *
         * Marks the past-the-end iterator for the specified row.
         *
         * @param i Index of the 2D vector in vec_3D.
         * @param j Index of the row inside vec_3D[i].
         * @return Iterator past the last element of vec_3D[i][j].
         */
        auto end(int i, int j) const noexcept { return vec_3D[i][j].end(); }

        /**
         * @brief Returns the last valid index of the outer 3D vector.
         *
         * Equivalent to vec_3D.size() - 1.
         *
         * @return Index of the last element in vec_3D.
         */
        size_t last_index() const noexcept { return vec_3D.size() - 1; }

        /**
         * @brief Returns the last valid index of the 2D vector at index i.
         *
         * Equivalent to vec_3D[i].size() - 1.
         *
         * @param i Index of the 2D vector.
         * @return Index of the last row in vec_3D[i].
         */
        size_t last_index(int i) const noexcept { return vec_3D[i].size() - 1; }

        /**
         * @brief Returns the last valid index of the 1D vector at position (i, j).
         *
         * Equivalent to vec_3D[i][j].size() - 1.
         *
         * @param i Index of the 2D vector in vec_3D.
         * @param j Index of the row inside vec_3D[i].
         * @return Index of the last element in vec_3D[i][j].
         */
        size_t last_index(int i, int j) const noexcept { return vec_3D[i][j].size() - 1; }

        /**
         * @brief Returns the capacity of the outer 3D vector.
         *
         * Capacity is the number of elements that can be stored without reallocation.
         *
         * @return Capacity of vec_3D.
         */
        size_t capacity() const noexcept { return vec_3D.capacity(); }

        /**
         * @brief Returns the capacity of the 2D vector at index i.
         *
         * Capacity is the number of rows that can be stored in vec_3D[i] without reallocation.
         *
         * @param i Index of the 2D vector.
         * @return Capacity of vec_3D[i].
         */
        size_t capacity(int i) const noexcept { return vec_3D[i].capacity(); }

        /**
         * @brief Returns the capacity of the 1D vector at position (i, j).
         *
         * Capacity is the number of elements that can be stored in vec_3D[i][j] without reallocation.
         *
         * @param i Index of the 2D vector in vec_3D.
         * @param j Index of the row inside vec_3D[i].
         * @return Capacity of vec_3D[i][j].
         */
        size_t capacity(int i, int j) const noexcept { return vec_3D[i][j].capacity(); }

        /**
         * @brief Copy assignment operator for vector_3d.
         *
         * Assigns the contents of another vector_3d object to this object,
         * performing a deep copy of the internal 3D vector and dimension sizes.
         *
         * @param other The vector_3d object to copy from.
         */
        void operator=(const vector_3d<T> &other)
        {
            if (this != &other)
            {
                vec_3D = other.vec_3D;
                w = other.w;
                n = other.n;
                m = other.m;
            }
        }

        /**
         * @brief Assignment operator for assigning a 3D vector using an initializer list.
         *
         * Allows the object to be assigned a new value using an initializer list of 3D vectors.
         *
         * @param init An initializer list containing std::vector<std::vector<T>> elements to assign to the internal 3D vector.
         */
        void operator=(std::initializer_list<std::vector<std::vector<T>>> init) noexcept { vec_3D = init; }

        /**
         * @brief Adds a scalar element to all elements of the 3D vector.
         *
         * @param element The scalar value to add.
         * @throws std::invalid_argument if vec_3D is empty.
         */
        void operator+=(const T element)
        {
            if (vec_3D.empty())
                throw std::invalid_argument("Empty Error: the 3d vector is empty");
            for (std::vector<std::vector<T>> &vec_2d : vec_3D)
            {
                for (std::vector<T> &vec : vec_2d)
                {
                    for (T &ele : vec)
                    {
                        ele += element;
                    }
                }
            }
        }

        /**
         * @brief Adds a 3D vector element-wise to the internal 3D vector.
         *
         * Both vectors must have the same dimensions.
         *
         * @param elements The 3D vector to add.
         * @throws std::invalid_argument if either vector is empty or sizes are incompatible.
         */
        void operator+=(const std::vector<std::vector<std::vector<T>>> &elements)
        {
            if (elements.empty() || vec_3D.empty())
                throw std::invalid_argument("Empty Error: one of the vector or both is empty");
            if (!is_equal_size(elements))
                throw std::invalid_argument("Size Error: the input vector size isn\'t compatible with the object vector size");
            for (size_t i = 0; i < elements.size(); i++)
            {
                for (size_t j = 0; j < elements[0].size(); j++)
                {
                    for (size_t k = 0; k < elements[0][0].size(); k++)
                    {
                        vec_3D[i][j][k] += elements[i][j][k];
                    }
                }
            }
        }

        /**
         * @brief Subtracts a scalar element from all elements of the 3D vector.
         *
         * @param element The scalar value to subtract.
         * @throws std::invalid_argument if vec_3D is empty.
         */
        void operator-=(const T element)
        {
            if (vec_3D.empty())
                throw std::invalid_argument("Empty Error: the 3d vector is empty");
            for (std::vector<std::vector<T>> &vec_2d : vec_3D)
            {
                for (std::vector<T> &vec : vec_2d)
                {
                    for (T &ele : vec)
                    {
                        ele -= element;
                    }
                }
            }
        }

        /**
         * @brief Subtracts a 3D vector element-wise from the internal 3D vector.
         *
         * Both vectors must have the same dimensions.
         *
         * @param elements The 3D vector to subtract.
         * @throws std::invalid_argument if either vector is empty or sizes are incompatible.
         */
        void operator-=(const std::vector<std::vector<std::vector<T>>> &elements)
        {
            if (elements.empty() || vec_3D.empty())
                throw std::invalid_argument("Empty Error: one of the vector or both is empty");
            if (!is_equal_size(elements))
                throw std::invalid_argument("Size Error: the input vector size isn\'t compatible with the object vector size");
            for (size_t i = 0; i < elements.size(); i++)
            {
                for (size_t j = 0; j < elements[0].size(); j++)
                {
                    for (size_t k = 0; k < elements[0][0].size(); k++)
                    {
                        vec_3D[i][j][k] -= elements[i][j][k];
                    }
                }
            }
        }

        /**
         * @brief Multiplies all elements of the 3D vector by a scalar.
         *
         * @param element The scalar multiplier.
         * @throws std::invalid_argument if vec_3D is empty.
         */
        void operator*=(const T element)
        {
            if (vec_3D.empty())
                throw std::invalid_argument("Empty Error: the 3d vector is empty");
            for (std::vector<std::vector<T>> &vec_2d : vec_3D)
            {
                for (std::vector<T> &vec : vec_2d)
                {
                    for (T &ele : vec)
                    {
                        ele *= element;
                    }
                }
            }
        }

        /**
         * @brief Multiplies the 3D vector element-wise by another 3D vector.
         *
         * Both vectors must have the same dimensions.
         *
         * @param elements The 3D vector to multiply with.
         * @throws std::invalid_argument if either vector is empty or sizes are incompatible.
         */
        void operator*=(const std::vector<std::vector<std::vector<T>>> &elements)
        {
            if (elements.empty() || vec_3D.empty())
                throw std::invalid_argument("Empty Error: one of the vector or both is empty");
            if (!is_equal_size(elements))
                throw std::invalid_argument("Size Error: the input vector size isn\'t compatible with the object vector size");
            for (size_t i = 0; i < elements.size(); i++)
            {
                for (size_t j = 0; j < elements[0].size(); j++)
                {
                    for (size_t k = 0; k < elements[0][0].size(); k++)
                    {
                        vec_3D[i][j][k] *= elements[i][j][k];
                    }
                }
            }
        }

        /**
         * @brief Divides all elements of the 3D vector by a scalar.
         *
         * @param element The scalar divisor.
         * @throws std::invalid_argument if vec_3D is empty or element is zero.
         */
        void operator/=(const T element)
        {
            if (vec_3D.empty())
                throw std::invalid_argument("Empty Error: the 3d vector is empty");
            if (element == 0)
                throw std::invalid_argument("dividing on zero is not allowed");
            for (std::vector<std::vector<T>> &vec_2d : vec_3D)
            {
                for (std::vector<T> &vec : vec_2d)
                {
                    for (T &ele : vec)
                    {
                        ele /= element;
                    }
                }
            }
        }

        /**
         * @brief Divides the 3D vector element-wise by another 3D vector.
         *
         * Elements of the divisor vector must be non-zero; if zero, division defaults to 1.
         *
         * @param elements The 3D vector divisor.
         * @throws std::invalid_argument if either vector is empty or sizes are incompatible.
         */
        void operator/=(const std::vector<std::vector<std::vector<T>>> &elements)
        {
            if (elements.empty() || vec_3D.empty())
                throw std::invalid_argument("Empty Error: one of the vector or both is empty");
            if (!is_equal_size(elements))
                throw std::invalid_argument("Size Error: the input vector size isn\'t compatible with the object vector size");
            for (size_t i = 0; i < elements.size(); i++)
            {
                for (size_t j = 0; j < elements[0].size(); j++)
                {
                    for (size_t k = 0; k < elements[0][0].size(); k++)
                    {
                        if (elements[i][j][k] != 0)
                            vec_3D[i][j][k] /= elements[i][j][k];
                        else
                            vec_3D[i][j][k] /= 1;
                    }
                }
            }
        }

        /**
         * @brief Raises all elements of the 3D vector to the given power.
         *
         * @param element The exponent to raise each element to.
         * @throws std::invalid_argument if vec_3D is empty or element is zero.
         */
        void operator^=(const T element)
        {
            if (vec_3D.empty())
                throw std::invalid_argument("Empty Error: the 3d vector is empty");
            if (element == 0)
                throw std::invalid_argument("dividing on zero is not allowed");
            for (std::vector<std::vector<T>> &vec_2d : vec_3D)
            {
                for (std::vector<T> &vec : vec_2d)
                {
                    for (T &ele : vec)
                    {
                        ele = std::pow(ele, element);
                    }
                }
            }
        }

        /**
         * Subscript operator for mutable depth layer access
         *
         * @param i Depth index (0-based)
         * @return Reference to the 2D matrix at specified depth
         * @warning No bounds checking - use with valid indices
         */
        std::vector<std::vector<T>> &operator[](size_t i) noexcept { return vec_3D[i]; }

        /**
         * Subscript operator for const depth layer access
         *
         * @param i Depth index (0-based)
         * @return Const reference to the 2D matrix at specified depth
         * @warning No bounds checking - use with valid indices
         */
        const std::vector<std::vector<T>> &operator[](size_t i) const noexcept { return vec_3D[i]; }

        /**
         * Assignment operator for 3D vector replacement
         *
         * @param vec3d 3D vector to assign to the internal storage
         * @post Replaces current vec_3D with the input vector
         */
        void operator=(const std::vector<std::vector<std::vector<T>>> &vec3d) noexcept { vec_3D = vec3d; }

        /**
         * Equality operator for 3D vector comparison
         *
         * @param vec3d 3D vector to compare against
         * @return true if:
         *           - Both vectors are empty, OR
         *           - All depth layers have identical:
         *               - Row counts
         *               - Column counts
         *               - Element values
         *         false otherwise
         * @note Uses same_vec() for 2D matrix comparison
         */
        bool operator==(const std::vector<std::vector<std::vector<T>>> &vec3d) const noexcept
        {
            if (vec3d.empty() && vec_3D.empty())
                return true;
            if (vec3d.empty())
                return false;
            if (vec_3D.empty())
                return false;
            if (vec_3D.size() != vec3d.size())
                return false;
            for (size_t i = 0; i < vec3d.size(); i++)
            {
                if (vec3d[i].size() != vec_3D[i].size())
                    return false;
                for (size_t j = 0; j < vec3d[i].size(); j++)
                {
                    if (!same_v(vec3d[i][j], vec_3D[i][j]))
                        return false;
                }
            }
            return true;
        }

        /**
         * Default destructor
         *
         * @note Automatically clears all managed resources
         * @warning Does not manually clear members - relies on vector destructors
         */
        ~vector_3d() = default;
    };

};
#endif // OPENUDT___UDT_VECTOR_MULTIDIMENSIONALVECTOR_HPP