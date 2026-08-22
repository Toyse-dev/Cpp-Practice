#include <iostream>
#include <string>
#include <vector>

class Credentials {
    private:
        std::string site, username, password;
    public:
        Credentials(std::string s, std::string u, std::string p) : site(s), username(u), password(p.substr(p.length() - 4)) {}
        void display() const {
            std::cout << "Site name: " << site << std::endl;
            std::cout << "Username: " << username << std::endl;
            if (password.length() <= 8) {
                std::cout << "Password too weak, reset password" << std::endl;
            } else {
                std::cout << "Password: " << " ****" << password << std::endl;
            }
        };
        std::string getSite() { return site; }
        std::string getUser() { return username; }
        std::string getPass() { return password; }
};

class Vault {
    private:
        std::vector <Credentials> items;
        std::string fileName;
};
