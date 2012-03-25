#ifndef _CRYPTO_H_
#define _CRYPTO_H_
#include <string>
#include <vector>
#include <list>
#include <cryptopp/osrng.h>
using namespace CryptoPP;

namespace WCMP {
    class Crypto
    {
        public:
        static std::string generateNonce();
        static std::string generateIV();
        static std::string generateSymmetricKey();
        static std::string symmetricEncrypt(std::string key, std::string IV, std::string message);
        static std::string symmetricDecrypt(std::string key, std::string IV, std::string ciphertext);
        static std::string asymmetricEncrypt(std::string publicKey, std::string message);
        static std::string asymmetricDecrypt(std::string privateKey, std::string ciphertext);
        static std::string asymmetricSign(std::string privateKey, std::string message);
        static bool        asymmetricVerify(std::string publicKey, std::string message, std::string signature);
        static std::string hashWithNonce(std::string nonce, std::string message);
        
    };
}
#endif

