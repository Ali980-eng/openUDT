#include <iostream>
#include <vector>
#include <initializer_list>
#include <string>

#pragma once
#ifndef OPENUDT___BASIC___LIST_HPP
#define OPENUDT___BASIC___LIST_HPP

namespace udt
{

    template <typename T>
    class list
    {
    private:
        T *arr;
        bool size_set = true;
        size_t max_size;
        size_t length;

    public:
        list()
        {
            max_size = -1;
            length = 0;
            size_set = false;
        }

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

        inline constexpr bool empty() const noexcept { return length == 0; }

        inline constexpr bool full() const noexcept
        {
            if (max_size == -1)
                std::cerr << "the array is dynamic allocation,\n so no max size available" << std::endl;
            return length == max_size;
        }

        inline constexpr int size() const noexcept { return length; }

        inline constexpr size_t capacity() const noexcept { return max_size; }

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

        int search(T element) const noexcept
        {
            for (size_t i = 0; i < length; i++)
            {
                if (arr[i] == element)
                    return i;
            }
            return -1;
        }

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

        void update(int pos, T element)
        {
            if (pos < 0 || pos >= length)
                throw std::out_of_range("pos parameter is bigger then length or less than zero");
            else
                arr[pos] = element;
        }

        int get(int pos) const
        {
            if (pos < 0 || pos > length)
                throw std::out_of_range("pos parameter is bigger then length or less than zero");
            return arr[pos];
        }

        inline constexpr void clear() noexcept { length = 0; }

        ~LIST() noexcept { delete[] arr; }
    };

}

#endif // OPENUDT___BASIC___LIST_HPP