#include "../Engine/Engine.h"
#include "../Engine/Input.h"
#include "../Game/Game.h"
#include <iostream>

Engine::Engine() : window(nullptr), running(false), game(nullptr), lastTime(0) {}

Engine::~Engine() {}

bool Engine::Init(int width, int height, const char* title) {
    if (!glfwInit()) return false;

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);

    // 2D Setup
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    game = new Game();
    running = true;
    lastTime = glfwGetTime();
    return true;
}

void Engine::Run() {
    while (running && !glfwWindowShouldClose(window)) {
        double currentTime = glfwGetTime(); //dk
        float deltaTime = (float)(currentTime - lastTime);
        lastTime = currentTime;

        // Input updaten
        Input::Update(window);

        // Spiel-Logik updaten
        game->Update(deltaTime);
        //game->HandleInput();

        // Rendern
        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        game->Render();

        glfwSwapBuffers(window);
        glfwPollEvents();

        // ESC check
        if (Input::GetKey(GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window, true);
        }
    }
}

void Engine::Shutdown() {
    delete game;
    if (window) glfwDestroyWindow(window);
    glfwTerminate();
}