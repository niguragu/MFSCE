#pragma once

#include "resister.hpp"
#include "pc.hpp"
#include "alu.hpp"
#include "ram.hpp"
#include "decoder.hpp"

#include <iostream>
#include <format>
#include <cstdint>
#include <bitset>

namespace MFSCE{
    class CPU
    {
        public:
        CPU();
        void run(); 
    };
}