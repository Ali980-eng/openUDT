/**
 * @file BFS.hpp
 * @brief This header defines the BFS_8, BFS_16, BFS_32, and BFS_64 classes, which are custom implementations of binary flag containers.
 * The BFS_8 class manages an 8-bit flag container, while the BFS_16, BFS_32, and BFS_64 classes manage 16-bit, 32-bit, and 64-bit flag containers respectively.
 * Each class provides constructors for initialization, methods to set and reset flags, and operators for comparison and assignment.
 * The classes are designed to allow easy manipulation of individual flags within the container, as well as bulk operations to set or reset all flags at once.
 * @note The BFS_8 class uses a single uint8_t to manage 8 flags, while the BFS_16, BFS_32, and BFS_64 classes use combinations of BFS_8 and BFS_16 to manage larger flag containers.
 * @warning Care should be taken when using these classes to ensure that flag positions are within the valid range (1-8 for BFS_8, 1-16 for BFS_16, 1-32 for BFS_32, and 1-64 for BFS_64).
 * @see std::bitset for a standard C++ implementation of a binary flag container.
 * @author Ali Lafi
 * @date 2025/9/25
 */

#pragma once
#ifndef OPENUDT___UDT_BFS_HPP
#define OPENUDT___UDT_BFS_HPP
#include "BFS/BFS_8.hpp"
#include "BFS/BFS_16.hpp"
#include "BFS/BFS_32.hpp"
#include "BFS/BFS_64.hpp"
#endif // OPENUDT___UDT_BFS_HPP