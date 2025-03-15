#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>

#define ITA_MAGIC "ITA\1"

void extractITA(const std::string& exePath) {
    std::ifstream exeFile(exePath, std::ios::binary);
    if (!exeFile) {
        std::cerr << "Failed to open executable.\n";
        return;
    }

    exeFile.seekg(-8, std::ios::end);
    uint64_t itaSize;
    exeFile.read(reinterpret_cast<char*>(&itaSize), sizeof(uint64_t));

    exeFile.seekg(-8 - itaSize, std::ios::end);
    std::vector<uint8_t> itaData(itaSize);
    exeFile.read(reinterpret_cast<char*>(itaData.data()), itaSize);

    std::ofstream itaFile("extracted.ita", std::ios::binary);
    itaFile.write(reinterpret_cast<char*>(itaData.data()), itaSize);

    std::cout << "Extracted ITA archive: extracted.ita\n";
}

int main() {
    char exePath[MAX_PATH];
    GetModuleFileNameA(NULL, exePath, MAX_PATH);
    extractITA(exePath);
    return 0;
}
