#include "dynamic_f.hpp"
#include <functional>
#include <vector>
#include <ostream>

#pragma once
#ifndef OPENUDT___UDT_DYNAMIC__DYANMIC_V2D__HPP
#define OPENUDT___UDT_DYNAMIC__DYANMIC_V2D__HPP

namespace udt
{
    /**
     * @class dynamic_v2d
     * @brief 2D vector container for heterogeneous dynamic type elements.
     *
     * @details A 2D matrix wrapper around std::vector<std::vector<dynamic>> that provides
     * dynamic type storage in a 2D grid format. Elements can be of mixed types as each
     * element is a `dynamic` type. Supports both fixed-size and dynamic-size matrices.
     *
     * Features:
     * - 2D heterogeneous type storage with dynamic elements
     * - Optional fixed-size mode for capacity-constrained matrices
     * - Support for rectangular and square matrices
     * - Row and column access patterns
     * - Flexible construction from initializer lists and vectors
     *
     * Storage Model:
     * - std::vector<std::vector<dynamic>> data: underlying 2D storage
     * - size_t n: number of rows (or -1 if dynamic)
     * - size_t m: number of columns (or -1 if dynamic)
     *
     * Size Modes:
     * | Mode | n | m | Behavior |
     * |------|-----|-----|----------|
     * | Dynamic | -1 | -1 | Fully dynamic row and column counts |
     * | Fixed Square | N | N | Fixed N×N matrix |
     * | Fixed Rectangular | N | M | Fixed N×M matrix |
     *
     * @note Each element maintains its own type information via the `dynamic` type.
     * @note Fixed-size mode prevents resizing once established.
     * @note Not thread-safe. External synchronization required for concurrent access.
     *
     * @see dynamic - Individual dynamic type holder
     * @see dynamic_v - 1D vector variant
     * @see dynamic_v3d - 3D vector variant
     */
    class dynamic_v2d
    {
    private:
        /// @brief Number of rows (or -1 if dynamic)
        size_t n = 0;
        /// @brief Number of columns (or -1 if dynamic)
        size_t m = 0;
        /// @brief Underlying 2D array storage for dynamic elements
        std::vector<std::vector<dynamic_f>> data;

    public:
        /**
         * @brief Default constructor - creates empty 2D dynamic vector.
         *
         * Initializes a dynamic_v2d with no elements and dynamic dimensions.
         *
         * @post n = -1, m = -1, data.empty() = true
         */
        dynamic_v2d() = default;

        /**
         * @brief Constructs square fixed-size 2D vector.
         *
         * Creates a dynamic_v2d with square fixed dimensions (size × size).
         * All elements are value-initialized to default dynamic values.
         *
         * @param size The number of rows and columns for the square matrix
         *
         * @post n = size, m = size, data is size×size with value-initialized elements
         */
        dynamic_v2d(size_t size) noexcept : n(size), m(size), data(size, std::vector<dynamic_f>(size)) {}

        /**
         * @brief Constructs rectangular fixed-size 2D vector.
         *
         * Creates a dynamic_v2d with fixed row and column dimensions.
         * All elements are value-initialized to default dynamic values.
         *
         * @param rows The number of rows in the matrix
         * @param cols The number of columns in the matrix
         *
         * @post n = rows, m = cols, data is rows×cols with value-initialized elements
         */
        dynamic_v2d(size_t rows, size_t cols) noexcept : n(rows), m(cols), data(rows, std::vector<dynamic_f>(cols)) {}

        /**
         * @brief Constructs fixed-size 2D vector with provided data.
         *
         * Creates a dynamic_v2d with specified dimensions and initializes it
         * with the provided 2D vector data.
         *
         * @param N The number of rows
         * @param M The number of columns
         * @param vec The 2D vector data to initialize with
         *
         * @post n = N, m = M, data contains vec
         */
        dynamic_v2d(size_t N, size_t M, const std::vector<std::vector<dynamic_f>> &vec) noexcept : n(N), m(M), data(vec) {}

