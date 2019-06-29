#ifndef SETTING_H
#define SETTING_H

#include <string>

struct WinInfo
{
	// window
	static int width;
	static int height;
	static std::string title;
};

class TimeManager
{
private:
	static float	previousTime;
	static float	currentTime;
	static float	deltaTime;

public:
	static void		OnUpdate();
	static float	getDeltaTime();
};

enum Color
{
	RED = 0,	GREEN,		BLUE, 
	YELLOW,		PURPLE,		AQUA,
	BLACK,		WHITE,		
	LIGHTGREY,	DARKGREY,
	ORANGE,		DARKGREEN,	LIGHTGREEN,
	DARKBLUE,	LIGHTBLUE,	
	LIGHTRED,	DARKRED
};

#endif
