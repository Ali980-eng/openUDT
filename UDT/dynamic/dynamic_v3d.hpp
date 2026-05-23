#include "dynamic_f.hpp"
#include <functional>
#include <vector>
#include <ostream>

#pragma once
#ifndef OPENUDT___UDT_DYNAMIC__DYANMIC_V3D__HPP
#define OPENUDT___UDT_DYNAMIC__DYANMIC_V3D__HPP

namespace udt
{
    /**
     * @class dynamic_v3d
     * @brief 3D vector container for heterogeneous dynamic type elements.
     *
     * @details A 3D tensor wrapper around std::vector<std::vector<std::vector<dynamic>>>
     * providing dynamic type storage in a 3D grid format. Elements can be of mixed types
     * as each element is a `dynamic` type. Supports both fixed-size and dynamic-size tensors.
     *
     * Features:
     * - 3D heterogeneous type storage with dynamic elements
     * - Optional fixed-size mode for capacity-constrained tensors
     * - Support for cubic and rectangular tensors
     * - Layers, rows, and columns access patterns
     * - Flexible construction from initializer lists and vectors
     *
     * Storage Model:
     * - std::vector<std::vector<std::vector<dynamic>>> data: underlying 3D storage
     * - size_t n: number of layers/depth (or -1 if dynamic)
     * - size_t m: number of rows (or -1 if dynamic)
     * - size_t w: number of columns/width (or -1 if dynamic)
     *
     * Dimensions:
     * - First dimension (n): number of 2D matrices (layers)
     * - Second dimension (m): number of rows per matrix
     * - Third dimension (w): number of columns per row
     *
     * Size Modes:
     * | Mode | n | m | w | Behavior |
     * |------|-----|-----|-----|----------|
     * | Dynamic | -1 | -1 | -1 | Fully dynamic dimensions |
     * | Fixed Cubic | N | N | N | Fixed N×N×N tensor |
     * | Fixed Rectangular | N | M | W | Fixed N×M×W tensor |
     *
     * @note Each element maintains its own type information via the `dynamic` type.
     * @note Fixed-size mode prevents resizing once established.
     * @note Not thread-safe. External synchronization required for concurrent access.
     *
     * @see dynamic - Individual dynamic type holder
     * @see dynamic_v - 1D vector variant
     * @see dynamic_v2d - 2D vector variant
     */
    class dynamic_v3d
    {
    private:
        /// @brief Number of layers/depth (or -1 if dynamic)
        size_t n = 0;
        /// @brief Number of rows per matrix (or -1 if dynamic)
        size_t m = 0;
        /// @brief Number of columns per row (or -1 if dynamic)
        size_t w = 0;
        /// @brief Underlying 3D array storage for dynamic elements
        std::vector<std::vector<std::vector<dynamic_f>>> data;

    public:
        /**
         * @brief Default constructor - creates empty 3D dynamic vector.
         *
         * Initializes a dynamic_v3d with no elements and dynamic dimensions.
         *
         * @post n = -1, m = -1, w = -1, data.empty() = true
         */
        dynamic_v3d() = default;

        /**
         * @brief Constructs cubic fixed-size 3D vector.
         *
         * Creates a dynamic_v3d with cubic fixed dimensions (size × size × size).
         * All elements are value-initialized to default dynamic values.
         *
         * @param size The dimension for all three axes of the cube
         *
         * @post n = size, m = size, w = size
         */
        dynamic_v3d(size_t size) noexcept : n(size), m(size), w(size) {}

        /**
         * @brief Constructs rectangular fixed-size 3D vector.
         *
         * Creates a dynamic_v3d with fixed dimensions for all three axes.
         * All elements are value-initialized to default dynamic values.
         *
         * @param N Number of layers (depth)
         * @param M Number of rows per matrix
         * @param W Number of columns per row
         *
         * @post n = N, m = M, w = W
         */
        dynamic_v3d(size_t N, size_t M, size_t W) noexcept : n(N), m(M), w(W) {}

        /**
         * @brief Constructs fixed-size 3D vector with provided data.
         *
         * Creates a dynamic_v3d with specified dimensions and initializes it
         * with the provided 3D vector data.
         *
         * @param N Number of layers (depth)
         * @param M Number of rows per matrix
         * @param W Number of columns per row
         * @param vec The 3D vector data to initialize with
         *
         * @post n = N, m = M, w = W, data contains vec
         */
        dynamic_v3d(int N, int M, int W, const std::vector<std::vector<std::vector<dynamic_f>>> &vec) noexcept : n(N), m(M), w(W), data(vec) {}

        /**
         * @brief Constructs from a 3D vector with dynamic dimensions.
         *
         * Creates a dynamic_v3d initialized from a 3D vector without fixed size constraints.
         * Dimensions are inferred from the vector structure.
         *
         * @param vec The 3D vector data to initialize with
         *
         * @post n = -1, m = -1, w = -1, data contains vec
         */
        dynamic_v3d(const std::vector<std::vector<std::vector<dynamic_f>>> &vec) noexcept : data(vec) {}

        /**
         * @brief Constructs from initializer list with dimension validation.
         *
         * Creates a dynamic_v3d from an initializer list of 2D matrices. If n, m, and w
         * are already set, validates that dimensions match.
         *
         * @param ini Initializer list of 2D matrices
         *
         * @throws std::length_error if n is fixed but doesn't match layer count
         * @throws std::invalid_argument if matrices have inconsistent row/column counts
         */
        dynamic_v3d(const std::initializer_list<std::vector<std::vector<dynamic_f>>> &ini) : data(ini)
        {
            if (n != static_cast<size_t>(-1) && m != static_cast<size_t>(-1) && w != static_cast<size_t>(-1))
            {
                if (data.size() != n)
                    throw std::length_error("the array is fixed size and can not be resized");
                for (const auto &mat : data)
                {
                    if (mat.size() != m)
                        throw std::invalid_argument("All matrices must have the same number of rows");
                    for (const auto &row : mat)
                    {
                        if (row.size() != w)
                            throw std::invalid_argument("All rows must have the same number of columns");
                    }
                }
            }
        }

