#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class Credential {
    private:
        std::string site, username, password;
    public:
        Credential(std::string s, std::string u, std::string p) : site(s), username(u), password(p) {}
        void display() const {
            std::cout << "Site name: " << site << std::endl;
            std::cout << "Username: " << username << std::endl;
            if (password.length() < 8) {
                std::cout << "Password too weak, reset password" << std::endl;
            } else {
                std::string pass = password.substr(password.length() - 4);
                std::cout << "Password: " << " ****" << pass << std::endl;
            }
        };
        std::string getSite() { return site; }
        std::string getUser() { return username; }
        std::string getPass() { return password; }
};

class Vault {
    private:
        std::vector <Credential> items;
        std::string fileName;
    public:
        void add(const Credential& c) {
            items.push_back(c);
        }

        size_t size() const {
            return items.size();
        }

        void listAll() {
            if (items.empty()) {
                std::cout << "This vault is empty" << std::endl;
                return;
            }

            std::cout << "---- Vault Items ----" << std::endl;
            for (const auto& item : items) {
                item.display();
            }
        }

        void saveToFile() {
            std::ofstream outFile(fileName);

            if (outFile.is_open()) {
                for (const auto& item : items) {
                    outFile << item.display() << '\n';
                }
            }
        }
};

int main() {
    Vault myVault;

    Credential cred1("Facebook", "Toyse", "12345678");
    Credential cred2("Twitter", "Ayomi", "Ayomi12");

    myVault.add(cred1);
    myVault.add(cred2);

    cred1.display();
    cred2.display();

    myVault.listAll();

    std::cout << "Vault size: " << myVault.size() << std::endl;

    return 0;
}
