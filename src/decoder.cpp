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
        switch (inst.opcode)
        {
        case 0b0110011: // R-type
        {
            inst.rd = (instruction >> 7) & 0x1F;
            inst.funct3 = (instruction >> 12) & 0x07;
            inst.rs1 = (instruction >> 15) & 0x1F;
            inst.rs2 = (instruction >> 20) & 0x1F;
            inst.funct7 = (instruction >> 25) & 0x7F;
            inst.imm = 0;
            break;
        }
        case 0b0010011: // I-type
        {
            inst.rd = (instruction >> 7) & 0x1F;
            inst.funct3 = (instruction >> 12) & 0x07;
            inst.rs1 = (instruction >> 15) & 0x1F;
            inst.rs2 = 0;
            inst.funct7 = 0;
            inst.imm = (instruction >> 20) & 0xFFF;
            inst.imm = signExtension(inst.imm << 20 >> 20);
            break;
        }
        case 0b0100011: // S-type
        {
            inst.rd = 0;
            inst.funct3 = (instruction >> 12) & 0x07;
            inst.rs1 = (instruction >> 15) & 0x1F;
            inst.rs2 = (instruction >> 20) & 0x1F;
            inst.funct7 = (instruction >> 25) & 0x7F;
            inst.imm = ((instruction >> 25) << 5) | ((instruction >> 7) & 0x1F);
            inst.imm = signExtension(inst.imm << 20 >> 20);
            break;
        }
        case 0b1100011: // B-type
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
            inst.imm = signExtension(inst.imm << 19 >> 19);
            break;
        }
        case 0b0110111: // U-type
        {
            inst.rd = (instruction >> 7) & 0x1F;
            inst.funct3 = 0;
            inst.rs1 = 0;
            inst.rs2 = 0;
            inst.funct7 = 0;
            inst.imm = (instruction >> 12) & 0xFFFFF;
            break;
        }
        case 0b1101111: // J-type
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
            inst.imm = signExtension(inst.imm << 11 >> 11);
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
        std::cout << std::format("opcode: {:b}", inst.opcode) << std::endl;
        std::cout << std::format("rd: {:b}", inst.rd) << std::endl;
        std::cout << std::format("funct3: {:b}", inst.funct3) << std::endl;
        std::cout << std::format("rs1: {:b}", inst.rs1) << std::endl;
        std::cout << std::format("rs2: {:b}", inst.rs2) << std::endl;
        std::cout << std::format("funct7: {:b}", inst.funct7) << std::endl;
        std::cout << std::format("imm: {:b}", inst.imm) << std::endl;
    }
    uint32_t DECODER::signExtension(uint32_t value)
    {
        return static_cast<uint32_t>(static_cast<int32_t>(value));
    }
} // MFSCE