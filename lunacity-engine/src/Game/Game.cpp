#include "Game.h"
#include "../Engine/GameObject.h"
#include "../Engine/Transform.h"
#include "../Engine/Components/SpriteRenderer.h"
#include "../Engine/Components/TextRenderer.h"
#include "../Engine/Input.h"
#include <GLFW/glfw3.h>
#include <algorithm>
#include <chrono>
#include <string>
#include <vector>

namespace {
    constexpr int kWindowWidth = 800;
    constexpr int kWindowHeight = 600;

    float CellCenter(int cell, int cellSize) {
        return cell * cellSize + cellSize * 0.5f;
    }

    int ToCell(float position, int cellSize) {
        return static_cast<int>(position / cellSize);
    }
}

class SnakeSegment : public GameObject {
public:
    explicit SnakeSegment(const std::string& name) : GameObject(name) {
        width = 18.0f;
        height = 18.0f;

        AddComponent<Transform>();
        auto* renderer = AddComponent<SpriteRenderer>();
        renderer->SetSize(width, height);
        renderer->SetColor(0.2f, 0.8f, 0.3f, 1.0f);
    }
};

Game::Game()
    : food(nullptr),
      scoreText(nullptr),
      statusText(nullptr),
      scoreRenderer(nullptr),
      statusRenderer(nullptr),
      foodRenderer(nullptr),
      foodTransform(nullptr),
      score(0),
      pendingGrowth(0),
      gridWidth(kWindowWidth / 20),
      gridHeight(kWindowHeight / 20),
      cellSize(20),
      moveTimer(0.0f),
      moveInterval(0.11f),
      gameOver(false),
      directionX(1),
      directionY(0),
      queuedDirectionX(1),
      queuedDirectionY(0),
      randomEngine(static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count())) {
    food = new GameObject("Food");
    food->width = 16.0f;
    food->height = 16.0f;
    foodTransform = food->AddComponent<Transform>();
    foodRenderer = food->AddComponent<SpriteRenderer>();
    foodRenderer->SetSize(food->width, food->height);
    foodRenderer->SetColor(0.95f, 0.15f, 0.2f, 1.0f);

    scoreText = new GameObject("ScoreText");
    scoreText->x = 20.0f;
    scoreText->y = 36.0f;
    scoreRenderer = scoreText->AddComponent<TextRenderer>();
    scoreRenderer->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

    statusText = new GameObject("StatusText");
    statusText->x = 20.0f;
    statusText->y = 70.0f;
    statusRenderer = statusText->AddComponent<TextRenderer>();
    statusRenderer->SetColor(0.8f, 0.9f, 1.0f, 1.0f);

    Reset();
}

Game::~Game() {
    ClearSnake();
    delete food;
    delete scoreText;
    delete statusText;
}

void Game::ClearSnake() {
    for (GameObject* segment : snakeSegments) {
        delete segment;
    }
    snakeSegments.clear();
}

void Game::CreateInitialSnake() {
    const int startX = gridWidth / 2;
    const int startY = gridHeight / 2;

    for (int i = 0; i < 4; ++i) {
        GameObject* segment = new SnakeSegment(i == 0 ? "SnakeHead" : "SnakeBody");
        segment->x = CellCenter(startX - i, cellSize);
        segment->y = CellCenter(startY, cellSize);
        segment->GetComponent<Transform>()->SetPosition(segment->x, segment->y);
        snakeSegments.push_back(segment);
    }

    UpdateVisuals();
}

void Game::Reset() {
    ClearSnake();
    score = 0;
    pendingGrowth = 0;
    moveTimer = 0.0f;
    moveInterval = 0.11f;
    gameOver = false;
    directionX = 1;
    directionY = 0;
    queuedDirectionX = 1;
    queuedDirectionY = 0;
    CreateInitialSnake();
    SpawnFood();
    UpdateText();
}

void Game::SetDirection(int newX, int newY) {
    if (newX == 0 && newY == 0) {
        return;
    }

    if (newX == -directionX && newY == -directionY) {
        return;
    }

    queuedDirectionX = newX;
    queuedDirectionY = newY;
}

void Game::HandleInput() {
    if (Input::GetKey(GLFW_KEY_UP)) {
        SetDirection(0, -1);
    }
    else if (Input::GetKey(GLFW_KEY_DOWN)) {
        SetDirection(0, 1);
    }
    else if (Input::GetKey(GLFW_KEY_LEFT)) {
        SetDirection(-1, 0);
    }
    else if (Input::GetKey(GLFW_KEY_RIGHT)) {
        SetDirection(1, 0);
    }
    else if (Input::GetKey(GLFW_KEY_W)) {
        SetDirection(0, -1);
    }
    else if (Input::GetKey(GLFW_KEY_S)) {
        SetDirection(0, 1);
    }
    else if (Input::GetKey(GLFW_KEY_A)) {
        SetDirection(-1, 0);
    }
    else if (Input::GetKey(GLFW_KEY_D)) {
        SetDirection(1, 0);
    }
}