        /**
         * @brief Constructs from a 2D vector with dynamic dimensions.
         *
         * Creates a dynamic_v2d initialized from a 2D vector without fixed size constraints.
         * Dimensions are inferred from the vector structure.
         *
         * @param vec The 2D vector data to initialize with
         *
         * @post n = -1, m = -1, data contains vec
         */
        dynamic_v2d(const std::vector<std::vector<dynamic_f>> &vec) noexcept : data(vec) {}

        /**
         * @brief Constructs from initializer list with dimension validation.
         *
         * Creates a dynamic_v2d from an initializer list of vectors. If n and m
         * are already set, validates that dimensions match.
         *
         * @param ini Initializer list of row vectors
         *
         * @throws std::length_error if n is fixed but doesn't match row count
         * @throws std::invalid_argument if rows have inconsistent column counts
         */
        dynamic_v2d(const std::initializer_list<std::vector<dynamic_f>> &ini) : data(ini)
        {
            if (n != static_cast<size_t>(-1) && m != static_cast<size_t>(-1))
            {
                if (data.size() != n)
                    throw std::length_error("the array is fixed size and can not be resized");
                for (const auto &row : data)
                {
                    if (row.size() != m)
                        throw std::invalid_argument("All rows must have the same number of columns");
                }
            }
        }

        /**
         * @brief Constructs square fixed-size 2D vector with initializer list.
         *
         * Creates a dynamic_v2d with square fixed dimensions (s × s) initialized
         * from an initializer list.
         *
         * @param s The size for both rows and columns
         * @param ini The initializer list for matrix data
         *
         * @post n = s, m = s, data initialized from ini
         */
        dynamic_v2d(size_t s, const std::initializer_list<std::vector<dynamic_f>> &ini) noexcept : n(s), m(s), data(ini) {}

        /**
         * @brief Constructs rectangular fixed-size 2D vector with initializer list.
         *
         * Creates a dynamic_v2d with specified fixed dimensions initialized
         * from an initializer list.
         *
         * @param N The number of rows
         * @param M The number of columns
         * @param ini The initializer list for matrix data
         *
         * @post n = N, m = M, data initialized from ini
         */
        dynamic_v2d(size_t N, size_t M, const std::initializer_list<std::vector<dynamic_f>> &ini) noexcept : n(N), m(M), data(ini) {}

        /**
         * @brief Copy constructor for dynamic_v2d.
         *
         * Creates an independent copy of another dynamic_v2d including dimensions and data.
         *
         * @param other The source dynamic_v2d to copy from
         *
         * @post This object is a complete and independent copy of other
         */
        dynamic_v2d(const dynamic_v2d &other) noexcept : n(other.n), m(other.m), data(other.data) {}

        /**
         * @brief Get the number of rows in the matrix.
         *
         * For fixed-size matrices, returns the fixed row count.
         * For dynamic matrices, returns the actual number of rows.
         *
         * @return The number of rows (or -1 if dynamic with no data)
         */
        size_t size() const noexcept
        {
            if (n != static_cast<size_t>(-1))
                return n;
            return data.size();
        }

        /**
         * @brief Get the number of columns in a specific row.
         *
         * For fixed-size matrices, returns the fixed column count.
         * For dynamic matrices, returns the column count of the specified row.
         *
         * @param i The row index to query
         *
         * @return The number of columns in row i
         *
         * @throws std::out_of_range if i is outside valid row range
         */
        size_t size(size_t i) const
        {
            if (i >= data.size())
                throw std::out_of_range("index out of range");
            return data[i].size();
        }

        size_t mat_size() const noexcept { return n * m; }

        std::vector<std::vector<dynamic_f>> get() const noexcept { return data; }

        void set(const std::vector<std::vector<dynamic_f>> &vec)
        {
            if (vec.empty() || vec[0].empty())
                throw std::invalid_argument("Input vector cannot be empty");
            size_t cols = vec[0].size();
            for (const auto &row : vec)
            {
                if (row.size() != cols)
                    throw std::invalid_argument("All rows must have the same number of columns");
            }
            data = vec;
            n = data.size();
            m = cols;
        }

        void set(size_t new_s)
        {
            if (is_fixed())
                throw std::length_error("the array is fixed size and can not be resized");
            data.resize(new_s);
        }

