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

float SineOscillator(float &phase, float frequency, float sampleRate);

float SawtoothOscillator(float &phase, float frequency, float sampleRate);

float SquareOscillator(float &phase, float frequency, float sampleRate);

float TriangleOscillator(float &phase, float frequency, float sampleRate);

float NoiseOscillator(float &phase, float frequency, float sampleRate, float lastValue, bool intense = false);