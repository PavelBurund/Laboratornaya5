#include <cmath>
class Shape {
public:
	double virtual calcArea() = 0;
	double virtual calcPerimeter() = 0;
};

class Triangle : public Shape {
private:
	double side1 = 0, side2 = 0, side3 = 0;
public:
	Triangle(double side1, double side2, double side3) : side1(side1), side2(side2), side3(side3)
	{
		if (!(side1 + side2 > side3 || side2 + side3 > side1 || side1 + side3 > side2)) throw("Вы ввели несуществущий треугольник");
		if (side1 <= 0 || side2 <= 0 || side3 <= 0) throw("Некорректное значение сторон");
	}
	double virtual calcArea() override
	{
		int Perimetr, HalfP;
		Perimetr = side1 + side2 + side3;
		HalfP = Perimetr / 2;
		return sqrt(HalfP * (HalfP - side1) * (HalfP - side2) * (HalfP - side3));
	}
	double virtual calcPerimeter() override
	{
		return side1 + side2 + side3;
	}
	double getSide1() {
		return side1;
	}
	double getSide2() {
		return side2;
	}
	double getSide3() {
		return side3;
	}
};
class Square : public Shape {
private:
	double side = 0;
public:
	Square(double side) : side(side)
	{
		if (side <= 0) throw("Некорректное значение стороны");
	}
	double virtual calcArea() override
	{
		return pow(side, 2);
	}
	double virtual calcPerimeter() override
	{
		return side * 4;
	}
	double getSide() { return side; }
};
class Rectangle : public Shape {
private:
	double width = 0, height = 0;
public:
	Rectangle(int width, int height) : width(width), height(height)
	{
		if (width <= 0 || height <= 0) throw("Некорректное значение сторон");
	}
	double virtual calcArea() override
	{
		return width * height;
	}
	double virtual calcPerimeter() override
	{
		return width * 2 + height * 2;
	}
	double getWidth() {
		return width;
	}
	double getHeight() {
		return height;
	}
};
class Circle : public Shape {
private:
	double radius = 0;
public:
	Circle(double radius) : radius(radius)
	{
		if (radius <= 0) throw("Некорректное значение радиуса");
	}
	double virtual calcArea() override
	{
		return  3.14 * radius * radius;
	}
	double virtual calcPerimeter()
	{
		return 3.14 * 2 * radius;
	}
	double getRadius() { return radius; }
};