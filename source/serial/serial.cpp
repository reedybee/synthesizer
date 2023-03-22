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

#include <serial/serial.h>

// https://stackoverflow.com/questions/15794422/serial-port-rs-232-connection-in-c

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

#include <serial/serial.h>

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

#include <serial/serial.h>

Serial::Serial(const char* comport, unsigned int baudRate) {
    handler = CreateFileA(comport, GENERIC_READ | GENERIC_WRITE,  0, NULL, OPEN_EXISTING, 0, NULL);

    errors = GetLastError();

    if (GetLastError() == ERROR_ACCESS_DENIED)
		std::cout << "Access was denied\n";
}

bool Serial::Write(const char* data) {
    DWORD bytesSent;
    WriteFile(handler, data, strlen(data), &bytesSent, NULL);
}

bool Serial::Write(int data) {
    DWORD bytesSent;
    std::string stringData = std::to_string(data);
    const char* dataChar = stringData.c_str();
    WriteFile(handler, dataChar, strlen(dataChar), &bytesSent, NULL);
}

void Serial::Close() {

}