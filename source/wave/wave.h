#pragma once

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <string>
#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

#include <util/util.h>

//this struct is the minimal required header data for a wav file
struct WaveAudioFile {
	// main chunk
	unsigned char chunkID[4];
	uint32 chunkSize;
	unsigned char format[4];

	// fmt sub chunk 1 
	unsigned char subChunk1ID[4];
	uint32 subChunk1Size;
	uint16 audioFormat;
	uint16 numChannels;
	uint32 sampleRate;
	uint32 byteRate;
	uint16 blockAlign;
	uint16 bitsPerSample;

	// "data" sub chunk 2
	unsigned char subChunk2ID[4];
	uint32 subChunk2Size;
};

template <typename T>
bool WriteWaveFile(const char* fileName, float *rawData, int32 numSamples, int16 numChannels, int32 sampleRate) {
	//open the file if we can

	FILE *File = fopen(fileName,"w+b");
	if(!File)
	{
		std::cout << "File failed to open.\n";
		return false;
	}

	//calculate bits per sample and the data size
	int32 bitsPerSample = sizeof(T) * 8;
	int dataSize = numSamples * sizeof(T);

	WaveAudioFile wave;

	//fill out the main chunk
	memcpy(wave.chunkID,"RIFF",4);
	wave.chunkSize = dataSize + 36;
	memcpy(wave.format,"WAVE",4);

	//fill out sub chunk 1 "fmt "
	memcpy(wave.subChunk1ID,"fmt ",4);
	wave.subChunk1Size = 16;
	wave.audioFormat = 1;
	wave.numChannels = numChannels;
	wave.sampleRate = sampleRate;
	wave.byteRate = sampleRate * numChannels * bitsPerSample / 8;
	wave.blockAlign = numChannels * bitsPerSample / 8;
	wave.bitsPerSample = bitsPerSample;

	//fill out sub chunk 2 "data"
	memcpy(wave.subChunk2ID,"data",4);
	wave.subChunk2Size = dataSize;

	//write the header
	fwrite(&wave,sizeof(WaveAudioFile),1,File);

	//write the wave data itself, converting it from float to the type specified
	T *pData = new T[numSamples];
	for(int nIndex = 0; nIndex < numSamples; ++nIndex)
		ConvertFloatToAudioSample(rawData[nIndex], pData[nIndex]);
	fwrite(pData, dataSize,1,File);
	delete[] pData;

	//close the file and return success
	fclose(File);
	return true;
}