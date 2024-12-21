#pragma once

#include "register.hpp"
#include "pc.hpp"
#include "alu.hpp"
#include "ram.hpp"
#include "decoder.hpp"

#include <iostream>
#include <format>
#include <cstdint>
#include <string>

namespace MFSCE
{
    void binaryLoader(std::string ,RAM &);

    class CPU
    {
    public:
        CPU();
        void run();

    private:
        REGISTER reg;
        PC pc;
        ALU alu;
        RAM ram;
        DECODER decoder;
        uint32_t signExtension(u_int32_t, uint8_t);
        int instructionConverter(uint32_t, uint32_t, uint32_t);
        enum instructionSet
        {
            LUI = 0x37,
            AUIPC = 0x17,
            JAL = 0x6f,
            JALR = 0x67,
            BEQ = 0x63,
            BNE = 0xe3,
            BLT = 0x263,
            BGE = 0x2e3,
            BLTU = 0x363,
            BGEU = 0x3e3,
            LB = 0x3,
            LH = 0x83,
            LW = 0x103,
            LBU = 0x203,
            LHU = 0x283,
            SB = 0x23,
            SH = 0xa3,
            SW = 0x123,
            ADDI = 0x13,
            SLTI = 0x113,
            SLTIU = 0x193,
            XORI = 0x213,
            ORI = 0x313,
            ANDI = 0x393,
            SLLI = 0x93,
            SRLI = 0x293,
            SRAI = 0x8293,
            ADD = 0x33,
            SUB = 0x8033,
            SLL = 0xb3,
            SLT = 0x133,
            SLTU = 0x1b3,
            XOR = 0x233,
            SRL = 0x2b3,
            SRA = 0x82b3,
            OR = 0x333,
            AND = 0x3b3,
        };
    };
}