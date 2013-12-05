/*
 * CS585
 *
 * Team Bammm
 * 	Alvaro Home
 * 	Matt Konstantinou
 * 	Michael Abramo
 *	Matt Witkowski
 *  Bradley Crusco
 * Description:
 * Vector3D cpp file.
 *
 */

#include "Vector3D.h"

namespace bammm
{
	Vector3D::Vector3D()
	{
		_x = 0;
		_y = 0;
		_z = 0;
	}

	Vector3D::Vector3D(float x, float y, float z)
	{
		_x = x;
		_y = y;
		_z = z;
	}

	Vector3D::~Vector3D()
	{
	}

	void Vector3D::set(float x, float y, float z)
	{
		_x = x;
		_y = y;
		_z = z;
	}

	void Vector3D::normalize()
	{
		float normal = magnitude();
		_x = _x / normal;
		_y = _y / normal;
		_z = _z / normal;
	}

	float Vector3D::magnitude()
	{
		return sqrt((_x * _x) + (_y * _y) + (_z * _z));
	}

	float Vector3D::squareMagnitude()
	{
		return (_x * _x) + (_y * _y) + (_z * _z);
	}

	float Vector3D::dotProduct(Vector3D &vect)
	{
		return (_x * vect.getX()) + (_y * vect.getY()) + (_z * vect.getZ());
	}

	void Vector3D::divideVector(int scalar)
	{
		_x = _x / scalar;
		_y = _y / scalar;
		_z = _z / scalar;
	}

	void Vector3D::multiplyVector(int scalar)
	{
		_x = _x * scalar;
		_y = _y * scalar;
		_z = _z * scalar;
	}

	Vector3D Vector3D::crossProduct(Vector3D &vector)
	{
		return Vector3D((_y * vector.getZ()) - (_z - vector.getY()),
				(_x * vector.getZ()) - (_z - vector.getX()),
				(_x * vector.getY()) - (_y - vector.getX()));

	}

	string Vector3D::toString()
	{
		return "(" + to_string(_x) + "," + to_string(_y) + "," + to_string(_z) + ")";
	}

	bool Vector3D::operator==(const Vector3D &vector)
	{
		if ((_x == vector.getX()) && (_y == vector.getY())
				&& (_z == vector.getZ()))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Vector3D::operator!=(const Vector3D &vector)
	{
		if ((_x == vector.getX()) && (_y == vector.getY())
				&& (_z == vector.getZ()))
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	Vector3D Vector3D::operator+(const Vector3D &vector)
	{
		return Vector3D(_x + vector.getX(), _y + vector.getY(),
				_z + vector.getZ());
	}

	Vector3D& Vector3D::operator+=(const Vector3D &vector)
	{
		_x += vector.getX();
		_y += vector.getY();
		_z += vector.getZ();
		return *this;
	}

	Vector3D Vector3D::operator-(const Vector3D &vector)
	{
		return Vector3D(_x - vector.getX(), _y - vector.getY(),
				_z - vector.getZ());
	}

	Vector3D& Vector3D::operator-=(const Vector3D &vector)
	{
		_x -= vector.getX();
		_y -= vector.getY();
		_z -= vector.getZ();
		return *this;
	}

	float Vector3D::getX() const
	{
		return _x;
	}

	float Vector3D::getY() const
	{
		return _y;
	}

	float Vector3D::getZ() const
	{
		return _z;
	}

	float& Vector3D::getX()
	{
		return _x;
	}

	float& Vector3D::getY()
	{
		return _y;
	}

	float& Vector3D::getZ()
	{
		return _z;
	}
}
