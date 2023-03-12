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

bool WriteWaveFile(const char* fileName, float *rawData, int32 numSamples, int16 numChannels, int32 sampleRate);