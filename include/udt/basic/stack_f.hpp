#include <iostream>

#pragma once
#ifndef OPENUDT___BASIC___stack_f_F_HPP
#define OPENUDT___BASIC___stack_f_F_HPP

namespace udt
{

    template <typename T, size_t MaxSize>
    class stack_f
    {
    private:
        size_t top;
        T item[MaxSize]; // T can be int, double, string, etc.

    public:
        stack_f() : top(-1) {}
        void push(T element)
        {
            if (top == MaxSize - 1)
            {
                std::cerr << "stack_f full on push" << endl;
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
                std::cerr << "stack_f empty on pop" << endl;
                return;
            }
            top--;
        }
        void pop(T &element)
        {
            if (isEmpty())
                std::cerr << "stack_f empty on pop" << endl;
            else
                element = item[top--];
        }
        void getTop(T &stack_fTop)
        {
            if (isEmpty())
                std::cerr << "stack_f empty on get top" << endl;
            else
                stack_fTop = item[top];
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

#endif // OPENUDT___BASIC___stack_f_F_HPP