#include "dynamic_f.hpp"
#include <vector>
#include <cmath>
#include <functional>

#pragma once
#ifndef OPENUDT___CORE_DYNAMIC__DYANMIC_V__HPP
#define OPENUDT___CORE_DYNAMIC__DYANMIC_V__HPP

namespace udt
{
    /**
     * @class dynamic_v
     * @brief Vector container for dynamic type elements with optional fixed-size constraint.
     *
     * @details A 1D vector wrapper around std::vector<dynamic> that provides dynamic
     * type storage with optional capacity constraints. Elements can be of mixed types
     * (bool, char, int, float, double) as each element is a `dynamic` type.
     *
     * Features:
     * - Dynamic container for heterogeneous type storage
     * - Optional fixed-size mode for capacity-constrained vectors
     * - Standard vector interface (push_back, pop_back, etc.)
     * - Random access to elements
     * - Type introspection via type_vector()
     *
     * Storage Model:
     * - std::vector<dynamic> data: underlying storage for dynamic elements
     * - bool fixed_size: flag indicating if vector is capacity-constrained
     * - size_t dsize: maximum capacity when fixed_size is true (or -1 when dynamic)
     *
     * Size Modes:
     * | Mode | fixed_size | dsize | Behavior |
     * |------|-----------|-------|----------|
     * | Dynamic | false | -1 (unchanged) | Standard std::vector growth |
     * | Fixed | true | N | Capacity fixed at N elements |
     *
     * @note Elements are stored as `dynamic` type objects, each maintaining type information.
     * @note Fixed-size mode prevents push operations once capacity is reached.
     * @note Type information is preserved for each element (accessible via type_vector()).
     * @note Not thread-safe. External synchronization required for concurrent access.
     *
     * @see dynamic - Individual dynamic type holder
     * @see dynamic_v2d - 2D vector variant
     * @see dynamic_v3d - 3D vector variant
     */
    class dynamic_v
    {
    private:
        /// @brief Flag indicating if vector capacity is fixed
        bool fixed_size = false;
        /// @brief Maximum capacity when fixed_size=true (-1 when dynamic)
        size_t dsize = -1;
        /// @brief Underlying vector storage for dynamic type elements
        std::vector<dynamic_f> data;

    public:
        /**
         * @brief Default constructor - creates empty dynamic vector.
         *
         * Initializes a dynamic_v in dynamic (unconstrained) mode with no elements.
         * The vector will grow as needed when elements are added.
         *
         * @post fixed_size = false, dsize = -1, data.empty() = true, data.capacity() >= 0
         */
        dynamic_v()
        {
            fixed_size = false;
            dsize = -1;
            data = {};
        }

        /**
         * @brief Constructs fixed-size vector with given capacity.
         *
         * Creates a dynamic_v in fixed-size mode with initial capacity constraint.
         * No elements are added; the vector is empty but capacity-constrained.
         *
         * @param nsize The fixed capacity limit for this vector
         * @post fixed_size = true, dsize = nsize, data.empty() = true
         *
         * @throws May throw if nsize would cause memory allocation failure
         */
        explicit dynamic_v(const size_t &nsize) noexcept : dsize(nsize), fixed_size(true) {}

        /**
         * @brief Constructs from a std::vector<dynamic>.
         *
         * Copies the provided vector into the dynamic_v. The resulting object
         * is in dynamic (unconstrained) mode.
         *
         * @param vec The source std::vector<dynamic> to copy from
         *
         * @post fixed_size = false, data contains a copy of vec elements
         */
        dynamic_v(const std::vector<dynamic_f> &vec) noexcept : data(vec) {}

        /**
         * @brief Move constructor from std::vector<dynamic>.
         *
         * Transfers ownership of a std::vector<dynamic> into this dynamic_v.
         * The resulting object is in dynamic (unconstrained) mode.
         *
         * @param vec The source std::vector<dynamic> to move from
         *
         * @post fixed_size = false, data has taken ownership of vec contents
         */
        dynamic_v(std::vector<dynamic_f> &&vec) noexcept : data(std::move(vec)) {}

