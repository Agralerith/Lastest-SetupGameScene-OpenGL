#include <iostream>

#ifndef VECTOR_H
#define VECTOR_H

class Vector3
{
public:
	float x, y, z;

	Vector3();
	Vector3(float x, float y);
	Vector3(float x, float y, float z);
	Vector3(const Vector3& vec);

	float length() const;				// get magnitude of the vector
	Vector3& normalized();				// get normalized of the vector
	float dot(const Vector3& rhs);
	Vector3 cross(const Vector3& rhs);

	Vector3 operator+(const Vector3& rhs) const;
	Vector3 operator-(const Vector3& rhs) const;
	Vector3 operator*(const Vector3& rhs) const;
	Vector3 operator*(float k) const;
	Vector3 operator/(const Vector3& rhs) const;
	Vector3 operator/(float k) const;
	
	void operator+=(const Vector3& rhs);
	void operator-=(const Vector3& rhs);
	void operator*=(const Vector3& rhs);
	void operator/=(const Vector3& rhs);
	void operator*=(float k);
	void operator/=(float k);

	float operator[](int index) const;
	float& operator[](int index);

	friend Vector3 operator-(const Vector3& rhs);
	friend Vector3 operator*(const float k, const Vector3& vec);
};

std::ostream& operator<<(std::ostream& out, const Vector3& rhs);

#endif