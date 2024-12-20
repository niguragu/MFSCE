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

    void binaryLoader(const std::string filename, RAM &ram)
    {
        std::string section, filepath;

        if (filename == "text")
        {
            filepath = text_filepath;
            section = "text";
        }
        else if (filename == "rodata")
        {
            filepath = rodata_filepath;
            section = "rodata";
        }
        else if (filename == "data")
        {
            filepath = data_filepath;
            section = "data";
        }
        else
        {
            std::cerr << "Undefined section: " << filepath << std::endl;
            return;
        }

        uint32_t baseAddress = 0;
        if (section == "text" || section == "rodata")
        {
            baseAddress = 0x00000000;
        }
        else if (section == "data")
        {
            baseAddress = 0x20000000;
        }

        std::ifstream file(filepath, std::ios::binary | std::ios::ate);
        if (!file)
        {
            std::cerr << "Cannot open file: " << filepath << std::endl;
            return;
        }

        std::streamsize fileSize = file.tellg();
        file.seekg(0, std::ios::beg);

        std::vector<char> buffer(fileSize);
        if (!file.read(buffer.data(), fileSize))
        {
            std::cerr << "Failed to load file: " << filepath << std::endl;
            return;
        }

        for (std::size_t i = 0; i < buffer.size(); ++i)
        {
            uint32_t data = static_cast<uint32_t>(static_cast<unsigned char>(buffer[i]));
            ram.sb(baseAddress + i, data);
        }
    }
}
