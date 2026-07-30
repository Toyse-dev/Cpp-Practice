#include <iostream>

class Shape {
	public:
	void virtual draw() {
		std::cout << "Drawing a generic shape" << std::endl;
	}
	virtual ~Shape() {}
};

class Circle: public Shape {
	private: double radius;
	public:
		Circle(double r) : radius(r) {}
		
		void draw() override {
			std::cout << "Drawing a circle with: " << radius << "cm radius" << std::endl;
		}
};

class Square: public Shape {
	private: double side;
	public:
		Square(double s) : side(s) {}
		
		void draw() override {
			std::cout << "Drawing a square with: " << side << "cm side" << std::endl;
		}
};

int main() {
	
	Shape* shape[2];
	shape[0] = new Circle(10);
	shape[1] = new Square(4);
	
	for (int i = 0; i < 2; i++) {
		shape[i]->draw();
	}
	
	delete shape[0];
	delete shape[1];
	
	return 0;
}