        /**
         * @brief Constructs rectangular fixed-size 3D vector with initializer list.
         *
         * Creates a dynamic_v3d with specified fixed dimensions initialized
         * from an initializer list of matrices.
         *
         * @param N Number of layers (depth)
         * @param M Number of rows per matrix
         * @param W Number of columns per row
         * @param vec The initializer list for 3D array data
         *
         * @post n = N, m = M, w = W, data initialized from vec
         */
        dynamic_v3d(int N, int M, int W, const std::initializer_list<std::vector<std::vector<dynamic_f>>> &vec) noexcept : n(N), m(M), w(W), data(vec) {}

        /**
         * @brief Constructs cubic fixed-size 3D vector with initializer list.
         *
         * Creates a dynamic_v3d with cubic fixed dimensions (s × s × s) initialized
         * from an initializer list.
         *
         * @param s The size for all three dimensions
         * @param ini The initializer list for 3D array data
         *
         * @post n = s, m = s, w = s, data initialized from ini
         */
        dynamic_v3d(int s, const std::initializer_list<std::vector<std::vector<dynamic_f>>> &ini) noexcept : n(s), m(s), w(s), data(ini) {}

        /**
         * @brief Convert cubic 3D vector to fixed-size mode or reset to new size.
         *
         * Converts from dynamic to fixed-size mode or resizes if already fixed.
         *
         * @param new_s The size for all three dimensions
         *
         * @post n = m = w = new_s, data resized accordingly
         *
         * @throws std::length_error if tensor is already in fixed-size mode
         * @throws std::invalid_argument if new_s < 0
         */
        void set(size_t new_s)
        {
            if (is_fixed())
                throw std::length_error("the array is fixed size and can not be resized");
            if (new_s < 0)
                throw std::invalid_argument("size must be non-negative");
            n = m = w = new_s;
            data.resize(new_s);
        }

