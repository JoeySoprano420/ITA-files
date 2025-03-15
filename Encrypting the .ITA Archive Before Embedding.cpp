#include <openssl/evp.h>
#include <openssl/rand.h>
#include <iostream>
#include <fstream>

void encryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& password) {
    std::ifstream in(inputFile, std::ios::binary);
    std::ofstream out(outputFile, std::ios::binary);
    
    if (!in || !out) {
        std::cerr << "File opening failed.\n";
        return;
    }

    unsigned char key[32], iv[16];
    RAND_bytes(iv, sizeof(iv));
    EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha256(), nullptr, (unsigned char*)password.c_str(), password.length(), 1, key, nullptr);

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key, iv);

    out.write(reinterpret_cast<char*>(iv), sizeof(iv));

    char buffer[4096];
    unsigned char encrypted[4096 + EVP_MAX_BLOCK_LENGTH];
    int readBytes, encryptedBytes;
    
    while ((readBytes = in.readsome(buffer, sizeof(buffer))) > 0) {
        EVP_EncryptUpdate(ctx, encrypted, &encryptedBytes, (unsigned char*)buffer, readBytes);
        out.write(reinterpret_cast<char*>(encrypted), encryptedBytes);
    }

    EVP_EncryptFinal_ex(ctx, encrypted, &encryptedBytes);
    out.write(reinterpret_cast<char*>(encrypted), encryptedBytes);

    EVP_CIPHER_CTX_free(ctx);
    std::cout << "Encryption successful: " << outputFile << "\n";
}
