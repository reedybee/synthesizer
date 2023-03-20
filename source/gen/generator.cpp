#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <string>

#define _USE_MATH_DEFINES
#include <math.h>

#include <wave/wave.h>
#include <gen/oscillator.h>
#include <gen/generator.h>

void DefaultGenerator::all(float frequency) {
    
    defaultGenerator.sine("sine", 5, frequency);
	defaultGenerator.sine("sineClip", 5, frequency, 1.4f);
	defaultGenerator.saw("sawtooth", 5, frequency);
	defaultGenerator.square("square", 5, frequency);
	defaultGenerator.triangle("triangle", 5, frequency);
	defaultGenerator.noise("noise", 5, frequency);
}

void DefaultGenerator::sine(const char* name, int seconds, float frequency, float amplitudeScale, int sampleRate, int numChannels) {
    //make a sine wave
    int numSamples = sampleRate * numChannels * seconds; 
    float* data = new float[numSamples];
    float phase = 0;
	for(int index = 0; index < numSamples; index++)
	{
		data[index] = SineOscillator(phase, frequency, (float)sampleRate) * amplitudeScale;
	}
	WriteWaveFile(name, data, numSamples, numChannels, sampleRate);
    delete[] data;
}

void DefaultGenerator::saw(const char* name, int seconds, float frequency, float amplitudeScale, int sampleRate, int numChannels) {
    //make a sine wave
    int numSamples = sampleRate * numChannels * seconds; 
    float* data = new float[numSamples];
    float phase = 0;
	for(int index = 0; index < numSamples; index++)
	{
		data[index] = SawtoothOscillator(phase, frequency, (float)sampleRate) * amplitudeScale;
	}
	WriteWaveFile(name, data, numSamples, numChannels, sampleRate);
    delete[] data;
}

void DefaultGenerator::square(const char* name, int seconds, float frequency, float amplitudeScale, int sampleRate, int numChannels) {
    //make a sine wave
    int numSamples = sampleRate * numChannels * seconds; 
    float* data = new float[numSamples];
    float phase = 0;
	for(int index = 0; index < numSamples; index++)
	{
		data[index] = SquareOscillator(phase, frequency, (float)sampleRate) * amplitudeScale;
	}
	WriteWaveFile(name, data, numSamples, numChannels, sampleRate);
    delete[] data;
}

void DefaultGenerator::triangle(const char* name, int seconds, float frequency, float amplitudeScale, int sampleRate, int numChannels) {
    //make a sine wave
    int numSamples = sampleRate * numChannels * seconds; 
    float* data = new float[numSamples];
    float phase = 0;
	for(int index = 0; index < numSamples; index++)
	{
		data[index] = TriangleOscillator(phase, frequency, (float)sampleRate) * amplitudeScale;
	}
	WriteWaveFile(name, data, numSamples, numChannels, sampleRate);
    delete[] data;
}

void DefaultGenerator::noise(const char* name, int seconds, float frequency, float amplitudeScale, int sampleRate, int numChannels) {
    //make a sine wave
    int numSamples = sampleRate * numChannels * seconds; 
    float* data = new float[numSamples];
    float phase = 0;
	for(int index = 0; index < numSamples; index++)
	{
		data[index] = NoiseOscillator(phase, frequency, (float)sampleRate, index > 0 ? data[index - 1] : 0.0f) * amplitudeScale;
	}
	WriteWaveFile(name, data, numSamples, numChannels, sampleRate);
    delete[] data;
}