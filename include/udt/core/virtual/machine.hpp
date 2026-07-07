
#include "ptr_8.hpp"
#include "ptr_16.hpp"
#include "ptr_32.hpp"
#include "ptr_64.hpp"
#include <vector>
#include <string>
#include <unordered_map>

#pragma once
#ifndef OPENUDT___CORE___VIRTUAL_MACHINE_HPP
#define OPENUDT___CORE___VIRTUAL_MACHINE_HPP

namespace udt
{
    namespace Virtual
    {
        using data = std::vector<uint8_t>;
        using segments = hash_map<str, std::pair<size_t, data>>;

        class machine_8
        {
            hash_map<str, uint8_t> registers;
            hash_map<str, std::pair<size_t, data>> segments;
            hash_map<str, ptr_8> segments_indexs;
        };

        class machine_16
        {
            hash_map<str, uint16_t> registers;
            hash_map<str, std::pair<size_t, data>> segments;
            hash_map<str, ptr_32> segments_indexs;
        };

        class machine_32
        {
            hash_map<str, uint32_t> registers;
            hash_map<str, std::pair<size_t, data>> segments;
            hash_map<str, ptr_32> segments_indexs;
        };

        class machine_64
        {
            hash_map<str, uint64_t> registers;
            hash_map<str, std::pair<size_t, data>> segments;
            hash_map<str, ptr_64> segments_indexs;
        };
    }
}

#endif // OPENUDT___CORE___VIRTUAL_MACHINE_HPP