#include "Matrix.h"
#include <iomanip>

Matrix4::Matrix4()
{
	identity();
}

Matrix4::Matrix4(const float arr[])
	:m { arr[0], arr[1], arr[2], arr[3], 
		 arr[4], arr[5], arr[6], arr[7], 
		 arr[8], arr[9], arr[10], arr[11], 
		 arr[12], arr[13], arr[14], arr[15] }
{}

Matrix4::Matrix4(float m00, float m01, float m02, float m03, float m04, float m05, float m06, float m07, float m08, float m09, float m10, float m11, float m12, float m13, float m14, float m15)
	:m { m00, m01, m02, m03, m04, m05, m06, m07, m08, m09, m10, m11, m12, m13, m14, m15 }
{}

void Matrix4::set(const float arr[])
{
	m[0] = arr[0];		m[1] = arr[1];		m[2] = arr[2];		m[3] = arr[3];
	m[4] = arr[4];		m[5] = arr[5];		m[6] = arr[6];		m[7] = arr[7];
	m[8] = arr[8];		m[9] = arr[9];		m[10] = arr[10];	m[11] = arr[11];
	m[12] = arr[12];	m[13] = arr[13];	m[14] = arr[14];	m[15] = arr[15];
}

void Matrix4::set(float m00, float m01, float m02, float m03, float m04, float m05, float m06, float m07, float m08, float m09, float m10, float m11, float m12, float m13, float m14, float m15)
{
	m[0] = m00;			m[1] = m01;		 m[2] = m02;		 m[3] = m03;
	m[4] = m04;			m[5] = m05;		 m[6] = m06;		 m[7] = m07;
	m[8] = m08;			m[9] = m09;		 m[10] = m10;		 m[11] = m11;
	m[12] = m12;		m[13] = m13;	 m[14] = m14;		 m[15] = m15;
}

void Matrix4::setColumn(int index, const Vector3 & vec)
{
	m[index * 4] = vec.x;		m[index * 4 + 1] = vec.y;		m[index * 4 + 2] = vec.z;
}

void Matrix4::setColumn(int index, const float arr[])
{
	m[index * 4] = arr[0];		m[index * 4 + 1] = arr[1];		m[index * 4 + 2] = arr[2];
}

/* Return the first matrix array */
const float * Matrix4::get() const
{
	return m;
}

/* Calculate and return transpose of current matrix */
const float * Matrix4::getTranspose()
{
	for (int i = 0; i < 16; i++)
	{
		tm[i] = m[i];
	}

	std::swap(tm[1], tm[4]);
	std::swap(tm[2], tm[8]);
	std::swap(tm[3], tm[12]);
	std::swap(tm[6], tm[9]);
	std::swap(tm[7], tm[13]);
	std::swap(tm[11], tm[14]);

	return tm;
}

/* Calculate and return determinant of current matrix */
float Matrix4::getDeterminant() const
{
	return (m[0]*getCofactor(m[5], m[6], m[7],		m[9], m[10], m[11],		m[13], m[14], m[15]) - 
			m[1]*getCofactor(m[4], m[6], m[7],		m[8], m[10], m[11],		m[12], m[14], m[15]) +
			m[2]*getCofactor(m[4], m[5], m[7],		m[8], m[9], m[11],		m[12], m[13], m[15]) -
			m[3]*getCofactor(m[4], m[5], m[6],		m[8], m[9], m[10],		m[12], m[13], m[14]));
}

/*
	Calculate and return matrix 3x3 cofactor value
*/
float Matrix4::getCofactor(float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8, float m9) const
{
	return (m1*(m5*m9 - m6*m8) - m2*(m4*m9 - m6*m7) + m3*(m4*m8 - m5*m7));
}

/* Reset current matrix to identity matrix */
Matrix4 & Matrix4::identity()
{
	m[0]  = m[5]  = m[10] = m[15] = 1.0f;
	m[1]  = m[2]  = m[3]  = m[4]  = 0.0f;
	m[6]  = m[7]  = m[8]  = m[9]  = 0.0f;
	m[11] = m[12] = m[13] = m[14] = 0.0f;

	return (*this);
}

/* Set the current matrix to calculated transposed matrix */
Matrix4 & Matrix4::transpose()
{
	std::swap(m[1], m[4]);
	std::swap(m[2], m[8]);
	std::swap(m[3], m[12]);
	std::swap(m[6], m[9]);
	std::swap(m[7], m[13]);
	std::swap(m[11], m[14]);

	return (*this);
}

