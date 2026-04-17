#pragma once
#include "Component.h"

// Forward Declaration
class GameObject;

class Transform : public Component {
private:
    float posX, posY;
    float scaleX, scaleY;
    float rotation;

public:
    Transform();

    void SetPosition(float x, float y);
    void SetX(float x) { posX = x; }
    void SetY(float y) { posY = y; }
    float GetX() const { return posX; }
    float GetY() const { return posY; }

    void Translate(float dx, float dy);

    void ApplyTransform();
    void ResetTransform();
};