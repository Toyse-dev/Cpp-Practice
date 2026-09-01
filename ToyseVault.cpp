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

            if (!inFile.is_open()) return;

            std::string line;

            while (std::getline(inFile, line)) {
                if (line.empty()) continue;
                
                size_t pos1 = line.find("|");
                size_t pos2 = line.find("|", pos1 + 1);

                std::string site = line.substr(0, pos1);
                std::string username = line.substr(pos1 + 1, pos2 - pos1 - 1);
                std::string password = line.substr(pos2 + 1);

                items.push_back(Credential(site, username, password));
            }
            inFile.close();
        }

        void searchBySite(const std::string query) {
            bool found = false;
            for (const auto& c : items) {
                if (c.getSite() == query || c.getUser() == query) {
                    c.display();
                    std::cout << "---------------------" << std::endl;
                    found = true;
                }
            }

            if (!found) {
                std::cout << "No Credential found " << query << std::endl;
            }
        }

        void deleteByUserName(const std::string deleteUser) {
            items.erase(
                std::remove_if(items.begin(), items.end(), [&](const Credential& c) {
                    return c.getUser() == deleteUser;;
                }), items.end()
            );
        }
};

int main() {
    Vault myVault;

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
            case 1: {
                std::string s, u, p;
 
                std::cout << "Enter site name: "; std::cin >> s;
                std::cout << "Enter username: "; std::cin >> u;
                std::cout << "Enter password: "; std::cin >> p;

                
                myVault.add(Credential(s, u, p));
                myVault.saveToFile();

                std::cout << "Credentials Added!/n";
                std::cout << "-------------------------" << std::endl;
                std::cout << std::endl;

                break;
            }
            
            case 2: {
                myVault.listAll();

                std::cout << "Vault size: " << myVault.size() << std::endl;
                std::cout << std::endl;

                break;
            }

            case 3: {
                std::string searchTerm;

                std::cout << "Enter site name to search: "; std::cin >> searchTerm;
                myVault.searchBySite(searchTerm);

                std::cout << std::endl;

                break;
            }
            
            case 4: {
            std::string deleteTerm;

            std::cout << "Enter word to delete: ";
            std::cin >> deleteTerm;

            myVault.deleteByUserName(deleteTerm);
                std::cout << "Credentials deleted" << std::endl;
                std::cout << std::endl;

                break;
            }

            case 5: {
                std::cout << "Goodbye!!" << std::endl;
                return 0;

                break;
            }

            default:
                std::cout << "Invalid choice" << std::endl;
        }
    } while (choice != 5);

    return 0;
}

// QUESTIONS:
// Ho do I prevent duplicate sites?
// What happens if vault.txtis corrupted?
// Should Vault be responsible for file I/O or should I create a separate FileManager class? Why?
