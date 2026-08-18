#include <iostream>
#include <string>
#include <chrono>
#include <vector>
using namespace std;

class PaymentMethod {
    public:
        virtual void pay(double amount) = 0;
        virtual string getName() const = 0;
        virtual ~PaymentMethod() {}
};

class CreditCard : public PaymentMethod {
private: string last4;
public:
    CreditCard(string cardNum) : last4(cardNum.substr(cardNum.length() - 4)) {}
    void pay(double amount) override {
        cout << "[Gateway] Charging $" << amount << " to card ending " << last4 << endl;
    }
    string getName() const override { return "Credit Card ending " + last4; }
};

class PayPal : public PaymentMethod {
    private: string email;
    public:
        PayPal(string e) : email(e) {}
        void pay(double amount) override {
            cout << "[Gateway] Charging $" << amount << " to PayPal " << email << endl;
        }
        string getName() const override { return "PayPal " + email; }
};

class BankTransfer : public PaymentMethod {
    private: string last2;
    public:
        BankTransfer(string p) : last2(p) {}
        void pay(double amount) override {
            cout << "[Gateway] Charging $" << amount << " to Bank Transfer **" << last2 << endl;
        }
        string getName() const override {
            return "Bank Transfer **" + last2;
        }
};

class Wallet {
    private: 
        double balance;
        string walletOwner;
    public:
        Wallet(double initial, string owner) : balance(initial), walletOwner(owner) {}
        void deposit(double amount) { if(amount > 0) balance += amount; }
        bool withdraw(double amount) {
            if(amount > 0 && amount <= balance) { balance -= amount; return true; }
            return false;
        }
        double getBalance() const { return balance; }
        string getOwner() const { return walletOwner; } 
};

class User {
    protected:
        string name;
        Wallet* wallet;
    public:
        User(string n, double initial) : name(n) {wallet = new Wallet(initial, n); }
        virtual void displayRole() const = 0;
        virtual ~User() { delete wallet; }
        Wallet& getWallet() const { return *wallet; }
        string getName() const { return name; }
};

class RegularUser : public User {
    public:
        RegularUser(string n, double initial) : User(n, initial) {}
        void displayRole() const override {
            cout << name << " is a Regular User." << endl;
        }
        bool makePayment(PaymentMethod* method, double amount) {
            if(wallet && wallet->withdraw(amount)) {
                method->pay(amount);
                cout << name << " paid $" << amount << " using " << method->getName() << endl;
                cout << "New Balance: " << wallet->getBalance() << "\n" << endl;
                return true;
            }
            cout << name << " insufficient balance. Current balance: " << wallet->getBalance() << endl;
            return false;
        }
};

class Merchant : public User {
    private: double commissionRate;
    public:
        Merchant(string n, double initial, double rate = 0.02) : User(n, initial) {
            if(rate > 0.1) commissionRate = 0.1;
            else if(rate < 0) commissionRate = 0;
            else commissionRate = rate;
        }
        void displayRole() const override {
            cout << name << " is a Merchant, commission: " << commissionRate * 100 << "%" << endl;
        }
        void receivePayment(double amount) {
            double commission = amount * commissionRate;
            double net = amount - commission;
            wallet->deposit(net);
            cout << name << " received $" << net << " after $" << commission << " commission." << endl;
        }
};

class Transaction {
    private: 
        string from, to;
        double amount;
        string timestamp;
    public:
        Transaction(string f, string t, double a) : from(f), to(t), amount(a) {
            auto now = chrono::system_clock::now();
            time_t t_now = chrono::system_clock::to_time_t(now);
            timestamp = ctime(&t_now);
            if(!timestamp.empty() && timestamp.back() == '\n') timestamp.pop_back();
        }
        void print() const {
            cout << "[" << timestamp << "] " << from << " -> " << to << " : $" << amount << endl;
        }
};