        void set(size_t new_n, size_t new_m)
        {
            if (is_fixed())
                throw std::length_error("the array is fixed size and can not be resized");
            if (new_m < 0)
                throw std::invalid_argument("size must be non-negative");
            data.resize(new_n);
            for (auto &row : data)
            {
                row.resize(new_m);
            }
            n = new_n;
            m = new_m;
        }

        std::vector<dynamic_f> &at(size_t index) noexcept
        {
            return data[index];
        }

        dynamic_f &at(size_t i, size_t j) noexcept
        {
            return data[i][j];
        }

        void resize(size_t new_n, size_t new_m) noexcept
        {
            data.resize(new_n);
            for (auto &row : data)
            {
                row.resize(new_m);
            }
            n = new_n;
            m = new_m;
        }

        void resize(size_t new_s) noexcept
        {
            data.resize(new_s);
            for (auto &row : data)
            {
                row.resize(new_s);
            }
            n = new_s;
            m = new_s;
        }

        void clear() noexcept
        {
            data.clear();
            n = m = -1;
        }

        void clear(size_t i) noexcept
        {
            data[i].clear();
        }

        void pop_back()
        {
            if (data.empty())
                throw std::out_of_range("the array is empty");
            data.pop_back();
            if (n != static_cast<size_t>(-1))
                n = data.size();
        }

        void pop_back(size_t i)
        {
            if (data[i].empty())
                throw std::out_of_range("the row is empty");
            data[i].pop_back();
            if (m != static_cast<size_t>(-1))
                m = data[i].size();
        }

        void pop_front(size_t i)
        {
            if (data[i].empty())
                throw std::out_of_range("the row is empty");
            data[i].erase(data[i].begin());
            if (m != static_cast<size_t>(-1))
                m = data[i].size();
        }

        void pop_front()
        {
            if (data.empty())
                throw std::out_of_range("the array is empty");
            data.erase(data.begin());
            if (n != static_cast<size_t>(-1))
                n = data.size();
        }

        void push_back(const std::vector<dynamic_f> &row)
        {
            if (is_fixed() && n != static_cast<size_t>(-1) && data.size() >= n)
                throw std::length_error("the array is fixed size and can not add more data");
            if (!data.empty() && row.size() != data[0].size())
                throw std::invalid_argument("All rows must have the same number of columns");
            data.push_back(row);
            if (n != static_cast<size_t>(-1))
                n = data.size();
            if (m == static_cast<size_t>(-1))
                m = row.size();
        }

        void push_back(int i, dynamic_f val)
        {
            if (is_fixed() && m != static_cast<size_t>(-1) && data[i].size() >= m)
                throw std::length_error("the array is fixed size and can not add more data");
            data[i].push_back(val);
            if (m != static_cast<size_t>(-1))
                m = data[i].size();
            if (n == static_cast<size_t>(-1))
                n = data.size();
        }
        void push_front(const std::vector<dynamic_f> &row)
        {
            if (is_fixed() && n != static_cast<size_t>(-1) && data.size() >= n)
                throw std::length_error("the array is fixed size and can not add more data");
            if (!data.empty() && row.size() != data[0].size())
                throw std::invalid_argument("All rows must have the same number of columns");
            data.insert(data.begin(), row);
            if (n != static_cast<size_t>(-1))
                n = data.size();
            if (m == static_cast<size_t>(-1))
                m = row.size();
        }

        void push_front(size_t i, dynamic_f val)
        {
            if (is_fixed() && data[i].size() >= m)
                throw std::length_error("the array is fixed size and can not add more data");
            data[i].insert(data[i].begin(), val);
            if (m != static_cast<size_t>(-1))
                m = data[i].size();
            if (n == static_cast<size_t>(-1))
                n = data.size();
        }

        void erase(size_t index)
        {
            if (index >= data.size())
                throw std::out_of_range("row index out of range");
            data.erase(data.begin() + index);
            if (n != static_cast<size_t>(-1))
                n = data.size();
        }

        void erase(size_t row, size_t index)
        {
            if (row >= data.size())
                throw std::out_of_range("row index out of range");
            if (index >= data[row].size())
                throw std::out_of_range("column index out of range");
            data[row].erase(data[row].begin() + index);
            if (m != static_cast<size_t>(-1))
                m = data[row].size();
        }

