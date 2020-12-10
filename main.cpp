#include "cryptlib.h"
#include "filters.h"
#include "osrng.h"
#include "modes.h"
#include "files.h"
#include "aes.h"
#include "hex.h"

#include <string>
#include <iostream>

template <class T>
void encryptFile(
        const char* outFilePath,
        const unsigned char *data,
        long dataLength,
        typename CryptoPP::CBC_Mode<T>::Encryption encryption,
        const unsigned char *iv,
        size_t ivLength,
        unsigned char *key,
        size_t keyLength)
{

    using namespace CryptoPP;

//    const CryptoPP::byte data[] = // 70 characters
//            "Now is the time for all good men to come to the aide of their country.";
//
//    const CryptoPP::byte key[16] = {
//            1,2,3,4, 1,2,3,4, 1,2,3,4, 1,2,3,4
//    };
//    const CryptoPP::byte iv[16] = {
//            8,7,6,5, 8,7,6,5, 8,7,6,5, 8,7,6,5
//    };
//
    // Write sample data
        FileSink outFile(outFilePath);
        word64 lengthToWrite = 8 + 4 + ivLength + dataLength;

        word32 h = lengthToWrite >> 32;
        word32 l = lengthToWrite;


        outFile.PutWord32(h, BIG_ENDIAN_ORDER);
        outFile.PutWord32(l, BIG_ENDIAN_ORDER);

        word32 ivL = ivLength;
        outFile.PutWord32(ivL, BIG_ENDIAN_ORDER);
        outFile.Put(iv, ivLength);

//        CBC_Mode<AES>::Encryption encryption;
        encryption.SetKeyWithIV(key, keyLength, iv, ivLength);

        StreamTransformationFilter stfEncryptor(encryption, new Redirector(outFile));
        stfEncryptor.Put(data, dataLength);
        stfEncryptor.MessageEnd();
//        StringSource(data, dataLength, true, new StreamTransformationFilter(encryption, new Redirector(outFile)));

}


template <class T>
unsigned char * decryptFile(
        long* dataLength,
        const char *inFilePath,
        typename CryptoPP::CBC_Mode<T>::Decryption decryption,
        unsigned char *key,
        size_t keyLength)
{

    using namespace CryptoPP;
    // Read sample data
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

//        CBC_Mode<AES>::Decryption decryption;
        decryption.SetKeyWithIV(key, keyLength, v, ivLength);

        *dataLength = length - 8 - 4 - ivLength;
        SecByteBlock d(*dataLength);

        auto * data = static_cast<unsigned char *>(malloc(*dataLength));
        StreamTransformationFilter stfDecryptor(decryption, new CryptoPP::ArraySink(data, *dataLength));
//        stfDecryptor.Put(reinterpret_cast<const unsigned char*>(data), dataLength);
        inFile.CopyTo(stfDecryptor);
        stfDecryptor.MessageEnd();

//        StreamTransformationFilter f(decryption, new ArraySink(d, d.size()));
//        inFile.CopyTo(f);
//        f.MessageEnd();
//
//        std::cout << "Key: ";
//        StringSource(key, 16, true, new Redirector(encoder));
//        std::cout << std::endl;
//
//        std::cout << "IV: ";
//        StringSource(v, 16, true, new Redirector(encoder));
//        std::cout << std::endl;
//
//        std::cout << "Data: ";
//        StringSource(d, d.size(), true, new Redirector(encoder));
//        std::cout << std::endl;

    return data;
//        message.assign(reinterpret_cast<const char*>(d.data()), d.size());

}

char* unsignedCharToSignedChar(unsigned char* data, size_t dataLength){
    char* res = static_cast<char *>(malloc(dataLength));
    for (int i = 0; i < dataLength; ++i) {
//        res[i] = reinterpret_cast<char>(data[i]);
    }
    return nullptr;

}
int main(int argc, char* argv[])
{
//    using namespace CryptoPP;

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

    encryptFile<CryptoPP::AES>(
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
    unsigned char *decryptedData = decryptFile<CryptoPP::AES>(
            &dataLength,
            infilePath.c_str(),
            decryption,
            const_cast<unsigned char *>(key),
            16);

    std::cout << dataLength << std::endl
    << decryptedData << std::endl;
    return 0;
}