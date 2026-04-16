#pragma once
#include <GLFW/glfw3.h>

class Window {
private:
    GLFWwindow* handle;
    int width, height;

public:
    Window();
    bool Create(int w, int h, const char* title);
    void SwapBuffers();
    void PollEvents();
    bool ShouldClose() const;
    void Close();
    GLFWwindow* GetHandle() const { return handle; }
};