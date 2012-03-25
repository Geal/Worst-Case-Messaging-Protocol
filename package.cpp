#include "package.h"

#include <iostream>
#include <sstream>
#include "crypto.h"

using namespace std;

namespace WCMP {
	Package::Package(string plaintext)
	{
        _plaintext = plaintext;
		cout << "plaintext message: " << plaintext << endl;
	}

	string Package::prepared()
	{
        ostringstream package;

        //insert the emitter
        string nonce = Crypto::generateNonce();
        package << nonce;
        package << endl;
        package << Crypto::hashWithNonce(nonce, _publicKey) << endl;
        string IV = Crypto::generateNonce();
        
        //encrypt with a symmetric key
        package << IV << endl;
        string symmetricKey = Crypto::generateSymmetricKey();
        package << Crypto::symmetricEncrypt(symmetricKey, IV, _plaintext) << endl;
        
        //use convergent encryption to give they key to the receivers
        string nonce2 = Crypto::generateNonce();
        list<string>::iterator receiversIt;
        for(receiversIt = _receivers.begin(); receiversIt != _receivers.end(); receiversIt++)
        {
            string publicKey = *receiversIt;
            package << Crypto::asymmetricEncrypt(publicKey, symmetricKey) << "|" << Crypto::hashWithNonce(nonce2, publicKey) << "!";
        }
        package << endl;

        //sign the whole package
        string signature = Crypto::asymmetricSign(_privateKey, package.str());
        package << signature << endl;
		return package.str();
	}

	void Package::addReceiver(string publicKey)
	{
        _receivers.push_back(publicKey);
	}

    void Package::addSender(string publicKey, string privateKey)
    {
        _publicKey = publicKey;
        _privateKey = privateKey;
    }
}
