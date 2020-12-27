#include <iostream>
#include <vector>
#include <typeinfo>
#include <fstream>
#include <ostream>
#include <istream>
#include "nlohmann/json.hpp"
#include <list>
#include "Shapes.h"

using namespace std;
using namespace nlohmann;

#define PATH "BOBROVBURUNDUKOVFILE.json"

template <class T>
json getJson(T obj)
{
	if (typeid(T).name() == typeid(Triangle).name())
	{
		json j;
		j["side1"] = obj.getSide1();
		j["side2"] = obj.getSide2();
		j["side3"] = obj.getSide3();
		return j;
	}
	else if (typeid(T).name() == typeid(Rectangle).name())
	{
		json j;
		j["width"] = obj.getWidth();
		j["height"] = obj.getHeight();
		return j;
	}
	else if (typeid(T).name() == typeid(Circle).name())
	{
		json j;
		j["radius"] = obj.getRadius();
		return j;
	}
	else if (typeid(T).name() == typeid(Square).name())
	{
		json j;
		j["side"] = obj.getSide();
		return j;
	}
}

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
		jsonStream["list"].push_back(getJson(*it));
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

			Triangle* rect = new Triangle(j.at("side1").get<double>(), j.at("side2").get<double>(), j.at("side3").get<double>());
			list.push_back(rect);
			continue;
		}
		catch (exception ex) 
		{
			throw std::exception("Некорректный файл");
		}

		try
		{
			json j;

			Square* rect = new Square(j.at("side").get<double>());
			list.push_back(rect);
			continue;
		}
		catch (exception ex) 
		{
			throw std::exception("Некорректный файл");
		}

		try
		{
			json j;

			Rectangle* rect = new Rectangle(j.at("width").get<int>(), j.at("height"));
			list.push_back(rect);
			continue;
		}
		catch (exception ex)
		{
			throw std::exception("Некорректный файл");
		}

		try
		{
			json j;

			Circle* rect = new Circle(j.at("radius").get<double>());
			list.push_back(rect);
			continue;
		}
		catch (exception ex)
		{
			throw std::exception("Некорректный файл");
		}

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