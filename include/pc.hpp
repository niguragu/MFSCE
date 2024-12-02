#pragma once

#include <cstdint>

class PC
{
public:
    PC();

    void write(const uint32_t &); // setter

    const uint32_t &read() const; // getter

    void view() const;

private:
    uint32_t pc_;
};
