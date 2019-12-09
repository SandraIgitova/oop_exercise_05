//C++ 14
#include <algorithm>
#include <cstdio>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <cassert>
#include<tuple>
#include "list.h"

#define TYPE int // тип координат

template <typename T>
using vertex_t = std::pair<T, T>; // вершина std:pair<TYPE,TYPE>

//------------------- математика------------------------------
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

template <typename T>// вывод координат вершин треугольника
void VertexOutput(vertex_t<T> a, vertex_t<T> b, vertex_t<T> c) {
	std::cout << "\t" << a.first << "\t" << a.second << std::endl;
	std::cout << "\t" << b.first << "\t" << b.second << std::endl;
	std::cout << "\t" << c.first << "\t" << c.second << std::endl;
}

// ---------------- классы --------------------------------
template <class T>
class Triangle
{
public:
	using vertex_t = std::pair<T, T>;
	vertex_t a, b, c;
	Triangle(vertex_t A, vertex_t B, vertex_t C) {
		a = A; b = B; c = C;
	}
	double Area() {
		return TriangleArea(a, b, c);
	}
	void Output(uint n) {
		std::cout << "Фигура № " << n << std::endl;
		std::cout << "Координаты вершин:" << std::endl;
		std::cout << "\t" << "X" << "\t" << "Y" << std::endl;
		VertexOutput(a, b, c);
		std::cout << "Площадь фигуры:" << std::endl;
		std::cout << "\t" << Area() << std::endl;
	}

};
// ------------ конец классов ------------------------

// ------------ ввод/вывод для main() ----------------
void MainMenuOutput(uint32_t& x) {
	std::cout << "\
1. Добавить треугольник в список в указанную позицию\n\
2. Удалить треугольник из списка\n\
3. Вывести все введенные фигуры (std::for_each)\n\
4. Вывести количество элементов, площадь которых меньше заданной (std::count_if) \n\
Ctrl-D Выход из программы\n\n" << std::endl;
	std::cin >> x;
	std::cout << std::endl;
}

int IndexInput() {
	int index;
	std::cout << "Введите индекс элемента в списке\n" << std::endl;
	std::cin >> index;
	std::cout << std::endl;
	return index;
}

void TriangleInput(containers::list<Triangle<TYPE>>& t) {
	using vertex_t = std::pair<TYPE, TYPE>;
	vertex_t A, B, C;
	std::cout << "Введите 6 чисел координат сторон треугольника, чередуя X и Y: \n";
	std::cin >> A.first >> A.second >> B.first >> B.second >> C.first >> C.second;
	t.insert(IndexInput(), Triangle<TYPE>(A, B, C));
}

void IndexInput(containers::list<Triangle<TYPE>>& t) {
	uint index;
	std::cout << "Введите индекс элемента в списке\n" << std::endl;
	std::cin >> index;
	t.erase(t.get_iterator(index));
	std::cout << std::endl;
}

uint fc;
void output(Triangle<TYPE> i) {
	i.Output(fc++);
}
void TrianglesOutput(containers::list<Triangle<TYPE>>& t) {
	std::cout << "Вывод с всех фигур" << std::endl;
	fc = 0;
	std::for_each(t.begin(), t.end(), output);
	std::cout << "------------------\n" << std::endl;
}

uint param;
bool comparison(Triangle<TYPE> i) {
	if (i.Area() < param) { return true; }
	else return false;
}
void TrianglesCounter(containers::list<Triangle<TYPE>>& t) {
	std::cout << "Введите величину максимальной площади\n" << std::endl;
	std::cin >> param;
	std::cout << "Количество элементов с площадью меньше заданной: ";
	std::cout << std::count_if(t.begin(), t.end(), comparison);
	std::cout << std::endl << "------------------\n" << std::endl;
}
// -------------------------------------------------

int main()
{
	using vertex_t = std::pair<TYPE, TYPE>;
	uint32_t x = 0;
	containers::list<Triangle<TYPE>> t;

	while (std::cin)
	{
		MainMenuOutput(x);
		if (x == 1) {
			TriangleInput(t);
			continue;
		}
		if (x == 2) {
			IndexInput(t);
			continue;
		}
		if (x == 3) {
			TrianglesOutput(t);
			continue;
		}
		if (x == 4) {
			TrianglesCounter(t);
		}
	}
	return 0;
}