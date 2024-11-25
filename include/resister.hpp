#pragma once

#include <cstdint>
#include <array>

class RESISTER
{
public:
   RESISTER()
   {
      resisters.fill(0); // constructor
   }

   void write(const int8_t, const uint32_t); // setter
   uint32_t read() const;                    // getter
   void ResistersView() const;

private:
   std::array<uint32_t, 32> resisters;
};
