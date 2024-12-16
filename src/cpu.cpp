#include "resister.hpp"
#include "pc.hpp"
#include "alu.hpp"
#include "ram.hpp"
#include "decoder.hpp"
#include "cpu.hpp"

#include <iostream>
#include <format>
#include <cstdint>
#include <string>

namespace MFSCE
{
    void binaryLoader(const std::string, RAM &);

    CPU::CPU()
    {
    }
    void CPU::run()
    {

        binaryLoader(text, ram);
        binaryLoader(rodata, ram);
        binaryLoader(data, ram);

        while (1)
        {
            decoder.setInstructionType(ram.lb(pc.read()));
            switch (instructionConverter(decoder.inst.funct7, decoder.inst.funct3, decoder.inst.opcode))
            {
            case instructionSet::LUI:
            {
            }
            break;

            case instructionSet::AUIPC:
            {
            }
            break;

            case instructionSet::JAL:
            {
            }
            break;

            case instructionSet::JALR:
            {
            }
            break;

            case instructionSet::BEQ:
            {
            }
            break;

            case instructionSet::BNE:
            {
            }
            break;

            case instructionSet::BLT:
            {
            }
            break;

            case instructionSet::BGE:
            {
            }
            break;

            case instructionSet::BLTU:
            {
            }
            break;

            case instructionSet::BGEU:
            {
            }
            break;

            case instructionSet::LB:
            {
                alu.set(decoder.inst.rs1, decoder.inst.imm);
                alu.add();
                int8_t tmp_val = static_cast<int8_t>(ram.lb(alu.get()));
                uint32_t result_data = static_cast<uint32_t>(tmp_val);
                resister.write(decoder.inst.rd, result_data);
            }
            break;

            case instructionSet::LH:
            {
                alu.set(decoder.inst.rs1, decoder.inst.imm);
                alu.add();
                int16_t tmp_val = static_cast<int16_t>(ram.lh(alu.get()));
                uint32_t result_data = static_cast<uint32_t>(tmp_val);
                resister.write(decoder.inst.rd, result_data);
            }
            break;

            case instructionSet::LW:
            {
                alu.set(decoder.inst.rs1, decoder.inst.imm);
                alu.add();
                uint32_t result_data = ram.lb(alu.get());
                resister.write(decoder.inst.rd, result_data);
            }
            break;

            case instructionSet::LBU:
            {
                uint8_t tmp_val = static_cast<uint8_t>(ram.lb(alu.get()));
                uint32_t result_data = static_cast<uint32_t>(tmp_val);
                resister.write(decoder.inst.rd, result_data);
            }
            break;

            case instructionSet::LHU:
            {
                uint16_t tmp_val = static_cast<uint16_t>(ram.lh(alu.get()));
                uint32_t result_data = static_cast<uint32_t>(tmp_val);
                resister.write(decoder.inst.rd, result_data);
            }
            break;

            case instructionSet::SB:
            {
                alu.set(decoder.inst.rs1, decoder.inst.imm);
                alu.add();
                
            }
            break;

            case instructionSet::SH:
            {
            }
            break;

            case instructionSet::SW:
            {
            }
            break;

            case instructionSet::ADDI:
            {
            }
            break;

            case instructionSet::SLTI:
            {
            }
            break;

            case instructionSet::SLTIU:
            {
            }
            break;

            case instructionSet::XORI:
            {
            }
            break;

            case instructionSet::ORI:
            {
            }
            break;

            case instructionSet::ANDI:
            {
            }
            break;

            case instructionSet::SLLI:
            {
            }
            break;

            case instructionSet::SRLI:
            {
            }
            break;

            case instructionSet::SRAI:
            {
            }
            break;

            case instructionSet::ADD:
            {
                alu.set(decoder.inst.rs1, decoder.inst.rs2);
                alu.add();
                resister.write(decoder.inst.rd, alu.get());
            }
            break;

            case instructionSet::SUB:
            {
                alu.set(decoder.inst.rs1, decoder.inst.rs2);
                alu.sub();
                resister.write(decoder.inst.rd, alu.get());
            }
            break;

            case instructionSet::SLL:
            {
            }
            break;

            case instructionSet::SLT:
            {
            }
            break;

            case instructionSet::SLTU:
            {
            }
            break;

            case instructionSet::XOR:
            {
            }
            break;

            case instructionSet::SRL:
            {
            }
            break;

            case instructionSet::SRA:
            {
            }
            break;

            case instructionSet::OR:
            {
            }
            break;

            case instructionSet::AND:
            {
            }
            break;
                break;
            default:
                break;
            }
            resister.view();
            pc.write(pc.read() + 4);
        }
    }

    uint32_t CPU::signExtention(u_int32_t value, uint8_t shiftCount)
    {
        return static_cast<uint32_t>(static_cast<int32_t>(value) >> shiftCount);
    }

    uint32_t CPU::zeroExtention(uint32_t)
    {
    }
    int CPU::instructionConverter(uint32_t opcode, uint32_t funct3, uint32_t funct7)
    {
        std::string funct3Str = (funct3 == 0) ? "000" : std::to_string(funct3);
        std::string funct7Str = (funct7 == 0) ? "0000000" : std::to_string(funct7);

        return std::stoi(funct7Str + funct3Str + std::to_string(opcode));
    }
} // MFSCE