#include <fstream>
#include <string>
#include <vector>
#include <iostream>

void elfLoader(const std::string filename)
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
    for (int i = 0; char c : buffer)
    {
    }
}
