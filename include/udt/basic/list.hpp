#include <iostream>
#include <vector>
#include <initializer_list>
#include <string>
#include "cfrost/structure.h"

#pragma once
#ifndef OPENUDT___BASIC___LIST_HPP
#define OPENUDT___BASIC___LIST_HPP

namespace udt
{

    /// @brief Represents a dynamic array-style list container.
    ///
    /// The class supports indexed access, insertion, removal, searching,
    /// and updating of elements using a contiguous storage model.
    template <typename T>
    class list
    {
    private:
        T *arr;
        bool size_set = true;
        size_t max_size;
        size_t length;

    public:
        /// @brief Constructs an empty dynamic list with no fixed capacity.
        list()
        {
            max_size = -1;
            length = 0;
            size_set = false;
        }

        /// @brief Constructs a list with a predefined capacity.
        ///
        /// @param s The initial capacity.
        list(size_t s)
        {
            max_size = s;
            length = 0;
            arr = new T[max_size];
            size_set = false;
        }

        list(int s)
        {
            if (s < 0)
            {
                std::cerr << "the size can not be zero or less\n";
                s *= -1;
            }
            max_size = static_cast<size_t>(s);
            length = 0;
            arr = new T[max_size];
        }

        list(const std::vector<T> &v) noexcept
        {
            arr = new T[v.size()];
            max_size = v.size();
            length = v.size();
            size_set = false;
            for (int i = 0; i < v.size(); i++)
                *(arr + i) = v[i];
        }

        list(std::initializer_list<T> &&list) noexcept
        {
            arr = new T[list.size()];
            max_size = list.size();
            length = list.size();
            size_set = false;
            for (int i = 0; i < list.size(); i++)
                *(arr + i) = *(list.begin() + i);
        }

        void set(const std::vector<T> &v) noexcept
        {
            if (v.empty())
                return;
            arr = new T[v.size()];
            max_size = v.size();
            length = v.size();
            size_set = false;
            for (int i = 0; i < v.size(); i++)
                *(arr + i) = v[i];
        }

        void set(const std::vector<T> &v, int s) noexcept
        {
            if (v.empty())
                return;
            if (s < 0)
            {
                std::cerr << "the max size can not be zero or less\n";
                s *= -1;
            }
            arr = new T[s];
            max_size = s;
            length = s;
            for (int i = 0; i < s; i++)
                *(arr + i) = v[i];
        }

        void set(size_t s)
        {
            if (!size_set)
                throw std::invalid_argument("size reset error");
            if (s < 0)
                throw std::invalid_argument("the size can not be zero or less");
            max_size = s;
            size_set = false;
        }

        void set(int s)
        {
            if (!size_set)
                throw std::invalid_argument("size reset error");
            if (s < 0)
                throw std::invalid_argument("the size can not be zero or less");
            max_size = static_cast<size_t>(s);
            size_set = false;
        }

        /// @brief Checks whether the list is empty.
        inline constexpr bool empty() const noexcept { return length == 0; }

        /// @brief Checks whether the list has reached its capacity.
        inline constexpr bool full() const noexcept
        {
            if (max_size == -1)
                std::cerr << "the array is dynamic allocation,\n so no max size available" << std::endl;
            return length == max_size;
        }

        /// @brief Returns the current number of stored elements.
        inline constexpr int size() const noexcept { return length; }

        /// @brief Returns the list capacity.
        inline constexpr size_t capacity() const noexcept { return max_size; }

        /// @brief Inserts an element at the specified position.
        ///
        /// @param pos The zero-based insertion position.
        /// @param element The value to insert.
        void insert(int pos, T element)
        {
            if (full())
                throw std::length_error("list full");
            else if (pos < 0 || pos > length)
                throw std::out_of_range("pos parameter is bigger then length or less than zero");
            else
                for (int i = length; i > pos; i--)
                    arr[i] = arr[i - 1];
            arr[pos] = element;
            length++;
        }

        /// @brief Removes the element at the specified position.
        ///
        /// @param pos The zero-based index of the element to remove.
        void remove(int pos)
        {
            if (empty())
                throw std::invalid_argument("Empty list");
            else if (pos < 0 || pos > length)
                throw std::out_of_range("pos parameter is bigger then length or less than zero");
            else
                for (int i = pos; i < length; i++)
                    arr[i] = arr[i + 1];
            length--;
        }

        /// @brief Searches for the first occurrence of an element.
        ///
        /// @param element The value to locate.
        /// @return The index of the element, or -1 if it was not found.
        int search(T element) const noexcept
        {
            for (size_t i = 0; i < length; i++)
            {
                if (arr[i] == element)
                    return i;
            }
            return -1;
        }

        /// @brief Appends an element to the end of the list.
        ///
        /// @param element The value to append.
        void push_back(T element)
        {
            if (full())
                throw std::invalid_argument("The list is full on push");
            else
                arr[length] = element;
            length++;
        }

        void inseratNoDuplicate(int pos, T element)
        {
            if (search(element) == -1)
                insert(pos, element);
        }

        /// @brief Updates the value stored at the specified position.
        ///
        /// @param pos The zero-based index to update.
        /// @param element The replacement value.
        void update(int pos, T element)
        {
            if (pos < 0 || pos >= length)
                throw std::out_of_range("pos parameter is bigger then length or less than zero");
            else
                arr[pos] = element;
        }

        /// @brief Returns the element stored at the specified position.
        ///
        /// @param pos The zero-based index.
        int get(int pos) const
        {
            if (pos < 0 || pos > length)
                throw std::out_of_range("pos parameter is bigger then length or less than zero");
            return arr[pos];
        }

        /// @brief Clears all stored elements from the list.
        inline constexpr procedure(clear) noexcept { length = 0; }

        ~list() noexcept { delete[] arr; }
    };

}

#endif // OPENUDT___BASIC___LIST_HPP