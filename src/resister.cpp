#include "resister.hpp"

#include <iostream>
#include <cstdint>
#include <array>
#include <format>

namespace MFSCE
{

    RESISTER::RESISTER()
    {
        resisters_.fill(0);
    }
    void RESISTER::write(uint8_t reg, uint32_t data)
    {
        if (reg == 0)
        {
        }
        else if (reg < 32)
            resisters_[reg] = data;
    }

    const uint32_t RESISTER::read(uint8_t reg) const
    {
        return resisters_[reg];
    }

    void RESISTER::view() const
    {
        for (int i = 0; auto &&e : resisters_)
        {
            std::cout << std::format("x{:02}:{:010}", i, e) << std::endl;
            ++i;
        }
    }

} // MFSCE