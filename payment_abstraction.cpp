#include <iostream>
#include <string>
using namespace std;

class PaymentMethod {
	public:
		virtual void pay(double amount) = 0;
		virtual void printReceipt() = 0;
		virtual ~PaymentMethod() {};
};

class CreditCard : public PaymentMethod {
	private:
		string cardNumber;
	public:
		
		CreditCard(string num) : cardNumber(num.substr(num.length() - 4)) {}

		void pay(double am) override {
			cout << "Paid $" << am <<" using Credit Card ending in "  << cardNumber << endl;
		}
		
		void printReceipt() override {
			cout << "Credit Card receipt" << endl;
		}
};

class PayPal : public  PaymentMethod {
	private: string email;
	public:
		PayPal(string e) : email(e) {}
		void pay(double p) override {
			cout << "Paid $" << p << " using Paypal account " << email << endl;
		}
		void printReceipt() override {
			cout << "PayPal receipt" << endl;
		}
};

int main() {
	PaymentMethod* pm = new CreditCard("12345671234567");
	pm->pay(50);
	pm->printReceipt();
	
	cout << endl;
	
	PaymentMethod* pay = new PayPal("toyse@gmail.com");
	pay->pay(20);
	pay->printReceipt();
	
	return 0;
}