        /**
         * @brief Convert rectangular 3D vector to fixed-size mode with specified dimensions.
         *
         * Converts from dynamic to fixed-size mode with the specified dimensions.
         *
         * @param new_n New depth (number of layers)
         * @param new_m New number of rows per matrix
         * @param new_w New number of columns per row
         *
         * @post n = new_n, m = new_m, w = new_w
         *
         * @throws std::length_error if tensor is already in fixed-size mode
         * @throws std::invalid_argument if any dimension < 0
         */
        void set(size_t new_n, size_t new_m, size_t new_w)
        {
            if (is_fixed())
                throw std::length_error("the array is fixed size and can not be resized");
            if (new_n < 0 || new_m < 0 || new_w < 0)
                throw std::invalid_argument("size must be non-negative");
            n = new_n;
            m = new_m;
            w = new_w;
            data.resize(new_n);
            for (auto &mat : data)
            {
                mat.resize(new_m);
                for (auto &row : mat)
                {
                    row.resize(new_w);
                }
            }
        }
        void set(const std::vector<std::vector<std::vector<dynamic_f>>> &vec)
        {
            if (vec.empty() || vec[0].empty() || vec[0][0].empty())
                throw std::invalid_argument("Input vector cannot be empty");
            size_t rows = vec[0].size();
            size_t cols = vec[0][0].size();
            for (const auto &mat : vec)
            {
                if (mat.size() != rows)
                    throw std::invalid_argument("All matrices must have the same number of rows");
                for (const auto &row : mat)
                {
                    if (row.size() != cols)
                        throw std::invalid_argument("All rows must have the same number of columns");
                }
            }
            data = vec;
            n = data.size();
            m = rows;
            w = cols;
        }
        std::vector<std::vector<std::vector<dynamic_f>>> get() const noexcept { return data; }
        std::vector<std::vector<dynamic_f>> &at(int i) noexcept
        {
            return data[i];
        }
        std::vector<dynamic_f> &at(int i, int j) noexcept
        {
            return data[i][j];
        }
        dynamic_f &at(int i, int j, int k) noexcept
        {
            return data[i][j][k];
        }
        size_t size() const noexcept
        {
            if (n != static_cast<size_t>(-1))
                return n;
            return data.size();
        }
        size_t size(int i) const
        {
            if (m != static_cast<size_t>(-1))
                return m;
            if (i < 0 || i >= data.size())
                throw std::out_of_range("index out of range");
            return data[i].size();
        }
        size_t size(int i, int j) const
        {
            if (w != static_cast<size_t>(-1))
                return w;
            if (i < 0 || i >= data.size())
                throw std::out_of_range("index out of range");
            if (j < 0 || j >= data[i].size())
                throw std::out_of_range("index out of range");
            return data[i][j].size();
        }
        bool is_fixed() const noexcept
        {
            return n != static_cast<size_t>(-1) && m != static_cast<size_t>(-1) && w != static_cast<size_t>(-1);
        }
        void resize(size_t new_s) noexcept
        {
            data.resize(new_s);
            for (auto &mat : data)
            {
                mat.resize(new_s);
                for (auto &row : mat)
                {
                    row.resize(new_s);
                }
            }
            n = m = w = new_s;
        }
        void resize(size_t new_n, size_t new_m, size_t new_w) noexcept
        {
            data.resize(new_n);
            for (auto &mat : data)
            {
                mat.resize(new_m);
                for (auto &row : mat)
                {
                    row.resize(new_w);
                }
            }
            n = new_n;
            m = new_m;
            w = new_w;
        }
        bool empty() const noexcept
        {
            return data.empty();
        }
        bool empty(int i) const
        {
            if (i < 0 || i >= data.size())
                throw std::out_of_range("index out of range");
            return data[i].empty();
        }
        bool empty(int i, int j) const
        {
            if (i < 0 || i >= data.size())
                throw std::out_of_range("index out of range");
            if (j < 0 || j >= data[i].size())
                throw std::out_of_range("index out of range");
            return data[i][j].empty();
        }
        void clear() noexcept
        {
            data.clear();
            n = m = w = -1;
        }
        void clear(int i) noexcept
        {
            data[i].clear();
        }
        void clear(int i, int j) noexcept
        {
            data[i][j].clear();
        }
        void push_back(const std::vector<std::vector<dynamic_f>> &mat)
        {
            if (is_fixed() && n != static_cast<size_t>(-1) && data.size() >= n)
                throw std::length_error("the array is fixed size and can not add more data");
            if (!data.empty())
            {
                if (mat.size() != data[0].size())
                    throw std::invalid_argument("All matrices must have the same number of rows");
                for (const auto &row : mat)
                {
                    if (row.size() != data[0][0].size())
                        throw std::invalid_argument("All rows must have the same number of columns");
                }
            }
            data.push_back(mat);
            if (n != static_cast<size_t>(-1))
                n = data.size();
            if (m == static_cast<size_t>(-1))
                m = mat.size();
            if (w == static_cast<size_t>(-1) && !mat.empty())
                w = mat[0].size();
        }
        void push_back(int i, const std::vector<dynamic_f> &row)
        {
            if (is_fixed() && m != static_cast<size_t>(-1) && data[i].size() >= m)
                throw std::length_error("the array is fixed size and can not add more data");
            if (!data[i].empty() && row.size() != data[i][0].size())
                throw std::invalid_argument("All rows must have the same number of columns");
            data[i].push_back(row);
            if (m != static_cast<size_t>(-1))
                m = data[i].size();
            if (n == static_cast<size_t>(-1))
                n = data.size();
            if (w == static_cast<size_t>(-1) && !row.empty())
                w = row.size();
        }
        void push_back(int i, int j, dynamic_f val)
        {
            if (is_fixed() && w != static_cast<size_t>(-1) && data[i][j].size() >= w)
                throw std::length_error("the array is fixed size and can not add more data");
            data[i][j].push_back(val);
            if (w != static_cast<size_t>(-1))
                w = data[i][j].size();
            if (m == static_cast<size_t>(-1))
                m = data[i].size();
            if (n == static_cast<size_t>(-1))
                n = data.size();
        }
        void push_front(const std::vector<std::vector<dynamic_f>> &mat)
        {
            if (is_fixed() && n != static_cast<size_t>(-1) && data.size() >= n)
                throw std::length_error("the array is fixed size and can not add more data");
            if (!data.empty())
            {
                if (mat.size() != data[0].size())
                    throw std::invalid_argument("All matrices must have the same number of rows");
                for (const auto &row : mat)
                {
                    if (row.size() != data[0][0].size())
                        throw std::invalid_argument("All rows must have the same number of columns");
                }
            }
            data.insert(data.begin(), mat);
            if (n != static_cast<size_t>(-1))
                n = data.size();
            if (m == static_cast<size_t>(-1))
                m = mat.size();
            if (w == static_cast<size_t>(-1) && !mat.empty())
                w = mat[0].size();
        }
        void push_front(int i, const std::vector<dynamic_f> &row)
        {
            if (is_fixed() && m != static_cast<size_t>(-1) && data[i].size() >= m)
                throw std::length_error("the array is fixed size and can not add more data");
            if (!data[i].empty() && row.size() != data[i][0].size())
                throw std::invalid_argument("All rows must have the same number of columns");
            data[i].insert(data[i].begin(), row);
            if (m != static_cast<size_t>(-1))
                m = data[i].size();
            if (n == static_cast<size_t>(-1))
                n = data.size();
            if (w == static_cast<size_t>(-1) && !row.empty())
                w = row.size();
        }
        void push_front(int i, int j, dynamic_f val)
        {
            if (is_fixed() && w != static_cast<size_t>(-1) && data[i][j].size() >= w)
                throw std::length_error("the array is fixed size and can not add more data");
            data[i][j].insert(data[i][j].begin(), val);
            if (w != static_cast<size_t>(-1))
                w = data[i][j].size();
            if (m == static_cast<size_t>(-1))
                m = data[i].size();
            if (n == static_cast<size_t>(-1))
                n = data.size();
        }
        void pop_back()
        {
            if (data.empty())
                throw std::out_of_range("the array is empty");
            data.pop_back();
            if (n != static_cast<size_t>(-1))
                n = data.size();
        }
        void pop_back(int i)
        {
            if (data[i].empty())
                throw std::out_of_range("the matrix is empty");
            data[i].pop_back();
            if (m != static_cast<size_t>(-1))
                m = data[i].size();
        }
        void pop_back(int i, int j)
        {
            if (data[i][j].empty())
                throw std::out_of_range("the row is empty");
            data[i][j].pop_back();
            if (w != static_cast<size_t>(-1))
                w = data[i][j].size();
        }
        void pop_front()
        {
            if (data.empty())
                throw std::out_of_range("the array is empty");
            data.erase(data.begin());
            if (n != static_cast<size_t>(-1))
                n = data.size();
        }
        void pop_front(int i)
        {
            if (data[i].empty())
                throw std::out_of_range("the matrix is empty");
            data[i].erase(data[i].begin());
            if (m != static_cast<size_t>(-1))
                m = data[i].size();
        }
        void pop_front(int i, int j)
        {
            if (data[i][j].empty())
                throw std::out_of_range("the row is empty");
            data[i][j].erase(data[i][j].begin());
            if (w != static_cast<size_t>(-1))
                w = data[i][j].size();
        }
        void erase(int index)
        {
            if (index < 0 || index >= data.size())
                throw std::out_of_range("matrix index out of range");
            data.erase(data.begin() + index);
            if (n != static_cast<size_t>(-1))
                n = data.size();
        }
        void erase(int i, int j)
        {
            if (i < 0 || i >= data.size())
                throw std::out_of_range("matrix index out of range");
            if (j < 0 || j >= data[i].size())
                throw std::out_of_range("row index out of range");
            data[i].erase(data[i].begin() + j);
            if (m != static_cast<size_t>(-1))
                m = data[i].size();
        }
        void erase(int i, int j, int k)
        {
            if (i < 0 || i >= data.size())
                throw std::out_of_range("matrix index out of range");
            if (j < 0 || j >= data[i].size())
                throw std::out_of_range("row index out of range");
            if (k < 0 || k >= data[i][j].size())
                throw std::out_of_range("column index out of range");
            data[i][j].erase(data[i][j].begin() + k);
            if (w != static_cast<size_t>(-1))
                w = data[i][j].size();
        }
        void erase(std::function<bool(const std::vector<std::vector<dynamic_f>> &)> func)
        {
            auto it = std::remove_if(data.begin(), data.end(), func);
            data.erase(it, data.end());
            if (n != static_cast<size_t>(-1))
                n = data.size();
        }
        void erase(int i, std::function<bool(const std::vector<dynamic_f> &)> func)
        {
            if (i < 0 || i >= data.size())
                throw std::out_of_range("matrix index out of range");
            auto it = std::remove_if(data[i].begin(), data[i].end(), func);
            data[i].erase(it, data[i].end());
            if (m != static_cast<size_t>(-1))
                m = data[i].size();
        }
        void erase(int i, int j, std::function<bool(const dynamic_f &)> func)
        {
            if (i < 0 || i >= data.size())
                throw std::out_of_range("matrix index out of range");
            if (j < 0 || j >= data[i].size())
                throw std::out_of_range("row index out of range");
            auto it = std::remove_if(data[i][j].begin(), data[i][j].end(), func);
            data[i][j].erase(it, data[i][j].end());
            if (w != static_cast<size_t>(-1))
                w = data[i][j].size();
        }
        void insert(const std::vector<std::vector<dynamic_f>> &mat, int index)
        {
            if (is_fixed() && n != static_cast<size_t>(-1) && data.size() >= n)
                throw std::length_error("the array is fixed size and can not add more data");
            if (!data.empty())
            {
                if (mat.size() != data[0].size())
                    throw std::invalid_argument("All matrices must have the same number of rows");
                for (const auto &row : mat)
                {
                    if (row.size() != data[0][0].size())
                        throw std::invalid_argument("All rows must have the same number of columns");
                }
            }
            if (index < 0 || index > data.size())
                throw std::out_of_range("matrix index out of range");
            data.insert(data.begin() + index, mat);
            if (n != static_cast<size_t>(-1))
                n = data.size();
            if (m == static_cast<size_t>(-1))
                m = mat.size();
            if (w == static_cast<size_t>(-1) && !mat.empty())
                w = mat[0].size();
        }

