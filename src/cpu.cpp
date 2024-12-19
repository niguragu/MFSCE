#include "register.hpp"
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

                reg.write(decoder.inst.rd, decoder.inst.imm << 20);
            }
            break;

            case instructionSet::AUIPC:
            {
                int32_t casted_imm = static_cast<int32_t>(decoder.inst.imm);
                int32_t casted_pc = static_cast<int32_t>(pc.read());
                uint32_t target_addr = (static_cast<uint32_t>((casted_imm << 12) + casted_pc));
                reg.write(decoder.inst.rd, target_addr);
            }
            break;

            case instructionSet::JAL:
            {
                reg.write(decoder.inst.rd, pc.read() + 4);
                int32_t shifted_imm = static_cast<int32_t>(decoder.inst.imm) << 1;
                pc.write((static_cast<uint32_t>((static_cast<int32_t>(pc.read())) + shifted_imm)));
            }
            break;

            case instructionSet::JALR:
            {
                reg.write(decoder.inst.rd, pc.read() + 4);
                int32_t casted_imm = static_cast<int32_t>(decoder.inst.imm);
                pc.write((static_cast<uint32_t>((static_cast<int32_t>(decoder.inst.rs1)) + casted_imm)));
            }
            break;

            case instructionSet::BEQ:
            {
                alu.set(decoder.inst.rs1, decoder.inst.rs2);
                alu.beq();
                if (alu.get())
                {
                    int32_t casted_imm = static_cast<int32_t>(decoder.inst.imm);
                    int32_t casted_pc = static_cast<int32_t>(pc.read());
                    uint32_t target_addr = (static_cast<uint32_t>(casted_imm + casted_pc));
                    pc.write(target_addr);
                }
            }
            break;

            case instructionSet::BNE:
            {
                alu.set(decoder.inst.rs1, decoder.inst.rs2);
                alu.bne();
                if (alu.get())
                {
                    int32_t casted_imm = static_cast<int32_t>(decoder.inst.imm);
                    int32_t casted_pc = static_cast<int32_t>(pc.read());
                    uint32_t target_addr = (static_cast<uint32_t>(casted_imm + casted_pc));
                    pc.write(target_addr);
                }
            }
            break;

            case instructionSet::BLT:
            {
                alu.set(decoder.inst.rs1, decoder.inst.rs2);
                alu.slt(); // Use the same method because the processing is identical to SLT
                if (alu.get())
                {
                    int32_t casted_imm = static_cast<int32_t>(decoder.inst.imm);
                    int32_t casted_pc = static_cast<int32_t>(pc.read());
                    uint32_t target_addr = (static_cast<uint32_t>(casted_imm + casted_pc));
                    pc.write(target_addr);
                }
            }
            break;

            case instructionSet::BGE:
            {
                alu.set(decoder.inst.rs1, decoder.inst.rs2);
                alu.bge();
                if (alu.get())
                {
                    int32_t casted_imm = static_cast<int32_t>(decoder.inst.imm);
                    int32_t casted_pc = static_cast<int32_t>(pc.read());
                    uint32_t target_addr = (static_cast<uint32_t>(casted_imm + casted_pc));
                    pc.write(target_addr);
                }
            }
            break;

            case instructionSet::BLTU:
            {
                alu.set(decoder.inst.rs1, decoder.inst.rs2);
                alu.sltu(); // Use the same method because the processing is identical to SLTU
                if (alu.get())
                {
                    int32_t casted_imm = static_cast<int32_t>(decoder.inst.imm);
                    int32_t casted_pc = static_cast<int32_t>(pc.read());
                    uint32_t target_addr = (static_cast<uint32_t>(casted_imm + casted_pc));
                    pc.write(target_addr);
                }
            }
            break;

            case instructionSet::BGEU:
            {
                alu.set(decoder.inst.rs1, decoder.inst.rs2);
                alu.bgeu();
                if (alu.get())
                {
                    int32_t casted_imm = static_cast<int32_t>(decoder.inst.imm);
                    int32_t casted_pc = static_cast<int32_t>(pc.read());
                    uint32_t target_addr = (static_cast<uint32_t>(casted_imm + casted_pc));
                    pc.write(target_addr);
                }
            }
            break;

            case instructionSet::LB:
            {
                alu.set(decoder.inst.rs1, decoder.inst.imm);
                alu.add();
                int8_t tmp_val = static_cast<int8_t>(ram.lb(alu.get()));
                uint32_t result_data = static_cast<uint32_t>(tmp_val);
                reg.write(decoder.inst.rd, result_data);
            }
            break;

            case instructionSet::LH:
            {
                alu.set(decoder.inst.rs1, decoder.inst.imm);
                alu.add();
                int16_t tmp_val = static_cast<int16_t>(ram.lh(alu.get()));
                uint32_t result_data = static_cast<uint32_t>(tmp_val);
                reg.write(decoder.inst.rd, result_data);
            }
            break;

            case instructionSet::LW:
            {
                alu.set(decoder.inst.rs1, decoder.inst.imm);
                alu.add();
                uint32_t result_data = ram.lb(alu.get());
                reg.write(decoder.inst.rd, result_data);
            }
            break;

            case instructionSet::LBU:
            {
                uint8_t tmp_val = static_cast<uint8_t>(ram.lb(alu.get()));
                uint32_t result_data = static_cast<uint32_t>(tmp_val);
                reg.write(decoder.inst.rd, result_data);
            }
            break;

            case instructionSet::LHU:
            {
                uint16_t tmp_val = static_cast<uint16_t>(ram.lh(alu.get()));
                uint32_t result_data = static_cast<uint32_t>(tmp_val);
                reg.write(decoder.inst.rd, result_data);
            }
            break;

            case instructionSet::SB:
            {
                alu.set(decoder.inst.rs1, decoder.inst.imm);
                alu.add();
                ram.sb(alu.get(), decoder.inst.rs2);
            }
            break;

            case instructionSet::SH:
            {
                alu.set(decoder.inst.rs1, decoder.inst.imm);
                alu.add();
                ram.sh(alu.get(), decoder.inst.rs2);
            }
            break;

            case instructionSet::SW:
            {
                alu.set(decoder.inst.rs1, decoder.inst.imm);
                alu.add();
                ram.sw(alu.get(), decoder.inst.rs2);
            }
            break;

            case instructionSet::ADDI:
            {
                alu.set(decoder.inst.rs1, decoder.inst.imm);
                alu.add();
                reg.write(decoder.inst.rd, alu.get());
            }
            break;

            case instructionSet::SLTI:
            {
                alu.set(decoder.inst.rs1, decoder.inst.imm);
                alu.slt();
                reg.write(decoder.inst.rd, alu.get());
            }
            break;

            case instructionSet::SLTIU:
            {
                alu.set(decoder.inst.rs1, decoder.inst.imm);
                alu.sltu();
                reg.write(decoder.inst.rd, alu.get());
            }
            break;

            case instructionSet::XORI:
            {
                alu.set(decoder.inst.rs1, decoder.inst.imm);
                alu.bitwiseXor();
                reg.write(decoder.inst.rd, alu.get());
            }
            break;

            case instructionSet::ORI:
            {
                alu.set(decoder.inst.rs1, decoder.inst.imm);
                alu.bitwiseOr();
                reg.write(decoder.inst.rd, alu.get());
            }
            break;

            case instructionSet::ANDI:
            {
                alu.set(decoder.inst.rs1, decoder.inst.imm);
                alu.bitwiseAnd();
                reg.write(decoder.inst.rd, alu.get());
            }
            break;

            case instructionSet::SLLI:
            {
                alu.set(decoder.inst.rs1, decoder.inst.imm);
                alu.sll();
                reg.write(decoder.inst.rd, alu.get());
            }
            break;

            case instructionSet::SRLI:
            {
                alu.set(decoder.inst.rs1, decoder.inst.imm);
                alu.srl();
                reg.write(decoder.inst.rd, alu.get());
            }
            break;

            case instructionSet::SRAI:
            {
                alu.set(decoder.inst.rs1, decoder.inst.imm);
                alu.sra();
                reg.write(decoder.inst.rd, alu.get());
            }
            break;

            case instructionSet::ADD:
            {
                alu.set(decoder.inst.rs1, decoder.inst.rs2);
                alu.add();
                reg.write(decoder.inst.rd, alu.get());
            }
            break;

            case instructionSet::SUB:
            {
                alu.set(decoder.inst.rs1, decoder.inst.rs2);
                alu.sub();
                reg.write(decoder.inst.rd, alu.get());
            }
            break;

            case instructionSet::SLL:
            {
                alu.set(decoder.inst.rs1, decoder.inst.rs2);
                alu.sll();
                reg.write(decoder.inst.rd, alu.get());
            }
            break;

            case instructionSet::SLT:
            {
                alu.set(decoder.inst.rs1, decoder.inst.rs2);
                alu.slt();
                reg.write(decoder.inst.rd, alu.get());
            }
            break;

            case instructionSet::SLTU:
            {
                alu.set(decoder.inst.rs1, decoder.inst.rs2);
                alu.sltu();
                reg.write(decoder.inst.rd, alu.get());
            }
            break;

            case instructionSet::XOR:
            {
                alu.set(decoder.inst.rs1, decoder.inst.rs2);
                alu.bitwiseXor();
                reg.write(decoder.inst.rd, alu.get());
            }
            break;

            case instructionSet::SRL:
            {
                alu.set(decoder.inst.rs1, decoder.inst.rs2);
                alu.srl();
                reg.write(decoder.inst.rd, alu.get());
            }
            break;

            case instructionSet::SRA:
            {
                alu.set(decoder.inst.rs1, decoder.inst.rs2);
                alu.sra();
                reg.write(decoder.inst.rd, alu.get());
            }
            break;

            case instructionSet::OR:
            {
                alu.set(decoder.inst.rs1, decoder.inst.rs2);
                alu.bitwiseOr();
                reg.write(decoder.inst.rd, alu.get());
            }
            break;

            case instructionSet::AND:
            {
                alu.set(decoder.inst.rs1, decoder.inst.rs2);
                alu.bitwiseAnd();
                reg.write(decoder.inst.rd, alu.get());
            }
            break;

            default:
                break;
            }
            ram.view();
            pc.write(pc.read() + 4);
        }
    }

    uint32_t CPU::signExtension(u_int32_t value, uint8_t shiftCount)
    {
        return static_cast<uint32_t>(static_cast<int32_t>(value) >> shiftCount);
    }

    int CPU::instructionConverter(uint32_t opcode, uint32_t funct3, uint32_t funct7)
    {
        std::string funct3Str = (funct3 == 0) ? "000" : std::to_string(funct3);
        std::string funct7Str = (funct7 == 0) ? "0000000" : std::to_string(funct7);

        return std::stoi(funct7Str + funct3Str + std::to_string(opcode));
    }
} // MFSCE