/* Set the current matrix to calculated inversed matrix */
Matrix4 & Matrix4::inverse()
{
	float scalar = 1.0 / getDeterminant();
	(*this).transpose();
	
	m[0] = getCofactor(m[5], m[6], m[7], m[9], m[10], m[11], m[13], m[14], m[15]);
	m[1] = getCofactor(m[4], m[6], m[7], m[8], m[10], m[11], m[12], m[14], m[15]);
	m[2] = getCofactor(m[4], m[5], m[7], m[8], m[9], m[11], m[12], m[13], m[15]);
	m[3] = getCofactor(m[4], m[5], m[6], m[8], m[9], m[10], m[12], m[13], m[14]);
	m[4] = getCofactor(m[1], m[2], m[3], m[9], m[10], m[11], m[13], m[14], m[15]);
	m[5] = getCofactor(m[0], m[2], m[3], m[8], m[10], m[11], m[12], m[14], m[15]);
	m[6] = getCofactor(m[0], m[1], m[3], m[8], m[9], m[11], m[12], m[13], m[15]);
	m[7] = getCofactor(m[0], m[1], m[2], m[8], m[9], m[10], m[12], m[13], m[14]);
	m[8] = getCofactor(m[1], m[2], m[3], m[5], m[6], m[7], m[13], m[14], m[15]);
	m[9] = getCofactor(m[0], m[2], m[3], m[4], m[6], m[7], m[12], m[14], m[15]);
	m[10] = getCofactor(m[0], m[1], m[3], m[4], m[5], m[7], m[12], m[13], m[15]);
	m[11] = getCofactor(m[0], m[1], m[2], m[4], m[5], m[6], m[12], m[13], m[14]);
	m[12] = getCofactor(m[1], m[2], m[3], m[5], m[6], m[7], m[9], m[10], m[11]);
	m[13] = getCofactor(m[0], m[2], m[3], m[4], m[6], m[7], m[8], m[10], m[11]);
	m[14] = getCofactor(m[0], m[1], m[3], m[4], m[5], m[7], m[8], m[9], m[11]);
	m[15] = getCofactor(m[0], m[1], m[2], m[4], m[5], m[6], m[8], m[9], m[10]);

	return (*this);
}

/* fovy is expected to be radian */
Matrix4& Matrix4::perspective(float fovy, float aspect, float zNear, float zFar)
{
	const float tanHalfFovy = tanf(fovy / 2.0);

	m[0]  = 1.0 / (aspect * tanHalfFovy);
	m[5]  = 1.0 / tanHalfFovy;
	m[10] = - ( zFar + zNear) / (zFar - zNear);
	m[11] = - 1.0f;
	m[14] = -( 2 * zFar * zNear) / (zFar - zNear);

	return (*this);
}

Matrix4 & Matrix4::translate(float x, float y, float z)
{
	m[12] += m[0]*x + m[4]*y + m[8]*z;
	m[13] += m[1]*x + m[5]*y + m[9]*z;
	m[14] += m[2]*x + m[6]*y + m[10]*z;
	m[15] += m[3]*x + m[7]*y + m[11]*z;

	return (*this);
}

Matrix4 & Matrix4::translate(const Vector3 & vec)
{
	m[12] += m[0]*vec.x + m[4]*vec.y + m[8]* vec.z;
	m[13] += m[1]*vec.x + m[5]*vec.y + m[9]* vec.z;
	m[14] += m[2]*vec.x + m[6]*vec.y + m[10]*vec.z;
	m[15] += m[3]*vec.x + m[7]*vec.y + m[11]*vec.z;

	return (*this);
}

Matrix4 & Matrix4::rotate(float angle, const Vector3 & axis)
{
	return (*this);
}

Matrix4 & Matrix4::rotate(float angle, float x, float y, float z)
{
	return (*this);
}

/*
				[1			0			0			]
R(angle)	=	[0			cos(angle)	-sin(angle)	]
				[0			sin(angle)	 cos(angle)	]
*/
Matrix4 & Matrix4::rotateX(float angle)
{
	return (*this);
}

Matrix4 & Matrix4::rotateY(float angle)
{
	return (*this);
}

Matrix4 & Matrix4::rotateZ(float angle)
{
	return (*this);
}

Matrix4 & Matrix4::scale(float k)
{
	m[0] *= k;	m[4] *= k;	m[8] *=  k;
	m[1] *= k;	m[5] *= k;	m[9] *=  k;
	m[2] *= k;	m[6] *= k;	m[10] *= k;
	m[3] *= k;	m[7] *= k;	m[11] *= k;

	return (*this);
}

