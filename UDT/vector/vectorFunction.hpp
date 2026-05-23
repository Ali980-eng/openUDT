/**
 * @file vectorFunction.hpp
 * @brief A collection of utility functions for working with vectors in C++.
 * This header defines various functions to manipulate vectors, including reversing, generating Fibonacci sequences, comparing vectors, extracting subvectors, and erasing rows/columns from 2D vectors. The functions are designed to be generic and work with vectors of any type.
 * @namespace udt
 * @note All functions throw exceptions for invalid input, such as empty vectors or out-of-range indices. The Fibonacci sequence function also checks for potential overflow when calculating large Fibonacci numbers.
 * @date 2025/9/25
 * @author Ali Lafi
 */

#include <type_traits>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>

#pragma once
#ifndef OPENUDT___UDT_VECTOR_VECTORFUNCTION_HPP
#define OPENUDT___UDT_VECTOR_VECTORFUNCTION_HPP

namespace udt
{
    /**
     * Reverses a vector of any type.
     * @param dynvec: The input vector to reverse.
     * @return A new vector containing the elements in reverse order.
     * @throws VectorEmptyException if the input vector is empty.
     */
    template <typename T>
    std::vector<T> reverse_v(const std::vector<T> &dynvec)
    {
        if (dynvec.empty())
            throw std::runtime_error("Empty Error");
        std::vector<T> result;
        for (int i = static_cast<int>(dynvec.size()) - 1; i >= 0; i--)
            result.push_back(dynvec[i]);
        return result;
    }

    /**
     * reverses a 2D vector (vector of vectors) of any type.
     * @param dynvec: The input 2D vector to reverse.
     * @throw runtime_error if the input vector is empty.
     * @return A new 2D vector containing the elements in reverse order.
     */
    template <typename T>
    std::vector<std::vector<T>> reverse_v(const std::vector<std::vector<T>> &dynvec)
    {
        if (dynvec.empty())
            throw std::runtime_error("Empty Error");
        std::vector<std::vector<T>> result;
        for (int i = static_cast<int>(dynvec.size()) - 1; i >= 0; i--)
            result.push_back(reverse_v(dynvec[i]));
        return result;
    }

    /**
     * reverses a 3D vector (vector of vector of vectors) of any type.
     * @param dynvec: The input 3D vector to reverse.
     * @throw runtime_error if the input vector is empty.
     * @return A new 3D vector containing the elements in reverse order.
     */
    template <typename T>
    std::vector<std::vector<std::vector<T>>> reverse_v(const std::vector<std::vector<std::vector<T>>> &dynvec)
    {
        if (dynvec.empty())
            throw std::runtime_error("Empty Error");
        std::vector<std::vector<std::vector<T>>> result;
        for (int i = static_cast<int>(dynvec.size()) - 1; i >= 0; i--)
            result.push_back(reverse_v(dynvec[i]));
        return result;
    }

    /**
     * Generates the Fibonacci sequence from F(0) to F(n).
     * @param terms The index n of the last Fibonacci number to include (inclusive).
     * @return A vector containing F(0) to F(n), with (terms + 1) elements.
     */
    std::vector<long long> FibonacciSequence(short terms)
    {
        if (terms <= 0)
            return {};
        if (terms == 1)
            return {0};
        if (terms == 2)
            return {0, 1};
        std::vector<long long> Fibonacci = {0, 1};
        for (short i = 2; i <= terms; i++)
        {
            if (Fibonacci[i - 1] > LLONG_MAX - Fibonacci[i - 2])
                throw std::overflow_error("Fibonacci value exceeds long long capacity");
            Fibonacci.push_back(Fibonacci[i - 1] + Fibonacci[i - 2]);
        }
        return Fibonacci;
    }

    /**
     * Returns the index of the last element in the vector.
     * @param vec The input vector.
     * @return Index of the last element (vec.size() - 1), or -1 if the vector is
     * empty.
     */
    template <typename T>
    size_t v_end(const std::vector<T> &vec)
    {
        if (vec.empty())
            throw std::runtime_error("Empty Error");
        return vec.size() - 1;
    }

    /**
     * Compares two vectors element by element to check if they are identical in
     * content and order.
     * @param vec1 The first vector.
     * @param vec2 The second vector.
     * @return true if the vectors have the same size and elements in the same
     * order; false otherwise.
     */
    template <typename T>
    bool same_v(const std::vector<T> &vec1, const std::vector<T> &vec2)
    {
        if (vec1.empty() && vec2.empty())
            return true;
        if (vec1.size() != vec2.size())
            return false;
        for (size_t i = 0; i < vec2.size(); i++)
        {
            if (vec2[i] != vec1[i])
                return false;
        }
        return true;
    }

