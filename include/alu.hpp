#pragma once

#include <cstdint>
#include <array>

namespace MFSCE
{

    class ALU
    {
    public:
        ALU();

        void set(const uint32_t, const uint32_t); // setter

        const uint32_t get() const; // getter

        // arithmetic instruction
        void add();
        void sub();
        void bitwiseAnd();
        void bitwiseOr();
        void bitwiseXor();
        void sll();
        void sra();
        void srl();
        void slt();
        void sltu();

        void view() const;

    private:
        uint32_t operand1_;
        uint32_t operand2_;
        uint32_t result_;
    };

} // MFSCE