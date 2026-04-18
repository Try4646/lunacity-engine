#include "CoinSpawner.h"
#include "../GameObject.h"
#include "../Transform.h"
#include "../Components/SpriteRenderer.h"

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


CoinSpawner::CoinSpawner() {}




void CoinSpawner::SpawnCoin() {
    float spawnX = static_cast<float>(rand() % 770 + 15);
    float spawnY = static_cast<float>(rand() % 570 + 15);

    Coin* newCoin = new Coin(spawnX, spawnY);

    if (!coinsStorage) {
        return;
    }

    coinsStorage->push_back(newCoin);
}
void CoinSpawner::Start() {
    if (!coinsStorage) {
        return;
    }

    SpawnCoin();
}

void CoinSpawner::Update(float delta) {
    if (!coinsStorage) return;

    if (coinsStorage->size() < 3) {
        SpawnCoin();
    }
}