#include <iostream>
#include <vector>
#include <string>
#include <initializer_list>

#pragma once
#ifndef OPENUDT___BASIC___QUE_HPP
#define OPENUDT___BASIC___QUE_HPP

namespace udt
{

    template <typename T>
    class que
    {
    private:
        struct node
        {
            T item;
            node *next;
        };
        node *front_ptr;
        node *rear_ptr;
        int length;

    public:
        que()
        {
            front_ptr = rear_ptr = nullptr;
            length = 0;
        }

        que(T element)
        {
            front_ptr = new node;
            front_ptr->item = element;
            front_ptr->next = nullptr;
            rear_ptr = front_ptr;
            length++;
        }

        que(std::initializer_list<T> list)
        {
            for (T element : list)
                enque(element);
        }

        inline bool is_empty() const noexcept
        {
            if (rear_ptr == nullptr)
                return true;
            return false;
        }

        void enque(T element) noexcept
        {
            if (is_empty())
            {
                front_ptr = new node;
                front_ptr->item = element;
                front_ptr->next = nullptr;
                rear_ptr = front_ptr;
            }
            else
            {
                node *new_ptr = new node;
                new_ptr->item = element;
                new_ptr->next = nullptr;
                rear_ptr->next = new_ptr;
                rear_ptr = new_ptr;
            }
            length++;
        }

        void deque()
        {
            if (is_empty())
            {
                throw std::invalid_argument("empty que can\'t deque");
            }
            else
            {
                node *temp_ptr = front_ptr;
                if (front_ptr == rear_ptr)
                {
                    rear_ptr = nullptr;
                    front_ptr = nullptr;
                    length--;
                }
                else
                {
                    front_ptr = front_ptr->next;
                    length--;
                }
                temp_ptr->next = nullptr;
                delete temp_ptr;
            }
        }

        inline T get_front() const
        {
            if (is_empty())
                throw std::invalid_argument("empty que");
            return front_ptr->item;
        }

        inline T get_rear() const
        {
            if (is_empty())
                throw std::invalid_argument("empty que");
            return rear_ptr->item;
        }

        void clear()
        {
            node *current;
            while (front_ptr != nullptr)
            {
                current = front_ptr;
                front_ptr = front_ptr->next;
                delete current;
            }
            rear_ptr = nullptr;
            length = 0;
        }

        void operator=(const std::vector<T> &elements)
        {
            clear();
            for (const T &element : elements)
                enque(element);
        }

        void operator=(const std::string &s)
        {
            clear();
            for (const char &c : s)
                enque(static_cast<T>(c));
        }

        inline void operator<<(T element) { enque(element); }

        inline void operator<<(std::vector<T> &elements)
        {
            enque(elements[elements.size() - 1]);
            elements.pop_back();
        }

        inline void operator<<(std::string &s)
        {
            enque(s[s.size() - 1]);
            s.pop_back();
        }

        inline void operator>>(T &element)
        {
            element = get_front();
            deque();
        }

        inline void operator>>(std::vector<T> &elements)
        {
            elements.push_back(get_front());
            deque();
        }

        inline void operator>>(std::string &s)
        {
            s += static_cast<char>(get_front());
            deque();
        }

        ~que() { clear(); }
    };
}

#endif // OPENUDT___BASIC___QUE_HPP