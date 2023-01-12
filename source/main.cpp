#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <string>

#define _USE_MATH_DEFINES
#include <math.h>

#include <util/util.h>
#include <util/song.h>
#include <wave/wave.h>
#include <gen/oscillator.h>

/*
	frequency equatione
	frequency = 440(2^(n/12))

	N=0 is A4
	N=1 is A#4

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

//the entry point of our application
int main(int argc, char* argv[]) {

	std::cout << "A4 " << CalculateFrequency(4, A) << "\n";
	std::cout << "B4 " << CalculateFrequency(4, B) << "\n";
	std::cout << "C4 " << CalculateFrequency(4, C) << "\n";
	std::cout << "D4 " << CalculateFrequency(4, D) << "\n";
	std::cout << "E4 " << CalculateFrequency(4, E) << "\n";
	std::cout << "F4 " << CalculateFrequency(4, F) << "\n";
	std::cout << "G4 " << CalculateFrequency(4, G) << "\n\n";

	// song input testing

	Song song = Song("res/song.txt");

	// end

	// standard waveform params
	int sampleRate = 44100;
	int numSeconds = 9;
	int numChannels = 1;
	float frequency = CalculateFrequency(3,3);

	//make our buffer to hold the samples
	int numSamples = sampleRate * numChannels * numSeconds; // TODO: remember this, later make sound dependant
	float *data = new float[numSamples];

	//the phase of our oscilator, we don't really need to reset it between wave files
	//it just needs to stay continuous within a wave file
	float phase = 0;

	//make a naive sine wave
	for(int index = 0; index < numSamples; ++index)
	{
		data[index] = sin((float)index * 2 * (float)M_PI * frequency / (float)sampleRate);
	}

	WriteWaveFile<int16>("sinenaive.wav", data, numSamples, numChannels, sampleRate);

	//make a discontinuitous (popping) sine wave
	for(int index = 0; index < numSamples; ++index)
	{
		if(index < numSamples / 2)
		{
			float fCurrentFrequency = CalculateFrequency(3,3);
			data[index] = sin((float)index * 2 * (float)M_PI * fCurrentFrequency / (float)sampleRate);
		}
		else
		{
			float fCurrentFrequency = CalculateFrequency(3,4);
			data[index] = sin((float)index * 2 * (float)M_PI * fCurrentFrequency / (float)sampleRate);
		}
	}

	WriteWaveFile<int16>("sinediscon.wav", data, numSamples, numChannels, sampleRate);

	//make a continuous sine wave that changes frequencies
	for(int index = 0; index < numSamples; ++index)
	{
		if(index < numSamples / 2)
		{
			float fCurrentFrequency = CalculateFrequency(3,3);
			phase += 2 * (float)M_PI * fCurrentFrequency/(float)sampleRate;

			while(phase >= 2 * (float)M_PI)
				phase -= 2 * (float)M_PI;

			while(phase < 0)
				phase += 2 * (float)M_PI;

			data[index] = sin(phase);
		}
		else
		{
			float fCurrentFrequency = CalculateFrequency(3,4);
			phase += 2 * (float)M_PI * fCurrentFrequency / (float)sampleRate;

			while(phase >= 2 * (float)M_PI)
				phase -= 2 * (float)M_PI;

			while(phase < 0)
				phase += 2 * (float)M_PI;

			data[index] = sin(phase);
		}
	}

	WriteWaveFile<int16>("sinecon.wav", data, numSamples, numChannels, sampleRate);

	//make a sine wave
	for(int index = 0; index < numSamples; ++index)
	{
		data[index] = SineOscillator(phase, frequency, (float)sampleRate);
	}

	WriteWaveFile<int16>("sine.wav", data, numSamples, numChannels, sampleRate);

	//make a quieter sine wave
	for(int index = 0; index < numSamples; ++index)
	{
		data[index] = SineOscillator(phase, frequency, (float)sampleRate) * 0.4f;
	}

	WriteWaveFile<int16>("sinequiet.wav", data, numSamples, numChannels, sampleRate);

	//make a clipping sine wave
	for(int index = 0; index < numSamples; ++index)
	{
		data[index] = SineOscillator(phase, frequency, (float)sampleRate) * 1.4f;
	}

	WriteWaveFile<int16>("sineclip.wav", data, numSamples, numChannels, sampleRate);

	//make a saw wave
	for(int index = 0; index < numSamples; ++index)
	{
		data[index] = SawtoothOscillator(phase, frequency, (float)sampleRate);
	}

	WriteWaveFile<int16>("saw.wav", data, numSamples, numChannels, sampleRate);

	//make a square wave
	for(int index = 0; index < numSamples; ++index)
	{
		data[index] = SquareOscillator(phase, frequency, (float)sampleRate);
	}

	WriteWaveFile<int16>("square.wav", data, numSamples, numChannels, sampleRate);

	//make a triangle wave
	for(int index = 0; index < numSamples; ++index)
	{
		data[index] = TriangleOscillator(phase, frequency, (float)sampleRate);
	}

	WriteWaveFile<int16>("triangle.wav", data, numSamples, numChannels, sampleRate);

	//make some noise or... make... some... NOISE!!!
	for(int index = 0; index < numSamples; ++index)
	{
		data[index] = NoiseOscillator(phase, frequency, (float)sampleRate, index > 0 ? data[index-1] : 0.0f);
	}

	WriteWaveFile<int16>("noise.wav", data, numSamples, numChannels, sampleRate);

	float octaves[] = {
		4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
		4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
	};
	
	float notes[] = {
		3, 10, 2, 10, 
		3, 2, 0, 10, 0, 2, 10,
		5, 10, 2, 10,
		3, 2, 0, 10, 0, 2, 5, 2, 
		7, 10, 2, 10, 
		3, 2, 0, 10, 0, 2, 10 
	};

	for (int index = 0; index < numSamples; index++) {
		int quarterNote = index * 4 / sampleRate;
		data[index] = SineOscillator(phase,CalculateFrequency(2,notes[quarterNote]),(float)sampleRate);
	}

	WriteWaveFile<int16>("songtest.wav", data, numSamples, numChannels, sampleRate);

	// TODO: fix this you  dummy
	// for (int index = 0; index < numSamples; index++) {
	// 	int quarterNote = index * 4 / sampleRate;
	// 	data[index] = SineOscillator(phase, CalculateFrequency(2, quarterNote), (float)sampleRate);
	// }

	// WriteWaveFile<int16>("scale.wav", data, numSamples, numChannels, sampleRate);

	//make a dumb little song
	for(int index = 0; index < numSamples; index++)
	{
		//calculate which quarter note we are on
		int nQuarterNote = index * 4 / sampleRate;
		float fQuarterNotePercent = (float)((index * 4) % sampleRate) / (float)sampleRate;

		//do different logic based on which quarter note we are on
		switch(nQuarterNote)
		{
			case 0:
			{
				data[index] = SineOscillator(phase,CalculateFrequency(1,3),(float)sampleRate);
				break;
			}
			case 1:
			{
				data[index] = SineOscillator(phase,CalculateFrequency(1,10),(float)sampleRate);
				break;
			}
			case 2:
			{
				data[index] = SineOscillator(phase,CalculateFrequency(1,2),(float)sampleRate);
				break;
			}
			case 3:
			{
				data[index] = SineOscillator(phase,CalculateFrequency(1,10),(float)sampleRate);
				break;
			}
			case 4:
			{
				data[index] = SineOscillator(phase,CalculateFrequency(1,3),(float)sampleRate);
				break;
			}
			case 5:
			{
				data[index] = SineOscillator(phase,CalculateFrequency(1,2),(float)sampleRate);
				break;
			}
			case 6:
			{
				data[index] = SineOscillator(phase,CalculateFrequency(1,0),(float)sampleRate) * (1.0f - fQuarterNotePercent);
				break;
			}
			case 7: {
				data[index] = SawtoothOscillator(phase,CalculateFrequency(1,10),(float)sampleRate);
				break;
			}
			case 8:
			{
				data[index] = SawtoothOscillator(phase,CalculateFrequency(3,0),(float)sampleRate);
				break;
			}
			case 9:
			{
				data[index] = SawtoothOscillator(phase,CalculateFrequency(3,2),(float)sampleRate);
				break;
			}
			case 10:
			{
				data[index] = SawtoothOscillator(phase,CalculateFrequency(3,10),(float)sampleRate);
				break;
			}
			case 11:
			{
				data[index] = SawtoothOscillator(phase,CalculateFrequency(3,5),(float)sampleRate);
				break;
			}
			case 12:
			{
				data[index] = SawtoothOscillator(phase,CalculateFrequency(3,5),(float)sampleRate);
				break;
			}
			case 13:
			{
				data[index] = SawtoothOscillator(phase,CalculateFrequency(3,3 + fQuarterNotePercent * 2.0f),(float)sampleRate);
				break;
			}
			case 14:
			{
				data[index] = SawtoothOscillator(phase,CalculateFrequency(3,5),(float)sampleRate) * (1.0f - fQuarterNotePercent);
				break;
			}
			case 15:
			case 16: {
				data[index] = SawtoothOscillator(phase,CalculateFrequency(3,5),(float)sampleRate) * (1.0f - fQuarterNotePercent);
				break;
			}
			default:
			{
				data[index] = 0;
				break;
			}
		}
	}

	WriteWaveFile<int16>("song.wav",data,numSamples,numChannels,sampleRate);



	//free our data buffer
	delete[] data;

	return 0;
}