#pragma once
#include <random>
#include <vector>

class GameObject;
class TextRenderer;
class SpriteRenderer;
class Transform;

class Game {
private:
    GameObject* food;
    std::vector<GameObject*> snakeSegments;
    GameObject* scoreText;
    GameObject* statusText;
    TextRenderer* scoreRenderer;
    TextRenderer* statusRenderer;
    SpriteRenderer* foodRenderer;
    Transform* foodTransform;
    int score;
    int pendingGrowth;
    int gridWidth;
    int gridHeight;
    int cellSize;
    float moveTimer;
    float moveInterval;
    bool gameOver;
    int directionX;
    int directionY;
    int queuedDirectionX;
    int queuedDirectionY;
    std::mt19937 randomEngine;

    void Reset();
    void HandleInput();
    void StepSnake();
    void UpdateVisuals();
    void SpawnFood();
    bool IsSnakeCell(int cellX, int cellY) const;
    void SetDirection(int newX, int newY);
    void ClearSnake();
    void CreateInitialSnake();
    void UpdateText();

public:
    Game();
    ~Game();

    void Update(float deltaTime);
    void Render();

    int GetScore() const { return score; }
};
