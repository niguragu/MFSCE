#include "resister.hpp"

#include <iostream>
#include <cstdint>
#include <array>
#include <format>


RESISTER::RESISTER()
{
    resisters.fill(0);
}
void RESISTER::write(const uint8_t &reg, const uint32_t &data)
{
    if (reg == 0)
    {
    }
    else if (reg < 32)
        resisters[reg] = data;
}

const uint32_t &RESISTER::read(uint8_t reg) const
{
    return resisters[reg];
}

void RESISTER::view() const
{
    for (int i = 0; auto &&e : resisters)
    {
        std::cout << std::format("x{:02}:{:010}",i,e) << std::endl;
        ++i;
    }
}