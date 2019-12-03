// Representa vectores o puntos en dos dimensiones

#ifndef __VECTOR2D_H__
#define __VECTOR2D_H__

#include "checkML.h"
#include <cmath>
#include <iostream>

const double PI = 3.14159265358979323846;

class Vector2D
{
private:
	double x_;
	double y_;

public:
	Vector2D() : x_(), y_() {}
	Vector2D(double x, double y) : x_(x), y_(y) {}
	~Vector2D() {}

	// Gets
	double getX() const { return x_; }
	double getY() const { return y_; }

	// Sets
	void setX(double x) { x_ = x; }
	void setY(double y) { y_ = y; }

	// Normaliza el vector
	void normalize();
	// Operando suma de vectores
	Vector2D operator+(const Vector2D& v) const;
	// Operando resta de vectores
	Vector2D operator-(const Vector2D& v) const;
	// Operando producto escalar de vectores
	Vector2D operator*(double d)const;
	// Operando producto de un vector por un escalar
	double operator*(const Vector2D& d) const;

	// Operando para el cout
	friend std::ostream& operator<<(std::ostream& out, const Vector2D& v);
	// Operando para el cout
	friend std::istream& operator>>(std::istream& in, Vector2D& v);

	// AUX: para girar el arco
	void rotate(double degrees);
};

typedef Vector2D Point2D;

#endif // !__VECTOR2D_H__