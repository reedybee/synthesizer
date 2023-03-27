#define NOMINMAX
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include <stdio.h>
#include <memory.h>
#include <thread>
#include <algorithm>
#include <stdlib.h>
#include <string>

#define _USE_MATH_DEFINES
#include <math.h>

#include <util/util.h>
#include <wave/wave.h>
#include <gen/oscillator.h>
#include <gen/generator.h>
#include <ren/renderer.h>

#include <serial/serial.h>

float phase = 0;

float frequency = CalculateFrequency(4,4);

//the entry point of our application
int main(int argc, char* argv[]) {
	std::cout << "A4 " << CalculateFrequency(4, A) << "\n";
	std::cout << "B4 " << CalculateFrequency(4, B) << "\n";
	std::cout << "C4 " << CalculateFrequency(4, C) << "\n";
	std::cout << "D4 " << CalculateFrequency(4, D) << "\n";
	std::cout << "E4 " << CalculateFrequency(4, E) << "\n";
	std::cout << "F4 " << CalculateFrequency(4, F) << "\n";
	std::cout << "G4 " << CalculateFrequency(4, G) << "\n\n";

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
	
	Renderer renderer = Renderer(500, 500, "synthesizer");

	if (!gladLoadGLLoader((GLADloadproc(glfwGetProcAddress)))) {
		return 0;
	}

	Serial serial = Serial("\\\\.\\COM3", CBR_19200); 

	renderer.ImGuiInit();

	float value = 0;
	float voltage = 0;
	float normValue = 0;

	double lasttime = glfwGetTime();
	static const char* selectedWaveform = defaultWaveforms[0];
	while (!renderer.ShouldClose()) {
		renderer.ClearFramebuffer();
		renderer.ImGuiNewFrame();

		ImGui::Begin("synth window");

		if (ImGui::BeginCombo("Default Waveform", selectedWaveform)) {
			for (int i = 0; i < IM_ARRAYSIZE(defaultWaveforms); i++) {
				bool selected = (selectedWaveform == defaultWaveforms[i]);
				if (ImGui::Selectable(defaultWaveforms[i], selected))
					selectedWaveform = defaultWaveforms[i];
				if (selected)
					ImGui::SetItemDefaultFocus();
			}
		}
		std::string defaultWaveName = "Generate ";
		defaultWaveName.append(selectedWaveform);
		if (ImGui::Button(defaultWaveName.c_str())) {
			if (selectedWaveform == "None")
				std::cout << "Could not generate file as no waveform is selected.\n";
			if (selectedWaveform == "Sine")
				defaultGenerator.sine("sine", 5, frequency);
			if (selectedWaveform == "Sawtooth")
				defaultGenerator.saw("sawtooth", 5, frequency);
			if (selectedWaveform == "Square")
				defaultGenerator.square("square", 5, frequency);
			if (selectedWaveform == "Triangle")
				defaultGenerator.triangle("triangle", 5, frequency);
			if (selectedWaveform == "Noise")
				defaultGenerator.noise("noise", 5, frequency);
		}


		static std::chrono::time_point<std::chrono::steady_clock> lastSendTime;
		if (std::chrono::steady_clock::now() - lastSendTime >= std::chrono::milliseconds(70)) {
			
			value = SineOscillator(phase, frequency, 44100 / 2);

			voltage = (value + 1) * 1.5;

			normValue = (value + 1) * 127.5f;

			serial.Write(normValue);

			lastSendTime = std::chrono::steady_clock::now();
		}

		ImGui::SliderFloat("Value", &value, -1, 1);
		ImGui::SliderFloat("Voltage", &voltage, 0, 3);
		ImGui::SliderFloat("Phase", &phase, 0, 6);
		ImGui::SliderFloat("Normalized", &normValue, 0, 255);

		renderer.ImGuiRender();
		renderer.Render();

		while (glfwGetTime() < lasttime + 1.0 / 30) {
			glfwWaitEventsTimeout(lasttime + 1.0 / 30 - glfwGetTime());
		}

    	lasttime = glfwGetTime();
	}
	glfwTerminate();
	serial.Close();
	return 0;
	}