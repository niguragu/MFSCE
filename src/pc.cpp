#include "pc.hpp"

#include <iostream>
#include <cstdint>


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

}