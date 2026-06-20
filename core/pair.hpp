/**
 * @file pair.hpp
 * @brief This file contains the implementation of the pair_t and pair__t classes, which represent pairs of values.
 * The pair_t class represents a pair of values of the same type, while the pair__t class represents a pair of values of different types.
 * Both classes provide various constructors, assignment operators, comparison operators, and arithmetic operators to manipulate the pairs of values.
 * The classes are designed to be used in the openUDT library and can be included in other parts of the library or in user code that requires pair-like functionality.
 * The classes are implemented in a header file to allow for inline functions and templates, which can improve performance and flexibility when using the classes.
 * The classes are defined within the udt namespace to avoid naming conflicts with other libraries or user code.
 * The classes are designed to be simple and efficient, providing basic functionality for working with pairs of values without unnecessary overhead.
 * The classes are implemented using C++23 features, such as constexpr and noexcept, to ensure that they can be used in a wide range of contexts and with various types of values.
 * Overall, the pair.hpp file provides a useful utility for working with pairs of values in the openUDT library and can be easily integrated into other parts of the library or user code as needed.
 * @date 2025/9/25
 * @author Ali Lafi
 */

#pragma once
#ifndef OPENUDT___CORE___PAIR_HPP
#define OPENUDT___CORE___PAIR_HPP

#include "pair/pair_t.hpp"
#include "pair/pair_v.hpp"
#include "pair/pair__t.hpp"
#include "pair/pair__v.hpp"

#endif // OPENUDT___CORE___PAIR_HPP