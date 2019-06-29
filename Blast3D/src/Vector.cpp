#include "Vector.h"
#include "GLEssential.h"
#include <math.h>


// Constructor
Vector3::Vector3()
	:x(0), y(0), z(0) {}

Vector3::Vector3(float x, float y)
	:x(x), y(y), z(0) {}

Vector3::Vector3(float x, float y, float z)
	:x(x), y(y), z(z) {}

Vector3::Vector3(const Vector3 & vec)
	:x(vec.x), y(vec.y), z(vec.z) {}


float Vector3::length() const
{
	return sqrtf(x*x + y * y + z * z);
}

Vector3& Vector3::normalized()
{
	float magnitude = (*this).length();
	
	(*this).x /= magnitude;
	(*this).y /= magnitude;
	(*this).z /= magnitude;

	return (*this);
}

float Vector3::dot(const Vector3 & rhs)
{
	return (x * rhs.x + y * rhs.y + z * rhs.z);
}

Vector3 Vector3::cross(const Vector3 & rhs)
{
	return Vector3(y * rhs.z - z * rhs.y,
				   z * rhs.x - x * rhs.z,
				   x * rhs.y - y * rhs.x);
}

Vector3 Vector3::operator+(const Vector3 & rhs) const
{
	return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
}

Vector3 Vector3::operator-(const Vector3 & rhs) const
{
	return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
}

Vector3 Vector3::operator*(const Vector3 & rhs) const
{
	return Vector3(x * rhs.x, y * rhs.y, z * rhs.z);
}

Vector3 Vector3::operator/(const Vector3 & rhs) const
{
	return Vector3(x / rhs.x, y / rhs.y, z / rhs.z);
}

Vector3 Vector3::operator*(float k) const
{
	return Vector3(x * k, y * k, z * k);
}

Vector3 Vector3::operator/(float k) const
{
	return Vector3(x / k, y / k, z / k);
}

void Vector3::operator+=(const Vector3 & rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
}

void Vector3::operator-=(const Vector3 & rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
}

void Vector3::operator*=(const Vector3 & rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;
}

void Vector3::operator/=(const Vector3 & rhs)
{
	x /= rhs.x;
	y /= rhs.y;
	z /= rhs.z;
}

void Vector3::operator*=(float k)
{
	x *= k;
	y *= k;
	z *= k;
}

void Vector3::operator/=(float k)
{
	x /= k;
	y /= k;
	z /= k;
}

float Vector3::operator[](int index) const
{
	switch (index)
	{
		case 0: return x; break;
		case 1: return y; break;
		case 2: return z; break;
		default: std::cout << "[Vector3] : Invalid index " << index << std::endl; break;
	}

	ASSERT(false);
	return 0;
}

float & Vector3::operator[](int index)
{
	switch (index)
	{
		case 0: return x; break;
		case 1: return y; break;
		case 2: return z; break;
		default: std::cout << "[Vector3] : Invalid index " << index << std::endl; break;
	}

	ASSERT(false);
	return z;		// Note : This statement should not be executed at any time.
}

Vector3 operator-(const Vector3 & rhs)
{
	return Vector3(-rhs.x, -rhs.y, -rhs.z);
}

Vector3 operator*(const float k, const Vector3 & vec)
{
	return Vector3(vec.x * k, vec.y * k, vec.z * k);
}

std::ostream& operator<<(std::ostream& out, const Vector3& rhs)
{
	out << "(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ")";
	return out;
}
