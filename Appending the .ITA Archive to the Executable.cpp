void createSFX(const std::string& sfxStub, const std::string& itaFile, const std::string& outputExe) {
    std::ifstream stub(sfxStub, std::ios::binary);
    std::ifstream ita(itaFile, std::ios::binary);
    std::ofstream output(outputExe, std::ios::binary);

    if (!stub || !ita || !output) {
        std::cerr << "File opening failed.\n";
        return;
    }

    output << stub.rdbuf();  // Copy SFX stub
    output << ita.rdbuf();   // Append ITA archive

    ita.seekg(0, std::ios::end);
    uint64_t itaSize = ita.tellg();
    output.write(reinterpret_cast<char*>(&itaSize), sizeof(uint64_t));

    std::cout << "Created self-extracting ITA: " << outputExe << "\n";
}
