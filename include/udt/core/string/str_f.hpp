#include <string>

#pragma once
#ifndef OPENUDT___BASIC___STRING_STR_F_HPP
#define OPENUDT___BASIC___STRING_STR_F_HPP

namespace udt
{
    template <size_t fixSize>
    class str_f
    {
    private:
        char string[fixSize];
        size_t length, maxSize = fixSize;

    public:
        str_f() noexcept : string(""), length(0) {}

        str_f()
    };
}

#endif // OPENUDT___BASIC___STRING_STR_F_HPP