#include <iostream>
#include "cfrost/structure.h"

#pragma once
#ifndef OPENUDT___BASIC___stack_f_F_HPP
#define OPENUDT___BASIC___stack_f_F_HPP

namespace udt
{

    /// @brief Represents a fixed-capacity stack implemented on a static array.
    ///
    /// This container supports push, pop, and top access operations within a predefined size.
    template <typename T, size_t MaxSize>
    class stack_f
    {
    private:
        size_t top;
        T item[MaxSize]; // T can be int, double, string, etc.

    public:
        /// @brief Constructs an empty fixed-capacity stack.
        stack_f() : top(-1) {}

        /// @brief Pushes an element onto the stack.
        ///
        /// @param element The value to push.
        void push(T element)
        {
            if (top == MaxSize - 1)
            {
                std::cerr << "stack_f full on push" << endl;
                return;
            }
            item[++top] = element;
        }

        /// @brief Checks whether the stack is empty.
        bool isEmpty()
        {
            return top < 0;
        }

        /// @brief Removes the top element from the stack.
        procedure(pop)
        {
            if (isEmpty())
            {
                std::cerr << "stack_f empty on pop" << endl;
                return;
            }
            top--;
        }

        /// @brief Removes the top element and stores it in the provided reference.
        ///
        /// @param element Receives the removed value.
        void pop(T &element)
        {
            if (isEmpty())
                std::cerr << "stack_f empty on pop" << endl;
            else
                element = item[top--];
        }

        /// @brief Copies the top element to the provided reference.
        ///
        /// @param stack_fTop Receives the top value.
        void getTop(T &stack_fTop)
        {
            if (isEmpty())
                std::cerr << "stack_f empty on get top" << endl;
            else
                stack_fTop = item[top];
        }

        /// @brief Prints the stack contents to the standard output stream.
        procedure(print)
        {
            for (int i = top; i >= 0; --i)
            {
                if (i == top)
                    std::cout << " [" << item[i] << ", ";
                else if (i == 0)
                    std::cout << item[i] << "] " << endl;
                else
                    std::cout << item[i] << ", ";
            }
        }
    };

}

#endif // OPENUDT___BASIC___stack_f_F_HPP