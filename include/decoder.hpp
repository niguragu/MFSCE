#pragma once

#include "pc.hpp"

#include <iostream>
#include <format>
#include <cstdint>
#include <bitset>

namespace MFSCE
{
    class DECODER
    {
    public:
        DECODER();
        void setInstructionType(const PC &);
        struct Instruction get();
        void view();

        struct Instruction
        {
            uint32_t opcode : 7;
            uint32_t rd : 5;
            uint32_t funct3 : 3;
            uint32_t rs1 : 5;
            uint32_t rs2 : 5;
            uint32_t funct7 : 7;
            uint32_t imm : 20;
        };

    private:
        uint32_t singExtention(uint32_t);
        uint32_t zeroExtention(uint32_t);
        Instruction inst;
    };

} // MFSCE