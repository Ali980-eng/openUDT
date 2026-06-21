#include <string>

#pragma once
#ifndef OPENUDT___BASIC___STRING_STR_F_HPP
#define OPENUDT___BASIC___STRING_STR_F_HPP

template <size_t fixSize>
class str_f
{
private:
    char string[fixSize] = "\0";
    size_t maxSize = fixSize, size = 0;

public:
};

#endif // OPENUDT___BASIC___STRING_STR_F_HPP