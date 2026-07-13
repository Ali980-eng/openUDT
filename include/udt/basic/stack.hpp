#include <iostream>

#pragma once
#ifndef OPENUDT___BASIC___STACK_HPP
#define OPENUDT___BASIC___STACK_HPP

namespace udt
{

    /// @brief Represents a stack implemented with a linked-list-based node structure.
    ///
    /// This container supports pushing, popping, and inspecting the current top element.
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
        size_t size;

    public:
        /// @brief Constructs an empty stack.
        inline constexpr stack() { top = nullptr; }

        /// @brief Pushes a new item onto the stack.
        ///
        /// @param newItem The value to push.
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

        /// @brief Checks whether the stack is empty.
        inline constexpr bool isEmpty() const noexcept { return top == nullptr; }

        /// @brief Removes the top item from the stack.
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

        /// @brief Removes the top item and stores it in the provided reference.
        ///
        /// @param stackTop Receives the removed value.
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

        /// @brief Copies the current top element to the provided reference.
        ///
        /// @param stackTop Receives the top value.
        inline void getTop(T &stackTop) noexcept
        {
            if (isEmpty())
                std::cerr << "Stack empty on pop" << std::endl;
            else
                stackTop = top->item;
        }

        /// @brief Prints the stack contents to the standard output stream.
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