        /**
         * @brief Copy constructor for dynamic_v.
         *
         * Creates a copy of another dynamic_v, including size mode and capacity constraints.
         *
         * @param other The source dynamic_v to copy from
         *
         * @post This object is an independent copy of other with same fixed_size and dsize
         */
        dynamic_v(const dynamic_v &other) noexcept : data(other.data), dsize(other.dsize), fixed_size(other.fixed_size) {}

        /**
         * @brief Constructs from initializer list of dynamic elements.
         *
         * Creates a dynamic_v populated with elements from an initializer list.
         * The resulting object is in dynamic (unconstrained) mode.
         *
         * @param init The initializer list of dynamic elements
         *
         * @post fixed_size = false, data contains all elements from init
         */
        dynamic_v(std::initializer_list<dynamic_f> init) noexcept : data(init) {}

        /**
         * @brief Constructs fixed-size vector with initializer list.
         *
         * Creates a dynamic_v in fixed-size mode and populates it with initial elements.
         * The capacity is set to nsize but elements will not exceed that capacity.
         *
         * @param nsize The fixed capacity limit
         * @param init The initializer list of initial elements
         *
         * @post fixed_size = true, dsize = nsize, data contains elements from init
         *
         * @throws std::out_of_range if init.size() > nsize
         */
        dynamic_v(const size_t &nsize, std::initializer_list<dynamic_f> init) noexcept : dsize(nsize) { data = init; }

        /**
         * @brief Replace the vector data with a new vector.
         *
         * @param vec The new std::vector<dynamic> to use (moved into this object)
         *
         * @post data contains the contents of vec (moved), fixed_size remains unchanged
         */
        void set(std::vector<dynamic_f> &vec) noexcept { data = std::move(vec); }

        /**
         * @brief Convert from dynamic to fixed-size mode.
         *
         * Converts the vector from dynamic growth mode to fixed-size mode with the
         * specified capacity. After this call, no more elements can be added beyond
         * the specified size.
         *
         * @param s The fixed capacity limit (must be >= 0)
         *
         * @post fixed_size = true, dsize = s
         *
         * @throws std::length_error if vector is already in fixed_size mode
         * @throws std::invalid_argument if s < 0
         */
        void set_size(int s)
        {
            if (is_fixed())
                throw std::length_error("The vector is fixed size and can not be resized");
            if (s < 0)
                throw std::invalid_argument("Size must be non-negative");
            dsize = s;
            fixed_size = true;
        }

        /**
         * @brief Get a copy of the underlying vector.
         *
         * @return A copy of std::vector<dynamic> containing all elements
         */
        std::vector<dynamic_f> get() const noexcept { return data; }

        /**
         * @brief Get a vector of type names for all elements.
         *
         * Returns a vector of strings where each string is the type name of the
         * corresponding element in the vector.
         *
         * @return std::vector<std::string> with type names ("bool", "char", "int", "float", "double")
         *
         * @throws std::invalid_argument if the vector is empty
         */
        std::vector<std::string> type_vector() const
        {
            if (data.empty())
                throw std::invalid_argument("Empty type vector");
            std::vector<std::string> result;
            for (dynamic_f d : data)
                result.push_back(d.type());
            return result;
        }

        /**
         * @brief Get iterator to the beginning of the vector.
         *
         * @return Const iterator pointing to the first element
         */
        auto begin() const noexcept { return data.begin(); }

        /**
         * @brief Get iterator to the end of the vector.
         *
         * @return Const iterator pointing past the last element
         */
        auto end() const noexcept { return data.end(); }

        /**
         * @brief Get the size of the vector.
         *
         * For fixed-size vectors, returns the fixed capacity.
         * For dynamic vectors, returns the actual number of elements.
         *
         * @return The size (capacity if fixed_size, element count if dynamic)
         */
        size_t size() const noexcept
        {
            if (fixed_size)
                return dsize;
            return data.size();
        }

        size_t capacity() const noexcept { return data.capacity(); }

        bool is_fixed() const noexcept { return fixed_size; }

        bool empty() const noexcept { return data.empty(); }

