#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <Windows.h>

#include "GLEssential.h"
#include "Setting.h"
#include "Vector.h"
#include "Matrix.h"
#include "Camera.h"
#include "Shader.h"

Vector3 cameraPos	(0.0f, 3.0f, 3.0f);
Vector3 cameraFront	(0.0f, 0.0f, -1.0f);
Vector3 cameraUp	(0.0f, 1.0f, 0.0f);


void initGL()
{
	// for safety purpose
	ASSERT(sizeof(GLuint) == sizeof(unsigned int))
	ASSERT(sizeof(GLenum) == sizeof(unsigned int))
	ASSERT(sizeof(GLint) == sizeof(int))
	ASSERT(sizeof(GLsizei) == sizeof(int))

	unsigned int err = glewInit();

	if (err != GLEW_OK)
	{
		std::cout << "[GLEW] : " << glewGetErrorString(err) << std::endl;
	}
	std::cout << "GL Version : " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GL Vendor  : " << glGetString(GL_VENDOR) << std::endl;

	glEnable(GL_DEPTH_TEST);
}

void processInput(GLFWwindow *window)
{
	float deltaTime = TimeManager::getDeltaTime();

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += deltaTime * cameraFront;

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= deltaTime * cameraFront;

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= deltaTime * cameraUp.cross(-cameraFront).normalized();

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += deltaTime * cameraUp.cross(-cameraFront).normalized();
}

void OnCursorMovement(GLFWwindow* window, double xpos, double ypos)
{
	Camera::cursor_callback(xpos, ypos, cameraFront);
}

void ChangeColor(Color color)
{
	switch (color)
	{
	case RED:			glColor3f(0.5f, 0.0f, 0.0f);	break;
	case ORANGE:		glColor3f(1.0f, 0.5f, 0.0f);	break;
	case YELLOW:		glColor3f(1.0f, 1.0f, 0.0f);	break;
	case LIGHTRED:		glColor3f(1.0f, 0.0f, 0.0f);	break;
	case DARKRED:		glColor3f(0.3f, 0.0f, 0.0f);	break;
	case GREEN:			glColor3f(0.0f, 5.0f, 0.0f);	break;
	case LIGHTGREEN:	glColor3f(0.0f, 1.0f, 0.0f);	break;
	case DARKGREEN:		glColor3f(0.0f, 0.3f, 0.0f);	break;
	case AQUA:			glColor3f(0.0f, 1.0f, 1.0f);	break;
	case BLUE:			glColor3f(0.0f, 0.0f, 5.0f);	break;
	case PURPLE:		glColor3f(1.0f, 0.0f, 1.0f);	break;
	case LIGHTBLUE:		glColor3f(0.0f, 0.0f, 1.0f);	break;
	case DARKBLUE:		glColor3f(0.0f, 0.0f, 0.3f);	break;
	case WHITE:			glColor3f(1.0f, 1.0f, 1.0f);	break;
	case LIGHTGREY:		glColor3f(0.6f, 0.6f, 0.6f);	break;
	case BLACK:			glColor3f(0.0f, 0.0f, 0.0f);	break;
	case DARKGREY:		glColor3f(0.3f, 0.3f, 0.3f);	break;

	default:			ASSERT(false);					break;
	}
}

void DrawCube(float x, float y, float z)
{
	x *= 0.3f;	y *= 0.3f;	z *= 0.3f;

	glBegin(GL_QUADS);
		// front
		ChangeColor(DARKRED);
		glVertex3f(0.0f + x, 0.0f + y, 0.0f + z);
		ChangeColor(LIGHTRED);
		glVertex3f(0.3f + x, 0.0f + y, 0.0f + z);
		glVertex3f(0.3f + x, 0.3f + y, 0.0f + z);
		ChangeColor(DARKRED);
		glVertex3f(0.0f + x, 0.3f + y, 0.0f + z);

		// back
		ChangeColor(DARKRED);
		glVertex3f(0.0f + x, 0.0f + y, 0.3f + z);
		ChangeColor(LIGHTRED);
		glVertex3f(0.3f + x, 0.0f + y, 0.3f + z);
		glVertex3f(0.3f + x, 0.3f + y, 0.3f + z);
		ChangeColor(DARKRED);
		glVertex3f(0.0f + x, 0.3f + y, 0.3f + z);

		// bottom
		ChangeColor(BLACK);
		glVertex3f(0.0f + x, 0.0f + y, 0.0f + z);
		ChangeColor(LIGHTGREY);
		glVertex3f(0.0f + x, 0.0f + y, 0.3f + z);
		glVertex3f(0.3f + x, 0.0f + y, 0.3f + z);
		ChangeColor(BLACK);
		glVertex3f(0.3f + x, 0.0f + y, 0.0f + z);

		// up
		ChangeColor(BLACK);
		glVertex3f(0.0f + x, 0.3f + y, 0.0f + z);
		glVertex3f(0.3f + x, 0.3f + y, 0.0f + z);
		ChangeColor(LIGHTGREY);
		glVertex3f(0.3f + x, 0.3f + y, 0.3f + z);
		glVertex3f(0.0f + x, 0.3f + y, 0.3f + z);

		// left
		ChangeColor(DARKBLUE);
		glVertex3f(0.0f + x, 0.0f + y, 0.0f + z);
		glVertex3f(0.0f + x, 0.3f + y, 0.0f + z);
		ChangeColor(LIGHTBLUE);
		glVertex3f(0.0f + x, 0.3f + y, 0.3f + z);
		glVertex3f(0.0f + x, 0.0f + y, 0.3f + z);

		// right
		ChangeColor(DARKGREEN);
		glVertex3f(0.3f + x, 0.3f + y, 0.0f + z);
		glVertex3f(0.3f + x, 0.0f + y, 0.0f + z);
		ChangeColor(LIGHTGREEN);
		glVertex3f(0.3f + x, 0.0f + y, 0.3f + z);
		glVertex3f(0.3f + x, 0.3f + y, 0.3f + z);

	glEnd();
}

