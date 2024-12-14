#include "resister.hpp"
#include "pc.hpp"
#include "alu.hpp"
#include "ram.hpp"
#include "decoder.hpp"
#include "cpu.hpp"

using namespace MFSCE;

int main()
{
    CPU cpu;
    cpu.run();
    return 0;
}