        void push_back(const dynamic_f &val)
        {
            if (data.size() + 1 > dsize && fixed_size)
                throw std::out_of_range("The vector is full on push");
            data.push_back(val);
        }

        void push_front(const dynamic_f &val)
        {
            if (data.size() + 1 > dsize && fixed_size)
                throw std::out_of_range("The vector is full on push");
            data.insert(data.begin(), val);
        }

        void pop_back()
        {
            if (data.empty())
                throw std::out_of_range("The vector is empty on pop");
            data.pop_back();
        }

        void pop_front()
        {
            if (data.empty())
                throw std::out_of_range("The vector is empty on pop");
            data.erase(data.begin());
        }

        void insert(size_t index, const dynamic_f &val)
        {
            if (data.size() + 1 > dsize && fixed_size)
                throw std::out_of_range("The vector is full on push");
            if (index >= data.size())
                throw std::out_of_range("Index out of range");
            data.insert(data.begin() + index, val);
        }

        void insert_after(size_t index, const dynamic_f &val)
        {
            if (data.size() + 1 > dsize && fixed_size)
                throw std::out_of_range("The vector is full on push");
            if (index >= data.size())
                throw std::out_of_range("Index out of range");
            data.insert(data.begin() + index + 1, val);
        }

        void insert_after(std::function<bool(const dynamic_f &)> func, const dynamic_f &val)
        {
            if (data.size() + 1 > dsize && fixed_size)
                throw std::out_of_range("The vector is full on push");
            auto it = std::find_if(data.begin(), data.end(), func);
            if (it != data.end())
                data.insert(it + 1, val);
            else
                throw std::invalid_argument("No element found matching the condition");
        }

        void insert_before(size_t index, const dynamic_f &val)
        {
            if (data.size() + 1 > dsize && fixed_size)
                throw std::out_of_range("The vector is full on push");
            if (index >= data.size())
                throw std::out_of_range("Index out of range");
            data.insert(data.begin() + index, val);
        }

        void insert_before(std::function<bool(const dynamic_f &)> func, const dynamic_f &val)
        {
            if (data.size() + 1 > dsize && fixed_size)
                throw std::out_of_range("The vector is full on push");
            auto it = std::find_if(data.begin(), data.end(), func);
            if (it != data.end())
                data.insert(it, val);
            else
                throw std::invalid_argument("No element found matching the condition");
        }

        void clear() noexcept { data.clear(); }

        dynamic_f &at(size_t index)
        {
            if (index >= data.size())
                throw std::out_of_range("Index out of range");
            return data.at(index);
        }

        void erase(size_t index)
        {
            if (data.empty())
                throw std::invalid_argument("The vector is empty");
            if (index >= data.size())
                throw std::out_of_range("Index out of range");
            data.erase(data.begin() + index);
        }

        void erase(std::function<bool(const dynamic_f &)> func)
        {
            if (data.empty())
                throw std::invalid_argument("The vector is empty");
            auto it = std::remove_if(data.begin(), data.end(), func);
            data.erase(it, data.end());
        }

        void resize(size_t new_size) noexcept
        {
            dsize = new_size;
            fixed_size = true;
        }

        std::string type(size_t index)
        {
            if (index >= data.size())
                throw std::out_of_range("Index out of range");
            dynamic_f d(data[index]);
            return d.type();
        }

        size_t last_index() const
        {
            if (data.empty())
                throw std::out_of_range("The vector is empty");
            return data.size() - 1;
        }

        dynamic_f &operator[](size_t index)
        {
            if (index >= data.size())
                throw std::out_of_range("Index out of range");
            return data[index];
        }

        dynamic_v &operator=(const dynamic_v &other) noexcept
        {
            if (this != &other)
            {
                data = other.data;
                dsize = other.dsize;
                fixed_size = other.fixed_size;
            }
            return *this;
        }

        dynamic_v &operator=(std::vector<dynamic_f> &&vec)
        {
            if (vec.size() > dsize)
                throw std::invalid_argument("The size of the vector is bigger than the fixed size");
            data = std::move(vec);
            return *this;
        }

