#include <stdexcept>
#include <cmath>
#include <iostream>
#include "meta/adva/function.hpp"
#include "cfrost/structure.h"

#pragma once
#ifndef OPENUDT___CORE___PAIR_PAIR__V_HPP
#define OPENUDT___CORE___PAIR_PAIR__V_HPP

namespace udt
{

    /**
     * A Pair-vector container that stores two vectors and their reversed versions.
     * Useful for comparing, printing, summing, and swapping two vectors together.
     *
     * @tparam T1, and T2 Type of elements stored in the vectors.
     */
    template <typename T1, typename T2>
    class pair__v
    {
    private:
        vec<T1> vec1;
        vec<T2> vec2;

    public:
        /**
         * Default constructor
         */
        pair__v()
        {
            vec1 = {};
            vec2 = {};
        }

        /**
         * Parameterized constructor
         * @param v1 First vector
         * @param v2 Second vector
         */
        pair__v(const vec<T1> &v1, const vec<T2> &v2)
        {
            vec1 = v1;
            vec2 = v2;
        }

        /**
         * Parameterized constructor using initializer lists
         * @param list1 Initializer list for the first vector
         * @param list2 Initializer list for the second vector
         */
        pair__v(std::initializer_list<T1> list1, std::initializer_list<T2> list2) noexcept
        {
            vec1 = list1;
            vec2 = list2;
        }

        /**
         * Copy constructor
         * @param other Another pair_v object to copy from
         */
        template <typename T>
        pair__v(const pair_v<T> &other)
        {
            for (T element : other.vec1)
                vec1.push_back(static_cast<T1>(element));
            for (T element : other.vec2)
                vec2.push_back(static_cast<T2>(element));
        }

        /**
         * Copy constructor
         * @param other Another pair_v object to copy from
         */
        pair__v(const pair__v<T1, T2> &other)
        {
            vec1 = other.vec1;
            vec2 = other.vec2;
        }

        /**
         * Checks if both vectors are empty
         * @return true if both vec1 and vec2 are empty, false otherwise
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        bool empty() const noexcept { return vec1.empty() && vec2.empty(); }

        /**
         * Checks if the first vector is empty
         * @return true if vec1 is empty, false otherwise
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        bool empty_v1() const noexcept { return vec1.empty(); }

        /**
         * Checks if the second vector is empty
         * @return true if vec2 is empty, false otherwise
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        bool empty_v2() const noexcept { return vec2.empty(); }

        /**
         * Sets the values of both vectors and their reversed versions
         * @param v1 First vector
         * @param v2 Second vector
         */
        void set(const vec<T1> &v1, const vec<T2> &v2) noexcept
        {
            vec1 = v1;
            vec2 = v2;
        }

        /**
         * Sets the first vector
         * @param v1 First vector
         */
        void set_v1(const vec<T1> &v1) noexcept { vec1 = v1; }

        /**
         * Sets the second vector
         * @param v2 Second vector
         */
        void set_v2(const vec<T2> &v2) noexcept { vec2 = v2; }

        /**
         * Gets the first vector
         * @return A const reference to the first vector
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        const vec<T1> &get_vec1() const noexcept { return vec1; }

        /**
         * Gets a copy of the first vector
         * @return A copy of the first vector
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        vec<T1> get_copy_vec1() const noexcept { return vec1; }

        /**
         * Gets the second vector
         * @return A const reference to the second vector
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        const vec<T2> &get_vec2() const noexcept { return vec2; }

        /**
         * Gets a copy of the second vector
         * @return A copy of the second vector
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        vec<T2> get_copy_vec2() const noexcept { return vec2; }

        /**
         * Multiplies all elements of the first vector by a given number
         * @param num The number to multiply with
         * @return The result of the multiplication
         */
        long double Mult_v1(double num = 1) const
        {
            if (vec1.empty())
                throw std::runtime_error("empty vector can not do this operation");
            if (!num)
                return 0;
            long double result = num;
            for (const double &LNum : vec1)
                result *= LNum;
            return result;
        }

