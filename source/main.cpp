#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <string>

#define _USE_MATH_DEFINES
#include <math.h>

#include <util/util.h>
#include <wave/wave.h>
#include <gen/oscillator.h>

//the entry point of our application
int main(int argc, char* argv[]) {

	std::cout << "A4 " << CalculateFrequency(4, A) << "\n";
	std::cout << "B4 " << CalculateFrequency(4, B) << "\n";
	std::cout << "C4 " << CalculateFrequency(4, C) << "\n";
	std::cout << "D4 " << CalculateFrequency(4, D) << "\n";
	std::cout << "E4 " << CalculateFrequency(4, E) << "\n";
	std::cout << "F4 " << CalculateFrequency(4, F) << "\n";
	std::cout << "G4 " << CalculateFrequency(4, G) << "\n\n";

	// standard waveform params
	int sampleRate = 44100;
	int numSeconds = 5;
	int numChannels = 1;
	float frequency = CalculateFrequency(3,3);

	//make our buffer to hold the samples
	int numSamples = sampleRate * numChannels * numSeconds; // TODO: remember this, later make sound dependant
	float *data = new float[numSamples];

	//the phase of our oscilator
	float phase = 0;

	//make a sine wave
	for(int index = 0; index < numSamples; ++index)
	{
		data[index] = SineOscillator(phase, frequency, (float)sampleRate);
	}

	WriteWaveFile("sine.wav", data, numSamples, numChannels, sampleRate);
	
	for(int index = 0; index < numSamples; ++index)
	{
		data[index] = SineOscillator(phase, frequency, (float)sampleRate);
	}

	WriteWaveFile("sineclip.wav", data, numSamples, numChannels, sampleRate);

	//make a saw wave
	for(int index = 0; index < numSamples; ++index)
	{
		data[index] = SawtoothOscillator(phase, frequency, (float)sampleRate);
	}

	WriteWaveFile("saw.wav", data, numSamples, numChannels, sampleRate);

	//make a square wave
	for(int index = 0; index < numSamples; ++index)
	{
		data[index] = SquareOscillator(phase, frequency, (float)sampleRate);
	}

	WriteWaveFile("square.wav", data, numSamples, numChannels, sampleRate);

	//make a triangle wave
	for(int index = 0; index < numSamples; ++index)
	{
		data[index] = TriangleOscillator(phase, frequency, (float)sampleRate);
	}

	WriteWaveFile("triangle.wav", data, numSamples, numChannels, sampleRate);

	//make some noise
	for(int index = 0; index < numSamples; ++index)
	{
		data[index] = NoiseOscillator(phase, frequency, (float)sampleRate, index > 0 ? data[index - 1] : 0.0f);
	}

	WriteWaveFile("noise.wav", data, numSamples, numChannels, sampleRate);

	//free our data buffer
	delete[] data;

	return 0;
}