        void erase(std::function<bool(const std::vector<dynamic_f> &)> func)
        {
            auto it = std::remove_if(data.begin(), data.end(), func);
            data.erase(it, data.end());
            if (n != static_cast<size_t>(-1))
                n = data.size();
        }

        void erase(size_t row, std::function<bool(const dynamic_f &)> func)
        {
            if (row >= data.size())
                throw std::out_of_range("row index out of range");
            auto it = std::remove_if(data[row].begin(), data[row].end(), func);
            data[row].erase(it, data[row].end());
            if (m != static_cast<size_t>(-1))
                m = data[row].size();
        }

        void insert(const std::vector<dynamic_f> &row, size_t index)
        {
            if (is_fixed() && data.size() >= n)
                throw std::length_error("the array is fixed size and can not add more data");
            if (!data.empty() && row.size() != data[0].size())
                throw std::invalid_argument("All rows must have the same number of columns");
            if (index < 0 || index > data.size())
                throw std::out_of_range("row index out of range");
            data.insert(data.begin() + index, row);
            if (n != static_cast<size_t>(-1))
                n = data.size();
            if (m == static_cast<size_t>(-1))
                m = row.size();
        }

        void insert(size_t row, size_t index, dynamic_f val)
        {
            if (is_fixed() && data[row].size() >= m)
                throw std::length_error("the array is fixed size and can not add more data");
            if (row >= data.size())
                throw std::out_of_range("row index out of range");
            if (index > data[row].size())
                throw std::out_of_range("column index out of range");
            data[row].insert(data[row].begin() + index, val);
            if (m != static_cast<size_t>(-1))
                m = data[row].size();
            if (n == static_cast<size_t>(-1))
                n = data.size();
        }

        void insert(const std::vector<dynamic_f> &row, std::function<bool(const std::vector<dynamic_f> &)> func)
        {
            if (is_fixed() && data.size() >= n)
                throw std::length_error("the array is fixed size and can not add more data");
            if (!data.empty() && row.size() != data[0].size())
                throw std::invalid_argument("All rows must have the same number of columns");
            auto it = std::find_if(data.begin(), data.end(), func);
            if (it != data.end())
                data.insert(it, row);
            else
                throw std::invalid_argument("no row found matching the condition");
            if (n != static_cast<size_t>(-1))
                n = data.size();
            if (m == static_cast<size_t>(-1))
                m = row.size();
        }

        bool is_fixed() const noexcept { return n != static_cast<size_t>(-1) && m != static_cast<size_t>(-1); }

        std::vector<dynamic_f> &operator[](size_t index)
        {
            if (index < 0 || index >= data.size())
                throw std::out_of_range("row index out of range");
            return data[index];
        }

        void operator=(const dynamic_v2d &other) noexcept
        {
            if (this != &other)
            {
                data = other.data;
                n = other.n;
                m = other.m;
            }
        }

        void operator=(const std::vector<std::vector<dynamic_f>> &vec)
        {
            if (vec.empty() || vec[0].empty())
                throw std::invalid_argument("Input vector cannot be empty");
            size_t cols = vec[0].size();
            for (const auto &row : vec)
            {
                if (row.size() != cols)
                    throw std::invalid_argument("All rows must have the same number of columns");
            }
            data = vec;
            n = data.size();
            m = cols;
        }

        void operator=(const std::initializer_list<std::vector<dynamic_f>> &ini)
        {
            data = ini;
            if (n != static_cast<size_t>(-1) && m != static_cast<size_t>(-1))
            {
                if (data.size() != n)
                    throw std::length_error("the array is fixed size and can not be resized");
                for (const auto &row : data)
                {
                    if (row.size() != m)
                        throw std::invalid_argument("All rows must have the same number of columns");
                }
            }
        }

        bool operator==(const dynamic_v2d &other) const noexcept { return data == other.data; }

        bool operator!=(const dynamic_v2d &other) const noexcept { return data != other.data; }

        bool operator==(const std::vector<std::vector<dynamic_f>> &other) const noexcept
        {
            dynamic_v2d temp = other;
            return data == temp.data;
        }

        bool operator!=(const std::vector<std::vector<dynamic_f>> &other) const noexcept
        {
            dynamic_v2d temp = other;
            return data == temp.data;
        }

