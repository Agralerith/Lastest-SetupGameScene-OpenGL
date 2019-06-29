#ifndef CAMERA_H
#define CAMERA_H

#include "Vector.h"
#include "Matrix.h"

class Camera
{
private:
	// cursor
	static float	previousCursorPosX;
	static float	previousCursorPosY;
	static Matrix4	m_ViewMatrix;
	static bool		firstMouse;

public:
	Camera();

	static void			UpdateViewMatrix(const Vector3& cameraPos, const Vector3& targetPos, const Vector3& upVector);
	static float		getPreviousCursorPosX();
	static float		getPreviousCursorPoxY();
	static void			setPreviousCursorPosX(float value);
	static void			setPreviousCursorPosY(float value);
	Matrix4				getViewMatrix();

	static void			cursor_callback(double xpos, double ypos, Vector3& cameraFront);

	static float pitch;
	static float yaw;
};

#endif