        /**
         * Multiplies all elements of the second vector by a given number
         * @param num The number to multiply with
         * @return The result of the multiplication
         */
        long double Mult_v2(double num = 1) const
        {
            if (vec2.empty())
                throw std::runtime_error("empty vector can not do this operation");
            if (!num)
                return 0;
            long double result = num;
            for (const double &LNum : vec2)
                result *= LNum;
            return result;
        }

        /**
         * Divides all elements of the first vector by a given number
         * @param num The number to divide with
         * @return The result of the division
         */
        long double Divi_v1(double num = 1) const
        {
            if (vec1.empty())
                throw std::runtime_error("empty vector can not do this operation");
            if (!num)
                return 0;
            long double result = num;
            for (const double &LNum : vec1)
                result /= LNum;
            return result;
        }

        /**
         * Divides all elements of the second vector by a given number
         * @param num The number to divide with
         * @return The result of the division
         */
        long double Divi_v2(double num = 1) const
        {
            if (vec2.empty())
                throw std::runtime_error("empty vector can not do this operation");
            if (!num)
                return 0;
            long double result = num;
            for (const double &LNum : vec2)
                result /= LNum;
            return result;
        }

        /**
         * Calculates the sum of all elements in the first vector
         * @param num Initial value to add to the sum (default is 0.0)
         * @return The total sum of elements in vec1
         * @throws Error if vec1 is empty
         */
        long double sum_v1(double num = 0.0) const
        {
            if (vec1.empty())
                throw std::runtime_error("empty vector can not do this operation");
            long double sum = num; // Initialize properly
            for (const double &LNum : vec1)
                sum += LNum;
            return sum;
        }

        /**
         * Calculates the sum of all elements in the second vector
         * @param num Initial value to add to the sum (default is 0.0
         * @return The total sum of elements in vec2
         * @throws Error if vec2 is empty
         */
        long double sum_v2(double num = 0.0) const
        {
            if (vec2.empty())
                throw std::runtime_error("empty vector can not do this operation");
            long double sum = num; // Initialize properly
            for (const double &LNum : vec2)
                sum += LNum;
            return sum;
        }

        /**
         * @brief Calculates the average of all elements in the first vector
         * @return The average value of elements in vec1
         */
        long double average_v1() { return sum_v1() / vec1.size(); }

        /**
         * @brief Calculates the average of all elements in the second vector
         * @return The average value of elements in vec2
         */
        long double average_v2() { return sum_v2() / vec2.size(); }

        /**
         * Returns the size of the first vector
         * @return The size of vec1
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        size_t size_v1() const noexcept { return vec1.size(); }

        /**
         * Returns the size of the second vector
         * @return The size of vec2
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        size_t size_v2() const noexcept { return vec2.size(); }

        /**
         * Accesses an element in the first vector by index
         * @param index Index of the element to access (0-based)
         * @return The element at the specified index in vec1
         * @throws out_of_range if index is invalid
         */
        T1 at_v1(size_t index) const
        {
            if (index >= vec1.size())
                throw std::out_of_range("Index is out of range.");
            return vec1[index];
        }

        /**
         * Accesses an element in the second vector by index
         * @param index Index of the element to access (0-based)
         * @return The element at the specified index in vec2
         * @throws out_of_range if index is invalid
         */
        T2 at_v2(size_t index) const
        {
            if (index >= vec2.size())
                throw std::out_of_range("Index is out of range.");
            return vec2[index];
        }

        /**
         * Clears all vectors versions
         * @post All vectors are empty
         * @note This function is noexcept, meaning it does not throw exceptions.
         * @warning Does not free memory, just clears the vectors.
         */
        void clear_all() noexcept
        {
            vec1.clear();
            vec2.clear();
        }

