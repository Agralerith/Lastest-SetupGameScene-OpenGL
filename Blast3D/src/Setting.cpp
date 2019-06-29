#include "Setting.h"
#include <GLFW\glfw3.h>

int			WinInfo::width	= 800;
int			WinInfo::height	= 600;
std::string	WinInfo::title	= "3D Blast Gaming";

float	TimeManager::previousTime	= 0.0f;
float	TimeManager::currentTime	= 0.0f;
float	TimeManager::deltaTime		= 0.0f;

void TimeManager::OnUpdate()
{
	currentTime = glfwGetTime();
	deltaTime = currentTime - previousTime;
	previousTime = currentTime;
}

float TimeManager::getDeltaTime()
{
	return deltaTime;
}
