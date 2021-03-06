//
// Created by RedmiBook on 10.12.2020.
//

#ifndef SECKIT_ENCRYPTOR_H
#define SECKIT_ENCRYPTOR_H


#include "cryptlib.h"
#include "filters.h"
#include "modes.h"
#include "files.h"
#include "aes.h"

#include <string>
#include <iostream>

class Encryptor {
public:

template <class T>
static void encryptFile(
        const char* outFilePath,
        const unsigned char *data,
        long dataLength,
        typename CryptoPP::CBC_Mode<T>::Encryption encryption,
        const unsigned char *iv,
        size_t ivLength,
        const unsigned char *key,
        size_t keyLength)
{

    using namespace CryptoPP;

    FileSink outFile(outFilePath);
    word64 lengthToWrite = 8 + 4 + ivLength + dataLength;

    word32 h = lengthToWrite >> 32;
    word32 l = lengthToWrite;


    outFile.PutWord32(h, BIG_ENDIAN_ORDER);
    outFile.PutWord32(l, BIG_ENDIAN_ORDER);

    word32 ivL = ivLength;
    outFile.PutWord32(ivL, BIG_ENDIAN_ORDER);
    outFile.Put(iv, ivLength);

    encryption.SetKeyWithIV(key, keyLength, iv, ivLength);

    StreamTransformationFilter stfEncryptor(encryption, new Redirector(outFile));
    stfEncryptor.Put(data, dataLength);
    stfEncryptor.MessageEnd();

}


template <class T>
static unsigned char * decryptFile(
        long* dataLength,
        const char *inFilePath,
        typename CryptoPP::CBC_Mode<T>::Decryption decryption,
        const unsigned char *key,
        size_t keyLength)
{

    using namespace CryptoPP;
    FileSource inFile(inFilePath, true /*pumpAll*/);

    word64 read, length;
    word32 h, l;
    read = inFile.GetWord32(h, BIG_ENDIAN_ORDER);
    read += inFile.GetWord32(l, BIG_ENDIAN_ORDER);

    length = ((word64)h << 32) | l;
    if (read != 8)
        throw std::runtime_error("Failed to read data length");

    read = inFile.GetWord32(l, BIG_ENDIAN_ORDER);
    if (read != 4)
        throw std::runtime_error("Failed to read iv length");
    size_t ivLength = l;

    SecByteBlock v(ivLength);
    read = inFile.Get(v, ivLength);
    if (read != ivLength)
        throw std::runtime_error("Failed to read iv");

    decryption.SetKeyWithIV(key, keyLength, v, ivLength);

    *dataLength = length - 8 - 4 - ivLength;
    SecByteBlock d(*dataLength);

    auto * data = static_cast<unsigned char *>(malloc(*dataLength));
    StreamTransformationFilter stfDecryptor(decryption, new CryptoPP::ArraySink(data, *dataLength));
    inFile.CopyTo(stfDecryptor);
    stfDecryptor.MessageEnd();
    return data;

}
static const CryptoPP::byte * ELFHash(std::string str, int hashSize) {
        unsigned int hash = 0;
        unsigned int x = 0;
        unsigned int i = 0;
        unsigned int len = str.length();

        for (i = 0; i < len; i++)
        {
            hash = (hash << 4) + (str[i]);
            if ((x = hash & 0xF0000000) != 0)
            {
                hash ^= (x >> 24);
            }
            hash &= ~x;
        }

        auto* array = static_cast<CryptoPP::byte *>(malloc(hashSize));
        for (int i = 0; i < hashSize; i++)
            array[i] = (hash >> ((i * 8) % 32));
        return array;
    }

    template <class T>
    static void encryptFile(
            const char* outFilePath,
            const std::string& data,
            typename CryptoPP::CBC_Mode<T>::Encryption encryption,
            std::string key)
    {
        const CryptoPP::byte iv[16] = {
                8,7,6,5, 8,7,6,5, 8,7,6,5, 8,7,6,5
        };

        auto hash = ELFHash(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
        Encryptor::encryptFile<T>(
                outFilePath,
                reinterpret_cast<const CryptoPP::byte *> (data.c_str()),
                data.size() + 1,
                encryption,
                iv,
                16,
                hash,
                CryptoPP::AES::DEFAULT_KEYLENGTH);
    }

    template <class T>
    static std::string decryptFile(
            const char *inFilePath,
            typename CryptoPP::CBC_Mode<T>::Decryption decryption,
            std::string key)
    {
        long dataLength;

        auto hash = ELFHash(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
        unsigned char *decryptedData = Encryptor::decryptFile<T>(
                &dataLength,
                inFilePath,
                decryption,
                hash,
                CryptoPP::AES::DEFAULT_KEYLENGTH);
        std::string serialized(reinterpret_cast<const char *const>(decryptedData), dataLength);
        return serialized;
    }
};


#endif //SECKIT_ENCRYPTOR_H
