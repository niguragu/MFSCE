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
            decoder.setInstructionType(pc.read());
            switch (instructionConverter(decoder.inst.funct7, decoder.inst.funct3, decoder.inst.opcode))
            {
            case instructionSet::ADD:
            {
                alu.set(decoder.inst.rs1, decoder.inst.rs2);
                resister.write(decoder.inst.rd, alu.get());
            }
            break;

            default:
                break;
            }
            resister.view();
            pc.write(pc.read() + 4);
        }
    }

    uint32_t CPU::signExtention(u_int32_t value)
    {
        return static_cast<uint32_t>(static_cast<int32_t>(value));
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