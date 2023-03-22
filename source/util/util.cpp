#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include <util/util.h>

void NormalizeByte(float value, uint8 &clampedValue) {
	value = (value - 0) / (0 - 255);
	
	clampedValue = (uint8)value;
}

void ConvertFloatToAudioSample(float value, int16 &clampedValue) {
	value *= 32767.0f;
	CLAMP(value, -32768.0f, 32767.0f);
	clampedValue = (int16)value;
}

void ConvertFloatToAudioSample(float value, int32 &clampedValue) {
    double workingValue = (double)value;
	workingValue *= 2147483647.0;
	CLAMP(workingValue, -2147483648.0, 2147483647.0);
	clampedValue = (int32)workingValue;
}

//calculate the frequency of the specified note.
float CalculateFrequency(float octave, float note) {
	return (float)(440 * pow(2.0, ((double)((octave-5) * 12 + note)) / 12.0));
}

/*
	notes:
	0  = A
	1  = A#
	2  = B
	3  = C
	4  = C#
	5  = D
	6  = D#
	7  = E
	8  = F
	9  = F#
	10 = G
	11 = G#
*/