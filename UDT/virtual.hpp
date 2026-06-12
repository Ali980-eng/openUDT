/**
 * @file virtual.hpp
 * @brief Defines virtual pointer classes for 8-bit, 16-bit, 32-bit, and 64-bit sizes with safe arithmetic operations.
 * @details This header provides four classes: ptr_8, ptr_16, ptr_32, and ptr_64.
 * Each class encapsulates a virtual pointer of the corresponding size and offers methods for setting, getting,
 * clearing, and performing arithmetic operations with saturation semantics. The classes are designed to be
 * constexpr-compatible for compile-time usage and include stream output operators for easy debugging and visualization.
 * @note All operations that could potentially overflow or underflow will saturate at the maximum or minimum value
 * respectively, ensuring safe arithmetic behavior. Division by zero will throw a runtime error.
 * @see ptr_8, ptr_16, ptr_32, ptr_64
 * @author Ali Lafi
 * @date 2025/9/25
 */

#pragma once
#ifndef OPENUDT___UDT_VIRTUAL_HPP
#define OPENUDT___UDT_VIRTUAL_HPP

#include "virtual/ptr_8.hpp"
#include "virtual/ptr_16.hpp"
#include "virtual/ptr_32.hpp"
#include "virtual/ptr_64.hpp"
#include "virtual/machine.hpp"

#endif // OPENUDT___UDT_VIRTUAL_HPP