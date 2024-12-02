#pragma once

#include <cstdint>
#include <array>

class ALU
{
public:
    ALU();

    void set(const uint32_t &, const uint32_t &); // setter

    const uint32_t &getResult() const; // getter

    // arithmetic instruction
    void add();
    void sub();
    void bitwiseOr();
    void bitwiseAnd();
    void bitwiseXor();
    void sll();
    void sra();
    void srl();
    void slt();
    void sltu();

    // conditional branch instruction
    void beq();
    void bne();
    void bge();
    void bgeu();
    void blt();
    void bltu();

    void view() const;

private:
    private:
    uint32_t operand1_;
    uint32_t operand2_;
    uint32_t result_;
    bool result_flag_;
};
