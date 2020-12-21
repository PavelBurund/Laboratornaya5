#include <iostream>
#include <cmath>
#include <vector>
#include <typeinfo>
#include <fstream>
#include <ostream>
#include <istream>
#include "nlohmann/json.hpp"
#include <list>

using namespace std;
using namespace nlohmann;

#define PATH "BOBROVBURUNDUKOVFILE.json"

class Shape {
public:
	double virtual calcArea() = 0;
	double virtual calcPerimeter() = 0;
	json virtual getJson() = 0;
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
	json virtual getJson()
	{
		json j;
		j["side1"] = side1;
		j["side2"] = side2;
		j["side3"] = side3;
		return j;
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
	json virtual getJson()
	{
		json j;
		j["side"] = side;
		return j;
	}
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
	json virtual getJson()
	{
		json j;
		j["width"] = width;
		j["height"] = height;
		return j;
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
	json virtual getJson()
	{
		json j;
		j["radius"] = radius;
		return j;
	}
};

void ListToJson(list<Shape*>& shapes)
{
	ofstream ostream;
	ostream.open(PATH);
	if (!ostream.is_open())
	{
		ofstream ostream(PATH);
		ostream.open(PATH);
	}

	json jsonStream;
	jsonStream["list"] = {};
	for (auto it = shapes.cbegin(); it != shapes.cend(); it++)
		jsonStream["list"].push_back((*it)->getJson());
	ostream << jsonStream;
}

list<Shape*> ListFromJson()
{
	list<Shape*> list;
	ifstream istream;
	istream.open(PATH);

	json jsonStream;
	istream >> jsonStream;
	for (auto element : jsonStream["list"])
	{
		try
		{
			json j;

			Triangle *rect = new Triangle(j.at("side1").get<double>(), j.at("side2").get<double>(), j.at("side3").get<double>());
			list.push_back(rect);
			continue;
		}
		catch(exception ex) {}

		try
		{
			json j;

			Square* rect = new Square(j.at("side").get<double>());
			list.push_back(rect);
			continue;
		}
		catch (exception ex) {}

		try
		{
			json j;

			Rectangle* rect = new Rectangle(j.at("width").get<int>(), j.at("height"));
			list.push_back(rect);
			continue;
		}
		catch (exception ex) {}

		try
		{
			json j;

			Circle* rect = new Circle(j.at("radius").get<double>());
			list.push_back(rect);
			continue;
		}
		catch (exception ex) {}

	}

	return list;
}

int main()
{
	std::list<Shape*> shapes;
	shapes.push_back(new Circle(3));
	shapes.push_back(new Rectangle(2, 3));
	shapes.push_back(new Square(3));
	shapes.push_back(new Triangle(3, 4, 5));
	ListToJson(shapes);

	return 0;
}