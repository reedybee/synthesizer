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

#include <util/util.h>
#include <wave/wave.h>
#include <gen/oscillator.h>

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

void sine(const char* name) {
	//make a sine wave
	for(int index = 0; index < numSamples; ++index)
	{
		data[index] = SineOscillator(phase, frequency, (float)sampleRate);
	}

	WriteWaveFile(name, data, numSamples, numChannels, sampleRate);
}

//the entry point of our application
int main(int argc, char* argv[]) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
	glfwWindowHint(GLFW_DECORATED, true);
	glfwWindowHint(GLFW_MAXIMIZED, false);
	
	GLFWwindow* window = glfwCreateWindow(500, 500, "synthesizer", NULL, NULL);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc(glfwGetProcAddress)))) {
		return 0;
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO & io = ImGui::GetIO();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();

	ImGui::StyleColorsDark();

	char* name;

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glClearColor(0.0f,0.0f,0.0f,0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("synth window");
		ImGui::InputFloat("Phase", &phase);
		ImGui::InputText("Name", name, 256);
		if (ImGui::Button("Generate Sine Wave")) {
			sine(name);
		}
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	}

	std::cout << "A4 " << CalculateFrequency(4, A) << "\n";
	std::cout << "B4 " << CalculateFrequency(4, B) << "\n";
	std::cout << "C4 " << CalculateFrequency(4, C) << "\n";
	std::cout << "D4 " << CalculateFrequency(4, D) << "\n";
	std::cout << "E4 " << CalculateFrequency(4, E) << "\n";
	std::cout << "F4 " << CalculateFrequency(4, F) << "\n";
	std::cout << "G4 " << CalculateFrequency(4, G) << "\n\n";
 
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