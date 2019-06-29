#include "GLEssential.h"
#include "GL\glew.h"
#include <iostream>

void GLClear()
{
	while (unsigned int err = glGetError());
}

bool GLCheck()
{
	bool tof = true;

	while (unsigned int err = glGetError())
	{
		std::cout << "[OpenGL Error] :" << err << std::endl;
		tof = false;
	}

	return tof;
}