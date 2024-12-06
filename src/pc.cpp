#include "pc.hpp"

#include <iostream>
#include <cstdint>
#include <format>

namespace MFSCE
{

    PC::PC() : pc_(0)
    {
    }
    void PC::write(const uint32_t &data)
    {
        pc_ = data;
    }

    const uint32_t &PC::read() const
    {
        return pc_;
    }

    void PC::view() const
    {
        std::cout << std::format("PC:{:010}", pc_) << std::endl;
    }

} // MFSCE