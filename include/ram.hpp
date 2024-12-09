#pragma once

#include <cstdint>
#include <array>
#include <map>

namespace MFSCE
{
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

    private:
        std::map<uint32_t, uint8_t> mem_;
        uint32_t main_memory_ = 0x0FFFFFFF;
        uint32_t IO_device_ = 0x10000FFF;
        bool alignmentCheck(uint32_t, uint8_t);
    };
} //  MFSCE
