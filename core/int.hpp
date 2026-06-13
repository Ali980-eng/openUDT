/**
 * @file INT.hpp
 * @brief Defines uint128_t and int128_t classes for extended precision integer arithmetic.
 * @details This header provides two classes, uint128_t and int128_t, which implement 128-bit unsigned and signed integers respectively.
 * The classes support construction from various numeric types, arithmetic operations with overflow/underflow checks, and comparison operators.
 * The uint128_t class uses a two-part representation (upper and lower 64 bits) to achieve 128-bit precision, while int128_t uses a sign-magnitude approach.
 * @note All operations that can potentially overflow or underflow will throw exceptions to ensure safe arithmetic.
 * @warning The comparison logic in int128_t may have issues due to the use of uint64_t for both positive and negative parts, which could lead to incorrect comparisons in edge cases.
 * @date 2025/9/25
 * @author Ali Lafi
 */

#pragma once
#ifndef OPENUDT___CORE_INT_HPP
#define OPENUDT___CORE_INT_HPP

#include "int/int128_t.hpp"
#include "int/uint128_t.hpp"

#endif // OPENUDT___CORE_INT_HPP