    /**
     * @brief Returns a subvector from the given vector within the specified range.
     *
     * This function extracts a subvector from the input vector `v`, starting from index `start` and ending at index `end` (inclusive).
     *
     * @tparam T The type of elements in the vector.
     * @param v The input vector from which to extract the subvector.
     * @param start The starting index of the subvector (inclusive).
     * @param end The ending index of the subvector (inclusive).
     * @return std::vector<T> The resulting subvector containing elements from `start` to `end`.
     *
     * @throws std::invalid_argument If the input vector is empty.
     * @throws std::out_of_range If `start` is less than 0 or `end` is greater than the last valid index of the vector.
     */
    template <typename T>
    std::vector<T> sub_v(const std::vector<T> &v, int start, int end)
    {
        if (v.empty())
            throw std::invalid_argument("Empty Error: the vector is empty no sub vector can be generate");
        if (start < 0 || end >= static_cast<int>(v.size()))
            throw std::out_of_range("the start or end is out of range of vector");
        std::vector<T> result_v;
        for (int i = start; i <= end; i++)
            result_v.push_back(v[i]);
        return result_v;
    }

    /**
     * @brief Extracts a submatrix from a 2D vector based on start and end indices for each dimension.
     *
     * This function generates a subvector (submatrix) from a given 2D vector `v`, using the provided
     * `start_v` and `end_v` vectors to specify the start and end indices for each dimension.
     * It recursively applies the subvector extraction for each dimension.
     *
     * @tparam T The type of the elements in the 2D vector.
     * @param v The input 2D vector from which to extract the submatrix.
     * @param start_v A vector of start indices for each dimension.
     * @param end_v A vector of end indices for each dimension (exclusive).
     * @return A submatrix of `v` defined by the specified ranges.
     *
     * @throws std::invalid_argument If the input vector `v` is empty.
     * @throws std::out_of_range If the start or end indices are out of range, or if the size of `start_v`
     *         does not match the dimensions of the result.
     */
    template <typename T>
    std::vector<std::vector<T>> sub_v(const std::vector<std::vector<T>> &v, const std::vector<int> &start_v, const std::vector<int> &end_v)
    {
        if (v.empty())
            throw std::invalid_argument("Empty Error: the vector is empty no sub vector can be generate");
        if (start_v[0] < 0 || end_v[0] > static_cast<int>(v.size()))
            throw std::out_of_range("the start or end is out of range of vector");
        auto result = sub_v<std::vector<T>>(v, start_v[0], end_v[0]);
        if (result.size() + 1 != start_v.size())
            throw std::out_of_range("the start vector can\'n fit the size of the result");
        for (size_t i = 0; i < result.size(); i++)
            sub_v<T>(result[i], start_v[i + 1], end_v[i + 1]);
        return result;
    }

    /**
     * @brief Removes a row from a 2D vector at the specified index.
     *
     * @tparam T The type of the elements in the 2D vector.
     * @param v The input 2D vector from which a row will be removed.
     * @param index The zero-based index of the row to remove.
     * @return A new 2D vector with the specified row removed.
     * @throws std::out_of_range If the index is out of bounds (less than 0 or greater than or equal to the vector size).
     */
    template <typename T>
    std::vector<std::vector<T>> erase_row(const std::vector<std::vector<T>> &v, int index)
    {
        if (index > static_cast<int>(v.size()) || index < 0)
            throw std::out_of_range("the vector erase index is begger than the vector size or is equal or less than zero");
        std::vector<std::vector<T>> result;
        for (size_t i = 0; i < v.size(); i++)
        {
            if (static_cast<int>(i) == index)
                continue;
            result.push_back(v[i]);
        }
        return result;
    }

    /**
     * @brief Removes a specified column from a 2D vector.
     *
     * This function creates and returns a new 2D vector with the column at the given index removed from each row.
     * If a row does not have enough columns (i.e., its size is less than or equal to the specified index), that row is skipped.
     *
     * @tparam T The type of the elements in the 2D vector.
     * @param v The input 2D vector from which a column will be removed.
     * @param index The zero-based index of the column to remove.
     * @return std::vector<std::vector<T>> A new 2D vector with the specified column removed from each row.
     *
     * @throws std::invalid_argument If the input vector is empty.
     * @throws std::out_of_range If the index is negative.
     *
     * @note If no columns are erased due to incorrect indexing, a message is printed to std::cout.
     */
    template <typename T>
    std::vector<std::vector<T>> erase_column(const std::vector<std::vector<T>> &v, int index)
    {
        if (v.empty())
            throw std::invalid_argument("Empty Error");
        if (index < 0)
            throw std::out_of_range("the index is less then or equal to zero");
        std::vector<std::vector<T>> result_v;
        int erase_count = 0;
        for (size_t i = 0; i < v.size(); i++)
        {
            if (static_cast<int>(v[i].size()) < index)
                continue;
            result_v.push_back({});
            for (size_t j = 0; j < v[i].size(); j++)
            {
                if (static_cast<int>(j) != index)
                    result_v[i].push_back(v[i][j]);
            }
            erase_count++;
        }
        if (erase_count == 0)
            std::cout << "nothing was erase form the vector due to incorrect indexing" << std::endl;
        return result_v;
    }

