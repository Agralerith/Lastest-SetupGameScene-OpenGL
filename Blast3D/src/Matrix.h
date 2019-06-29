#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"
#include <iostream>

class Matrix4
{
public:
	// constructor
	Matrix4();
	Matrix4(const float arr[]);
	Matrix4(float m00, float m01, float m02, float m03,
			float m04, float m05, float m06, float m07,
			float m08, float m09, float m10, float m11,
			float m12, float m13, float m14, float m15);

	// setter
	void					set(const float arr[]);
	void					set(float m00, float m01, float m02, float m03,
								float m04, float m05, float m06, float m07,
								float m08, float m09, float m10, float m11,
								float m12, float m13, float m14, float m15);
	void					setColumn(int index, const Vector3& vec);
	void					setColumn(int index, const float arr[]);

	// getter
	const float*			get() const;
	const float*			getTranspose();
	float					getDeterminant() const;
	float					getCofactor(float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8, float m9) const;

	Matrix4&				identity();
	Matrix4&				transpose();
	Matrix4&				inverse();
	Matrix4&				perspective(float fovy, float aspect, float zNear, float zFar);

	// transformation
	Matrix4&				translate(float x, float y, float z);
	Matrix4&				translate(const Vector3& vec);
	Matrix4&				rotate(float angle, const Vector3& axis);
	Matrix4&				rotate(float angle, float x, float y, float z);
	Matrix4&				rotateX(float angle);
	Matrix4&				rotateY(float angle);
	Matrix4&				rotateZ(float angle);
	Matrix4&				scale(float k);
	Matrix4&				scale(float x, float y, float z);
	Matrix4&				lookAt(float x, float y, float z);

	// operators
	Matrix4					operator+(const Matrix4& rhs)const;
	Matrix4					operator-(const Matrix4& rhs)const;
	Matrix4					operator*(const Matrix4& n)const;
	Vector3					operator*(const Vector3& v)const;
	Matrix4&				operator+=(const Matrix4& rhs);
	Matrix4&				operator-=(const Matrix4& rhs);
	Matrix4&				operator*=(const Matrix4& n);

	float					operator[](int index) const;
	float&					operator[](int index);

	friend Matrix4			operator-(const Matrix4& mat);
	friend std::ostream&	operator<<(std::ostream& os, const Matrix4& mat);


private:
	float m[16];	// matrices
	float tm[16];
};

#endif