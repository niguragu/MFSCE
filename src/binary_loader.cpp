#include "ram.hpp"

#include <fstream>
#include <vector>
#include <iostream>
#include <cstdint>

namespace MFSCE
{
    inline const std::string text_filepath = "../testcode/test_text.bin";
    inline const std::string rodata_filepath = "../testcode/test_rodata.bin";
    inline const std::string data_filepath = "../testcode/test_data.bin";

    void binaryLoader(std::string memory_area, RAM &ram)
    {
        uint32_t baseAddress = 0;
        if (memory_area == "ROM")
        {
            baseAddress = 0x00000000;
            std::size_t i = 0;

            // text
            {
                std::ifstream file(text_filepath, std::ios::binary | std::ios::ate);
                if (!file)
                {
                    std::cerr << "Cannot open file: " << text_filepath << std::endl;
                    return;
                }

                std::streamsize fileSize = file.tellg();
                file.seekg(0, std::ios::beg);

                std::vector<char> buffer(fileSize);
                if (!file.read(buffer.data(), fileSize))
                {
                    std::cerr << "Failed to load file: " << text_filepath << std::endl;
                    return;
                }

                for (; i < buffer.size(); ++i)
                {
                    uint32_t data = static_cast<uint32_t>(static_cast<unsigned char>(buffer[i]));
                    ram.sb(baseAddress + i, data);
                }
            }

            // rodata
            {
                std::ifstream file(rodata_filepath, std::ios::binary | std::ios::ate);
                if (!file)
                {
                    std::cerr << "Cannot open file: " << rodata_filepath << std::endl;
                    return;
                }

                std::streamsize fileSize = file.tellg();
                file.seekg(0, std::ios::beg);

                std::vector<char> buffer(fileSize);
                if (!file.read(buffer.data(), fileSize))
                {
                    std::cerr << "Failed to load file: " << rodata_filepath << std::endl;
                    return;
                }

                for (std::size_t j = 0; j < buffer.size(); ++j, ++i)
                {
                    uint32_t data = static_cast<uint32_t>(static_cast<unsigned char>(buffer[j]));
                    ram.sb(baseAddress + i, data);
                }
            }
        }

        else if (memory_area == "RAM")
        {
            baseAddress = 0x20000000;
            std::ifstream file(data_filepath, std::ios::binary | std::ios::ate);
            if (!file)
            {
                std::cerr << "Cannot open file: " << data_filepath << std::endl;
                return;
            }

            std::streamsize fileSize = file.tellg();
            file.seekg(0, std::ios::beg);

            std::vector<char> buffer(fileSize);
            if (!file.read(buffer.data(), fileSize))
            {
                std::cerr << "Failed to load file: " << data_filepath << std::endl;
                return;
            }

            for (std::size_t i = 0; i < buffer.size(); ++i)
            {
                uint32_t data = static_cast<uint32_t>(static_cast<unsigned char>(buffer[i]));
                ram.sb(baseAddress + i, data);
            }
        }
    }
}