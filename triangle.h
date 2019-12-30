#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>
#include <cstdint>

#define TYPE int // тип координат

template <typename T>
using vertex_t = std::pair<T, T>; // вершина std:pair<TYPE,TYPE>

class Triangle
{
public:
	Triangle(std::istream &is);

	friend std::ostream& operator <<(std::ostream &os, const Triangle &obj);
	friend std::istream& operator >>(std::istream &is, Triangle &obj);

	double Square();
	void Print();

private:
	vertex_t<TYPE> a, b, c;
};

#endif /*TRIANGLE_H */