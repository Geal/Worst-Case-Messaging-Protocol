#include "crypto.h"

#include <cryptopp/rsa.h>
#include <cryptopp/pubkey.h>
#include <cryptopp/pssr.h>
#include <cryptopp/osrng.h>
#include <cryptopp/base64.h>
#include <cryptopp/files.h>
#include <cryptopp/modes.h>

using namespace std;
using namespace CryptoPP;

namespace WCMP {
    string Crypto::generateNonce()
    {
        string bytes;
        AutoSeededRandomPool rng;
        byte randomBytes[10];
        rng.GenerateBlock(randomBytes, 10);
        bytes.insert (bytes.begin(), randomBytes, randomBytes+10);
        return bytes;
    }

    string Crypto::generateIV()
    {
        string bytes;
        AutoSeededRandomPool rng;
        byte randomBytes[CryptoPP::AES::BLOCKSIZE];
        rng.GenerateBlock(randomBytes, CryptoPP::AES::BLOCKSIZE);
        bytes.insert (bytes.begin(), randomBytes, randomBytes+CryptoPP::AES::BLOCKSIZE);
        return bytes;
    }

    string Crypto::generateSymmetricKey()
    {
        string bytes;
        SecByteBlock key(SHA256::DIGESTSIZE);
        AutoSeededRandomPool rng;
        byte randomBytes[CryptoPP::AES::BLOCKSIZE];
        rng.GenerateBlock(randomBytes, CryptoPP::AES::BLOCKSIZE);
        //bytes.insert (bytes.begin(), randomBytes, randomBytes+CryptoPP::AES::BLOCKSIZE);
        SHA256().CalculateDigest(key, randomBytes, CryptoPP::AES::BLOCKSIZE);

        //FIXME: bytes.insert(bytes.begin(), key.BytePtr, key.BytePtr+SHA256::DIGESTSIZE);
        return "a"; //FIXME: bytes;
    }

    string Crypto::symmetricEncrypt(string aeskey, string IV, string plaintext)
    {
        byte key[ CryptoPP::AES::DEFAULT_KEYLENGTH ], iv[ CryptoPP::AES::BLOCKSIZE ];
        memset( key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH );
        memset( iv, 0x00, CryptoPP::AES::BLOCKSIZE );

        //
        // String and Sink setup
        //
       // std::string plaintext = "Now is the time for all good men to come to the aide...";
        std::string ciphertext;

        //
        // Dump Plain Text
        //
        std::cout << "Plain Text (" << plaintext.size() << " bytes)" << std::endl;
        std::cout << plaintext;
        std::cout << std::endl << std::endl;

        //
        // Create Cipher Text
        //
        //AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
        //CBC_Mode<AES>::Encryption cbcEncryption( aesEncryption, iv );
        CBC_Mode<AES>::Encryption cbcEncryption( key, CryptoPP::AES::DEFAULT_KEYLENGTH, iv);

        StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink( ciphertext ) );
        stfEncryptor.Put( reinterpret_cast<const unsigned char*>( plaintext.c_str() ), plaintext.length() + 1 );
        stfEncryptor.MessageEnd();
        return ciphertext;
    }

    string Crypto::symmetricDecrypt(string key, string IV, string ciphertext)
    {
        CBC_Mode< AES >::Decryption d;
        d.SetKeyWithIV( (const unsigned char *)key.c_str(), key.size(), (const unsigned char *)IV.c_str() );

        string recovered;
        // The StreamTransformationFilter removes
        //  padding as required.
        StringSource( ciphertext, true, 
            new StreamTransformationFilter( d,
                new StringSink( recovered )
            ) // StreamTransformationFilter
        ); // StringSource

        cout << "recovered text: " << recovered << endl;
        return recovered;
    }

    string Crypto::asymmetricEncrypt(string publicKey, string message)
    {
        AutoSeededRandomPool rng;

        RSAES<OAEP<SHA1, P1363_MGF1> >::Encryptor myencryptor(
            StringSource( publicKey, true,
            new Base64Decoder).Ref() );
 
        size_t sz = myencryptor.CiphertextLength(message.size());
        SecByteBlock sbbCipherText( sz );

        myencryptor.Encrypt(
        rng,
        (byte const*) message.data(),
        message.size(),
        sbbCipherText.begin());

        string encrypted;
        Base64Encoder b64( new StringSink( encrypted ) );
        b64.Put(sbbCipherText.begin(), sbbCipherText.size());
        b64.MessageEnd();
        return encrypted;
    }

    string Crypto::asymmetricDecrypt(string privateKey, string ciphertext)
    {
        return "a";
    }

    string Crypto::asymmetricSign(string privateKey, string message)
    {
        return "a";
    }

    bool Crypto::asymmetricVerify(string publicKey, string message, string signature)
    {
        RSASS<PSS, SHA1>::Verifier verifier(
            StringSource( publicKey, true,
            new Base64Decoder).Ref() );

        string decodedsig;
        StringSource( (const byte *)signature.c_str(), signature.size(), true,
            new Base64Decoder( new StringSink( decodedsig ) ) );

        bool verified = verifier.VerifyMessage((const byte *) message.c_str(), message.size(), (const byte *) decodedsig.c_str(), decodedsig.size());
        return verified;
    }
               
    string Crypto::hashWithNonce(string nonce, string message)
    {
        string hashed;
        StringSource( nonce+message, true,
                    new Base64Decoder(new StringSink(hashed)));
        return hashed;
    }

}
