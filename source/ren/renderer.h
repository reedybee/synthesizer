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
    // Default Constructor
    Renderer(int width, int height, const char* title);
    // Clears the framebuffers specified and clears the color buffer bit to the color specified
    void ClearFramebuffer(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 0.0f, int flags = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Returns the close flag, if true, the window has been told to close
    bool ShouldClose();
    // Returns the GLFW window
    GLFWwindow* GetWindow();
    // Swaps the buffers and polls any events
    void Render();

    ~Renderer();

    // how to interface with imgui from within the renderer
    
    // Initializes ImGui
    void ImGuiInit();
    // Creates a new frame for ImGui
    void ImGuiNewFrame();
    // Renders the ImGui context
    void ImGuiRender();

    void ImGuiTerminate();

private:
    GLFWwindow* window;
};