Matrix4 & Matrix4::scale(float x, float y, float z)
{
	m[0] *= x;	m[4] *= y;	m[8] *= z;
	m[1] *= x;	m[5] *= y;	m[9] *= z;
	m[2] *= x;	m[6] *= y;	m[10] *= z;
	m[3] *= x;	m[7] *= y;	m[11] *= z;

	return (*this);
}

Matrix4 & Matrix4::lookAt(float x, float y, float z)
{
	return (*this);
}

Matrix4 Matrix4::operator+(const Matrix4 & rhs) const
{
	return Matrix4(m[0] + rhs[0],		m[1] + rhs[1],		m[2] + rhs[2],		m[3] + rhs[3],
				   m[4] + rhs[4],		m[5] + rhs[5],		m[6] + rhs[6],		m[7] + rhs[7],
				   m[8] + rhs[8],		m[9] + rhs[9],		m[10] + rhs[10],	m[11] + rhs[11],
				   m[12] + rhs[12],		m[13] + rhs[13],	m[14] + rhs[14],	m[15] + rhs[15]);
}

Matrix4 Matrix4::operator-(const Matrix4 & rhs) const
{
	return Matrix4(m[0] - rhs[0],		m[1] - rhs[1],		m[2] - rhs[2],		m[3] - rhs[3],
				   m[4] - rhs[4],		m[5] - rhs[5],		m[6] - rhs[6],		m[7] - rhs[7],
				   m[8] - rhs[8],		m[9] - rhs[9],		m[10] - rhs[10],	m[11] - rhs[11],
				   m[12] - rhs[12],		m[13] - rhs[13],	m[14] - rhs[14],	m[15] - rhs[15]);
}

Matrix4 Matrix4::operator*(const Matrix4 & n) const
{
	return Matrix4(m[0]*n[0] + m[4]*n[1] + m[8]* n[2] + m[12]*n[3],
				   m[1]*n[0] + m[5]*n[1] + m[9]* n[2] + m[13]*n[3],
				   m[2]*n[0] + m[6]*n[1] + m[10]*n[2] + m[14]*n[3],
				   m[3]*n[0] + m[7]*n[1] + m[11]*n[2] + m[15]*n[3],

				   m[0]*n[4] + m[4]*n[5] + m[8]* n[6] + m[12]*n[7],
				   m[1]*n[4] + m[5]*n[5] + m[9]* n[6] + m[13]*n[7],
				   m[2]*n[4] + m[6]*n[5] + m[10]*n[6] + m[14]*n[7],
				   m[3]*n[4] + m[7]*n[5] + m[11]*n[6] + m[15]*n[7],
		
				   m[0]*n[8] + m[4]*n[9] + m[8]* n[10] + m[12]*n[11],
				   m[1]*n[8] + m[5]*n[9] + m[9]* n[10] + m[13]*n[11],
				   m[2]*n[8] + m[6]*n[9] + m[10]*n[10] + m[14]*n[11],
				   m[3]*n[8] + m[7]*n[9] + m[11]*n[10] + m[15]*n[11],
		
				   m[0]*n[12] + m[4]*n[13] + m[8]* n[14] + m[12]*n[15],
				   m[1]*n[12] + m[5]*n[13] + m[9]* n[14] + m[13]*n[15],
				   m[2]*n[12] + m[6]*n[13] + m[10]*n[14] + m[14]*n[15],
				   m[3]*n[12] + m[7]*n[13] + m[11]*n[14] + m[15]*n[15]);
}


/*

[m00 m04 m08 m12]		[v0]		[m0*v0 + m4*v1 + m8* v2 + m12]
[m01 m05 m09 m13]	*	[v1]	=	[m1*v0 + m5*v1 + m9* v2 + m13]
[m02 m06 m10 m14]		[v2]		[m2*v0 + m6*v1 + m10*v2 + m14]
[  0   0   0   1]		[ 1]		[				1			 ]

*/
Vector3 Matrix4::operator*(const Vector3 & v) const
{
	return Vector3(m[0]*v[0] + m[4]*v[1] + m[8]* v[2] + m[12],
				   m[1]*v[0] + m[5]*v[1] + m[9]* v[2] + m[13],
				   m[2]*v[0] + m[6]*v[1] + m[10]*v[2] + m[14]);
}

