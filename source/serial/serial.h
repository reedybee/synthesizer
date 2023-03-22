#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <time.h>
#include <fstream>

#define _USE_MATH_DEFINES
#include <math.h>

#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <time.h>
#include <fstream>

#define _USE_MATH_DEFINES
#include <math.h>

struct Serial {
public:
    // Default Constructor
    Serial(const char* comport, unsigned int baudRate);
    // Writes a char* to the comport
    bool Write(const char* data);
    // Writes an int to the comport
    bool Write(int data);
    // Closes the communication with the comport
    void Close();
private:
    HANDLE handler;
    DWORD errors;
};
