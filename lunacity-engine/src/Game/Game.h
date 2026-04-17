#pragma once
#include <vector>

class GameObject;
class Player;
class Coin;
class TextRenderer;

class Game {
private:
    GameObject* player;
    std::vector<GameObject*> coins;
    GameObject* scoreText;      
    TextRenderer* textRenderer; 
    int score;

public:
    Game();
    ~Game();

    void Update(float deltaTime);
    void Render();

    int GetScore() const { return score; }
};