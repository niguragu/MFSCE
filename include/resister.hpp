#pragma once

#include <cstdint>
#include <array>

namespace MFSCE
{

class RESISTER
{
public:
   RESISTER();

   void write(const uint8_t &, const uint32_t &); // setter

   const uint32_t &read(uint8_t) const; // getter

   void view() const;

private:
   std::array<uint32_t, 32> resisters;
};

} // MFSCE