#include "Encryptor.h"
int main(int argc, char* argv[])
{

    const std::string infilePath = "test.txt";
    const CryptoPP::byte data[] = // 70 characters
            "Now is the time for all good men to come to the aide of their country.";

    const CryptoPP::byte key[16] = {
            1,2,3,4, 1,2,3,4, 1,2,3,4, 1,2,3,4
    };
    const CryptoPP::byte iv[16] = {
            8,7,6,5, 8,7,6,5, 8,7,6,5, 8,7,6,5
    };

    CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption encryption;
    Encryptor::encryptFile<CryptoPP::AES>(
            infilePath.c_str(),
            data,
            70,
            encryption,
            iv,
            16,
            const_cast<unsigned char *>(key),
            16);

    long dataLength;
    CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption decryption;

    unsigned char *decryptedData = Encryptor::decryptFile<CryptoPP::AES>(
            &dataLength,
            infilePath.c_str(),
            decryption,
            const_cast<unsigned char *>(key),
            16);

    std::cout << dataLength << std::endl
    << decryptedData << std::endl;
    return 0;
}