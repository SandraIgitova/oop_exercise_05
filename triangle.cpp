#include <cmath>
#include <cstring>
#include <iostream>
#include "triangle.h"

//---- математика для треугольника------------------------------
 // сортировка вершин
template <typename T>
void Sort(int n, vertex_t<T> *arr) {
	for (int i = 1; i < n; i++) {
		for (int j = i; j > 0 && arr[j - 1].first > arr[j].first; j--) {
			vertex_t<T> tmp = arr[j - 1];
			arr[j - 1] = arr[j];
			arr[j] = tmp;
		}
	}
}
// площадь треугольника по формуле Герона
template <typename T>
double TriangleArea(vertex_t<T> a, vertex_t<T> b, vertex_t<T> c)
{
	vertex_t<T> mas[3] = { a, b, c };
	Sort(3, mas);
	// x- first, y - second
	if (mas[0].first == mas[1].first)
		if (mas[0].second > mas[1].second) { vertex_t<T> hlp = mas[1]; mas[1] = mas[0]; mas[0] = hlp; }
	if (mas[1].first == mas[2].first)
		if (mas[2].second > mas[1].second) { vertex_t<T> hlp = mas[1]; mas[1] = mas[2]; mas[2] = hlp; }
		else if (mas[1].second < mas[2].second) { vertex_t<T> hlp = mas[1]; mas[1] = mas[2]; mas[2] = hlp; }
	double a1 = sqrt(pow(mas[1].first - mas[0].first, 2) + pow(mas[1].second - mas[0].second, 2));
	double b1 = sqrt(pow(mas[1].first - mas[2].first, 2) + pow(mas[2].second - mas[1].second, 2));
	double c1 = sqrt(pow(mas[2].first - mas[0].first, 2) + pow(mas[0].second - mas[2].second, 2));
	double p = (a1 + b1 + c1) / 2;
	return  sqrt(p*(p - a1)*(p - b1)*(p - c1));
}
// ---------------- конец математики ----------------------

Triangle::Triangle(std::istream& is)
{
	// ввод треугольника
	std::cout << "Введите 6 чисел координат сторон треугольника, чередуя X и Y: \n";
	std::cin >> a.first >> a.second >> b.first >> b.second >> c.first >> c.second;
}

double Triangle::Square()
{
	return  TriangleArea(a, b, c);
}

void Triangle::Print()
{
		std::cout << "Координаты вершин:" << std::endl;
		std::cout << "\t" << "X" << "\t" << "Y" << std::endl;
		std::cout << "\t" << a.first << "\t" << a.second << std::endl;
		std::cout << "\t" << b.first << "\t" << b.second << std::endl;
		std::cout << "\t" << c.first << "\t" << c.second << std::endl;
		std::cout << "Площадь фигуры:" << std::endl;
		std::cout << "\t" << Square() << std::endl;
}

std::ostream& operator <<(std::ostream &os, const Triangle &obj)
{
	os << "Координаты вершин:" << std::endl\
		<< "\t" << "X" << "\t" << "Y" << std::endl\
		<< "\t" << obj.a.first << "\t" << obj.a.second << std::endl\
		<< "\t" << obj.b.first << "\t" << obj.b.second << std::endl\
		<< "\t" << obj.c.first << "\t" << obj.c.second << std::endl\
		<< "Площадь фигуры:" << std::endl;
	return os;
}

std::istream& operator >>(std::istream &is, Triangle &obj)
{
	std::cout << "Введите 6 чисел координат сторон треугольника, чередуя X и Y: \n";
	is >> obj.a.first >> obj.a.second >> obj.b.first >> obj.b.second >> obj.c.first >> obj.c.second;
	return is;
}