#pragma once 
#include "../Component.h"
#include <vector>
class GameObject;
class Coin;
class CoinSpawner : public Component {
public:
	CoinSpawner();
	void Update(float deltaTime) override;
	void Start() override;
	void SpawnCoin();
	int TotalCoinsActive;
	std::vector <GameObject*>* coinsStorage;
private:

};