        void operator=(std::initializer_list<dynamic_f> init)
        {
            if (init.size() > dsize)
                throw std::invalid_argument("The size of the initializer list is bigger than the fixed size");
            data = init;
        }

        bool operator==(const dynamic_v &other) const noexcept { return data == other.data; }

        bool operator!=(const dynamic_v &other) const noexcept { return data != other.data; }

        bool operator==(const std::vector<dynamic_f> &other) const noexcept
        {
            dynamic_v temp = other;
            return data == temp.data;
        }

        bool operator!=(const std::vector<dynamic_f> &other) const noexcept
        {
            dynamic_v temp = other;
            return data != temp.data;
        }

        bool operator==(const std::initializer_list<dynamic_f> &temp) const noexcept
        {
            dynamic_v other = temp;
            return data == other.data;
        }

        bool operator!=(const std::initializer_list<dynamic_f> &temp) const noexcept
        {
            dynamic_v other = temp;
            return data != other.data;
        }

        void operator+=(int val)
        {
            if (data.empty())
                throw std::runtime_error("The vector is empty");
            for (int i = 0; i < data.size(); i++)
                data[i] += val;
        }

        void operator+=(float val)
        {
            if (data.empty())
                throw std::runtime_error("The vector is empty");
            for (int i = 0; i < data.size(); i++)
                data[i] += val;
        }

        void operator+=(double val)
        {
            if (data.empty())
                throw std::runtime_error("The vector is empty");
            for (int i = 0; i < data.size(); i++)
                data[i] += val;
        }

        void operator+=(char val)
        {
            if (data.empty())
                throw std::runtime_error("The vector is empty");
            for (int i = 0; i < data.size(); i++)
                data[i] += static_cast<int>(val);
        }

        void operator-=(int val)
        {
            if (data.empty())
                throw std::runtime_error("The vector is empty");
            for (int i = 0; i < data.size(); i++)
                data[i] -= val;
        }

        void operator-=(float val)
        {
            if (data.empty())
                throw std::runtime_error("The vector is empty");
            for (int i = 0; i < data.size(); i++)
                data[i] -= val;
        }

        void operator-=(double val)
        {
            if (data.empty())
                throw std::runtime_error("The vector is empty");
            for (int i = 0; i < data.size(); i++)
                data[i] -= val;
        }

        void operator-=(char val)
        {
            if (data.empty())
                throw std::runtime_error("The vector is empty");
            for (int i = 0; i < data.size(); i++)
                data[i] -= static_cast<int>(val);
        }

        void operator*=(int val)
        {
            if (data.empty())
                throw std::runtime_error("The vector is empty");
            for (int i = 0; i < data.size(); i++)
                data[i] *= val;
        }

        void operator*=(float val)
        {
            if (data.empty())
                throw std::runtime_error("The vector is empty");
            for (int i = 0; i < data.size(); i++)
                data[i] *= val;
        }

        void operator*=(double val)
        {
            if (data.empty())
                throw std::runtime_error("The vector is empty");
            for (int i = 0; i < data.size(); i++)
                data[i] *= val;
        }

        void operator*=(char val)
        {
            if (data.empty())
                throw std::runtime_error("The vector is empty");
            for (int i = 0; i < data.size(); i++)
                data[i] *= static_cast<int>(val);
        }

        void operator^=(int val)
        {
            if (data.empty())
                throw std::runtime_error("The vector is empty");
            for (int i = 0; i < data.size(); i++)
                data[i] ^= val;
        }

        void operator^=(float val)
        {
            if (data.empty())
                throw std::runtime_error("The vector is empty");
            for (int i = 0; i < data.size(); i++)
                data[i] ^= val;
        }

        void operator^=(double val)
        {
            if (data.empty())
                throw std::runtime_error("The vector is empty");
            for (int i = 0; i < data.size(); i++)
                data[i] ^= val;
        }

        void operator^=(char val)
        {
            if (data.empty())
                throw std::runtime_error("The vector is empty");
            for (int i = 0; i < data.size(); i++)
                data[i] ^= static_cast<int>(val);
        }
    };
}

#endif // OPENUDT___CORE_DYNAMIC__DYANMIC_V__HPP
