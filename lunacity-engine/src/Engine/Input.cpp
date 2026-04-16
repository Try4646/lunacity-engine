#include "Input.h"

bool Input::keys[1024] = { false };

void Input::Update(GLFWwindow* window) {
    for (int i = 0; i < 1024; i++) {
        keys[i] = glfwGetKey(window, i) == GLFW_PRESS;
    }
}

bool Input::GetKey(int key) {
    return keys[key];
}