#include <iostream>
#include <initializer_list>
#include <vector>
#include <string>

#pragma once
#ifndef OPENUDT___BASIC___DOUBLE_LINKED_LIST_HPP
#define OPENUDT___BASIC___DOUBLE_LINKED_LIST_HPP

namespace udt
{

    template <typename T>
    class double_linked_list
    {
    private:
        struct node
        {
            node *next;
            node *prev;
            T item;
        };
        node *first = nullptr;
        node *last = nullptr;
        size_t length = 0;

    public:
        linked_list() = default;

        linked_list(std::initializer_list<T> list)
        {
            for (const T &value : list)
                insert_last(value);
        }

        linked_list(const std::vector<T> &v)
        {
            for (const T &value : v)
                insert_last(value);
        }

        linked_list(const linked_list<T> &list)
        {
            const node *temp = list->first;
            while (temp != nullptr)
            {
                insert_last(temp->item);
                temp = temp->next;
            }
        }

        constexpr bool empty() const noexcept
        {
            return length == 0;
        }

        constexpr size_t size() const noexcept
        {
            return length;
        }

        constexpr T last_item() noexcept
        {
            return last->item;
        }

        constexpr T first_item() noexcept
        {
            return first->item;
        }

        void insert_first(const T &element)
        {
            node *newNode = new node{nullptr, nullptr, element};
            if (empty())
            {
                first = last = newNode;
            }
            else
            {
                newNode->next = first;
                first->prev = newNode;
                first = newNode;
            }
            length++;
        }

        void insert_last(const T &element)
        {
            node *newNode = new node{nullptr, nullptr, element};
            if (empty())
            {
                first = last = newNode;
            }
            else
            {
                newNode->prev = last;
                last->next = newNode;
                last = newNode;
            }
            length++;
        }

        void insert_before(T element, T befEle)
        {
            if (empty())
            {
                std::cerr << "Empty Error: no elements exist in this list.\n";
                return;
            }
            if (first->item == element)
            {
                insert_first(befEle);
                return;
            }
            node *temp = first->next;
            while (temp != nullptr)
            {
                if (temp->item == element)
                {
                    node *bef = temp->prev;
                    node *newNode = new node{temp, bef, befEle};
                    bef->next = newNode;
                    temp->prev = newNode;
                    length++;
                    return;
                }
                temp = temp->next;
            }
            std::cerr << "no element exist like this element: " << element;
        }

        void insert_after(T element, T aftEle)
        {
            if (empty())
            {
                std::cerr << "Empty Error: no elements exist in the list.\n";
                return;
            }
            if (last->item == element)
            {
                insert_last(aftEle);
                return;
            }
            node *temp = last->prev;
            while (temp != nullptr)
            {
                if (temp->item == element)
                {
                    node *aft = temp->next;
                    node *newNode = new node{aft, temp, aftEle};
                    aft->prev = newNode;
                    temp->next = newNode;
                    length++;
                    return;
                }
                temp = temp->prev;
            }
            std::cerr << "no element exist like this element: " << element;
        }

        void pop_first()
        {
            if (empty())
            {
                std::cerr << "Empty Error: The list is empty on pop.\n";
                return;
            }
            if (length == 1)
            {
                node *temp = first;
                last = nullptr;
                first = nullptr;
                delete temp;
                length = 0;
                return;
            }
            node *temp = first;
            first = first->next;
            first->prev = nullptr;
            delete temp;
            length--;
        }

        void pop_last()
        {
            if (empty())
            {
                std::cerr << "Empty Error: The list is empty on pop.\n";
                return;
            }
            if (length == 1)
            {
                node *temp = first;
                last = nullptr;
                first = nullptr;
                delete temp;
                length = 0;
                return;
            }
            node *temp = last;
            last = last->prev;
            last->next = nullptr;
            delete temp;
            length--;
        }

        void replace(T oldEle, T newEle)
        {
            if (empty())
            {
                std::cerr << "Empty Error: can't replace item in empty list.\n";
                return;
            }
            else if (first->item == oldEle)
            {
                first->item = newEle;
                return;
            }
            node *temp = first->next;
            while (temp != nullptr)
            {
                if (temp->item == oldEle)
                {
                    temp->item = newEle;
                    return;
                }
                temp = temp->next;
            }
            std::cerr << "Error: no element found to replace.\n";
        }

