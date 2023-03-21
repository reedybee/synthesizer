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
    Serial(char* comport, DWORD baudRate);

    std::string ReadSerialPort(int replyWaitTime);
    bool WriteSerialPort(char* data);
    bool CloseSerial();
    bool connected;

    ~Serial();
private:
    HANDLE ioHandler;
    COMSTAT status;
    DWORD errors;

    char frontDelimiter;
	char endDelimiter;
};