        /**
         * Clears the first vector
         * @post vec1 is empty
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        void clear_v1() noexcept { vec1.clear(); }

        /**
         * Clears the second vector
         * @post vec2 is empty
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        void clear_v2() noexcept { vec2.clear(); }

        /**
         * Swaps the contents of the first and second vectors
         * @post vec1 and vec2 are swapped
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        void swap_vecs() noexcept
        {
            vec<T1> temp1 = vec1;
            vec<T2> temp2 = vec2;
            vec1.clear();
            vec2.clear();
            for (size_t i = 0; i < temp1.size(); i++)
                vec2.push_back(static_cast<T2>(temp1[i]));
            for (size_t i = 0; i < temp2.size(); i++)
                vec1.push_back(static_cast<T1>(temp2[i]));
        }

        /**
         * @brief Overloaded stream insertion operator for printing a pair__v object.
         *
         * This function allows objects of type pair__v<T1, T2> to be sent directly to an
         * output stream (such as std::cout). It prints the contents of both vectors
         * (vec1 and vec2) in a formatted manner.
         *
         * @tparam T1 Type of elements stored in the first vector (vec1).
         * @tparam T2 Type of elements stored in the second vector (vec2).
         *
         * @param os Reference to the output stream where the pair__v object will be printed.
         * @param pair Constant reference to the pair__v object to be output.
         *
         * @return A reference to the modified output stream (os), enabling chained output operations.
         */
        friend std::ostream &operator<<(std::ostream &os, const pair__v<T1, T2> &pair)
        {
            os << "vec1: ";
            for (const auto &elem : pair.vec1)
                os << elem << " ";
            os << "\nvec2: ";
            for (const auto &elem : pair.vec2)
                os << elem << " ";
            return os;
        }

        /**
         * @brief Assignment operator for assigning a vec<T1> to vec1.
         *
         * Replaces the contents of the internal vec1 member with the elements from the provided vector.
         * This operation is noexcept and does not affect other members of the class.
         *
         * @param input The vec<T1> whose contents will be assigned to vec1.
         */
        void operator=(const vec<T1> &input) noexcept
        {
            vec1 = vec;
        }

        /**
         * @brief Assignment operator for assigning a vec<T2> to vec2.
         *
         * Replaces the contents of the internal vec2 member with the elements from the provided vector.
         * This operation is noexcept and does not affect other members of the class.
         *
         * @param input The vec<T2> whose contents will be assigned to vec2.
         */
        void operator=(const vec<T2> &input) noexcept
        {
            vec2 = vec;
        }

        /**
         * Equality operator for pair_v
         * @param input Pair-vector to compare
         * @return true if either vec1 is equal to vec, false otherwise
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        bool operator==(const vec<T1> &input) const noexcept
        {
            return same_vec(vec, vec1);
        }

        /**
         * Equality operator for pair_v
         * @param input Pair-vector to compare
         * @return true if either vec2 is equal to vec, false otherwise
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        bool operator==(const vec<T2> &input) const noexcept
        {
            return same_vec(vec, vec2);
        }

        /**
         * Addition assignment operator for pair_v
         * @param input Pair-vector to add
         * @post Adds the contents of vec to the first vector
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        void operator+=(const vec<T1> &input) noexcept
        {
            if (input.empty() || vec1.empty())
                return;
            if (vec1.empty())
            {
                for (size_t i = 0; i < input.size(); i++)
                    vec2.push_back(vec[i]);
            }
            else
            {
                for (size_t i = 0; i < input.size(); i++)
                    vec1.push_back(vec[i]);
            }
        }

        /**
         * Addition assignment operator for pair_v
         * @param input Pair-vector to add
         * @post Adds the contents of vec to the second vector
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        void operator+=(const vec<T2> &input) noexcept
        {
            if (input.empty() || vec2.empty())
                return;
            if (vec2.empty())
            {
                for (size_t i = 0; i < input.size(); i++)
                    vec1.push_back(vec[i]);
            }
            else
            {
                for (size_t i = 0; i < input.size(); i++)
                    vec2.push_back(vec[i]);
            }
        }

        /**
         * Adds an element to the first vector
         * @param element Element to add
         * @post Adds the element to the first vector
         */
        void operator+(T1 element)
        {
            if (vec1.empty())
                return;
            auto temp1 = vec1;
            vec1.clear();
            if (temp1.empty())
                throw std::invalid_argument("Empty Error: operator can not add on empty vector");
            for (size_t i = 0; i < temp1.size(); i++)
                vec1.push_back(temp1[i] + element);
        }

