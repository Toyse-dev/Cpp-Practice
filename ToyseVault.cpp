#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

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
        std::string getSite() const { return site; }
        std::string getUser() const { return username; }
        std::string getPass() const { return password; }

        std::string makeString() const {
        return site + "|" + username + "|" + password;
    }
};

class Vault {
    private:
        std::vector <Credential> items;
        std::string fileName = "vault.txt";
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
                    outFile << item.makeString() << '\n';
                }
                outFile.close();
            }
        }

        void loadFromFile() {
            std::ifstream inFile(fileName);

            if (!inFile.is_open()) {
                std::cerr << "Failed to read from file" << std::endl;
            }

            std::string line;

            while (std::getline(inFile, line)) {
                std::cout << line << std::endl;
            }
            inFile.close();
        }

        void searchBySite(const std::string searchSite) {
            bool found = false;
            for (const auto& c : items) {
                if (c.getSite() == searchSite) {
                    c.display();
                    std::cout << "---------------------" << std::endl;
                    found = true;
                }
            }

            if (!found) {
                std::cout << "No Credential found " << searchSite << std::endl;
            }
        }

        void searchByUsername(const std::string searchUser) {
            bool found = false;
            for (const auto& c : items) {
                if(c.getUser() == searchUser) {
                    c.display();
                    std::cout << "----------------------" << std::endl;
                    found = true;
                }
            }
            if (!found) {
                std::cout << "No username found " << searchUser << std::endl;
            }
        }
};

int main() {
    Vault myVault;

    Credential cred1("Facebook", "Toyse", "12345678");
    Credential cred2("Twitter", "Ayomi", "Ayomi12");
    Credential cred3("Thread", "Ola", "88522225");

    myVault.saveToFile();
    myVault.loadFromFile();

    int choice;

    do {
        std::cout << "---- MENU LOOP ----" << std::endl;
        std::cout << "1. Add" << std::endl;
        std::cout << "2. List" << std::endl;
        std::cout << "3. Search" << std::endl;
        std::cout << "4. Delete" << std::endl;
        std::cout << "5. Exit" << std::endl;

        std::cout << std::endl;

        std::cout << "Choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                myVault.add(cred1);
                myVault.add(cred2);
                myVault.add(cred3);

                std::cout << "Credentials Added" << std::endl;
                std::cout << "-------------------------" << std::endl;

                break;
            
            case 2:
                cred1.display();
                cred2.display();
                myVault.listAll();
                std::cout << "Vault size: " << myVault.size() << std::endl;

                std::cout << std::endl;

                break;

            case 3:
                myVault.searchBySite("Twitter");
                myVault.searchByUsername("Ola");

                break;

            default:
                std::cout << "Invalid choice" << std::endl;
        }
    } while (choice != 6);

    return 0;
}
