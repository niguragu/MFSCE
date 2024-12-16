#include "cpu.hpp"
#include "ram.hpp"

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <cstdint>

namespace MFSCE
{
    void binaryLoader(const std::string filename, RAM &ram)
    {

        if (filename == "text" || "rodata")
        {
            std::size_t i = 0;
            std::ifstream file(filename, std::ios::binary | std::ios::ate);
            if (!file)
            {
                std::cerr << "can not opend file: " << filename << std::endl;
            }

            std::streamsize fileSize = file.tellg();
            file.seekg(0, std::ios::beg);

            std::vector<char> buffer(fileSize);
            if (!file.read(buffer.data(), fileSize))
            {
                std::cerr << "Failed to load file: " << filename << std::endl;
            }
            uint32_t baseAddress = 0x00000000;
            for (; i < buffer.size(); ++i)
            {
                uint32_t data = static_cast<uint32_t>(static_cast<unsigned char>(buffer[i]));

                ram.sb(baseAddress + i, data);
            }
        }
        else if (filename == "data")
        {
            std::ifstream file(filename, std::ios::binary | std::ios::ate);
            if (!file)
            {
                std::cerr << "can not opend file: " << filename << std::endl;
            }

            std::streamsize fileSize = file.tellg();
            file.seekg(0, std::ios::beg);

            std::vector<char> buffer(fileSize);
            if (!file.read(buffer.data(), fileSize))
            {
                std::cerr << "Failed to load file: " << filename << std::endl;
            }
            uint32_t baseAddress = 0x00000000;
            for (std::size_t i = 0; i < buffer.size(); ++i)
            {
                uint32_t data = static_cast<uint32_t>(static_cast<unsigned char>(buffer[i]));

                ram.sb(baseAddress + i, data);
            }
        }
        else
        {
            std::cerr << "Undefined section: " << filename << std::endl;
        }
    }
}
