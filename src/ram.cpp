#include "ram.hpp"

#include <iostream>
#include <format>
#include <cstdint>
#include <map>
#include <vector>

namespace MFSCE
{

    RAM::RAM()
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
        return (lh(address + 2) << 16 | lh(address));
    }

    void RAM::sb(uint32_t address, uint32_t data)
    {
        if (address < memory_map.MMIO_origin_ || address >= (memory_map.MMIO_origin_ + memory_map.MMIO_length_))
        {
            mem_[address] = data & 0xff;
        }
        else
        {
            mmio_buffer_.push_back(static_cast<char>(data & 0xff));
            mmioFlush();
        }
    }

    void RAM::sh(uint32_t address, uint32_t data)
    {
        if (!alignmentCheck(address, 2))
        {
            std::cerr << "Alignment violation: Address must be 2-byte aligned for 'sh'" << std::endl;
            return;
        }
        if (address < memory_map.MMIO_origin_ || address >= (memory_map.MMIO_origin_ + memory_map.MMIO_length_))
        {
            sb(address + 0, (data >> 0) & 0xff);
            sb(address + 1, (data >> 8) & 0xff);
        }
        else
        {
            mmio_buffer_.push_back(static_cast<char>(data & 0xffff));
            mmioFlush();
        }
    }

    void RAM::sw(uint32_t address, uint32_t data)
    {
        if (!alignmentCheck(address, 4))
        {
            std::cerr << "Alignment violation: Address must be 4-byte aligned for 'sw'" << std::endl;
            return;
        }
        if (address < memory_map.MMIO_origin_ || address >= (memory_map.MMIO_origin_ + memory_map.MMIO_length_))
        {
            sb(address + 0, (data >> 0) & 0xff);
            sb(address + 1, (data >> 8) & 0xff);
            sb(address + 2, (data >> 16) & 0xff);
            sb(address + 3, (data >> 24) & 0xff);
        }
        else
        {
            mmio_buffer_.push_back(static_cast<char>(data & 0xffffffff));
            mmioFlush();
        }
    }

    void RAM::view() const
    {
        for (auto &&[key, value] : mem_)
        {
            std::cout << std::format("[addr]{:08x}:{:02x}", key, value) << std::endl;
        }
    }

    bool RAM::alignmentCheck(uint32_t address, uint8_t alignment)
    {
        return (address % alignment) == 0;
    }

    void RAM::mmioFlush()
    {
        for (auto e : mmio_buffer_)
        {
            printf("%c", e);
        }
        printf("\n");
        mmio_buffer_.clear();
    }

} // MFSCE