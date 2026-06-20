#include <functional>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <string>
#include "metaCore/adva/function.hpp"

#pragma once
#ifndef OPENUDT___CORE___VECTOR_MULTIDIMENSIONAL_VECTOR_3D_HPP
#define OPENUDT___CORE___VECTOR_MULTIDIMENSIONAL_VECTOR_3D_HPP

namespace udt
{
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
        std::vector<std::vector<T>> get_copy_flatten() const { return flatten_2dvec(); }

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
        std::vector<long double> get_determinant_vec(const std::vector<std::vector<std::vector<T>>> &vec = {}) const { return determinant_vec(vec); }

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
}

#endif // OPENUDT___CORE___VECTOR_MULTIDIMENSIONAL_VECTOR_3D_HPP