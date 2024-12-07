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

        //load instruction
        void lh();
        void lh();
        void lw();
        void lbu();
        void lhu();

        //store instruction
        void sb();
        void sh();
        void sw();


    private:
    std::map<uint32_t,uint32_t> mem_;
    };
} // namespace MFSCE
