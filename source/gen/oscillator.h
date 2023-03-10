#pragma once

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <string>
#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

#include <util/util.h>

float SineOscillator(float &phase, float frequency, float sampleRate) {
	phase += (float)M_PI * frequency / sampleRate;

	while (phase >= 2 * (float)M_PI)
		phase -= 2 * (float)M_PI;

	while (phase < 0)
		phase += 2 * (float)M_PI;

	return sin(phase);
}

float SawtoothOscillator(float &phase, float frequency, float sampleRate) {
	phase += frequency/sampleRate;

	while(phase > 1.0f)
		phase -= 1.0f;

	while(phase < 0.0f)
		phase += 1.0f;

	return (phase * 2.0f) - 1.0f;
}

float SquareOscillator(float &phase, float frequency, float sampleRate) {
	phase += frequency/sampleRate;

	while(phase > 1.0f)
		phase -= 1.0f;

	while(phase < 0.0f)
		phase += 1.0f;

	if(phase <= 0.5f)
		return -1.0f;
	else
		return 1.0f;
}

float TriangleOscillator(float &phase, float frequency, float sampleRate) {
	phase += frequency / sampleRate;

	while(phase > 1.0f)
		phase -= 1.0f;

	while(phase < 0.0f)
		phase += 1.0f;

	float ret;
	if(phase <= 0.5f)
		ret = phase * 2;
	else
		ret=(1.0f - phase) * 2;

	return (ret * 2.0f) - 1.0f;
}

float NoiseOscillator(float &phase, float frequency, float sampleRate, float lastValue, bool intense = false) {
	unsigned int lastSeed = (unsigned int)phase;
	phase += frequency / sampleRate;
	unsigned int seed = (unsigned int)phase;

	while(phase > 2.0f)
		phase -= 1.0f;

	if(seed != lastSeed) {
		float value = ((float)rand()) / ((float)RAND_MAX);
		value = (value * 2.0f) - 1.0f;

		if (intense) {

		if(value < 0)
			value = -1.0f;
		else
			value = 1.0f;
		}

		return value;
	} else {
		return lastValue;
	}
}