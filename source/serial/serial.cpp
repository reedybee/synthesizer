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

Serial::Serial(const char* comport, DWORD baudRate) {
    connected = false;

    ioHandler = CreateFileA((LPCSTR)comport, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (ioHandler == INVALID_HANDLE_VALUE) {
        if (GetLastError() == ERROR_FILE_NOT_FOUND)
            std::cout << comport << " not available or doesn't exist.\n";
    } else {
        DCB serialParams = { 0 };
        if (!GetCommState(ioHandler, &serialParams)) {
            std::cout << "Failed to get current serial parameters.\n";
        } else {
            serialParams.BaudRate = baudRate;
            serialParams.ByteSize = 8;
            serialParams.StopBits = ONESTOPBIT;
            serialParams.Parity = NOPARITY;
            serialParams.fDtrControl = DTR_CONTROL_ENABLE;

            if (!SetCommState(ioHandler, &serialParams)) {
                std::cout << "Could not set serial parameters.\n";
            } else {
                connected = true;
                PurgeComm(ioHandler, PURGE_RXCLEAR | PURGE_TXCLEAR);
            }
        }
    }
}

std::string Serial::ReadSerialPort(int replyWaitTime) {
    DWORD bytesRead;
    char msg[1];
    std::string completemsg;
    bool began = false;

    unsigned long startTime = time(nullptr);

    ClearCommError(ioHandler, &errors, &status);

    while ((time(nullptr) - startTime) < replyWaitTime) {
        if (status.cbInQue > 0) {
            if (ReadFile(ioHandler, msg, 1, &bytesRead, NULL)) {
                if (msg[0] == frontDelimiter || began) {
                    began = true;
                    if (msg[0] == endDelimiter)
                        return completemsg;
                    if (msg[0] != frontDelimiter)
                        completemsg.append(msg, 1);
                }
            } else {
                return ("Failed to receive data.\n");
            }
        }
    }
    return completemsg;
}

bool Serial::WriteSerialPort(const char* data) {
    DWORD bytesSent;
    unsigned int dataSentLength = strlen(data);

    if (!WriteFile(ioHandler, (void*)data, dataSentLength, &bytesSent, NULL)) {
        ClearCommError(ioHandler, &errors, &status);
        return false;
    } else {
        return false;
    }
}

bool Serial::CloseSerial() {
    if (connected) {
        connected = false;
        CloseHandle(ioHandler);
        return true;
    } else {
        return false;
    }
}


Serial::~Serial() {
    if (connected) {
        connected = false;
        CloseHandle(ioHandler);
    }
}