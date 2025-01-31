#pragma once

#include <cstdint>
#include <array>

namespace MFSCE
{

   class REGISTER
   {
   public:
      REGISTER();
      void write(uint8_t, uint32_t);      // setter
      const uint32_t read(uint8_t) const; // getter
      void view() const;

   private:
      std::array<uint32_t, 32> registers_;
   };

} // MFSCE