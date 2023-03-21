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

struct Renderer {
public:
    Renderer(int width, int height, const char* title);

    bool ShouldClose();

    GLFWwindow* GetWindow();

    void ImGuiInit();

    void ImGuiNewFrame();

    void ImGuiRender();

    void Render();
private:
    GLFWwindow* window;
};