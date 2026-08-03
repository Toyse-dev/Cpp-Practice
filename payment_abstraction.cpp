#include <iostream>
#include <string>

class PaymentMethod {
	public:
		virtual void pay(double amount) = 0;
		virtual void printReceipt() = 0;
		virtual ~PaymentMethod() {};
};

class CreditCard : public PaymentMethod {
	private:
		std::string cardNumber;
	public:
		
		CreditCard(std::string num) : cardNumber(num.substr(num.length() - 4)) {}

		void pay(double am) override {
			std::cout << "Paid $" << am <<" using Credit Card ending in "  << cardNumber << std::endl;
		}
		
		void printReceipt() override {
			std::cout << "Credit Card receipt" << std::endl;
		}
};

class PayPal : public  PaymentMethod {
	private: std::string email;
	public:
		PayPal(std::string e) : email(e) {}
		void pay(double p) override {
			std::cout << "Paid $" << p << " using PayPal account " << email << std::endl;
		}
		void printReceipt() override {
			std::cout << "PayPal receipt" << std::endl;
		}
};

int main() {
	PaymentMethod* pm = new CreditCard("12345671234567");
	pm->pay(50);
	pm->printReceipt();
	
	std::cout << std::endl;
	
	PaymentMethod* pay = new PayPal("toyse@gmail.com");
	pay->pay(20);
	pay->printReceipt();
	
	return 0;
}
