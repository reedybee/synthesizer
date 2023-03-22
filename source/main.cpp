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
#include <gen/generator.h>
#include <ren/renderer.h>

#include <serial/serial.h>

// TODO: talk to mr stone about finding a better name for this "synth"

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

	int value = 0;

	Serial serial = Serial("\\\\.\\COM3", CBR_9600);

	renderer.ImGuiInit();

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
			ImGui::EndCombo();
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
		if (ImGui::Button("Generate All Default Wave Files")) {
			defaultGenerator.all(frequency);
		}
		if (ImGui::Button("100%")) {
			serial.Write(255);
		}
		if (ImGui::Button("50%")) {
			serial.Write(128);
		}
		if (ImGui::Button("0%")) {
			serial.Write(0);
		}
		
		ImGui::SliderInt("Value", &value, 0, 255);
		
		if (ImGui::Button("Set Value")) {
			serial.Write(value);
		}

		renderer.ImGuiRender();
		renderer.Render();
	}
	glfwTerminate();
	serial.Close();
	return 0;
	}