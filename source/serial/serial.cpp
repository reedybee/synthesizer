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
#include <cstdlib>

#define _USE_MATH_DEFINES
#include <math.h>

#include <serial/serial.h>

// https://stackoverflow.com/questions/15794422/serial-port-rs-232-connection-in-c

Serial::Serial(const char* comport, unsigned int baudRate) {
    handler = CreateFileA(comport, GENERIC_READ | GENERIC_WRITE,  0, NULL, OPEN_EXISTING, 0, NULL);

    if (handler == INVALID_HANDLE_VALUE) {
        errors = GetLastError();

        switch (errors) {
            case (ERROR_SUCCESS):
                std::cout << "If you manage to trigger this, good job!\n";
            case (ERROR_ACCESS_DENIED):
                std::cout << "Access was denied, another program is most likely using the specified comport.\n"; 
            case (ERROR_FILE_NOT_FOUND):
                std::cout << comport << "was not found.\n"; 
            default:
                std::cout << errors << " has not been specified\n";
        }
    } else {
        DCB params = { 0 };

        if (!GetCommState(handler, &params)) {
            std::cout << "Failed to get serial parameters\n";
        } else {
            params.BaudRate = baudRate;
            params.ByteSize = 8;
            params.StopBits = ONESTOPBIT;
            params.Parity = NOPARITY;
            params.fDtrControl = DTR_CONTROL_ENABLE;

            if (!SetCommState(handler, &params)) {
                std::cout << "Could not set serial parameters.\n";
            } else {
                connected = true;
                PurgeComm(handler, PURGE_RXCLEAR | PURGE_TXCLEAR);
            }
        }

        COMMTIMEOUTS timeouts = { 0 };

        if (!GetCommTimeouts(handler, &timeouts)) {
            std::cout << "Failed to get serial timouts.\n";
        } else {
            // TODO: find defaults
            timeouts.ReadIntervalTimeout = 50;
            timeouts.ReadTotalTimeoutConstant = 50;
            timeouts.ReadTotalTimeoutMultiplier = 50;
            timeouts.WriteTotalTimeoutConstant = 50;
            timeouts.WriteTotalTimeoutMultiplier = 10;

            if (!SetCommTimeouts(handler, &timeouts)) {
                std::cout << "Could not set serial timeouts.\n";
            } else {
                connected = true;
                PurgeComm(handler, PURGE_RXCLEAR | PURGE_TXCLEAR);
            }
        }
    }
}

bool Serial::Write(const char* data) {
    DWORD bytesSent;
    if (!WriteFile(handler, data, strlen(data), &bytesSent, NULL)) {
        std::cout << "Failed to write data.\n";
        ClearCommError(handler, &errors, &status);
        return false;
    } else {
        return true;
    }
}

bool Serial::Write(int data) {
    DWORD bytesSent;
    std::string stringData = std::to_string(data);
    const char* dataChar = stringData.c_str();
    if (!WriteFile(handler, dataChar, strlen(dataChar), &bytesSent, NULL)) {
        std::cout << "Failed to write data.\n";
        ClearCommError(handler, &errors, &status);
        return false;
    } else {
        return true;
    }
}

void Serial::Close() {
    if (connected) {
        connected = false;
        CloseHandle(handler);
    }
}