        /**
         * @brief Insert a row at a specific position in the 3D vector.
         * @param i The layer index where the row should be inserted.
         * @param j The row index within the specified layer where the new row should be inserted.
         * @param row The row to be inserted, represented as a vector of dynamic elements.
         * @throws std::length_error if the array is fixed size and cannot add more data.
         * @throws std::invalid_argument if the input row has an incompatible number of columns or if the specified indices are out of range.
         * @note This function checks if the array is in fixed-size mode and if adding a new row would exceed the fixed size. It also validates that the input row has the same number of columns as existing rows in the specified layer. The function ensures that the specified indices (i, j) are within the valid range of the current data structure. If all checks pass, it inserts the row at the specified position and updates the size parameters (n, m, w) if they are in dynamic mode.
         */
        void insert(int i, int j, const std::vector<dynamic_f> &row)
        {
            if (is_fixed() && m != static_cast<size_t>(-1) && data[i].size() >= m)
                throw std::length_error("the array is fixed size and can not add more data");
            if (!data[i].empty() && row.size() != data[i][0].size())
                throw std::invalid_argument("All rows must have the same number of columns");
            if (j < 0 || j > data[i].size())
                throw std::out_of_range("row index out of range");
            data[i].insert(data[i].begin() + j, row);
            if (m != static_cast<size_t>(-1))
                m = data[i].size();
            if (n == static_cast<size_t>(-1))
                n = data.size();
            if (w == static_cast<size_t>(-1) && !row.empty())
                w = row.size();
        }

        /**
         * @brief Insert a value at a specific position in the 3D vector.
         * @param i The layer index where the value should be inserted.
         * @param j The row index within the specified layer where the value should be inserted.
         * @param k The column index within the specified row where the value should be inserted.
         * @param val The value to be inserted.
         * @throws std::length_error if the array is fixed size and cannot add more data.
         * @throws std::out_of_range if the specified indices are out of range.
         * @note This function checks if the array is in fixed-size mode and if adding a new value would exceed the fixed size. It also validates that the specified indices (i, j, k) are within the valid range of the current data structure. If all checks pass, it inserts the value at the specified position and updates the size parameters (n, m, w) if they are in dynamic mode.
         */
        void insert(int i, int j, int k, dynamic_f val)
        {
            if (is_fixed() && w != static_cast<size_t>(-1) && data[i][j].size() >= w)
                throw std::length_error("the array is fixed size and can not add more data");
            if (k < 0 || k > data[i][j].size())
                throw std::out_of_range("column index out of range");
            data[i][j].insert(data[i][j].begin() + k, val);
            if (w != static_cast<size_t>(-1))
                w = data[i][j].size();
            if (m == static_cast<size_t>(-1))
                m = data[i].size();
            if (n == static_cast<size_t>(-1))
                n = data.size();
        }

        /**
         * @brief Insert a matrix at a position determined by a condition.
         * @param mat The matrix to be inserted.
         * @param func A function that takes a matrix and returns true if the matrix matches the condition for insertion.
         * @throws std::length_error if the array is fixed size and cannot add more data.
         * @throws std::invalid_argument if the input matrix has incompatible dimensions or if no matrix matches the condition.
         * @note This function checks if the array is in fixed-size mode and if adding a new matrix would exceed the fixed size. It also validates that the input matrix has the same number of rows and columns as existing matrices. The function uses std::find_if to locate the position where the new matrix should be inserted based on the provided condition function. If a matching position is found, the new matrix is inserted at that position; otherwise, an exception is thrown. After insertion, it updates the size parameters (n, m, w) if they are in dynamic mode.
         */
        void insert(const std::vector<std::vector<dynamic_f>> &mat, std::function<bool(const std::vector<std::vector<dynamic_f>> &)> func)
        {
            if (is_fixed() && n != static_cast<size_t>(-1) && data.size() >= n)
                throw std::length_error("the array is fixed size and can not add more data");
            if (!data.empty())
            {
                if (mat.size() != data[0].size())
                    throw std::invalid_argument("All matrices must have the same number of rows");
                for (const auto &row : mat)
                {
                    if (row.size() != data[0][0].size())
                        throw std::invalid_argument("All rows must have the same number of columns");
                }
            }
            auto it = std::find_if(data.begin(), data.end(), func);
            if (it != data.end())
                data.insert(it, mat);
            else
                throw std::invalid_argument("no matrix found matching the condition");
            if (n != static_cast<size_t>(-1))
                n = data.size();
            if (m == static_cast<size_t>(-1))
                m = mat.size();
            if (w == static_cast<size_t>(-1) && !mat.empty())
                w = mat[0].size();
        }

