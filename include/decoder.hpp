#pragma once

#include "pc.hpp"

#include <iostream>
#include <format>
#include <cstdint>
#include <bitset>

namespace MFSCE
{
    struct Instruction
    {
        uint32_t opcode : 7;
        uint32_t rd : 5;
        uint32_t funct3 : 3;
        uint32_t rs1 : 5;
        uint32_t rs2 : 5;
        uint32_t funct7 : 7;
        uint32_t imm : 32;
    };
    class DECODER
    {
    public:
        DECODER();
        void setInstructionType(uint32_t);
        Instruction get() const;
        void view() const;
        Instruction inst;

    private:
        uint32_t signExtension(uint32_t);
    };

} // MFSCE