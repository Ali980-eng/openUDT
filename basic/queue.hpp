#include "metaCore/lite/io.hpp"

#pragma once
#ifndef OPENUDT___BASIC___QUEUE_HPP
#define OPENUDT___BASIC___QUEUE_HPP

namespace udt
{

    template <typename T>
    class queue
    {
    private:
        size_t rear;
        size_t front;
        int length;
        T *arr;
        int maxSize;

    public:
        queue(int ArrSize)
        {
            if (ArrSize < 0)
                throw invalid_argument("the size have to be bigger then zero");
            front = 0;
            arr = new T[ArrSize];
            maxSize = ArrSize;
            rear = maxSize - 1;
            length = 0;
        }

        queue(initializer_list<T> &vec) noexcept : arr(vec) {};

        inline constexpr bool empty() const noexcept { return length == 0; }

        inline constexpr bool full() const noexcept { return length == maxSize; }

        void que(T element) noexcept
        {
            if (full())
                meta::lite::io::println_error("Queue Full Can't Enqueue");
            else
            {
                rear = (rear + 1) % maxSize;
                arr[rear] = element;
                length++;
            }
        }

        void dque() noexcept
        {
            if (empty())
                meta::lite::io::println_error("Empty Queue Can't Dequeue");
            else
            {
                front = (front + 1) % maxSize;
                length--;
            }
        }

        T get_front() const
        {
            if (empty())
            {
                meta::lite::io::println_error("the queue is empty, no elements to get");
                throw std::invalid_argument("Queue is empty, no front element available.");
            }
            return arr[front];
        }

        void get_front(T &element) const noexcept
        {
            if (empty())
            {
                meta::lite::io::println_error("the queue is empty, no elements to get");
                return;
            }
            element = arr[front];
        }

        T get_rear() const
        {
            if (empty())
            {
                meta::lite::io::println_error("the queue is empty, no elements to get");
                throw std::invalid_argument("Queue is empty, no rear element available.");
            }
            return arr[rear];
        }

        void print() const noexcept
        {
            if (empty())
            {
                meta::lite::io::println_error("the queue is empty, no elements to print");
                return;
            }
            std::cout << "Queue elements: ";
            for (size_t i = 0; i < length; i++)
                cout << arr[(front + i) % maxSize] << " ";
            std::cout << '\n';
        }

        T search(T element) const noexcept
        {
            if (!empty())
            {
                for (int i = front; i != rear; i = (i + 1) % maxSize)
                {
                    if (arr[i] == element)
                        return i;
                }
                if (arr[rear] == element)
                    return rear;
            }
            else
                meta::lite::io::println_error("Q is empty ! ");
            return -1;
        }

        void operator=(const vector<T> &vec)
        {
            if (!vec.empty())
            {
                for (int i = 0; i < vec.size(); i++)
                    addQueue(vec[i]);
            }
            else
                meta::lite::io::println_error("Empty Error");
        }

        void operator=(const queue &other) noexcept
        {
            if (this != &other)
            {
                front = other.front;
                rear = other.rear;
                length = other.length;
                for (size_t i = 0; i < maxSize; i++)
                    arr[i] = other.arr[i];
            }
        }

        T operator>>(T &element)
        {
            if (empty())
            {
                meta::lite::io::println_error("the queue is empty, no elements to read");
                throw std::invalid_argument("Queue is empty, no elements to read.");
            }
            element = get_front();
            deleteQueue();
            return element;
        }

        T operator<<(const T &element)
        {
            if (full())
            {
                meta::lite::io::println_error("Queue Full Can't Enqueue");
                throw std::out_of_range("Queue is full, cannot add more elements.");
            }
            addQueue(element);
            return element;
        }

        ~queue() = default;
    };

}

#endif // OPENUDT___BASIC___QUEUE_HPP