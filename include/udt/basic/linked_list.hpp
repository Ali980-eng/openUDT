#include <iostream>
#include <initializer_list>
#include <vector>

#pragma once
#ifndef OPENUDT___BASIC___LINKED_LIST_HPP
#define OPENUDT___BASIC___LINKED_LIST_HPP

namespace udt
{

    template <typename T>
    class linked_list
    {
    private:
        struct node
        {
            T item;
            node *next;
        };

        node *first;

        node *last;

        size_t length;

    public:
        linked_list() noexcept
        {
            first = nullptr;
            last = nullptr;
            length = 0;
        }

        linked_list(std::initializer_list<T> list) noexcept
        {
            first = nullptr;
            last = nullptr;
            length = 0;
            for (const T &value : list)
            {
                insertLast(value);
            }
        }

        linked_list(const std::vector<T> &list) noexcept
        {
            first = nullptr;
            last = nullptr;
            length = 0;
            for (const T &value : list)
            {
                insertLast(value);
            }
        }

        linked_list(const linked_list<T> &list) noexcept
        {
            first = nullptr;
            last = nullptr;
            length = 0;
            const node *current = list.first;
            while (current != nullptr)
            {
                insertLast(current->item);
                current = current->next;
            }
        }

        linked_list<T> &operator=(const linked_list<T> &list) noexcept
        {
            if (this != &list)
            {
                clear();
                const node *current = list.first;
                while (current != nullptr)
                {
                    insertLast(current->item);
                    current = current->next;
                }
            }
            return *this;
        }

        T at(size_t index) noexcept
        {
            if (index >= length)
            {
                std::cerr << "Out Of Range: index exceed the length of the list.\n";
                return T();
            }
            else if (index == 0)
            {
                return first->item;
            }
            else if (index == length - 1)
            {
                return last->item;
            }
            else
            {
                const node *curr = first;
                for (size_t i = 0; i < index; i++)
                {
                    curr = curr->next;
                }
                return curr->item;
            }
        }

        constexpr T last_item() noexcept { return last->item; }

        constexpr T first_item() noexcept { return first->item; }

        constexpr bool empty() noexcept { return length == 0; }

        constexpr size_t size() noexcept { return length; }

        void insertFirst(T element) noexcept
        {
            node *newNode = new node;
            newNode->item = element;
            if (length == 0)
            {
                first = newNode;
                last = newNode;
                newNode->next = nullptr;
            }
            else
            {
                newNode->next = first;
                first = newNode;
            }
            length++;
        }

        void insertLast(T element) noexcept
        {
            node *newNode = new node;
            newNode->item = element;
            if (length == 0)
            {
                first = newNode;
                last = newNode;
                newNode->next = nullptr;
            }
            else
            {
                newNode->next = nullptr;
                last->next = newNode;
                last = newNode;
            }
            length++;
        }

        void insert(size_t pos, T element) noexcept
        {
            if (pos > length)
                std::cerr << "out of range error: The position of the element exceeds the length of the list.\n";
            else if (pos == 0)
                insertFirst(element);
            else if (pos == length)
                insertLast(element);
            else
            {
                node *cur = first;
                for (size_t i = 0; i < pos - 1; i++)
                {
                    cur = cur->next;
                }
                node *newNode = new node;
                newNode->item = element;
                newNode->next = cur->next;
                cur->next = newNode;
                length++;
            }
        }

        void removeFirst() noexcept
        {
            if (length == 0)
            {
                std::cerr << "Empty Error: no element in the list to remove.\n";
            }
            else if (length == 1)
            {
                delete first;
                last = first = nullptr;
                length = 0;
            }
            else
            {
                node *curr = first;
                first = first->next;
                delete curr;
                length--;
            }
        }

        void removeLast() noexcept
        {
            if (length == 0)
            {
                std::cerr << "Empty Error: no element in the list to remove.\n";
            }
            else if (length == 1)
            {
                delete first;
                last = first = nullptr;
                length = 0;
            }
            else if (length == 2)
            {
                delete last;
                last = first;
                first->next = nullptr;
                length = 1;
            }
            else
            {
                node *curr = first->next;
                node *prev = first;
                while (curr != last)
                {
                    prev = curr;
                    curr = curr->next;
                }
                delete curr;
                prev->next = nullptr;
                last = prev;
                length--;
            }
        }

