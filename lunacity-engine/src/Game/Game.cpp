#include "Game.h"
#include "../Engine/Input.h"
#include <GLFW/glfw3.h>
#include <math.h>

Game::Game() {
    playerX = 400;
    playerY = 300;
    playerWidth = 50;
    playerHeight = 50;
    speed = 300.0f; 
}

void Game::Update(float deltaTime) {
    float move = speed * deltaTime;

    if (Input::GetKey(GLFW_KEY_W)) playerY -= move;
    if (Input::GetKey(GLFW_KEY_S)) playerY += move;
    if (Input::GetKey(GLFW_KEY_A)) playerX -= move;
    if (Input::GetKey(GLFW_KEY_D)) playerX += move;



    // walls  
    if (playerX < 0) playerX = 0;
    if (playerX > 800 - playerWidth) playerX = 800 - playerWidth;
    if (playerY < 0) playerY = 0;
    if (playerY > 600 - playerHeight) playerY = 600 - playerHeight;
}

void Game::Render() {
    //Player
    glColor3f(0.2f, 0.8f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(playerX, playerY);
    glVertex2f(playerX + playerWidth, playerY);
    glVertex2f(playerX + playerWidth, playerY + playerHeight);
    glVertex2f(playerX, playerY + playerHeight);
    glEnd();

    //coin 
    glColor3f(1.0f, 0.8f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(700, 100);  //middle 
    for (int i = 0; i <= 20; i++) {
        float angle = 3.14159f * 2 * i / 20;
        float x = 700 + cos(angle) * 15;
        float y = 100 + sin(angle) * 15;
        glVertex2f(x, y);
    }
    glEnd();
}

void Game::HandleInput() {
    
}