#include <iostream>
#include <initializer_list>
#include <vector>
#include "cfrost/structure.h"

#pragma once
#ifndef OPENUDT___BASIC___LINKED_LIST_HPP
#define OPENUDT___BASIC___LINKED_LIST_HPP

namespace udt
{

    /// @brief Represents a singly linked list of values.
    ///
    /// The list supports insertion, removal, lookup, replacement, and traversal
    /// operations while preserving the existing implementation semantics.
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
        /// @brief Constructs an empty linked list.
        linked_list() noexcept
        {
            first = nullptr;
            last = nullptr;
            length = 0;
        }

        /// @brief Constructs a linked list from an initializer list.
        ///
        /// @param list The values to insert in order.
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

        /// @brief Constructs a linked list from a vector.
        ///
        /// @param list The values to insert in order.
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

        /// @brief Copies the contents of another linked list.
        ///
        /// @param list The linked list to copy.
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

        /// @brief Copies the contents of another linked list into this one.
        ///
        /// @param list The linked list to copy.
        /// @return A reference to this linked list.
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

        /// @brief Returns the element at the specified index.
        ///
        /// @param index The zero-based position to access.
        /// @return The value at the given index, or a default value if out of range.
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

        /// @brief Returns the last element in the list.
        constexpr T last_item() noexcept { return last->item; }

        /// @brief Returns the first element in the list.
        constexpr T first_item() noexcept { return first->item; }

        /// @brief Checks whether the list is empty.
        constexpr bool empty() noexcept { return length == 0; }

        /// @brief Returns the current number of elements in the list.
        constexpr size_t size() noexcept { return length; }

        /// @brief Inserts an element at the front of the list.
        ///
        /// @param element The value to insert.
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

        /// @brief Inserts an element at the end of the list.
        ///
        /// @param element The value to insert.
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

        /// @brief Inserts an element at the specified position.
        ///
        /// @param pos The zero-based insertion position.
        /// @param element The value to insert.
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

        /// @brief Removes the first element from the list.
        procedure(remove_first) noexcept
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

        /// @brief Removes the last element from the list.
        procedure(remove_last) noexcept
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

        /// @brief Removes the first occurrence of the specified element.
        ///
        /// @param element The value to remove.
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

        /// @brief Checks whether the specified value exists in the list.
        ///
        /// @param element The value to search for.
        /// @return true if the value is found, false otherwise.
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

        /// @brief Finds the index of the specified element.
        ///
        /// @param element The value to locate.
        /// @return The zero-based index of the element, or 0 if it was not found.
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

        /// @brief Clears the stored values while keeping the nodes intact.
        procedure(clear_items) noexcept
        {
            node *temp = first;
            while (temp != nullptr)
            {
                temp->item = T();
                temp = temp->next;
            }
        }

        /// @brief Removes all nodes from the list and resets its state.
        procedure(clear) noexcept
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

        /// @brief Replaces the value stored at the first node.
        ///
        /// @param newElement The replacement value.
        void replaceFirst(T newElement) noexcept
        {
            if (empty())
            {
                std::cerr << "Empty Error: empty list cann't replace any item.\n";
                return;
            }
            first->item = newElement;
        }

        /// @brief Replaces the value stored at the last node.
        ///
        /// @param newElement The replacement value.
        void replaceLast(T newElement) noexcept
        {
            if (empty())
            {
                std::cerr << "Empty Error: empty list cann't replace any item.\n";
                return;
            }
            last->item = newElement;
        }

        /// @brief Replaces the first occurrence of an old value with a new value.
        ///
        /// @param oldElement The value to replace.
        /// @param newElement The replacement value.
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

        /// @brief Replaces all occurrences of an old value with a new value.
        ///
        /// @param oldElement The value to replace.
        /// @param newElement The replacement value.
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

        /// @brief Reverses the order of the list.
        ///
        /// The operation runs in linear time.
        procedure(reverse) noexcept
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

        /// @brief Prints the list contents to the standard output stream.
        procedure(print) noexcept
        {
            const node *cur = first;
            while (cur != nullptr)
            {
                std::cout << cur->item << ' ';
                cur = cur->next;
            }
            std::cout << char(10);
        }

        /// @brief Returns the element at the given index using array-style access.
        ///
        /// @param index The zero-based position to access.
        /// @return The value stored at the given index, or a default value if out of range.
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
