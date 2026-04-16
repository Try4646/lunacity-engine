#pragma once

class Game {
private:
    float playerX, playerY;
    float playerWidth, playerHeight;
    float speed;
	int score;

public:
    Game();
    void Update(float deltaTime);
    void Render();
    void HandleInput();
};