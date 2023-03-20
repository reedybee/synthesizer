#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <string>

#define _USE_MATH_DEFINES
#include <math.h>

#include <util/util.h>

#include <wave/wave.h>

bool WriteWaveFile(const char* fileName, float *rawData, int32 numSamples, int16 numChannels, int32 sampleRate) {
	//open the file if we can

	std::string name = fileName;
	name.append(".wav");

	FILE *File = fopen(name.c_str(), "w+b");
	if(!File) {
		std::cout << "File failed to open.\n";
		return false;
	}
	else {
		std::cout << "File has been created of name " << fileName << "\n";
	}

	//calculate bits per sample and the data size
	int32 bitsPerSample = sizeof(int32) * 8;
	int dataSize = numSamples * sizeof(int32);

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
	fwrite(&wave, sizeof(WaveAudioFile), 1, File);

	//write the wave data itself, converting it from float to the type specified
	int32* data = new int32[numSamples];
	for(int i = 0; i < numSamples; i++)
		ConvertFloatToAudioSample(rawData[i], data[i]);
	fwrite(data, dataSize,1,File);
	delete[] data;

	//close the file and return success
	fclose(File);
	return true;
}