        /**
         * Adds an element to the second vector
         * @param element Element to add
         * @post Adds the element to the second vector
         */
        void operator+(T2 element)
        {
            if (vec2.empty())
                return;
            auto temp2 = vec2;
            vec2.clear();
            if (temp2.empty())
                throw std::invalid_argument("Empty Error: operator can not add on empty vector");
            for (size_t i = 0; i < temp2.size(); i++)
                vec2.push_back(temp2[i] + element);
        }

        /**
         * Adds a vector to the first vector
         * @param input Vector to add
         * @post Adds the contents of vec to the first vector
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        void operator+(const vec<T1> &input) noexcept
        {
            if (input.empty() || vec1.empty())
                return;
            auto temp1 = input;
            input.clear();
            if (temp1.size() == input.size())
            {
                for (size_t i = 0; i < input.size(); i++)
                    vec1.push_back(temp1[i] + vec[i]);
            }
            else if (temp1.size() > input.size())
            {
                for (size_t i = 0; i < input.size(); i++)
                    vec1.push_back(temp1[i] + vec[i]);
                for (size_t j = input.size(); j < temp1.size(); j++)
                    vec1.push_back(temp1[j]);
            }
            else
            {
                for (size_t i = 0; i < temp1.size(); i++)
                    vec1.push_back(temp1[i] + vec[i]);
                for (size_t j = temp1.size(); j < input.size(); j++)
                    vec1.push_back(vec[j]);
            }
        }

        /**
         * Adds a vector to the second vector
         * @param input Vector to add
         * @post Adds the contents of vec to the second vector
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        void operator+(const vec<T2> &input) noexcept
        {
            if (input.empty() || vec2.empty())
                return;
            auto temp2 = vec2;
            vec2.clear();
            if (temp2.size() == input.size())
            {
                for (size_t i = 0; i < input.size(); i++)
                    vec2.push_back(temp2[i] + vec[i]);
            }
            else if (temp2.size() > input.size())
            {
                for (size_t i = 0; i < input.size(); i++)
                    vec2.push_back(temp2[i] + vec[i]);
                for (size_t j = input.size(); j < temp2.size(); j++)
                    vec2.push_back(temp2[j]);
            }
            else
            {
                for (size_t i = 0; i < temp2.size(); i++)
                    vec2.push_back(temp2[i] + vec[i]);
                for (size_t j = temp2.size(); j < input.size(); j++)
                    vec2.push_back(vec[j]);
            }
        }

        /**
         * Subtraction operator for pair_v
         * @param input Pair-vector to subtract
         * @post Subtracts the contents of vec from the first vector
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        void operator-(T1 element) noexcept
        {
            if (vec1.empty())
                return;
            auto temp1 = vec1;
            vec1.clear();
            for (size_t i = 0; i < temp1.size(); i++)
                vec1.push_back(temp1[i] - element);
        }

        /**
         * Subtraction operator for pair_v
         * @param input Pair-vector to subtract
         * @post Subtracts the contents of vec from the second vector
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        void operator-(T2 element) noexcept
        {
            if (vec2.empty())
                return;
            auto temp2 = vec2;
            vec2.clear();
            for (size_t i = 0; i < temp2.size(); i++)
                vec2.push_back(temp2[i] - element);
        }

        /**
         * Subtracts a vector from the first vector
         * @param input Vector to subtract
         * @post Subtracts the contents of vec from the first vector
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        void operator-(const vec<T1> &input) noexcept
        {
            if (input.empty() || vec1.empty())
                return;
            auto temp1 = vec1;
            vec1.clear();
            if (temp1.size() == input.size())
            {
                for (size_t i = 0; i < input.size(); i++)
                    vec1.push_back(temp1[i] - vec[i]);
            }
            else if (temp1.size() > input.size())
            {
                for (size_t i = 0; i < input.size(); i++)
                    vec1.push_back(temp1[i] - vec[i]);
                for (size_t j = input.size(); j < temp1.size(); j++)
                    vec1.push_back(temp1[j]);
            }
            else
            {
                for (size_t i = 0; i < temp1.size(); i++)
                    vec1.push_back(temp1[i] - vec[i]);
                for (size_t j = temp1.size(); j < input.size(); j++)
                    vec1.push_back(vec[j]);
            }
        }

        /**
         * Subtracts a vector from the second vector
         * @param input Vector to subtract
         * @post Subtracts the contents of vec from the second vector
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        void operator-(const vec<T2> &input) noexcept
        {
            if (input.empty() || vec2.empty())
                return;
            auto temp2 = vec2;
            vec2.clear();
            if (temp2.size() == input.size())
            {
                for (size_t i = 0; i < input.size(); i++)
                    vec2.push_back(temp2[i] - vec[i]);
            }
            else if (temp2.size() > input.size())
            {
                for (size_t i = 0; i < input.size(); i++)
                    vec2.push_back(temp2[i] - vec[i]);
                for (size_t j = input.size(); j < temp2.size(); j++)
                    vec2.push_back(temp2[j]);
            }
            else
            {
                for (size_t i = 0; i < temp2.size(); i++)
                    vec2.push_back(temp2[i] - vec[i]);
                for (size_t j = temp2.size(); j < input.size(); j++)
                    vec2.push_back(vec[j]);
            }
        }

        /**
         * Multiplication operator for pair_v
         * @param element Element to multiply with
         * @post Multiplies the contents of vec1 with the element
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        void operator*(T1 element) noexcept
        {
            if (vec1.empty())
                return;
            auto temp1 = vec1;
            vec1.clear();
            for (size_t i = 0; i < temp1.size(); i++)
                vec1.push_back(temp1[i] * element);
        }

        /**
         * Multiplication operator for pair_v
         * @param element Element to multiply with
         * @post Multiplies the contents of vec2 with the element
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        void operator*(T2 element) noexcept
        {
            if (vec2.empty())
                return;
            auto temp2 = vec2;
            vec2.clear();
            for (size_t i = 0; i < temp2.size(); i++)
                vec2.push_back(temp2[i] * element);
        }

        /**
         * Divides the contents of vec1 by a given element
         * @param element Element to divide with
         * @post Divides the contents of vec1 by the element
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        void operator/(T1 element) noexcept
        {
            if (vec1.empty() && vec2.empty())
                return;
            auto temp1 = vec1;
            vec1.clear();
            for (size_t i = 0; i < temp1.size(); i++)
                vec1.push_back(temp1[i] / element);
        }

        /**
         * Divides the contents of vec2 by a given element
         * @param element Element to divide with
         * @post Divides the contents of vec2 by the element
         * @note This function is noexcept, meaning it does not throw exceptions.
         */
        void operator/(T2 element) noexcept
        {
            if (vec2.empty())
                return;
            auto temp2 = vec2;
            vec2.clear();
            for (size_t i = 0; i < temp2.size(); i++)
                vec2.push_back(temp2[i] / element);
        }

        /**
         * Destructor for `pair__v`
         */
        ~pair__v() = default;
    };
}
#endif // OPENUDT___CORE___PAIR_PAIR__V_HPP