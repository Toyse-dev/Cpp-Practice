#include <iostream>
#include <string>
using namespace std;

class PaymentMethod {
    public:
        virtual void pay(double amount) = 0;
        virtual string getName() = 0;
        virtual ~PaymentMethod() {};
};

class CreditCard : public PaymentMethod {
    private:
        string cardNumber;
    public:
        CreditCard(string cardNum) : cardNumber(cardNum.substr(cardNum.length() - 4)) {}
        void pay(double amount) override {
            cout << "Paid $" << amount << " using " << getName() << " ending with " << cardNumber << endl;
        }
        string getName() override {
            return "Credit Card";
        }
};

class PayPal : public PaymentMethod {
    private:
        string email;
    public:
        PayPal(string e) : email(e) {}
        void pay(double amount) override {
            cout << "Paid $" << amount << " using " << getName() << " account: " << email << endl;
        }
        string getName() override {
            return "PayPal";
        }
};

class Wallet : public PaymentMethod {
    private:
        double balance;
        string walletOwner;
    public:
        Wallet(string owner, double initialBalance) : walletOwner(owner), balance(initialBalance) {}
        void deposit(double amount) {
            if (amount > 0) balance += amount;
        }
        
        void pay(double amount) override {
        	withdraw(amount);
        }
        
        string getName() override {
        	return "Wallet: " + walletOwner;
        }
        
        bool withdraw(double amount) {
            if (amount > 0 && amount <= balance) {
                balance -= amount;
                return true;
            }
            return false;
        }
        double getBalance() const {
            return balance;
        }
        string getOwner() const {
            return walletOwner;
        }
};

class User {
    protected:
        string name;
        Wallet* wallet;
    public:
        User(string name, double initialBalance) : name(name) {
        	wallet = new Wallet(name, initialBalance);
        }
        
        virtual void displayRole() = 0;
        virtual ~User() {
        	delete wallet;
        }
        
        void depositToWallet(double amount) {
            if (wallet) {
                wallet->deposit(amount);
            }
        }

        Wallet& getWallet() const {
            return *wallet;
        }
        
        string getName() {
        	return name;
        }
};

class RegularUser : public User {
    public:
        RegularUser(string name, double initialBalance) : User(name, initialBalance) {}

        virtual void displayRole() {
            cout << name << " is a Regular user." << endl;
        }

        virtual void makePayment(PaymentMethod* method, double amount) {
            if (wallet && wallet->withdraw(amount)) {
                method->pay(amount);
                
                cout << name << " paid " << amount << " using " << method->getName() << "." << endl;
                cout << "New Balance: " << wallet->getBalance() << endl;
            } else {
                cout << name << " has insufficient balance to pay " << amount << "." << endl;
            }
        }
};

class Merchant : public User {
    private:
        double commissionRate;
    public:
        Merchant(string name, double initialBalance, double commissionRate) : User(name, initialBalance), commissionRate(0.02) {}
        
        virtual void displayRole() {
            cout << name << " is a Merchant with commission rate of " << commissionRate * 100 << "%" << endl;
        }
        virtual void receivePayment(double amount) {
            double commission = amount * commissionRate;
            double netAmount = amount - commission;
            if (wallet) {
                wallet->deposit(netAmount);
                cout << name << " received payment of " << netAmount << " after commission of " << commission << "." << endl;
            }
        }
};

int main() {
    RegularUser user("Alice", 5000);
    Merchant merchant("Bob's Store", 10000, 0.02);

    PaymentMethod* card = new CreditCard("1234567897889");

    user.displayRole();
    merchant.displayRole();

    cout << "User balance before: " << user.getWallet().getBalance() << endl;
    user.makePayment(card, 2000);
}
    private:
        double commissionRate;
    public:
        Merchant(string name, double initialBalance, double commissionRate) : User(name, initialBalance), commissionRate(commissionRate) {}
        virtual void displayRole() {
            cout << name << " is a Merchant with commission rate: " << commissionRate << endl;
        }
        virtual void receivePayment(double amount) {
            double commission = amount * commissionRate;
            double netAmount = amount - commission;
            if (wallet) {
                wallet->deposit(netAmount);
                cout << name << "received payment of " << netAmount << " after commission of " << commission << "." << endl;
            }
        }
};

int main() {
    RegularUser user("Alice", 5000);
    Merchant merchant("Bob's Store", 10000, 0.1);

    PaymentMethod* card = new CreditCard("1234567897889");

    user.displayRole();
    merchant.displayRole();

    cout << "User balance before: " << user.getWallet()->getBalance() << endl;
    user.makePayment(card, 2000);
}
