#include <iostream>

#pragma once
#ifndef OPENUDT___UDT_FIXED_STACK_HPP
#define OPENUDT___UDT_FIXED_STACK_HPP

namespace udt
{

    template <typename T, size_t MaxSize>
    class Stack
    {
        int top;
        T item[MaxSize]; // T can be int, double, string, etc.
    public:
        Stack() : top(-1) {}
        void push(T element)
        {
            if (top == MaxSize - 1)
            {
                std::cerr << "Stack full on push" << endl;
                return;
            }
            item[++top] = element;
        }
        bool isEmpty()
        {
            return top < 0;
        }
        void pop()
        {
            if (isEmpty())
            {
                std::cerr << "Stack empty on pop" << endl;
                return;
            }
            top--;
        }
        void pop(T &element)
        {
            if (isEmpty())
                std::cerr << "Stack empty on pop" << endl;
            else
                element = item[top--];
        }
        void getTop(T &stackTop)
        {
            if (isEmpty())
                std::cerr << "Stack empty on get top" << endl;
            else
                stackTop = item[top];
        }
        void print()
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

#endif // OPENUDT___UDT_FIXED_STACK_HPP