Matrix4 & Matrix4::operator+=(const Matrix4 & rhs)
{
	m[0] += rhs[0];		m[4] += rhs[4];		m[8] += rhs[8];		m[12] += rhs[12];
	m[1] += rhs[1];		m[5] += rhs[5];		m[9] += rhs[9];		m[13] += rhs[13];
	m[2] += rhs[2];		m[6] += rhs[6];		m[10] += rhs[10];	m[14] += rhs[14];
	m[3] += rhs[3];		m[7] += rhs[7];		m[11] += rhs[11];	m[15] += rhs[15];

	return (*this);
}

Matrix4 & Matrix4::operator-=(const Matrix4 & rhs)
{
	m[0] -= rhs[0];		m[4] -= rhs[4];		m[8] -= rhs[8];		m[12] -= rhs[12];
	m[1] -= rhs[1];		m[5] -= rhs[5];		m[9] -= rhs[9];		m[13] -= rhs[13];
	m[2] -= rhs[2];		m[6] -= rhs[6];		m[10] -= rhs[10];	m[14] -= rhs[14];
	m[3] -= rhs[3];		m[7] -= rhs[7];		m[11] -= rhs[11];	m[15] -= rhs[15];

	return (*this);
}

Matrix4 & Matrix4::operator*=(const Matrix4 & n)
{
	m[0]  = m[0]*n[0]  + m[4]*n[1]  + m[8]* n[2]  + m[12]*n[3];
	m[1]  = m[1]*n[0]  + m[5]*n[1]  + m[9]* n[2]  + m[13]*n[3];
	m[2]  = m[2]*n[0]  + m[6]*n[1]  + m[10]*n[2]  + m[14]*n[3];
	m[3]  = m[3]*n[0]  + m[7]*n[1]  + m[11]*n[2]  + m[15]*n[3];
	m[4]  = m[0]*n[4]  + m[4]*n[5]  + m[8]* n[6]  + m[12]*n[7];
	m[5]  = m[1]*n[4]  + m[5]*n[5]  + m[9]* n[6]  + m[13]*n[7];
	m[6]  = m[2]*n[4]  + m[6]*n[5]  + m[10]*n[6]  + m[14]*n[7];
	m[7]  = m[3]*n[4]  + m[7]*n[5]  + m[11]*n[6]  + m[15]*n[7];
	m[8]  = m[0]*n[8]  + m[4]*n[9]  + m[8]* n[10] + m[12]*n[11];
	m[9]  = m[1]*n[8]  + m[5]*n[9]  + m[9]* n[10] + m[13]*n[11];
	m[10] = m[2]*n[8]  + m[6]*n[9]  + m[10]*n[10] + m[14]*n[11];
	m[11] = m[3]*n[8]  + m[7]*n[9]  + m[11]*n[10] + m[15]*n[11];
	m[12] = m[0]*n[12] + m[4]*n[13] + m[8]* n[14] + m[12]*n[15];
	m[13] = m[1]*n[12] + m[5]*n[13] + m[9]* n[14] + m[13]*n[15];
	m[14] = m[2]*n[12] + m[6]*n[13] + m[10]*n[14] + m[14]*n[15];
	m[15] = m[3]*n[12] + m[7]*n[13] + m[11]*n[14] + m[15]*n[15];
	
	return (*this);
}

float Matrix4::operator[](int index) const
{
	return m[index];
}

float& Matrix4::operator[](int index)
{
	return m[index];
}

Matrix4 operator-(const Matrix4 & mat)
{
	return Matrix4(-mat[0], -mat[4], -mat[8],  -mat[12],
				   -mat[1], -mat[5], -mat[9],  -mat[13], 
				   -mat[2], -mat[6], -mat[10], -mat[14], 
				   -mat[3], -mat[7], -mat[11], -mat[15]);
}

std::ostream & operator<<(std::ostream & os, const Matrix4 & mat)
{
	os << "[" << std::left << std::setw(12) << mat[0] << std::right << std::setw(12) << mat[4] << std::setw(12) << mat[8] << std::setw(12) << mat[12] << std::setw(12) << "]" << std::endl

		<< "[" << std::left << std::setw(12) << mat[1] << std::right << std::setw(12) << mat[5] << std::setw(12) << mat[9] << std::setw(12) << mat[13] << std::setw(12) << "]" << std::endl

		<< "[" << std::left << std::setw(12) << mat[2] << std::right << std::setw(12) << mat[6] << std::setw(12) << mat[10] << std::setw(12) << mat[14] << std::setw(12) << "]" << std::endl

		<< "[" << std::left << std::setw(12) << mat[3] << std::right << std::setw(12) << mat[7] << std::setw(12) << mat[11] << std::setw(12) << mat[15] << std::setw(12) << "]" << std::endl;

	return os;
}
