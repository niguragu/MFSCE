#include "decoder.hpp"

#include <iostream>
#include <format>
#include <cstdint>

namespace MFSCE
{
    DECODER::DECODER() : inst{}
    {
    }

    void DECODER::setInstructionType(uint32_t instruction)
    {
        inst.opcode = instruction & 0x7f; // 7-bit mask for opcode

        char opcode_type = '0';

        if (inst.opcode == 0b0110111 || inst.opcode == 0b0010111)
        {
            opcode_type = 'U';
        }
        else if (inst.opcode == 0b1101111)
        {
            opcode_type = 'J';
        }

        else if (inst.opcode == 0b0000011 || inst.opcode == 0b1100111 || inst.opcode == 0b0010011)
        {
            opcode_type = 'I';
        }

        else if (inst.opcode == 0b1100011)
        {
            opcode_type = 'B';
        }

        else if (inst.opcode == 0b0100011)
        {
            opcode_type = 'S';
        }

        else if (inst.opcode == 0b0110011)
        {
            opcode_type = 'R';
        }

        switch (opcode_type)
        {
        case 'R':
        {
            inst.rd = (instruction >> 7) & 0x1F;
            inst.funct3 = (instruction >> 12) & 0x07;
            inst.rs1 = (instruction >> 15) & 0x1F;
            inst.rs2 = (instruction >> 20) & 0x1F;
            inst.funct7 = (instruction >> 25) & 0x7F;
            inst.imm = 0;
            break;
        }
        case 'I':
        {
            inst.rd = (instruction >> 7) & 0x1F;
            inst.funct3 = (instruction >> 12) & 0x07;
            inst.rs1 = (instruction >> 15) & 0x1F;
            inst.rs2 = 0;
            inst.funct7 = 0;
            inst.imm = (instruction >> 20) & 0xFFF;
            inst.imm = signExtension(12);
            break;
        }
        case 'S':
        {
            inst.rd = 0;
            inst.funct3 = (instruction >> 12) & 0x07;
            inst.rs1 = (instruction >> 15) & 0x1F;
            inst.rs2 = (instruction >> 20) & 0x1F;
            inst.funct7 = 0;
            inst.imm = ((instruction >> 25) & 0x7F) << 5 | ((instruction >> 7) & 0x1F);
            inst.imm = signExtension(12);
            break;
        }
        case 'B':
        {
            inst.rd = 0;
            inst.funct3 = (instruction >> 12) & 0x07;
            inst.rs1 = (instruction >> 15) & 0x1F;
            inst.rs2 = (instruction >> 20) & 0x1F;
            inst.funct7 = 0;
            inst.imm = (((instruction >> 31) & 0x1) << 12) |
                       (((instruction >> 7) & 0x1) << 11) |
                       (((instruction >> 25) & 0x3F) << 5) |
                       (((instruction >> 8) & 0xF) << 1);
            inst.imm = signExtension(12);
            break;
        }
        case 'U':
        {
            inst.rd = (instruction >> 7) & 0x1F;
            inst.funct3 = 0;
            inst.rs1 = 0;
            inst.rs2 = 0;
            inst.funct7 = 0;
            inst.imm = instruction & 0xFFFFF000;
            break;
        }
        case 'J':
        {
            inst.rd = (instruction >> 7) & 0x1F;
            inst.funct3 = 0;
            inst.rs1 = 0;
            inst.rs2 = 0;
            inst.funct7 = 0;
            inst.imm = (((instruction >> 31) & 0x1) << 20) |
                       (((instruction >> 12) & 0xFF) << 12) |
                       (((instruction >> 20) & 0x1) << 11) |
                       (((instruction >> 21) & 0x3FF));
            inst.imm = signExtension(20);
            break;
        }
        default:
            std::cerr << "Undefined Instruction" << std::endl;
            break;
        }
    }
    Instruction DECODER::get() const
    {
        return inst;
    }
    void DECODER::view() const
    {
        std::cout << std::format("opcode: {:07b}", inst.opcode) << std::endl;
        std::cout << std::format("rd: {:05b}", inst.rd) << std::endl;
        std::cout << std::format("funct3: {:03b}", inst.funct3) << std::endl;
        std::cout << std::format("rs1: {:05b}", inst.rs1) << std::endl;
        std::cout << std::format("rs2: {:05b}", inst.rs2) << std::endl;
        std::cout << std::format("funct7: {:07b}", inst.funct7) << std::endl;
        std::cout << std::format("imm: {:b}", inst.imm) << std::endl;
    }
    uint32_t DECODER::signExtension(int bit_width)
    {
        uint32_t value = this->inst.imm;
        int sift_count = 32 - bit_width;
        int32_t tmp = static_cast<int32_t>(value);
        return static_cast<uint32_t>((tmp << sift_count) >> sift_count);
    }
} // MFSCE