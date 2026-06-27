#include <iostream>

#pragma once
#ifndef OPENUDT___BASIC___STACK_HPP
#define OPENUDT___BASIC___STACK_HPP

namespace udt
{

    template <class T>
    class stack
    {
    private:
        struct node
        {
            T item;
            node *next;
        };
        node *top, *cur;

    public:
        inline constexpr stack() { top = nullptr; }

        void push(T newItem) noexcept
        {
            node *NewItemPtr = new node;
            if (NewItemPtr == nullptr)
                std::cerr << "Stack push cannot allocat memory" << std::endl;
            else
            {
                NewItemPtr->item = newItem;
                NewItemPtr->next = top;
                top = NewItemPtr;
            }
        }

        inline constexpr bool isEmpty() const noexcept { return top == nullptr; }

        void pop() noexcept
        {
            if (isEmpty())
                std::cerr << "Stack empty on pop" << std::endl;
            else
            {
                node *temp = top;
                top = top->next;
                temp = temp->next = nullptr;
                delete temp;
            }
        }

        void pop(T &stackTop) noexcept
        {
            if (isEmpty())
                std::cerr << "Stack empty on pop" << std::endl;
            else
            {
                stackTop = top->item;
                node *temp = top;
                top = top->next;
                temp = temp->next = nullptr;
                delete temp;
            }
        }

        inline void getTop(T &stackTop) noexcept
        {
            if (isEmpty())
                std::cerr << "Stack empty on pop" << std::endl;
            else
                stackTop = top->item;
        }

        void display() noexcept
        {
            cur = top;
            while (cur != nullptr)
            {
                cout << cur->item << std::endl;
                cur = cur->next;
            }
        }
    };

}

#endif // OPENUDT___BASIC___STACK_HPP