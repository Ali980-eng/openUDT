
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
        typedef std::vector<uint8_t> data;

        struct machine_8
        {
            std::unordered_map<std::string, uint8_t> registers;
            std::unordered_map<std::string, std::pair<size_t, data>> segments;
            std::unordered_map<std::string, ptr_8> segments_indexs;
        };

        struct machine_16
        {
            std::unordered_map<std::string, uint16_t> registers;
            std::unordered_map<std::string, std::pair<size_t, data>> segments;
            std::unordered_map<std::string, ptr_32> segments_indexs;
        };

        struct machine_32
        {
            std::unordered_map<std::string, uint32_t> registers;
            std::unordered_map<std::string, std::pair<size_t, data>> segments;
            std::unordered_map<std::string, ptr_32> segments_indexs;
        };

        struct machine_64
        {
            std::unordered_map<std::string, uint64_t> registers;
            std::unordered_map<std::string, std::pair<size_t, data>> segments;
            std::unordered_map<std::string, ptr_64> segments_indexs;
        };
    }
}

#endif // OPENUDT___CORE___VIRTUAL_MACHINE_HPP