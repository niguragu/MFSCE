#pragma once

#include <cstdint>
#include <array>
#include <map>

namespace MFSCE
{
    struct MemoryMap
    {
        unsigned int ROM_origin_ = 0x00000000;
        unsigned int ROM_length_ = 0x40000;
        unsigned int RAM_origin_ = 0x20000000;
        unsigned int RAM_length_ = 0x10000;
        unsigned int MMIO_origin_ = 0x40000000;
        unsigned int MMIO_length_ = 0x1000;
    };

    class RAM
    {
    public:
        RAM();

        // load instruction
        uint32_t lb(uint32_t) const;
        uint32_t lh(uint32_t) const;
        uint32_t lw(uint32_t) const;

        // store instruction
        void sb(uint32_t, uint32_t);
        void sh(uint32_t, uint32_t);
        void sw(uint32_t, uint32_t);

        void view() const;

        MemoryMap memory_map;

    private:
        std::map<uint32_t, uint8_t> mem_;
        bool alignmentCheck(uint32_t, uint8_t);
    };
} //  MFSCE
