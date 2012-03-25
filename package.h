#ifndef _PACKAGE_H_
#define _PACKAGE_H_
#include <string>
#include <list>

namespace WCMP {
    class Package
    {
        public:
        Package(std::string plaintext);
        std::string prepared(void);
        void addReceiver(std::string publicKey);
        void addSender(std::string publicKey, std::string privateKey);

        private:
        std::list<std::string> _receivers;
        std::string            _publicKey;
        std::string            _privateKey;
        std::string            _plaintext;
    };
}
#endif

