#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stdexcept>
#include <initializer_list>

#pragma once
#ifndef OPENUDT___CORE___TREE_USING_KEYS_HPP
#define OPENUDT___CORE___TREE_USING_KEYS_HPP

namespace udt
{
    namespace tree
    {
        template <typename T1, typename T2>
        using arithmetic_condition = typename std::enable_if<std::is_arithmetic<T1>::value, T2>::type;
        template <bool T1, typename T2>
        using enableIF = typename std::enable_if_t<T1, T2>;
    }
}

#endif // OPENUDT___CORE___TREE_USING_KEYS_HPP