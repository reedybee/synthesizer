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

float frequency = CalculateFrequency(3,3);

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
	glfwWindowHint(GLFW_DECORATED, true);
	glfwWindowHint(GLFW_MAXIMIZED, false);
	
	Renderer renderer = Renderer(500, 500, "synthesizer");

	if (!gladLoadGLLoader((GLADloadproc(glfwGetProcAddress)))) {
		return 0;
	}

	renderer.ImGuiInit();

	const char* waveforms[] = {"Sine", "Sawtooth", "Square", "Triangle", "Noise"};
	static const char* selectedWaveform = waveforms[0];
	while (!renderer.ShouldClose()) {
		glClearColor(0.0f,0.0f,0.0f,0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		renderer.ImGuiNewFrame();
		ImGui::Begin("synth window");

		Serial serial = Serial("\\\\.\\COM3", CBR_9600);

		if (!serial.WriteSerialPort("255")) {

			printf("meow\n");
		}

		if (ImGui::BeginCombo("Default Waveform", selectedWaveform)) {
			for (int i = 0; i < IM_ARRAYSIZE(waveforms); i++) {
				bool selected = (selectedWaveform == waveforms[i]);
				if (ImGui::Selectable(waveforms[i], selected))
					selectedWaveform = waveforms[i];
				if (selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}
		std::string generate = "Generate ";
		generate.append(selectedWaveform);
		if (ImGui::Button(generate.c_str())) {
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
		
		ImGui::End();

		renderer.ImGuiRender();

		renderer.Render();
	}
	glfwTerminate();
	return 0;
}