/* Description	:  Draw bottom left side of scene
 * Author		:  Created by Wei Yon
 * Restriction	:  None
 * Usage		:  Called before swapping buffers
 */
void chDrawTopLeftScene()
{
	float deltaTime = TimeManager::getDeltaTime();

	//draw x=-1.0f to -13.0f && z=-3.0f
	for (float x = -1.0f; x > -14.0f; x--)
		DrawCube(x, 0.0f, -3.0f);

	//draw x=-10.0f && z=-0.0f to -12.0f
	for (float z = 0.0f; z > -13.0f; z--)
		DrawCube(-10.0f, 0.0f, z);
	
	//draw x=-16.0f && z=0.0f to -15.0f
	for (float z = 0.0f; z > -16.0f; z--)
		DrawCube(-16.0f, 0.0f, z);

	//draw x=-4.0f to -15.0f && z=-15.0f
	for (float x = -4.0f; x > -16.0f; x--)
		DrawCube(x, 0.0f, -15.0f);

	//draw x=-13.0f && z=-14.0f to -12.0f
	for (float z = -12.0f; z >= -14.0f; z--)
		DrawCube(-13.0f, 0.0f, z);

	//draw x=-13.0f && z=-6.0f to -9.0f
	for (float z = -7.0f; z >= -9.0f; z--)
		DrawCube(-13.0f, 0.0f, z);

	//draw x=-11.0f to -13.0f && z=-9.0f
	for (float x = -11.0f; x >= -13.0f; x--)
		DrawCube(x, 0.0f, -9.0f);

	//draw x=-10.0f to -8.0f && z=-12.0f
	for (float x = -8.0f; x >= -10.0f; x--)
		DrawCube(x, 0.0f, -12.0f);

	//draw x=-4.0f && z=-4.0f to -9.0f
	for (float z = -4.0f; z >= -9.0f; z--)
		DrawCube(-4.0f, 0.0f, z);

	//draw x=1.0f to -7.0f && z=-9.0f
	for (float x = -1.0f; x >= -7.0f; x--)
		DrawCube(x, 0.0f, -9.0f);

	//draw x=-7.0f && z=-6.0f to -9.0f
	for (float z = -6.0f; z >= -9.0f; z--)
		DrawCube(-7.0f, 0.0f, z);

	//draw x=-4.0f && z=-12.0f to -15.0f
	for (float z = -12.0f; z >= -15.0f; z--)
		DrawCube(-4.0f, 0.0f, z);

	//draw x=-1.0f && z=-9.0f to -12.0f
	for (float z = -9.0f; z >= -12.0f; z--)
		DrawCube(-1.0f, 0.0f, z);

	//draw x=-1.0f && z=-6.0f
	DrawCube(-1.0f, 0.0f, -6.0f);
}

void chDrawTopRightScene()
{
	float deltaTime = TimeManager::getDeltaTime();

	//draw x=0.0 to 16.0f && z=-9.0f
	for (float x = 0.0f; x <= 16.0f; x++)
		DrawCube(x, 0.0f, -9.0f);

	//draw x=-1.0f to x=16.0f && z=-15.0f
	for (float x = -1.0f; x <= 16.0f; x++)
		DrawCube(x, 0.0f, -15.0f);

	//draw x=3.0f && z=-12.0f to -14.0f
	for (float z = -12.0f; z >= -14.0f; z--)
		DrawCube(3.0f, 0.0f, z);

	//draw x=6.0f && z=-9.0f to -12.0f
	for (float z = -9.0f; z >= -12.0f; z--)
		DrawCube(6.0f, 0.0f, z);

	//draw x=6.0f to 10.0f && z=-12.0f
	for (float x = 6.0f; x <= 10.0f; x++)
		DrawCube(x, 0.0f, -12.0f);

	//draw x=10.0f && z=-6.0f to -9.0f
	for (float z = -6.0f; z >= -9.0; z--)
		DrawCube(10.0f, 0.0f, z);

	//draw x=0.0f to 5.0f && z=-6.0f
	for (float x = 0.0f; x <= 5.0f; x++)
		DrawCube(x, 0.0f, -6.0f);

	//draw x=2.0f && z=-1.0f to -6.0f
	for (float z = -1.0f; z >= -6.0f; z--)
		DrawCube(2.0f, 0.0f, z);

	//draw x=5.0f && z=-1.0f to -3.0f
	for (float z = -1.0f; z >= -3.0f; z--)
		DrawCube(5.0f, 0.0f, z);

	//draw x=5.0f to 15.0f && z=-3.0f
	for (float x = 5.0f; x <= 15.0f; x++)
		DrawCube(x, 0.0f, -3.0f);

	//draw x-13.0f && z=-3.0f to -6.0f
	for (float z = -3.0f; z >= -6.0f; z--)
		DrawCube(13.0f, 0.0f, z);
	
	//draw x=16.0f && z=-1.0f to -15.0f
	for (float z = -1.0f; z >= -15.0f; z--)
		DrawCube(16.0f, 0.0f, z);
}


