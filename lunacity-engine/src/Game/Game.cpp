#include "Game.h"
#include "../Engine/GameObject.h"
#include "../Engine/Transform.h"
#include "../Engine/Components/SpriteRenderer.h"
#include "../Engine/Components/TextRenderer.h"
#include "../Engine/Input.h"
#include <GLFW/glfw3.h>
#include <string>

class Player : public GameObject {
public:
    Player() : GameObject("Player") {
        x = 400; y = 300;
        width = 50; height = 50;

        auto* transform = AddComponent<Transform>();
        transform->SetPosition(x, y);

        auto* renderer = AddComponent<SpriteRenderer>();
        renderer->SetColor(0.2f, 0.8f, 0.2f, 1.0f);
        renderer->SetSize(width, height);
    }

    void Update(float deltaTime) override {
        float speed = 300.0f * deltaTime;

        if (Input::GetKey(GLFW_KEY_W)) y -= speed;
        if (Input::GetKey(GLFW_KEY_S)) y += speed;
        if (Input::GetKey(GLFW_KEY_A)) x -= speed;
        if (Input::GetKey(GLFW_KEY_D)) x += speed;

        if (x < 0) x = 0;
        if (x > 800 - width) x = 800 - width;
        if (y < 0) y = 0;
        if (y > 600 - height) y = 600 - height;

        auto* transform = GetComponent<Transform>();
        transform->SetPosition(x, y);
    }
};

class Coin : public GameObject {
public:
    Coin(float startX, float startY) : GameObject("Coin") {
        x = startX; y = startY;
        width = 30; height = 30;

        auto* transform = AddComponent<Transform>();
        transform->SetPosition(x, y);

        auto* renderer = AddComponent<SpriteRenderer>();
        renderer->SetColor(1.0f, 0.8f, 0.0f, 1.0f);
        renderer->SetSize(width, height);
    }
};

// Game Implementation
Game::Game() : score(0) {
    player = new Player();
    coins.push_back(new Coin(700, 100));
    coins.push_back(new Coin(100, 500));
    coins.push_back(new Coin(650, 450));

    // NUR EINMAL hier erstellen, nicht in Render()!
    scoreText = new GameObject("ScoreText");
    scoreText->x = 20;
    scoreText->y = 50;
    textRenderer = scoreText->AddComponent<TextRenderer>();
    textRenderer->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}

Game::~Game() {
    delete player;
    for (auto* coin : coins) delete coin;
    delete scoreText;
}

void Game::Update(float deltaTime) {
    player->Update(deltaTime);

    // Coin Kollision
    for (auto* coin : coins) {
        if (coin->IsActive() &&
            player->x < coin->x + coin->width &&
            player->x + player->width > coin->x &&
            player->y < coin->y + coin->height &&
            player->y + player->height > coin->y) {
            coin->SetActive(false);
            score++;

            // Score Text aktualisieren
            textRenderer->SetText("Score: " + std::to_string(score));
        }
    }
}

void Game::Render() {
    player->Render();

    for (auto* coin : coins) {
        if (coin->IsActive()) {
            coin->Render();
        }
    }

    // Score Text rendern
    if (scoreText) {
        scoreText->Render();
    }
}