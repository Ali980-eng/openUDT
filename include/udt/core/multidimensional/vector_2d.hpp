#include <functional>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <string>
#include "meta/adva/function.hpp"

#pragma once
#ifndef OPENUDT___CORE___VECTOR_MULTIDIMENSIONAL_VECTOR_2D_HPP
#define OPENUDT___CORE___VECTOR_MULTIDIMENSIONAL_VECTOR_2D_HPP

namespace udt
{

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
        void set_size(int num)
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
        void set_size(size_t Nnum, size_t Mnum)
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
            auto temp = transpose(v2d);
            return temp[index];
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
}

#endif // OPENUDT___CORE___VECTOR_MULTIDIMENSIONAL_VECTOR_2D_HPP