        void replace_all(T oldEle, T newEle)
        {
            if (empty())
            {
                std::cerr << "Empty Error: can't replace item in empty list.\n";
                return;
            }
            const node *temp1 = first;
            const node *temp2 = last;
            while (temp1 != temp2 && temp1->prev != temp2)
            {
                if (temp1->item == oldEle)
                    temp1->item = newEle;
                if (temp2->item == oldEle)
                    temp2->item = newEle;
                temp1 = temp1->next;
                temp2 = temp2->prev;
            }
        }

        void remove(T element)
        {
            if (empty())
            {
                std::cerr << "Empty Error: can't remove elements form empty list.\n";
            }
            else if (length == 1 && element == first->item)
            {
                node *temp = first;
                last = nullptr;
                first = nullptr;
                delete temp;
                length--;
            }
            else if (first->item == element)
            {
                pop_first();
            }
            else if (last->item == element)
            {
                pop_last();
            }
            else
            {
                node *temp1 = first;
                node *temp2 = last;
                while (temp1 != temp2 && temp1->prev != temp2)
                {
                    if (temp1->item == element)
                    {
                        node *prev = temp1->prev;
                        node *next = temp1->next;
                        prev->next = next;
                        next->prev = prev;
                        delete temp1;
                        length--;
                        return;
                    }
                    if (temp2->item == element)
                    {
                        node *prev = temp2->prev;
                        node *next = temp2->next;
                        prev->next = next;
                        next->prev = prev;
                        delete temp2;
                        length--;
                        return;
                    }
                    temp1 = temp1->next;
                    temp2 = temp2->prev;
                }
                std::cerr << "Element not found\n";
            }
        }

        void clear()
        {
            node *curr = first;
            while (curr != nullptr)
            {
                node *nextNode = curr->next;
                delete curr;
                curr = nextNode;
            }
            first = nullptr;
            last = nullptr;
            length = 0;
        }

        bool exist(T element)
        {
            if (empty())
            {
                std::cerr << "Empty Error: no element exist in the list.\n";
                return false;
            }
            const node *temp1 = first;
            const node *temp2 = last;
            while (temp1 != temp2 && temp1->prev != temp2)
            {
                if (temp1->item == element || temp2->item == element)
                    return true;
                temp2 = temp2->prev;
                temp1 = temp1->next;
            }
            return false;
        }

        size_t where(T element)
        {
            if (empty())
            {
                std::cerr << "Empty Error: no element exist in the list.\n";
                return 0;
            }
            const node *temp1 = first;
            const node *temp2 = last;
            size_t ind1 = 0;
            size_t ind2 = length - 1;
            while (temp1 != temp2 && temp1->prev != temp2)
            {
                if (temp1->item == element)
                    return ind1;
                if (temp2->item == element)
                    return ind2;
                temp2 = temp2->prev;
                temp1 = temp1->next;
                ind1++;
                ind2--;
            }
            std::cerr << "Error: no element found.\n";
            return 0;
        }

        void print()
        {
            if (empty())
            {
                std::cout << "linked_list: {}\n";
            }
            else if (length == 1)
            {
                std::cout << "linked_list: {" << first->item << "}\n";
            }
            else if (length == 2)
            {
                std::cout << "linked_list: {" << first->item << ", " << last->item << "}\n";
            }
            else
            {
                std::cout << "linked_list: {";
                const node *temp = first;
                while (temp != nullptr)
                {
                    if (temp == last)
                    {
                        std::cout << temp->item << "}\n";
                        return;
                    }
                    std::cout << temp->item << ", ";
                    temp = temp->next;
                }
            }
        }

        ~linked_list()
        {
            if (length >= 0 && length <= 2)
            {
                delete last;
                delete first;
            }
            else if (length == 3)
            {
                delete last->prev;
                delete last;
                delete first;
            }
            else if (length == 4)
            {
                delete last->prev;
                delete first->next;
                delete first;
                delete last;
            }
            while (length != 0)
            {
                last = last->prev;
                delete last->next;
                if (last == first)
                {
                    delete last;
                    delete first;
                }
                length--;
            }
        }
    };

}

#endif // OPENUDT___BASIC___DOUBLE_LINKED_LIST_HPP