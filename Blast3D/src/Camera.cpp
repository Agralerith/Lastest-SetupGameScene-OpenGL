#include "Camera.h"
#include "GLEssential.h"
#include "Setting.h"
#include <iostream>

float Camera::pitch	= 0.0f;
float Camera::yaw	= 0.0f;
float Camera::previousCursorPosX = 0.0f;
float Camera::previousCursorPosY = 0.0f;
bool  Camera::firstMouse	= true;
Matrix4 Camera::m_ViewMatrix;

Camera::Camera()
{}


/* Return the view matrix to be multiplied by the scene */
void Camera::UpdateViewMatrix(const Vector3& cameraPos, const Vector3& targetPos, const Vector3& upVector)
{
	Vector3 up = upVector;
	Vector3 forward = (targetPos - cameraPos).normalized(); // vector from target to camera
	Vector3 right = forward.cross(up).normalized();
	up = right.cross(forward);


	Matrix4 translation;
	translation.identity();
	translation.setColumn(3, -cameraPos);

	Vector3 lastColumn(-right.dot(cameraPos), -up.dot(cameraPos), forward.dot(cameraPos));

	Matrix4 rotation;
	rotation.identity();
	rotation.setColumn(0, right);
	rotation.setColumn(1, up);
	rotation.setColumn(2, -forward);
	rotation.transpose();
	rotation.setColumn(3, lastColumn);

	m_ViewMatrix = rotation;
}

void Camera::cursor_callback(double xpos, double ypos, Vector3& cameraFront)
{
	float fPosX = static_cast<float>(xpos);
	float fPosY = static_cast<float>(ypos);

	if (firstMouse)
	{
		setPreviousCursorPosX(fPosX);
		setPreviousCursorPosX(fPosY);
		firstMouse = false;
	}
	float currentCursorPosX = fPosX - getPreviousCursorPosX();	// positive : move to right
	float currentCursorPosY = getPreviousCursorPoxY() - fPosY;	// positive : move to top

	float mouseSensitivity = 0.10f;
	currentCursorPosX *= mouseSensitivity;
	currentCursorPosY *= mouseSensitivity;

	Camera::pitch = currentCursorPosY;	// up and down
	Camera::yaw   = currentCursorPosX;	// left and right

	 // Restrict up and down movement
	 if (Camera::pitch > 89.0)
	 	Camera::pitch = 89.0;
	 if (Camera::pitch < -89.0)
	 	Camera::pitch = -89.0;

	Vector3 front;
	front.x = cosf(Camera::pitch * DEGtoRAD) * cosf(Camera::yaw * DEGtoRAD);
	front.y = sinf(Camera::pitch * DEGtoRAD);
	front.z = cosf(Camera::pitch * DEGtoRAD) * sinf(Camera::yaw * DEGtoRAD);
	cameraFront = front.normalized();
}


float Camera::getPreviousCursorPosX()
{
	return previousCursorPosX;
}

float Camera::getPreviousCursorPoxY()
{
	return previousCursorPosY;
}

void Camera::setPreviousCursorPosX(float value)
{
	previousCursorPosX = value;
}

void Camera::setPreviousCursorPosY(float value)
{
	previousCursorPosY = value;
}

Matrix4 Camera::getViewMatrix()
{
	return m_ViewMatrix;
}
