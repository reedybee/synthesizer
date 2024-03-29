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
#include <ren/renderer.h>

Renderer::Renderer(int width, int height, const char* title) {
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        std::cout <<  glfwGetError(NULL) << "\n";
    }
    glfwMakeContextCurrent(window);
}

void Renderer::ClearFramebuffer(float r, float g, float b, float a , int flags) {
    glClearColor(r, g, b, a);
    glClear(flags);
}

int Renderer::ShouldClose() {
    return glfwWindowShouldClose(window);
}

GLFWwindow*  Renderer::GetWindow() {
    return window;
}

void Renderer::ImGuiInit() {
    IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO & io = ImGui::GetIO();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();

	ImGui::StyleColorsDark();
}

void Renderer::ImGuiNewFrame() {
    ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Renderer::ImGuiRender() {
    ImGui::End();
    ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Renderer::Render() {
    glfwPollEvents();
    glfwSwapBuffers(window);
}