    /**
     * @brief Removes the specified row and column from a 2D vector.
     *
     * This function creates a new 2D vector by removing the row at index `i` and the column at index `j`
     * from the input vector `v`. The original vector is not modified.
     *
     * @tparam T The type of the elements in the 2D vector.
     * @param v The input 2D vector from which a row and a column will be removed.
     * @param i The index of the row to remove.
     * @param j The index of the column to remove.
     * @return A new 2D vector with the specified row and column removed.
     *
     * @throws std::invalid_argument If the input vector is empty.
     * @throws std::out_of_range If the row index `i` is out of range.
     *
     * @note This function depends on the existence of `erase_row` and `erase_column` helper functions.
     */
    template <typename T>
    std::vector<std::vector<T>> erase_row_column(const std::vector<std::vector<T>> &v, int i, int j)
    {
        if (v.empty())
            throw std::invalid_argument("Empty Error");
        if (i < 0 || i > static_cast<int>(v.size()))
            throw std::out_of_range("the indexing is out of rang vector passed to the function");
        std::vector<std::vector<T>> result_v = erase_row<T>(v, i);
        return erase_column<T>(result_v, j);
    }

    /**
     * @brief Casts a vector of one type to a vector of another type using static_cast.
     * This function takes a vector of type T2 and returns a new vector of type T1, where each element is cast from T2 to T1 using static_cast.
     * @param input The input vector of type T2 to be cast.
     * @return A new vector of type T1 containing the casted elements from the input vector.
     * @tparam T1 The target type to which the elements will be cast.
     * @param T2 The source type of the elements in the input vector.
     * @note This function assumes that the static_cast from T2 to T1 is valid for all elements in the input vector. If the cast is not valid, it may result in undefined behavior.
     * @throws std::bad_cast If the static_cast fails for any element in the input vector (not checked at compile time).
     * @see std::vector, static_cast
     * @example
     * std::vector<int> intVec = {1, 2, 3};
     * std::vector<double> doubleVec = vector_cast<double>(intVec); // doubleVec will contain {1.0, 2.0, 3.0}
     * std::vector<std::vector<int>> intVec2D = {{1, 2}, {3, 4}};
     * std::vector<std::vector<double>> doubleVec2D = vector_cast<double>(intVec2D); // doubleVec2D will contain {{1.0, 2.0}, {3.0, 4.0}}
     */
    template <typename T1, typename T2>
    std::vector<T1> vector_cast(const std::vector<T2> &input) noexcept
    {
        std::vector<T1> result;
        for (size_t i = 0; i < input.size(); i++)
            result.push_back(static_cast<T1>(input[i]));
        return result;
    }

    /**
     * @brief Casts a 2D vector of one type to a 2D vector of another type using static_cast.
     * This function takes a 2D vector of type T2 and returns a new 2D vector of type T1, where each element is cast from T2 to T1 using static_cast.
     * @param input The input 2D vector of type T2 to be cast.
     * @return A new 2D vector of type T1 containing the casted elements from the input 2D vector.
     * @tparam T1 The target type to which the elements will be cast.
     * @param T2 The source type of the elements in the input 2D vector.
     * @note This function assumes that the static_cast from T2 to T1 is valid for all elements in the input 2D vector. If the cast is not valid, it may result in undefined behavior.
     * @throws std::bad_cast If the static_cast fails for any element in the input 2D vector (not checked at compile time).
     * @see std::vector, static_cast
     * @example
     * std::vector<std::vector<int>> intVec2D = {{1, 2}, {3, 4}};
     * std::vector<std::vector<double>> doubleVec2D = vector_cast<double>(intVec2D); // doubleVec2D will contain {{1.0, 2.0}, {3.0, 4.0}}
     * std::vector<std::vector<std::vector<int>>> intVec3D = {{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}};
     * std::vector<std::vector<std::vector<double>>> doubleVec3D = vector_cast<double>(intVec3D); // doubleVec3D will contain {{{1.0, 2.0}, {3.0, 4.0}}, {{5.0, 6.0}, {7.0, 8.0}}}
     */
    template <typename T1, typename T2>
    std::vector<std::vector<T1>> vector_cast(const std::vector<std::vector<T2>> &input) noexcept
    {
        std::vector<std::vector<T1>> result;
        for (size_t i = 0; i < input.size(); i++)
            result.push_back(vector_cast<T1, T2>(input[i]));
        return result;
    }

