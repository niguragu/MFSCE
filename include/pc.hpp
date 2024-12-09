#pragma once

#include <cstdint>

namespace MFSCE
{

    class PC
    {
    public:
        PC();

        void write(uint32_t); // setter

        const uint32_t read() const; // getter

        void view() const;

    private:
        uint32_t pc_;
    };

} // MFSCE