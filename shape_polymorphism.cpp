#include <iostream>
using namespace std;

class Shape {
	public:
		virtual void draw() {
			cout << "Drawing a generic shape" << endl;
		}
		virtual ~Shape() {}
};

class Circle: public Shape {
	public:
		void draw() override {
			cout << "Drawing a circle with radius: " << <radius> << endl;
		}
};

class Square: public Shape {
	public:
		void draw() override {
			cout << "Drawing a square with sode:" << <side> << endl;
		}
};