        /// @brief Get the ending iterator for the 2D vector.
        /// @return An iterator pointing to the end of the 2D vector.
        auto end() noexcept { return data.end(); }

        /// @brief Get the beginning iterator for the 2D vector.
        /// @return An iterator pointing to the beginning of the 2D vector.
        auto begin() noexcept { return data.begin(); }

        /// @brief Get the ending iterator for a specific element in the 2D vector.
        /// @param i The layer index.
        /// @return An iterator pointing to the end of the specified element.
        auto end(int i) const noexcept { return data[i].end(); }

        /// @brief Get the beginning iterator for a specific element in the 2D vector.
        /// @param i The layer index.
        /// @return An iterator pointing to the beginning of the specified element.
        auto begin(int i) const noexcept { return data[i].begin(); }

        /// @brief Get the ending iterator for a specific element in the 2D vector.
        /// @param i The layer index.
        /// @param j The row index within the specified layer.
        /// @return An iterator pointing to the end of the specified element.
        auto end(int i, int j) const noexcept { return data[i][j].end(); }

        /// @brief Get the beginning iterator for a specific element in the 2D vector.
        /// @param i The layer index.
        /// @param j The row index within the specified layer.
        /// @return An iterator pointing to the beginning of the specified element.
        auto begin(int i, int j) const noexcept { return data[i][j].begin(); }

        /**
         * @brief Get the last valid layer index.
         * @return The last valid layer index.
         * @throws std::out_of_range if the array is empty.
         */
        size_t last_index() const
        {
            if (n != static_cast<size_t>(-1))
                return n - 1;
            if (data.empty())
                throw std::out_of_range("the array is empty");
            return data.size() - 1;
        }

        /**
         * @brief Get the last valid row index for a given layer.
         * @param i The layer index.
         * @return The last valid row index for the specified layer.
         * @throws std::out_of_range if the specified layer index is out of range or if the layer is empty.
         * @note This function checks if the number of rows (m) is fixed. If it is fixed, it returns m - 1 as the last valid row index. If m is dynamic, it validates the provided layer index (i) against the current data structure and returns the last valid row index based on the size of the specified layer.
         */
        size_t last_index(int i) const
        {
            if (m != static_cast<size_t>(-1))
                return m - 1;
            if (i < 0 || i >= data.size())
                throw std::out_of_range("index out of range");
            if (data[i].empty())
                throw std::out_of_range("the matrix is empty");
            return data[i].size() - 1;
        }

        /**
         * @brief Get the last valid column index for a given layer and row.
         * @param i The layer index.
         * @param j The row index within the specified layer.
         * @return The last valid column index for the specified layer and row.
         * @throws std::out_of_range if the specified layer or row index is out of range, or if the row is empty.
         * @note This function checks if the width (w) is fixed.
         * If it is fixed, it returns w - 1 as the last valid column index.
         * If w is dynamic, it validates the provided layer (i) and row (j) indices against the current data structure and returns the last valid column index based on the size of the specified row.
         */
        size_t last_index(int i, int j) const
        {
            if (w != static_cast<size_t>(-1))
                return w - 1;
            if (i < 0 || i >= data.size())
                throw std::out_of_range("index out of range");
            if (j < 0 || j >= data[i].size())
                throw std::out_of_range("index out of range");
            if (data[i][j].empty())
                throw std::out_of_range("the row is empty");
            return data[i][j].size() - 1;
        }

        /**
         * @brief Assignment operator for dynamic_v3d.
         * @param other The dynamic_v3d instance to assign from.
         * @note This operator performs a deep copy of the underlying 3D vector data from the other instance to this instance.
         * It first checks for self-assignment to avoid unnecessary copying.
         * If the other instance is different from this instance, it copies the data and updates the dimensions (n, m, w) accordingly.
         * @see operator=(const std::vector<std::vector<std::vector<dynamic>>> &) for assignment from a 3D vector.
         */
        void operator=(const dynamic_v3d &other) noexcept
        {
            if (this != &other)
            {
                data = other.data;
                n = other.n;
                m = other.m;
                w = other.w;
            }
        }

        /**
         * @brief Assignment operator for dynamic_v3d.
         * @param vec The 3D vector to assign to this instance.
         * @throws std::invalid_argument if the input vector is empty or if the matrices within the vector have inconsistent row/column counts.
         * @note This operator assigns the provided 3D vector to the underlying data of this instance.
         * It first validates that the input vector is not empty and that all matrices within the vector have consistent dimensions.
         * If the input data is valid, it updates the internal state of this instance to reflect the new data and dimensions inferred from the input vector.
         * @see operator=(const std::initializer_list<std::vector<std::vector<dynamic>>> &) for assignment from initializer lists.
         */
        void operator=(const std::vector<std::vector<std::vector<dynamic_f>>> &vec)
        {
            if (vec.empty() || vec[0].empty() || vec[0][0].empty())
                throw std::invalid_argument("Input vector cannot be empty");
            size_t rows = vec[0].size();
            size_t cols = vec[0][0].size();
            for (const auto &mat : vec)
            {
                if (mat.size() != rows)
                    throw std::invalid_argument("All matrices must have the same number of rows");
                for (const auto &row : mat)
                {
                    if (row.size() != cols)
                        throw std::invalid_argument("All rows must have the same number of columns");
                }
            }
            data = vec;
            n = data.size();
            m = rows;
            w = cols;
        }

