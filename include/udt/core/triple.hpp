/**
 * @file triple.hpp
 * @brief Defines the triple_t and triple_t3 classes for storing and manipulating triples of values.
 * This header provides two template classes:
 * - triple_t<T>: A class for storing three values of the same type T, with various member functions for accessing and modifying the elements.
 * - triple_t3<T1, T2, T3>: A class for storing three values of potentially different types (T1, T2, T3), with similar member functions for access and modification.
 * Both classes include constructors, getters/setters, element search, swapping, and various arithmetic operations. The member functions are designed to be constexpr and noexcept where appropriate, allowing for compile-time evaluation and guaranteeing no exceptions will be thrown.
 * The classes are defined within the 'udt' namespace and are intended for use in contexts where a simple grouping of three related values is needed, with convenient member functions for common operations on those values.
 * @note The implementation of some member functions (e.g., change_element) contains a bug where '==' is used instead of '=' for assignment, which should be addressed for correct functionality.
 * @see std::tuple for a more general-purpose alternative that can store an arbitrary number of elements of varying types.
 * @author Ali Lafi
 * @date 2025/9/25
 */

#pragma once
#ifndef OPENUDT___CORE___TRIPLE_HPP
#define OPENUDT___CORE___TRIPLE_HPP

#include "triple/triple_t.hpp"
#include "triple/triple_3t.hpp"

#endif // OPENUDT___CORE___TRIPLE_HPP