        void remove(T element) noexcept
        {
            if (empty())
            {
                std::cerr << "Empty Error: no element in the list to remove.\n";
                return;
            }
            if (first->item == element)
            {
                removeFirst();
                return;
            }
            else if (last->item == element)
            {
                removeLast();
                return;
            }
            else
            {
                node *curr = first->next;
                node *prev = first;
                while (curr != nullptr)
                {
                    if (curr->item == element)
                    {
                        prev->next = curr->next;
                        delete curr;
                        length--;
                        return;
                    }
                    prev = curr;
                    curr = curr->next;
                }
            }
            std::cerr << "Error: The element doesn't exist in the list.\n";
        }

        bool exist(T element) noexcept
        {
            const node *temp = first;
            while (temp != nullptr)
            {
                if (temp->item == element)
                    return true;
                temp = temp->next;
            }
            return false;
        }

        size_t where(T element) noexcept
        {
            const node *temp = first;
            size_t index = 0;
            while (temp != nullptr)
            {
                if (temp->item == element)
                    return index;
                temp = temp->next;
                index++;
            }
            std::cerr << "Error: this element don't exist.\n";
            return 0;
        }

        void clear_items() noexcept
        {
            node *temp = first;
            while (temp != nullptr)
            {
                temp->item = T();
                temp = temp->next;
            }
        }

        void clear() noexcept
        {
            node *temp = first;
            while (temp != nullptr)
            {
                first = first->next;
                delete temp;
                temp = first;
            }
            last = nullptr;
            length = 0;
        }

        void replaceFirst(T newElement) noexcept
        {
            if (empty())
            {
                std::cerr << "Empty Error: empty list cann't replace any item.\n";
                return;
            }
            first->item = newElement;
        }

        void replaceLast(T newElement) noexcept
        {
            if (empty())
            {
                std::cerr << "Empty Error: empty list cann't replace any item.\n";
                return;
            }
            last->item = newElement;
        }

        void replace(T oldElement, T newElement) noexcept
        {
            if (empty())
            {
                std::cerr << "Empty Error: empty list cann't replace any item.\n";
                return;
            }
            node *temp = first;
            while (temp != nullptr)
            {
                if (temp->item == oldElement)
                {
                    temp->item = newElement;
                    return;
                }
                temp = temp->next;
            }
            std::cerr << "No element found to replace.\n";
        }

        void replace_all(T oldElement, T newElement) noexcept
        {
            if (empty())
            {
                std::cerr << "Empty Error: empty list cann't replace any item.\n";
                return;
            }
            node *temp = first;
            while (temp != nullptr)
            {
                if (temp->item == oldElement)
                    temp->item = newElement;
                temp = temp->next;
            }
        }

        // The complexity is O(N)
        void reverse() noexcept
        {
            if (empty())
            {
                std::cerr << "Empty Error: cann't reverse empty list.\n";
            }
            else if (length == 1)
            {
                std::cerr << "Error: cann't reverse list with one element.\n";
            }
            else if (length == 2)
            {
                last->next = first;
                first->next = nullptr;
                node *temp = first;
                first = last;
                last = temp;
            }
            else
            {
                node *prev = nullptr;
                node *curr = first;
                node *next = nullptr;
                while (curr != nullptr)
                {
                    next = curr->next;
                    curr->next = prev;
                    prev = curr;
                    curr = next;
                }
                last = first;
                first = prev;
            }
        }

        template <typename U>
        friend std::ostream &operator<<(std::ostream &os, const linked_list<U> &value) noexcept
        {
            os << "list: {";
            const node *curr = value.first;
            for (size_t i = 0; i < value.length; ++i)
            {
                os << curr->item;
                if (i != value.length - 1)
                    os << ", ";
                curr = curr->next;
            }
            os << "}\n";
            return os;
        }

        void print() noexcept
        {
            const node *cur = first;
            while (cur != nullptr)
            {
                std::cout << cur->item << ' ';
                cur = cur->next;
            }
            std::cout << char(10);
        }

        T operator[](size_t index) noexcept
        {
            if (index >= length)
            {
                std::cerr << "Out Of Range: index exceed the length of the list.\n";
                return T();
            }
            else if (index == 0)
            {
                return first->item;
            }
            else if (index == length - 1)
            {
                return last->item;
            }
            else
            {
                const node *curr = first;
                for (size_t i = 0; i < index; i++)
                {
                    curr = curr->next;
                }
                return curr->item;
            }
        }

        ~linked_list()
        {
            node *current = first;
            while (current != nullptr)
            {
                node *next = current->next;
                delete current;
                current = next;
            }
        }
    };

}

#endif // OPENUDT___BASIC___LINKED_LIST_HPP