        /**
         * @brief Assignment operator for dynamic_v3d.
         * @param ini The initializer list of 2D matrices to assign to this instance.
         * @throws std::length_error if n is fixed but doesn't match layer count of ini.
         * @throws std::invalid_argument if matrices in ini have inconsistent row/column counts or if ini is empty.
         * @note This operator assigns the provided initializer list of 2D matrices to the underlying 3D vector data of this instance. If n, m, and w are already set to fixed values, it validates that the dimensions of the provided data match those fixed dimensions. If the data is valid, it updates the internal state of this instance to reflect the new data and dimensions.
         */
        void operator=(const std::initializer_list<std::vector<std::vector<dynamic_f>>> &ini)
        {
            data = ini;
            if (n != static_cast<size_t>(-1) && m != static_cast<size_t>(-1) && w != static_cast<size_t>(-1))
            {
                if (data.size() != n)
                    throw std::length_error("the array is fixed size and can not be resized");
                for (const auto &mat : data)
                {
                    if (mat.size() != m)
                        throw std::invalid_argument("All matrices must have the same number of rows");
                    for (const auto &row : mat)
                    {
                        if (row.size() != w)
                            throw std::invalid_argument("All rows must have the same number of columns");
                    }
                }
            }
        }

        /**
         * @brief Equality operator for dynamic_v3d.
         * @param other The dynamic_v3d instance to compare with.
         * @return true if the underlying 3D vector data of this instance is equal to that of the other instance; false otherwise.
         * @note This operator compares the contents of the 3D vector data for both instances. If the data is identical, it returns true; if there are any differences in the data, it returns false.
         * @see operator!= for inequality comparison of dynamic_v3d instances.
         */
        bool operator==(const dynamic_v3d &other) const noexcept { return data == other.data; }

        /**
         * @brief Inequality operator for dynamic_v3d.
         * @param other The dynamic_v3d instance to compare with.
         * @return true if the underlying 3D vector data of this instance is not equal to that of the other instance; false otherwise.
         * @note This operator compares the contents of the 3D vector data for both instances. If the data is identical, it returns false; if there are any differences in the data, it returns true.
         * @see operator== for equality comparison of dynamic_v3d instances.
         */
        bool operator!=(const dynamic_v3d &other) const noexcept { return data != other.data; }

        /**
         * @brief Performs element-wise addition of a given integer value to each element in the 3D array.
         * @param val The integer value to add to each element of the array.
         * @throws std::runtime_error if the array is empty (i.e., if data is empty or if the first matrix or the first row of the first matrix is empty).
         * @note The addition operation is performed in-place, modifying the existing elements of the array. Each element is increased by the provided integer value.
         * @see operator+=(float), operator+=(double), operator+=(char) for addition operations with other types of values.
         */
        void operator+=(int val)
        {
            if (data.empty() || data[0].empty() || data[0][0].empty())
                throw std::runtime_error("the array is empty");
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data[i].size(); j++)
                    for (int k = 0; k < data[i][j].size(); k++)
                        data[i][j][k] += val;
        }

