void decryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& password) {
    std::ifstream in(inputFile, std::ios::binary);
    std::ofstream out(outputFile, std::ios::binary);

    if (!in || !out) {
        MessageBoxA(NULL, "Failed to open encrypted ITA file!", "Error", MB_ICONERROR);
        return;
    }

    unsigned char key[32], iv[16];
    in.read(reinterpret_cast<char*>(iv), sizeof(iv));
    EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha256(), nullptr, (unsigned char*)password.c_str(), password.length(), 1, key, nullptr);

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key, iv);

    char buffer[4096];
    unsigned char decrypted[4096];
    int readBytes, decryptedBytes;

    while ((readBytes = in.readsome(buffer, sizeof(buffer))) > 0) {
        EVP_DecryptUpdate(ctx, decrypted, &decryptedBytes, (unsigned char*)buffer, readBytes);
        out.write(reinterpret_cast<char*>(decrypted), decryptedBytes);
    }

    EVP_DecryptFinal_ex(ctx, decrypted, &decryptedBytes);
    out.write(reinterpret_cast<char*>(decrypted), decryptedBytes);

    EVP_CIPHER_CTX_free(ctx);
    MessageBoxA(NULL, "Decryption and Extraction Successful!", "Success", MB_OK);
}