bool Game::IsSnakeCell(int cellX, int cellY) const {
    for (GameObject* segment : snakeSegments) {
        if (ToCell(segment->x, cellSize) == cellX && ToCell(segment->y, cellSize) == cellY) {
            return true;
        }
    }

    return false;
}

void Game::SpawnFood() {
    std::vector<std::pair<int, int>> openCells;
    openCells.reserve(gridWidth * gridHeight);

    for (int y = 0; y < gridHeight; ++y) {
        for (int x = 0; x < gridWidth; ++x) {
            if (!IsSnakeCell(x, y)) {
                openCells.emplace_back(x, y);
            }
        }
    }

    if (openCells.empty()) {
        gameOver = true;
        UpdateText();
        return;
    }

    std::uniform_int_distribution<size_t> distribution(0, openCells.size() - 1);
    const std::pair<int, int>& foodCell = openCells[distribution(randomEngine)];

    food->x = CellCenter(foodCell.first, cellSize);
    food->y = CellCenter(foodCell.second, cellSize);
    foodTransform->SetPosition(food->x, food->y);
}

void Game::UpdateVisuals() {
    for (size_t i = 0; i < snakeSegments.size(); ++i) {
        GameObject* segment = snakeSegments[i];
        Transform* transform = segment->GetComponent<Transform>();
        SpriteRenderer* renderer = segment->GetComponent<SpriteRenderer>();
        transform->SetPosition(segment->x, segment->y);

        if (i == 0) {
            renderer->SetColor(0.35f, 0.95f, 0.45f, 1.0f);
            renderer->SetSize(18.0f, 18.0f);
        }
        else {
            renderer->SetColor(0.15f, 0.7f, 0.3f, 1.0f);
            renderer->SetSize(16.0f, 16.0f);
        }
    }
}

void Game::UpdateText() {
    scoreRenderer->SetText("Score: " + std::to_string(score));

    if (gameOver) {
        statusRenderer->SetText("Game Over  Press Space to restart");
    }
    else {
        statusRenderer->SetText("Arrow Keys or WASD");
    }
}

void Game::StepSnake() {
    directionX = queuedDirectionX;
    directionY = queuedDirectionY;

    std::vector<std::pair<int, int>> previousCells;
    previousCells.reserve(snakeSegments.size());

    for (GameObject* segment : snakeSegments) {
        previousCells.emplace_back(ToCell(segment->x, cellSize), ToCell(segment->y, cellSize));
    }

    int nextHeadX = previousCells.front().first + directionX;
    int nextHeadY = previousCells.front().second + directionY;

    if (nextHeadX < 0 || nextHeadX >= gridWidth || nextHeadY < 0 || nextHeadY >= gridHeight) {
        gameOver = true;
        UpdateText();
        return;
    }

    size_t collisionLimit = snakeSegments.size();
    if (pendingGrowth == 0 && collisionLimit > 0) {
        collisionLimit -= 1;
    }

    for (size_t i = 0; i < collisionLimit; ++i) {
        if (previousCells[i].first == nextHeadX && previousCells[i].second == nextHeadY) {
            gameOver = true;
            UpdateText();
            return;
        }
    }

    bool ateFood = ToCell(food->x, cellSize) == nextHeadX && ToCell(food->y, cellSize) == nextHeadY;
    if (ateFood) {
        pendingGrowth += 1;
        score += 1;
        if (moveInterval > 0.05f) {
            moveInterval -= 0.003f;
        }
    }

    snakeSegments[0]->x = CellCenter(nextHeadX, cellSize);
    snakeSegments[0]->y = CellCenter(nextHeadY, cellSize);

    for (size_t i = 1; i < snakeSegments.size(); ++i) {
        snakeSegments[i]->x = CellCenter(previousCells[i - 1].first, cellSize);
        snakeSegments[i]->y = CellCenter(previousCells[i - 1].second, cellSize);
    }

    if (pendingGrowth > 0) {
        GameObject* segment = new SnakeSegment("SnakeBody");
        const auto& tailCell = previousCells.back();
        segment->x = CellCenter(tailCell.first, cellSize);
        segment->y = CellCenter(tailCell.second, cellSize);
        segment->GetComponent<Transform>()->SetPosition(segment->x, segment->y);
        snakeSegments.push_back(segment);
        pendingGrowth -= 1;
    }

    UpdateVisuals();

    if (ateFood) {
        SpawnFood();
    }

    UpdateText();
}

void Game::Update(float deltaTime) {
    if (gameOver) {
        if (Input::GetKey(GLFW_KEY_SPACE)) {
            Reset();
        }
        return;
    }

    HandleInput();
    moveTimer += deltaTime;

    while (moveTimer >= moveInterval && !gameOver) {
        moveTimer -= moveInterval;
        StepSnake();
    }
}

void Game::Render() {
    for (GameObject* segment : snakeSegments) {
        segment->Render();
    }

    if (!gameOver || !snakeSegments.empty()) {
        food->Render();
    }

    scoreText->Render();
    statusText->Render();
}
