/**
 * @file bfs.hpp
 * @brief This header defines the bfs_8, bfs_16, bfs_32, and bfs_64 classes, which are custom implementations of binary flag containers.
 * The bfs_8 class manages an 8-bit flag container, while the bfs_16, bfs_32, and bfs_64 classes manage 16-bit, 32-bit, and 64-bit flag containers respectively.
 * Each class provides constructors for initialization, methods to set and reset flags, and operators for comparison and assignment.
 * The classes are designed to allow easy manipulation of individual flags within the container, as well as bulk operations to set or reset all flags at once.
 * @note The bfs_8 class uses a single uint8_t to manage 8 flags, while the bfs_16, bfs_32, and bfs_64 classes use combinations of bfs_8 and bfs_16 to manage larger flag containers.
 * @warning Care should be taken when using these classes to ensure that flag positions are within the valid range (1-8 for bfs_8, 1-16 for bfs_16, 1-32 for bfs_32, and 1-64 for bfs_64).
 * @see std::bitset for a standard C++ implementation of a binary flag container.
 * @author Ali Lafi
 * @date 2025/9/25
 */

#pragma once
#ifndef OPENUDT___CORE___BFS_HPP
#define OPENUDT___CORE___BFS_HPP

#include "bfs/bfs_8.hpp"
#include "bfs/bfs_16.hpp"
#include "bfs/bfs_32.hpp"
#include "bfs/bfs_64.hpp"

#endif // OPENUDT___CORE___BFS_HPP