    /**
     * @brief Casts a 3D vector of one type to a 3D vector of another type using static_cast.
     * This function takes a 3D vector of type T2 and returns a new 3D vector of type T1, where each element is cast from T2 to T1 using static_cast.
     * @param input The input 3D vector of type T2 to be cast.
     * @return A new 3D vector of type T1 containing the casted elements from the input 3D vector.
     * @tparam T1 The target type to which the elements will be cast.
     * @param T2 The source type of the elements in the input 3D vector.
     * @note This function assumes that the static_cast from T2 to T1 is valid for all elements in the input 3D vector. If the cast is not valid, it may result in undefined behavior.
     * @throws std::bad_cast If the static_cast fails for any element in the input 3D vector (not checked at compile time).
     * @see std::vector, static_cast
     * @example
     * std::vector<std::vector<std::vector<int>>> intVec3D = {{{
     * 1, 2}, {3, 4}}, {{5, 6}, {7, 8}}};
     * std::vector<std::vector<std::vector<double>>> doubleVec3D = vector_cast<double>(intVec3D); // doubleVec3D will contain {{{1.0, 2.0}, {3.0, 4.0}}, {{5.0, 6.0}, {7.0, 8.0}}}
     */
    template <typename T1, typename T2>
    std::vector<std::vector<std::vector<T1>>> vector_cast(const std::vector<std::vector<std::vector<T2>>> &input) noexcept
    {
        std::vector<std::vector<std::vector<T1>>> result;
        for (size_t i = 0; i < input.size(); i++)
            result.push_back(vector_cast<T1, T2>(input[i]));
        return result;
    }

    /**
     * @brief Finds the index of the first occurrence of an element in a vector within a specified range.
     * This function searches for the element `e` in the vector `v` starting from index `start` and ending at index `end` (exclusive). If the element is found, its index is returned; otherwise, a default value (size_t()) is returned.
     * @param v The vector to search through.
     * @param e The element to find in the vector.
     * @param end The index at which to stop the search (exclusive). If set to 0, the search will go until the end of the vector.
     * @param start The index at which to start the search (inclusive). Default is 0.
     * @return The index of the first occurrence of the element `e` in the vector `v` within the specified range, or size_t() if the element is not found.
     * @tparam T The type of elements in the vector.
     * @note If the vector is empty, the function will return size_t() immediately. The function does not perform bounds checking on the `start` and `end` parameters, so it is the caller's responsibility to ensure they are within valid ranges.
     */
    template <typename T>
    size_t where(const std::vector<T> &v, const T &e,
                 size_t end = 0, size_t start = 0) noexcept
    {
        if (v.empty())
            return size_t();
        if (end == 0)
            end = v.length();
        for (size_t i = start; i < end; i++)
        {
            if (v[i] == e)
                return i;
        }
        return size_t();
    }

    /**
     * @brief Checks if an element exists in a vector within a specified range.
     * This function searches for the element `e` in the vector `v` starting from index `start` and ending at index `end` (exclusive). It returns true if the element is found within the specified range, and false otherwise.
     * @param v The vector to search through.
     * @param e The element to check for existence in the vector.
     * @param end The index at which to stop the search (exclusive). If set to 0, the search will go until the end of the vector.
     * @param start The index at which to start the search (inclusive). Default is 0.
     * @return true if the element `e` exists in the vector `v` within the specified range, false otherwise.
     * @tparam T The type of elements in the vector.
     * @note If the vector is empty, the function will return false immediately. The function does not perform bounds checking on the `start` and `end` parameters, so it is the caller's responsibility to ensure they are within valid ranges.
     */
    template <typename T>
    bool exist(const std::vector<T> &v, const T &e,
               size_t end = 0, size_t start = 0) noexcept
    {
        if (end == 0)
            end = v.length();
        for (size_t i = start; i < end; i++)
        {
            if (v[i] == e)
                return true;
        }
        return false;
    }
}
#endif // OPENUDT___UDT_VECTOR_VECTORFUNCTION_HPP