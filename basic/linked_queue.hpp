#include <iostream>
#include <vector>
#include <string>
#include <initializer_list>

#pragma once
#ifndef OPENUDT___BASIC___LINKED_QUEUE_HPP
#define OPENUDT___BASIC___LINKED_QUEUE_HPP

namespace udt
{

    template <typename T>
    class linked_queue
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
        linked_queue()
        {
            front_ptr = rear_ptr = nullptr;
            length = 0;
        }

        linked_queue(T element)
        {
            front_ptr = new node;
            front_ptr->item = element;
            front_ptr->next = nullptr;
            rear_ptr = front_ptr;
            length++;
        }

        linked_queue(std::initializer_list<T> list)
        {
            for (T element : list)
                enqueue(element);
        }

        inline bool is_empty() const noexcept
        {
            if (rear_ptr == nullptr)
                return true;
            return false;
        }

        void enqueue(T element) noexcept
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

        void dequeue()
        {
            if (is_empty())
            {
                throw std::invalid_argument("empty queue can\'t dequeue");
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
                throw std::invalid_argument("empty queue");
            return front_ptr->item;
        }

        inline T get_rear() const
        {
            if (is_empty())
                throw std::invalid_argument("empty queue");
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
                enqueue(element);
        }

        void operator=(const std::string &s)
        {
            clear();
            for (const char &c : s)
                enqueue(static_cast<T>(c));
        }

        inline void operator<<(T element) { enqueue(element); }

        inline void operator<<(std::vector<T> &elements)
        {
            enqueue(elements[elements.size() - 1]);
            elements.pop_back();
        }

        inline void operator<<(std::string &s)
        {
            enqueue(s[s.size() - 1]);
            s.pop_back();
        }

        inline void operator>>(T &element)
        {
            element = get_front();
            dequeue();
        }

        inline void operator>>(std::vector<T> &elements)
        {
            elements.push_back(get_front());
            dequeue();
        }

        inline void operator>>(std::string &s)
        {
            s += static_cast<char>(get_front());
            dequeue();
        }

        ~linked_queue() { clear(); }
    };
}

#endif // OPENUDT___BASIC___LINKED_QUEUE_HPP