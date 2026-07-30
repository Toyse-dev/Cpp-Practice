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
			cout << "Drawing a circle with radius: 10cm" << endl;
		}
};

class Square: public Shape {
	public:
		void draw() override {
			cout << "Drawing a square with 4 side" << endl;
		}
};

int main() {
	
	Shape* shape[2];
	shape[0] = new Circle();
	shape[1] = new Square();
	
	for (int i = 0; i < 2; i++) {
		shape[i]->draw();
	};
	
	delete shape[0];
	delete shape[1];
	
	return 0;
}
