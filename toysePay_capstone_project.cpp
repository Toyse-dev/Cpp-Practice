#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include <vector>
using namespace std;

class PaymentMethod {
    public:
        virtual void pay(double amount) = 0;
        virtual string getName() = 0;
        virtual ~PaymentMethod() {};
};

class CreditCard : public PaymentMethod {
    private: string last4;
    public:
        CreditCard(string cardNum) : last4(cardNum.substr(cardNum.length() - 4)) {}
        void pay(double amount) override {
            cout << "[Payment Gateway] Charging $" << amount << " to card ending " << last4 << endl;
        }
        string getName() override {
            return "Credit Card ending " + last4;
        }
};

class PayPal : public PaymentMethod {
    private:
        string email;
    public:
        PayPal(string e) : email(e) {}
        void pay(double amount) override {
            cout << "[Payment Gateway] Charging $" << amount << " to account with email " << email << endl;
        }
        string getName() override {
            return "PayPal " + email;
        }
};

class BankTransfer: public PaymentMethod {
    private:
        string pin;
    public:
        BankTransfer(string p) : pin(p.substr(p.length() - 2)) {}
        void pay(double amount) override {
            cout << "[Payment Gateway] Charging $" << amount << " to account with pin ending " << pin << endl;
        }
        string getName() override {
            return "Bank Transfer with pin ending " + pin;
        }
        
};

class Wallet {
    private:
        double balance;
        string walletOwner;
    public:
        Wallet(string owner, double initialBalance) : walletOwner(owner), balance(initialBalance) {}

        void deposit(double amount) {
            if (amount > 0) balance += amount;
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
        User(string n, double initialBalance) : name(n) {
            wallet = new Wallet(n, initialBalance);
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

        string getName() const {
            return name;
        }
};

class RegularUser : public User {
    public:
        RegularUser(string name, double initialBalance) : User(name, initialBalance) {}

        virtual void displayRole() {
            cout << name << " is a Regular user." << endl;
        }

        virtual bool makePayment(PaymentMethod* method, double amount) {
            if (wallet && wallet->withdraw(amount)) {
                method->pay(amount);
                cout << name << " paid " << amount << " using " << method->getName() << "." << endl;
                cout << "New Balance: " << wallet->getBalance() << endl;
                return true;
            } else {
                cout << name << " has insufficient balance to pay " << amount << "." << endl;
                cout << "Current Balance: " << wallet->getBalance() << endl;
                return false;
            }
            cout << endl;
        }
};

class Merchant : public User {
    private:
        double commissionRate;
    public:
        Merchant(string name, double initialBalance) : User(name, initialBalance), commissionRate(0.02) {}
        virtual void displayRole() {
            cout << name << " is a Merchant with commission rate: " << commissionRate * 100 << "%" << endl;
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

class Transaction {
    private:
        string from, to;
        double amount;
        string timeStamp;
    public:
        Transaction(string f, string t, double a) : from(f), to(t), amount(a) {
            auto now = chrono::system_clock::now();
            time_t t_now = chrono::system_clock::to_time_t(now);
            timeStamp = ctime(&t_now);
        }
        void print() const {
            cout << "[" << timeStamp.substr(0, timeStamp.length() - 1)
<< "] " << from << " -> " << to << " : $" << amount << endl;        }
};

int main() {
    cout << "ToysePay Digital Wallet" << endl;
    cout << endl;
    cout << endl;

    RegularUser u("Alice", 5000);
    Merchant m("Bob's Store", 10000);

    PaymentMethod* card = new CreditCard("1234567897889");
    PaymentMethod* p = new PayPal("JohnDoe@example.com");
    PaymentMethod* tf = new BankTransfer("1234");

    u.displayRole();
    m.displayRole();

    cout << endl;

    double amount = 2000;

    cout << "User balance before: " << u.getWallet().getBalance() << endl;
    if (u.makePayment(card, amount)) {
        m.receivePayment(amount);
    } else {
        cout << "Failed. Insufficient fund." << endl;
    }

    cout << "User balance after: " << u.getWallet().getBalance() << endl;
    cout << "Merchant balance after: " << m.getWallet().getBalance() << endl;

    // Transaction history
    vector<Transaction> history;
    history.push_back(Transaction(u.getName(), m.getName(), amount));
    for(auto &tx : history) tx.print();

    delete card;
    delete p;
    delete tf;
}
