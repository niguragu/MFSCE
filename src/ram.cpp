#include "ram.hpp"

#include <iostream>
#include <format>
#include <cstdint>
#include <array>
#include <map>

namespace MFSCE
{

    RAM::RAM() : main_memory_(0x0FFFFFFF), IO_device_(0x10000FFF)
    {
    }

    uint32_t RAM::lb(uint32_t address) const
    {
        return mem_.at(address);
    }

    uint32_t RAM::lh(uint32_t address) const
    {
        return (lb(address + 1) << 8 | lb(address));
    }

    uint32_t RAM::lw(uint32_t address) const
    {
        return (lb(address + 2) << 16 | lb(address));
    }

    void RAM::sb(uint32_t address, uint32_t data)
    {
        if (address < main_memory_)
        {
            mem_[address] = data & 0xff;
        }
        else if (address < IO_device_)
        {
            std::cout << (data & 0xff) << std::endl;
        }
    }

    void RAM::sh(uint32_t address, uint32_t data)
    {
        if (!alignmentCheck(address, 2))
        {
        }
        sb(address + 0, (data >> 0) & 0xff);
        sb(address + 1, (data >> 8) & 0xff);
    }

    void RAM::sw(uint32_t address, uint32_t data)
    {
        if (!alignmentCheck(address, 4))
        {
        }
        sb(address + 0, (data >> 0) & 0xff);
        sb(address + 1, (data >> 8) & 0xff);
        sb(address + 2, (data >> 16) & 0xff);
        sb(address + 3, (data >> 24) & 0xff);
    }

    bool RAM::alignmentCheck(uint32_t address, uint8_t alignment)
    {
        return (address % alignment) == 0;
    }

} // MFSCE