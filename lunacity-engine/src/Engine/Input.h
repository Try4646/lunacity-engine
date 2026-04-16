#pragma once
#include <GLFW/glfw3.h>

class Input {
private:
    static bool keys[1024];

public:
    static void Update(GLFWwindow* window);
    static bool GetKey(int key);
    static bool GetKeyDown(int key);
};