        /**
         * @brief Performs element-wise addition of a given float value to each element in the 3D array.
         * @param val The float value to add to each element of the array.
         * @throws std::runtime_error if the array is empty (i.e., if data is empty or if the first matrix or the first row of the first matrix is empty).
         * @note The addition operation is performed in-place, modifying the existing elements of the array. Each element is increased by the provided float value.
         * @see operator+=(int), operator+=(double), operator+=(char) for addition operations with other types of values.
         */
        void operator+=(float val)
        {
            if (data.empty() || data[0].empty() || data[0][0].empty())
                throw std::runtime_error("the array is empty");
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data[i].size(); j++)
                    for (int k = 0; k < data[i][j].size(); k++)
                        data[i][j][k] += val;
        }

        /**
         * @brief Performs element-wise addition of a given double value to each element in the 3D array.
         * @param val The double value to add to each element of the array.
         * @throws std::runtime_error if the array is empty (i.e., if data is empty or if the first matrix or the first row of the first matrix is empty).
         * @note The addition operation is performed in-place, modifying the existing elements of the array. Each element is increased by the provided double value.
         * @see operator+=(int), operator+=(float), operator+=(char) for addition operations with other types of values.
         */
        void operator+=(double val)
        {
            if (data.empty() || data[0].empty() || data[0][0].empty())
                throw std::runtime_error("the array is empty");
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data[i].size(); j++)
                    for (int k = 0; k < data[i][j].size(); k++)
                        data[i][j][k] += val;
        }

        /**
         * @brief Performs element-wise addition of a given char value to each element in the 3D array.
         * @param val The char value to add to each element of the array. It will be cast to an int before the addition.
         * @throws std::runtime_error if the array is empty (i.e., if data is empty or if the first matrix or the first row of the first matrix is empty).
         * @note The addition operation is performed in-place, modifying the existing elements of the array. Each element is increased by the integer value of the provided char.
         * @warning The behavior of addition by a char value is implementation-defined and may not produce meaningful results if the elements of the array are not of a compatible type. It is generally recommended to use addition with integer or floating-point types for predictable behavior.
         * @see operator+=(int), operator+=(float), operator+=(double) for addition operations
         */
        void operator+=(char val)
        {
            if (data.empty() || data[0].empty() || data[0][0].empty())
                throw std::runtime_error("the array is empty");
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data[i].size(); j++)
                    for (int k = 0; k < data[i][j].size(); k++)
                        data[i][j][k] += static_cast<int>(val);
        }

        /**
         * @brief Performs element-wise subtraction of a given integer value from each element in the 3D array.
         * @param val The integer value to subtract from each element of the array.
         * @throws std::runtime_error if the array is empty (i.e., if data is empty or if the first matrix or the first row of the first matrix is empty).
         * @note The subtraction operation is performed in-place, modifying the existing elements of the array. Each element is reduced by the provided integer value.
         * @see operator-=(float), operator-=(double), operator-=(char) for subtraction operations with other types of values.
         */
        void operator-=(int val)
        {
            if (data.empty() || data[0].empty() || data[0][0].empty())
                throw std::runtime_error("the array is empty");
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data[i].size(); j++)
                    for (int k = 0; k < data[i][j].size(); k++)
                        data[i][j][k] -= val;
        }

        /**
         * @brief Performs element-wise subtraction of a given float value from each element in the 3D array.
         * @param val The float value to subtract from each element of the array.
         * @throws std::runtime_error if the array is empty (i.e., if data is empty or if the first matrix or the first row of the first matrix is empty).
         * @note The subtraction operation is performed in-place, modifying the existing elements of the array. Each element is reduced by the provided float value.
         * @see operator-=(int), operator-=(double), operator-=(char) for subtraction operations with other types of values.
         */
        void operator-=(float val)
        {
            if (data.empty() || data[0].empty() || data[0][0].empty())
                throw std::runtime_error("the array is empty");
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data[i].size(); j++)
                    for (int k = 0; k < data[i][j].size(); k++)
                        data[i][j][k] -= val;
        }

        /**
         * @brief Performs element-wise subtraction of a given double value from each element in the 3D array.
         * @param val The double value to subtract from each element of the array.
         * @throws std::runtime_error if the array is empty (i.e., if data is empty or if the first matrix or the first row of the first matrix is empty).
         * @note The subtraction operation is performed in-place, modifying the existing elements of the array. Each element is reduced by the provided double value.
         * @see operator-=(int), operator-=(float), operator-=(char) for subtraction operations with other types of values.
         */
        void operator-=(double val)
        {
            if (data.empty() || data[0].empty() || data[0][0].empty())
                throw std::runtime_error("the array is empty");
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data[i].size(); j++)
                    for (int k = 0; k < data[i][j].size(); k++)
                        data[i][j][k] -= val;
        }

        /**
         * @brief Performs element-wise subtraction of a given char value from each element in the 3D array.
         * @param val The char value to subtract from each element of the array. It will
         * be cast to an int before the subtraction.
         * @throws std::runtime_error if the array is empty (i.e., if data is empty or if the first matrix or the first row of the first matrix is empty).
         * @note The subtraction operation is performed in-place, modifying the existing elements of the array. Each element is reduced by the integer value of the provided char.
         * @warning The behavior of subtraction by a char value is implementation-defined and may not produce meaningful results if the elements of the array are not of a compatible type. It is generally recommended to use subtraction with integer or floating-point types for predictable behavior.
         * @see operator-=(int), operator-=(float), operator-=(double)
         */
        void operator-=(char val)
        {
            if (data.empty() || data[0].empty() || data[0][0].empty())
                throw std::runtime_error("the array is empty");
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data[i].size(); j++)
                    for (int k = 0; k < data[i][j].size(); k++)
                        data[i][j][k] -= static_cast<int>(val);
        }

        /**
         * @brief Performs element-wise multiplication of each element in the 3D array by a given integer value.
         * @param val The integer value to multiply each element of the array by.
         * @throws std::runtime_error if the array is empty (i.e., if data is empty or if the first matrix or the first row of the first matrix is empty).
         * @note The multiplication operation is performed in-place, modifying the existing elements of the array. Each element is multiplied by the provided integer value.
         * @see operator*=(float), operator*=(double), operator*=(char) for multiplication operations with other types of values.
         */
        void operator*=(int val)
        {
            if (data.empty() || data[0].empty() || data[0][0].empty())
                throw std::runtime_error("the array is empty");
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data[i].size(); j++)
                    for (int k = 0; k < data[i][j].size(); k++)
                        data[i][j][k] *= val;
        }

        /**
         * @brief Performs element-wise multiplication of each element in the 3D array by a given float value.
         * @param val The float value to multiply each element of the array by.
         * @throws std::runtime_error if the array is empty (i.e., if data is empty or if the first matrix or the first row of the first matrix is empty).
         * @note The multiplication operation is performed in-place, modifying the existing elements of the array. Each element is multiplied by the provided float value.
         * @see operator*=(int), operator*=(double), operator*=(char) for multiplication operations with other types of values.
         */
        void operator*=(float val)
        {
            if (data.empty() || data[0].empty() || data[0][0].empty())
                throw std::runtime_error("the array is empty");
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data[i].size(); j++)
                    for (int k = 0; k < data[i][j].size(); k++)
                        data[i][j][k] *= val;
        }

        /**
         * @brief Performs element-wise multiplication of each element in the 3D array by a given double value.
         * @param val The double value to multiply each element of the array by.
         * @throws std::runtime_error if the array is empty (i.e., if data is empty or if the first matrix or the first row of the first matrix is empty).
         * @note The multiplication operation is performed in-place, modifying the existing elements of the array. Each element is multiplied by the provided double value.
         * @see operator*=(int), operator*=(float), operator*=(char) for multiplication operations with other types of values.
         */
        void operator*=(double val)
        {
            if (data.empty() || data[0].empty() || data[0][0].empty())
                throw std::runtime_error("the array is empty");
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data[i].size(); j++)
                    for (int k = 0; k < data[i][j].size(); k++)
                        data[i][j][k] *= val;
        }

        /**
         * @brief Performs element-wise multiplication of each element in the 3D array by a given char value.
         * @param val The char value to multiply each element of the array by. It will be cast to an int before the multiplication.
         * @throws std::runtime_error if the array is empty (i.e., if data is empty or if the first matrix or the first row of the first matrix is empty).
         * @note The multiplication operation is performed in-place, modifying the existing elements of the array. Each element is multiplied by the integer value of the provided char.
         * @warning The behavior of multiplication by a char value is implementation-defined and may not produce meaningful results if the elements of the array are not of a compatible type. It is generally recommended to use multiplication with integer or floating-point types for predictable behavior.
         * @see operator*=(int), operator*=(float), operator*=(double)
         */
        void operator*=(char val)
        {
            if (data.empty() || data[0].empty() || data[0][0].empty())
                throw std::runtime_error("the array is empty");
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data[i].size(); j++)
                    for (int k = 0; k < data[i][j].size(); k++)
                        data[i][j][k] *= static_cast<int>(val);
        }

        /**
         * @brief Performs element-wise division of each element in the 3D array by a given integer value.
         * @param val The integer value to divide each element of the array by.
         * @throws std::runtime_error if the array is empty (i.e., if data is empty or if the first matrix or the first row of the first matrix is empty).
         * @note The division operation is performed in-place, modifying the existing elements of the array. Each element is divided by the provided integer value.
         * @see operator/=(float), operator/=(double), operator/=(char) for division operations with other types of values.
         * @warning The behavior of division by an integer value is implementation-defined and may not produce meaningful results if the elements of the array are not of a compatible type.
         * It is generally recommended to use division with integer or floating-point types for predictable behavior.
         */
        void operator/=(int val)
        {
            if (data.empty() || data[0].empty() || data[0][0].empty())
                throw std::runtime_error("the array is empty");
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data[i].size(); j++)
                    for (int k = 0; k < data[i][j].size(); k++)
                        data[i][j][k] /= val;
        }

        /**
         * @brief Performs element-wise division of each element in the 3D array by a given float value.
         * @param val The float value to divide each element of the array by.
         * @throws std::runtime_error if the array is empty (i.e., if data is empty or if the first matrix or the first row of the first matrix is empty).
         * @note The division operation is performed in-place, modifying the existing elements of the array. Each element is divided by the provided float value.
         * @see operator/=(int), operator/=(double), operator/=(char) for division operations with other types of values.
         * @warning The behavior of division by a float value is implementation-defined and may not produce meaningful results if the elements of the array are not of a compatible type. It is generally recommended to use division with integer or floating-point types for predictable behavior.
         */
        void operator/=(float val)
        {
            if (data.empty() || data[0].empty() || data[0][0].empty())
                throw std::runtime_error("the array is empty");
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data[i].size(); j++)
                    for (int k = 0; k < data[i][j].size(); k++)
                        data[i][j][k] /= val;
        }

        /**
         * @brief Performs element-wise division of each element in the 3D array by a given double value.
         * @param val The double value to divide each element of the array by.
         * @throws std::runtime_error if the array is empty (i.e., if data is empty or if the first matrix or the first row of the first matrix is empty).
         * @note The division operation is performed in-place, modifying the existing elements of the array. Each element is divided by the provided double value.
         * @see operator/=(int), operator/=(float), operator/=(char) for division operations with other types of values.
         * @warning The behavior of division by a double value is implementation-defined and may not produce meaningful results if the elements of the array are not of a compatible type. It is generally recommended to use division with integer or floating-point types for predictable behavior.
         */
        void operator/=(double val)
        {
            if (data.empty() || data[0].empty() || data[0][0].empty())
                throw std::runtime_error("the array is empty");
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data[i].size(); j++)
                    for (int k = 0; k < data[i][j].size(); k++)
                        data[i][j][k] /= val;
        }

        /**
         * @brief Performs element-wise division of each element in the 3D array by a given char value.
         * @param val The char value to divide each element of the array by. It will be cast to an int before the division.
         * @throws std::runtime_error if the array is empty (i.e., if data is empty or if the first matrix or the first row of the first matrix is empty).
         * @note The division operation is performed in-place, modifying the existing elements of the array. Each element is divided by the integer value of the provided char.
         * @warning The behavior of division by a char value is implementation-defined and may not produce meaningful results if the elements of the array are not of a compatible type. It is generally recommended to use division with integer or floating-point types for predictable behavior.
         */
        void operator/=(char val)
        {
            if (data.empty() || data[0].empty() || data[0][0].empty())
                throw std::runtime_error("the array is empty");
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data[i].size(); j++)
                    for (int k = 0; k < data[i][j].size(); k++)
                        data[i][j][k] /= val;
        }

        /**
         * @brief Performs a bitwise XOR operation on each element of the 3D array with the given integer value.
         * @param val The integer value to XOR with each element of the array.
         * @throws std::runtime_error if the array is empty (i.e., if data is empty or if the first matrix or the first row of the first matrix is empty).
         * @note The XOR operation is performed in-place, modifying the existing elements of the array. Each element is XORed with the provided integer value.
         * @see operator^=(float), operator^=(double), operator^=(char) for XOR operations with other types of values.
         */
        void operator^=(int val)
        {
            if (data.empty() || data[0].empty() || data[0][0].empty())
                throw std::runtime_error("the array is empty");
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data[i].size(); j++)
                    for (int k = 0; k < data[i][j].size(); k++)
                        data[i][j][k] ^= val;
        }

        /**
         * @brief Performs a bitwise XOR operation on each element of the 3D array with the given float value.
         * @param val The float value to XOR with each element of the array. It will be cast to an int before the operation.
         * @throws std::runtime_error if the array is empty (i.e., if data is empty or if the first matrix or the first row of the first matrix is empty).
         * @note The XOR operation is performed in-place, modifying the existing elements of the array. Each element is XORed with the integer value of the provided float.
         * @warning The behavior of the XOR operation on floating-point values is implementation-defined and may not produce meaningful results. It is generally recommended to use XOR with integer types for predictable behavior.
         * @see operator^=(int) for XOR operations on integer values.
         */
        void operator^=(float val)
        {
            if (data.empty() || data[0].empty() || data[0][0].empty())
                throw std::runtime_error("the array is empty");
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data[i].size(); j++)
                    for (int k = 0; k < data[i][j].size(); k++)
                        data[i][j][k] ^= val;
        }

        /**
         * @brief Performs a bitwise XOR operation on each element of the 3D array with the given double value.
         * @param val The double value to XOR with each element of the array. It will be cast to an int before the operation.
         * @throws std::runtime_error if the array is empty (i.e., if data is empty or if the first matrix or the first row of the first matrix is empty).
         * @note The XOR operation is performed in-place, modifying the existing elements of the array. Each element is XORed with the integer value of the provided double.
         */
        void operator^=(double val)
        {
            if (data.empty() || data[0].empty() || data[0][0].empty())
                throw std::runtime_error("the array is empty");
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data[i].size(); j++)
                    for (int k = 0; k < data[i][j].size(); k++)
                        data[i][j][k] ^= val;
        }

        /**
         * @brief Performs a bitwise XOR operation on each element of the 3D array with the given char value.
         * @param val The char value to XOR with each element of the array. It will be cast to an int before the operation.
         * @throws std::runtime_error if the array is empty (i.e., if data is empty or if the first matrix or the first row of the first matrix is empty).
         * @note The XOR operation is performed in-place, modifying the existing elements of the array. Each element is XORed with the integer value of the provided char.
         */
        void operator^=(char val)
        {
            if (data.empty() || data[0].empty() || data[0][0].empty())
                throw std::runtime_error("the array is empty");
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data[i].size(); j++)
                    for (int k = 0; k < data[i][j].size(); k++)
                        data[i][j][k] ^= static_cast<int>(val);
        }
        ~dynamic_v3d() = default;
    };
}

#endif // OPENUDT___UDT_DYNAMIC__DYANMIC_V3D__HPP