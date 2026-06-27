/**
 * @file strObject.hpp
 * @brief This header defines the udt::str and udt::str_r classes, which are custom str implementations.
 * The udt::str class manages its own memory using std::unique_ptr, while the udt::str_r class uses raw pointers for memory management.
 * Both classes provide various constructors, assignment operators, and member functions for str manipulation, including setting values, checking properties, and performing operations like capitalization and splitting.
 * The classes also include error handling for fixed-size strs and provide comparison operators for equality and inequality checks.
 * @note The udt::str class is designed
 * to be more modern and safer with automatic memory management, while the udt::str_r class offers a more traditional approach with manual memory management.
 * @warning The udt::str_r class requires careful handling to avoid memory leaks and dangling pointers, while the udt::str class is safer due to its use of smart pointers.
 * @see std::string for a standard str implementation in C++.
 * @author Ali Lafi
 * @date 2025/9/25
 */

#include <memory>
#include <stdexcept>
#include <string>

#pragma once
#ifndef OPENUDT___BASIC___STRING_HPP
#define OPENUDT___BASIC___STRING_HPP

#include "string/str.hpp"
#include "string/str_r.hpp"
#include "string/str_f.hpp"

#endif // OPENUDT___BASIC___STRING_HPP