void wyDrawBottomLeftScene()
{
	float deltaTime = TimeManager::getDeltaTime();

	//draw z=16.0f
	for (float x = -1.0f; x >= -16.0f; x--)
		DrawCube(x, 0.0f, 16.0f);

	//draw x=-16.0f
	for (float z = 0.0f; z <= 16.0f; z++)
		DrawCube(-16.0f, 0.0f, z);

	//draw x=-13.0f to -16.0f && z=10.0f
	for (float x = -13.0f; x >= -16.0f; x--)
		DrawCube(x, 0.0f, 10.0f);

	//draw x=-13.0f && z=10.0f to 13.0f
	for (float z = 10.0f; z <= 13.0f; z++)
		DrawCube(-13.0f, 0.0f, z);

	//draw x=-7.0f && z=13.0f to 15.0f
	for (float z = 13.0f; z <= 15.0f; z++)
		DrawCube(-7.0f, 0.0f, z);

	//draw x=-10.0f && z=13.0f to 15.0f
	for (float z = 13.0f; z <= 15.0f; z++)
		DrawCube(-10.0f, 0.0f, z);

	//draw x=-4.0f && z=0.0f to 13.0f
	for (float z = 0.0f; z <= 13.0f; z++)
		DrawCube(-4.0f, 0.0f, z);

	//draw x=-1.0f && z=7.0f to 15.0f
	for (float z = 7.0f; z <= 15.0f; z++)
		DrawCube(-1.0f, 0.0f, z);

	//draw x=-1.0f to -3.0f && z=7.0f
	for (float x = -1.0f; x >= -3.0f; x--)
		DrawCube(x, 0.0f, 7.0f);

	//draw x=-4.0f to -7.0f && z=10.0f
	for (float x = -4.0f; x >= -7.0f; x--)
		DrawCube(x, 0.0f, 10.0f);

	//draw x=-1.0f && z=4.0f
	DrawCube(-1.0f, 0.0f, 4.0f);

	//draw x=-1.0f to -4.0f && z=0.0f
	for (float x = -1.0f; x >= -4.0f; x--)
		DrawCube(x, 0.0f, 0.0f);

	//draw x=-13.0f to -15.0f && z = 0.0f
	for (float x = -13.0f; x >= -15.0f; x--)
		DrawCube(x, 0.0f, 0.0f);

	//draw x=-13.0f && z=0.0f to 6.0f
	for (float z = 0.0f; z <= 6.0f; z++)
		DrawCube(-13.0f, 0.0f, z);
				
	//draw x=-13.0f to -7.0f && z=7.0f
	for (float x = -7.0f; x >= -13.0f; x--)
		DrawCube(x, 0.0f, 7.0f);

	//draw x=-10.0f && z=4.0f to 10.0f
	for (float z = 4.0f; z <= 10.0f; z++)
		DrawCube(-10.0f, 0.0f, z);

	//draw x=-7.0f to -10.0f && z=0.0f
	for (float x = -7.0f; x >= -10.0f; x--)
		DrawCube(x, 0.0f, 0.0f);

	//draw x=-7.0f && z=0.0f to 4.0f
	for (float z = 0.0f; z <= 4.0f; z++)
		DrawCube(-7.0f, 0.0f, z);

}

void DrawGameScene()
{
	wyDrawBottomLeftScene();
	chDrawTopLeftScene();
	chDrawTopRightScene();

}
	 

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_MAXIMIZED, GL_FALSE);

	// GLFWmonitor *glfwGetPrimaryMonitor() : Full Screen
	GLFWwindow *window = glfwCreateWindow(WinInfo::width, WinInfo::height, WinInfo::title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, OnCursorMovement);
	initGL();

	Camera camera;

	Matrix4 MVP;
	Matrix4 viewMatrix;
	Matrix4 projection;
	projection.perspective(45.0f * DEGtoRAD, static_cast<float>(WinInfo::width) / static_cast<float>(WinInfo::height), 0.1f, 10.0f);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.1f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		processInput(window);
		TimeManager::OnUpdate();

		camera.UpdateViewMatrix(cameraPos, cameraPos + cameraFront, cameraUp);
		viewMatrix = camera.getViewMatrix();
		MVP = projection * viewMatrix;

		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(MVP.get());

		DrawGameScene();



		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}