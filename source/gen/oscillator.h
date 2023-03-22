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
#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

#include <util/util.h>

// Generates the value at a specific point along a sine waveform 
float SineOscillator(float &phase, float frequency, float sampleRate);
// Generates the value at a specific point along a sawtooth waveform
float SawtoothOscillator(float &phase, float frequency, float sampleRate);
// Generates the value at a specific point along a square waveform
float SquareOscillator(float &phase, float frequency, float sampleRate);
// Generates the value at a specific point along a triangle waveform
float TriangleOscillator(float &phase, float frequency, float sampleRate);
// Generates random noise
float NoiseOscillator(float &phase, float frequency, float sampleRate, float lastValue, bool intense = false);