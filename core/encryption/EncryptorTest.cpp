#include "Encryptor.h"

int mainVeryOld(int argc, char* argv[])
{
    const std::string infilePath = "D:\\encrypted1.enc";
//    const CryptoPP::byte data[] =
//            "simple_password;{\"name\":\"name1\",\"password\":\"password1\",\"folder\":\"name1\"};simple_password;{\"name\":\"name2\",\"password\":\"2\",\"folder\":\"name2\"};";
    std::string str(
            "simple_password;{\"name\":\"name1\",\"password\":\"password1\",\"folder\":\"name1\"};simple_password;{\"name\":\"name2\",\"password\":\"2\",\"folder\":\"name2\"};"
    );
    const CryptoPP::byte *data = reinterpret_cast<const CryptoPP::byte *> (str.c_str());

//    const CryptoPP::byte key[16] = {
//            1,2,3,4, 1,2,3,4, 1,2,3,4, 1,2,3,4
//    };
    std::string keystr("Now is the time for bbb");
    auto* key = reinterpret_cast<const CryptoPP::byte *>(keystr.c_str());
    const CryptoPP::byte iv[16] = {
            8,7,6,5, 8,7,6,5, 8,7,6,5, 8,7,6,5
    };

    CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption encryption;
    Encryptor::encryptFile<CryptoPP::AES>(
            infilePath.c_str(),
            data,
            str.size() + 1,
//            sizeof(data),
            encryption,
            iv,
            16,
            const_cast<unsigned char *>(key),
            CryptoPP::AES::DEFAULT_KEYLENGTH);

    keystr = *(new std::string("Now is the "));
    keystr.append("time for aaa");
    key = reinterpret_cast<const CryptoPP::byte *>(keystr.c_str());
    long dataLength;
    CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption decryption;

    unsigned char *decryptedData = Encryptor::decryptFile<CryptoPP::AES>(
            &dataLength,
            infilePath.c_str(),
            decryption,
            const_cast<unsigned char *>(key),
            CryptoPP::AES::DEFAULT_KEYLENGTH);

    std::string serialized(reinterpret_cast<const char *const>(decryptedData), dataLength);
    std::cout << dataLength << std::endl
    << serialized << std::endl;
    return 0;
}


int mainOld(int argc, char* argv[])
{
    std::string pas("password");
    const CryptoPP::byte* key = Encryptor::ELFHash(pas, CryptoPP::AES::DEFAULT_KEYLENGTH);
    for (int i = 0; i < CryptoPP::AES::DEFAULT_KEYLENGTH; ++i) {
        std::cout << (static_cast<int>(key[i]) & 0xFF) << " ";
    }
    std::cout << std::endl;
    pas = "pass";
    pas.append("word");
    key = Encryptor::ELFHash(pas, CryptoPP::AES::DEFAULT_KEYLENGTH);
    for (int i = 0; i < CryptoPP::AES::DEFAULT_KEYLENGTH; ++i) {
        std::cout << (static_cast<int>(key[i]) & 0xFF) << " ";
    }
    return 0;
}

int main(int argc, char* argv[])
{
    const std::string infilePath = "D:\\encrypted1.enc";
    std::string str(
            "simple_password;{\"name\":\"name1\",\"password\":\"password1\",\"folder\":\"name1\"};simple_password;{\"name\":\"name2\",\"password\":\"2\",\"folder\":\"name2\"};"
    );
    std::string keystr("Now is the time for bbb");

    CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption encryption;
    Encryptor::encryptFile<CryptoPP::AES>(
            infilePath.c_str(),
            str,
            encryption,
            keystr
    );
    CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption decryption;
    std::cout << Encryptor::decryptFile<CryptoPP::AES>(infilePath.c_str(), decryption, keystr);
    return 0;
}
