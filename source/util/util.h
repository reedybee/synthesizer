#pragma once

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>

typedef int int32;
typedef unsigned int uint32;
typedef short int16;
typedef unsigned short uint16;
typedef signed char int8;
typedef unsigned char uint8;

#define CLAMP(value,min,max) {if(value < min) { value = min; } else if(value > max) { value = max; }}

//convert 8 bit float to audio sample; 0 to 255.
void ConvertFloatToAudioSample(float fFloat, uint8 &nOut);
//convert 16 bit float to audio sample; -32,768 to 32,767.
void ConvertFloatToAudioSample(float fFloat, int16 &nOut);
//convert 32 bit float to audio sample; -2,147,483,648 to 2,147,483,647.
void ConvertFloatToAudioSample(float fFloat, int32 &nOut);


//calculate the frequency of the specified note.
float CalculateFrequency(float octave,float note);