        void operator+=(int val)
        {
            if (data.empty() || data[0].empty())
                throw std::runtime_error("the array is empty");
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data[i].size(); j++)
                    data[i][j] += val;
        }

        void operator+=(float val)
        {
            if (data.empty() || data[0].empty())
                throw std::runtime_error("the array is empty");
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data[i].size(); j++)
                    data[i][j] += val;
        }

        void operator+=(double val)
        {
            if (data.empty() || data[0].empty())
                throw std::runtime_error("the array is empty");
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data[i].size(); j++)
                    data[i][j] += val;
        }

        void operator+=(char val)
        {
            if (data.empty() || data[0].empty())
                throw std::runtime_error("the array is empty");
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data[i].size(); j++)
                    data[i][j] += static_cast<int>(val);
        }

        void operator-=(int val)
        {
            if (data.empty() || data[0].empty())
                throw std::runtime_error("the array is empty");
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data[i].size(); j++)
                    data[i][j] -= val;
        }

        void operator-=(float val)
        {
            if (data.empty() || data[0].empty())
                throw std::runtime_error("the array is empty");
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data[i].size(); j++)
                    data[i][j] -= val;
        }

        void operator-=(double val)
        {
            if (data.empty() || data[0].empty())
                throw std::runtime_error("the array is empty");
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data[i].size(); j++)
                    data[i][j] -= val;
        }

        void operator-=(char val)
        {
            if (data.empty() || data[0].empty())
                throw std::runtime_error("the array is empty");
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data[i].size(); j++)
                    data[i][j] -= static_cast<int>(val);
        }

        void operator*=(int val)
        {
            if (data.empty() || data[0].empty())
                throw std::runtime_error("the array is empty");
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data[i].size(); j++)
                    data[i][j] *= val;
        }

        void operator*=(float val)
        {
            if (data.empty() || data[0].empty())
                throw std::runtime_error("the array is empty");
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data[i].size(); j++)
                    data[i][j] *= val;
        }

        void operator*=(double val)
        {
            if (data.empty() || data[0].empty())
                throw std::runtime_error("the array is empty");
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data[i].size(); j++)
                    data[i][j] *= val;
        }

        void operator*=(char val)
        {
            if (data.empty() || data[0].empty())
                throw std::runtime_error("the array is empty");
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data[i].size(); j++)
                    data[i][j] *= static_cast<int>(val);
        }

        void operator/=(int val)
        {
            if (data.empty() || data[0].empty())
                throw std::runtime_error("the array is empty");
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data[i].size(); j++)
                    data[i][j] /= val;
        }

        void operator/=(float val)
        {
            if (data.empty() || data[0].empty())
                throw std::runtime_error("the array is empty");
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data[i].size(); j++)
                    data[i][j] /= val;
        }

        void operator/=(double val)
        {
            if (data.empty() || data[0].empty())
                throw std::runtime_error("the array is empty");
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data[i].size(); j++)
                    data[i][j] /= val;
        }

        void operator/=(char val)
        {
            if (data.empty() || data[0].empty())
                throw std::runtime_error("the array is empty");
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data[i].size(); j++)
                    data[i][j] /= val;
        }

        void operator^=(int val)
        {
            if (data.empty() || data[0].empty())
                throw std::runtime_error("the array is empty");
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data[i].size(); j++)
                    data[i][j] ^= val;
        }

        void operator^=(float val)
        {
            if (data.empty() || data[0].empty())
                throw std::runtime_error("the array is empty");
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data[i].size(); j++)
                    data[i][j] ^= val;
        }

        void operator^=(double val)
        {
            if (data.empty() || data[0].empty())
                throw std::runtime_error("the array is empty");
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data[i].size(); j++)
                    data[i][j] ^= val;
        }

        void operator^=(char val)
        {
            if (data.empty() || data[0].empty())
                throw std::runtime_error("the array is empty");
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data[i].size(); j++)
                    data[i][j] ^= static_cast<int>(val);
        }
        ~dynamic_v2d() = default;
    };
}

#endif // OPENUDT___UDT_DYNAMIC__DYANMIC_V2D__HPP