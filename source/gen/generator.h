#pragma once

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

#include <gen/oscillator.h>

// A bunch of different default waveforms, exports as a .wav file
struct DefaultGenerator {
    void all(float frequency);

    void sine(const char* name, int seconds, float frequency, float amplitudeScale = 1.0f ,int sampleRate = 44100, int numChannels = 1);
    void saw(const char* name, int seconds, float frequency, float amplitudeScale = 1.0f, int sampleRate = 44100, int numChannels = 1);
    void square(const char* name, int seconds, float frequency, float amplitudeScale = 1.0f, int sampleRate = 44100, int numChannels = 1);
    void triangle(const char* name, int seconds, float frequency, float amplitudeScale = 1.0f, int sampleRate = 44100, int numChannels = 1);
    void noise(const char* name, int seconds, float frequency, float amplitudeScale = 1.0f, int sampleRate = 44100, int numChannels = 1);
} static defaultGenerator;