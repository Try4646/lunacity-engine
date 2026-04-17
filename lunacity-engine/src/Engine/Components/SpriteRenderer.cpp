#include "SpriteRenderer.h"
#include "../GameObject.h"      
#include "../Transform.h"
#include <GLFW/glfw3.h>

SpriteRenderer::SpriteRenderer() : r(1), g(1), b(1), a(1), width(50), height(50) {}

void SpriteRenderer::SetColor(float red, float green, float blue, float alpha) {
    r = red;
    g = green;
    b = blue;
    a = alpha;
}

void SpriteRenderer::SetSize(float w, float h) {
    width = w;
    height = h;
}

void SpriteRenderer::Render() {
    glColor4f(r, g, b, a);

    if (owner) {
        Transform* transform = owner->GetComponent<Transform>();
        if (transform) {
            transform->ApplyTransform();
        }
    }

    glBegin(GL_QUADS);
    glVertex2f(-width / 2, -height / 2);
    glVertex2f(width / 2, -height / 2);
    glVertex2f(width / 2, height / 2);
    glVertex2f(-width / 2, height / 2);
    glEnd();

    if (owner) {
        Transform* transform = owner->GetComponent<Transform>();
        if (transform) {
            transform->ResetTransform();
        }
    }
}