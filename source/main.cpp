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

	char name[256];

	const char* waveforms[] = {"Sine", "Sawtooth", "Square", "Triangle", "Noise"};
	static const char* selectedWaveform = waveforms[0];

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glClearColor(0.0f,0.0f,0.0f,0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("synth window");
		ImGui::InputText("File Name", name, sizeof(name));

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
				defaultGenerator.sine(name, 5, frequency);
			if (selectedWaveform == "Sawtooth")
				defaultGenerator.saw(name, 5, frequency);
			if (selectedWaveform == "Square")
				defaultGenerator.square(name, 5, frequency);
			if (selectedWaveform == "Triangle")
				defaultGenerator.triangle(name, 5, frequency);
			if (selectedWaveform == "Noise")
				defaultGenerator.noise(name, 5, frequency);
		}
		if (ImGui::Button("Generate All Default Wave Files")) {
			defaultGenerator.all(frequency);
		}
		
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}