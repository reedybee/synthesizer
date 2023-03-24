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

// TODO: talk to mr stone about finding a better name for this "synth"

float phase;

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

	Serial serial = Serial("\\\\.\\COM3", CBR_9600); 

	renderer.ImGuiInit();

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


		float value = SineOscillator(phase, frequency, 44100);

		float voltage = (value + 1) * 1.5;
		ImGui::SliderFloat("Value", &value, 0, 255);
		ImGui::InputFloat("Voltage", &voltage, 0, 255);
		ImGui::InputFloat("Phase", &phase);

		float normValue = (value + 1) * 127.5f;

		ImGui::SliderFloat("Normalized", &normValue, 0, 255);
		serial.Write(normValue);
		renderer.ImGuiRender();
		renderer.Render();
		while (glfwGetTime() < lasttime + 1.0 / 30) {

    	}
		lasttime += 1.0 / 30;
	}
	glfwTerminate();
	serial.Close();
	return 0;
	}