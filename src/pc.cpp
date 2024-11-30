#include "pc.hpp"

#include <iostream>
#include <cstdint>
#include <format>


PC::PC():pc(0)
{
    
}
void PC::write(const uint32_t &data)
{
    pc = data;
}

const uint32_t &PC::read() const
{
    return pc;
}

void PC::View() const
{
std::cout << std::format("PC:{:010}",pc) << std::endl;
}