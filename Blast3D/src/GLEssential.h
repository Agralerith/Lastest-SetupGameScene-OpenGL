#ifndef GLESSENTIAL_H
#define GLESSENTIAL_H

const float PI			= 3.141593f;
const float DEGtoRAD	= PI / 180.0f;
const float RADtoDEG	= 180.0f / PI;

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClear();x;ASSERT(GLCheck());


void GLClear();
bool GLCheck();

#endif