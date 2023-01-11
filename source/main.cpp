#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <string>

#define _USE_MATH_DEFINES
#include <math.h>

#include <util/util.h>
#include <wave/wave.h>

/*
	frequency equation
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

float SineOscillator(float &phase, float frequency, float sampleRate)
{
	phase += 2 * (float)M_PI * frequency / sampleRate;

	while (phase >= 2 * (float)M_PI)
		phase -= 2 * (float)M_PI;

	while (phase < 0)
		phase += 2 * (float)M_PI;

	return sin(phase);
}

float SawtoothOscillator(float &fPhase, float fFrequency, float fSampleRate)
{
	fPhase += fFrequency/fSampleRate;

	while(fPhase > 1.0f)
		fPhase -= 1.0f;

	while(fPhase < 0.0f)
		fPhase += 1.0f;

	return (fPhase * 2.0f) - 1.0f;
}

float SquareOscillator(float &fPhase, float fFrequency, float fSampleRate)
{
	fPhase += fFrequency/fSampleRate;

	while(fPhase > 1.0f)
		fPhase -= 1.0f;

	while(fPhase < 0.0f)
		fPhase += 1.0f;

	if(fPhase <= 0.5f)
		return -1.0f;
	else
		return 1.0f;
}

float TriangleOscillator(float &fPhase, float fFrequency, float fSampleRate)
{
	fPhase += fFrequency/fSampleRate;

	while(fPhase > 1.0f)
		fPhase -= 1.0f;

	while(fPhase < 0.0f)
		fPhase += 1.0f;

	float fRet;
	if(fPhase <= 0.5f)
		fRet=fPhase*2;
	else
		fRet=(1.0f - fPhase)*2;

	return (fRet * 2.0f) - 1.0f;
}

float NoiseOscillator(float &fPhase, float fFrequency, float fSampleRate, float fLastValue, bool intense = false)
{
	unsigned int nLastSeed = (unsigned int)fPhase;
	fPhase += fFrequency/fSampleRate;
	unsigned int nSeed = (unsigned int)fPhase;

	while(fPhase > 2.0f)
		fPhase -= 1.0f;

	if(nSeed != nLastSeed)
	{
		float fValue = ((float)rand()) / ((float)RAND_MAX);
		fValue = (fValue * 2.0f) - 1.0f;

		if (intense) {

		if(fValue < 0)
			fValue = -1.0f;
		else
			fValue = 1.0f;
		}

		return fValue;
	}
	else
	{
		return fLastValue;
	}
}

//the entry point of our application
int main(int argc, char* argv[])
{
	// standard waveform params
	int nSampleRate = 44100;
	int nNumSeconds = 4;
	int nNumChannels = 1;
	float fFrequency = CalculateFrequency(3,3); // middle C

	//make our buffer to hold the samples
	int nNumSamples = nSampleRate * nNumChannels * nNumSeconds; // TODO: remember this, later make sound dependant
	float *pData = new float[nNumSamples];

	//the phase of our oscilator, we don't really need to reset it between wave files
	//it just needs to stay continuous within a wave file
	float fPhase = 0;

	//make a naive sine wave
	for(int nIndex = 0; nIndex < nNumSamples; ++nIndex)
	{
		pData[nIndex] = sin((float)nIndex * 2 * (float)M_PI * fFrequency / (float)nSampleRate);
	}

	WriteWaveFile<int16>("sinenaive.wav",pData,nNumSamples,nNumChannels,nSampleRate);

	//make a discontinuitous (popping) sine wave
	for(int nIndex = 0; nIndex < nNumSamples; ++nIndex)
	{
		if(nIndex < nNumSamples / 2)
		{
			float fCurrentFrequency = CalculateFrequency(3,3);
			pData[nIndex] = sin((float)nIndex * 2 * (float)M_PI * fCurrentFrequency / (float)nSampleRate);
		}
		else
		{
			float fCurrentFrequency = CalculateFrequency(3,4);
			pData[nIndex] = sin((float)nIndex * 2 * (float)M_PI * fCurrentFrequency / (float)nSampleRate);
		}
	}

	WriteWaveFile<int16>("sinediscon.wav",pData,nNumSamples,nNumChannels,nSampleRate);

	//make a continuous sine wave that changes frequencies
	for(int nIndex = 0; nIndex < nNumSamples; ++nIndex)
	{
		if(nIndex < nNumSamples / 2)
		{
			float fCurrentFrequency = CalculateFrequency(3,3);
			fPhase += 2 * (float)M_PI * fCurrentFrequency/(float)nSampleRate;

			while(fPhase >= 2 * (float)M_PI)
				fPhase -= 2 * (float)M_PI;

			while(fPhase < 0)
				fPhase += 2 * (float)M_PI;

			pData[nIndex] = sin(fPhase);
		}
		else
		{
			float fCurrentFrequency = CalculateFrequency(3,4);
			fPhase += 2 * (float)M_PI * fCurrentFrequency/(float)nSampleRate;

			while(fPhase >= 2 * (float)M_PI)
				fPhase -= 2 * (float)M_PI;

			while(fPhase < 0)
				fPhase += 2 * (float)M_PI;

			pData[nIndex] = sin(fPhase);
		}
	}

	WriteWaveFile<int16>("sinecon.wav",pData,nNumSamples,nNumChannels,nSampleRate);

	//make a sine wave
	for(int nIndex = 0; nIndex < nNumSamples; ++nIndex)
	{
		pData[nIndex] = SquareOscillator(fPhase,fFrequency,(float)nSampleRate);
	}

	WriteWaveFile<int16>("sine.wav",pData,nNumSamples,nNumChannels,nSampleRate);

	//make a quieter sine wave
	for(int nIndex = 0; nIndex < nNumSamples; ++nIndex)
	{
		pData[nIndex] = SineOscillator(fPhase,fFrequency,(float)nSampleRate) * 0.4f;
	}

	WriteWaveFile<int16>("sinequiet.wav",pData,nNumSamples,nNumChannels,nSampleRate);

	//make a clipping sine wave
	for(int nIndex = 0; nIndex < nNumSamples; ++nIndex)
	{
		pData[nIndex] = SineOscillator(fPhase,fFrequency,(float)nSampleRate) * 1.4f;
	}

	WriteWaveFile<int16>("sineclip.wav",pData,nNumSamples,nNumChannels,nSampleRate);

	//make a saw wave
	for(int nIndex = 0; nIndex < nNumSamples; ++nIndex)
	{
		pData[nIndex] = SawtoothOscillator(fPhase,fFrequency,(float)nSampleRate);
	}

	WriteWaveFile<int16>("saw.wav",pData,nNumSamples,nNumChannels,nSampleRate);

	//make a square wave
	for(int nIndex = 0; nIndex < nNumSamples; ++nIndex)
	{
		pData[nIndex] = SquareOscillator(fPhase,fFrequency,(float)nSampleRate);
	}

	WriteWaveFile<int16>("square.wav",pData,nNumSamples,nNumChannels,nSampleRate);

	//make a triangle wave
	for(int nIndex = 0; nIndex < nNumSamples; ++nIndex)
	{
		pData[nIndex] = TriangleOscillator(fPhase,fFrequency,(float)nSampleRate);
	}

	WriteWaveFile<int16>("triangle.wav",pData,nNumSamples,nNumChannels,nSampleRate);

	//make some noise or... make... some... NOISE!!!
	for(int nIndex = 0; nIndex < nNumSamples; ++nIndex)
	{
		pData[nIndex] = NoiseOscillator(fPhase,fFrequency,(float)nSampleRate, nIndex > 0 ? pData[nIndex-1] : 0.0f);
	}

	WriteWaveFile<int16>("noise.wav",pData,nNumSamples,nNumChannels,nSampleRate);

	//make a dumb little song
	for(int nIndex = 0; nIndex < nNumSamples; ++nIndex)
	{
		//calculate which quarter note we are on
		int nQuarterNote = nIndex * 4 / nSampleRate;
		float fQuarterNotePercent = (float)((nIndex * 4) % nSampleRate) / (float)nSampleRate;

		//intentionally add a "pop" noise mid way through the 3rd quarter note
		// if(nIndex == nSampleRate * 3 / 4 + nSampleRate / 8)
		// {
		// 	pData[nIndex] = -1.0f;
		// 	continue;
		// }

		//do different logic based on which quarter note we are on
		switch(nQuarterNote)
		{
			case 0:
			{
				pData[nIndex] = SineOscillator(fPhase,CalculateFrequency(1,3),(float)nSampleRate);
				break;
			}
			case 1:
			{
				pData[nIndex] = SineOscillator(fPhase,CalculateFrequency(1,10),(float)nSampleRate);
				break;
			}
			case 2:
			{
				pData[nIndex] = SineOscillator(fPhase,CalculateFrequency(1,2),(float)nSampleRate);
				break;
			}
			case 3:
			{
				pData[nIndex] = SineOscillator(fPhase,CalculateFrequency(1,10),(float)nSampleRate);
				break;
			}
			case 4:
			{
				pData[nIndex] = SineOscillator(fPhase,CalculateFrequency(1,3),(float)nSampleRate);
				break;
			}
			case 5:
			{
				pData[nIndex] = SineOscillator(fPhase,CalculateFrequency(1,2),(float)nSampleRate);
				break;
			}
			case 6:
			{
				pData[nIndex] = SineOscillator(fPhase,CalculateFrequency(1,0),(float)nSampleRate) * (1.0f - fQuarterNotePercent);
				break;
			}
			case 7: {
				pData[nIndex] = SawtoothOscillator(fPhase,CalculateFrequency(1,10),(float)nSampleRate);
				break;
			}
			case 8:
			{
				pData[nIndex] = SawtoothOscillator(fPhase,CalculateFrequency(3,0),(float)nSampleRate);
				break;
			}
			case 9:
			{
				pData[nIndex] = SawtoothOscillator(fPhase,CalculateFrequency(3,2),(float)nSampleRate);
				break;
			}
			case 10:
			{
				pData[nIndex] = SawtoothOscillator(fPhase,CalculateFrequency(3,10),(float)nSampleRate);
				break;
			}
			case 11:
			{
				pData[nIndex] = SawtoothOscillator(fPhase,CalculateFrequency(3,5),(float)nSampleRate);
				break;
			}
			case 12:
			{
				pData[nIndex] = SawtoothOscillator(fPhase,CalculateFrequency(3,5),(float)nSampleRate);
				break;
			}
			case 13:
			{
				pData[nIndex] = SawtoothOscillator(fPhase,CalculateFrequency(3,3 + fQuarterNotePercent * 2.0f),(float)nSampleRate);
				break;
			}
			case 14:
			{
				pData[nIndex] = SawtoothOscillator(fPhase,CalculateFrequency(3,5),(float)nSampleRate) * (1.0f - fQuarterNotePercent);
				break;
			}
			case 15:
			case 16: {
				pData[nIndex] = SawtoothOscillator(fPhase,CalculateFrequency(3,5),(float)nSampleRate) * (1.0f - fQuarterNotePercent);
				break;
			}
			default:
			{
				pData[nIndex] = 0;
				break;
			}
		}
	}

	WriteWaveFile<int16>("song.wav",pData,nNumSamples,nNumChannels,nSampleRate);

	//free our data buffer
	delete[] pData;

	return 0;
}