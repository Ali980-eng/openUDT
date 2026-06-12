#pragma once
#ifndef OPENUDT___UDT_ARRAY_QUEUE_HPP
#define OPENUDT___UDT_ARRAY_QUEUE_HPP

namespace udt
{

    template <typename T>
    class queue_arr
    {
    private:
        size_t rear;
        size_t front;
        int length;
        T *arr;
        int maxSize;

    public:
        queue_arr(int ArrSize)
        {
            if (ArrSize < 0)
                throw invalid_argument("the size have to be bigger then zero");
            front = 0;
            arr = new T[ArrSize];
            maxSize = ArrSize;
            rear = maxSize - 1;
            length = 0;
        }
        queue_arr(initializer_list<T> &vec) : arr(vec) {};
        constexpr bool empty() const noexcept
        {
            return length == 0;
        }
        constexpr bool full() const noexcept
        {
            return length == maxSize;
        }
        void addQueue(T element) noexcept
        {
            if (full())
                io::println_error("Queue Full Can't Enqueue");
            else
            {
                rear = (rear + 1) % maxSize;
                arr[rear] = element;
                length++;
            }
        }
        void deleteQueue() noexcept
        {
            if (empty())
                io::println_error("Empty Queue Can't Dequeue");
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
                io::println_error("the queue is empty, no elements to get");
                throw std::invalid_argument("Queue is empty, no front element available.");
            }
            return arr[front];
        }
        void get_front(T &element) const noexcept
        {
            if (empty())
            {
                io::println_error("the queue is empty, no elements to get");
                return;
            }
            element = arr[front];
        }
        T get_rear() const
        {
            if (empty())
            {
                io::println_error("the queue is empty, no elements to get");
                throw std::invalid_argument("Queue is empty, no rear element available.");
            }
            return arr[rear];
        }
        void print() const noexcept
        {
            if (empty())
            {
                io::println_error("the queue is empty, no elements to print");
                return;
            }
            cout << "Queue elements: ";
            for (size_t i = 0; i < length; i++)
                cout << arr[(front + i) % maxSize] << " ";
            cout << endl;
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
                io::println_error("Q is empty ! ");
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
                io::println_error("Empty Error");
        }
        void operator=(const queue_arr &other) noexcept
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
                io::println_error("the queue is empty, no elements to read");
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
                io::println_error("Queue Full Can't Enqueue");
                throw std::out_of_range("Queue is full, cannot add more elements.");
            }
            addQueue(element);
            return element;
        }
        ~queue_arr() = default;
    };

}

#endif // OPENUDT___UDT_ARRAY_QUEUE_HPP