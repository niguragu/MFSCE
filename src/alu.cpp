#include "alu.hpp"

#include <iostream>
#include <cstdint>
#include <array>
#include <format>
#include <bitset>

namespace MFSCE
{

    ALU::ALU() : operand1_(0), operand2_(0), result_(0)
    {
    }
    void ALU::set(uint32_t operand1, uint32_t operand2)
    {
        operand1_ = operand1;
        operand2_ = operand2;
    }

    const uint32_t ALU::get() const
    {
        return result_;
    }

    void ALU::add()
    {
        result_ = operand1_ + operand2_;
    }

    void ALU::sub()
    {
        result_ = operand1_ - operand2_;
    }

    void ALU::bitwiseAnd()
    {
        result_ = operand1_ & operand2_;
    }

    void ALU::bitwiseOr()
    {
        result_ = operand1_ | operand2_;
    }

    void ALU::bitwiseXor()
    {
        result_ = operand1_ ^ operand2_;
    }

    void ALU::sll()
    {
        auto shiftCount = operand2_ & 0b11111; // LSB 5bit mask
        result_ = operand1_ << shiftCount;
    }

    void ALU::sra()
    {
        auto shiftCount = operand2_ & 0b11111;
        result_ = static_cast<uint32_t>((static_cast<int32_t>(operand1_)) >> shiftCount);
    }

    void ALU::srl()
    {
        uint shiftCount = operand2_ & 0b11111;
        result_ = operand1_ >> shiftCount;
    }

    void ALU::slt()
    {
        if (static_cast<int32_t>(operand1_) < static_cast<int32_t>(operand2_))
        {
            result_ = 1;
        }
        else
        {
            result_ = 0;
        }
    }

    void ALU::sltu()
    {
        if (operand1_ < operand2_)
        {
            result_ = 1;
        }
        else
        {
            result_ = 0;
        }
    }

    void ALU::view() const
    {
        std::cout << std::format("operand1:{:032b} operand2:{:032b} result_:{:032b}", operand1_, operand2_, result_) << std::endl;
    }

} // MFSCE