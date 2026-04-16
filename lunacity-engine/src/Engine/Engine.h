#pragma once
#include <GLFW/glfw3.h>
#include "../Game/Game.h"

class Engine {
private:
    GLFWwindow* window;
    bool running;
    Game* game;
    double lastTime;

public:
    Engine();
    ~Engine();
    bool Init(int width, int height, const char* title);
    void Run();
    void Shutdown();
};