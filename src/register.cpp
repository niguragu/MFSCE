#include "register.hpp"

#include <iostream>
#include <cstdint>
#include <array>
#include <format>

namespace MFSCE
{

    REGISTER::REGISTER()
    {
        registers_.fill(0);
    }
    void REGISTER::write(uint8_t reg, uint32_t data)
    {
        if (reg == 0)
        {
        }
        else if (reg < 32)
            registers_[reg] = data;
    }

    const uint32_t REGISTER::read(uint8_t reg) const
    {
        return registers_[reg];
    }

    void REGISTER::view() const
    {
        for (int i = 0; auto &&e : registers_)
        {
            std::cout << std::format("x{:02}:{:010}", i, e) << std::endl;
            ++i;
        }
    }

} // MFSCE