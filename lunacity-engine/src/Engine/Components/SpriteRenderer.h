#pragma once
#include "../Component.h"

class GameObject;
class Transform;

class SpriteRenderer : public Component {
private:
    float r, g, b, a;
    float width, height;

public:
    SpriteRenderer();

    void SetColor(float red, float green, float blue, float alpha = 1.0f);
    void SetSize(float w, float h);

    void Render() override;
};