#include <iostream>

class Employee {
	public:
		virtual void work() {
			std::cout << "Employee is working..." << std::endl;
		}
		virtual ~Employee() {}
};

class Developer : public Employee {
	public:
		void work() override {
		std::cout << "Developer is coding in C++" << std::endl;
	}
};

class Designer : public Employee {
	public:
		void work() override {
			std::cout << "Designer is designing UI" << std::endl;
		}
};

int main() {
	
	Employee* staff[2];
	staff[0] = new Developer();
	staff[1] = new Designer();
	
	for (int i = 0; i < 2; ++i) {
		staff[i]->work();
	}
	
	delete staff[0];
	delete staff[1];
	
	return 0;
}
